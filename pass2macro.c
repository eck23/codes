#include<stdio.h>
#include<string.h>
void main()
{
 char macros[20][10], label[20],opcode[20],operand[20];
 int i, j, n,m=0;
 FILE *fp1, *fp[10],*fp2;
 
 fp1=fopen("inputm.txt","r");
 fp2=fopen("macro_out.txt","w");
 fscanf(fp1,"%s%s%s",label,opcode,operand);
 while(strcmp(opcode,"END")!=0)
 {
 if(!strcmp(opcode,"CALL"))
 {
 fp[m]=fopen(operand,"r");
 m++;
 fscanf(fp[m-1],"%s%s%s",label,opcode,operand);
 while(!feof(fp[m-1]))
 {
 fprintf(fp2,"%s\t%s\t%s\n",label,opcode,operand);
 fscanf(fp[m-1],"%s%s%s",label,opcode,operand);
 }
 }
else
 {
 fprintf(fp2,"%s\t%s\t%s\n",label,opcode,operand);
 }
 
 fscanf(fp1,"%s%s%s",label,opcode,operand);
 }
 fprintf(fp2,"%s\t%s\t%s\n",label,opcode,operand);
}