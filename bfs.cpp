/*This implements breadth first search in a sparse graph in an adjancy list representation
time-complexity: O(m+n)*/
#include<cstdio>
#include<queue>
#include<cassert>
//#define V 6
using namespace std;

int main(void)
{
  int V;
  printf("Enter number of verticies :\t");
  scanf("%d",&V);

  int graph[V+1][V+1]={0};
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
  printf("\nEnter start vertex (between 1 and %d) for BFS :\t", V);
  scanf("%d",&start);
  assert(start>=1 && start<=V);

  int explored[V+1]={0};    //All nodes are initially unexplored.
  explored[start]=1;        //Mark start vertex as explored.

  queue<int> Q;             //Insert starting node in the queue.
  Q.push(start);

  int depth[V+1]={0};       //Starting node is in layer 0.
  depth[start]=0;

  while(!Q.empty())         //Until Q is non-empty, explore the top node.
  { int i=Q.front();
    //printf("%d ",i);
    Q.pop();
    for(int x: graph[i])    //Explore all nodes adjacent to current node.
    { if(x==0)
        break;
      if(!explored[x])      //If x node has not been explored yet, insert it into the queue.
      { explored[x]=1;
        Q.push(x);
        //printf("%d\n",x);
        depth[x]=depth[i]+1;
      }
    }
  }
  for(int i=1; i<=V; i++)         //Auxilary.
    printf("%d %d\n",i,depth[i]); //depth[i] denotes number of "layer" of i.
  return 0;
}
