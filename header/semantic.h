#ifndef __SEMANTIC_H_
#define __SEMANTIC_H_

#include "tree.h"

#define MAX_ID_LENGTH 64
#define TABLE_SIZE 16384

extern int semantic_error;

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct ID_type ID_type;
typedef struct FieldWrapper FieldWrapper;
//ID defination
struct ID_type{
    char *ID;
    int type;//0:var    1:function  2:struct name
    union{
        struct{Type var; int var_no;} varType;//var_no用来生成中间代码。var_no=2,中间代码对应为v2。
        struct {
            Type retType;
            int param_num;
            Type *param_type;
            int state;//0:declaration 1:definition 2:defined but wrong 
            int funcLine;//函数第一次声明时的行号，当函数只声明未定义时，用于输出错误信息
        }funcType;
        Type structType;
    };
    int is_param;//记录是否是参数，对于数组ID是否是参数会影响到地址运算，例如 a + offset / &a + offset 
    ID_type *next;
};
extern ID_type* ID_table[TABLE_SIZE];//global symbol table

// type defination
// Type定义为指针使得Type_的大小可计算，计算其大小时会无限递归下去。

struct FieldWrapper{
    char *name;
    FieldList head;
    FieldList tail;
};

struct Type_{
    enum {BASIC,ARRAY,STRUCTURE}kind;
    union{
        int basic;//0:int 1:float
        struct {Type elem;int size;} array;
        FieldWrapper structure;
    };
};



struct FieldList_{
    char *name;
    Type type;
    FieldList next;
};

//semantic analysis funtions
void semantic_analysis(tree_node *);
Type specifier_analysis(tree_node *);
void stmt_analysis(tree_node *, Type);//第二个参数为当前函数的返回类型
void compSt_ret_analysis(tree_node *, Type);//同上
Type varDec_analysis(tree_node *, Type, int);//第二个参数为变量之前的类型
                                            //第三个参数用来判断是否将ID插入符号表
                                            //在函数声明时不插入:0,其余插入:1
Type exp_analysis(tree_node *);

//hash funtions
unsigned short hash_pjw(char *);
ID_type * hash_find(char *,int);
void hash_insert(ID_type*);

//other functions
int isTypeEqual(Type,Type);
void print_node(tree_node *);


#endif 
