#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void convert(char h[12]);
char bitmask[12];
char bit[12] = {0};
void main()
{
    char  input[10], binary[12], relocbit, ch, pn[5];
    int start, inp, len, i, address, opcode, addr, actualadd, tlen,add, length;
    FILE *reloc_in, *reloc_out;
    printf("\n\n Enter the actual starting address : ");
    scanf("%x", &start);
    reloc_in = fopen("RLIN.txt", "r");
    reloc_out = fopen("RLOUT.txt", "w");
    fscanf(reloc_in, "%s", input);
    fprintf(reloc_out, " ----------------------------\n");
    fprintf(reloc_out, " ADDRESS\tCONTENT\n");
    fprintf(reloc_out, " ----------------------------\n");
    while (strcmp(input, "E") != 0)
    {
        if (strcmp(input, "H") == 0)
        {
            fscanf(reloc_in, "%s", pn);
            fscanf(reloc_in, "%x", &add);
            fscanf(reloc_in, "%x", &length);
            fscanf(reloc_in, "%s", input);
        }
        if (strcmp(input, "T") == 0)
        {
            fscanf(reloc_in, "%x", &address);
            fscanf(reloc_in, "%x", &tlen);
            fscanf(reloc_in, "%s", bitmask);
            address += start;
            convert(bitmask);
            len = strlen(bit);
            if (len >= 11)
                len = 10;
            for (i = 0; i < len; i++)
            {
                fscanf(reloc_in, "%x", &opcode);
                fscanf(reloc_in, "%x", &addr);
                relocbit = bit[i];
                if (relocbit == '0')
                    actualadd = addr;
                else
                    actualadd = addr + start;
                fprintf(reloc_out, "\n  %x\t\t%x%x\n", address, opcode, actualadd);
                address += 3;
            }
            fscanf(reloc_in, "%s", input);
        }
    }
    fprintf(reloc_out, " ----------------------------\n");
    fclose(reloc_in);
    fclose(reloc_out);
    printf("\n\n The contents of output file(RLOUT.TXT) \n");
    reloc_out = fopen("RLOUT.txt", "r");
    ch = fgetc(reloc_out);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(reloc_out);
    }
    fclose(reloc_out);
    //
}
void convert(char h[12])
{
    int i, l;
    strcpy(bit, "");
    l = strlen(h);
    for (i = 0; i < l; i++)
    {
        switch (h[i])
        {
        case '0':
            strcat(bit, "0");
            break;
        case '1':
            strcat(bit, "1");
            break;
        case '2':
            strcat(bit, "10");
            break;
        case '3':
            strcat(bit, "11");
            break;
        case '4':
            strcat(bit, "100");
            break;
        case '5':
            strcat(bit, "101");
            break;
        case '6':
            strcat(bit, "110");
            break;
        case '7':
            strcat(bit, "111");
            break;
        case '8':
            strcat(bit, "1000");
            break;
        case '9':
            strcat(bit, "1001");
            break;
        case 'A':
            strcat(bit, "1010");
            break;
        case 'B':
            strcat(bit, "1011");
            break;
        case 'C':
            strcat(bit, "1100");
            break;
        case 'D':
            strcat(bit, "1101");
            break;
        case 'E':
            strcat(bit, "1110");
            break;
        case 'F':
            strcat(bit, "1111");
            break;
        }
    }
}