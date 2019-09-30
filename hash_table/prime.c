#define false 0
#define true 1

long long max(long long x, long long y)
{
	return ((x>=y)? x : y);
}

int is_prime(const long long x) 
{
	if(x%2 == 0)
		return false;
		
	for(long long i=3; i*i <=x; i+=2)
	{
		if(x%i == 0)
			return false;
	}
	return true;
}

long long next_prime(long long x) 
{
	long long i = max(x, 50);
	while(!is_prime(i))
	{	i++;
	}
	return i;
}
