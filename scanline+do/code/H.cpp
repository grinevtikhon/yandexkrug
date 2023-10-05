#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(239);

struct node
{
    node *l, *r;

    int cnt;
    int shag;
    int f_num;
    int pr;

    node()
    {
        pr = rnd();
    }
};

typedef node * qnode;

void split(qnode &l, qnode &r, qnode a)
{
    if(a == nullptr)
    {
        l = r = nullptr;
        return;
    }

    if()
}

int main()
{

}