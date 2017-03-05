#include <stdio.h>
#include <string.h>

int main ()
{

    char s[1000];
    int state; // -1 for trap
    int length,i;

    printf("Enter a string(of only 'a's and 'b's : \n");

    scanf("%s",s);

    length=strlen(s);

    state=0;

    printf("q%d",state);

    for(i=0;i<length;i++)
    {

        printf("-> ");
        switch(state)
        {
            case 0: if(s[i]=='a')
                    state=1;

                    break;

            case 1: if(s[i]=='b')
                    state=2;

                    break;

            case 2: if(s[i]=='a')
                    state=3;
                    else
                    state=0;
                    break;

            case 3: if(s[i]=='b')
                    state=4;
                    else state=1;
                    break;

        }

        if(state==4)
        break;

        printf("q%d",state);


    }
    printf("\n");

    if(state==4)
    printf("Valid String \n");
    else
    printf("Invalid String \n");

}

