/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

/* Definitions */
%{
    // Libraries
    #include <stdbool.h>
    #include "tree.h"
    #include "structures.h"
    #include "symbol_table.h"
    #include "semantics.h"
    #include "y.tab.h"

    // Macros
    #define LINE line++; column = 1;
    #define COLUMN column += yyleng;

    // Global Variables
    bool print = false, send = false, semicol = false, errorSyntax = false;
    int line = 1, column = 1, errorLine = 0, errorColumn = 0, auxColumn = 0, auxLine = 0, errorSemantic = 0;
    extern is_program* head;
%}

/* States */
%X COMMENT1 COMMENT2 STRERROR

/* Rules */
ID                  [a-zA-Z_][a-zA-Z_0-9]*
STRLIT              ([^\r\n\"\\]|(\\f|\\t|\\\\|\\n|\\r|\\\"))*
INTLIT              [1-9][0-9]*|"0"[0-7]*|"0"("x"|"X")[a-fA-F0-9]+
REALLIT             [0-9]+"."([0-9]+)?(("e"|"E")("+"|"-")?[0-9]+)?|[0-9]+("e"|"E")("+"|"-")?[0-9]+|"."[0-9]+(("e"|"E")("+"|"-")?[0-9]+)?
RESERVED            "break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"fallthrough"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"|"++"|"--"
NEWLINE             \n|\r\n|\r
SPACES              " "|\n|\t

/* Subroutines */
%%
";"                 {if (print) printf("SEMICOLON\n"); COLUMN; semicol = false; if (send) return SEMICOLON;}
","                 {if (print) printf("COMMA\n"); COLUMN; semicol = false; if (send) return COMMA;}
"_"                 {if (print) printf("BLANKID\n"); COLUMN; semicol = false; if (send) return BLANKID;}
"="                 {if (print) printf("ASSIGN\n"); yylval.token = insert_token(strdup("Assign"), line, column); COLUMN; semicol = false; if (send) return ASSIGN;}
"*"                 {if (print) printf("STAR\n"); yylval.token = insert_token(strdup("Mul"), line, column); COLUMN; semicol = false; if (send) return STAR;}
"/"                 {if (print) printf("DIV\n"); yylval.token = insert_token(strdup("Div"), line, column); COLUMN; semicol = false; if (send) return DIV;}
"-"                 {if (print) printf("MINUS\n"); yylval.token = insert_token(strdup("Minus"), line, column); COLUMN; semicol = false; if (send) return MINUS;}
"+"                 {if (print) printf("PLUS\n"); yylval.token = insert_token(strdup("Plus"), line, column); COLUMN; semicol = false; if (send) return PLUS;}
"=="                {if (print) printf("EQ\n"); yylval.token = insert_token(strdup("Eq"), line, column); COLUMN; semicol = false; if (send) return EQ;}
">="                {if (print) printf("GE\n"); yylval.token = insert_token(strdup("Ge"), line, column); COLUMN; semicol = false; if (send) return GE;}
">"                 {if (print) printf("GT\n"); yylval.token = insert_token(strdup("Gt"), line, column); COLUMN; semicol = false; if (send) return GT;}
"{"                 {if (print) printf("LBRACE\n"); COLUMN; semicol = false; if (send) return LBRACE;}
"<="                {if (print) printf("LE\n"); yylval.token = insert_token(strdup("Le"), line, column); COLUMN; semicol = false; if (send) return LE;}
"("                 {if (print) printf("LPAR\n"); COLUMN; semicol = false; if (send) return LPAR;}
"["                 {if (print) printf("LSQ\n"); COLUMN; semicol = false; if (send) return LSQ;}
"<"                 {if (print) printf("LT\n"); yylval.token = insert_token(strdup("Lt"), line, column); COLUMN; semicol = false; if (send) return LT;}
"%"                 {if (print) printf("MOD\n"); yylval.token = insert_token(strdup("Mod"), line, column); COLUMN; semicol = false; if (send) return MOD;}
"!="                {if (print) printf("NE\n"); yylval.token = insert_token(strdup("Ne"), line, column); COLUMN; semicol = false; if (send) return NE;}
"!"                 {if (print) printf("NOT\n"); yylval.token = insert_token(strdup("Not"), line, column); COLUMN; semicol = false; if (send) return NOT;}
"&&"                {if (print) printf("AND\n"); yylval.token = insert_token(strdup("And"), line, column); COLUMN; semicol = false; if (send) return AND;}
"||"                {if (print) printf("OR\n"); yylval.token = insert_token(strdup("Or"), line, column); COLUMN; semicol = false; if (send) return OR;}
"}"                 {if (print) printf("RBRACE\n"); COLUMN; semicol = true; if (send) return RBRACE;}
")"                 {if (print) printf("RPAR\n"); COLUMN; semicol = true; if (send) return RPAR;}
"]"                 {if (print) printf("RSQ\n"); COLUMN; semicol = true; if (send) return RSQ;}
"package"           {if (print) printf("PACKAGE\n"); COLUMN; semicol = false; if (send) return PACKAGE;}
"return"            {if (print) printf("RETURN\n"); COLUMN; yylval.token = insert_token(strdup("Return"), line, column); semicol = true; if (send) return RETURN;}
"else"              {if (print) printf("ELSE\n"); COLUMN; semicol = false; if (send) return ELSE;}
"for"               {if (print) printf("FOR\n"); COLUMN; yylval.token = insert_token(strdup("For"), line, column); semicol = false; if (send) return FOR;}
"if"                {if (print) printf("IF\n"); COLUMN; yylval.token = insert_token(strdup("If"), line, column); semicol = false; if (send) return IF;}
"var"               {if (print) printf("VAR\n"); COLUMN; semicol = false; if (send) return VAR;}
"int"               {if (print) printf("INT\n"); COLUMN; semicol = false; if (send) return INT;}
"float32"           {if (print) printf("FLOAT32\n"); COLUMN; semicol = false; if (send) return FLOAT32;}
"bool"              {if (print) printf("BOOL\n"); COLUMN; semicol = false; if (send) return BOOL;}
"string"            {if (print) printf("STRING\n"); COLUMN; semicol = false; if (send) return STRING;}
"fmt.Println"       {if (print) printf("PRINT\n"); COLUMN; yylval.token = insert_token(strdup("fmt.Println"), line, column); semicol = false; if (send) return PRINT;}
"strconv.Atoi"      {if (print) printf("PARSEINT\n"); yylval.token = insert_token(strdup("strconv.Atoi"), line, column); COLUMN; semicol = false; if (send) return PARSEINT;}
"func"              {if (print) printf("FUNC\n"); COLUMN; semicol = false; if (send) return FUNC;}
"os.Args"           {if (print) printf("CMDARGS\n"); COLUMN; semicol = false; if (send) return CMDARGS;}
{RESERVED}          {if (print) printf("RESERVED(%s)\n", yytext); semicol = false; yylval.token = insert_token(strdup(yytext), line, column); COLUMN; if (send) return RESERVED;}
{ID}                {if (print) printf("ID(%s)\n", yytext); semicol = true; yylval.token = insert_token(strdup(yytext), line, column); COLUMN; if (send) return ID;}
\"{STRLIT}\"        {if (print) printf("STRLIT(%s)\n", yytext); semicol = true; yylval.token = insert_token(strdup(yytext), line, column); COLUMN; if (send) return STRLIT;}
{REALLIT}           {if (print) printf("REALLIT(%s)\n", yytext); semicol = true; yylval.token = insert_token(strdup(yytext), line, column); COLUMN; if (send) return REALLIT;}
{INTLIT}            {if (print) printf("INTLIT(%s)\n", yytext); semicol = true; yylval.token = insert_token(strdup(yytext), line, column); COLUMN; if (send) return INTLIT;}
{NEWLINE}           {if (print && semicol) printf("SEMICOLON\n"); auxLine = line; auxColumn = column; LINE; if (semicol) {semicol = false; if (send) return SEMICOLON;} }
{SPACES}            {COLUMN;}
"//"                {BEGIN COMMENT1; COLUMN;}
"/*"                {BEGIN COMMENT2; errorLine = line; errorColumn = column; COLUMN;}
"0"([0-7]*[8-9]+[0-7]*)+  {printf("Line %d, column %d: invalid octal constant (%s)\n", line, column, yytext); COLUMN; semicol = false;}
\"                  {BEGIN STRERROR; errorColumn = column; COLUMN;}
.				    {printf("Line %d, column %d: illegal character (%s)\n", line, column, yytext); COLUMN; semicol = false;}


<STRERROR>{STRLIT}                  {COLUMN;}
<STRERROR>\\.?                      {printf("Line %d, column %d: invalid escape sequence (%s)\n", line, column, yytext); COLUMN; semicol = false;}
<STRERROR>{NEWLINE}                 {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", line, errorColumn); LINE; semicol = false;}
<STRERROR>\"                        {BEGIN 0; COLUMN;}
<STRERROR><<EOF>>                   {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", line, errorColumn); COLUMN; semicol = false;}
            
<COMMENT1>\n        {if (print && semicol) printf("SEMICOLON\n"); BEGIN 0; LINE; if (semicol) {semicol = false; if (send) return SEMICOLON;}}
<COMMENT1>.         {COLUMN;}
<COMMENT2>"*/"      {BEGIN 0; COLUMN;}
<COMMENT2>\n        {if (print && semicol) printf("SEMICOLON\n"); LINE; if (semicol) {semicol = false; if (send) return SEMICOLON;}}
<COMMENT2><<EOF>>   {BEGIN 0; printf("Line %d, column %d: unterminated comment\n", errorLine, errorColumn); COLUMN; semicol = false;}
<COMMENT2>.         {COLUMN;}  
<<EOF>>             {if (print && semicol) printf("SEMICOLON\n"); COLUMN; if (semicol) {semicol = false; if (send) return SEMICOLON;} return EOF;}
%%

// Main
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        // Lexical Analyzer
        if (!strcmp(argv[1], "-l"))
        {
            send = false;
            print = true;
            yylex();
        }

        // Syntax Analyzer
        if (!strcmp(argv[1], "-t"))
        {
            send = true;
            print = false;
            yyparse();

            if (head && !errorSyntax)
                print_program(head, false);
        }

        // Semantic Analyzer
        if (!strcmp(argv[1], "-s"))
        {
            send = true;
            print = false;
            yyparse();
            if (!errorSyntax)
                errorSemantic = check_program(head);
            else
                return 1;

            // Global Symbol Table
            printf("===== Global Symbol Table =====\n");
            show_table(head->symtab);

            // Functions Symbol Table
            is_declarations *tmp = head->u_decl;
            for (; tmp != NULL; tmp = tmp->next)
            {
                if (tmp->u_funcdecl)
                {
                    table_element* aux = search_funcdecl(head->symtab, tmp->u_funcdecl->id->id);
                    if (aux)
                    {
                        printf("===== Function %s(", tmp->u_funcdecl->id->id);
                        print_params(aux->funcdec->params);
                        printf(") Symbol Table =====\n");
                        if (tmp->u_funcdecl->u_type) printf("return\t\t%s\n", tmp->u_funcdecl->u_type);
                        else printf("return\t\tnone\n");
                        show_table(tmp->u_funcdecl->symtab);
                    }
                }
            }

            // Annotated AST
            print_program(head, true);
        }
    }
    else if (argc == 1)
    {
        print = false;
        send = true;
        yyparse();
        check_program(head);
    }
    return 0;
}

// Wrapper
int yywrap()
{
    return 1;
}

// Print Errors
void yyerror(char *string)
{
    errorSyntax = true;
    if (!strcmp(yytext, "\n") || !strcmp(yytext, "\r\n") || !strcmp(yytext, "\r"))
        printf("Line %d, column %d: %s: \n", auxLine, auxColumn, string);
    else
        printf("Line %d, column %d: %s: %s\n", line, column - yyleng, string, yytext);
}
