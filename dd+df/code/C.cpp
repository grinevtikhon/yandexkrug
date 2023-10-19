#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(239);

struct node
{
    node *l, *r;

    int y;
    int val;
    int cnt;

    node(int _val)
    {
        l = r = nullptr;
        val = _val;
        cnt = 1;
        y = rnd();
    }
};

typedef node * qnode;

int get_cnt(qnode a)
{
    if(a == nullptr)
    {
        return 0;
    }
    return a->cnt;
}

void update(qnode a)
{
    if(a == nullptr)
    {
        return;
    }
    a->cnt = 1 + get_cnt(a->l) + get_cnt(a->r);
}

void split(qnode &l, qnode &r, qnode a, int val)
{
    if(a == nullptr)
    {
        l = r = nullptr;
        return;
    }

    if(a->val >= val)
    {
        split(l, a->l, a->l, val);
        r = a;
        update(r);
    } else {
        split(a->r, r, a->r, val);
        l = a;
        update(l);
    }
}

void merge(qnode &a, qnode l, qnode r)
{
    if(l == nullptr)
    {
        a = r;
        return;
    }
    if(r == nullptr)
    {
        a = l;
        return;
    }

    if(l->y > r->y)
    {
        merge(l->r, l->r, r);
        a = l;
        update(a);
    } else {
        merge(r->l, l, r->l);
        a = r;
        update(a);
    }
}

struct D_o
{
    vector<qnode> t;
    int n;

    D_o(int _n)
    {
        n = _n;
        t.resize(4 * n, nullptr);
    }

    void update(int v, int tl, int tr, int pos, int val)
    {
        if(tr <= pos || pos + 1 <= tl)
        {
            return;
        }

        if(pos <= tl && tr <= pos+1)
        {
            qnode a, b;
            split(a, b, t[v], val);
            merge(t[v], a, new node(val));
            merge(t[v], t[v], b);
            return;
        }

        int tm = (tl + tr) / 2;

        update(2 * v + 1, tl, tm, pos, val);
        update(2 * v + 2, tm, tr, pos, val);

        qnode a, b;
        split(a, b, t[v], val);
        merge(t[v], a, new node(val));
        merge(t[v], t[v], b);
    }

    int get(int v, int tl, int tr, int l, int r, int val)
    {
        if(tr <= l || r <= tl)
        {
            return 0;
        }

        if(l <= tl && tr <= r)
        {
            qnode a, b;
            split(a, b, t[v], val + 1);
            int ans = get_cnt(b);
            merge(t[v], a, b);
            return ans;
        }

        int tm = (tl + tr) / 2;

        return get(2 * v + 1, tl, tm, l, r, val) + get(2 * v + 2, tm, tr, l, r, val);
    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;

    while(cin >> n)
    {
        D_o sm(n);

        for(int i = 0; i < n; ++i)
        {
            int pos, val;
            cin >> pos >> val;
            --pos;
            cout << sm.get(0, 0, n, 0, pos, val) << ' ';
            sm.update(0, 0, n, pos, val);
        }
    }
    
}