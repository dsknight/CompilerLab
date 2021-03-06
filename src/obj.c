/*
 * generate object code
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../header/ir.h"
#include "../header/obj.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))

int reg_state[32];
int codeLen;
int *basic_block;
int curr_offset;
int curr_param_cnt = 0;
int curr_arg_cnt = 0;
my_descriptor *var_descriptor;
my_descriptor *tmp_descriptor;

//init my_descriptor; partition of basic block; init code_index in InterCode
static void preprocess(){
    //init my_descriptor
    var_descriptor = (my_descriptor *)malloc(sizeof(my_descriptor)*(var_cnt+1));
    memset(var_descriptor,0,sizeof(my_descriptor)*(var_cnt+1));
    tmp_descriptor = (my_descriptor *)malloc(sizeof(my_descriptor)*(tmp_cnt+1));
    memset(tmp_descriptor,0,sizeof(my_descriptor)*(tmp_cnt+1));

    //init code_index and count code length
    codeLen = 0;
    ListHead *ptr;
    list_foreach(ptr,&codeHead){
        InterCode code = list_entry(ptr,struct InterCode_,list);
        code->code_index = codeLen;
        codeLen ++;
    }

    //devide codes into basic blocks
    basic_block = (int *)malloc(sizeof(int)*codeLen);
    memset(basic_block,0,sizeof(int)*codeLen);

    list_foreach(ptr,&codeHead){
        InterCode code = list_entry(ptr,struct InterCode_,list);
        if( code->code_index == 0 || code->kind == GOTO || code->kind == COND_GOTO || 
            code->kind == DEF_LABEL || code->kind == DEF_FUN || code->kind == RET || code->kind == ASSIGN_CALL)
            basic_block[code->code_index] = 1;
    }
}

void update_next_appear(Operand op, int code_index){
    if(op == NULL)
        return;
    int var_update_flag[var_cnt+1];
    for(int i = 0; i < var_cnt+1; i++){
        var_descriptor[i].next_appear = codeLen;
        var_update_flag[i] = 0;
    }
    ListHead *ptr;
    list_foreach(ptr,&codeHead){
        InterCode code = list_entry(ptr,struct InterCode_,list);
        if(code->code_index >= code_index){
            if(code->kind <= 7){
            }
            else if(code->kind > 7 && code->kind <= 13){
                Operand op2 = code->u.two_op.op2;
                if(op2 == NULL)
                if(var_update_flag[op2->u.var_no] == 0 && op2->kind == VARIABLE){
                    var_descriptor[op2->u.var_no].next_appear = code->code_index;
                    var_update_flag[op2->u.var_no] = 1;
                }
            }
            else if(code->kind > 13 && code->kind <= 17){
                Operand op2 = code->u.three_op.op2;
                Operand op3 = code->u.three_op.op3;
                if(var_update_flag[op2->u.var_no] == 0 && op2->kind == VARIABLE){
                    var_descriptor[op2->u.var_no].next_appear = code->code_index;
                    var_update_flag[op2->u.var_no] = 1;
                }
                if(var_update_flag[op3->u.var_no] == 0 && op3->kind == VARIABLE){
                    var_descriptor[op3->u.var_no].next_appear = code->code_index;
                    var_update_flag[op3->u.var_no] = 1;
                }
            }
            else{//CONN_GOTO
                Operand op2 = code->u.three_op.op2;
                Operand op1 = code->u.three_op.op1;
                if(var_update_flag[op2->u.var_no] == 0 && op2->kind == VARIABLE){
                    var_descriptor[op2->u.var_no].next_appear = code->code_index;
                    var_update_flag[op2->u.var_no] = 1;
                }
                if(var_update_flag[op1->u.var_no] == 0 && op1->kind == VARIABLE){
                    var_descriptor[op1->u.var_no].next_appear = code->code_index;
                    var_update_flag[op1->u.var_no] = 1;
                }
            }

            //whether at the end of block
            if(basic_block[code->code_index] == 1 && code->code_index > code_index)
                break;
        }
    }

    int tmp_update_flag[tmp_cnt+1];
    for(int i = 0; i < tmp_cnt+1; i++){
        tmp_descriptor[i].next_appear = codeLen;
        tmp_update_flag[i] = 0;
    }
    list_foreach(ptr,&codeHead){
        InterCode code = list_entry(ptr,struct InterCode_,list);
        if(code->code_index >= code_index){
            if(code->kind <= 7){
            }
            else if(code->kind > 7 && code->kind <= 13){
                Operand op2 = code->u.two_op.op2;
                if(tmp_update_flag[op2->u.var_no] == 0 && op2->kind == TEMP){
                    tmp_descriptor[op2->u.var_no].next_appear = code->code_index;
                    tmp_update_flag[op2->u.var_no] = 1;
                }
            }
            else if(code->kind > 13 && code->kind <= 17){
                Operand op2 = code->u.three_op.op2;
                Operand op3 = code->u.three_op.op3;
                if(tmp_update_flag[op2->u.var_no] == 0 && op2->kind == TEMP){
                    tmp_descriptor[op2->u.var_no].next_appear = code->code_index;
                    tmp_update_flag[op2->u.var_no] = 1;
                }
                if(tmp_update_flag[op3->u.var_no] == 0 && op3->kind == TEMP){
                    tmp_descriptor[op3->u.var_no].next_appear = code->code_index;
                    tmp_update_flag[op3->u.var_no] = 1;
                }
            }
            else{//CONN_GOTO
                Operand op2 = code->u.three_op.op2;
                Operand op1 = code->u.three_op.op1;
                if(tmp_update_flag[op2->u.var_no] == 0 && op2->kind == TEMP){
                    tmp_descriptor[op2->u.var_no].next_appear = code->code_index;
                    tmp_update_flag[op2->u.var_no] = 1;
                }
                if(tmp_update_flag[op1->u.var_no] == 0 && op1->kind == TEMP){
                    tmp_descriptor[op1->u.var_no].next_appear = code->code_index;
                    tmp_update_flag[op1->u.var_no] = 1;
                }
            }

            //whether at the end of block
            if(basic_block[code->code_index] == 1 && code->code_index > code_index)
                break;
        }
    }


}

static inline my_descriptor *get_descriptor(Operand op){
    if(op->kind == VARIABLE)
        return var_descriptor + op->u.var_no;
    else if(op->kind == TEMP)
        return tmp_descriptor + op->u.var_no;
    else{
        printf("no descriptor for kind %d\n",op->kind);
        return NULL;
    }
}

//generate a register index for op
static int allocate(Operand op, int code_index){
    for(int i = 8; i < 24; i++){
        if(reg_state[i] == 0){
            reg_state[i] = 1;
            return i;
        }
    }
    //if there is no free reg
    update_next_appear(op,code_index);
    int var_farthest_appear = 0;
    var_descriptor[0].next_appear = 0;
    for(int i = 1; i < var_cnt+1; i++){
        if(var_descriptor[i].next_appear > var_descriptor[var_farthest_appear].next_appear && var_descriptor[i].reg_index != 0)
            var_farthest_appear = i;
    }
    int tmp_farthest_appear = 0;
    tmp_descriptor[0].next_appear = 0;
    for(int i = 1; i < tmp_cnt+1; i++){
        if(tmp_descriptor[i].next_appear > tmp_descriptor[tmp_farthest_appear].next_appear && tmp_descriptor[i].reg_index != 0)
            tmp_farthest_appear = i;
    }
    int result;
    if(var_descriptor[var_farthest_appear].next_appear > tmp_descriptor[tmp_farthest_appear].next_appear)
        result = var_descriptor[var_farthest_appear].reg_index;
    else
        result = tmp_descriptor[tmp_farthest_appear].reg_index;

    if(result == 0){
        int test = result + 1;
    }
   
    my_descriptor *dsp = get_descriptor(op);
    printf("\tsw $%d, %d($sp)\n",result,dsp->offset);

    //reset the varible's reg_index, because other var/tmp will use it 
    for(int i = 1; i < var_cnt+1; i++){
        if(var_descriptor[i].reg_index == result){
            var_descriptor[i].reg_index = 0;
        }
    }
    for(int i = 1; i < tmp_cnt+1; i++){
        if(tmp_descriptor[i].reg_index == result){
            tmp_descriptor[i].reg_index = 0;
        }
    }


    return result;
}

//return a register index for op
static int ensure(Operand op,int code_index,int is_dst){
    if(op == NULL || (op->kind != VARIABLE && op->kind != TEMP))
        return 0;
    if(op->kind == VARIABLE){
        int reg_index = var_descriptor[op->u.var_no].reg_index;
        if(reg_index >= 1 && reg_index < 32)
            return reg_index;
    }
    else{
        int reg_index = tmp_descriptor[op->u.var_no].reg_index;
        if(reg_index >= 1 && reg_index < 32)
            return reg_index; 
    }
    //if the op is not in reg
    int result = allocate(op,code_index);
    if(!(result >= 8 && result < 24))
        printf("*** %d ***\n",result);
    assert(result >= 8 && result < 24);
    my_descriptor *dsp = get_descriptor(op);
    if(!is_dst){
        printf("\tlw $%d, %d($sp)\n",result,dsp->offset);
    }
    dsp->reg_index = result;
    reg_state[result] = 1;
    return result;
}

//free a register
static void free_reg(int reg_index){
    
}

//print data and function read,write
void preprint(){
    printf(".data\n_prompt:.asciiz \"Enter an integer:\"\n _ret: .asciiz \"\\n\"\n.globl main\n.text\nread:\n\
        li $v0, 4\n\
        la $a0, _prompt\n\
        syscall\n\
        li $v0, 5\n\
        syscall\n\
        jr $ra\n\
        \nwrite:\n\
        li $v0, 1\n\
        syscall\n\
        li $v0, 4\n\
        la $a0, _ret\n\
        syscall\n\
        move $v0, $0\n\
        jr $ra\n\
        \n");
}

//allocate space for var/tmp
static inline void allocate_space(Operand op){
    if(op == NULL )
        return;
    if(op->kind == VARIABLE || op->kind == TEMP){
        my_descriptor *dsp = get_descriptor(op);
        if(dsp->offset == 0){
            curr_offset -= 4;
            dsp->offset = curr_offset;
        }
    }
}

//generate object code
void generate_objCode(){
    char code_for_move_arg[1000] = "";
    preprocess();
    preprint();
    ListHead *ptr;
    list_foreach(ptr,&codeHead){
        InterCode code = list_entry(ptr,struct InterCode_,list);
        if(basic_block[code->code_index] == 1){//at the begining of a basic block
            for(int i = 8; i < 24; i++ ){
                reg_state[i] = 0;
            }
            //sw the varible's whose value is in register 
            for(int i = 0; i < var_cnt+1; i++){
                int reg_index = var_descriptor[i].reg_index;
                if(reg_index >= 8  && reg_index <= 24){
                    printf("\tsw $%d, %d($sp)\n",reg_index,var_descriptor[i].offset);
                    var_descriptor[i].reg_index = 0;
                }
            }
            for(int i = 0; i < tmp_cnt+1; i++){
                int reg_index = tmp_descriptor[i].reg_index;
                if(reg_index >= 8  && reg_index <= 24){
                    printf("\tsw $%d, %d($sp)\n",reg_index,tmp_descriptor[i].offset);
                    tmp_descriptor[i].reg_index = 0;
                }
            }

        }
        if(code->kind <= 7){
            Operand op1 = code->u.one_op;
            if(!op1)
                continue;
            //if it's a new variable, allocate space
            allocate_space(op1);
            switch(code->kind){    
                case 0 : printf("label%d:\n",op1->u.value);break;//LABEL
                case 1 : {//FUNCTION
                             int param_cnt = 0;
                             ListHead *ptr_ = ptr->next;
                             while(1){
                                 InterCode code_ = list_entry(ptr_,struct InterCode_,list);
                                 if(code_->kind == PARAM)
                                     param_cnt++;
                                 else
                                     break;
                                 ptr_ = code_->list.next;
                             }
                             int arg_space = ((param_cnt > 4) ? (param_cnt - 4) : 0) * 4;
                             int reg_space = ((param_cnt > 4) ? 4 : param_cnt)*4 + 4  ;
                             curr_offset = STACK_SIZE - (arg_space + reg_space);//store argument(>4) and $ra

                             printf("%s:\n",op1->u.func);
                             curr_param_cnt = 0;
                             break;
                         }
                case 2 : printf("\tj label%d\n",op1->u.value);break;//GOTO
                case 3 : {//RETURN
                             if(op1->kind == CONSTANT)
                                printf("\tli $v0, %d\n",op1->u.value);
                             else{
                                assert(op1->kind == VARIABLE || op1->kind == TEMP);
                                int reg_index = ensure(op1,code->code_index,0);
                                printf("\tmove $v0, $%d\n",reg_index);
                             }
                             printf("\tjr $ra\n");
                             break;
                         }
                case 4 : {//ARG
                             while(code->kind == ARG){
                                 ptr = ptr->next;
                                 code = list_entry(ptr,struct InterCode_,list);
                             }
                             ptr = ptr->prev;
                             ListHead *ptr_ = ptr;
                             code = list_entry(ptr_,struct InterCode_,list);
                             while(code->kind == ARG){
                                Operand op1 = code->u.one_op;
                                int reg_index = ensure(op1,code->code_index,0);
                                if(curr_arg_cnt == 0){
                                    if(op1->kind == CONSTANT)
                                        sprintf(code_for_move_arg,"%s\tli $a0, %d\n",code_for_move_arg,op1->u.value);
                                    else if(op1->kind == ADDR){
                                        sprintf(code_for_move_arg,"%s\tla $a0, %d($sp)\n",
                                                code_for_move_arg,var_descriptor[op1->u.value].offset + STACK_SIZE);
                                    }
                                    else
                                        sprintf(code_for_move_arg,"%s\tmove $a0, $%d\n",code_for_move_arg,reg_index);
                                }
                                else if(curr_arg_cnt == 1){
                                    if(op1->kind == CONSTANT)
                                        sprintf(code_for_move_arg,"%s\tli $a1, %d\n",code_for_move_arg,op1->u.value);
                                    else if(op1->kind == ADDR){
                                        sprintf(code_for_move_arg,"%s\tla $a1, %d($sp)\n",
                                                code_for_move_arg,var_descriptor[op1->u.value].offset + STACK_SIZE);
                                    }
                                    else
                                        sprintf(code_for_move_arg,"%s\tmove $a1, $%d\n",code_for_move_arg,reg_index);
                                }
                                else if(curr_arg_cnt == 2){
                                    if(op1->kind == CONSTANT)
                                        sprintf(code_for_move_arg,"%s\tli $a2, %d\n",code_for_move_arg,op1->u.value);
                                    else if(op1->kind == ADDR){
                                        sprintf(code_for_move_arg,"%s\tla $a2, %d($sp)\n",
                                                code_for_move_arg,var_descriptor[op1->u.value].offset + STACK_SIZE);
                                    }
                                    else
                                        sprintf(code_for_move_arg,"%s\tmove $a2, $%d\n",code_for_move_arg,reg_index);
                                }
                                else if(curr_arg_cnt == 3){
                                    if(op1->kind == CONSTANT)
                                        sprintf(code_for_move_arg,"%s\tli $a3, %d\n",code_for_move_arg,op1->u.value);
                                    else if(op1->kind == ADDR){
                                        sprintf(code_for_move_arg,"%s\tla $a3, %d($sp)\n",
                                                code_for_move_arg,var_descriptor[op1->u.value].offset + STACK_SIZE);
                                    }
                                    else
                                        sprintf(code_for_move_arg,"%s\tmove $a3, $%d\n",code_for_move_arg,reg_index);
                                }
                                else{
                                    int offset = STACK_SIZE - 4 * (curr_arg_cnt - 4) - 4;
                                    if(op1->kind == CONSTANT)
                                        sprintf(code_for_move_arg,"%s\tli $25, %d\n\tsw $25, %d($sp)\n",
                                                code_for_move_arg,op1->u.value,offset);
                                    else if(op1->kind == ADDR){
                                        sprintf(code_for_move_arg,"%s\tla $26, %d($sp)\n",
                                                code_for_move_arg,var_descriptor[op1->u.value].offset);
                                        sprintf(code_for_move_arg,"%s\tsw $26, %d($sp)\n",code_for_move_arg,offset + STACK_SIZE);
                                    }
                                    else
                                    sprintf(code_for_move_arg,"%s\tsw $%d, %d($sp)\n",code_for_move_arg,reg_index,offset);
                                }
                                curr_arg_cnt ++;
                                ptr_ = ptr_->prev;
                                code = list_entry(ptr_,struct InterCode_,list);
                             }
                             break;
                         }
                case 5 : {//PARAM
                             if(curr_param_cnt == 0){
                                 var_descriptor[op1->u.var_no].reg_index = 4;
                                 curr_offset -= 4;
                             }
                             else if(curr_param_cnt == 1){
                                 var_descriptor[op1->u.var_no].reg_index = 5;
                                 curr_offset -= 4;
                             }
                             else if(curr_param_cnt == 2){
                                 var_descriptor[op1->u.var_no].reg_index = 6;
                                 curr_offset -= 4;
                             }
                             else if(curr_param_cnt == 3){
                                 var_descriptor[op1->u.var_no].reg_index = 7;
                                 curr_offset -= 4;
                             }
                             else{
                                 var_descriptor[op1->u.var_no].offset = STACK_SIZE - 4 * (curr_param_cnt - 4) - 4;
                             }
                             curr_param_cnt ++;
                             break;
                         }
                case 6 : {//READ
                             int reg_index = ensure(op1,code->code_index,1);
                             assert(op1->kind == VARIABLE || op1->kind == TEMP);
                             printf("\taddi $sp, $sp, -4\n");
                             printf("\tsw $ra, 0($sp)\n");
                             printf("\tjal read\n");
                             printf("\tlw $ra, 0($sp)\n");
                             printf("\taddi $sp, $sp, 4\n");
                             printf("\tmove $%d, $v0\n",reg_index);
                             break;
                         }
                case 7 : {//WRITE
                             int reg_index = ensure(op1,code->code_index,0);
                             int offset = min(curr_param_cnt,4)*4;
                             printf("\taddi $sp, $sp, -%d\n",4+min(curr_param_cnt,4)*4);
                             printf("\tsw $ra, %d($sp)\n",offset);
                             for(int i = 0; i < min(curr_param_cnt,4); i++)
                                 printf("\tsw $a%d, %d($sp)\n",i,offset-(4*i)-4);
                             if(op1->kind == CONSTANT){
                                 printf("\tli $25, %d\n",op1->u.value);
                                 reg_index = 25;
                             }
                             printf("\tmove $a0, $%d\n",reg_index);
                             printf("\tjal write\n");
                             printf("\tlw $ra, %d($sp)\n",offset);
                             for(int i = min(curr_param_cnt,4)-1; i >= 0; i--)
                                printf("\tlw $a%d, %d($sp)\n",i,offset-(4*i)-4);
                             printf("\taddi $sp, $sp, %d\n",4+min(curr_param_cnt,4)*4);
                             break;
                         }
            }
        }
        else if(code->kind <= 13){
            Operand op1 = code->u.two_op.op1;
            Operand op2 = code->u.two_op.op2;
            if(code->kind != 13 && (!op1 || !op2))
                continue;
            allocate_space(op1);
            allocate_space(op2);
            int reg_index2 = ensure(op2,code->code_index,0);
            int reg_index1 = ensure(op1,code->code_index,1);
            switch(code->kind){
                case 8 : {//ASSIGN
                             if(op2->kind != CONSTANT){
                                 printf("\tmove $%d, $%d\n",reg_index1,reg_index2);
                             }
                             else{//op2 is a constant
                                 printf("\tli $%d, %d\n",reg_index1,op2->u.value);
                             }
                             break;
                         }
                case 9 : {//ASSIGN_ADDR
                             my_descriptor *dsp = get_descriptor(op2);
                             printf("\tla $%d, %d($sp)\n",reg_index1,dsp->offset);
                             break;
                         }
                case 10: {//ASSIGN_MEM
                             printf("\tlw $%d, 0($%d)\n",reg_index1,reg_index2);
                             break;
                         }
                case 11: {//MEM_ASSIGN
                             if(op2->kind == CONSTANT){
                                 printf("\tli $25, %d\n",op2->u.value);
                                 printf("\tsw $25, 0($%d)\n",reg_index1);
                             }
                             else
                                 printf("\tsw $%d, 0($%d)\n",reg_index2,reg_index1);
                             break;
                         }
                case 12: {//DEC
                             int size = op2->u.value;
                             curr_offset -= op2->u.value;
                             my_descriptor *dsp = get_descriptor(op1);
                             dsp->offset = curr_offset;
                             dsp->reg_index = 0;
                             break;
                         }
                case 13: {//CALL
                             assert(op2->kind == FUNCTION);
                             int arg_space_caller = (curr_param_cnt > 4) ? (curr_param_cnt - 4) : 0;
                             int arg_space_callee = (curr_arg_cnt > 4) ? (curr_arg_cnt - 4) : 0;
                             int offset = STACK_SIZE - (4 * arg_space_caller + 4);//space for argument(>4) and $ra
                             int offset_ = STACK_SIZE - (4 * arg_space_callee + 4);//space for argument(>4) and $ra
                             for(int i = 0; i < min(curr_param_cnt,4); i++)
                                 printf("\tsw $a%d, %d($sp)\n",i,offset-(4*i)-4);

                             printf("\taddi $sp, $sp, %d\n",-STACK_SIZE);
                             printf("\tsw $ra, %d($sp)\n",offset_);
                             printf("%s",code_for_move_arg);
                             memset(code_for_move_arg,0,100);
                             printf("\tjal %s\n",op2->u.func);
                             printf("\tlw $ra, %d($sp)\n",offset_);
                             printf("\taddi $sp, $sp, %d\n",STACK_SIZE);
                             for(int i = min(curr_param_cnt,4)-1; i >= 0; i--)
                                printf("\tlw $a%d, %d($sp)\n",i,offset-(4*i)-4);
                             if(op1){
                                 printf("\tmove $%d, $v0\n",reg_index1);
                             }
                             else{

                             }
                             curr_arg_cnt = 0;
                             break;
                         }
            }
        }
        else if(code->kind <= 17){
            Operand op1 = code->u.if_goto.op1;
            Operand op2 = code->u.if_goto.op2;
            Operand op3 = code->u.if_goto.op3;
            if(!op1 || !op2 || !op3)
                continue;
            allocate_space(op1);
            allocate_space(op2);
            allocate_space(op3);
            int reg_index2 = ensure(op2,code->code_index,0);
            int reg_index3 = ensure(op3,code->code_index,0);
            int reg_index1 = ensure(op1,code->code_index,1);

            switch(code->kind){
                case 14: {
                             assert(op2->kind != CONSTANT || op3->kind != CONSTANT);
                             if(op2->kind == CONSTANT){
                                 if(op3->kind != ADDR)
                                     printf("\taddi $%d, $%d, %d\n",reg_index1,reg_index3,op2->u.value);
                                 else{
                                     printf("\tla $26, %d($sp)\n",var_descriptor[op3->u.value].offset);
                                     printf("\taddi $%d, $26, %d\n",reg_index1,op2->u.value);
                                 }
                             }
                             else if(op3->kind == CONSTANT){
                                 if(op2->kind != ADDR)
                                     printf("\taddi $%d, $%d, %d\n",reg_index1,reg_index2,op3->u.value);
                                 else{
                                     printf("\tla $26, %d($sp)\n",var_descriptor[op2->u.value].offset);
                                     printf("\taddi $%d, $26, %d\n",reg_index1,op3->u.value);
                                 }
                             }
                             else{
                                 if(op2->kind == ADDR){
                                     printf("\tla $26, %d($sp)\n",var_descriptor[op2->u.value].offset);
                                     printf("\tadd $%d, $26, $%d\n",reg_index1,reg_index3);
                                 }
                                 else if(op3->kind == ADDR){
                                     printf("\tla $26, %d($sp)\n",var_descriptor[op2->u.value].offset);
                                     printf("\tadd $%d, $%d, $26\n",reg_index1,reg_index2);
                                 }
                                 else
                                     printf("\tadd $%d, $%d, $%d\n",reg_index1,reg_index2,reg_index3);
                             }
                             break;
                         }
                case 15: {
                             assert(op2->kind != CONSTANT || op3->kind != CONSTANT);
                             if(op2->kind == CONSTANT){
                                 printf("\tli $25, %d\n",op2->u.value);
                                 printf("\tsub $%d, $25, $%d\n",reg_index1,reg_index3);
                             }
                             else if(op3->kind == CONSTANT){
                                 printf("\taddi $%d, $%d, %d\n",reg_index1,reg_index2,-op3->u.value);
                             }
                             else{
                                 printf("\tsub $%d, $%d, $%d\n",reg_index1,reg_index2,reg_index3);
                             }
                             break;
                         }
                case 16: {
                             assert(op2->kind != CONSTANT || op3->kind != CONSTANT);
                             if(op2->kind == CONSTANT){
                                 printf("\tli $25, %d\n",op2->u.value);
                                 printf("\tmul $%d, $25, $%d\n",reg_index1,reg_index3);
                             }
                             else if(op3->kind == CONSTANT){
                                 printf("\tli $25, %d\n",op3->u.value);
                                 printf("\tmul $%d, $%d, $25\n",reg_index1,reg_index2);
                             }
                             else
                                 printf("\tmul $%d, $%d, $%d\n",reg_index1,reg_index2,reg_index3);
                             break;
                         }
                case 17: {
                             assert(op2->kind != CONSTANT || op3->kind != CONSTANT);
                             if(op2->kind == CONSTANT){
                                 printf("\tli $25, %d\n",op2->u.value);
                                 printf("\tdiv $%d, $25, $%d\n",reg_index1,reg_index3);
                             }
                             else if(op3->kind == CONSTANT){
                                 printf("\tli $25, %d\n",op3->u.value);
                                 printf("\tdiv $%d, $%d, $25\n",reg_index1,reg_index2);
                             }
                             else
                                 printf("\tdiv $%d, $%d, $%d\n",reg_index1,reg_index2,reg_index3);
                             break;
                         }
            }
        }
        else{
            Operand op1 = code->u.if_goto.op1;
            Operand op2 = code->u.if_goto.op2;
            Operand op3 = code->u.if_goto.op3;
            if(!op1 || !op2 || !op3)
                continue;
            int reg_index1 = ensure(op1,code->code_index,0);
            int reg_index2 = ensure(op2,code->code_index,0);
            assert(op3->kind == LABEL);
            char relop[6][5] = {"==","!=","<",">","<=",">="};
            char instruction[6][5] = {"beq","bne","blt","bgt","ble","bge"};
            assert(code->u.if_goto.relop >= 0 && code->u.if_goto.relop < 6);
            if(op1->kind == CONSTANT){
                printf("\tli $25, %d\n",op1->u.value);
                reg_index1 = 25;
            }
            if(op2->kind == CONSTANT){
                printf("\tli $26, %d\n",op2->u.value);
                reg_index2 = 26;
            }
            printf("\t%s $%d, $%d, label%d\n",instruction[code->u.if_goto.relop],
                                              reg_index1,reg_index2,op3->u.value);    
        }
    }
}


int is_operand_equal(Operand op1, Operand op2){
    if(op1->kind != op2->kind)
        return 0;
    switch(op1->kind){
        case VARIABLE : if(op1->u.var_no == op2->u.var_no) return 1;break;
        case TEMP : if(op1->u.var_no == op2->u.var_no) return 1;break;
        default : break;
    }
    return 0;
}











