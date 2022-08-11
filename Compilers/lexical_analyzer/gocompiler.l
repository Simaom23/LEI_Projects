/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

/* Definitions */
%{
    // Libraries
    #include <stdbool.h>

    // Macros
    #define LINE line++; column = 1;
    #define COLUMN column += yyleng;
    
    // Global Variables
    bool print = false, semicol = false;
    int line = 1, column = 1, errorLine = 0, errorColumn = 0;
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
";"                 {if (print) printf("SEMICOLON\n"); COLUMN; semicol = false;}
","                 {if (print) printf("COMMA\n"); COLUMN; semicol = false;}
"_"                 {if (print) printf("BLANKID\n"); COLUMN; semicol = false;}
"="                 {if (print) printf("ASSIGN\n"); COLUMN; semicol = false;}
"*"                 {if (print) printf("STAR\n"); COLUMN; semicol = false;}
"/"                 {if (print) printf("DIV\n"); COLUMN; semicol = false;}
"-"                 {if (print) printf("MINUS\n"); COLUMN; semicol = false;}
"+"                 {if (print) printf("PLUS\n"); COLUMN; semicol = false;}
"=="                {if (print) printf("EQ\n"); COLUMN; semicol = false;}
">="                {if (print) printf("GE\n"); COLUMN; semicol = false;}
">"                 {if (print) printf("GT\n"); COLUMN; semicol = false;}
"{"                 {if (print) printf("LBRACE\n"); COLUMN; semicol = false;}
"<="                {if (print) printf("LE\n"); COLUMN; semicol = false;}
"("                 {if (print) printf("LPAR\n"); COLUMN; semicol = false;}
"["                 {if (print) printf("LSQ\n"); COLUMN; semicol = false;}
"<"                 {if (print) printf("LT\n"); COLUMN; semicol = false;}
"%"                 {if (print) printf("MOD\n"); COLUMN; semicol = false;}
"!="                {if (print) printf("NE\n"); COLUMN; semicol = false;}
"!"                 {if (print) printf("NOT\n"); COLUMN; semicol = false;}
"&&"                {if (print) printf("AND\n"); COLUMN; semicol = false;}
"||"                {if (print) printf("OR\n"); COLUMN; semicol = false;}
"}"                 {if (print) printf("RBRACE\n"); COLUMN; semicol = true;}
")"                 {if (print) printf("RPAR\n"); COLUMN; semicol = true;}
"]"                 {if (print) printf("RSQ\n"); COLUMN; semicol = true;}
"package"           {if (print) printf("PACKAGE\n"); COLUMN; semicol = false;}
"return"            {if (print) printf("RETURN\n"); COLUMN; semicol = true;}
"else"              {if (print) printf("ELSE\n"); COLUMN; semicol = false;}
"for"               {if (print) printf("FOR\n"); COLUMN; semicol = false;}
"if"                {if (print) printf("IF\n"); COLUMN; semicol = false;}
"var"               {if (print) printf("VAR\n"); COLUMN; semicol = false;}
"int"               {if (print) printf("INT\n"); COLUMN; semicol = false;}
"float32"           {if (print) printf("FLOAT32\n"); COLUMN; semicol = false;}
"bool"              {if (print) printf("BOOL\n"); COLUMN; semicol = false;}
"string"            {if (print) printf("STRING\n"); COLUMN; semicol = false;}
"fmt.Println"       {if (print) printf("PRINT\n"); COLUMN; semicol = false;}
"strconv.Atoi"      {if (print) printf("PARSEINT\n"); COLUMN; semicol = false;}
"func"              {if (print) printf("FUNC\n"); COLUMN; semicol = false;}
"os.Args"           {if (print) printf("CMDARGS\n"); COLUMN; semicol = false;}
{RESERVED}          {if (print) printf("RESERVED(%s)\n", yytext); COLUMN; semicol = false;}
{ID}                {if (print) printf("ID(%s)\n", yytext); COLUMN; semicol = true;}
\"{STRLIT}\"        {if (print) printf("STRLIT(%s)\n", yytext); COLUMN; semicol = true;}
{REALLIT}           {if (print) printf("REALLIT(%s)\n", yytext); COLUMN; semicol = true;}
{INTLIT}            {if (print) printf("INTLIT(%s)\n", yytext); COLUMN; semicol = true;}
{NEWLINE}           {if (print && semicol) printf("SEMICOLON\n"); LINE; semicol = false;}
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

            
<COMMENT1>\n        {if (print && semicol) printf("SEMICOLON\n"); BEGIN 0; LINE; semicol = false;}
<COMMENT1>.         {COLUMN;}


<COMMENT2>"*/"      {BEGIN 0; COLUMN;}
<COMMENT2>\n        {if (print && semicol) printf("SEMICOLON\n"); LINE; semicol = false;}
<COMMENT2><<EOF>>   {BEGIN 0; printf("Line %d, column %d: unterminated comment\n", errorLine, errorColumn); COLUMN; semicol = false;}
<COMMENT2>.         {COLUMN;}  


<<EOF>>             {if (print && semicol) printf("SEMICOLON\n"); COLUMN; semicol = false; return 0;}
%%

// Main
int main(int argc, char *argv[]){
    if (argc == 2){

        // Print tokens
        if (!strcmp(argv[1], "-l"))
            print = true;
    }

    yylex();
    return 0;
}

// Wraper
int yywrap() {
    return 1;
}
