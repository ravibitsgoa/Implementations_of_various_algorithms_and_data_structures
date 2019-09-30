/*This implements randomized quicksort that works in place, and in time theta (NlogN),
and randomized ith order statistic selection algorithm Rselect in time theta (N) */
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
int N;
const int NMAX=10000;
int x[NMAX];


template <typename T>
void quicksort(T *pbegin, T *pend)
{ int len=pend - pbegin;
  if(len>1)
  {                                         //choosing pivot:
    int pivot_pos=rand()%len;
    T pivot=*(pbegin + pivot_pos);          //pivot_pos'th element is chosen.
    int i=1;
    swap(*(pbegin + pivot_pos), *pbegin);   //Swapping the pivot to the 1st position.
    //cout<<pivot<<endl;
                                            //partitioning:
    for(int j=1; j<len && i<len; j++)
    { if(*(pbegin + j) <= pivot)            //Moving all elements less than the pivot to the left part.
      { swap(*(pbegin +j), *(pbegin +i));
        i++;
      }
    }
    swap(*pbegin, *(pbegin + i-1));         //moving the pivot to its correct position.
    quicksort(pbegin, pbegin + i-1);        //Only elements less than pivot need to be sorted.
    quicksort(pbegin+i, pend);              //And those bigger than pivot.
  }
  else {}                                   //base case: already sorted.
}

template <typename T>
T Rselect(T *pbegin, T *pend, int k)     //This finds kth order statistic from the given array.
{ int len=pend - pbegin;
  if(len>1)
  {                                         //choosing pivot:
    int pivot_pos=rand()%len;
    T pivot=*(pbegin + pivot_pos);          //pivot_pos'th element is chosen.
    int i=1;
    swap(*(pbegin + pivot_pos), *pbegin);   //Swapping the pivot to the 1st position.
    //cout<<pivot<<endl;
                                            //partitioning:
    for(int j=1; j<len && i<len; j++)
    { if(*(pbegin + j) <= pivot)            //Moving all elements less than the pivot to the left part.
      { swap(*(pbegin +j), *(pbegin +i));
        i++;
      }
    }
    swap(*pbegin, *(pbegin + i-1));         //moving the pivot to its correct position.
    if(k == i-1)                            //If we are looking for i-1th element, we have found it.
      return *(pbegin + i-1);
    else if(k < i-1)
      Rselect(pbegin, pbegin + i-1, k);     //Only elements less than pivot need to be checked.
    else
      Rselect(pbegin+i, pend, k-i+1);     //Only those bigger than pivot have to be checked in this case.
  }
  else {return *pbegin;}                    //base case: must be ith statistic.
}


int main()
{ cin>>N;
  for(int i=0; i<N; i++)
    cin>>x[i];
  time_t t;
  srand((unsigned) time(&t));               //To introduce randomization from system time.
  int k;
  cout<<"Enter k (between 1 and "<<N<<") for kth order statistic\t: ";
  cin>>k;
  cout<<Rselect(x, x+N, k-1)<<endl;         //To make it zero based indexed.

  quicksort(x, x+N);
  for(int i=0; i<N; i++)
    cout<<x[i]<<' ';
  return 0;
}
