#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCKC_POW 12
#define MAX_LEN_FNAME 128
#define FAT_EOF -1
#define FAT_MTY -2

#define FS_INFO_IDX 0
#define FS_FAT_IDX 10
#define FS_BLOCKS_IDX 8202

#define DIR_ENTRY_SIZE 32
#define DIR_ENTRY_FILENAME_SIZE 21
#define DIR_ENTRY_ATTRIBUTE_SIZE 1
#define DIR_ENTRY_DATE_TIME_SIZE 4
#define DIR_ENTRY_FIRST_BLOCK_SIZE 2
#define DIR_ENTRY_SIZE_SIZE 4

#define DIR_ENTRY_ATTR_NULL 0
#define DIR_ENTRY_ATTR_DIR 1
#define DIR_ENTRY_ATTR_FILE 2

typedef struct fat12_fs {
    char filename[MAX_LEN_FNAME];
    FILE *fp;
    unsigned int block_size;
    unsigned int block_count;
} fat12_fs_t;

typedef struct dir_entry {
    char filename[DIR_ENTRY_FILENAME_SIZE + 1];
    char attribute;
    char date_time[DIR_ENTRY_DATE_TIME_SIZE];
    short first_block;
    int size;
} dir_entry_t;

static unsigned int pow2(unsigned int n){
    if(n <= 0) return 1;
    else return 2 * pow2(n-1);
}

static short int16_from_str(char *str){
    return ((0x00FF & str[0]) << 8) | (0x00FF & str[1]);
}

static char *int16_to_str(short num, char *str){
    str[0] = (num >> 8) & 0x00FF;
    str[1] = num & 0x00FF;
    return str;
}

static int int32_from_str(char *str){
    return ((0x000000FF & str[0]) << 24) | ((0x000000FF & str[1]) << 16) | ((0x000000FF & str[2]) << 8) | (0x000000FF & str[3]);
}

static char *int32_to_str(int num, char *str){
    str[0] = (num >> 24) & 0x000000FF;
    str[1] = (num >> 16) & 0x000000FF;
    str[2] = (num >> 8) & 0x000000FF;
    str[3] = num & 0x000000FF;
    return str;
}

static int fwr(int buffc, char *buff, FILE *fp){
    for(int i = 0; i < buffc; i++){
        if(fputc((int)buff[i], fp) == EOF)return -1;
    }
    return 0;
}

static int frd(int buffc, char *buff, FILE *fp){
    unsigned char c;
    for(int i = 0; i < buffc; i++){
        if((c = fgetc(fp)) == EOF){
            printf("HERE\n");
            return -1;
        }
        buff[i] = c;
    }
    return 0;
}

static void read_dir_entry(dir_entry_t *dep, char *buff){
    int idx = 0;
    for(int i = 0; i < DIR_ENTRY_FILENAME_SIZE; i++){
        dep->filename[i] = buff[idx];
        idx++;
    }
    dep->filename[DIR_ENTRY_FILENAME_SIZE] = '\0';

    dep->attribute = buff[idx];
    idx++;

    for(int i = 0; i < DIR_ENTRY_DATE_TIME_SIZE; i++){
        dep->date_time[i] = buff[idx];
        idx++;
    }

    char buff2[DIR_ENTRY_FIRST_BLOCK_SIZE];
    for(int i = 0; i < DIR_ENTRY_FIRST_BLOCK_SIZE; i++){
        buff2[i] = buff[idx];
        idx++;
    }
    dep->first_block = int16_from_str(buff2);

    char buff4[DIR_ENTRY_SIZE_SIZE];
    for(int i = 0; i < DIR_ENTRY_SIZE_SIZE; i++){
        buff4[i] = buff[idx];
        idx++;
    }
    dep->size = int32_from_str(buff4);
}

static void write_dir_entry(dir_entry_t *dep, char *buff){
    int idx = 0;
    for(int i = 0; i < DIR_ENTRY_FILENAME_SIZE; i++){
        buff[idx] = dep->filename[i];
        idx++;
    }

    buff[idx] = dep->attribute;
    idx++;

    for(int i = 0; i < DIR_ENTRY_DATE_TIME_SIZE; i++){
        buff[idx] = dep->date_time[i];
        idx++;
    }

    char buff2[DIR_ENTRY_FIRST_BLOCK_SIZE];
    int16_to_str(dep->first_block, buff2);
    for(int i = 0; i < DIR_ENTRY_FIRST_BLOCK_SIZE; i++){
        buff[idx] = buff2[i];
        idx++;
    }

    char buff4[DIR_ENTRY_SIZE_SIZE];
    int32_to_str(dep->size, buff4);
    for(int i = 0; i < DIR_ENTRY_SIZE_SIZE; i++){
        buff[idx] = buff4[i];
        idx++;
    }
}

static void parse_first_rest_path(char *first, char *rest, char *path){
    int frs_idx = (path[0] == '/') ? 1 : 0;
    int mid_idx = frs_idx;
    int lst_idx = strlen(path);

    for(int i = frs_idx; i < lst_idx; i++){
        if(path[i] == '/')break;
        mid_idx++;
    }

    int j = 0;
    for(int i = frs_idx; i < mid_idx; i++){
        first[j] = path[i];
        j++;
    }
    first[j] = '\0';

    j = 0;
    for(int i = mid_idx+1; i < lst_idx; i++){
        rest[j] = path[i];
        j++;
    }
    rest[j] = '\0';
}

static void parse_rest_last_path(char *rest, char *last, char *path){
    int lst_idx = strlen(path);
    int mid_idx = lst_idx-1;
    int frs_idx = (path[0] == '/') ? 1 : 0;
    
    for(int i = lst_idx-1; i >= 0; i--){
        if(path[i] == '/')break;
        mid_idx--;
    }

    int j = 0;
    for(int i = frs_idx; i < mid_idx; i++){
        rest[j] = path[i];
        j++;
    }
    rest[j] = '\0';

    j = 0;
    for(int i = mid_idx+1; i < lst_idx; i++){
        last[j] = path[i];
        j++;
    }
    last[j] = '\0';
}

static short find_empty_fat_idx(fat12_fs_t *fsp){
    short result = -1;
    char buff[2];
    long offset = ftell(fsp->fp);
    fseek(fsp->fp, FS_FAT_IDX, SEEK_SET);
    for(int i = 0; i < fsp->block_count && frd(sizeof(buff), buff, fsp->fp) != 1; i++){
        if(int16_from_str(buff) == FAT_MTY){
            result = i;
            break;
        }
    }
    fseek(fsp->fp, offset, SEEK_SET);
    return result;
}

static short get_fat_val(fat12_fs_t *fsp, short fat_idx){
    char buff[2];
    long offset = ftell(fsp->fp);
    fseek(fsp->fp, FS_FAT_IDX + fat_idx * 2, SEEK_SET);
    frd(sizeof(buff), buff, fsp->fp);
    fseek(fsp->fp, offset, SEEK_SET);
    return int16_from_str(buff);
}

static void set_fat_val(fat12_fs_t *fsp, short fat_idx, short fat_val){
    char buff[2];
    long offset = ftell(fsp->fp);
    fseek(fsp->fp, FS_FAT_IDX + fat_idx * 2, SEEK_SET);
    int16_to_str(fat_val, buff);
    fwr(sizeof(buff), buff, fsp->fp);
    fseek(fsp->fp, offset, SEEK_SET);
}

int create_fat12_fs(fat12_fs_t *fsp, unsigned int block_size, char *filename){
    strcpy(fsp->filename, filename);
    fsp->block_size = block_size * pow2(10);
    fsp->block_count = pow2(BLOCKC_POW);
    if((fsp->fp = fopen(fsp->filename, "w+")) == NULL)return -1;

    char buff[2];

    // block count
    int16_to_str((short) pow2(BLOCKC_POW), buff);
    fwr(sizeof(buff), buff, fsp->fp);

    // block size KB
    int16_to_str((short) block_size, buff);
    fwr(sizeof(buff), buff, fsp->fp);
    
    // free block count
    int16_to_str((short) (pow2(BLOCKC_POW) - 1), buff);
    fwr(sizeof(buff), buff, fsp->fp);
    
    // file count
    int16_to_str(0, buff);
    fwr(sizeof(buff), buff, fsp->fp);

    // dir count
    int16_to_str(0, buff);
    fwr(sizeof(buff), buff, fsp->fp);

    int16_to_str(FAT_EOF, buff);
    fwr(sizeof(buff), buff, fsp->fp);
    
    int16_to_str(FAT_MTY, buff);
    for(int i = 1; i < fsp->block_count; i++)fwr(sizeof(buff), buff, fsp->fp);
    
    char tmp = 0;
    for(int i = 0; i < fsp->block_count * fsp->block_size; i++)fwr(1, &tmp, fsp->fp);
    
    return 0;
}

int open_fat12_fs(fat12_fs_t *fsp, char *filename){
    strcpy(fsp->filename, filename);
    
    if((fsp->fp = fopen(fsp->filename, "r+")) == NULL)return -1;

    char buff[2];
    frd(sizeof(buff), buff, fsp->fp);
    fsp->block_count = int16_from_str(buff);

    frd(sizeof(buff), buff, fsp->fp);
    fsp->block_size = int16_from_str(buff) * pow2(10);
    return 0;
}

int close_fat12_fs(fat12_fs_t *fsp){
    if(fclose(fsp->fp) != 0)return -1;
    return 0;
}

short get_dir_block_idx(fat12_fs_t *fsp, char *dir_path){
    char buff[DIR_ENTRY_SIZE];
    dir_entry_t de;

    char p_first[strlen(dir_path)+1];
    char p_rest[strlen(dir_path)+1];
    parse_first_rest_path(p_first, p_rest, dir_path);

    short dir_block_idx = 0;
    while(strlen(p_first) > 0){
        short found = 0;

        for(short block_idx = dir_block_idx; block_idx != FAT_EOF; block_idx = get_fat_val(fsp, block_idx)){
            fseek(fsp->fp, FS_BLOCKS_IDX + block_idx * fsp->block_size, SEEK_SET);
            for(int i = 0; i < fsp->block_size / DIR_ENTRY_SIZE; i++){
                frd(DIR_ENTRY_SIZE, buff, fsp->fp);
                read_dir_entry(&de, buff);
                if(de.attribute == DIR_ENTRY_ATTR_DIR && strcmp(p_first, de.filename) == 0){
                    found = 1;
                    dir_block_idx = de.first_block;
                    break;
                }
            }
            if(found == 1)break;
        }
        if(found == 0)return -1;

        parse_first_rest_path(p_first, p_rest, p_rest);
    }
    return dir_block_idx;
}

int mkdir(fat12_fs_t *fsp, char *path){
    char parent_path[strlen(path)];
    char dir_name[strlen(path)];

    parse_rest_last_path(parent_path, dir_name, path);

    char buff[DIR_ENTRY_SIZE];
    dir_entry_t de;

    short prev_dir_block_idx = get_dir_block_idx(fsp, parent_path);
    short created = 0;
    
    for(short dir_block_idx = prev_dir_block_idx; dir_block_idx != FAT_EOF; dir_block_idx = get_fat_val(fsp, dir_block_idx)){
        fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size, SEEK_SET);
        for(int i = 0; i < fsp->block_size / DIR_ENTRY_SIZE; i++){
            frd(DIR_ENTRY_SIZE, buff, fsp->fp);
            read_dir_entry(&de, buff);
            if(strcmp(de.filename, dir_name) == 0)return -1;
            if(de.attribute == DIR_ENTRY_ATTR_NULL){
                fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size + i * DIR_ENTRY_SIZE, SEEK_SET);
                strcpy(de.filename, dir_name);
                de.attribute = DIR_ENTRY_ATTR_DIR;
                strcpy(de.date_time, "0000");
                de.first_block = find_empty_fat_idx(fsp);
                set_fat_val(fsp, de.first_block, FAT_EOF);
                de.size = 0;
                
                write_dir_entry(&de, buff);
                fwr(DIR_ENTRY_SIZE, buff, fsp->fp);

                created = 1;
                break;
            }
        }
        if(created == 1)break;

        prev_dir_block_idx = dir_block_idx;
    }

    if(created == 0){
        short new_block = find_empty_fat_idx(fsp);
        set_fat_val(fsp, new_block, FAT_EOF);
        set_fat_val(fsp, prev_dir_block_idx, new_block);

        fseek(fsp->fp, FS_BLOCKS_IDX + new_block * fsp->block_size, SEEK_SET);
                
        strcpy(de.filename, dir_name);
        de.attribute = DIR_ENTRY_ATTR_DIR;
        strcpy(de.date_time, "0000");
        de.first_block = find_empty_fat_idx(fsp);
        set_fat_val(fsp, de.first_block, FAT_EOF);
        de.size = 0;
        
        write_dir_entry(&de, buff);
        fwr(DIR_ENTRY_SIZE, buff, fsp->fp);
    }

    return 1;
}

int write(fat12_fs_t *fsp, char *path, char *file_path){
    char parent_path[strlen(path)];
    char dir_name[strlen(path)];

    parse_rest_last_path(parent_path, dir_name, path);

    char buff[DIR_ENTRY_SIZE];
    dir_entry_t de;

    short prev_dir_block_idx = get_dir_block_idx(fsp, parent_path);
    short created = 0;

    for(short dir_block_idx = prev_dir_block_idx; dir_block_idx != FAT_EOF; dir_block_idx = get_fat_val(fsp, dir_block_idx)){
        fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size, SEEK_SET);
        for(int i = 0; i < fsp->block_size / DIR_ENTRY_SIZE; i++){
            frd(DIR_ENTRY_SIZE, buff, fsp->fp);
            read_dir_entry(&de, buff);
            if(strcmp(de.filename, dir_name) == 0)return -1;
            if(de.attribute == DIR_ENTRY_ATTR_NULL){
                fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size + i * DIR_ENTRY_SIZE, SEEK_SET);
                strcpy(de.filename, dir_name);
                de.attribute = DIR_ENTRY_ATTR_FILE;
                strcpy(de.date_time, "0000");
                de.first_block = find_empty_fat_idx(fsp);
                set_fat_val(fsp, de.first_block, FAT_EOF);
                de.size = 0;
                
                write_dir_entry(&de, buff);
                fwr(DIR_ENTRY_SIZE, buff, fsp->fp);

                created = 1;
                break;
            }
        }
        if(created == 1)break;

        prev_dir_block_idx = dir_block_idx;
    }

    if(created == 0){
        short new_block = find_empty_fat_idx(fsp);
        set_fat_val(fsp, new_block, FAT_EOF);
        set_fat_val(fsp, prev_dir_block_idx, new_block);

        fseek(fsp->fp, FS_BLOCKS_IDX + new_block * fsp->block_size, SEEK_SET);
                
        strcpy(de.filename, dir_name);
        de.attribute = DIR_ENTRY_ATTR_FILE;
        strcpy(de.date_time, "0000");
        de.first_block = find_empty_fat_idx(fsp);
        set_fat_val(fsp, de.first_block, FAT_EOF);
        de.size = 0;
        
        write_dir_entry(&de, buff);
        fwr(DIR_ENTRY_SIZE, buff, fsp->fp);
    }

    short allocd_block_idx = de.first_block;

    FILE *fp_out = fopen(file_path, "r");
    char c;

    do {
        fseek(fsp->fp, FS_BLOCKS_IDX + fsp->block_size * allocd_block_idx, SEEK_SET);
        for(int i = 0; i < fsp->block_size && ((c = fgetc(fp_out)) != EOF); i++){
            fwr(1, &c, fsp->fp);
        }
        short new_block_idx = find_empty_fat_idx(fsp);
        set_fat_val(fsp, allocd_block_idx, new_block_idx);
        set_fat_val(fsp, new_block_idx, FAT_EOF);
        allocd_block_idx = new_block_idx;
    } while(c != EOF);

    fclose(fp_out);

    return 1;
}

int read(fat12_fs_t *fsp, char *path, char *file_path){
    char parent_path[strlen(path)];
    char dir_name[strlen(path)];

    parse_rest_last_path(parent_path, dir_name, path);

    char buff[DIR_ENTRY_SIZE];
    dir_entry_t de;

    short prev_dir_block_idx = get_dir_block_idx(fsp, parent_path);
    short found = 0;

    for(short dir_block_idx = prev_dir_block_idx; dir_block_idx != FAT_EOF; dir_block_idx = get_fat_val(fsp, dir_block_idx)){
        fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size, SEEK_SET);
        for(int i = 0; i < fsp->block_size / DIR_ENTRY_SIZE; i++){
            frd(DIR_ENTRY_SIZE, buff, fsp->fp);
            read_dir_entry(&de, buff);
            if(de.attribute == DIR_ENTRY_ATTR_FILE && strcmp(de.filename, dir_name) == 0){
                found = 1;
                break;
            }
        }
        if(found == 1)break;

        prev_dir_block_idx = dir_block_idx;
    }
    if(found == 0)return 0;

    short allocd_block_idx = de.first_block;

    FILE *fp_out = fopen(file_path, "w");
    char c;
    do {
        fseek(fsp->fp, FS_BLOCKS_IDX + fsp->block_size * allocd_block_idx, SEEK_SET);
        for(int i = 0; i < fsp->block_size && frd(1, &c, fsp->fp) != -1 && c != 0; i++){
            fputc(c, fp_out);
        }
        allocd_block_idx = get_fat_val(fsp, allocd_block_idx);
    } while(allocd_block_idx != FAT_EOF && c != 0);

    fclose(fp_out);

    return 1;
}

int is_dir_empty(fat12_fs_t *fsp, short dir_block_idx){
    int result = 1;
    char buff[DIR_ENTRY_SIZE];
    dir_entry_t de;

    long offset = ftell(fsp->fp);
    fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size, SEEK_SET);

    for(int i = 0; i < (fsp->block_size / DIR_ENTRY_SIZE); i++){
        frd(DIR_ENTRY_SIZE, buff, fsp->fp);
        read_dir_entry(&de, buff);
        if(de.attribute != DIR_ENTRY_ATTR_NULL){
            result = 0;
            break;
        }
    }

    fseek(fsp->fp, offset, SEEK_SET);

    return result;
}

int rmdir(fat12_fs_t *fsp, char *path){
    char parent_path[strlen(path)];
    char dir_name[strlen(path)];

    parse_rest_last_path(parent_path, dir_name, path);

    char buff[DIR_ENTRY_SIZE];
    dir_entry_t de;
    
    int removed = 0;
    
    long cur_offset = -1;
    long prev_offset = -1;

    short dir_block = get_dir_block_idx(fsp, parent_path);

    for(short dir_block_idx = dir_block; dir_block_idx != FAT_EOF; dir_block_idx = get_fat_val(fsp, dir_block_idx)){
        fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size, SEEK_SET);
        for(int i = 0; i < fsp->block_size / DIR_ENTRY_SIZE; i++){
            prev_offset = cur_offset;
            cur_offset = ftell(fsp->fp);

            frd(DIR_ENTRY_SIZE, buff, fsp->fp);
            read_dir_entry(&de, buff);

            if(removed == 0){
                if(strcmp(de.filename, dir_name) == 0 && de.attribute == DIR_ENTRY_ATTR_DIR){
                    if(is_dir_empty(fsp, de.first_block) == 0)return -1;
                    for(int k = 0; k < DIR_ENTRY_SIZE; k++)buff[k] = 0x00;
                    fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size + i * DIR_ENTRY_SIZE, SEEK_SET);
                    fwr(DIR_ENTRY_SIZE, buff, fsp->fp);
                    removed = 1;
                }
            } else {
                fseek(fsp->fp, prev_offset, SEEK_SET);
                fwr(DIR_ENTRY_SIZE, buff, fsp->fp);
                for(int k = 0; k < DIR_ENTRY_SIZE; k++)buff[k] = 0x00;
                fwr(DIR_ENTRY_SIZE, buff, fsp->fp);
            }
        }
    }

    short cur_idx;
    short nxt_idx;

    for(short dir_block_idx = dir_block; dir_block_idx != FAT_EOF; dir_block_idx = get_fat_val(fsp, dir_block_idx)){
        cur_idx = get_fat_val(fsp, dir_block_idx);
        if(cur_idx != FAT_EOF){
            nxt_idx = get_fat_val(fsp, cur_idx);
            if(nxt_idx == FAT_EOF && is_dir_empty(fsp, nxt_idx)){
                set_fat_val(fsp, nxt_idx, FAT_MTY);
                set_fat_val(fsp, cur_idx, FAT_EOF);
            }
        }
    }

    return 1;
}

int del(fat12_fs_t *fsp, char *path){
    char parent_path[strlen(path)];
    char file_name[strlen(path)];

    parse_rest_last_path(parent_path, file_name, path);

    char buff[DIR_ENTRY_SIZE];
    dir_entry_t de;
    
    int removed = 0;
    
    long cur_offset = -1;
    long prev_offset = -1;

    short dir_block = get_dir_block_idx(fsp, parent_path);

    for(short dir_block_idx = dir_block; dir_block_idx != FAT_EOF; dir_block_idx = get_fat_val(fsp, dir_block_idx)){
        fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size, SEEK_SET);
        for(int i = 0; i < fsp->block_size / DIR_ENTRY_SIZE; i++){
            prev_offset = cur_offset;
            cur_offset = ftell(fsp->fp);

            frd(DIR_ENTRY_SIZE, buff, fsp->fp);
            read_dir_entry(&de, buff);

            if(removed == 0){
                if(strcmp(de.filename, file_name) == 0 && de.attribute == DIR_ENTRY_ATTR_FILE){
                    for(int k = 0; k < DIR_ENTRY_SIZE; k++)buff[k] = 0x00;
                    fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size + i * DIR_ENTRY_SIZE, SEEK_SET);
                    fwr(DIR_ENTRY_SIZE, buff, fsp->fp);
                    removed = 1;
                }
            } else {
                fseek(fsp->fp, prev_offset, SEEK_SET);
                fwr(DIR_ENTRY_SIZE, buff, fsp->fp);
                for(int k = 0; k < DIR_ENTRY_SIZE; k++)buff[k] = 0x00;
                fwr(DIR_ENTRY_SIZE, buff, fsp->fp);
            }
        }
    }

    short cur_idx;
    short nxt_idx;

    for(short dir_block_idx = dir_block; dir_block_idx != FAT_EOF; dir_block_idx = get_fat_val(fsp, dir_block_idx)){
        cur_idx = get_fat_val(fsp, dir_block_idx);
        if(cur_idx != FAT_EOF){
            nxt_idx = get_fat_val(fsp, cur_idx);
            if(nxt_idx == FAT_EOF && is_dir_empty(fsp, nxt_idx)){
                set_fat_val(fsp, nxt_idx, FAT_MTY);
                set_fat_val(fsp, cur_idx, FAT_EOF);
            }
        }
    }

    return 1;
}

void dumpe2fs(fat12_fs_t *fsp){
    char buff[2];

    fseek(fsp->fp, FS_INFO_IDX, SEEK_SET);
    frd(2, buff, fsp->fp);
    printf("Blocks: %d\n", int16_from_str(buff));
    frd(2, buff, fsp->fp);
    printf("Block Size: %d\n", int16_from_str(buff));
    frd(2, buff, fsp->fp);
    printf("Free Blocks: %d\n", int16_from_str(buff));
    frd(2, buff, fsp->fp);
    printf("Files: %d\n", int16_from_str(buff));
    frd(2, buff, fsp->fp);
    printf("Directories: %d\n", int16_from_str(buff));
}

void dir(fat12_fs_t *fsp, char *path){
    char buff[DIR_ENTRY_SIZE];
    dir_entry_t de;

    for(short dir_block_idx = get_dir_block_idx(fsp, path); dir_block_idx != FAT_EOF; dir_block_idx = get_fat_val(fsp, dir_block_idx)){
        fseek(fsp->fp, FS_BLOCKS_IDX + dir_block_idx * fsp->block_size, SEEK_SET);
        for(int i = 0; i < fsp->block_size / DIR_ENTRY_SIZE; i++){
            frd(DIR_ENTRY_SIZE, buff, fsp->fp);
            read_dir_entry(&de, buff);
            if(de.attribute != DIR_ENTRY_ATTR_NULL) printf("%s\n", de.filename);
        }
    }
}