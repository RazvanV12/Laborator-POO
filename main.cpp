#include <iostream>
#include <vector>
using namespace std;

// Tema 3 Velciu Razvan Gabriel Grupa 133

class Vector
{
private:
    int n;
    vector<int> v;
    int x;
public:
    int getN()
    {
        return n;
    }
    vector<int> getVector()
    {
        return v;
    }
    int getX()
    {
        return x;
    }
    void setN(int n_)
    {
        n = n_;
    }
    void setVector(vector<int> v_)
    {
        v = v_;
    }
    void setX(int x_)
    {
        x = x_;
    }
    Vector(int n_, vector<int> v_, int x_)
    {
        this->n = n_;
        this->v = v_;
        this->x = x_;
        for( int i=0 ; i<n; i++)
            v.push_back(x);
    }

    Vector( Vector &obj)
    {
        n = obj.n;
        v = obj.v;
    }

    ~Vector()
    {
        v.clear();
    }

    Vector &operator=(Vector &obj)
    {
        n =obj.n;
        v =obj.v;
    }

    int Suma( Vector &obj)
    {
        int s = 0;
        for ( int i=0; i<v.size(); i++)
        {
            s = s + v[i];
        }
        return s;
    }

    void reactualizare (int n, int x)
    {
        this->n = n;
        for(int i= 0; i<n; i++)
            v.push_back(x);
    }

    void max_pozitie (Vector &obj, int &max, int &index)
    {
        index = 0;
        max = v[0];
        for (int i=1; i<v.size(); i++)
            if (v[i] > max)
            {
                max = v[i];
                index = i;
            }
    }

    void Sortare( Vector &obj)
    {
        int aux;
        for ( int i=0; i<v.size(); i++)
            for( int j=i+1 ; j< v.size(); j++)
                if (v[i] > v[j])
                {
                    v[i] = aux;
                    v[i] = v[j];
                    v[j] = aux;
                }
    }

    void afisare( Vector &obj)
    {
        for (int i=0; i<n; i++)
            cout<< v[i]<< " ";
        cout<<"\n";
    }

};

int main()
{
    int n=3;
    vector<int> v;
    Vector obj(n, v, 2);

    return 0;
}