/*
 * generate object code
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../header/ir.h"
#include "../header/obj.h"

int reg_state[32];
int codeLen;
int *basic_block;
int curr_offset = 0;
int curr_param_cnt = 0;
int curr_arg_cnt = 0;
my_descriptor *var_descriptor;
my_descriptor *tmp_descriptor;

//init my_descriptor; partition of basic block; init code_index in InterCode
static void code_preprocess(){
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
            code->kind == DEF_LABEL || code->kind == DEF_FUN || code->kind == RET)
            basic_block[code->code_index] = 1;
    }
}

void update_next_appear(Operand op, int code_index){
    int var_update_flag[var_cnt+1];
    for(int i = 0; i < var_cnt+1; i++){
        var_descriptor[i].next_appear = codeLen;
        var_update_flag[i] = 0;
    }
    ListHead *ptr;
    list_foreach(ptr,&codeHead){
        InterCode code = list_entry(ptr,struct InterCode_,list);
        if(code->code_index >= code_index){
            if(code->kind > 7 && code->kind <= 13){
                Operand op2 = code->u.two_op.op2;
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
            if(code->kind > 7 && code->kind <= 13){
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
    for(int i = 0; i < var_cnt+1; i++){
        if(var_descriptor[i].next_appear > var_descriptor[var_farthest_appear].next_appear)
            var_farthest_appear = i;
    }
    int tmp_farthest_appear = 0;
    for(int i = 0; i < tmp_cnt+1; i++){
        if(tmp_descriptor[i].next_appear > tmp_descriptor[tmp_farthest_appear].next_appear)
            tmp_farthest_appear = i;
    }
    int result;
    if(var_descriptor[var_farthest_appear].next_appear > tmp_descriptor[tmp_farthest_appear].next_appear)
        result = var_descriptor[var_farthest_appear].reg_index;
    else
        result = tmp_descriptor[tmp_farthest_appear].reg_index;
   
    my_descriptor *dsp = get_descriptor(op);
    printf("\tsw $%d, %d($sp)\n",result,dsp->offset);

    //change the varible's reg_index, because other var/tmp will lw to it 
    int flag = 1;
    for(int i = 0; i < var_cnt+1; i++){
        if(var_descriptor[i].reg_index == result){
            var_descriptor[i].reg_index = 0;
            flag = 0;
            break;
        }
    }
    if(flag){
        for(int i = 0; i < tmp_cnt+1; i++){
            if(tmp_descriptor[i].reg_index == result){
                tmp_descriptor[i].reg_index = 0;
                break;
            }
        }
    }

    return result;
}

//return a register index for op
static int ensure(Operand op,int code_index,int is_dst){
    if(op->kind != VARIABLE && op->kind != TEMP)
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
    assert(result >= 8 && result < 24);
    my_descriptor *dsp = get_descriptor(op);
    dsp->reg_index = result;
    if(!is_dst)
        printf("\tlw $%d, %d($sp)\n",result,dsp->offset);
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

//generate object code
void generate_objCode(){
    code_preprocess();
    preprint();
    ListHead *ptr;
    list_foreach(ptr,&codeHead){
        InterCode code = list_entry(ptr,struct InterCode_,list);
        /*if(basic_block[code->code_index] == 1){//at the begining of a basic block
            for(int i = 8; i < 24; i++ )
                reg_state[i] = 0;
        }*/
        if(code->kind <= 7){
            Operand op1 = code->u.one_op;
            if(!op1)
                continue;
            switch(code->kind){    
                case 0 : printf("label%d:\n",op1->u.value);break;//LABEL
                case 1 : printf("%s:\n",op1->u.func);break;//FUNCTION
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
                             int reg_index = ensure(op1,code->code_index,0);
                             if(curr_arg_cnt == 0){
                                 printf("\tmove $a0, $%d\n",reg_index);
                             }
                             else if(curr_arg_cnt == 1){
                                 printf("\tmove $a1, $%d\n",reg_index);
                             }
                             else if(curr_arg_cnt == 2){
                                 printf("\tmove $a2, $%d\n",reg_index);
                             }
                             else if(curr_arg_cnt == 3){
                                 printf("\tmove $a3, $%d\n",reg_index);
                             }
                             else{
                                 int offset = STACK_SIZE - 4 * (curr_arg_cnt - 4);
                                 printf("\tsw $%d, %d($sp)\n",reg_index,offset);
                             }
                             curr_arg_cnt ++;
                             break;
                         }
                case 5 : {//PARAM
                             if(curr_param_cnt == 0){
                                 var_descriptor[op1->u.var_no].reg_index = 4;
                             }
                             else if(curr_param_cnt == 1){
                                 var_descriptor[op1->u.var_no].reg_index = 5;
                             }
                             else if(curr_param_cnt == 2){
                                 var_descriptor[op1->u.var_no].reg_index = 6;
                             }
                             else if(curr_param_cnt == 3){
                                 var_descriptor[op1->u.var_no].reg_index = 7;
                             }
                             else{
                                 var_descriptor[op1->u.var_no].offset = STACK_SIZE - 4 * (curr_param_cnt - 4);
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
                             printf("\tmove $a0, $%d\n",reg_index);
                             printf("\taddi $sp, $sp, -4\n");
                             printf("\tsw $ra, 0($sp)\n");
                             printf("\tjal write\n");
                             printf("\tlw $ra, 0($sp)\n");
                             printf("\taddi $sp, $sp, 4\n");
                             break;
                         }
            }
        }
        else if(code->kind <= 13){
            Operand op1 = code->u.two_op.op1;
            Operand op2 = code->u.two_op.op2;
            if(code->kind != 13 && (!op1 || !op2))
                continue;
            int reg_index1 = ensure(op1,code->code_index,1);
            int reg_index2 = ensure(op2,code->code_index,0);
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
                             printf("\tsw $%d, 0($%d)\n",reg_index2,reg_index1);
                             break;
                         }
                case 12: {//DEC
                             break;
                         }
                case 13: {//CALL
                             if(op1){

                             }
                             else{

                             }
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
            int reg_index1 = ensure(op1,code->code_index,1);
            int reg_index2 = ensure(op2,code->code_index,0);
            int reg_index3 = ensure(op3,code->code_index,0);

            switch(code->kind){
                case 14: {
                             assert(op2->kind != CONSTANT || op3->kind != CONSTANT);
                             if(op2->kind == CONSTANT)
                                 printf("\taddi $%d, $%d, %d\n",reg_index1,reg_index3,op2->u.value);
                             else if(op3->kind == CONSTANT){
                                 printf("\taddi $%d, $%d, %d\n",reg_index1,reg_index2,op3->u.value);
                             }
                             else
                                 printf("\tadd $%d, $%d, $%d\n",reg_index1,reg_index2,reg_index3);
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
                                 printf("\tdiv $%d, $%d, $%d\n",reg_index1,reg_index2,reg_index3);
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











