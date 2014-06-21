/***********
 * this file is the header of intermediate representation
 **/
#ifndef __IR_H__
#define __IR_H__

#include "list.h"
#include "tree.h"
#include "semantic.h"

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;

extern ListHead codeHead;
extern int tmp_cnt;
extern int var_cnt;
extern int label_cnt;

extern int ir_error;

struct Operand_{
    enum{VARIABLE,CONSTANT,SIZE,TEMP,LABEL,FUNCTION,ADDR}kind;//这里的ADDR指形如&v1的操作数，并且&后面必须是v,也就是变量
    union{
        int var_no;
        int value;
        char *func;
    }u;
    int reg_index;//0:not in register; 1-31:in corresponding register
    struct ListHead list;//这个域用来实现arg_list
};

struct InterCode_{
    enum{DEF_LABEL,DEF_FUN,GOTO,RET,ARG,PARAM,READ,WRITE,ASSIGN,ASSIGN_ADDR,
         ASSIGN_MEM,MEM_ASSIGN,DEC_SIZE,ASSIGN_CALL,ADD,SUB,MUL,DIV_,COND_GOTO} kind;
    union{
        Operand one_op;
        struct {Operand op1,op2;} two_op;
        struct {Operand op1,op2,op3;} three_op;
        struct {Operand op1,op2,op3;int relop;} if_goto;// relop:== != < > <= >=
                                                        //       0  1  2 3 4  5
    }u;
    int code_index;//the index of this code
    struct ListHead list;
};


//inter code generate and display
Operand Operand_construct(int,int);
char *print_operand(Operand);
InterCode interCode_construct(int kind,...);
void print_interCode(InterCode);

//translate funtions
void translate_Program(tree_node*,ID_type**);
void translate_Exp(tree_node*,ID_type**,Operand*);
void translate_Stmt(tree_node*,ID_type**);
void translate_Cond(tree_node*,Operand,Operand,ID_type**);
void translate_Args(tree_node*,ID_type**,ListHead*);
void translate_CompSt(tree_node *,ID_type**);
Operand translate_VarDec(tree_node *,ID_type**);
void translate_Array(tree_node *,ID_type**,Operand);

void Optimize_InterCode(ListHead *);
int is_operand_equal(Operand,Operand);



#endif

