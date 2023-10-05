#include<bits/stdc++.h>

using namespace std;

long double eps = 1e-8;

class Mylong 
{
    public: 
    long double a;

    Mylong (long double _a)
    {
        a = _a;
    }
    Mylong ()
    {
        a = 0;
    }

    bool operator<(const Mylong & b) const{
        if(a < b.a - eps)
        {
            return true;
        }
        return false;
    }

    //  bool operator<(const Mylong double b){
    //     if(a < b.a - eps)
    //     {
    //         return true;
    //     }
    //     return false;
    // }

    bool operator==(Mylong  b){
        if(abs(a - b.a) < eps)
        {
            return true;
        }
        return false;
    }
    bool operator>(Mylong  b){
        if(a > b.a + eps)
        {
            return true;
        }
        return false;
    }
};


long long foo(long long a, long long b)
{
    a = abs(a);
    b = abs(b);

    if(a > b)
    {
        swap(a, b);
    }

    if(a == 0)
    {
        return b;
    }

    return foo(a, b % a);

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;

    long long sum = 0;

    map<pair<long long, long long>, map<Mylong , long long>> mp;
    map<pair<long long, long long>, long long> s;

    for(long long i = 0; i < n; ++i){
        long long t, a, b, c;
        Mylong  cc;

        cin >> t >> a >> b >> c;

        if(a == 0)
        {
            cc.a = c / (b + 0.0);
            b = 1;
        } else if(b == 0)
        {
            cc.a = c / (a + 0.0);
            a = 1;
        } else {
            long long k = foo(a, b);
            if(a < 0)
            {
                k *= -1;
            }

            a /= k;
            b /= k;
            cc.a = c / (k + 0.0);
        }

        if(t == 1)
        {
            long long q = 0;
            cin >> q;

            sum += q;

            mp[make_pair(a, b)][cc] += q;
            s[make_pair(a, b)] += q;
        } else {
            long long buf = mp[make_pair(a, b)][cc];
            if( buf != 0)
            {
                cout << "inf\n";
            }else {
                cout << sum - s[make_pair(a, b)] << '\n';
            }
        }

        // cout << a << ' ' << b << " " << cc.a << '\n';



    }



}