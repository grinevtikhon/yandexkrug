#include<bits/stdc++.h>

using namespace std;

struct D_o
{
    long long n;
    vector<long long> vec;
    vector<long long> t;
    vector<long long> promis;

    D_o(vector<long long> &_vec)
    {
        vec = _vec;
        n = vec.size();
        t.resize(4 * n);
        promis.resize(4 * n);

        build(0, 0, n);
    }

    void build(long long v, long long tl ,long long tr)
    {
        if(tl + 1 == tr)
        {
            t[v] = vec[tl];
            return;
        }

        long long tm = (tl + tr) / 2;

        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);
    }

    void push(long long v, long long tl, long long tr)
    {
        t[v] += promis[v];
        if(tl + 1 != tr)
        {
            promis[2 * v + 1] += promis[v];
            promis[2 * v + 2] += promis[v];
        }
        promis[v] = 0;
    }

    long long get(long long v, long long tl, long long tr, long long l, long long r)
    {
        push(v, tl, tr);
        if(tr <= l || r <= tl)
        {
            return 0;
        }

        if(l <= tl && tr <= r)
        {
            return t[v];
        }

        long long tm = (tl + tr) / 2;

        return get(2 * v + 1, tl, tm, l, r) + get(2 * v + 2, tm, tr, l, r);
    }

    

    void update(long long v, long long tl, long long tr, long long l, long long r, long long d)
    {
        push(v, tl, tr);

        if(tr <= l || r <= tl)
        {
            return;
        }

        if(l <= tl && tr <= r)
        {
            promis[v] += d;
            push(v, tl, tr);
            return;
        }

        long long tm = (tl + tr) / 2;

        update(2 * v + 1, tl, tm, l, r, d);
        update(2 * v + 2, tm, tr, l, r, d);
    }

};

int main()
{
    long long n;
    cin >> n;

    vector<long long> w(n);
    vector<long long> b(n);

    for(long long i = 0; i < 2 * n; ++i)
    {
        char c;
        long long numb;
        cin >> c >> numb;
        --numb;
        if(c == 'B')
        {
            b[numb] = i;
        } else {
            w[numb] = i;
        }
    }

    vector<long long> v(2 * n);
    for(long long i = 0; i < v.size(); ++i)
    {
        v[i] = i;
    }

    D_o st(v);

    long long x = 0;
    long long y = 0;

    long long ans = 0;

    for(long long i = 0; i < 2*n; ++i)
    {
        long long pos1, pos2;
        if(x < n)
        {
            pos1 = st.get(0, 0, st.n, w[x], w[x] + 1);
        } else {
            pos1 = 1e9;
        }

        if(y < n)
        {
            pos2 = st.get(0, 0, st.n, b[y], b[y] + 1);
        } else {
            pos2 = 1e9;
        }

        long long pos;

        if(pos1 < pos2)
        {
            pos = pos1;
            st.update(0, 0, st.n, w[x], st.n, -1);
            ++x;
            
        } else {
            pos = pos2;
            st.update(0, 0, st.n, b[y], st.n, -1);
            ++y;
            
        }

        
        ans += pos;
    }

    cout << ans << '\n';
}