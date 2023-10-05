#include<bits/stdc++.h>

using namespace std;

struct node
{
    node *l, *r;
    int val;

    node(int x)
    {
        l = r = nullptr;
        val = x;
    }
};

vector<vector<int>> gr;

int main()
{
    int n, k, q;

    cin >> n >> k >> q;
    gr.resize(n);

    vector<pair<int, int>> deep(n);
    vector<int> glub(n);

    for(int i = 0; i < n; ++i)
    {
        cin >> deep[i].first;
        glub[i] = deep[i].first;
        deep[i].second = i;
    }

    sort(deep.begin(), deep.end());



    vector<vector<int>> gg(n);

    vector<node *> v(n);
    for(int i = 0; i < n; ++i)
    {
        v[i] = new node(i);
        if(i != 0)
        {
            v[i-1]->r = v[i];
            v[i]->l = v[i-1];
            gr[i].push_back(i-1);
            gr[i-1].push_back(i);
        }
    }

    int h = 0;
    
    while(h < n)
    {
        int val = deep[h].first;

        int l = -1;
        int r = 0;

        
        while(h < n && deep[h].first == val)
        {
            int x = deep[h].second;

            if(v[x]->l != nullptr && glub[v[x]->l->val] != val)
            {
                l = v[x]->l->val;
            }

            if(v[x]->r != nullptr && glub[v[x]->r->val] != val)
            {
                r = v[x]->r->val;
                if(l != -1)
                {
                    v[l]->r = v[r];
                    v[r]->l = v[l];
                    gr[l].push_back(r);
                    gr[r].push_back(l);
                }
            }

            ++h;
        }
    }

    // for(int i = 0; i < n; ++i)
    // {
    //     if(v[i]->l == nullptr)
    //     {
    //         cout << " ";
    //     } else {
    //         cout << v[i]->l->val;
    //     }

    //     cout << " | ";

    //     if(v[i]->r == nullptr)
    //     {
    //         cout << " ";
    //     } else {
    //         cout << v[i]->r->val;
    //     }

    //     cout << '\n';

    // }

    for(int i = 0; i < q; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a;
        --b;


        vector<int> tim(n, 1e9);

        tim[a] = 0;

        deque<int> dq;
        dq.push_back(a);

        while(tim[b] == 1e9)
        {
            int v = dq.front();
            dq.pop_front();

            for(auto u : gr[v]){
                if(tim[u] == 1e9)
                {
                    tim[u] = tim[v] + 1;
                    dq.push_back(u);
                }
            }
        }

        cout << tim[b] - 1 << '\n';
    }

}