#include<bits/stdc++.h>

using namespace std;

const long double EPS = 1e-9;
struct dot
{
    long double x, y;

    dot(long double _x, long double _y)
    {
        x = _x;
        y = _y;
    }

    dot()
    {
        x = 0;
        y = 0;
    }

    dot operator+(dot o)
    {
        return dot(x + o.x, y + o.y);
    }
    dot operator-(dot o)
    {
        return dot(x - o.x, y - o.y);
    }
    dot operator*(long double k)
    {
        return dot(x*k, y*k);
    }
    long double operator*(dot o)
    {
        return x*o.x + y*o.y;
    }
    long double operator%(dot o)
    {
        return x*o.y - o.x*y;
    }

    bool is_keep(dot o)
    {
        return (*this - o)*(*this - o) < EPS;
    }

    long double len2()
    {
        return (*this) * (*this);
    }
    long double len()
    {
        return sqrt(len2());
    }
};

struct line
{
    dot O;
    dot napr;

    line(dot a, dot b)
    {
        O = a;
        napr = (b - a);

        napr = napr * (1 / napr.len());
    }

    line(dot x, line l)
    {
        O = x;
        napr.x = l.napr.y;
        napr.y = -l.napr.x;
        napr = napr * (1 / napr.len());
    }

    bool is_paral(line b)
    {
        return abs(b.napr % napr) < EPS;
        
    }

    dot cross(line b)
    {
        line a = *this;

        long double k = ((a.O - b.O) % a.napr) / (b.napr % a.napr);

        return b.O + b.napr*k;
    }

    dot proect(dot x)
    {
        line l(x, *this);

        return cross(l);
    }


    bool is_keep(dot o)
    {
        return abs((O - o) % napr) < EPS;
    }
};

int sign(long double a)
{
    if(abs(a) < EPS)
    {
        return 0;
    }

    if(a < 0)
    {
        return -1;
    }

    return 1;
}

bool in_treugol(dot a, dot b, dot c, dot x)
{
    long double S1 = (b - a) % (x - a);
    long double S2 = (c - b) % (x - b);
    long double S3 = (a - c) % (x - c);
    long double SS = (a - b) % (c - b);
    S1 = abs(S1);
    S2 = abs(S2);
    S3 = abs(S3);
    SS = abs(SS);

    if(sign(SS - (S1 + S2 + S3)) == 0)
    {
        return true;
    }
    return false;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    int cnt = 0;

    vector<dot> v;

    for(int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        v.emplace_back(x, y);
    }

    dot O = v[0];


    for(int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        dot X(x, y);

        X = X - O;

        if(sign((v[1] - O) % X) < 0 || sign(X % (v.back() - O)) < 0)
        {
            continue;
        }

        int l = 1;
        int r = n-1;
        while(r - l > 1)
        {
            int mm = (r + l) / 2;

            dot Y = v[mm] - O;

            if(sign(Y % X) >= 0)
            {
                l = mm;
            } else {
                r = mm;
            }
        }

        if(in_treugol(v[0], v[l], v[r], X + O))
        {
            ++cnt;
        }
    }


    if(cnt >= k)
    {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

}