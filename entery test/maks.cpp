#include <bits/stdc++.h>
using namespace std;

#define int long long

void init() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
}
mt19937_64 rnd(17);

struct node {
    int prior, size = 1;
    node *l = 0, *r = 0;

    int val, sum, lazy = 0;
    node(int _val) : val(_val), sum(_val) { prior = rnd(); }
};

node *root = 0;
// using pdd = pair<node*, node*>;

int size(node* p) { return (p ? p->size : 0); }

void push(node *p) {
    if(!p) return;
    if(p->lazy != 0) {
        p->val = p->lazy;
        p->sum = size(p) * p->lazy;
        if(p->l) {
            p->l->lazy = p->lazy;
        }
        if(p->r) {
            p->r->lazy = p->lazy;
        }
        p->lazy = 0;
    }
}

int sum(node *p) {
    return (p ? p->sum : 0);
}

void upd(node* p) {
    if(!p) return;
    p->size = 1 + size(p->l) + size(p->r);
    p->sum = p->val + sum(p->l) + sum(p->r);
}



pair<node*, node*> split_am(node *p, int k) {
    if(!p) {
        return { 0, 0 };
    }
    push(p);
    if(size(p->l) >= k) {
        auto [l, r] = split_am(p->l, k);
        p->l = r;
        upd(p);
        return { l, p };
    } else {
        auto [l, r] = split_am(p->r, k - size(p->l) - 1);
        p->r = l;
        upd(p);
        return { p, r };
    }
}

pair<node*, node*> split_val(node *p, int x) {
    if(!p) {
        return { 0, 0 };
    }
    push(p);
    if(p->val <= x) {
        auto [l, r] = split_val(p->l, x);
        p->l = r;
        upd(p);
        return { l, p };
    } else {
        auto [l, r] = split_val(p->r, x);
        p->r = l;
        upd(p);
        return { p, r };
    }
}

pair<node*, node*> split_sum(node *p, int s) {
    if(!p) return { 0, 0 };
    push(p);
    push(p->l);
    if(sum(p->l) + p->val <= s) {
        auto [l, r] = split_sum(p->r, s - sum(p->l) - p->val);
        p->r = l;
        upd(p);
        return { p, r };
    } else {
        auto [l, r] = split_sum(p->l, s);
        p->l = r;
        upd(p);
        return { l, p };
    }
}

node* merge(node* l, node* r) {
    push(l);
    push(r);
    if(!l) return r;
    if(!r) return l;

    if(l->prior < r->prior) {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    } else {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    }
}

void type1(int k, int x) {
    auto [L, R] = split_am(root, k);
    auto [L1, L2] = split_val(L, x);
    if(L2) {
        L2->lazy = x;
    }
    root = merge(merge(L1, L2), R);
}

int type2(int k, int x) {
    auto [L, R] = split_am(root, k - 1);
    auto [R1, R2] = split_sum(R, x);
    int ans = size(R1);
    x -= sum(R1);
    L = merge(L, R1);
    while(R2 && x > 0) {
        auto [R3, R4] = split_val(R2, x - 1);
        L = merge(L, R3);
        auto [R5, R2] = split_sum(R4, x);
        x -= sum(R5);
        ans += size(R5);
        L = merge(L, R5);
    }
    root = merge(L, R2);
    return ans;
}

signed main() {
    init();

    int n, m;
    cin >> n >> m;

    for(int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        node* t = new node(p);
        root = merge(root, t);
    }
    for(int i = 0; i < m; ++i) {
        int t, k, x;

        cin >> t >> k >> x;
        if(t == 1) {
            type1(k, x);
        } else {
            cout << type2(k, x) << '\n';
        }
    }
}