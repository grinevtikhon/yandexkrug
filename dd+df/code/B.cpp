#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(239);

struct node
{
    node *l, *r;

    int y;
    int cnt;
    int i;

    node(int val)
    {
        l = r = nullptr;
        y = rnd();
        cnt = 1;
        i = val;
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

void split_cnt(qnode &l, qnode &r, qnode a, int cnt)
{
    if(a == nullptr)
    {
        l = r = nullptr;
        return;
    }

    if(get_cnt(a->l) >= cnt)
    {
        split_cnt(l, a->l, a->l, cnt);
        r = a;
        update(r);
    } else {
        cnt -= get_cnt(a->l) + 1;
        split_cnt(a->r, r, a->r, cnt);
        l = a;
        update(l);
    }
}

void split_i(qnode &l, qnode &r, qnode a, int i)
{
    if(a == nullptr)
    {
        l = r = nullptr;
        return;
    }

    if(a->i >= i)
    {
        split_i(l, a->l, a->l, i);
        r = a;
        update(r);
    } else {
        split_i(a->r, r, a->r, i);
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

int main()
{
    int n;
    cin >> n;
    qnode root = nullptr;

    for(int i = 0; i < n; ++i)
    {
        int val;
        cin >> val;
        if(val == 0)
        {
            merge(root, root, new node(i));
        }
    }

    int m;
    cin >> m;

    for(int i = 0; i < m; ++i)
    {
        char c;
        cin >> c;

        if(c == 'u')
        {
            int x, val;
            cin >> x >> val;
            --x;

            qnode a, b, c;
            split_i(a, b, root, x);
            split_i(b, c, b, x + 1);

            if(b != nullptr)
            {
                delete b;
            }

            if(val == 0)
            {
                merge(root, a, new node(x));
                merge(root, root, c);
            } else {
                merge(root, a, c);
            }
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            --r;

            qnode a, b, c;

            split_i(a, b, root, l);
            split_i(b, c, b, r + 1);


            qnode bl, bm, br;
            split_cnt(bl, br, b, k);
            split_cnt(bl, bm, bl, k-1);

            if(get_cnt(bl) == k-1 && get_cnt(bm) == 1)
            {
                cout << bm->i + 1 << ' ';
            } else {
                cout << -1 << ' ';
            }

            merge(root, a, bl);
            merge(root, root, bm);
            merge(root, root, br);
            merge(root, root, c);
        }
    }
    cout << '\n';
}