#include<stdio.h>
#include<string.h>
void main()
{
 char macros[20][10], label[20],opcode[20],operand[20];
 int i, j, n,m=0;
 FILE *fp1, *fp[10];
 
 fp1=fopen("inputm.txt","r");
 fscanf(fp1,"%s%s%s",label,opcode,operand);
 while(strcmp(opcode,"END")!=0)
 {
 if(!strcmp(opcode,"MACRO")){
 fp[m]=fopen(operand,"w");
 m++;
 fscanf(fp1,"%s%s%s",label,opcode,operand);
 while(strcmp(opcode,"MEND")!=0){
 fprintf(fp[m-1],"%s\t%s\t%s\n",label,opcode,operand);
 fscanf(fp1,"%s%s%s",label,opcode,operand);
 }
 } 
 fscanf(fp1,"%s%s%s",label,opcode,operand);
 }
}