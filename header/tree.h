#ifndef __TREE_H_
#define __TREE_H_


#define INT_T 1
#define FLOAT_T 2
#define ID_T 3
#define OTHER_TERMINAL_T 4
#define NONTERMINAL_T 5
#define MAX_LEN 64

struct Nonterminal_node{
	char name[MAX_LEN];
	int num; //num of children
	struct tree_node **node;
};
typedef struct Nonterminal_node Nonterminal_node;

struct tree_node{
	int type;
	int lineno;
	union{
		int int_attr;
		float float_attr;
		char id_attr[MAX_LEN];
		char other_terminal[MAX_LEN];
		Nonterminal_node nt_node;
	};
};
typedef struct tree_node tree_node;
extern tree_node *root;

tree_node *reduce(char *name,int num, ...);
void print_tree(tree_node *p, int depth);
void destroy_tree(tree_node *p);











#endif
