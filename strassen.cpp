#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll pow2[50] = {1};


inline bool ispow2(ll a)
{
    for(ll i = 0; i < 50; i++)
    {
        if(pow2[i] == a) return true;
    }
    return false;
}

inline ll nearpow2(ll a)
{
    for(ll i = 0; i < 50; i++)
    {
        if(pow2[i] >= a) return i;
    }
    return 49;
}

inline void filler(vector<vll>& a)
{
    vll row;
    if(ispow2(a[0].size()) && ispow2(a.size())) return;
    ll asize = a.size(), a0size = a[0].size();
    ll limitd = pow2[nearpow2(a0size)] - a0size, limita = pow2[nearpow2(asize)] - asize;
    for(ll i = 0; i < asize; i++)
    {
        for(ll j = 0; j < limitd; j++)
        {
            a[i].push_back(0);
        }
    }
    for(ll i = 0; i < pow2[nearpow2(a0size)]; i++)
    {
        row.push_back(0);
    }
    for(ll i = 0; i < limita; i++)
    {
        a.push_back(row);
    }
    return;
}

inline vector<vector<vll> > matrix4(vector<vll>& a)
{
    vector<vector<vll> > ans;
    vector<vll> a1,a2,a3,a4;
    vll row;
    ll asize = a.size()/2, i = 0, j = 0;
    for(i = 0; i < asize; i++)
    {
        row.clear();
        for(j = 0; j < asize; j++)
        {
            row.push_back(a[i][j]);
        }
        a1.push_back(row);
    }
    for(i = asize; i < a.size(); i++)
    {
        row.clear();
        for(j = 0; j < asize; j++)
        {
            row.push_back(a[i][j]);
        }
        a2.push_back(row);
    }
    for(i = 0; i < asize; i++)
    {
        row.clear();
        for(j = asize; j < a.size(); j++)
        {
            row.push_back(a[i][j]);
        }
        a3.push_back(row);
    }
    for(i = asize; i < a.size(); i++)
    {
        row.clear();
        for(ll j = asize; j < a.size(); j++)
        {
            row.push_back(a[i][j]);
        }
        a4.push_back(row);
    }
    ans.push_back(a1); ans.push_back(a2); ans.push_back(a3); ans.push_back(a4);
    return ans;
}

vector<vll> operator+(vector<vll>& a, vector<vll>& b)
{
    vector<vll> c(a.size(),vll(a[0].size(), 0));
    for(ll i = 0; i < a.size(); i++)
    {
        for(ll j = 0; j < a[0].size(); j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

vector<vll> operator-(vector<vll>& a, vector<vll>& b)
{
    vector<vll> c(a.size(),vll(a[0].size(), 0));
    for(ll i = 0; i < a.size(); i++)
    {
        for(ll j = 0; j < a[i].size(); j++)
        {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

ostream &operator<<(ostream &output, const vector<vll>& a)
{
    for(ll i = 0; i < a.size(); i++)
    {
        for(ll j = 0; j < a[0].size(); j++)
        {
            output << a[i][j] << " ";
        }
        output<<endl;
    }
    return output;
}

vector<vll> join(vector<vector<vll> >& a)
{
    vector<vll> c(a[0].size()*2,vll(a[0].size()*2, 0));
    ll asize = a[0].size(), i = 0, j = 0;
    for(i = 0; i < a[0].size(); i++)
    {
        for(j = 0; j < a[0][0].size(); j++)
        {
            c[i][j] = a[0][i][j];
        }
    }
    for(i = asize; i < 2*asize; i++)
    {
        for(j = 0; j < asize; j++)
        {
            c[i][j] = a[1][i%asize][j];
        }
    }
    for(i = 0; i < asize; i++)
    {
        for(j = asize; j < 2*asize; j++)
        {
            c[i][j] = a[2][i][j%asize];
        }
    }
    for(i = asize; i < 2*asize;i++)
    {
        for(j = asize; j < 2*asize; j++)
        {
            c[i][j] = a[3][i%asize][j%asize];
        }
    }
    return c;
}

void cut(vector<vll>& a, ll n)
{
    ll diff = a.size()-n;
    for(ll i = 0; i < diff; i++) a.pop_back();
    for(ll i = 0; i < n; i++)
    {
        for(ll j = 0; j < diff; j++)
        {
            a[i].pop_back();
        }
    }
    return;
}

vector<vll> strassen(vector<vll>& a, vector<vll>& b)
{
    vector<vll> c, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
    vector<vll> p1,p2,p3,p4,p5,p6,p7;
    filler(a);filler(b);
    //cout<<a<<endl;
    vector<vector<vll> > a1 = matrix4(a),b1 = matrix4(b),c1 = a1;
    if(a.size() == 1)
    {
        c.resize(1,vll(1,0));
        c[0][0] = a[0][0]*b[0][0];
        return c;
    }
    s1 = b1[2] - b1[3];
    s2 = a1[0] + a1[2];
    s3 = a1[1] + a1[3];
    s4 = b1[1] - b1[0];
    s5 = a1[0] + a1[3];
    s6 = b1[0] + b1[3];
    s7 = a1[2] - a1[3];
    s8 = b1[1] + b1[3];
    s9 = a1[0] - a1[1];
    s10 = b1[0] + b1[2];
    p1 = strassen(a1[0],s1);
    p2 = strassen(s2,b1[3]);
    p3 = strassen(s3,b1[0]);
    p4 = strassen(a1[3],s4);
    p5 = strassen(s5, s6);
    p6 = strassen(s7, s8);
    p7 = strassen(s9, s10);
    c1[0] = p5 + p4; //- p2 + p6;
    c1[0] = c1[0] + p6;
    c1[0] = c1[0] - p2;
    c1[2] = p1 + p2;
    c1[1] = p3 + p4;
    c1[3] = p5 + p1; // - p3 + p7;
    c1[3] = c1[3] - p3;
    c1[3] = c1[3] - p7;
    return join(c1);
}



int main()
{
    for(ll i = 1; i < 50; i++)
    {
        pow2[i] = pow2[i-1]*2;
    }
    vll row;
    vector<vll> a, b, c;
    ll n, dato;
    cin>>n;
    c.resize(n,vll(n,0));
    cout<<"A"<<endl;
    for(ll i = 0; i < n; i++)
    {
        row.clear();
        for(ll j = 0; j < n; j++)
        {
            cin>>dato;
            row.push_back(dato);
        }
        a.push_back(row);
    }
    cout<<"B"<<endl;
    for(ll i = 0; i < n; i++)
    {
        row.clear();
        for(ll j = 0; j < n; j++)
        {
            cin>>dato;
            row.push_back(dato);
        }
        b.push_back(row);
    }
    c = strassen(a,b);
    cut(c,n);
    cout<<c<<endl;
    /*c = a-b;
    cout<<c<<endl;
    vector<vector<vll> > c1 = matrix4(c);
    for(ll i = 0; i < c1.size(); i++)
    {
        cout<<c1[i]<<endl;
    }
    vector<vll> d = join(c1);
    cout<<d<<endl;*/
    return 0;
}