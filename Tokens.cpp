#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
int ch=0;

int isKeyword(const char* token)
{
    const char keywords[32][20]={"auto","break","case","char",
                                "const","continue","default","do","double",
                                "else","enum","extern","float",
                                "for","goto","if","int","long",
                                "register","return","short","signed",
                                "sizeof","static","struct","switch",
                                "typedef","union","unsigned",
                                "void","volatile","while"};
    for(int i=0;i<32;i++)
    {
        if(strcmp(token,keywords[i])==0)
            return 1;
    }
    return 0;
}

int isIntLiteral(const char* token)
{
    for(int i=0;token[i];i++)
    {
        if(!isdigit(token[i]))
            return 0;
    }
    return 1;
}

int isFloatLiteral(const char* token)
{
    if(isdigit(token[0]))
    {
        for(int i=1;token[i]!=(char)NULL;i++)
        {
            if(!isdigit(token[i]) && token[i]!='.' && token[i]!='E' && token[i]!='E')
                return 0;
        }
        return 1;
    }
    return 0;
}

int isCharLiteral(const char* token)
{
	if (ch==1)
		return 1;

    if(token[0]=='\'' && strlen(token)==3 && token[2]=='\'')
        return 1;
    else
        return 0;
}

int isLiteral(const char* token)
{
    if(isCharLiteral(token)||isIntLiteral(token)||isFloatLiteral(token))
        return 1;
    else
        return 0;
}

int isIdentifier(const char* token)
{
    if(isalpha(token[0]) || token[0]=='_')
    {
        for(int i=1;token[i]!=(char)NULL;i++)
        {
            if(!isalnum(token[i]) || (token[i]=='_' && token[i-1]=='_'))
                return 0;
        }
        return 1;
    }
    return 0;
}

int isOperator(const char* token)
{
    const char operators[41][10] = {".","->","++","--","!","~","(type)","*","&",
                                 "sizeof","*","/","%","+","-","<<",">>","<",
                                 "<=",">",">=","==","!=","&","^","|","&&","||",
                                 "?:","=","+=","-=","*=","/=","%=","&=","^=",
                                 "|=","<<=",">>=",","};

    for(int i=0;i<41;i++)
    {
        if(strcmp(token,operators[i])==0)
            return 1;
    }
    return 0;
}

int main()
{
  	int count=0,sc=1,found=0,i=0;
	FILE *fp=fopen("Test_2.cpp","r");

	if(!fp)
	{
    	printf("File ERROR \n");
    	exit(1);
	}

    char *token;
    char scope[2][10]={"Local","Global"},a[1024][100]={NULL};
    char string[1024];
    const char delimiters[]=" .,;!=\n\t";

    printf(" S NO. \t NAME \t TYPE \t       SCOPE \t SIZE  \n");

    fgets(string,sizeof string, fp);
    while( fgets(string,sizeof string, fp)!=NULL )
    {
        token = strtok(string,delimiters);

        while(token!=NULL)
        {
        // printf("\n %s \n",token);

        	if(strcmp(token,"{")==0)
        		sc=0;
        	else
        		sc=1;

        	if(strcmp(token,"\"")==0)
        		if(ch==1)
        			ch==0;
        			else
        			ch=1;
        //	printf("%d",sc);

			for(int i=0;i<count;i++)
			{
				if(strcmp(a[i],token)==0)
					found=1;
			}

			if(found==1)
			{
				found=0;
				continue;
			}
			else
			{
				count++;
				strncpy(a[count], token, sizeof token-1);

			}



            if(isKeyword(token))
            	if(strcmp(token,"byte")==0 || strcmp(token,"char")==0)
            		printf(" %d \t %s \t Keyword \t - \t 1 byte \n",count,token);
            	else
            	if(strcmp(token,"short")==0)
            		printf(" %d \t %s \t Keyword \t - \t 2 bytes \n",count,token);
            	else
            	if(strcmp(token,"int")==0)
            		printf(" %d \t %s \t Keyword \t - \t 4 bytes \n",count,token);
            	else
            	if(strcmp(token,"long")==0 || strcmp(token,"float")==0)
            		printf(" %d \t %s \t Keyword \t - \t 8 bytes \n",count,token);
            	else
            	if(strcmp(token,"double")==0)
            		printf(" %d \t %s \t Keyword \t - \t 16 bytes \n",count,token);

                else   	printf(" %d \t %s \t Keyword \t - \t - \n",count,token);
            else if(isOperator(token))
                 printf(" %d \t %s \t Operator \t - \t - \n",count,token);
            else if(isIdentifier(token))
                 printf(" %d \t %s \t Identifier \t %s \t - \n",count,token,scope[sc]);
            else if(isLiteral(token))
                printf(" %d \t %s \t Literal \t - \t - \n",count,token);
            else
                 printf(" %d \t %s \t Symbol \t - \t - \n",count,token);

            token = strtok(NULL,delimiters);
        }
        fgets(string,sizeof string, fp);
    }

    fclose(fp);
    return 0;
}
