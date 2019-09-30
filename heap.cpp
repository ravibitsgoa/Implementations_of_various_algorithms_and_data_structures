#include<cstdio>

class heap
{
private:
    int size;
    vector<int> values;

public:
    heap(int sz)
    {   size=sz;
        values.resize(sz);
    }

    int search(int x)
    {   int i=1;
        if(size==0)
            return -1;
        while(x!=values[i])
        {   if(x>values[i])
            {   i*=2;
                i++;
            }
            else
                i*=2;
            if(i>=size)
                return -1;
        }
        if(x==values[i])
            return i;
        else
            return -1;
    }

    int select(int x)
    {

    }

    int min()
    {   return values[1];
    }

    int pred(int x);
    int rank(int x);
    void print();
    void insert(int x);
    void delete(int x);

};

int main()
{
    return 0;
}
-
