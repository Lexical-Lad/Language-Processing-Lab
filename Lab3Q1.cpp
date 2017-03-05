#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fout,*fin;
    char str1[100000],str2[100000],str3[100000];
    int i,j,k;
    char *tt,*tt2;

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

	strcpy(str3,str2);

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


	//checking variable definintions

	strcpy(str2,str3);


	tt=strtok(str2," ,{}()\r\n\r\v\f\t;");


	while(tt!=NULL)
	{
		k=0;
		for(i=0;i<73;i++)
		if(strcmp(tt,lex[i])==0)
		k=1;

		if(k==0)
		fprintf(fout,"%s %s %s \r\n",tt,"\t","identifier\n");

		tt=strtok(NULL," ,{}()\r\n\r\v\f\t;");
	}



	//for(i=0;i<1000;i++)
	//printf("%c",str2[i]);

	/*tt=strtok(str2," ,\n{}");

	while(tt!=NULL)
	{
		printf("%s \n",tt);
		for(i=0;i<7;i++)
		{
			printf("%s \n",tt);

			if(strcmp(tt,lex[i])==0)
			{
				tt=strtok(NULL," ,\n{}");
				printf("%s",tt);

				while(strcmp(tt,lex[0])==0 || strcmp(tt,lex[1])==0 || strcmp(tt,lex[2])==0 || strcmp(tt,lex[3])==0 || strcmp(tt,lex[4])==0 || strcmp(tt,lex[5])==0 || strcmp(tt,lex[6])==0 )
				tt=strtok(NULL," ,\n{}");


				do
				{
					printf("%s",tt);
					if(strstr(tt,"(")!=NULL)
					break;


					fprintf(fout,"%s %s %s \r\n",tt,"\t","identifier\n");
					tt=strtok(NULL," ,\n{}");

				}while(strcmp(tt,";")!=0);

			}

		}
		tt=strtok(NULL," ,\n{}");
		//printf("%s \n",tt);


	}*/



   return 0;


}


