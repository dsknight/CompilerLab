%{
	#include<ctype.h>
	#include<stdio.h>
	#include<stdarg.h>
	#include"../header/tree.h"
    #include"../header/semantic.h"
	#include"lex_analysis.c"
	
	void yyerror(char*);
    tree_node *root;
 
%}

%locations

/*declared types*/
%union{
	tree_node *attr_node;
}


/*declared tokens*/
%token <attr_node>error
%token <attr_node> DEC OTC HEX 
%token <attr_node> FLOAT 
%token <attr_node> ID TYPE
%token <attr_node>IF ELSE WHILE STRUCT RETURN SEMI COMMA

%right <attr_node>ASSIGNOP
%left <attr_node>OR
%left <attr_node>AND
%left <attr_node>RELOP
%left <attr_node>PLUS MINUS
%left <attr_node>STAR DIV
%right <attr_node>NOT
%left <attr_node>DOT LP RP LB RB LC RC

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%type <attr_node> Program ExtDefList ExtDef ExtDecList
%type <attr_node> Specifier StructSpecifier OptTag Tag
%type <attr_node> VarDec FunDec VarList ParamDec
%type <attr_node> CompSt StmtList Stmt
%type <attr_node> DefList Def DecList Dec
%type <attr_node> Exp Args

%%

Program 	: ExtDefList	 {  $$ = reduce("Program", 1, $1); 
                                root = $$;
                             }
		;
ExtDefList	: ExtDef ExtDefList	 { $$ = reduce("ExtDefList", 2, $1, $2); }
	   	| /*empty*/	{$$ = reduce("ExtDefList",0);}	
		;
ExtDef		: Specifier ExtDecList SEMI	 { $$ = reduce("ExtDef", 3, $1, $2 ,$3); }
		| Specifier SEMI	 { $$ = reduce("ExtDef", 2, $1, $2); }
		| Specifier FunDec CompSt  	{ $$ = reduce("ExtDef", 3, $1, $2, $3); }
        | Specifier FunDec SEMI     { $$ = reduce("ExtDef", 3, $1, $2, $3); }
ExtDecList 	: VarDec	{ $$ = reduce("ExtDecList", 1, $1); }
	    	| VarDec COMMA ExtDecList	{ $$ = reduce("ExtDecList", 3, $1, $2, $3); }

/*Specifiers*/
Specifier  	: TYPE	{ $$ = reduce("Specifier", 1, $1); }
	    	| StructSpecifier	{ $$ = reduce("Specifier", 1, $1); }
StructSpecifier : STRUCT OptTag LC DefList RC	{ $$ = reduce("StructSpecifier", 5, $1, $2,$3,$4,$5); }
		| STRUCT Tag	{ $$ = reduce("StructSpecifier", 2, $1, $2); }
OptTag		: ID	{ $$ = reduce("OptTag", 1, $1); }
		| /*empty*/	{$$ = reduce("OptTag",0);}
Tag		: ID	{ $$ = reduce("Tag", 1, $1); }

/*Declarators*/
VarDec		: ID	{ $$ = reduce("VarDec", 1, $1); }
		| VarDec LB DEC RB	{ $$ = reduce("VarDec", 4, $1, $2 ,$3 ,$4); }
FunDec		: ID LP VarList RP	{ $$ = reduce("FunDec", 4, $1, $2 ,$3 ,$4); }
		| ID LP RP	{ $$ = reduce("FunDec", 3, $1, $2 ,$3); }
        | error RP
VarList  	: ParamDec COMMA VarList	{ $$ = reduce("VarList", 3, $1, $2,$3); }
	  	| ParamDec	{ $$ = reduce("VarList", 1, $1); }
ParamDec        : Specifier VarDec	{ $$ = reduce("ParamDec", 2, $1 ,$2); }

/*Statements*/
CompSt		: LC DefList StmtList RC	{ $$ = reduce("CompSt", 4, $1, $2 ,$3 ,$4); }
		| error RC	
StmtList	: Stmt StmtList		{ $$ = reduce("StmtList", 2, $1, $2); }
		|	{$$ = reduce("StmtList",0);}
Stmt 		: Exp SEMI	{ $$ = reduce("Stmt", 2, $1, $2); }
       		| CompSt	{ $$ = reduce("Stmt", 1, $1); }
		| RETURN Exp SEMI	{ $$ = reduce("Stmt", 3, $1, $2, $3); }
		| IF LP Exp RP Stmt	%prec LOWER_THAN_ELSE 	{ $$ = reduce("Stmt", 5, $1, $2,$3,$4,$5); }
		| IF LP Exp RP Stmt ELSE Stmt 	{ $$ = reduce("Stmt", 7, $1, $2,$3,$4,$5,$6,$7); }
		| WHILE LP Exp RP Stmt 	{ $$ = reduce("Stmt", 5,$1, $2 ,$3 ,$4, $5); }
		| error SEMI 
		| error RP
/*Local Definitions*/
DefList 	: Def DefList { $$ = reduce("DefList", 2, $1, $2); }
	 	|	{$$ = reduce("DefList",0);}
Def		: Specifier DecList SEMI	{ $$ = reduce("Def", 3, $1, $2 ,$3); }
DecList		: Dec			{ $$ = reduce("DecList", 1, $1); }
	 	| Dec COMMA DecList	{ $$ = reduce("DecList", 3, $1, $2,$3); }
Dec		: VarDec		{ $$ = reduce("Dec", 1, $1); }
     		| VarDec ASSIGNOP Exp	{ $$ = reduce("Dec", 3, $1, $2 ,$3); }

/*Expressions*/
Exp 		: Exp ASSIGNOP Exp	{ $$ = reduce("Exp", 3, $1, $2,$3); }
      		| Exp AND Exp 	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| Exp OR Exp	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| Exp RELOP Exp	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| Exp PLUS Exp	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| Exp MINUS Exp	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| Exp STAR Exp	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| Exp DIV Exp	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| LP Exp RP	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| MINUS Exp	{ $$ = reduce("Exp", 2, $1, $2); }
		| NOT Exp	{ $$ = reduce("Exp", 2, $1, $2); }
		| ID LP Args RP	{ $$ = reduce("Exp", 4, $1, $2,$3,$4); }
		| ID LP RP	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| Exp LB Exp RB	{ $$ = reduce("Exp", 4, $1, $2 ,$3 ,$4); }
		| Exp DOT ID	{ $$ = reduce("Exp", 3, $1, $2,$3); }
		| ID	{ $$ = reduce("Exp", 1 ,$1); }
		| DEC	{ $$ = reduce("Exp", 1 ,$1); }
		| OTC	{ $$ = reduce("Exp", 1 ,$1); }
		| HEX	{ $$ = reduce("Exp", 1 ,$1); }
		| FLOAT	{ $$ = reduce("Exp", 1 ,$1); }
Args		: Exp COMMA Args	{ $$ = reduce("Args", 3, $1, $2 ,$3); }
      		| Exp	{ $$ = reduce("Args", 1, $1); }
		| error RP
		

%%

void yyerror(char *msg){
	error_flag = 1;
	printf("Error type B at line %d: %s\n",yylineno,msg);
}


tree_node* reduce(char* name, int num, ...){
	va_list ap;
	tree_node *p;
	int i;

	p = malloc(sizeof(tree_node));
	p->nt_node.node = malloc(num * 4);

	p->type = NONTERMINAL_T;
	p->lineno = 0;

	strncpy(p->nt_node.name,name,MAX_LEN);
	p->nt_node.num = num;

	va_start(ap,num);
	for(i = 0; i < num ; i++)
		p->nt_node.node[i] = va_arg(ap,tree_node*);
	if(num != 0)
		p->lineno = p->nt_node.node[0]->lineno;

	va_end(ap);
	return p;
}


void print_tree(tree_node *p,int depth){
	int i;
	if(p->type == NONTERMINAL_T && p->nt_node.num == 0)
		return ;
	for(i = 0;i < depth;i++)
		printf("  ");
	if(p->type == INT_T)
		printf("INT: %d\n",p->int_attr);
	else if(p->type == FLOAT_T)
		printf("FLOAT: %f\n ",p->float_attr);
	else if(p->type == ID_T)
		printf("ID: %s\n",p->id_attr);
	else if(p->type == OTHER_TERMINAL_T){
		if(strcmp(p->other_terminal,"INT") == 0)
			printf("TYPE: int\n");
		else if(strcmp(p->other_terminal,"FLOAT") == 0)
			printf("TYPE: float\n");
		else
			printf("%s\n",p->other_terminal);
	}
	else if(p->type == NONTERMINAL_T){
		if(p->nt_node.num != 0){
			depth++;
			printf("%s (%d)\n",p->nt_node.name,p->lineno);
			for(i = 0; i < p->nt_node.num; i++)
				print_tree(p->nt_node.node[i],depth);
		}
	}

	
}	


void destroy_tree(tree_node* p){
	int i;
	
	if(!p) return;
	if(p->type == NONTERMINAL_T){
		for(i = 0; i < p->nt_node.num ; i++)
			destroy_tree(p->nt_node.node[i]);
		free(p->nt_node.node);
	}
	free(p); 
}















