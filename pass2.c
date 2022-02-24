#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){

        FILE *output,*interFile,*lenFile,*optab,*symtab;
        
        char address[10],label[10],opcode[10],operand[10],len[5],mnemonic[10],mnemonic_val[5],symbol[10],symbol_val[10];
        int opcode_found,counter=0,ignore=0,constant=0,sym_found;
        //printf("length %d",length);
        interFile=fopen("interFile.txt","r");
        //output=fopen("output.txt","w");
        lenFile=fopen("lenFile.txt","r");
        fscanf(interFile,"%s\t%s\t%s\t%s",address,label,opcode,operand);
        fscanf(lenFile,"%s",len);
        //length=atoi(len);
        //printf("length %d",length);
        if(strcmp(opcode,"START")==0){
           // fprintf(output,"H^%s^%.6d^%.6d\n",label,atoi(operand),length);
            printf("H^%s^%s^%s",label,operand,len);
            fscanf(interFile,"%s\t%s\t%s\t%s",address,label,opcode,operand);
        }

        while (!feof(interFile))
        {
                if(strcmp(opcode,"END")==0){
                    //fprintf(output,"\nE^%.6d",atoi(operand));
                    printf("\nE^%.6d",atoi(operand));
                    
                    exit(1);
                }
                optab=fopen("optab.txt","r");
                opcode_found=0;
                while(!feof(optab)){

                        fscanf(optab,"%s\t%s",mnemonic,mnemonic_val);
                        if(strcmp(mnemonic,opcode)==0){
                            opcode_found=1;
                            break;
                        }
                        
                }
                fclose(optab);
                if(opcode_found==0){
                        ignore=0;
                        constant=0;
                        if(strcmp(opcode,"WORD")==0 || strcmp(opcode,"BYTE")==0){
                            strcpy(mnemonic_val,operand);
                            opcode_found=1;
                            constant=1;
                            counter++;
                            
                        }else if(strcmp(opcode,"RESB")==0 || strcmp(opcode,"RESW")==0){
                            ignore=1;
                        }else{
                            printf("invalid opcode found!!");
                            exit(1);
                        }
                        
                }
                if(ignore==0){
                    if(constant==0){
                        symtab=fopen("symtab.txt","r");
                        sym_found=0;
                        while(!feof(symtab)){
                                fscanf(symtab,"%s\t%s",symbol,symbol_val);
                                if(strcmp(operand,symbol)==0){
                                    strcat(mnemonic_val,symbol_val);
                                    sym_found=1;
                                    counter++;
                                    
                                    break;
                                }
                        }
                        if(sym_found==0){
                            printf("invalid symbol found: %s",operand);
                            exit(1);
                        }
                        fclose(symtab);
                    }
                    if(counter>10)
                        counter=1;
                    if(counter==1){
                       // fprintf(output,"\nT^%.6d^1E^",atoi(address));
                        printf("\nT^%s^1E",address);
                    }
                    //fprintf(output,"%.6d^",atoi(mnemonic_val));
                    printf("^%s",mnemonic_val);
                }
                fscanf(interFile,"%s\t%s\t%s\t%s",address,label,opcode,operand);

                if(strcmp(opcode,"END")==0){
                    //fprintf(output,"\nE^%.6d",atoi(operand));
                    printf("\nE^%s",operand);
                    
                    exit(1);
                }

        }
        fclose(interFile);
        fclose(output);
        fclose(symtab);
        fclose(optab);
        fclose(lenFile);

}