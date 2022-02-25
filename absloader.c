#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(){

    FILE *objcode,*tempFile;
    objcode=fopen("objcode.txt","r");

    char record[200],address[10];
    int i,start,count=0,j=0,change=0;
    fscanf(objcode,"%s",record);
  
    
    for(i=0;record[i]!='\0';i++){
        if(record[i]=='^')
            count++;
        if(count==2 && record[i]!='^')
            address[j++]=record[i];
        if(count==3)
            break;
    }
    scanf("%x",&start);
    // tempFile=fopen("tempFile.txt","w");
	// fprintf(tempFile,"%s",address);
	// fclose(tempFile);
	// tempFile=fopen("tempFile.txt","r");
	// fscanf(tempFile,"%x",&start);
	// fclose(tempFile);
    fscanf(objcode,"%s",record);
    
    printf("adress\tobjectCode",record);
    
    while (record[0]!='E' && !feof(objcode))
    {
        
        count=0;
        for(i=0;record[i]!='\0';i++){
            if(record[i]=='^'){
                 count++;
                 j=0;
                 if(count>=3){
                    printf("\n%x\t",start);
                    start+=3;
                 }
            }
            if(count>=3 && record[i]!='^'){
                printf("%c",record[i]);
            }
                
        }
            
        fscanf(objcode,"%s",record);

    }

    
    
    fclose(objcode);
    
}