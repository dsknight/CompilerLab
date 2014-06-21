/*
 *this file is the header of object code generating
 */
#ifndef __OBJ_H__
#define __OBJ_H__


#define STACK_SIZE 1024

extern int *basic_block;
extern int reg_state[32];

/*typedef struct reg{
    int reg_index;
    int state;//0:free; 1:occupied
}my_reg;*/

typedef struct descriptor_var_tmp{
    int reg_index;
    int next_appear;
    int offset;
}my_descriptor;
extern my_descriptor *var_descriptor;
extern my_descriptor *tmp_descriptor;


void generate_objCode();





#endif

