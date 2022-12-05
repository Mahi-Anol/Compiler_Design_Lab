#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define elif else if 

int main()
{
    FILE *input=fopen("input.txt","r");
    FILE *output=fopen("output.txt","w"); 

    if(input)
    {
        printf("Input Loading Succesful\n");
    }
    else
    {
        perror("Input Loading Unsuccesful\n");
    }

    fseek(input,0,SEEK_END);
    int len=ftell(input);
    fseek(input,0,SEEK_SET);

    char *text=(char*)malloc(len+1);
    char *mtext=(char*)malloc(len+1);

    fread(text,sizeof(char),len,input);

    text[len]='\0';

    // printf("%s",text);

    printf("\n");

    int sl=0;
    int ml=0;
    int st=0;

    for(int i=0;i<len;i++)
    {
        // printf("%c",text[i]);
        if(text[i]=='#'&&text[i+1]=='#'&&text[i+2]=='#')
        {
            sl=1;
            i+=2;
        }
        else if(text[i]=='@'&&text[i+1]=='%')
        {
            ml=1;
            i+=1;
        }
        else if(sl==1 && text[i]=='\n')
        {
            sl=0;
        }
        else if(ml==1 && text[i]=='%'&&text[i+1]=='@')
        {
            ml=0;
            i+=1;
        }
        else if(sl==1 || ml==1)
        {
            continue;
        }
        else
        {
            //  printf("%c",text[i]);
             mtext[st++]=text[i];
        }
    }
      
     mtext[st]='\0';
    //  printf("%s",mtext);
    fprintf(output,"%s",mtext);
    fclose(input);
    fclose(output);

    input=fopen("output.txt","r");

    FILE *fe=fopen("even.txt","w");
    FILE *fo=fopen("odd.txt","w");
    
    while(!feof(input))
    {
        char str[40];
        fscanf(input,"%s",str);
        // printf("%s\n",str);

        int ln=strlen(str);
        // printf("%d",ln);

        if(str[ln-1]=='.' ||str[ln-1]==','||str[ln-1]=='?')
        {
            str[ln-1]='\0';
            ln--;
        }
        printf("%s\n",str);

        int flag=1;

        
        for(int i=0;i<ln/2;i++)
        { 
                if(str[i]>str[ln-i-1])
                {
                    if(str[i]-32!=str[ln-i-1])
                    flag=0;
                    break;
                }
                else if(str[i]<str[ln-i-1])
                {
                    if(str[i]!=str[ln-i-1]-32)
                    flag=0;
                    break;
                }
                else
                {
                    continue;
                }
            
        }

        if(flag)
        {
             if(ln%2==0)
             {
                fprintf(fe,"%s\n",str);
             }
             else
             {
                fprintf(fo,"%s\n",str);
             }
        }

    }

    fclose(input);
    fclose(fe);
    fclose(fo);
}
