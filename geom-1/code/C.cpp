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

int main()
{
    cout.setf(ios::fixed);
    cout.precision(10);

    long double PI = 2 * acos(0);

    int x1, y1, x2, y2, x3, y3, r;

    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> r;

    dot A(x1, y1);
    dot B(x2, y2);
    dot O(x3, y3);

    line a(A, B);
    line n1(O, a);
    
    dot G = a.cross(n1);

    if(sign((G - A) * (B - A)) < 0 || sign((G - B) * (A - B)) < 0 || sign(r - (G - O).len()) <= 0)
    {
        cout << (A - B).len() << '\n';
        return 0;
    }


    dot A1, A2;

    dot j1 = (O - A);
    long double alpha = acos(r / j1.len());
    line norm1 (O, line(O, A));
    dot nm1 = norm1.napr;
    nm1 = nm1 * (1 / nm1.len());
    j1 = j1 * (1 / j1.len());

    A1 = O - (j1 * r * cos(alpha)) + (nm1 * r * sin(alpha));
    A2 = O - (j1 * r * cos(alpha)) - (nm1 * r * sin(alpha));



    dot B1, B2;

    dot j2 = (O - B);
    long double beta = acos(r / j2.len());
    line norm2 (O, line(O, B));
    dot nm2 = norm2.napr;
    nm2 = nm2 * (1 / nm2.len());
    j2 = j2 * (1 / j2.len());

    B1 = O - (j2 * r * cos(beta)) + (nm2 * r * sin(beta));
    B2 = O - (j2 * r * cos(beta)) - (nm2 * r * sin(beta));


    long double ans = (A - A1).len() + (B - B1).len();

    long double kek = (A1 - B1).len();
    kek = min(kek, (A1 - B2).len());
    kek = min(kek, (A2 - B1).len());
    kek = min(kek, (A2 - B2).len());

    long double gama = 2 * asin(kek / (2 * r));

    cout << ans  + gama*r << "\n";



}


/*

0 0 4 0
2 0

*/