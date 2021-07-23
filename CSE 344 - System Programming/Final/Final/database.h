#include <string.h>
#include <strings.h>

#include "llstrarr.h"

#define SELECT_S "SELECT"
#define UPDATE_S "UPDATE"
#define FROM_S "FROM"
#define SET_S "SET"
#define TABLE_S "TABLE"
#define WHERE_S "WHERE"
#define DISTINCT_S "DISTINCT"

#define OTHER_C -1
#define SELECT_C 0
#define UPDATE_C 1
#define FROM_C 2
#define SET_C 3
#define TABLE_C 4
#define WHERE_C 5
#define DISTINCT_C 6

#define ERR_N -1
#define SELECT_N 0
#define UPDATE_N 1

#define ERR_MPTY "SQL Exception\n"

typedef struct dbm {
    llstrarr_t *data;
} dbm_t;

int get_spec_code(char *str){
         if(strcasecmp(str, SELECT_S) == 0)   return SELECT_C;
    else if(strcasecmp(str, UPDATE_S) == 0)   return UPDATE_C;
    else if(strcasecmp(str, FROM_S) == 0)     return FROM_C;
    else if(strcasecmp(str, SET_S) == 0)      return SET_C;
    else if(strcasecmp(str, TABLE_S) == 0)    return TABLE_C;
    else if(strcasecmp(str, WHERE_S) == 0)    return WHERE_C;
    else if(strcasecmp(str, DISTINCT_S) == 0) return DISTINCT_C;
    else                                      return OTHER_C;
}

void init_dbm(struct dbm *dbmo, int col_size){
    dbmo->data = (llstrarr_t *) malloc(sizeof(llstrarr_t));
    init_llstrarr(dbmo->data, col_size);
}

void destroy_dbm(struct dbm *dbmo){
    destroy_llstrarr(dbmo->data);
    free(dbmo->data);
}

void insert(struct dbm *dbmo, char **strv){
    push_back_llstrarr(dbmo->data, strv);
}

int query_type(char *str){
    char cpy_str[strlen(str)+1];
    strcpy(cpy_str, str);

    if(cpy_str != NULL){
        char *tkn = strtok(cpy_str, " ");
        if(tkn != NULL){
            if(strcasecmp(tkn, SELECT_S) == 0)return SELECT_N;
            else if(strcasecmp(tkn, UPDATE_S) == 0)return UPDATE_N;
            else return ERR_N;
        } else return ERR_N;
    } else return ERR_N;
}

static int parse_key_value(char *str, char *col, char *val){
    int eq_found = -1;
    int sqo_found = -1;
    int sqc_found = -1;
    
    for(int i = 0; i < strlen(str); i++){
             if(str[i] == '='  && eq_found  == -1)eq_found = i;
        else if(str[i] == '='  && eq_found  != -1)return -1;
        else if(str[i] == '\'' && sqo_found == -1)sqo_found = i;
        else if(str[i] == '\'' && sqc_found == -1)sqc_found = i;
        else if(str[i] == '\'' && sqc_found != -1)return -1;
    }
    
    if(eq_found  == -1 || sqo_found == -1 || sqc_found == -1)return -1;
    if(eq_found + 1 != sqo_found)return -1;
    if(sqc_found + 1 != strlen(str))return -1;

    for(int i = 0; i < eq_found; i++)col[i] = str[i];
    for(int i = 0; i+sqo_found+1 < sqc_found; i++)val[i] = str[i+sqo_found+1];

    return 0;
}

char *exec_query(struct dbm *dbmo, char *str){
    char cpy_str[strlen(str)+1];
    strcpy(cpy_str, str);

    if(cpy_str != NULL){
        char *tkn;
        if((tkn = strtok(cpy_str, " ")) == NULL){
            char *err_str = (char *) malloc(sizeof(ERR_MPTY));
            strcpy(err_str, ERR_MPTY);
            return err_str;
        }

        if(get_spec_code(tkn) == SELECT_C) {
            if((tkn = strtok(NULL, " ")) == NULL){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }
            
            short distinct = 0;

            if(get_spec_code(tkn) == DISTINCT_C){
                distinct = 1;
                if((tkn = strtok(NULL, " ")) == NULL){
                    char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                    strcpy(err_str, ERR_MPTY);
                    return err_str;
                }
            }
            
            if(get_spec_code(tkn) != OTHER_C){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }
            
            char cols_bdy[sizeof(cpy_str)];
            memset(cols_bdy, '\0', sizeof(cpy_str));

            while(get_spec_code(tkn) != FROM_C){
                strcat(cols_bdy, tkn);
                if((tkn = strtok(NULL, " ")) == NULL || (get_spec_code(tkn) != FROM_C && get_spec_code(tkn) != OTHER_C)){
                    char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                    strcpy(err_str, ERR_MPTY);
                    return err_str;
                }
            }

            if((tkn = strtok(NULL, " ")) == NULL){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }

            for(int i = strlen(tkn)-1; i >= 0; i--){
                if(tkn[i] == ';')tkn[i] = '\0';
                else break;
            }

            if(get_spec_code(tkn) != TABLE_C){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }

            while((tkn = strtok(NULL, " ")) != NULL){
                for(int i = strlen(tkn)-1; i >= 0; i--){
                    if(tkn[i] != ';') {
                        char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                        strcpy(err_str, ERR_MPTY);
                        return err_str;
                    }
                }
            }
            
            int col_idxs[dbmo->data->col_size];
            
            tkn = strtok(cols_bdy, ",");
            if(strcmp(tkn, "*") == 0){
                for(int i = 0; i < dbmo->data->col_size; i++)col_idxs[i] = 1;
            } else {
                for(int i = 0; i < dbmo->data->col_size; i++)col_idxs[i] = 0;
                int idx;
                while(tkn != NULL){
                    idx = get_col_index_llstrarr(dbmo->data, tkn);
                    if(idx != -1){
                        col_idxs[idx] = 1;
                        tkn = strtok(NULL, ",");
                    } else {
                        char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                        strcpy(err_str, ERR_MPTY);
                        return err_str;
                    }
                }
            }

            return get_cols_llstrarr(dbmo->data, dbmo->data->col_size, col_idxs, distinct);
        } else if(get_spec_code(tkn) == UPDATE_C){
            if((tkn = strtok(NULL, " ")) == NULL && get_spec_code(tkn) != TABLE_C){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }
            if((tkn = strtok(NULL, " ")) == NULL && get_spec_code(tkn) != SET_C){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }

            if((tkn = strtok(NULL, " ")) == NULL){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }

            char cols_bdy[sizeof(cpy_str)];
            memset(cols_bdy, '\0', sizeof(cpy_str));
            
            while(get_spec_code(tkn) != WHERE_C){
                strcat(cols_bdy, tkn);
                if((tkn = strtok(NULL, " ")) == NULL){
                    char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                    strcpy(err_str, ERR_MPTY);
                    return err_str;
                }
            }

            char conds_bdy[sizeof(cpy_str)];
            memset(conds_bdy, '\0', sizeof(cpy_str));
            
            while((tkn = strtok(NULL, " ")) != NULL){
                strcat(conds_bdy, tkn);
            }
            
            for(int i = strlen(conds_bdy)-1; i >= 0; i--){
                if(conds_bdy[i] == ';')conds_bdy[i] = '\0';
                else break;
            }

            int col_keys[dbmo->data->col_size];
            char *col_vals[dbmo->data->col_size];

            tkn = strtok(cols_bdy, ",");

            for(int i = 0; i < dbmo->data->col_size; i++){
                col_keys[i] = 0;
                col_vals[i] = (char *) malloc(sizeof(char) * (strlen(tkn)+1));
                memset(col_vals[i], '\0', (strlen(tkn)+1));
            }
            
            char col[strlen(tkn)+1];
            char val[strlen(tkn)+1];

            while(tkn != NULL){
                memset(col, '\0', sizeof(col));
                memset(val, '\0', sizeof(val));

                if(parse_key_value(tkn, col, val) == -1){
                    char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                    strcpy(err_str, ERR_MPTY);
                    return err_str;
                }

                int idx;
                if((idx = get_col_index_llstrarr(dbmo->data, col)) == -1){
                    char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                    strcpy(err_str, ERR_MPTY);
                    return err_str;
                }

                col_keys[idx] = 1;
                strcpy(col_vals[idx], val);

                tkn = strtok(NULL, ",");
            }

            memset(col, '\0', sizeof(col));
            memset(val, '\0', sizeof(val));

            if(parse_key_value(conds_bdy, col, val) == -1){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }
            
            int idx;
            if((idx = get_col_index_llstrarr(dbmo->data, col)) == -1){
                char *err_str = (char *) malloc(sizeof(ERR_MPTY));
                strcpy(err_str, ERR_MPTY);
                return err_str;
            }

            int col_key = idx;
            char col_val[strlen(val)+1];
            strcpy(col_val, val);
            
            char *out = update_cols_llstrarr(dbmo->data, dbmo->data->col_size, col_keys, col_vals, col_key, col_val);
            for(int i = 0; i < dbmo->data->col_size; i++) free(col_vals[i]);

            return out;
        } else {
            char *err_str = (char *) malloc(sizeof(ERR_MPTY));
            strcpy(err_str, ERR_MPTY);
            return err_str;
        }
    } else {
        char *err_str = (char *) malloc(sizeof(ERR_MPTY));
        strcpy(err_str, ERR_MPTY);
        return err_str;
    }
}

void free_query_resp(char *str){
    free_get_llstrarr(str);
}
