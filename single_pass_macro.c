#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

void main(){
    FILE *input,*output,*nametab,*deftab;
    remove("nametab.txt");
    input=fopen("macroInput.txt","r");
    output=fopen("macroOut.txt","w");
    nametab=fopen("nametab.txt","w");
    deftab=fopen("deftab.txt","w");

    char label[20],opcode[20],operand[20],parameter[20],args[20],name[20];
    int pos,length,isCall,arglen,isarg;
    
    fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    

    if(strcmp(opcode,"START")==0){
        fprintf(output,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
        
    }

    while(!feof(input)){

            if(strcmp(opcode,"MACRO")==0){
                
                    
                fprintf(deftab,"%s\t%s\t%s\n",label,opcode,operand);  //writing the macro definition into the deftab
                
                length=0;
                if(strcmp(operand,"**")!=0){    //to find the position of the arguments if any
                    
                    for(int i=0;operand[i]!='\0';i++){

                        if(operand[i]!='&' && operand[i]!=',' && operand[i]!=' '){
                            parameter[length++]=operand[i];
                        }
                        parameter[length]='\0';
                    }
                }
                fclose(nametab);
                nametab=fopen("nametab.txt","r");
                while(!feof(nametab)){  //checking for macro duplication
                    
                    fscanf(nametab,"%s\t%d",name,&arglen);
                       if(strcmp(name,label)==0){
                            printf("duplicate macro name found : %s ",label);
                            exit(0);
                       }
                }
                fclose(nametab);
                nametab=fopen("nametab.txt","a");
                fprintf(nametab,"%s\t%d\n",label,length); //printing the macro name to the nametab with the number of arguments

                
                fscanf(input,"%s\t%s\t%s",label,opcode,operand);
                
                
                while(strcmp(opcode,"MEND")!=0){
                    
                        
                    pos=0;
                    for(int i=0;i<length;i++){       //checking if the operand is a parameter in the macro
                        if(parameter[i]==operand[1]){
                            pos=i+1;
                            break;
                        }
                    }
                    
                        
                    if(pos>0)
                        fprintf(deftab,"%s\t%s\t%d\n",label,opcode,pos);
                    else
                        fprintf(deftab,"%s\t%s\t%s\n",label,opcode,operand);
                        
                    fscanf(input,"%s\t%s\t%s",label,opcode,operand); //scanning the next line

                    if(strcmp(opcode,"MEND")==0)
                        fprintf(deftab,"%s\t%s\t%s\n",label,opcode,operand);

                }
                
                
            }else{
                if(strcmp(opcode,"END")!=0){
                    fclose(nametab);
                    nametab=fopen("nametab.txt","r");
                    isCall=0;
                    while(!feof(nametab)){    //search nametag for opcode to know if it is a macro call
                       fscanf(nametab,"%s\t%d",name,&arglen);
                       if(strcmp(name,opcode)==0){
                            isCall=1;
                            break;
                       }
                    }

                    if(isCall==1){
                        fprintf(output,"%s\t.%s\t%s\n",label,opcode,operand);
                        if(arglen>0 && strcmp(operand,"**")!=0 && operand[0]!='\0'){  //storing the arguments into the argtab(here args array is used)
                                int j=0;
                                for(int i=0;i<strlen(operand);i++){
                                        if(operand[i]!=','&& operand[i]!=' '){
                                                args[j++]=operand[i];
                                        }
                                }
                                args[j]='\0';
                                
                        }else{
                            printf("arguments expected for the macro call %s",opcode);
                            exit(0);
                        }
                        fclose(deftab);
                        deftab=fopen("deftab.txt","r");
                        while(!feof(deftab)){
                            fscanf(deftab,"%s\t%s\t%s",label,opcode,operand);
                            if(strcmp(label,name)==0){
                                fscanf(deftab,"%s\t%s\t%s",label,opcode,operand);
                                while(strcmp(opcode,"MEND")!=0){
                                    isarg=1;
                                    for(int i=0;i<strlen(operand);i++){
                                        if(!isdigit(operand[i])){
                                            isarg=0;
                                            break;
                                        }
                                    }
                                    if(isarg==1)
                                        fprintf(output,"%s\t%s\t%c\n",label,opcode,args[atoi(operand)-1]);
                                    else
                                        fprintf(output,"%s\t%s\t%s\n",label,opcode,operand);

                                    fscanf(deftab,"%s\t%s\t%s",label,opcode,operand);
                                }
                            }
                        }
                    }else{
                        
                        fprintf(output,"%s\t%s\t%s\n",label,opcode,operand);
                    }
                    
                }
            }
            fscanf(input,"%s\t%s\t%s",label,opcode,operand);

            if(strcmp(opcode,"END")==0){
                fprintf(output,"%s\t%s\t%s",label,opcode,operand);
                break;
            }
    }

}

/*
SAMPLE INPUT
__ __ __ __ _ __ __ __ __ _ __ __ __ ___ __  __
PGM     START   0
ABC     MACRO   &A,&B
**      STA     &A
**      STB     &B
**      MEND    **
DEF    MACRO   &F,&T
**      STA     &F
**      STB     &T
**      MEND    **
**      ABC     P,Q
**      DEF     R,S
**      END     **


INPUT CRITERIA 
_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    1. THE PARAMETER AND ARGUMENT LENGTH SHOULD BE 1
    2. GIVE ** IN EMPTY SPACE
    3. SHOULD GIVE START & END 

*/
        