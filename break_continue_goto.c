#include <stdio.h>
int main()
{
    // int i,j,n;
    // for(i=1; i<n; i++)
    // {
    //     printf("Eneter number of people: ");
    //      scanf("%d ",&n);
    //     printf("Your age: %d\n", i);
    //      if(i==0)
    //      {
    //          printf("does not exist: ");
    //      }
    // }
    int i=0,j,n=0;
    printf("Enter number: \n");
    scanf("%d",&n);
    printf("Entered number: %d\n",n);
    for(i=0;i<n;i++)
    {
        printf("Your number is %d\n", i+1);
    }
    return 0;
}