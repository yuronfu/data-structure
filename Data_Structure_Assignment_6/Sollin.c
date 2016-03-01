#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct{
        int endpoint1;
        int endpoint2;
        int weight;
}EDGE;
EDGE Find_min_cost_edge(int **graph,int vertex,int **MST,int *flag,int cur_vertex)
{
     EDGE min;
     int i,next_vertex[vertex],front = 0,rear = 0;
     
     next_vertex[0] = -1;            //Queue to store set member
     min.weight = INT_MAX;
     while( cur_vertex != -1 )       //search the set for min. cost edge
     {
            for(i = 0 ; i < vertex ; i++)   //search min. cost edge for current vertex in graph
                  if( graph[cur_vertex][i] && (graph[cur_vertex][i] < min.weight) )
                  {
                      min.weight = graph[cur_vertex][i];            //min is used to record the smallest cost edge
                      min.endpoint1 = cur_vertex;
                      min.endpoint2 = i;
                  }
            for(i = 0 ; i < vertex ; i++)  // find other vertices in set
            {
                  if( MST[cur_vertex][i] && !flag[i])
                  {
                      next_vertex[rear] = i;
                      next_vertex[++rear] = -1;
                  }
            }
            flag[cur_vertex] = 1;
            cur_vertex = next_vertex[front++]; //move to next vertex in set until no vertex in set
     }
     return min;
}
void Sollin_MST(int **graph,int vertex,int **MST)
{
     int n = 0,i,j;
     int flag[vertex];
     EDGE temp;
     
     for(i = 0 ; i < vertex ; i++) flag[i] = 0; //initializing flag
     while(n < vertex-1)
     {
             for(i = 0 ; i < vertex ; i++)      //each stage start
             {
                   if(flag[i]) continue;        //searched vertices will be ignored
                   temp = Find_min_cost_edge(graph,vertex,MST,flag,i);
                   MST[temp.endpoint1][temp.endpoint2] = temp.weight; //store min. cost edge of a tree to minimum spanning tree
             }
             for(i = 0 ; i < vertex ; i++) //reset flag for next stage and eliminate picked edge from graph
             {
                   flag[i] = 0;            //reset
                   for(j = i ; j < vertex ; j++)
                   {
                         if(MST[i][j] || MST[j][i])     //adjacency matrix of undirected graph is symmetric 
                         {                              //store non-zero value to another side
                                      (MST[i][j] != 0) ? (MST[j][i] = MST[i][j]) : (MST[i][j] = MST[j][i]);
                                      graph[i][j] = graph[j][i] = 0;  //eliminate
                                      n++;
                         }
                   }
             }
     }
}
void List_MST_edge(int **MST,int vertex)
{
     int i,j,n = 0;
     EDGE MST_edge[vertex-1],temp;
     
     for(i = 0 ; i < vertex ; i++)
           for(j = i ; j < vertex ; j++)
                 if(MST[i][j])
                 {
                              MST_edge[n].endpoint1 = i;
                              MST_edge[n].endpoint2 = j; 
                              MST_edge[n++].weight = MST[i][j];
                 }
     
     for(i = 1 ; i < vertex-1 ; i++)
     {
           n = i-1;
           temp.endpoint1 = MST_edge[i].endpoint1;
           temp.endpoint2 = MST_edge[i].endpoint2;
           temp.weight = MST_edge[i].weight;
           while(n >= 0 && MST_edge[n].weight > temp.weight)
           {
                   MST_edge[n+1].endpoint1 = MST_edge[n].endpoint1;
                   MST_edge[n+1].endpoint2 = MST_edge[n].endpoint2;
                   MST_edge[n+1].weight = MST_edge[n].weight;
                   n--;
           }
           MST_edge[n+1].endpoint1 = temp.endpoint1;
           MST_edge[n+1].endpoint2 = temp.endpoint2;
           MST_edge[n+1].weight = temp.weight;
     }
     for(i = 0 ; i < vertex-1 ; i++) printf("(%d,%d) = %d\n",MST_edge[i].endpoint1,MST_edge[i].endpoint2,MST_edge[i].weight);
}
int main()
{
    int **graph,**MST,vertex,i,j;
    char filename[128];
    FILE *fprt;
    
    printf("Please input file name: ");
    scanf("%s",filename);
    
    fprt = fopen(filename,"r");
    fscanf(fprt,"%d",&vertex);
    
    graph = (int **) malloc(vertex*sizeof(int*));
    for(i = 0 ; i < vertex ; i++) graph[i] = (int *) malloc(vertex*sizeof(int));
    
    for(i = 0 ; i < vertex ; i++)
          for(j = 0 ; j < vertex ; j++) fscanf(fprt,"%d",&graph[i][j]);
                
    
    MST = (int **) malloc(vertex*sizeof(int*));
    for(i = 0 ; i < vertex ; i++) MST[i] = (int *) malloc(vertex*sizeof(int));
    for(i = 0 ; i < vertex ; i++)
          for(j = 0 ; j < vertex ; j++) MST[i][j] = 0;
    
    Sollin_MST(graph,vertex,MST);
    List_MST_edge(MST,vertex);
    
    fclose(fprt);
    free(graph);
    free(MST);
    
    system("pause");
    return 0;
}
