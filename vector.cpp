#include <iostream>
#include <vector>

using namespace std;

template<class T> class vectors
{   private:
        int dim;
        vector<T> Vec;
    public:
        T mod()
        {   T ans=0;
            for(int i=0; i<this->dim; i++)
                ans += this.Vec[i]*this.Vec[i];
            return ans;
        }
        vectors<T>(vector<T> x)
        {   Vec = x;
            dim = x.size();
        }
        vectors<T>()
        {   dim=0;
            Vec.clear();
        }
        vectors operator+(vectors<T> V)     //Use of operator + to add two vectors.
        {   if(V.dim != this->dim)
            {   cerr<<"Size of vectors is not same. can't add.";
                return vectors<T>();
            }
            else
            {
                vector<T> ans = V.Vec;
                for(int i=0; i<this->dim; i++)
                    ans[i] += this->Vec[i];
                return ans;
            }
        }
        vectors add(vectors<T> V)           //Add function to add two vectors.
        {   return V+(*this);
        }
        friend ostream& operator<<(ostream& os, vectors<T> V)   //This prints current vector to ostream.
        {   for(int i=0; i<V.dim; i++)
                os<<V.Vec[i]<<' ';
            os<<endl;
            return os;
        }
        T dot(vectors<T> V)
        {   if(V.dim != this->dim)
            {   cerr<<"Size of vectors is not same. can't dot multiply.";
                return 0;
            }
            else
            {   T ans=0;
                for(int i=0; i<V.dim; i++)
                    ans += V.Vec[i]*(this->Vec[i]);
                return ans;
            }
        }
        vectors<T> cross(vectors<T> V)
        {   if(V.dim != this->dim || V.dim>3)
            {   cerr<<"Not possible.";
                return vectors();
            }
            else if(V.dim == 2)
            {   T product = this->Vec[0]*V.Vec[1] - this->Vec[1]*V.Vec[0];
                return vectors( {0, 0, product} );
            }
            else
            {   T x = this->Vec[1]*V.Vec[2] - this->Vec[2]*V.Vec[1];
                T y = this->Vec[0]*V.Vec[2] - this->Vec[2]*V.Vec[0];
                T z = this->Vec[0]*V.Vec[1] - this->Vec[1]*V.Vec[0];
                return vectors( {x, -y, z} );
            }
        }
};

int main()
{   vector<double> first={1, 2}, second={3,1};
    vectors<double> p(first), q(second);
    //p = p + q;
    cout<<p;
    cout<<p.dot(q)<<'\n';
    cout<<p.cross(q);
    return 0;
}
