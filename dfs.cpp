/*This implements depth first search and topological in a graph in an adjancy list representation
time-complexity: O(m+n)*/
#include<cstdio>
#include<cassert>
#define VMAX 100
using namespace std;

int graph[VMAX+1][VMAX+1]={0};
int explored[VMAX+1]={0};     //All nodes are initially unexplored.
int currentLabel=0;
int Label[VMAX+1]={0};        //topological ordering of nodes.

void DFS(int s) //start vertex s.
{ explored[s]=1;
  for(int x: graph[s])
  { if(!explored[x])
      DFS(x);
  }
  Label[s]=currentLabel;
  currentLabel--;
}

int main(void)
{
  int V;
  printf("Enter number of verticies (at most %d) :\t",VMAX);
  scanf("%d",&V);
  assert(V>=1 && V<=VMAX);
  //Input has to be in this format: 1 v1 v2 ... vk 0
  //                                2 v1 v2 ... vk 0
  for(int i=1; i<=V; i++)
  { int x;
    scanf("%d",&x);
    assert(x==i);
    for(int j=0; j<V; j++)
    { int x;
      scanf("%d", &x);
      if(x==0)  {break;}
      else      {graph[i][j]=x;}
    }
  }

  int start;
  printf("\nEnter start vertex (between 1 and %d) for DFS :\t", V);
  scanf("%d",&start);
  assert(start>=1 && start<=V);

  currentLabel=V+1;               //Initialize current label to V for topological sorting.

  DFS(start);                     //Start DFS from this vertex.
  for(int i=1; i<=V; i++)         //Prints topological ordering of the graph.
    printf("%d %d\n",i,Label[i]);
  return 0;
}
