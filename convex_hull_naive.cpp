#include <vector>
#include <iostream>
//TODO: debug.
using namespace std;

class point
{
public:
    double x, y;
public:
    point(double x, double y)
    {   this->x = x;
        this->y = y;
    }
    point()
    {   this->x = this->y = 0;
    }
    double cross(const point &p)
    {   double temp = (this->x) * (p.y);
        temp -= (this->y) * (p.x);
        return temp;
    }
    point diff(const point &p)
    {   point a(this->x - p.x, this->y - p.y);
        return a;
    }
    bool operator !=(point p)
    {   if(this->x == p.x && this->y == p.y)
            return 1;
        return 0;
    }
};

class convexHull : point
{
private:
    int size;
    vector<point> points;
public:
    convexHull(int x)
    {   size = x;
        points.resize(x);
    }
    convexHull(int x, vector<point> given)
    {   points = given;
        if(x!=given.size())
            cerr<<"invalid input";
        size = points.size();
    }
    convexHull()
    {   size=0;
    }
    void insert(point x)
    {   points.push_back(x);
    }
    vector<point> find()
    {   vector<point> cHull;
        point first = points[0];
        int index=0;

        //To find the first point of the hull, which will be the left (top) point.
        for(int i=1; i<size; i++)
        {   if(first.x > points[i].x)
            {   first = points[i];
                index=i;
            }
            else if(first.x == points[i].x && first.y < points[i].y)
            {   first = points[i];
                index=i;
            }
        }
        cHull.push_back(first);
        point prev=first;

        do
        {   int n = -1;
            for(int i = 0; i<size; i++)
            {
                //Don't go back to the same point you came from
                if(i == index) continue;
                //If there is no N yet, set it to i
                if(n == -1)
                {   n = i;
                }
                point temp = points[i].diff(prev);
                int cross = temp.cross( points[n].diff(prev) );
                if(cross < 0)
                {
                    //As described above, set N=X
                    n = i;
                }
            }
            prev = points[n];
            index = n;
            cHull.push_back(prev);
            //cout<<index<<'\n';
        } while(prev!=first);

        for(point p : cHull)
            cout<<p.x<<' '<<p.y<<'\n';
        return cHull;
    }
};

int main()
{
    point p1(0,0), p2(1,2), p3(2,3), p4(-1, 1), p5(2, 0);
    convexHull A(5);
    A.insert(p1);
    A.insert(p2);
    A.insert(p3);
    A.insert(p4);
    A.insert(p5);
    A.find();
    return 0;
}
