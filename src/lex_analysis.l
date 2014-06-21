%{
	#include <string.h>
	#include <ctype.h>
	#include "../header/tree.h"
    #include "../header/list.h"
    #include "../header/semantic.h"
    #include "../header/ir.h"
    #include "../header/obj.h"
	#include "syntax_analysis.h"

	int yycolumn = 1;
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;\
		yylloc.first_column = yycolumn;yylloc.last_column = yycolumn + yyleng - 1;\
		yycolumn += yyleng;
	int error_flag = 0;
	int parse_to_dec(int,char*);
	int char_to_val(char);
	tree_node *new_node(char *text,int lineno ,int type);

%}
%option noinput
%option nounput
%option yylineno


linebreak	[\n]
delim 		[ \t]
ws 		{delim}+
letter		[a-zA-z]
digit_D		[0-9]
digit_O		[0-7]
digit_H 	[0-9A-Fa-f]
id 		[_a-zA-Z]([_a-zA-Z]|[0-9])* 

%%

"struct"	{yylval.attr_node = new_node("STRUCT", yylineno,4);	return STRUCT;}

"return"	{yylval.attr_node = new_node("RETURN", yylineno,4);	return RETURN; }		
"if"		{yylval.attr_node = new_node("IF", yylineno,4);	return  IF;}

"else"		{yylval.attr_node = new_node("ELSE", yylineno,4);	return  ELSE;}

"while"		{yylval.attr_node = new_node("WHILE", yylineno,4);	return  WHILE;}

"int"		{yylval.attr_node = new_node("INT", yylineno,4);	return  TYPE;}

"float"		{yylval.attr_node = new_node("FLOAT", yylineno,4);	return  TYPE;}

";"		{yylval.attr_node = new_node("SEMI", yylineno,4);	return  SEMI;}

","		{yylval.attr_node = new_node("COMMA", yylineno,4);return  COMMA;}

"="		{yylval.attr_node = new_node("ASSIGNOP", yylineno,4);	return  ASSIGNOP;}

">"|"<"|">="|"<="|"=="|"!=" 	{yylval.attr_node = new_node(yytext, yylineno,4);	return RELOP; }

"+"		{yylval.attr_node = new_node("PLUS", yylineno,4);	return  PLUS;}

"-"		{yylval.attr_node = new_node("MINUS", yylineno,4);	return  MINUS;}

"*"		{yylval.attr_node = new_node("STAR", yylineno,4);	return  STAR;}

"/"		{yylval.attr_node = new_node("DIV", yylineno,4);	return  DIV;}

"&&"		{yylval.attr_node = new_node("AND", yylineno,4);	return  AND;}

"||"		{yylval.attr_node = new_node("OR", yylineno,4);	return  OR;}

"."		{yylval.attr_node = new_node("DOT", yylineno,4);	return  DOT;}

"!"		{yylval.attr_node = new_node("NOT", yylineno,4);	return  NOT;}

"("		{yylval.attr_node = new_node("LP", yylineno,4);	return  LP;}

")"		{yylval.attr_node = new_node("RP", yylineno,4);	return  RP;}

"["		{yylval.attr_node = new_node("LB", yylineno,4);	return  LB;}

"]"		{yylval.attr_node = new_node("RB", yylineno,4);	return  RB;}

"{"		{yylval.attr_node = new_node("LC", yylineno,4);	return  LC;}

"}"		{yylval.attr_node = new_node("RC", yylineno,4);;	return  RC;}

{linebreak}	{
			yycolumn = 1;	
		}

{ws}		{}

[1-9]{digit_D}*|0		{yylval.attr_node = new_node(yytext, yylineno,1);	return  DEC;}

0([1-7]{digit_O}*|0+)		{yylval.attr_node = new_node(yytext, yylineno,1);	return  OTC;}

0x([1-9A-F]{digit_H}*|0+)	{yylval.attr_node = new_node(yytext, yylineno,1);	return  HEX;}

([1-9]{digit_D}*|0)\.{digit_D}+	{yylval.attr_node = new_node(yytext, yylineno,2);	return  FLOAT;}

{id}				{yylval.attr_node = new_node(yytext, yylineno,3);	return  ID;}

.		{printf("Error Type A at line %d: Mysterious character '%s'\n",yylineno , yytext); error_flag = 1;}

%%

int main(int argc, char **argv){
	if(argc <= 1 )
		return 1;
	FILE *f;
	if(!(f = fopen(argv[1],"r"))){
		perror(argv[1]);
		return 1;
	}
    

	yyrestart(f);
    yyparse();
    if(error_flag == 0){
        semantic_analysis(root);

        if(semantic_error == 0){
            list_init(&codeHead);//初始化intercode链表
            translate_Program(root,ID_table);

            if(ir_error == 0){
                generate_objCode();
            }
        }
        destroy_tree(root);
    }
	return 0;
}

tree_node *new_node(char *text,int lineno ,int type){
	tree_node *p;
	if((p = malloc(sizeof(tree_node))) == NULL){
		printf("fail to malloc\n");
	}
	
	p->type = type;
	p->lineno = lineno;
	if(type == INT_T){
		int result = 0;
		if(strlen(text) <= 1)
			result = atoi(text);
		else{
			if(text[0] == '0' && text [1] == 'x')
				result = parse_to_dec(16,text+2);
			else if(text[0] == '0')
				result = parse_to_dec(8,text+1);
			else
				result = atoi(text);
		}		
		p->int_attr = result;
		
	}
	else if(type == FLOAT_T)
		p->float_attr = atof(text);
	else if(type == ID_T)
		strncpy(p->id_attr,text,MAX_LEN);
	else if(type == OTHER_TERMINAL_T)
		strncpy(p->other_terminal,text,MAX_LEN);
	else{
		printf("tree node attr type error\n");
	}
	
	return p;
}

int parse_to_dec(int ary,char*num){
	int ans = 0;
	int len = strlen(num);
	int i = 0;
	while(i < len){
		int coefficient = 1;
		int j = i;
		while(j-- > 0)
			coefficient *= ary;
		ans += char_to_val(num[len-i-1])*coefficient;
		i++;
	}	
	return ans;
}



int char_to_val(char ch){
	if(ch >= 'a' && ch <= 'z')
		return ch + 10 -'a';
	else if(ch >= 'A' && ch <= 'Z')
		return ch + 10 - 'A';
	else if(ch >= '0' && ch <= '9')
		return ch - '0';	
}











