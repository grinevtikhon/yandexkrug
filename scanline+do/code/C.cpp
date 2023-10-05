#include<bits/stdc++.h>

using namespace std;

vector<long long> coord;
vector<long long> rash;

pair<long long, long long> fo(pair<long long, long long> a, pair<long long, long long> b)
{
    if(a.first < b.first)
    {
        return a;
    }
    if(a.first == b.first)
    {
        return {a.first, a.second + b.second};
    }
    return b;
}


struct D_o
{
    long long n;
    vector<pair<long long, long long>> t;
    vector<long long> promis;

    D_o(){
        n = coord.size() - 1;
        t.resize(4 * n);
        promis.resize(4 * n);

        build(0, 0, n);
    }

    void build(long long v, long long tl, long long tr)
    {
        if(tl + 1 == tr)
        {
            t[v] = {0, coord[tl + 1] - coord[tl]};
            return;
        }

        long long tm = (tl + tr) / 2;

        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);

        t[v] = fo(t[2 * v + 1], t[2 * v + 2]);
    }

    void push(long long v, long long tl, long long tr)
    {
        t[v].first += promis[v];

        if(tl +1 != tr)
        {
            promis[2 * v + 1] += promis[v];
            promis[2 * v + 2] += promis[v];
        }

        promis[v] = 0;
    }

    pair<long long, long long> get(long long v, long long tl, long long tr, long long l, long long r)
    {
        push(v, tl, tr);

        if(tr <= l || r <= tl)
        {
            return {1e9, 0};
        }

        if(l <= tl && tr <= r)
        {
            return t[v];
        }

        long long tm = (tl + tr) / 2;

        return fo(get(2 * v + 1, tl, tm, l, r), get(2 * v + 2, tm, tr, l, r));
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
            push(v, tl ,tr);
            return;
        }

        long long tm = (tl + tr)/ 2;

        update(2 * v + 1, tl, tm, l, r, d);
        update(2 * v + 2, tm, tr, l, r, d);

        t[v] = fo(t[2 * v + 1], t[2 * v + 2]);
    }


    long long get_ans()
    {
        pair<long long, long long> buf = get(0, 0, n, 0, n);

        if(buf.first != 0)
        {
            return coord.back() - coord[0];
        }

        return  coord.back() - coord[0] - buf.second;
    }

};

int main()
{

    long long n;

    cin >> n;


    if(n == 0)
    {
        cout << "0\n";
        return 0;
    }

    vector<vector<long long>> zap(n);

    for(long long i = 0; i < n; ++i)
    {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        coord.push_back(y1);
        coord.push_back(y2);
        zap[i] = {x1, y1, x2, y2};
    }

    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    vector<vector<long long>> sob;

    for(long long i = 0; i < n; ++i)
    {
        long long x1, y1, x2, y2;

        x1 = zap[i][0];
        y1 = zap[i][1];
        x2 = zap[i][2];
        y2 = zap[i][3];

        y1 = lower_bound(coord.begin(), coord.end(), y1) - coord.begin();
        y2 = lower_bound(coord.begin(), coord.end(), y2) - coord.begin();

        sob.push_back({x1, 1, y1, y2});
        sob.push_back({x2, -1, y1, y2});
    } 

    sort(sob.begin(), sob.end());

    long long prx = zap[0][0];
    long long sum = 0;

    D_o gg;



    for(long long i = 0; i < sob.size(); ++i)
    {
        long long x = sob[i][0];
        long long d = sob[i][1];
        long long y1 = sob[i][2];
        long long y2 = sob[i][3];

        sum += gg.get_ans() * (x - prx);

        gg.update(0, 0, gg.n, y1, y2, d);
        prx = x;
    }

    cout << sum << '\n';



}