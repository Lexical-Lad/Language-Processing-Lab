#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fout,*fin;
    char str1[100000],str2[100000];
    int i,j,k;
    char *tt;

    char lex[100][20]={"double","int","long","float","void","struct","char","auto","break","case",
                        "const","continue","default","do",
                        "else","enum","extern",
                        "for","goto","if",
                        "register","return","short","signed",
                        "sizeof","static","switch",
                        "typedef","union","unsigned",
                        "volatile","while",

                        ".","->","++","--","!","~","(type)","*","&",
                         "sizeof","*","/","%","+","-","<<",">>","<",
                         "<=",">",">=","==","!=","&","^","|","&&","||",
                         "?:","=","+=","-=","*=","/=","%=","&=","^=",
                         "|=","<<=",">>=",","};

    // indices 0 to 31 correspond to keywords
    //  indices 32 to 72 are operators
    //


    fin=fopen("input.txt","r");
    fout=fopen("output.txt","w");

    char temp,temp1;

    temp=fgetc(fin);

    i=-1;

    while(!feof(fin))
    {
        str1[++i]=temp;
       // printf("%d \n",temp);

        temp=fgetc(fin);
        //fflush(stdin);
    }

    // printf("%c",str1[0]);

    //printf("whatever");
    //printf("%d",i);

    for(j=0;j<=i;j++)
     printf("%c",str1[j]);

    k=-1;

    for(j=0;j<=i;j++)
    {

        temp=str1[j];

        if(temp!=' ' && temp!='/')
        str2[++k]=temp;
        else if(temp==' ')
        {
            str2[++k]=temp;

            if(j<i)
            while((temp=str1[++j])==' ')
            {
                if(j==i)
                break;
            }

            if(temp!=' ')
                j--;




        }
        else if(temp=='/')
        {

            temp1=str1[j+1];

            if(temp1=='/')
            {
                j++;
                while((temp=str1[++j])!='\n')
                {
                    if(j==i)
                    break;
                }

                if(temp=='\n')
                {
                    str2[++k]=temp;

                }

            }
            else if(temp1=='*')
            {
                j++;

                while(!(temp=str1[++j]=='*'  && str1[j+1]=='/'))
                {
                    if(j==i)
                    break;
                }


                if(j==i)
                {
                    printf("SYNTAX ERROR");
                    exit(0);
                }


                str2[++k]='\n';



            }


        }


    } // k has the length(-1) of the new program(without comments and extra spaces)(the new program is in str2

    fprintf(fout,"%s %s %s \r\n","LEXEME","\t","TOKEN\n");


    // searching for operators first




    for(i=32;i<=72;i++)
    {
        if((tt=strstr(str2,lex[i]))!=NULL )
        fprintf(fout,"%s %s %s \r\n",lex[i],"\t","operator\n");

    }


    //searching for keywords



    tt=strtok(str2," \n");

	while(tt!=NULL)
	{
		for(i=0;i<=31;i++)
		{
			if(strcmp(tt,lex[i])==0)
			fprintf(fout,"%s %s %s \r\n",lex[i],"\t","keyword\n");


		}
		tt=strtok(NULL," \n");
	}
	
	