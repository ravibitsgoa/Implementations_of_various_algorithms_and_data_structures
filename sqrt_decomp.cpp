//answers range sum queries [l, r] in time O(sqrt(N)), using auxilary array of prefix sums.
#include <iostream>
#include <cmath>
using namespace std;
struct segment
{
	int l, r;
	long long sum=0;
};

int main()
{
	int n;
	cin>>n;
	int arr[n];
	for(int i=0; i<n; i++)
		cin>>arr[i];
	int size= sqrt(n);
	segment segments[size+5]={0};
	int segment_index=0, segment_size=0;
	segments[0].l = segments[0].r = segments[0].sum = 0;
	for(int i=0; i<n; i++)
	{
		segments[segment_index].r = i;
		segments[segment_index].sum += arr[i];
		//add ith element to segment_index'th segment.
		segment_size++;
		if(segment_size >= size)
		{	segment_index++;
			segment_size=0;
			segments[segment_index].l = i+1;
			segments[segment_index].r = i+1;
			segments[segment_index].sum = 0;
		}
	}
	segment_index++;
	
	int queries=0;
	cin>>queries;
	while(queries--)
	{
		int l, r;
		cin>>l>>r;
		long long sum=0;
		for(int i=0; i<segment_index; i++)
		{
			//if the segment totally falls within the query range.
			if(segments[i].l >= l && segments[i].r <= r)
				sum+= segments[i].sum;
			//if segment partially overlaps with the query range 
			//or query is totally inside this segment.
			else if(segments[i].l <= l || segments[i].r >= r)
			{
				int l_limit = max(l, segments[i].l), r_limit = min(r, segments[i].r);
				for(int j=l_limit; j<=r_limit; j++)
					sum+= arr[j];
			}
		}
		cout << sum << '\n';
	}
	
}