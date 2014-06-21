/**********
 * this is the implement of ir
 **/
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "../header/ir.h"
#include "../header/semantic.h"

ListHead codeHead;
int tmp_cnt = 0;
int var_cnt = 0;
int label_cnt = 0;

int ir_error = 0;


static inline void shift_op(Operand op_target,Operand op_src,Operand op_constant){//if target equals src,shift rto constant
    if(op_target->kind == op_src->kind && op_target->u.value == op_src->u.value)
        *op_target = *op_constant;
}

//Optimize
void Optimize_InterCode(ListHead *list){
    ListHead *ptr;

    list_foreach(ptr,list){
        InterCode currCode = list_entry(ptr,struct InterCode_,list);
        if(currCode->u.one_op == NULL)
            continue;
        if(currCode->kind == ASSIGN && ptr->prev != list){
            InterCode prevCode = list_entry(ptr->prev,struct InterCode_,list);
            if(prevCode->kind >= 14 && prevCode->kind <= 17){
                Operand op1 = prevCode->u.three_op.op1;
                Operand op2 = currCode->u.two_op.op2;
                if(op1->kind == TEMP && op2->kind == TEMP && op1->u.value == op2->u.value){//无用赋值
                    prevCode->u.three_op.op1 = currCode->u.two_op.op1;
                    list_del(ptr);
                    ptr = &prevCode->list;
                }
            }
        }
        /*else if(currCode->kind == GOTO && ptr->next != list){
            InterCode nextCode = list_entry(ptr->next,struct InterCode_,list);
            if(nextCode->kind == DEF_LABEL){
                Operand op1 = nextCode->u.one_op;
                Operand op2 = currCode->u.one_op;
                if(op1->kind == op2->kind && op1->u.value == op2->u.value){//跳到下一句
                    list_del(ptr);
                }
            }
        }*/
        else if(currCode->kind >= 14 && currCode->kind <= 17){
            Operand op_left = currCode->u.three_op.op1;
            Operand op2 = currCode->u.three_op.op2;
            Operand op3 = currCode->u.three_op.op3;
            if(op_left->kind == TEMP && op2->kind == CONSTANT && op3->kind == CONSTANT){//可折叠常数
                list_del(ptr);
                Operand op_constant;
                int constant1 = op2->u.value;
                int constant2 = op3->u.value;
                switch(currCode->kind){
                    case 14 :   op_constant = Operand_construct(CONSTANT,constant1 + constant2);break;
                    case 15 :   op_constant = Operand_construct(CONSTANT,constant1 - constant2);break;
                    case 16 :   op_constant = Operand_construct(CONSTANT,constant1 * constant2);break;
                    case 17 :   op_constant = Operand_construct(CONSTANT,constant1 / constant2);break;
                }
                ListHead *ptr_;
                list_foreach(ptr_,list){
                    InterCode code = list_entry(ptr_,struct InterCode_,list);
                    if(code->kind <= 7){
                        Operand op1 = code->u.one_op;
                        if(op1 != NULL)
                            shift_op(op1,op_left,op_constant);
                    }
                    else if(code->kind <= 13){
                        Operand op1 = code->u.two_op.op1;
                        Operand op2 = code->u.two_op.op2;
                        if(op1 != NULL)
                            shift_op(op1,op_left,op_constant);
                        if(op2 != NULL)
                            shift_op(op2,op_left,op_constant);
                    }
                    else if(code->kind <= 18){
                        Operand op1 = code->u.three_op.op1;
                        Operand op2 = code->u.three_op.op2;
                        Operand op3 = code->u.three_op.op3;
                        if(op1 != NULL)
                            shift_op(op1,op_left,op_constant);
                        if(op2 != NULL)
                            shift_op(op2,op_left,op_constant);
                        if(op3 != NULL)
                            shift_op(op3,op_left,op_constant);
                    }
                }
            }

        }
    }

}





//the constructer of Operand
Operand Operand_construct(int kind, int no_val_func){
    Operand currOp = (Operand)malloc(sizeof(struct Operand_));
    assert(kind >= 0 && kind <= 6);
    currOp->kind = kind;
    if(kind == 1 || kind == 2)//constant or size
        currOp->u.value = no_val_func;
    else if(kind == 5)//func
        currOp->u.func = (char *)no_val_func;
    else//var,temp,label,addr
        currOp->u.var_no = no_val_func;
    return currOp;
}

InterCode interCode_construct(int kind,...){
    assert(kind >= 0 && kind <= 18);
    InterCode currCode = (InterCode)malloc(sizeof(struct InterCode_));
    currCode->kind = kind;
    va_list arg_ptr;
    va_start(arg_ptr,kind);
    if(kind <= 7){
        currCode->u.one_op = va_arg(arg_ptr,Operand);
    }
    else if(kind <= 13){
        currCode->u.two_op.op1 = va_arg(arg_ptr,Operand);
        currCode->u.two_op.op2 = va_arg(arg_ptr,Operand);
    }
    else if(kind <= 17){
        currCode->u.three_op.op1 = va_arg(arg_ptr,Operand);
        currCode->u.three_op.op2 = va_arg(arg_ptr,Operand);
        currCode->u.three_op.op3 = va_arg(arg_ptr,Operand);
    }
    else{
        currCode->u.if_goto.op1 = va_arg(arg_ptr,Operand);
        currCode->u.if_goto.op2 = va_arg(arg_ptr,Operand);
        currCode->u.if_goto.op3 = va_arg(arg_ptr,Operand);
        currCode->u.if_goto.relop = va_arg(arg_ptr,int);
        assert(currCode->u.if_goto.relop >= 0 && currCode->u.if_goto.relop <= 5);
    }
    va_end(arg_ptr);

    return currCode;

}

char *print_operand(Operand op){
    if(op == NULL)
        return NULL;
    char *buf = (char*)malloc(50);
    switch(op->kind){
        case 0 : sprintf(buf,"v%d",op->u.var_no);break;
        case 1 : sprintf(buf,"#%d",op->u.value);break;
        case 2 : sprintf(buf,"%d",op->u.value);break;
        case 3 : sprintf(buf,"t%d",op->u.var_no);break;
        case 4 : sprintf(buf,"label%d",op->u.var_no);break;
        case 5 : sprintf(buf,"%s",op->u.func);break;
        case 6 : sprintf(buf,"&v%d",op->u.var_no);
    }
    return buf;
}

void print_interCode(InterCode code){
    if(code->kind <= 7){
        char *op1 = print_operand(code->u.one_op);
        if(!op1)
            return;
        switch(code->kind){    
            case 0 : printf("LABEL %s :\n",op1);break;
            case 1 : printf("FUNCTION %s :\n",op1);break;
            case 2 : printf("GOTO %s\n",op1);break;
            case 3 : printf("RETURN %s\n",op1);break;
            case 4 : printf("ARG %s\n",op1);break;
            case 5 : printf("PARAM %s\n",op1);break;
            case 6 : printf("READ %s\n",op1);break;
            case 7 : printf("WRITE %s\n",op1);break;
        }
        free(op1);
    }
    else if(code->kind <= 13){
        char *op1 = print_operand(code->u.two_op.op1);
        char *op2 = print_operand(code->u.two_op.op2);
        if(code->kind != 13 && (!op1 || !op2))
            return;
        switch(code->kind){
            case 8 : printf("%s := %s\n",op1,op2);break;
            case 9 : printf("%s := &%s\n",op1,op2);break;
            case 10: printf("%s := *%s\n",op1,op2);break;
            case 11: printf("*%s := %s\n",op1,op2);break;
            case 12: printf("DEC %s %s\n",op1,op2);break;
            case 13: {
                        if(op1)
                            printf("%s := CALL %s\n",op1,op2);
                        else{
                            char *op_ = print_operand(Operand_construct(TEMP,++tmp_cnt));
                            printf("%s := CALL %s\n",op_,op2);
                        }
                        break;
                     }
        }
        free(op1);
        free(op2);
    }
    else if(code->kind <= 17){
        char *op1 = print_operand(code->u.three_op.op1);
        char *op2 = print_operand(code->u.three_op.op2);
        char *op3 = print_operand(code->u.three_op.op3);
        if(!op1 || !op2 || !op3)
            return;
        switch(code->kind){
            case 14: printf("%s := %s + %s\n",op1,op2,op3);break;
            case 15: printf("%s := %s - %s\n",op1,op2,op3);break;
            case 16: printf("%s := %s * %s\n",op1,op2,op3);break;
            case 17: printf("%s := %s / %s\n",op1,op2,op3);break;
        }
        free(op1);
        free(op2);
        free(op3);
    }
    else{
        char *op1 = print_operand(code->u.if_goto.op1);
        char *op2 = print_operand(code->u.if_goto.op2);
        char *op3 = print_operand(code->u.if_goto.op3);
        if(!op1 || !op2 || !op3)
            return;
        char relop[6][5] = {"==","!=","<",">","<=",">="};
        printf("IF %s %s %s GOTO %s\n",op1,relop[code->u.if_goto.relop],op2,op3);
        free(op1);
        free(op2);
        free(op3);
    }
}


static inline Operand varOperand(tree_node* ID_node){//返回语法树一个ID节点对应中间代码的变量的operand
    assert(ID_node->type == ID_T);
    ID_type *var = hash_find(ID_node->id_attr,0);
    assert(var != NULL);
    if(var->varType.var_no == 0)
        var->varType.var_no = ++var_cnt;
    Operand op = Operand_construct(VARIABLE,var->varType.var_no);
    return op;
}

static inline void conditionExp(tree_node* Exp, ID_type **table, Operand op){//处理条件表达式 RELOP/NOT/AND/OR
    Operand op_label1 = Operand_construct(LABEL,++label_cnt);
    Operand op_label2 = Operand_construct(LABEL,++label_cnt);
    Operand op_0 = Operand_construct(CONSTANT,0);
    Operand op_1 = Operand_construct(CONSTANT,1);
    InterCode code0 = interCode_construct(ASSIGN,op,op_0);
    list_add_before(&codeHead,&code0->list);
    translate_Cond(Exp,op_label1,op_label2,table);
    InterCode code1 = interCode_construct(DEF_LABEL,op_label1);
    InterCode code2 = interCode_construct(ASSIGN,op,op_1);
    InterCode code3 = interCode_construct(DEF_LABEL,op_label2);
    list_add_before(&codeHead,&code1->list);
    list_add_before(&codeHead,&code2->list);
    list_add_before(&codeHead,&code3->list);
}



void translate_Exp(tree_node *Exp, ID_type **table, Operand* op_place){
    Operand op = (op_place == NULL) ? NULL : (*op_place);
    if(Exp->nt_node.num == 1){
        if(Exp->nt_node.node[0]->type == ID_T){//ID
            Operand op_ = varOperand(Exp->nt_node.node[0]);
            *op_place = op_;
            free(op);
        }
        else if(Exp->nt_node.node[0]->type == INT_T){//INT
            int val = Exp->nt_node.node[0]->int_attr;
            Operand op_ = Operand_construct(CONSTANT,val);
            *op_place = op_;
            free(op);
        }
        else if(Exp->nt_node.node[0]->type == FLOAT_T){//FLOAT
        }
    }
    else if(Exp->nt_node.num == 2){
        if(strcmp(Exp->nt_node.node[0]->other_terminal,"MINUS") == 0){//MINUS Exp
            tree_node *Exp_ = Exp->nt_node.node[1];
            if(Exp_->nt_node.num == 1){//Exp_->INT,Optimize
                if(Exp_->nt_node.node[0]->type == INT_T){
                    int val = -Exp_->nt_node.node[0]->int_attr;
                    Operand op_ = Operand_construct(CONSTANT,val);
                    InterCode code = interCode_construct(ASSIGN,op,op_);
                    list_add_before(&codeHead,&code->list);
                }
                else if(Exp_->nt_node.node[0]->type == ID_T){//Exp_->ID,Optimize  
                    Operand op_var = varOperand(Exp_->nt_node.node[0]);
                    Operand op_ = Operand_construct(CONSTANT,0);
                    InterCode code = interCode_construct(ASSIGN,op,op_,op_var);
                    list_add_before(&codeHead,&code->list);
                }
            }
            else{
                Operand op_tmp = Operand_construct(TEMP,++tmp_cnt);
                translate_Exp(Exp_,table,&op_tmp);
                Operand op_ = Operand_construct(CONSTANT,0);
                InterCode code = interCode_construct(SUB,op,op_,op_tmp);
                list_add_before(&codeHead,&code->list);
            }
        }
        else if(strcmp(Exp->nt_node.node[0]->other_terminal,"NOT") == 0){//NOT Exp
            conditionExp(Exp,table,op);
        }
    }
    else if(Exp->nt_node.num == 3){
        if(strcmp(Exp->nt_node.node[1]->other_terminal,"ASSIGNOP") == 0){//Exp ASSIGNOP Exp
            tree_node *Exp1 = Exp->nt_node.node[0];
            if( Exp1->nt_node.num == 1 && Exp1->nt_node.node[0]->type == ID_T ||     //ID
                Exp1->nt_node.num == 3 && strcmp(Exp1->nt_node.node[1]->other_terminal,"DOT") == 0 ||   // Exp DOT ID
                Exp1->nt_node.num == 4 && strcmp(Exp1->nt_node.node[1]->other_terminal,"LB") == 0){//Exp LB Exp RB
                Operand op_tmp = Operand_construct(TEMP,++tmp_cnt);
                translate_Exp(Exp->nt_node.node[2],table,&op_tmp);
                if(Exp1->nt_node.num == 1){//ID
                    Operand op_var = varOperand(Exp1->nt_node.node[0]);
                    InterCode code1 = interCode_construct(ASSIGN,op_var,op_tmp);
                    InterCode code2 = interCode_construct(ASSIGN,op,op_var);
                    list_add_before(&codeHead,&code1->list);
                    list_add_before(&codeHead,&code2->list);
                }
                else if(Exp1->nt_node.num == 4){//Exp LB Exp RB
                    Operand op_ = Operand_construct(TEMP,++tmp_cnt);
                    translate_Array(Exp1,table,op_);
                    InterCode code1 = interCode_construct(MEM_ASSIGN,op_,op_tmp);
                    InterCode code2 = interCode_construct(ASSIGN_MEM,op,op_);
                    list_add_before(&codeHead,&code1->list);
                    list_add_before(&codeHead,&code2->list);
                }
                else{//other cases remaining
                }
            }
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"AND") == 0){//Exp AND Exp
            conditionExp(Exp,table,op);
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"OR") == 0){//Exp OR Exp
            conditionExp(Exp,table,op);
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"<" ) == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,">" ) == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,"<=") == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,"<=") == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,"==") == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,"!=") == 0 ){//Exp RELOP Exp
                conditionExp(Exp,table,op);
            
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"PLUS") == 0){//Exp PLUS Exp
            tree_node* Exp1 = Exp->nt_node.node[0];
            tree_node*Exp2 = Exp->nt_node.node[2];
            if(Exp1->nt_node.num == 1 && Exp1->nt_node.node[0]->type == INT_T && Exp1->nt_node.node[0]->int_attr == 0){
                translate_Exp(Exp2,table,&op);
                return;
            }
            if(Exp2->nt_node.num == 1 && Exp2->nt_node.node[0]->type == INT_T && Exp2->nt_node.node[0]->int_attr == 0){
                translate_Exp(Exp1,table,&op);
                return;
            }
            Operand op_tmp1 = Operand_construct(TEMP,++tmp_cnt);
            Operand op_tmp2 = Operand_construct(TEMP,++tmp_cnt);
            translate_Exp(Exp->nt_node.node[0],table,&op_tmp1);
            translate_Exp(Exp->nt_node.node[2],table,&op_tmp2);
            InterCode code = interCode_construct(ADD,op,op_tmp1,op_tmp2);
            list_add_before(&codeHead,&code->list);
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"MINUS") == 0){//Exp MINUS Exp
            tree_node* Exp1 = Exp->nt_node.node[0];
            tree_node* Exp2 = Exp->nt_node.node[2];
            if(Exp2->nt_node.num == 1 && Exp2->nt_node.node[0]->type == INT_T && Exp2->nt_node.node[0]->int_attr == 0){
                translate_Exp(Exp1,table,&op);
                return;
            }
            Operand op_tmp1 = Operand_construct(TEMP,++tmp_cnt);
            Operand op_tmp2 = Operand_construct(TEMP,++tmp_cnt);
            translate_Exp(Exp->nt_node.node[0],table,&op_tmp1);
            translate_Exp(Exp->nt_node.node[2],table,&op_tmp2);
            InterCode code = interCode_construct(SUB,op,op_tmp1,op_tmp2);
            list_add_before(&codeHead,&code->list);
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"STAR") == 0){//Exp STAR Exp
            tree_node* Exp1 = Exp->nt_node.node[0];
            tree_node* Exp2 = Exp->nt_node.node[2];
            if(Exp1->nt_node.num == 1 && Exp1->nt_node.node[0]->type == INT_T && Exp1->nt_node.node[0]->int_attr == 1){
                translate_Exp(Exp2,table,&op);
                return;
            }
            if(Exp2->nt_node.num == 1 && Exp2->nt_node.node[0]->type == INT_T && Exp2->nt_node.node[0]->int_attr == 1){
                translate_Exp(Exp1,table,&op);
                return;
            }
            Operand op_tmp1 = Operand_construct(TEMP,++tmp_cnt);
            Operand op_tmp2 = Operand_construct(TEMP,++tmp_cnt);
            translate_Exp(Exp1,table,&op_tmp1);
            translate_Exp(Exp2,table,&op_tmp2);
            InterCode code = interCode_construct(MUL,op,op_tmp1,op_tmp2);
            list_add_before(&codeHead,&code->list);

        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"DIV") == 0){//Exp DIV Exp
            tree_node* Exp1 = Exp->nt_node.node[0];
            tree_node* Exp2 = Exp->nt_node.node[2];
            if(Exp2->nt_node.num == 1 && Exp2->nt_node.node[0]->type == INT_T && Exp2->nt_node.node[0]->int_attr == 1){
                translate_Exp(Exp1,table,&op);
                return;
            }
            Operand op_tmp1 = Operand_construct(TEMP,++tmp_cnt);
            Operand op_tmp2 = Operand_construct(TEMP,++tmp_cnt);
            translate_Exp(Exp->nt_node.node[0],table,&op_tmp1);
            translate_Exp(Exp->nt_node.node[2],table,&op_tmp2);
            InterCode code = interCode_construct(DIV_,op,op_tmp1,op_tmp2);
            list_add_before(&codeHead,&code->list);
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"LP") == 0){//ID LP RP
            char *func = Exp->nt_node.node[0]->id_attr;
            InterCode code;
            if(strcmp(func,"read") == 0){
                code = interCode_construct(READ,op);
            }
            else{
                Operand op_func = Operand_construct(FUNCTION,(int)func);
                code = interCode_construct(ASSIGN_CALL,op,op_func);
            }
            list_add_before(&codeHead,&code->list);
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"DOT") == 0){//Exp DOT ID
            printf("Can not translate the code: Contain structure!\n");
            ir_error = 1;
        }
        else{//LP Exp RP
            translate_Exp(Exp->nt_node.node[1],table,&op);
        }
    }
    else if(Exp->nt_node.num == 4){
        if(strcmp(Exp->nt_node.node[1]->other_terminal,"LB") == 0){//Exp LB Exp RB
            Operand op_ = Operand_construct(TEMP,++tmp_cnt);
            translate_Array(Exp,table,op_);
            InterCode code = interCode_construct(ASSIGN_MEM,op,op_);
            list_add_before(&codeHead,&code->list);
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"LP") == 0){//ID LP Args RP
            char *func = Exp->nt_node.node[0]->id_attr;
            ListHead arg_list;
            list_init(&arg_list);
            translate_Args(Exp->nt_node.node[2],table,&arg_list);
            if(strcmp(func,"write") == 0){
                assert(arg_list.next != &arg_list);
                InterCode code = interCode_construct(WRITE,list_entry(arg_list.next,struct Operand_,list));
                list_add_before(&codeHead,&code->list);
            }
            else{
                ListHead *ptr;
                list_foreach(ptr,&arg_list){
                    InterCode code = interCode_construct(ARG,list_entry(ptr,struct Operand_,list));
                    list_add_before(&codeHead,&code->list);
                }
                Operand op_func = Operand_construct(FUNCTION,(int)func);
                InterCode code = interCode_construct(ASSIGN_CALL,op,op_func);
                list_add_before(&codeHead,&code->list);
            }
        }
    }
}


static inline int currentArrayLen(tree_node* Exp){
    int depth = 0,arrayLen = 4;
    while(Exp->nt_node.num != 1){//直到Exp->ID
        depth ++;
        Exp = Exp->nt_node.node[0];
    }
    tree_node *ID = Exp->nt_node.node[0];
    ID_type *arrayID = hash_find(ID->id_attr,0);
    Type arrayType = arrayID->varType.var;
    while(depth > 0){//找到当前arrayType的起始点
        depth --;
        arrayType = arrayType->array.elem;
    }
    while(arrayType->kind == ARRAY){
        arrayType = arrayType->array.elem;
        if(arrayType->kind == ARRAY)
            arrayLen *= arrayType->array.size;
    }
    return arrayLen;
}

void translate_Array(tree_node* Exp,ID_type** table,Operand op){ //Exp LB Exp RB
    tree_node* Exp1 = Exp->nt_node.node[0];
    tree_node* Exp2 = Exp->nt_node.node[2];
    int length = currentArrayLen(Exp->nt_node.node[0]);
    Operand op_len = Operand_construct(CONSTANT,length);
    Operand op_tmp1 = Operand_construct(TEMP,++tmp_cnt);
    Operand op_offset = Operand_construct(TEMP,++tmp_cnt);
    translate_Exp(Exp2,table,&op_tmp1);
    InterCode code0 = interCode_construct(MUL,op_offset,op_tmp1,op_len);
    list_add_before(&codeHead,&code0->list);
    if(Exp1->nt_node.num == 1 && Exp1->nt_node.node[0]->type == ID_T){//Exp1->ID
        ID_type *arrayID = hash_find(Exp1->nt_node.node[0]->id_attr,0);
        assert(arrayID->varType.var_no != 0);
        if(arrayID->is_param == 0){//普通数组名在计算地址时要加&
            Operand op_addr = Operand_construct(ADDR,arrayID->varType.var_no);
            InterCode code = interCode_construct(ADD,op,op_addr,op_offset);
            list_add_before(&codeHead,&code->list);
        }
        else if(arrayID->is_param == 1){
            Operand op_array = Operand_construct(VARIABLE,arrayID->varType.var_no);
            InterCode code = interCode_construct(ADD,op,op_array,op_offset);
            list_add_before(&codeHead,&code->list);
        }
        else
            assert(0);
    }
    else{//Exp1->Exp LB Exp RB
        Operand op_tmp2 = Operand_construct(TEMP,++tmp_cnt);
        translate_Array(Exp1,table,op_tmp2);
        InterCode code = interCode_construct(ADD,op,op_tmp2,op_offset);
        list_add_before(&codeHead,&code->list);
    }

}

static inline int get_relop(char *tmp){//根据字符串返回relop的值
    if(strcmp(tmp,"==") == 0)
        return 0;
    if(strcmp(tmp,"!=") == 0)
        return 1;
    if(strcmp(tmp,"<") == 0)
        return 2;
    if(strcmp(tmp,">") == 0)
        return 3;
    if(strcmp(tmp,"<=") == 0)
        return 4;
    if(strcmp(tmp,">=") == 0)
        return 5;
}

void translate_Cond(tree_node *Exp,Operand label1,Operand label2,ID_type** table){
    char *tmp_ = Exp->nt_node.node[0]->other_terminal;
    char *tmp = Exp->nt_node.node[1]->other_terminal;
    if(Exp->nt_node.num == 2 && strcmp(tmp_,"NOT") == 0){//NOT Exp
        return translate_Cond(Exp->nt_node.node[1],label2,label1,table);
    }
    else if(Exp->nt_node.num == 3 && strcmp(tmp,"AND") == 0){//Exp AND Exp
        Operand op_label = Operand_construct(LABEL,++label_cnt);
        InterCode code = interCode_construct(DEF_LABEL,op_label);
        translate_Cond(Exp->nt_node.node[0],op_label,label2,table);
        list_add_before(&codeHead,&code->list);
        translate_Cond(Exp->nt_node.node[2],label1,label2,table);
    }
    else if(Exp->nt_node.num == 3 && strcmp(tmp,"OR") == 0){//Exp OR Exp
        Operand op_label = Operand_construct(LABEL,++label_cnt);
        InterCode code = interCode_construct(DEF_LABEL,op_label);
        translate_Cond(Exp->nt_node.node[0],label1,op_label,table);
        list_add_before(&codeHead,&code->list);
        translate_Cond(Exp->nt_node.node[2],label1,label2,table);
    }
    else if(Exp->nt_node.num == 3 && (strcmp(tmp,"==") == 0 || strcmp(tmp,"!=") == 0 || 
                                      strcmp(tmp,"<") == 0 || strcmp(tmp,">") == 0 || 
                                      strcmp(tmp,"<=") == 0 || strcmp(tmp,">=") == 0)){//Exp RELOP Exp
        Operand op_tmp1 = Operand_construct(TEMP,++tmp_cnt);
        Operand op_tmp2 = Operand_construct(TEMP,++tmp_cnt);
        translate_Exp(Exp->nt_node.node[0],table,&op_tmp1);
        translate_Exp(Exp->nt_node.node[2],table,&op_tmp2);
        int relop = get_relop(tmp);
        InterCode code0 = interCode_construct(COND_GOTO,op_tmp1,op_tmp2,label1,relop);
        InterCode code1 = interCode_construct(GOTO,label2);
        list_add_before(&codeHead,&code0->list);
        list_add_before(&codeHead,&code1->list);
    }
    else{//other case
        Operand op_tmp = Operand_construct(TEMP,++tmp_cnt);
        translate_Exp(Exp,table,&op_tmp);
        Operand op_0 = Operand_construct(CONSTANT,0);
        InterCode code0 = interCode_construct(COND_GOTO,op_tmp,op_0,label1,1);
        InterCode code1 = interCode_construct(GOTO,label2);
        list_add_before(&codeHead,&code0->list);
        list_add_before(&codeHead,&code1->list);
    }
}

void translate_Args(tree_node *Args,ID_type** table,ListHead *arg_list){
    if(Args->nt_node.num == 1){//Args->Exp
        Operand op_tmp = Operand_construct(TEMP,++tmp_cnt);
        translate_Exp(Args->nt_node.node[0],table,&op_tmp);
        tree_node *Exp = Args->nt_node.node[0];
        if(Exp->nt_node.num == 1){
            tree_node *ID = Exp->nt_node.node[0];
            if(ID->type == ID_T){
                char *ID_ = ID->id_attr;
                ID_type *array = hash_find(ID_,0);
                if(array->varType.var->kind == ARRAY){
                    Operand op_addr = Operand_construct(ADDR,op_tmp->u.value);
                    list_add_after(arg_list,&op_addr->list);
                    return;
                }
            }
            
        }
        list_add_after(arg_list,&op_tmp->list);
    }
    else{//Args->Exp COMMA Args
        Operand op_tmp = Operand_construct(TEMP,++tmp_cnt);
        translate_Exp(Args->nt_node.node[0],table,&op_tmp);
        tree_node *Exp = Args->nt_node.node[0];
        if(Exp->nt_node.num == 1){
            tree_node *ID = Exp->nt_node.node[0];
            if(ID->type == ID_T){
                char *ID_ = ID->id_attr;
                ID_type *array = hash_find(ID_,0);
                if(array->varType.var->kind == ARRAY){
                    Operand op_addr = Operand_construct(ADDR,op_tmp->u.value);
                    list_add_after(arg_list,&op_addr->list);
                    translate_Args(Args->nt_node.node[2],table,arg_list);
                    return;
                }
            }
            
        }
        list_add_after(arg_list,&op_tmp->list);
        translate_Args(Args->nt_node.node[2],table,arg_list);
    }
}

void translate_Stmt(tree_node *Stmt,ID_type** table){    
    if(Stmt->nt_node.num == 1)//Stmt->CompSt
        translate_CompSt(Stmt->nt_node.node[0],table);
    else if(Stmt->nt_node.num == 2)//Stmt->Exp SEMI
        translate_Exp(Stmt->nt_node.node[0],table,NULL);
    else if(Stmt->nt_node.num == 3){//Stmt->RETURN Exp SEMI
        Operand op_tmp = Operand_construct(TEMP,++tmp_cnt);
        translate_Exp(Stmt->nt_node.node[1],table,&op_tmp);
        InterCode code = interCode_construct(RET,op_tmp);
        list_add_before(&codeHead,&code->list);
    }
    else if(Stmt->nt_node.num == 7){//Stmt->IF LP Exp RP Stmt ELSE Stmt
        Operand op_label1 = Operand_construct(LABEL,++label_cnt);
        Operand op_label2 = Operand_construct(LABEL,++label_cnt);
        Operand op_label3 = Operand_construct(LABEL,++label_cnt);
        InterCode code0 = interCode_construct(GOTO,op_label3);
        InterCode code1 = interCode_construct(DEF_LABEL,op_label1);
        InterCode code2 = interCode_construct(DEF_LABEL,op_label2);
        InterCode code3 = interCode_construct(DEF_LABEL,op_label3);
        //add intercodes
        translate_Cond(Stmt->nt_node.node[2],op_label1,op_label2,table);
        list_add_before(&codeHead,&code1->list);
        translate_Stmt(Stmt->nt_node.node[4],table);
        list_add_before(&codeHead,&code0->list);
        list_add_before(&codeHead,&code2->list);
        translate_Stmt(Stmt->nt_node.node[6],table);
        list_add_before(&codeHead,&code3->list);
    }
    else if(strcmp(Stmt->nt_node.node[0]->other_terminal,"WHILE") == 0){
        //Stmt->WHILE LP EXP RP Stmt
        Operand op_label1 = Operand_construct(LABEL,++label_cnt);
        Operand op_label2 = Operand_construct(LABEL,++label_cnt);
        Operand op_label3 = Operand_construct(LABEL,++label_cnt);
        InterCode code0 = interCode_construct(GOTO,op_label1);
        InterCode code1 = interCode_construct(DEF_LABEL,op_label1);
        InterCode code2 = interCode_construct(DEF_LABEL,op_label2);
        InterCode code3 = interCode_construct(DEF_LABEL,op_label3);
        //add intercodes
        list_add_before(&codeHead,&code1->list);
        translate_Cond(Stmt->nt_node.node[2],op_label2,op_label3,table);
        list_add_before(&codeHead,&code2->list);
        translate_Stmt(Stmt->nt_node.node[4],table);
        list_add_before(&codeHead,&code0->list);
        list_add_before(&codeHead,&code3->list);
    }
    else{//Stmt->IF LP Exp RP Stmt
        Operand op_label1 = Operand_construct(LABEL,++label_cnt);
        Operand op_label2 = Operand_construct(LABEL,++label_cnt);
        InterCode code1 = interCode_construct(DEF_LABEL,op_label1);
        InterCode code2 = interCode_construct(DEF_LABEL,op_label2);
        translate_Cond(Stmt->nt_node.node[2],op_label1,op_label2,table);
        list_add_before(&codeHead,&code1->list);
        translate_Stmt(Stmt->nt_node.node[4],table);
        list_add_before(&codeHead,&code2->list);
    }
}
    
Operand translate_VarDec(tree_node *VarDec,ID_type** table){//返回值为变量id在中间代码里的Operand
    if(VarDec->nt_node.num == 1){//VarDec->ID
        return varOperand(VarDec->nt_node.node[0]);
    }
    else{//VarDec->VarDec LB INT RB
        tree_node *arrayDec = VarDec;
        while(arrayDec->nt_node.num == 4){//VarDec->VarDec LB INT RB
            arrayDec = arrayDec->nt_node.node[0];
        }
        //VarDec->ID,为数组变量开辟空间
        ID_type *arrayID = hash_find(arrayDec->nt_node.node[0]->id_attr,0);
        assert(arrayID->varType.var_no == 0);
        arrayID->varType.var_no = ++var_cnt;
        int size = 4;
        Type tmpType = arrayID->varType.var;
        while(tmpType->kind == ARRAY){
            size *= tmpType->array.size;
            tmpType = tmpType->array.elem;
        }
        Operand op_size = Operand_construct(SIZE,size);
        Operand op_var = Operand_construct(VARIABLE,arrayID->varType.var_no);
        InterCode code = interCode_construct(DEC_SIZE,op_var,op_size);
        list_add_before(&codeHead,&code->list);
        return op_var;
    }
}

void translate_CompSt(tree_node *CompSt,ID_type** table){
    tree_node *DefList = CompSt->nt_node.node[1];
    tree_node *StmtList = CompSt->nt_node.node[2];
    //DefList analysis
    while(DefList->nt_node.num){
        tree_node *Def = DefList->nt_node.node[0];
        tree_node *DecList = Def->nt_node.node[1];
        while(DecList){//DecList->Dec | Dec COMMA DecList
            tree_node *Dec = DecList->nt_node.node[0];
            if(Dec->nt_node.num == 1)//Dec->VarDec 
                translate_VarDec(Dec->nt_node.node[0],table);
            else{//Dec->VarDec ASSIGNOP EXP
                Operand op_var = translate_VarDec(Dec->nt_node.node[0],table);
                Operand op_tmp = Operand_construct(TEMP,++tmp_cnt);
                translate_Exp(Dec->nt_node.node[2],table,&op_tmp);
                InterCode code = interCode_construct(ASSIGN,op_var,op_tmp);
                list_add_before(&codeHead,&code->list);
            }

            if(DecList->nt_node.num == 1)
                DecList = NULL;
            else
                DecList = DecList->nt_node.node[2];
        }
        DefList = DefList->nt_node.node[1];
    }
    //StmtList analysis
    while(StmtList->nt_node.num){
        tree_node *Stmt = StmtList->nt_node.node[0];
        translate_Stmt(Stmt,table);
        StmtList = StmtList->nt_node.node[1];
    }

}




void translate_Program(tree_node * pTree, ID_type** table){
    if((pTree->type == NONTERMINAL_T && pTree->nt_node.num == 0) || pTree->type != NONTERMINAL_T)//产生式右边为空或者节点为终结符不分析
        return ;
    if(strcmp(pTree->nt_node.name,"ExtDef") == 0){
        tree_node *Specifier = pTree->nt_node.node[0];
        if(pTree->nt_node.num == 2){//ExtDef->Specifier SEMI
        }
        else if(strcmp(pTree->nt_node.node[1]->nt_node.name,"ExtDecList" ) == 0){//ExtDef->Specifier ExtDecList SEMI
            tree_node *ExtDecList = pTree->nt_node.node[1];
            while(ExtDecList){//ExtDecList->VarDec | VarDec COMMA ExtDecList
                tree_node *VarDec = ExtDecList->nt_node.node[0];
                translate_VarDec(VarDec,table);

                if(ExtDecList->nt_node.num == 1)
                    ExtDecList = NULL;
                else
                    ExtDecList = ExtDecList->nt_node.node[2];
            }
        }
        else if(strcmp(pTree->nt_node.node[1]->nt_node.name,"FunDec" ) == 0 && 
                pTree->nt_node.node[2]->type == OTHER_TERMINAL_T){//ExtDef->Specifier FunDec SEMI
            //翻译时不考虑函数声明
        }
        else{//ExtDef->Specifier FunDec CompSt
            tree_node *FunDec = pTree->nt_node.node[1];
            char *func = FunDec->nt_node.node[0]->id_attr;
            Operand op_fun = Operand_construct(FUNCTION,(int)func);
            InterCode code_ = interCode_construct(DEF_FUN,op_fun);
            list_add_before(&codeHead,&code_->list);
            if(FunDec->nt_node.num == 3){//FunDec->ID LP RP 
            }
            else{//FunDec->ID LP VarList RP
                tree_node *VarList = FunDec->nt_node.node[2];
                int i = 0;
                while(VarList){//VarList->ParamDec COMMA VarList | ParamDec
                    tree_node *ParamDec = VarList->nt_node.node[0];
                    tree_node *VarDec = ParamDec->nt_node.node[1];
                    //找到VarDec中的ID,这里的参数只能是一维数组
                    while(VarDec){
                        if(VarDec->nt_node.num == 1){
                            tree_node *ID = VarDec->nt_node.node[0];
                            ID_type *arrayID = hash_find(ID->id_attr,0);
                            arrayID->is_param = 1;//标记为参数，为数组结算地址服务
                            Operand op = varOperand(ID);
                            InterCode code = interCode_construct(PARAM,op);
                            list_add_before(&codeHead,&code->list);

                            VarDec = NULL;
                        }
                        else
                            VarDec = VarDec->nt_node.node[0];
                    }

                    if(VarList->nt_node.num == 1)
                        VarList = NULL;
                    else
                        VarList = VarList->nt_node.node[2];
                }
            }

            translate_CompSt(pTree->nt_node.node[2],table);
        }
    }
    else{
        int i;
        for(i=0; i < pTree->nt_node.num; i++){
            translate_Program(pTree->nt_node.node[i],table);
        }
    }

    if(strcmp(pTree->nt_node.name,"Program") == 0){//对代码优化
        Optimize_InterCode(&codeHead);
    }
}




