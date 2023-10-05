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
};

struct line
{
    dot O;
    dot napr;

    line(dot a, dot b)
    {
        O = a;
        napr = (b - a);
    }

    line(dot x, line l)
    {
        O = x;
        napr.x = l.napr.y;
        napr.y = -l.napr.x;
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

struct luch
{
    dot O;
    dot napr;

    luch(dot a, dot b)
    {
        O = a;
        napr = b - a;
    }


    bool is_keep(dot o)
    {
        return (abs((O - o) % napr) < EPS) && (napr * (o - O) > -EPS);
    }
};

struct segment
{
    dot A;
    dot B;

    segment(dot a, dot b)
    {
        A = a;
        B = b;
    }

    bool is_keep(dot o)
    {
        return abs((A - B) % (o - A)) < EPS && (B - A) * (o - A) > -EPS && (A - B) * (o - B) > -EPS;
    }
};

int main()
{

    cout.setf(ios::fixed);
    cout.precision(8);

    vector<dot> gg(4);
    for(int i = 0; i < 4; ++i)
    {
        int x, y;
        cin >> x >> y;
        gg[i] = dot(x, y);
    }

    dot A, B, C, D;

    A = gg[0];
    B = gg[1];
    C = gg[2];
    D = gg[3];

    gg.push_back(line(A, B).cross(line(C, D)));

    // cout << gg.back().x << ' ' << gg.back().y << '\n';

    gg.push_back(line(A, B).proect(C));
    gg.push_back(line(A, B).proect(D));
    gg.push_back(line(C, D).proect(A));
    gg.push_back(line(C, D).proect(B));


    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {

            vector<dot> v1;
            vector<dot> v2;

            if(i == 0)
            {
                for(int l = 0; l < gg.size(); ++l)
                {
                    if(A.is_keep(gg[l]))
                    {
                        v1.push_back(gg[l]);
                    }
                }
            }
            if(i == 1)
            {
                for(int l = 0; l < gg.size(); ++l)
                {
                    if(segment(A, B).is_keep(gg[l]))
                    {
                        v1.push_back(gg[l]);
                    }
                }
            }
            if(i == 2)
            {
                for(int l = 0; l < gg.size(); ++l)
                {
                    if(luch(A, B).is_keep(gg[l]))
                    {
                        v1.push_back(gg[l]);
                    }
                }
            }
            if(i == 3)
            {
                for(int l = 0; l < gg.size(); ++l)
                {
                    if(line(A, B).is_keep(gg[l]))
                    {
                        v1.push_back(gg[l]);
                    }
                }
            }



            if(j == 0)
            {
                for(int l = 0; l < gg.size(); ++l)
                {
                    if(C.is_keep(gg[l]))
                    {
                        v2.push_back(gg[l]);
                    }
                }
            }
            if(j == 1)
            {
                for(int l = 0; l < gg.size(); ++l)
                {
                    if(segment(C, D).is_keep(gg[l]))
                    {
                        v2.push_back(gg[l]);
                    }
                }
            }
            if(j == 2)
            {
                for(int l = 0; l < gg.size(); ++l)
                {
                    if(luch(C, D).is_keep(gg[l]))
                    {
                        v2.push_back(gg[l]);
                    }
                }
            }
            if(j == 3)
            {
                for(int l = 0; l < gg.size(); ++l)
                {
                    if(line(C, D).is_keep(gg[l]))
                    {
                        v2.push_back(gg[l]);
                    }
                }
            }



            long double ans = 1e15;

            for(int i1 = 0; i1 < v1.size(); ++i1)
            {
                for(int i2 = 0; i2 < v2.size(); ++i2)
                {
                    ans = min(ans, sqrt((v1[i1] - v2[i2]) * (v1[i1] - v2[i2])));
                }
            }

            cout << ans << '\n';


        }
    }


}