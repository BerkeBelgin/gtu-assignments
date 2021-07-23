#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h> 
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <signal.h>

#define F_PERMISSIONS_SIZE 9

struct f_params {
    char *f_path;
    char *f_name_exp;
    int *f_size;
    char *f_type;
    short *f_permissions;
    int *f_link_count;
};

struct f_tree {
    char *f_name;
    struct f_tree *sib;
    struct f_tree *sub;
};

void init_params(struct f_params *params){
    params->f_path = NULL;
    params->f_name_exp = NULL;
    params->f_size = NULL;
    params->f_type = NULL;
    params->f_permissions = NULL;
    params->f_link_count = NULL;
}

void free_params(struct f_params *params){
    free(params->f_path);
    free(params->f_name_exp);
    free(params->f_size);
    free(params->f_type);
    free(params->f_permissions);
    free(params->f_link_count);
}

void init_tree(struct f_tree *node){
    node->f_name = NULL;
    node->sib = NULL;
    node->sub = NULL;
}

void free_tree(struct f_tree *node){
    if(node == NULL) return;
    else {
        free_tree(node->sub);
        free_tree(node->sib);
        free(node->f_name);
        free(node->sub);
        free(node->sib);
    }
}

char toLower(char c){
    if (c >= 'A' && c <= 'Z') c = 'a' + (c - 'A');
    return c;
}

short filename_equals(char* f_name, char* exp){
    if(f_name == NULL || exp == NULL)return 0;
    else {
        int i_s = strlen(f_name);
        int j_s = strlen(exp);

        if(i_s == 0 || j_s == 0 || exp[0] == '+')return 0;
        else {
            int i = 0;
            int j = 0;
            while(i < i_s && j < j_s){
                if(f_name[i] == '+') return 0;
                else if(exp[j] == '+') {
                    if(toLower(f_name[i]) == toLower(exp[j - 1])) i++;
                    else j++;
                } else if(toLower(f_name[i]) == toLower(exp[j])){
                    i++;
                    j++;
                } else return 0;
            }
            if(j < j_s && exp[j] == '+')j++;
            if((i >= i_s && j < j_s) || (i < i_s && j >= j_s))return 0;
            else return 1;
        }
    }
}

//HANDLE ERRORS HERE
struct f_params get_params(int argc, char** argv){
    struct f_params params;
    init_params(&params);

    int n_param = 0;
    int w_param = 0;

    int opt;
    while((opt = getopt(argc, argv, ":w:f:b:t:p:l:")) != -1){ 
        switch(opt){
            case 'w':
                if(optarg != NULL && strlen(optarg) > 0){
                    w_param = 1;
                    params.f_path = (char *) malloc((strlen(optarg) + 1) * sizeof(char));
                    strcpy(params.f_path, optarg);
                }
                break;
            case 'f':
                if(optarg != NULL && strlen(optarg) > 0){
                    n_param++;
                    params.f_name_exp = (char *) malloc((strlen(optarg) + 1) * sizeof(char));
                    strcpy(params.f_name_exp, optarg);
                } else {
                    printf("Warning: Value of %c parameter is not valid. It will be ignored.\n", opt); 
                }
                break;
            case 'b':
                if(optarg != NULL && strlen(optarg) > 0){
                    if(atoi(optarg) >= 0){
                        n_param++;
                        params.f_size = (int *) malloc(sizeof(int));
                        *(params.f_size) = atoi(optarg);
                    } else {
                        printf("Warning: Value of %c parameter must be equal to or greater than 0. It will be ignored.\n", opt);
                    }
                } else {
                    printf("Warning: Value of %c parameter is not valid. It will be ignored.\n", opt); 
                }
                break;
            case 't':
                if(optarg != NULL && strlen(optarg) == 1){
                    switch(optarg[0]){
                        case 'f':
                        case 'd':
                        case 'c':
                        case 'b':
                        case 'p':
                        case 's':
                        case 'l':
                            n_param++;
                            params.f_type = (char *) malloc(sizeof(char));
                            *(params.f_type) = optarg[0];
                            break;
                        default:
                            printf("Warning: Value of %c parameter is not valid. It will be ignored.\n", opt);
                            break;
                    }
                } else {
                    printf("Warning: Value of %c parameter is not valid. It will be ignored.\n", opt);
                }
                break;
            case 'p':
                n_param++;
                if(optarg != NULL && strlen(optarg) == F_PERMISSIONS_SIZE){
                    params.f_permissions = (short *) malloc(F_PERMISSIONS_SIZE * sizeof(short));
                    for(int i = 0; i < F_PERMISSIONS_SIZE; i++){
                        if(optarg[i] != 'r' && optarg[i] != 'w' && optarg[i] != 'x' 
                        && optarg[i] != 'R' && optarg[i] != 'W' && optarg[i] != 'X' && optarg[i] != '-') {
                            printf("Warning: Characters other than \"rwxRWX-\" will be accepted as \"-\" character for %c.\n", opt);
                        }
                    }
                    for(int i = 0; i + 2 < F_PERMISSIONS_SIZE; i+=3){
                        params.f_permissions[i]   = (optarg[i]   == 'r' || optarg[i]   == 'R');
                        params.f_permissions[i+1] = (optarg[i+1] == 'w' || optarg[i+1] == 'W');
                        params.f_permissions[i+2] = (optarg[i+2] == 'x' || optarg[i+2] == 'X');
                    }
                } else {
                    printf("Warning: Value of %c parameter is not valid. It will be ignored.\n", opt);
                }
                break;
            case 'l':
                if(optarg != NULL && strlen(optarg) > 0){
                    if(atoi(optarg) >= 0){
                        n_param++;
                        params.f_link_count = (int *) malloc(sizeof(int));
                        *(params.f_link_count) = atoi(optarg);
                    } else {
                        printf("Warning: Value of %c parameter must be equal to or greater than 0. It will be ignored.\n", opt);
                    }
                } else {
                    printf("Warning: Value of %c parameter is not valid. It will be ignored.\n", opt); 
                }
                break;
            case ':': 
                printf("Warning: %c parameter did not get any value. It will be ignored.\n", opt); 
                break; 
            case '?': 
                printf("Warning: %c parameter could not be recognised. It will be ignored.\n", optopt);
                break; 
        } 
    }

    if(w_param == 0){
        fprintf(stderr, "Error: -W parameter and a directory path must be provided. Program has been terminated.\n");
        exit(0);
    }

    if(n_param == 0){
        fprintf(stderr, "Error: There must bu at least one optional parameter. Program has been terminated.\n");
        exit(0);
    }

    while(optind < argc){
        printf("Warning: %s value does not belong to any parameter. It will be ignored.\n", argv[optind]);
        optind++;
    }

    return params;
}

int short satisfies_params(char * f_name, char *f_path, struct f_params params){
    struct stat file_stat;
    if(stat(f_path, &file_stat) < 0){
 		printf("Warning: File could not be opened. It will be skipped.\n");
 		return 0;
 	} else {
        if(params.f_name_exp != NULL && !filename_equals(f_name, params.f_name_exp)) return 0;
        if(params.f_size != NULL && file_stat.st_size != *(params.f_size)) return 0;
        if(params.f_type != NULL){
            if(S_ISREG(file_stat.st_mode) && *(params.f_type) != 'f') return 0;
		    if(S_ISDIR(file_stat.st_mode) && *(params.f_type) != 'd') return 0;
		    if(S_ISCHR(file_stat.st_mode) && *(params.f_type) != 'c') return 0;
		    if(S_ISBLK(file_stat.st_mode) && *(params.f_type) != 'b') return 0;
		    if(S_ISFIFO(file_stat.st_mode) && *(params.f_type) != 'p') return 0;
		    if(S_ISSOCK(file_stat.st_mode) && *(params.f_type) != 's') return 0;
		    if(S_ISLNK(file_stat.st_mode) && *(params.f_type) != 'l') return 0;
        }
        if(params.f_permissions != NULL){
            if(!params.f_permissions[0] != !(file_stat.st_mode & S_IRUSR)) return 0;
            if(!params.f_permissions[1] != !(file_stat.st_mode & S_IWUSR)) return 0;
            if(!params.f_permissions[2] != !(file_stat.st_mode & S_IXUSR)) return 0;
            if(!params.f_permissions[3] != !(file_stat.st_mode & S_IRGRP)) return 0;
            if(!params.f_permissions[4] != !(file_stat.st_mode & S_IWGRP)) return 0;
            if(!params.f_permissions[5] != !(file_stat.st_mode & S_IXGRP)) return 0;
            if(!params.f_permissions[6] != !(file_stat.st_mode & S_IROTH)) return 0;
            if(!params.f_permissions[7] != !(file_stat.st_mode & S_IWOTH)) return 0;
            if(!params.f_permissions[8] != !(file_stat.st_mode & S_IXOTH)) return 0;
        }
        if(params.f_link_count != NULL && file_stat.st_nlink != *(params.f_link_count)) return 0;
        return 1;
    }
}

struct f_tree *build_tree(const char *path, struct f_params params){
    DIR *dir;
	struct dirent *entry = NULL;

    struct f_tree *root = NULL;
    struct f_tree *end = NULL;

    if(dir = opendir(path)){
        while((entry = readdir(dir)) != NULL){
            if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
                char* f_full_path = (char *) malloc((strlen(path) + strlen(entry->d_name) + 2) * sizeof(char));
                strcpy(f_full_path, path);
                strcat(f_full_path, "/");
                strcat(f_full_path, entry->d_name);
                
                if(entry->d_type == DT_DIR){
                    struct f_tree *children = build_tree(f_full_path, params);
                    if(children != NULL || satisfies_params(entry->d_name, f_full_path, params)){
                        if(end == NULL){
                            root = (struct f_tree *) malloc(sizeof(struct f_tree));
                            end = root;
                        } else {
                            end->sib = (struct f_tree *) malloc(sizeof(struct f_tree));
                            end = end->sib;
                        }
                        init_tree(end);
                        end->f_name = (char *) malloc((strlen(entry->d_name) + 1) * sizeof(char));
                        strcpy(end->f_name, entry->d_name);
                        end->sub = children;
                    }
                } else {
                    if(satisfies_params(entry->d_name, f_full_path, params)){
                        if(end == NULL){
                            root = (struct f_tree *) malloc(sizeof(struct f_tree));
                            end = root;
                        } else {
                            end->sib = (struct f_tree *) malloc(sizeof(struct f_tree));
                            end = end->sib;
                        }
                        init_tree(end);
                        end->f_name = (char *) malloc((strlen(entry->d_name) + 1) * sizeof(char));
                        strcpy(end->f_name, entry->d_name);
                    }
                }
                free(f_full_path);
            }
        }
        closedir(dir);
        return root;
    } else return NULL;
}

void print_tree(struct f_tree *node, int indent){
    if(node == NULL) return;
    else {
        if(indent != 0)printf("|");
        for(int i = 0; i < indent; i++)printf("--");
        printf("%s\n", node->f_name);
        print_tree(node->sub, indent + 1);
        print_tree(node->sib, indent);
    }
}

void int_handler(int sig){
    fprintf(stderr, "\nThe program has been terminated.\n");
    exit(0);
}

int main(int argc, char** argv){
    signal(SIGINT, int_handler);

    struct f_params params = get_params(argc, argv);

    struct f_tree *root = (struct f_tree *) malloc(sizeof(struct f_tree));
    root->sib = NULL;
    root->sub = build_tree(params.f_path, params);
    root->f_name = params.f_path;

    if(root->sub == NULL)printf("No file found.\n");
    else print_tree(root, 0);

    free_tree(root);
    free(root);
    free_params(&params);
    return 0;
}
