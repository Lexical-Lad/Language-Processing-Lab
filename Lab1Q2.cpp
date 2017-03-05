#include <stdio.h>

int main()
{
    int n,i,j;
    char bin[1000];
    int temp;
    int count;
    int state=0;

    printf("Enter a number :\n");

    scanf("%d",&n);

    //There are three states in the DFA in question viz. q0, q1 and q2. q0 state signifies numbers of the form 3n(hence divisible by 3), q1 signifies the numbers of the form '3n+1' and q2, of the form '3n+2'. So, for a number to be divisible by 3, on its binary scan from left to right, the last bit must cause it to end on q0.


    count=1;
    temp=n;

    while((temp/=10)?count++:0); // computes the number of digits

    temp=n;
    i=-1;

    while(temp>0)
    {
       bin[++i]=((temp%2)+48);
       temp/=2;
   }

   for(j=0;j<=(i/2);j++)
   {
       temp=bin[j];
       bin[j]=bin[i-j];
       bin[i-j]=temp;
   }


   printf("q%d ",state);


   for(j=0;j<=i;j++)
   {

       printf("-> ");
       if(state==0)
       {
           if(bin[j]=='1')
           state=1;

       }

       else if(state==1)
       {
           if(bin[j]=='0')
           state=2;
           else
           state=0;

       }

       else
       {
           if(bin[j]=='0')
           state=1;
       }

       printf("q%d ",state);

   }


   if(state==0)
   printf("\n Divisible by 3! \n");
   else
   printf("\n Not Divisible by 3! \n");


}


