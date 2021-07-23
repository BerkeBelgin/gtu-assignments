%{

%}
  
%%
^\n return 0;
"and" fprintf(yyout, "KW_AND\n");
"or" fprintf(yyout, "KW_OR\n");
"not" fprintf(yyout, "KW_NOT\n");
"equal" fprintf(yyout, "KW_EQUAL\n");
"less" fprintf(yyout, "KW_LESS\n");
"nil" fprintf(yyout, "KW_NIL\n");
"list" fprintf(yyout, "KW_LIST\n");
"append" fprintf(yyout, "KW_APPEND\n");
"concat" fprintf(yyout, "KW_CONCAT\n");
"set" fprintf(yyout, "KW_SET\n");
"deffun" fprintf(yyout, "KW_DEFFUN\n");
"for" fprintf(yyout, "KW_FOR\n");
"if" fprintf(yyout, "KW_IF\n");
"exit" fprintf(yyout, "KW_EXIT\n");
"load" fprintf(yyout, "KW_LOAD\n");
"disp" fprintf(yyout, "KW_DISP\n");
"true" fprintf(yyout, "KW_TRUE\n");
"false" fprintf(yyout, "KW_FALSE\n");
"+" fprintf(yyout, "OP_PLUS\n");
"-" fprintf(yyout, "OP_MINUS\n");
"/" fprintf(yyout, "OP_DIV\n");
"*" fprintf(yyout, "OP_MULT\n");
"(" fprintf(yyout, "OP_OP\n");
")" fprintf(yyout, "OP_CP\n");
"**" fprintf(yyout, "OP_DBLMULT\n");
"\"" fprintf(yyout, "OP_C\n");
"," fprintf(yyout, "OP_COMMA\n");
";;".* fprintf(yyout, "COMMENT\n");

[0-9]+[a-zA-Z][a-zA-Z0-9]* fprintf(yyout, "ERROR - identifier starting with digit\n");
0[0-9]+ fprintf(yyout, "ERROR - value starting with 0\n");
0|[1-9][0-9]* fprintf(yyout, "VALUE\n");
[a-zA-Z][a-zA-Z0-9]* fprintf(yyout, "IDENTIFIER\n");
" " {}
\t {}
\n {}
. fprintf(yyout, "ERROR - character could not be resolved\n");
%%

int yywrap(){}
int main(int argc, char **argv){
    yyout = fopen("parsed_cpp.txt", "w+");
    if(argc <= 1){
        yyin = stdin;
        yylex();
    } else {
        yyin = fopen(argv[1],"r");
        yylex();
        fclose(yyin);
    }
    fclose(yyout);
    return 0;
}