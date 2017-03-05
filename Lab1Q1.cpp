#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main()
{
    FILE *fout,*fin;
    char str1[100000],str2[100000];
    int i,j,k;

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


    }


    for(j=0;j<=k;j++)
        fprintf(fout,"%c",str2[j]);


        fclose(fin);
        fclose(fout);

   return 0;


}

