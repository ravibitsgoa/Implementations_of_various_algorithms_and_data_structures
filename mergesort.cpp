#include<iostream>
using namespace std;
//This mergesort function takes as an argument, the starting iterator and the end iterator.
//time-complexity: O(NlogN)

long long inversions=0;

template <class T>
void mergesort(T *start, T *end)
{ 	size_t l=end-start;
	if(l>1)
	{ 	T* mid = start + l/2;
		mergesort(start, mid);
		mergesort(mid, end);
		T z[l];
		for(size_t k=0, a=0, b=0; k<l; k++)
		{ 	//a and b are the indices of the first and second halves resp, k is overall index.
			if(a<l/2 && *(start+a)< *(start+ ((l/2)+b)) )
			{ 	z[k]=*(start + a); a++;
			}
			else if(b<l-(l/2))
			{ 	z[k]=*(start + (l/2 + b)); b++;
				if(a<l/2) inversions+=l/2 - a;
			}
			else
			{ 	z[k]=*(start + a); a++;
			}
		}
		for(size_t k=0; k<l; k++)
		{ 	*(start+k)=z[k];//copying. the linear work.
		}
	}
	else {}//base case: already sorted.
}

int main()
{ 	int x[10]={9,8,7,6,5,4,3,2,1,0};
	mergesort(x, x+10);
	for(int i=0; i<10; i++)
		cout<<x[i]<<' ';
	cout<<endl;
	cout<<"Number of inversions = "<<inversions<<endl;
	return 0;
}
//completed on 10th Dec 2016, 6:15 PM
