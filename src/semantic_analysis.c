#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../header/tree.h"
#include "../header/semantic.h"

int semantic_error = 0;
ID_type *ID_table[TABLE_SIZE];

//任何调用specifier_analysis()的过程需要在结束时将返回值free()
Type specifier_analysis(tree_node *specifier){
    //分析Specifier确定类型
    Type currType = (struct Type_*)malloc(sizeof(struct Type_));
    memset(currType,0,sizeof(struct Type_));
    if(specifier->nt_node.node[0]->type == OTHER_TERMINAL_T){//Specifier->TYPE
        currType->kind = 0;
        if(strcmp(specifier->nt_node.node[0]->other_terminal,"INT") == 0)
            currType->basic = 0;//int
        else
            currType->basic = 1;//float
    }
    else{//Specifier->StructSpecifier
        currType->kind = 2;
        tree_node *StructSpecifier = specifier->nt_node.node[0];
        if(StructSpecifier->nt_node.num == 5){//StructSpecifier->Struct OptTag LC DefList RC
            tree_node *OptTag = StructSpecifier->nt_node.node[1];
            if(OptTag->nt_node.num && hash_find(OptTag->nt_node.node[0]->id_attr,2)!=NULL){//Duplicate struct name
                printf("Error type 16 at line %d: Duplicated name '%s'\n",OptTag->lineno,OptTag->nt_node.node[0]->id_attr);
                semantic_error = 1;
            }
            else{
                tree_node *DefList = StructSpecifier->nt_node.node[3];
                currType->structure.name = OptTag->nt_node.num == 0 ? NULL : OptTag->nt_node.node[0]->id_attr;
                currType->structure.head = NULL;
                currType->structure.tail = NULL;
                while(DefList->nt_node.num){//analysis DefList and Def->Specifier DecList SEMI
                    tree_node *Def = DefList->nt_node.node[0];
                    Type DefType = specifier_analysis(Def->nt_node.node[0]);
                    tree_node *DecList = Def->nt_node.node[1];
                    while(DecList != NULL){//DecList->Dec COMMA DecList | Dec
                        tree_node *Dec = DecList->nt_node.node[0];
                        if(Dec->nt_node.num == 3){//Dec->VarDec ASSIGNOP Exp
                            printf("Error type 15 at line %d: Illegal initialize '%s'\n",
                                    Dec->lineno,Dec->nt_node.node[0]->nt_node.node[0]->id_attr);
                            semantic_error = 1;
                        }
                        else{//Dec->VarDec
                            tree_node *VarDec = Dec->nt_node.node[0];
                            FieldList newField = (struct FieldList_*)malloc(sizeof(struct FieldList_));
                            if(VarDec->nt_node.num == 1){//VarDec->ID
                                newField->name = VarDec->nt_node.node[0]->id_attr;
                                newField->type = DefType;
                                newField->next = NULL;

                            }
                            else{//VarDec->VarDec LB INT RB
                                tree_node *arrayDec = VarDec;
                                Type arrayType = (Type)malloc(sizeof(struct Type_));
                                *arrayType = *DefType;
                                while(arrayDec->nt_node.num == 4){//VarDec->VarDec LB INT RB
                                    Type newType = (Type)malloc(sizeof(struct Type_));
                                    newType->kind = 2;
                                    newType->array.elem = arrayType;
                                    newType->array.size = arrayDec->nt_node.node[2]->int_attr;
                                    arrayType = newType;
                                    arrayDec = arrayDec->nt_node.node[0];
                                }
                                //VarDec->ID
                                newField->name = arrayDec->nt_node.node[0]->id_attr;
                                newField->type = arrayType;
                                newField->next = NULL;
                            } 
                            //insert field
                            int fieldExist = 0;
                            for(FieldList pField = currType->structure.head;pField != NULL;pField = pField->next){
                                if(strcmp(pField->name,newField->name) == 0){
                                    printf("Error type 15 at line %d: Redefined field '%s'\n",
                                            VarDec->lineno,VarDec->nt_node.node[0]->id_attr);
                                    semantic_error = 1;
                                    fieldExist = 1;
                                    break;
                                }
                            }
                            if(!fieldExist){
                                if(currType->structure.tail == NULL){
                                    currType->structure.head = newField;
                                    currType->structure.tail = newField;
                                }
                                else{
                                    currType->structure.tail->next = newField;
                                    currType->structure.tail = newField;
                                }
                            }
                        }  
                        if(DecList->nt_node.num == 3)
                            DecList = DecList->nt_node.node[2];
                        else
                            DecList = NULL;
                    }
                    DefList = DefList->nt_node.node[1];
                }
                if(currType->structure.name){//结构体进ID表
                    ID_type *currID = (ID_type*)malloc(sizeof(struct ID_type));
                    memset(currID,0,sizeof(struct ID_type));
                    currID->ID = currType->structure.name;
                    currID->type = 2;
                    currID->next = NULL;
                    currID->structType  = (Type)malloc(sizeof(struct Type_));
                    *currID->structType = *currType;
                    hash_insert(currID);
                }
            }
        }
        else{//StructSpecifier->STRUCT Tag
            tree_node *Tag = StructSpecifier->nt_node.node[1];
            ID_type *tmp = hash_find(Tag->nt_node.node[0]->id_attr,2);
            if(tmp == NULL){
                printf("Error type 17 at line %d: Undefined struct '%s'\n",Tag->lineno,Tag->nt_node.node[0]->id_attr);
                semantic_error = 1;

                return NULL;
            }
            else{
                currType = tmp->structType;
            }
        }
    }
    
    return currType;
}

Type varDec_analysis(tree_node* VarDec,Type currType,int insert){//分析变量，插入符号表或者报错
    if(VarDec->nt_node.num == 1){//VarDec->ID
        if(hash_find(VarDec->nt_node.node[0]->id_attr,0) != NULL){
            printf("Error Type 3 at line %d: Redefined variable \"%s\"\n",
                    VarDec->lineno,VarDec->nt_node.node[0]->id_attr);
            semantic_error = 1;
        }
        else{
            ID_type *newID = (struct ID_type*)malloc(sizeof(struct ID_type));
            memset(newID,0,sizeof(struct ID_type));
            newID->ID = VarDec->nt_node.node[0]->id_attr;
            newID->type = 0;
            newID->next = NULL;
            Type newType;
            if(currType != NULL){
            newID->varType.var = (Type)malloc(sizeof(struct Type_));
            *newID->varType.var = *currType;
            newType = (Type)malloc(sizeof(struct Type_));//新开辟空间用于返回，便于之后的free
            *newType = *currType;
            }
            else{
                newID->varType.var = NULL;
                newType = NULL;
            }
            if(insert){
                hash_insert(newID);
            }

            return newType;
        }
    }
    else{//VarDec->VarDec LB INT RB
        tree_node *arrayDec = VarDec;
        Type arrayType = (Type)malloc(sizeof(struct Type_));
        *arrayType = *currType;
        while(arrayDec->nt_node.num == 4){//VarDec->VarDec LB INT RB
            Type newType = (Type)malloc(sizeof(struct Type_));
            newType->kind = 1;
            newType->array.elem = arrayType;
            newType->array.size = arrayDec->nt_node.node[2]->int_attr;
            arrayType = newType;
            arrayDec = arrayDec->nt_node.node[0];
        }
        //VarDec->ID
        if(hash_find(arrayDec->nt_node.node[0]->id_attr,0) != NULL){
            printf("Error Type 3 at line %d: Redefined variable \"%s\"\n",
                    arrayDec->lineno,arrayDec->nt_node.node[0]->id_attr);
            semantic_error = 1;
        }
        else{
            ID_type *newID = (struct ID_type*)malloc(sizeof(struct ID_type));
            memset(newID,0,sizeof(struct ID_type));
            newID->ID = arrayDec->nt_node.node[0]->id_attr;
            newID->type = 0;
            newID->next = NULL;
            newID->varType.var = (Type)malloc(sizeof(struct Type_));
            *newID->varType.var = *arrayType;
            if(insert)
                hash_insert(newID);
            return arrayType;
        }
    }
    return NULL;
}

Type exp_analysis(tree_node *Exp){
    Type retType = NULL;
    if(Exp->nt_node.num == 1){
        if(Exp->nt_node.node[0]->type == ID_T){//ID
            ID_type *tmpID = hash_find(Exp->nt_node.node[0]->id_attr,0);
            if(tmpID == NULL || tmpID->type != 0){
                printf("Error type 1 at line %d: Undefined variable \"%s\"\n",
                        Exp->lineno,Exp->nt_node.node[0]->id_attr);
                semantic_error = 1;
                retType = NULL;
            }
            else
                retType = tmpID->varType.var;
            return retType;
        }
        else if(Exp->nt_node.node[0]->type == INT_T){//INT
            retType = (Type)malloc(sizeof(struct Type_));
            retType->kind = 0;
            retType->basic = 0;
            return retType;
        }
        else if(Exp->nt_node.node[0]->type == FLOAT_T){//FLOAT
            retType = (Type)malloc(sizeof(struct Type_));
            retType->kind = 0;
            retType->basic = 1;
            return retType;
        }
    }
    else if(Exp->nt_node.num == 2){
        if(strcmp(Exp->nt_node.node[0]->other_terminal,"MINUS") == 0){//MINUS Exp
            retType = exp_analysis(Exp->nt_node.node[1]);
            return retType;
        }
        else if(strcmp(Exp->nt_node.node[0]->other_terminal,"NOT") == 0){//NOT Exp
            retType = exp_analysis(Exp->nt_node.node[1]);
            return retType;
        }
    }
    else if(Exp->nt_node.num == 3){
        if(strcmp(Exp->nt_node.node[1]->other_terminal,"ASSIGNOP") == 0){//Exp ASSIGNOP Exp
            tree_node *Exp1 = Exp->nt_node.node[0];
            if( Exp1->nt_node.num == 1 && Exp1->nt_node.node[0]->type == ID_T ||     //ID
                Exp1->nt_node.num == 3 && strcmp(Exp1->nt_node.node[1]->other_terminal,"DOT") == 0 ||   // Exp DOT ID
                Exp1->nt_node.num == 4 && strcmp(Exp1->nt_node.node[1]->other_terminal,"LB") == 0){//Exp LB Exp RB

                Type t1 = exp_analysis(Exp->nt_node.node[0]);
                Type t2 = exp_analysis(Exp->nt_node.node[2]);
                if(!isTypeEqual(t1,t2)){
                    printf("Error type 5 at line %d: Type mismatched\n",Exp->lineno);
                    semantic_error = 1;
                }
                retType = t1;
            }
            else{
                printf("Error type 6 at line %d: The left-hand side of an assignment must be a variable\n",Exp->lineno);
                semantic_error = 1;
                retType = NULL;
            }
            return retType;
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"AND") == 0){//Exp AND Exp
            Type t1 = exp_analysis(Exp->nt_node.node[0]);
            Type t2 = exp_analysis(Exp->nt_node.node[2]);
            
            if(!isTypeEqual(t1,t2) || t1->kind != 0 || t1->basic != 0){
                printf("Error type 7 at line %d: Operands type mismatched\n",Exp->lineno);
                semantic_error = 1;
            }
            
            retType = (Type)malloc(sizeof(struct Type_));
            retType->kind = 0;
            retType->basic = 0;
            return retType;
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"OR") == 0){//Exp OR Exp
            Type t1 = exp_analysis(Exp->nt_node.node[0]);
            Type t2 = exp_analysis(Exp->nt_node.node[2]);
            
            if(!isTypeEqual(t1,t2) || t1->kind != 0 || t1->basic != 0){
                printf("Error type 7 at line %d: Operands type mismatched\n",Exp->lineno);
                semantic_error = 1;
            }

            retType = (Type)malloc(sizeof(struct Type_));
            retType->kind = 0;
            retType->basic = 0;
            return retType;
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"<" ) == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,">" ) == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,"<=") == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,"<=") == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,"==") == 0 ||
                strcmp(Exp->nt_node.node[1]->other_terminal,"!=") == 0 ){//Exp RELOP Exp
            Type t1 = exp_analysis(Exp->nt_node.node[0]);
            Type t2 = exp_analysis(Exp->nt_node.node[2]);

            if(!isTypeEqual(t1,t2) || t1->kind != 0){
                printf("Error type 7 at line %d: Operands type mismatched\n",Exp->lineno);
                semantic_error = 1;
            }
            
            retType = (Type)malloc(sizeof(struct Type_));
            retType->kind = 0;
            retType->basic = 0;
            return retType;
            
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"PLUS") == 0){//Exp PLUS Exp
            Type t1 = exp_analysis(Exp->nt_node.node[0]);
            Type t2 = exp_analysis(Exp->nt_node.node[2]);

            if(!isTypeEqual(t1,t2) || t1->kind != 0){
                printf("Error type 7 at line %d: Operands type mismatched\n",Exp->lineno);
                semantic_error = 1;
            }
            retType = t1;
            return retType;
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"MINUS") == 0){//Exp MINUS Exp
            Type t1 = exp_analysis(Exp->nt_node.node[0]);
            Type t2 = exp_analysis(Exp->nt_node.node[2]);

            if(!isTypeEqual(t1,t2) || t1->kind != 0){
                printf("Error type 7 at line %d: Operands type mismatched\n",Exp->lineno);
                semantic_error = 1;
            }
            retType = t1;
            return retType;

        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"STAR") == 0){//Exp STAR Exp
            Type t1 = exp_analysis(Exp->nt_node.node[0]);
            Type t2 = exp_analysis(Exp->nt_node.node[2]);

            if(!isTypeEqual(t1,t2) || t1->kind != 0){
                printf("Error type 7 at line %d: Operands type mismatched\n",Exp->lineno);
                semantic_error = 1;
            }
            retType = t1;
            return retType;

        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"DIV") == 0){//Exp DIV Exp
            Type t1 = exp_analysis(Exp->nt_node.node[0]);
            Type t2 = exp_analysis(Exp->nt_node.node[2]);

            if(!isTypeEqual(t1,t2) || t1->kind != 0){
                printf("Error type 7 at line %d: Operands type mismatched\n",Exp->lineno);
                semantic_error = 1;
            }
            retType = t1;
            return retType;

        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"LP") == 0){//ID LP RP
            ID_type *tmpID = hash_find(Exp->nt_node.node[0]->id_attr,1);
            if(tmpID == NULL){
                semantic_error = 1;
                if(hash_find(Exp->nt_node.node[0]->id_attr,0) != NULL)
                    printf("Error type 11 at line %d: \"%s\" must be a function\n",
                            Exp->lineno,Exp->nt_node.node[0]->id_attr);
                else
                    printf("Error type 2 at line %d: Undefined function \"%s\"\n",
                            Exp->lineno,Exp->nt_node.node[0]->id_attr);
                retType = NULL;
            }
            else{
                if(tmpID->funcType.param_num > 0){
                    printf("Error type 9 at line %d: The method \"%s\" is not applicable for the arguments\n",
                            Exp->lineno,Exp->nt_node.node[0]->id_attr);
                    
                    semantic_error = 1;
                    retType = NULL;
                }
                else
                    retType = tmpID->funcType.retType;
            }
            return retType;
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"DOT") == 0){//Exp DOT ID
            Type tmpType = exp_analysis(Exp->nt_node.node[0]);
            if(tmpType == NULL || tmpType->kind != 2){
                printf("Error type 13 at line %d: Illegal use of \".\"\n",Exp->lineno);
                semantic_error = 1;
            }
            else{
                char *name = Exp->nt_node.node[2]->id_attr;
                int ID_valid = 0;
                for(FieldList pField = tmpType->structure.head;pField != NULL;pField = pField->next)
                    if(strcmp(pField->name,name) == 0){
                        ID_valid = 1;
                        retType = pField->type;
                        break;
                    }
                if(!ID_valid){
                    printf("Error type 14 at line %d: Un-existed field \"%s\"\n",Exp->lineno,name);
                    semantic_error = 1;
                    retType = NULL;
                }
            }
            return retType;
        }
        else{//LP Exp RP
            retType = exp_analysis(Exp->nt_node.node[1]);
            return retType;
        }
    }
    else if(Exp->nt_node.num == 4){
        if(strcmp(Exp->nt_node.node[1]->other_terminal,"LB") == 0){//Exp LB Exp RB
            Type t1 = exp_analysis(Exp->nt_node.node[0]);
            Type t2 = exp_analysis(Exp->nt_node.node[2]);
            int flag = 0;
            if(t1 == NULL || t1->kind != 1){
                flag = 1;
                tree_node *Exp1 = Exp->nt_node.node[0];
                printf("Error type 10 at line %d: \"",Exp->lineno);
                semantic_error = 1;
                for(int i = 0; i < Exp1->nt_node.num; i++)
                    print_node(Exp1->nt_node.node[i]);
                printf("\" must be an array\n");
            }
            if(t2 == NULL || t2->kind != 0 || (t2->kind == 0 && t2->basic == 1)){
                flag = 1;
                printf("Error type 12 at line %d: Operands type mistaken\n",Exp->lineno);
                semantic_error = 1;
            }
            if(flag)
                retType = NULL;
            else{
                retType = t1->array.elem;
            }
            return retType;
        }
        else if(strcmp(Exp->nt_node.node[1]->other_terminal,"LP") == 0){//ID LP Args RP
            ID_type *tmpID = hash_find(Exp->nt_node.node[0]->id_attr,1);
            if(tmpID == NULL){
                semantic_error = 1;
                if(hash_find(Exp->nt_node.node[0]->id_attr,0) != NULL)
                    printf("Error type 11 at line %d: \"%s\" must be a function\n",
                            Exp->lineno,Exp->nt_node.node[0]->id_attr);
                else
                    printf("Error type 2 at line %d: Undefined function \"%s\"\n",
                            Exp->lineno,Exp->nt_node.node[0]->id_attr);
                return NULL;
            }
            else{
                tree_node *Args = Exp->nt_node.node[2];
                int argNum = 0,flag = 0,count = 0;
                while(Args->nt_node.num == 3){//统计参数个数
                    argNum++;
                    Args = Args->nt_node.node[2];
                }
                if(tmpID->funcType.param_num != ++argNum)
                    flag = 1;//参数个数不等
                else{
                    Args = Exp->nt_node.node[2];
                    while(Args){//
                        tree_node *Exp = Args->nt_node.node[0];
                        if(!isTypeEqual(tmpID->funcType.param_type[count++],exp_analysis(Exp)))
                            flag = 1;//类型不一致
                        if(Args->nt_node.num == 3)
                            Args = Args->nt_node.node[2];
                        else 
                            Args = NULL;
                    }
                }
                if(flag){
                    printf("Error type 9 at line %d: The method \"%s\" is not applicable for the arguments\n",Exp->lineno,tmpID->ID);
                    semantic_error = 1;
                    return NULL;
                }
                else
                    return tmpID->funcType.retType;

            }
        }
    }
    return retType;
}
void stmt_analysis(tree_node *Stmt, Type funcRetType){
    if(Stmt->nt_node.num == 1)//Stmt->CompSt
        compSt_ret_analysis(Stmt->nt_node.node[0],funcRetType);
    else if(Stmt->nt_node.num == 2)//Stmt->Exp SEMI
        exp_analysis(Stmt->nt_node.node[0]);
    else if(Stmt->nt_node.num == 3){//Stmt->RETURN Exp SEMI
        //通常情况不分析，只有在函数后的CompSt里才分析
        Type retType = exp_analysis(Stmt->nt_node.node[1]);
        if(!isTypeEqual(funcRetType,retType)){
            printf("Error type 8 at line %d: The return type mismatched\n",Stmt->lineno);
            semantic_error = 1;
        }
    }
    else if(Stmt->nt_node.num == 7){//Stmt->IF LP Exp RP Stmt ELSE Stmt
        exp_analysis(Stmt->nt_node.node[2]);
        stmt_analysis(Stmt->nt_node.node[4],funcRetType);
        stmt_analysis(Stmt->nt_node.node[6],funcRetType);
    }
    else if(strcmp(Stmt->nt_node.node[0]->other_terminal,"WHILE") == 0){
        //Stmt->WHILE LP EXP RP Stmt
        exp_analysis(Stmt->nt_node.node[2]);
        stmt_analysis(Stmt->nt_node.node[4],funcRetType);
    }
    else{//Stmt->IF LP Exp RP Stmt
        exp_analysis(Stmt->nt_node.node[2]);
        stmt_analysis(Stmt->nt_node.node[4],funcRetType);

    }
}

void compSt_ret_analysis(tree_node *CompSt, Type funcRetType){
    tree_node *DefList = CompSt->nt_node.node[1];
    tree_node *StmtList = CompSt->nt_node.node[2];
    //DefList analysis
    while(DefList->nt_node.num){
        tree_node *Def = DefList->nt_node.node[0];
        tree_node *Specifier = Def->nt_node.node[0];
        Type currType = specifier_analysis(Specifier);
        tree_node *DecList = Def->nt_node.node[1];
        while(DecList){//DecList->Dec | Dec COMMA DecList
            tree_node *Dec = DecList->nt_node.node[0];
            if(Dec->nt_node.num == 1)//Dec->VarDec 
                varDec_analysis(Dec->nt_node.node[0],currType,1);
            else{//Dec->VarDec ASSIGNOP EXP
                Type varType = varDec_analysis(Dec->nt_node.node[0],currType,1);
                Type expType = exp_analysis(Dec->nt_node.node[2]);
                if(!isTypeEqual(varType,expType)){
                    printf("Error type 5 at line %d: Type mismatched\n",Dec->lineno);
                    semantic_error = 1;
                }
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
        stmt_analysis(Stmt,funcRetType);
        StmtList = StmtList->nt_node.node[1];
    }

}


static void addReadWrite(){//符号表中首先加入 READ() 和 WRITE()函数
    ID_type *readID = (ID_type*)malloc(sizeof(ID_type));
    readID->ID = (char *)malloc(10);
    strcpy(readID->ID,"read");
    readID->type = 1;
    readID->funcType.retType = (Type)malloc(sizeof(struct Type_));
    readID->funcType.retType->kind = BASIC;
    readID->funcType.retType->basic = 0;
    readID->funcType.param_num = 0;
    readID->funcType.param_type = NULL;
    readID->funcType.state = 1;
    readID->funcType.funcLine = -1;
    hash_insert(readID);

    ID_type *writeID = (ID_type*)malloc(sizeof(ID_type));
    writeID->ID = (char *)malloc(10);
    strcpy(writeID->ID,"write");
    writeID->type = 1;
    writeID->funcType.retType = NULL;
    writeID->funcType.param_num = 1;
    Type tmpType = (Type)malloc(sizeof(struct Type_));
    writeID->funcType.param_type = (Type *)malloc(4);
    writeID->funcType.param_type[0] = tmpType;
    writeID->funcType.param_type[0]->kind = BASIC;
    writeID->funcType.param_type[0]->basic = 0;
    writeID->funcType.state = 1;
    writeID->funcType.funcLine = -1;
    hash_insert(writeID);
}


void semantic_analysis(tree_node * pTree){
    addReadWrite();//符号表中首先加入 READ() 和 WRITE()函数

    if((pTree->type == NONTERMINAL_T && pTree->nt_node.num == 0) || pTree->type != NONTERMINAL_T)//产生式右边为空或者节点为终结符不分析
        return ;
    if(strcmp(pTree->nt_node.name,"ExtDef") == 0){
        tree_node *Specifier = pTree->nt_node.node[0];
        if(pTree->nt_node.num == 2){//ExtDef->Specifier SEMI
            specifier_analysis(Specifier);
        }
        else if(strcmp(pTree->nt_node.node[1]->nt_node.name,"ExtDecList" ) == 0){//ExtDef->Specifier ExtDecList SEMI
            Type currType = specifier_analysis(Specifier);
            tree_node *ExtDecList = pTree->nt_node.node[1];
            while(ExtDecList){//ExtDecList->VarDec | VarDec COMMA ExtDecList
                tree_node *VarDec = ExtDecList->nt_node.node[0];
                varDec_analysis(VarDec,currType,1);

                if(ExtDecList->nt_node.num == 1)
                    ExtDecList = NULL;
                else
                    ExtDecList = ExtDecList->nt_node.node[2];
            }
        }
        else if(strcmp(pTree->nt_node.node[1]->nt_node.name,"FunDec" ) == 0 && 
                pTree->nt_node.node[2]->type == OTHER_TERMINAL_T){//ExtDef->Specifier FunDec SEMI
            Type currType = specifier_analysis(Specifier);
            tree_node *FunDec = pTree->nt_node.node[1];
            ID_type *tmpID = hash_find(FunDec->nt_node.node[0]->id_attr,1);
            if(tmpID != NULL){//声明或者定义过
                tree_node *VarList = FunDec->nt_node.node[2];
                int argNum = 0,flag = 0,count = 0;
                if(!isTypeEqual(tmpID->funcType.retType,currType)){//返回值类型不同
                    flag = 1;
                }
                while(VarList->nt_node.num == 3){//统计参数个数
                    argNum++;
                    VarList = VarList->nt_node.node[2];
                }
                if(tmpID->funcType.param_num != ++argNum)
                    flag = 1;//参数个数不等
                else{
                    VarList = FunDec->nt_node.node[2];
                    while(VarList){//
                        tree_node *ParamDec = VarList->nt_node.node[0];
                        Type tmpType = specifier_analysis(ParamDec->nt_node.node[0]);
                        Type paramType = varDec_analysis(ParamDec->nt_node.node[1],tmpType,0);
                        if(!isTypeEqual(tmpID->funcType.param_type[count++],paramType))
                            flag = 1;//类型不一致
                        if(VarList->nt_node.num == 3)
                            VarList = VarList->nt_node.node[2];
                        else 
                            VarList = NULL;
                    }
                }
                if(flag){
                    printf("Error type 19 at line %d: Inconsistent declaration of function\"%s\"\n",FunDec->lineno,tmpID->ID);
                    semantic_error = 1;
                }
            }
            else{
                ID_type *newID = (ID_type *)malloc(sizeof(struct ID_type));
                memset(newID,0,sizeof(struct ID_type));
                newID->ID = FunDec->nt_node.node[0]->id_attr;
                newID->type = 1;
                newID->next = NULL;
                newID->funcType.retType = (Type)malloc(sizeof(struct Type_));
                *newID->funcType.retType = *currType;
                newID->funcType.state = 0;//声明状态
                newID->funcType.funcLine = FunDec->lineno;//写入第一次声明时的行号
                newID->funcType.param_num = 0;
                if(FunDec->nt_node.num == 3){//FunDec->ID LP RP 
                    newID->funcType.param_type = NULL;
                }
                else{//FunDec->ID LP VarList RP
                    tree_node *VarList = FunDec->nt_node.node[2];
                    int paramNum = 0;
                    while(VarList){//第一次循环统计参数个数
                        paramNum++;
                        if(VarList->nt_node.num == 1)
                            VarList = NULL;
                        else
                            VarList = VarList->nt_node.node[2];
                    }
                    newID->funcType.param_num = paramNum;
                    newID->funcType.param_type = (Type *)malloc(sizeof(Type)*paramNum);
                    VarList = FunDec->nt_node.node[2];
                    //第二次循环将对应参数类型写入
                    int i = 0;
                    while(VarList){//VarList->ParamDec COMMA VarList | ParamDec
                        tree_node *ParamDec = VarList->nt_node.node[0];
                        Type varType = specifier_analysis(ParamDec->nt_node.node[0]);
                        tree_node *VarDec = ParamDec->nt_node.node[1];
                        Type tmpType = varDec_analysis(VarDec,varType,0);
                        if(tmpType != NULL){
                            newID->funcType.param_type[i] = (Type)malloc(sizeof(struct Type_));
                            *newID->funcType.param_type[i++] = *tmpType;
                        }
                        else
                            newID->funcType.param_type[i++] = NULL;

                        if(VarList->nt_node.num == 1)
                            VarList = NULL;
                        else
                            VarList = VarList->nt_node.node[2];
                    }
                }
                hash_insert(newID); 
            }

        }
        else{//ExtDef->Specifier FunDec CompSt
            Type currType = specifier_analysis(Specifier);
            tree_node *FunDec = pTree->nt_node.node[1];
            ID_type *tmpID = hash_find(FunDec->nt_node.node[0]->id_attr,1);
            if(tmpID != NULL){//声明或者定义过
                if(tmpID->funcType.state == 1){//定义过
                    printf("Error type 4 at line %d: Redefined function \"%s\"\n",
                            FunDec->lineno,FunDec->nt_node.node[0]->id_attr);
                    semantic_error = 1;
                }
                else{//声明过    
                    tree_node *VarList = FunDec->nt_node.node[2];
                    int argNum = 0,flag = 0,count = 0;
                    if(!isTypeEqual(tmpID->funcType.retType,currType)){//返回值类型不同
                        flag = 1;
                    }
                    while(VarList->nt_node.num == 3){//统计参数个数
                        argNum++;
                        VarList = VarList->nt_node.node[2];
                    }
                    if(tmpID->funcType.param_num != ++argNum)
                        flag = 1;//参数个数不等
                    else{
                        VarList = FunDec->nt_node.node[2];
                        while(VarList){//
                            tree_node *ParamDec = VarList->nt_node.node[0];
                            Type tmpType = specifier_analysis(ParamDec->nt_node.node[0]);
                            Type paramType = varDec_analysis(ParamDec->nt_node.node[1],tmpType,1);
                            if(!isTypeEqual(tmpID->funcType.param_type[count++],paramType))
                                flag = 1;//类型不一致
                            if(VarList->nt_node.num == 3)
                                VarList = VarList->nt_node.node[2];
                            else 
                                VarList = NULL;
                        }
                    }
                    if(flag){
                        printf("Error type 19 at line %d: Inconsistent declaration of function\"%s\"\n",FunDec->lineno,tmpID->ID);
                        tmpID->funcType.state = 2;
                    }
                    else
                        tmpID->funcType.state = 1;

                }

            }
            else{
                ID_type *newID = (ID_type *)malloc(sizeof(struct ID_type));
                newID->ID = FunDec->nt_node.node[0]->id_attr;
                newID->type = 1;
                newID->next = NULL;
                newID->funcType.retType = (Type)malloc(sizeof(struct Type_));
                *newID->funcType.retType = *currType;
                newID->funcType.param_num = 0;
                newID->funcType.state = 1;
                if(FunDec->nt_node.num == 3){//FunDec->ID LP RP 
                    newID->funcType.param_type = NULL;
                }
                else{//FunDec->ID LP VarList RP
                    tree_node *VarList = FunDec->nt_node.node[2];
                    int paramNum = 0;
                    while(VarList){//第一次循环统计参数个数
                        paramNum++;
                        if(VarList->nt_node.num == 1)
                            VarList = NULL;
                        else
                            VarList = VarList->nt_node.node[2];
                    }
                    newID->funcType.param_num = paramNum;
                    newID->funcType.param_type = (Type *)malloc(sizeof(Type)*paramNum);
                    VarList = FunDec->nt_node.node[2];
                    //第二次循环将对应参数类型写入
                    int i = 0;
                    while(VarList){//VarList->ParamDec COMMA VarList | ParamDec
                        tree_node *ParamDec = VarList->nt_node.node[0];
                        Type varType = specifier_analysis(ParamDec->nt_node.node[0]);
                        tree_node *VarDec = ParamDec->nt_node.node[1];
                        Type tmpType = varDec_analysis(VarDec,varType,1);
                        if(tmpType != NULL){
                            newID->funcType.param_type[i] = (Type)malloc(sizeof(struct Type_));
                            *newID->funcType.param_type[i++] = *tmpType;
                        }
                        else
                            newID->funcType.param_type[i++] = NULL;
                        
                        if(VarList->nt_node.num == 1)
                            VarList = NULL;
                        else
                            VarList = VarList->nt_node.node[2];
                    }
                }
                hash_insert(newID);
            }
            
            compSt_ret_analysis(pTree->nt_node.node[2],currType);
        }
    }
    else{
        for(int i=0; i < pTree->nt_node.num; i++){
            semantic_analysis(pTree->nt_node.node[i]);
        }
    }

    if(strcmp(pTree->nt_node.name,"Program") == 0){//语义分析结束时查看是否有函数声明过，但是没有定义过
        for(int i = 0; i < TABLE_SIZE; i++){
            if(ID_table[i] != NULL){
                ID_type *tmpID = ID_table[i];
                while(tmpID){
                    if(tmpID->type == 1 && tmpID->funcType.state == 0){//ID为函数且为声明状态
                        printf("Error type 18 at line %d: Function \"%s\" is declared but not defined\n",
                                tmpID->funcType.funcLine,tmpID->ID);
                        semantic_error = 1;
                    }
                    tmpID = tmpID->next;
                }
            }
        }
    }
}



unsigned short hash_pjw(char *name){
    assert(name != NULL);
    unsigned short val = 0,i;
    for(; *name; ++name){
        val = (val << 2) + *name;
        if(i = val & ~0x3fff)
            val = (val^(i >> 12))&0x3fff;
    }
    return val;
}

ID_type *hash_find(char *name,int type){//0:var 1:func 2:struct
    if(name == NULL || type < 0 || type > 2){
        printf("hash_find error,name = '%s', type = %d\n",name,type);
        exit(0);
    }
    short pos = hash_pjw(name);
    ID_type *tmp = ID_table[pos];
    if(type != 1){//如果是变量和结构体，查找表中的变量和结构体
        while(tmp){
            if(strcmp(name,tmp->ID) == 0 && (tmp->type == 0 || tmp->type ==2))
                return tmp;
            tmp = tmp->next;
        }
    }
    else{//对于函数，只查找函数是否重名
        while(tmp){
            if(strcmp(name,tmp->ID) == 0 && tmp->type == type)
                return tmp;
            tmp = tmp->next;
        }
    }
    return NULL;
}

void hash_insert(ID_type* pID){
    if(pID == NULL){
        printf("hash_insert error,pID == NULL\n");
        exit(0);
    }
    short pos = hash_pjw(pID->ID);
    ID_type *tmp = ID_table[pos];
    if(tmp == NULL)
        ID_table[pos] = pID;
    else{
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = pID;
    }
}

int isTypeEqual(Type t1,Type t2){
    if(t1 == NULL || t2 == NULL || t1->kind != t2->kind)
        return 0;
    if(t1->kind == 0)//basic
        return t1->basic == t2->basic;
    else if(t1->kind == 1){//array
        return isTypeEqual(t1->array.elem,t2->array.elem);
    }
    else if(t1->kind == 2){//struct
        if(strcmp(t1->structure.name,t2->structure.name) == 0)
            return 1;
        else
            return 0;
    }
    else{
        printf("Type kind = %d error \n",t1->kind);
        exit(0);
    }
}

void print_node(tree_node *p){
    if(p->type == NONTERMINAL_T){
        for(int i = 0; i < p->nt_node.num; i++)
            print_node(p->nt_node.node[i]);
    }
    else{
        if(p->type == INT_T)
            printf("%d",p->int_attr);
        else if(p->type == FLOAT_T)
            printf("%f",p->float_attr);
        else if(p->type == ID_T)
            printf("%s",p->id_attr);
        else if(p->type == OTHER_TERMINAL_T)
            printf("%s",p->other_terminal);
    }
        
}







