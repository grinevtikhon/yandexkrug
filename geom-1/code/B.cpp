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

int main()
{
    cout.setf(ios::fixed);
    cout.precision(10);

    int x1, y1, r1, x2, y2, r2;

    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    dot A(x1, y1);
    dot B(x2, y2);

    if(A.is_keep(B))
    {
        if(r1 == r2)
        {
            cout << 3 << "\n";
            return 0;
        } else {
            cout << 0 << '\n';
            return 0;
        }
    }

    dot a = B-A;

    long double x = (a.len2() - r2*r2 + r1*r1) / (2*sqrt(a.len2()));
    dot C = a * (1 / sqrt(a.len2()));
    C = C * x;
    C = C + A;

    line rad = line(C, line(A, B));
    
    dot n1 = rad.napr;
    n1 = n1 * (1 / sqrt(n1.len2()));

    dot X1;
    dot X2;

    long double h = r1*r1 - (A - C).len2();

    if(abs(h) < EPS)
    {
        cout << 1 << '\n';
        cout << C.x << " " << C.y << '\n';
        return 0; 
    }

    if(h < 0)
    {
        cout << 0 << '\n';
        return 0;
    }

    h = sqrt(h);

    X1 = C + n1 * h;
    X2 = C - n1 * h;

    cout << 2 << '\n';
    cout << X1.x << ' ' << X1.y << '\n';
    cout << X2.x << ' ' << X2.y << '\n';




}
