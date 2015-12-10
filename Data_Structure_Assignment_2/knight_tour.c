#include <stdio.h>
#include <stdlib.h>

int ktmovev[8] = {-2,-1,1,2,2,1,-1,-2},ktmoveh[8] = {1,2,2,1,-1,-2,-2,-1};
int chessboard[8][8]={};

void chessboardPrint()
{
     int i,j;
     
     for(i = 0 ; i < 8 ; i++)
     {
           for(j = 0 ; j < 8 ; j++) printf("%d\t",chessboard[i][j]);
           printf("\n");
     }
}
int Listnpos(int starti,int startj,int *nexti,int *nextj)
{
    int i,npos = 0;
    
    for(i = 0; i < 8 ; i++)
    {
          if( starti+ktmovev[i] >= 0 && starti+ktmovev[i] <= 7 && startj+ktmoveh[i] >= 0 && startj+ktmoveh[i] <= 7)
              if( !chessboard[starti+ktmovev[i]][startj+ktmoveh[i]])
              {
                  nexti[npos] = starti + ktmovev[i];
                  nextj[npos] = startj + ktmoveh[i];
                  npos++;
              }
    }
    
    return npos;
}
int Findnextsquare(int *nexti,int *nextj,int npos)
{
    int i,j,exit[npos],min;
    
    for(i = 0 ; i < npos ; i++)
    {
          exit[i] = 0;
          for(j = 0; j < 8 ; j++)
          {
                if( nexti[i]+ktmovev[j] >= 0 && nexti[i]+ktmovev[j] <= 7 && nextj[i]+ktmoveh[j] >= 0 && nextj[i]+ktmoveh[j] <= 7)
                    if( !chessboard[nexti[i]+ktmovev[j]][nextj[i]+ktmoveh[j]])
                        exit[i]++;
          }
    }
    //for(i = 0 ; i < npos ; i++) printf("%d %d %d\n",exit[i],nexti[i],nextj[i]);
    min = npos-1;
    for(i = npos-2 ; i >= 0 ; i--) 
          if(exit[i] <= exit[min]) min = i;
    
    return min;
}
int main()
{
    int starti,startj;
    int npos,nexti[8],nextj[8],min,count = 2;
    
    scanf("%d %d",&starti,&startj);
    chessboard[starti][startj] = 1;
    
    /*printf("%d\n",(npos=Listnpos(starti,startj,nexti,nextj)));
    int i;
    for(i = 0 ; i < npos ; i++) printf("%d %d\n",nexti[i],nextj[i]);
    */
    while((npos = Listnpos(starti,startj,nexti,nextj)))
    {
           if(npos == 1)
           {
                   min = 0;
                   starti = nexti[min];
                   startj = nextj[min];
                   chessboard[starti][startj] = count++;
           }
           else
           {
               min = Findnextsquare(nexti,nextj,npos);
               starti = nexti[min];
               startj = nextj[min];
               chessboard[starti][startj] = count++;
           }
           /*chessboardPrint();
           system("pause");*/
    }
    
    if(count < 64) printf("Failed!\nUsing step: %d\nFinal position: (%d,%d)\n",count,starti,startj);
    else printf("Succeeded!\nFinal position: (%d,%d)\n",starti,startj);
    chessboardPrint();
    
    system("pause");
    return 0;
}
