//This implements segment tree. source: topcoder tutorials.
//https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/#Segment_Trees
#include<cstdio>
using namespace std;
const int MAXN=200000, MAXIND=4*MAXN;
int Segtree[MAXIND], Array[MAXN]={0};   //Array and Segtree will follow  0-based and 1-based indexing respectively.
//Below is an implementation of segment tree for RMQ.
//Elements of the segment tree contain the index of the min element of the array.

//initializes elements of Segtree with -1.
void init(void)
{ for(int i=0; i<MAXIND; i++)
    Segtree[i]=-1;
}

//initializes Segtree from Array.
void initialize(int node, int b, int e, int N)
{ if (b == e)
    Segtree[node] = b;
  else
  { //compute the values in the left and right subtrees
    initialize(2*node,      b,            (b+e)/2,  N);
    initialize(2*node + 1,  (b+e)/2 + 1,  e,        N);
    //search for the minimum value in the first and
    //second half of the interval
    if (Array[Segtree[2*node]] <= Array[Segtree[2*node + 1]])
      Segtree[node] = Segtree[2*node];
    else
      Segtree[node] = Segtree[2*node + 1];
  }
}

//Returns the index of the smallest element in the given range [b, e].
int query(int node, int b, int e, int i, int j)
{
  int p1, p2;
  //if the current interval doesn't intersect
  //the query interval return -1
  if (i > e || j < b)
    return -1;

  //if the current interval is included in
  //the query interval return Segtree[node]
  if (b >= i && e <= j)
    return Segtree[node];

  //compute the minimum position in the
  //left and right part of the interval
  p1 = query(2*node,      b,            (b+e)/2,  i, j);
  p2 = query(2*node + 1,  (b+e)/2 + 1,  e,        i, j);

  //return the position where the overall
  //minimum is
  if (p1 == -1)
    return Segtree[node] = p2;
  if (p2 == -1)
    return Segtree[node] = p1;
  if (A[p1] <= A[p2])
    return Segtree[node] = p1;
  return Segtree[node] = p2;
}



int main(void)
{ init();
  int N;
  cin>>N;
  for(int i=0; i<N; i++)
  { cin>>Array[i];
  }
  initialize(1, 0, N-1, N);
  return 0;
}
