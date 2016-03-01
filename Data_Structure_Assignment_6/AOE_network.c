#include <stdio.h>
#include <stdlib.h>

void modified_TopoSort(int **graph,int *count,int *early,int vertex)
{
     int i,j,k,top = -1,order = 0;
     int temp[vertex];
     
     for(i = 0 ; i < vertex ; i++)               //push starting vertex to stack
           if( !count[i])
           {
               count[i] = top;
               top = i;
           }
     for(i = 0 ; i < vertex ; i++) early[i] = 0; //initializing earliest start time for vertex to zero
     for(i = 0 ; i < vertex ; i++)               //determine the topological order(refer to textbook) and earliest start time
     {
           if(top <= -1)
           {
                  printf("Infeasible network! Network has a cycle.");
                  system("pasue");
                  exit(EXIT_FAILURE);
           }
           else
           {
               k = top;                       //pop from stack
               top = count[k];                //top move down
               count[k] = order--;            //record top. order in pop element
               for(j = 0 ; j < vertex ; j++)
                     if( graph[k][j])
                     {
                         count[j]--;
                         if( !count[j])
                         {
                             count[j] = top;
                             top = j;
                         }
                         if(early[j] < early[k] + graph[k][j]) early[j] = early[k] + graph[k][j]; //determine early
                     }
           }
     }
     for(i = 0 ; i < vertex ; i++) temp[i] = -count[i]; //count become top. ordered vertices in network
     for(i = 0 ; i < vertex ; i++) count[temp[i]] = i;
}
void AOE(int **graph,int *count,int vertex)                   //count record the number of predecessors
{
     int i,j,k,early[vertex],late[vertex];
     int e,l,slack,flag;
     
     modified_TopoSort(graph,count,early,vertex);             //calculate earliest start time by modified_TopoSort
     
     for(i = 0 ; i < vertex ; i++) late[i] = early[vertex-1]; //initialize latest time for vertex to finished time
     for(i = vertex -2 ; i >= 0; i--)                         //calculate latest time with inverse order of top. sort(count)
           for(j = 0 ; j < vertex ; j++)
                 if( graph[count[i]][j] && (late[count[i]] > late[j] - graph[count[i]][j]))
                     late[count[i]] = late[j] - graph[count[i]][j];
     
     printf("activity\tearly time\tlate time\tslack\n");
     for(i = 0 ; i < vertex ; i++)
           for(j = 0 ; j < vertex ; j++)                      //calculate early and late of activities(edges)
                 if( graph[i][j])
                 {
                     e = early[i];
                     l = late[j] - graph[i][j];
                     slack = l - e;
                     printf("(%d,%d)\t:\t%d\t\t%d\t\t%d\n",i,j,e,l,slack);
                     if(slack) graph[i][j] = 0;          //delete noncritical activities
                 }
                 
     printf("critical path:\n");
     for(i = 0 ; i < vertex ; i++)         //print all critical paths
     {
           flag = 0;
           for(j = 0 ; j < vertex ; j++)
                 if( graph[count[i]][j])
                 {
                     printf("(%d,%d),",count[i],j);
                     flag = 1;
                 }
           if(flag)printf("\b \n");
     }
}
int main()
{
    int i,j,**graph,vertex;
    char filename[128];
    FILE *fprt;
    
    printf("Please input file name: ");
    scanf("%s",filename);
    
    fprt = fopen(filename,"r");
    fscanf(fprt,"%d",&vertex);
    graph = (int **) malloc(vertex*sizeof(int*));
    for(i = 0 ; i < vertex ; i++) graph[i] = (int *) malloc(vertex*sizeof(int));
    
    int count[vertex];
    for(i = 0 ; i < vertex ; i++) count[i] = 0;
    for(i = 0 ; i < vertex ; i++)
          for(j = 0 ; j < vertex ; j++)
          {
                fscanf(fprt,"%d",&graph[i][j]);
                if(graph[i][j]) count[j]++;
          }
    
    AOE(graph,count,vertex);
    
    fclose(fprt);
    free(graph);
    
    system("pause");
    return 0;
}
