#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,k;
    int i,m,result = 1;
    
    printf("Compute n choose k, please enter n & k :\n");
    scanf("%d %d",&n,&k);
    
    if(2*k <= n) k = (n-k);
    m = n;
    
    for(i = 1; i <= k ; i++)
    {
          result = result*i/m;
    }
    
    system("pause");
    return 0;
}
