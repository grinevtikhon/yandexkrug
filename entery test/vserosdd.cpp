#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(229380928339);

struct node
{
    node *l, *r;

    long long val;
    long long sum;
    long long cnt;
    long long promis;
    long long pr;

    node(long long _val)
    {
        l = r = nullptr;
        val = _val;
        cnt = 1;
        sum = val;
        promis = 0;
        pr = rnd();
    }
};

typedef node * qnode;

long long get_cnt(qnode a)
{
    if(a == nullptr)
    {
        return 0;
    }
    return a->cnt;
}

long long get_sum(qnode a)
{
    if(a == nullptr)
    {
        return 0;
    }
    return a->sum;
}


void push(qnode a)
{
    if(a == nullptr)
    {
        return;
    }

    if(a->promis == 0)
    {
        return;
    }

    a->sum = a->promis * a->cnt;
    a->val = a->promis;
    
    if(a->l != nullptr)
    {
        a->l->promis = a->promis;
    }
    if(a->r != nullptr)
    {
        a->r->promis = a->promis;
    }

    a->promis = 0;
}

void update(qnode a)
{
    if(a == nullptr)
    {
        return;
    }

    
    push(a->l);
    push(a->r);

    a->cnt = 1 + get_cnt(a->l) + get_cnt(a->r);
    a->sum = a->val + get_sum(a->l) + get_sum(a->r);
}



void split_num(qnode &l, qnode &r, qnode a, long long x)
{
    

    if(a == nullptr)
    {
        l = r = nullptr;
        return;
    }

    push(a);

    if(a->val > x)
    {
        split_num(a->r, r, a->r, x);
        l = a;
        // update(l);
    } else {
        split_num(l, a->l, a->l, x);
        r = a;
        // update(r);
    }

    update(l);
    update(r);
}

void split_cnt(qnode &l, qnode &r, qnode a, long long k)
{
    

    if(a == nullptr)
    {
        l = r = nullptr;
        return;
    }

    push(a);

    if(get_cnt(a->l) >= k)
    {
        split_cnt(l, a->l, a->l, k);
        r = a;
        // update(r);
    } else {
        k-= get_cnt(a->l) + 1;
        split_cnt(a->r, r, a->r, k);
        l = a;
        // update(l);
    }


    update(l);
    update(r);
}

void split_sum(qnode &l, qnode &r, qnode a, long long s)
{
    

    if(a == nullptr)
    {
        l = r = nullptr;
        return;
    }

    push(a);
    push(a->l);

    if(get_sum(a->l) + a->val > s)
    {
        split_sum(l, a->l, a->l, s);
        r = a;
        // update(r);
    } else {
        s -= get_sum(a->l) + a->val;
        split_sum(a->r, r, a->r, s);
        l = a;
        // update(l);
    }
    update(l);
    update(r);
}

void merge(qnode &a, qnode l, qnode r)
{
    push(l);
    push(r);
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

    if(l->pr > r->pr)
    {
        merge(l->r, l->r, r);
        a = l;
    } else {
        merge(r->l, l, r->l);
        a = r;
    }

    update(a);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n, m;
    cin >> n >> m;

    qnode root = nullptr;

    for(long long i = 0; i < n; ++i)
    {
        long long p;

        cin >> p;

        qnode buf = new node(p);
        merge(root, root, buf);
    }

    for(long long i = 0; i < m; ++i)
    {
        long long t, k ,x;
        cin >> t >> k >> x;

        if(t == 1)
        {
            qnode a, b, c;

            split_cnt(a, c, root, k);
            split_num(a, b, a, x);
            if(b != nullptr)
            {
                b->promis = x;
                push(b);
            }

            merge(root, a, b);
            merge(root, root, c);
        } else {
            --k;
            long long ans = 0;

            qnode gg;

            split_cnt(root, gg, root, k);

            while(true)
            {
                qnode a, b, c;

                
                split_sum(b, c, gg, x);
                ans += get_cnt(b);
                x -= get_sum(b);

                qnode cl, cr;
                split_num(cl, gg, c, x);

                merge(root, root, b);
                merge(root, root, cl);

                k = get_cnt(root);

                if(k == n)
                {
                    break;
                }
            }
            cout << ans << '\n';
        }
    }
    

}