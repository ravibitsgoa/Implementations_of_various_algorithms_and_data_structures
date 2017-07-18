/*  This implements Karger's min cut finding algorithm in a graph, with union find data structure.
This runs the algorithm V^2 times, to ensure that probability of success is at least 1/e.
V is number of verticies and E is number of edges.
*/
#include<unordered_set>
#include<random>
#include<cstdio>
#include<unordered_map>
#include<cassert>
#include<utility>
using namespace std;
#define V 200
#define E 3000
int ver[V+1]={0};
unordered_map<int, unordered_multiset<int> > inp;

int mincut(int n)
{ random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, V); //Initialization of randomness.
  while(n>2)
  { //Selecting two verticies, uniformly at random, for merging.
    int x = dis(gen);
    int y = dis(gen);
    while(ver[x]==0)
      {x=dis(gen)%(V+1);} //printf("%d ",x);
    while(ver[y]==0 || y==x || inp[x].find(y)==inp[x].end())
      {y=dis(gen)%(V+1);} //printf("%d\n",y);

    if(inp[x].size() <= inp[y].size())           //Now, x has strictly bigger degree than y.
      swap(x, y);

    inp[x].insert(inp[y].begin(), inp[y].end()); //merging the two lists.

    //Joining x with all verticies adjacent to y, and breaking their edges with y.
    for(auto iter=inp[y].begin(); iter!=inp[y].end(); iter++)
    { if(*iter == x)
        continue;
      inp[*iter].insert(x);                     //This is correct because inp[y].count(*iter) == inp[*iter].count(y).
      inp[*iter].erase(inp[*iter].find(y));     //Removing all edges with y, from all of its adjacent verticies.
    }

    auto it=inp[x].find(x);                     //Removing self loops.
    while(it!=inp[x].end())
    { inp[x].erase(it);
      it=inp[x].find(x);
    }
    it=inp[x].find(y);
    while(it!=inp[x].end())
    { inp[x].erase(it);
      it=inp[x].find(y);
    }

    ver[y]=0; n--;                              //removed vertex y.
    //inp.erase(inp.find(y));                   //Not really required.
  }
  int i=1, ans=0;                               //Finding the first vertex that is remaining.
  for(; i<(V+1); i++)
  { if(ver[i]) break;
  }
  ans=inp[i].size();
  for(i++; i<(V+1); i++)                        //Finding the second vertex that is remaining.
  { if(ver[i]) break;
  }
  assert(ans==inp[i].size());                   //If they don't have same degree, something has gone wrong.
  return ans;
}

int main()
{ unordered_map<int, unordered_multiset<int> > original_input;
                                          //Input has to be in this format: 1 v1 v2 ... vk 0
                                          //                                2 v1 v2 ... vk 0
  for(int i=1; i<=V; i++)
  { int x;
    scanf("%d",&x);
    assert(x==i);
    for(int j=1; j<=V; j++)
    { int x;
      scanf("%d", &x);
      if(x==0)  {break;}
      else      {original_input[i].insert(x);}
    }
  }                                         //inputted into the master copy.
  int ans=E;                                //min cut can't have more than E edges!
  for(int a=0; a<V*V; a++)                  //To run Karger's algorithm V^2 times.
  { inp= original_input;                    //copying the input.
    for(int i=1; i<=V; i++) ver[i]=1;       //All verticies are initially separate.
    int n=V, x;                             //Number of verticies is initially V.
    x=mincut(n);                            //answer of this random iteration is x.
    //printf("\n%d\n",x);
    ans=min(ans, x);
  }
  printf("%d",ans);
  return 0;
}
