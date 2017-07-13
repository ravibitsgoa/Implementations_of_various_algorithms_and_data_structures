//Solution to a spoj question and a topic taught in the Coursera course.
//This is yet to be debugged.
#include<cstdio>
#include<utility>
#include<cmath>
#include<vector>
#include<map>
#include<algorithm>

#define xx first
#define yy second
using namespace std;

const int MAXPOINTS=50005;
const double EPS = 1e-9;
const double INF = 1e+10;
typedef pair<double, double> point;

point P[MAXPOINTS]={};//Global unsorted array of points.

double dist(point p1, point p2)
{ double ans=((p1.xx - p2.xx)*(p1.xx - p2.xx)) + ((p1.yy - p2.yy)*(p1.yy - p2.yy));
  return sqrt(ans);
}

pair<int, int> closest_split_pair(const int *Px, const int *Py, double delta, const int l)
{ pair<int, int> bestPair={INF, INF};
  double xbar=P[Px[l/2 - 1]].xx;
  int Sy[l], Sysize=0;
  for(int i=0; i<l; i++)
  { if((P[Py[i]].xx >= (xbar - delta)) && (P[Py[i]].xx <= (xbar + delta)) )
    { Sy[Sysize++]=Py[i];
    }
  }
  for(int i=0; i<Sysize-7; i++)
  { for(int j=1; j<=7; j++)
    { if(dist(P[Sy[i]], P[Sy[i+j]]) < delta)
      { delta= dist(P[Sy[i]], P[Sy[i+j]]);
        bestPair={Sy[i], Sy[i+j]};
      }
    }
  }
  return bestPair;
}

pair<int, int> closest_pair(const int *Px, const int *Py, int l)//Arguments: an array of indices of points sorted by x and y co-ords and length of the array.
{ if(l==2)
    return {Px[0], Px[1]};
  if(l==3)
  { point p1=P[Px[0]], p2=P[Px[1]], p3=P[Px[2]];
    double d1=dist(p1, p2), d2=dist(p2, p3), d3=dist(p1, p3);
    if(d1<= d2 && d1<= d3)      return {Px[0], Px[1]};
    else if(d2<= d1 && d2<= d3) return {Px[1], Px[2]};
    else                        return {Px[0], Px[2]};
  }
  int *Qx=(int*)malloc(sizeof(int)*(l/2)), *Qy=(int*)malloc(sizeof(int)*l/2);//Contains points of first half of Px sorted by x and y coordinates resp.
  int chhe[l]={0};
  for(int i=0; i<l/2; i++)
  { Qx[i]=Px[i];
    chhe[Px[i]]=1;
  }
  for(int i=0, j=0; i<l && j<l/2; i++)
  { if(chhe[Py[i]])
      Qy[j++]=Py[i];
  }
  //Copied indices of points from P to Q.

  pair<int, int> p1;
  p1=closest_pair(Qx, Qy, l/2);
  free((void*)Qx);
  free((void*)Qy);

  int *Rx=(int*)malloc(sizeof(int)*(l-l/2)), *Ry=(int*)malloc(sizeof(int)*(l-l/2));
  for(int i=l/2; i<l; i++)
  { Rx[i-l/2]=Px[i];
  }
  for(int i=0, j=0; i<l && j<l/2; i++)
  { if(!chhe[Py[i]])  //Complementary of those taken in Qy.
      Ry[j++]=Py[i];
  }
  //Copied indices of points from P to R.
  pair<int, int> p2, p3, dummy={INF, INF};
  p2=closest_pair(Rx, Ry, l-l/2);
  free((void*)Rx);
  free((void*)Ry);
  double d1=dist(P[p1.first], P[p1.second]), d2=dist(P[p2.first], P[p2.second]);
  double delta=min(d1, d2);
  p3=closest_split_pair(Px, Py, delta, l);
  double d3=+INF;
  if(p3!=dummy)
    d3=dist(P[p3.first], P[p3.second]);
  if(d1<= d2 && d1<= d3)      return p1;
  else if(d2<= d1 && d2<= d3) return p2;
  else                        return p3;
}

bool sortByYCorrdinate(point a, point b)
{ if(a.yy<b.yy || (abs(a.yy-b.yy)<EPS && a.xx<b.yy)) return true;
  return false;
}

int main()
{ int N;
  scanf("%d",&N);
  for(int i=0; i<N; i++)
  { int x, y;
    scanf("%d %d",&x,&y);
    P[i]={x,y};
  }
  map<point, int> indices;//map from points to original indices.

  for(int i=0; i<N; i++)
    indices[P[i]]=i;

  vector<point> Pcopy(P, P+N);
  sort(Pcopy.begin(), Pcopy.end());//sort by x coordinate.

  int px[N];
  for(int i=0; i<N; i++)
  { px[i]=indices[Pcopy[i]];//px's ith element stores the original index of ith point when sorted by x co-ord.
  }
  sort(Pcopy.begin(), Pcopy.end(), sortByYCorrdinate);//sort by y coordinate.
  int py[N];
  for(int i=0; i<N; i++)
  { py[i]=indices[Pcopy[i]];//px's ith element stores the original index of ith point when sorted by x co-ord.
  }
  pair<int, int> p= closest_pair(px, py, N);
  if(p.first > p.second)
    swap(p.first, p.second);
  printf("%d %d %.6f", p.first, p.second, dist(P[p.first], P[p.second]));
  return 0;
}
