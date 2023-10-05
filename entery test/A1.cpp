#include<bits/stdc++.h>

using namespace std;


struct dot
{
    long long x, y;

    dot()
    {
        x = 0;
        y = 0;
    }
    dot(long long _x, long long _y)
    {
        x = _x;
        y = _y;
    }

    dot operator-(dot o)
    {
        return dot(x - o.x, y - o.y);
    }

    dot operator+(dot o)
    {
        return dot(x + o.x, y + o.y);
    }

    long long operator*(dot o)
    {
        return x*o.x + y*o.y;
    }

    long long operator%(dot o)
    {
        return x * o.y - o.x * y;
    }

    bool operator< (dot&b)
    {
        if((*this) % b == 0){
            return (*this) * (*this) < b * b;
        } else {
            return  (*this) % b > 0;
        }
    }

    bool operator==(dot&b)
    {
        return x == b.x && y == b.y;
    }
};

int main()
{
    long long n;
    cin >> n;
    dot C;

    cin >> C.x >> C.y;

    vector<dot> v;

    dot F;

    for(long long i = 0; i < n; ++i)
    {
        dot A;
        cin >> A.x >> A.y;

        v.push_back(A);

        if(i == 0 || F.x > A.x)
        {
            F = A;
        }

        if(A.x == F.x && A.y < F.y)
        {
            F = A;
        }
    }   

    for(long long i = 0; i < v.size(); ++i)
    {
        v[i] = v[i] - F;
    }

    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());



    //{1, 1, 2, 3, 4, 4, 4, 12} => {1, 2, 3, 4, 12, 1,4,4}

    vector<dot> ob;

    for(long long i = 0; i < v.size(); ++i)
    {
        while(ob.size() >= 2)
        {
            dot l1 = ob[ob.size() - 2];
            dot l2 = ob.back();
            dot l3 = v[i];

            if((l3 - l2) % (l1 - l2) <= 0)
            {
                ob.pop_back();
            } else {
                break;
            }
        }
        ob.push_back(v[i]);
    }

    for(long long i = 0; i < ob.size(); ++i)
    {
        ob[i] = ob[i] + F;
        // cout << ob[i].x << " " << ob[i].y << '\n';

    }

    long long cnt = 0;

    for(long long i = 0; i < ob.size(); ++i)
    {
        dot A = ob[i];
        dot B = ob[(i + 1) % ob.size()];

        if((A - B) * (C - B) > 0 && (B - A) * (C - A) > 0)
        {
            ++cnt;
        }
    }

    cout << cnt << '\n';
}