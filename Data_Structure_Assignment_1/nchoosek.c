#include <stdio.h>
#include <stdlib.h>

int iteration_nchoosek(int n,int k)
{
    int i,result = 1;
    
    if(k == 0) return 1;
    
    for(i = 1 ; i <= k ; i++) result = result * (n--)/i;
    
    return result;
}
int recursion_nchoosek(int n,int k)
{
    if(k == 0)
         return 1;
    
    return recursion_nchoosek(n-1,k-1)*n/k;
}
int main()
{
    int n,k;
    int result;
    while(1){
    printf("Compute n choose k, please enter n & k :\n");
    scanf("%d %d",&n,&k);
    
    if(n < k)
    {
         fprintf(stderr,"input error!");
         exit(EXIT_FAILURE);
    }
    
    if(2*k > n) k = (n-k);
    
    result = iteration_nchoosek(n,k);
    printf("result = %d(iterative function)\n",result);
    
    result = 0;

    result = recursion_nchoosek(n,k);
    printf("result = %d(recursive function)\n",result);
        
    system("pause");
    }
    return 0;
}
