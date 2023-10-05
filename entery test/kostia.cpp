#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

void build(int i, int l, int r, vector<long long>&tree, vector<long long>&a){
    if(r-l==1){
        tree[i]=a[l];
        return;
    }
    int m=(l+r)/2;
    build(2*i+1, l, m, tree, a);
    build(2*i+2, m, r, tree, a);
    tree[i]=max(tree[2*i+1], tree[2*i+2]);
    return;
}

void change(int i, int l, int r, int qi, int qx, vector<long long>&tree){
    if(l>qi || r<=qi){
        return;
    }
    if(r-l==1){
        tree[i]=qx;
        return;
    }
    int m=(l+r)/2;
    change(2*i+1, l, m, qi, qx, tree);
    change(2*i+2, m, r, qi, qx, tree);
    tree[i]=max(tree[2*i+1], tree[2*i+2]);
    return;
}

int maxx(int i, int l, int r, int ql, int qr, vector<long long>&tree){
    if(l>=qr || r<=ql){
        return 0;
    }
    if(ql<=l && r<=qr){
        return tree[i];
    }
    int m=(l+r)/2;
    return max(maxx(2*i+1, l, m, ql, qr, tree), maxx(2*i+2, m, r, ql, qr, tree));
}

void build1(int i, int l, int r, vector<long long>&tree, vector<long long>&a){
    if(r-l==1){
        tree[i]=a[l];
        return;
    }
    int m=(l+r)/2;
    build(2*i+1, l, m, tree, a);
    build(2*i+2, m, r, tree, a);
    tree[i]=min(tree[2*i+1], tree[2*i+2]);
    return;
}

void change1(int i, int l, int r, int qi, int qx, vector<long long>&tree){
    if(l>qi || r<=qi){
        return;
    }
    if(r-l==1){
        tree[i]=qx;
        return;
    }
    int m=(l+r)/2;
    change(2*i+1, l, m, qi, qx, tree);
    change(2*i+2, m, r, qi, qx, tree);
    tree[i]=min(tree[2*i+1], tree[2*i+2]);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<long long>a(n);
    vector<long long>b(n);
    unordered_map<long long, vector<int>>m;
    unordered_map<long long, int>m1;
    unordered_map<long long, int>m2;
    vector<long long>h(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        h[i]=a[i];
        m[a[i]].push_back(i);
        m1[a[i]]++;
        m2[a[i]]++;
        b[i]=i+1;
    }
    long long mod=998244353;
    vector<long long>dp1(n);
    vector<long long>dp2(n);
    vector<long long>dp3(n);
    vector<long long>pref(n+1);
    vector<long long>tree(4*n);
    sort(a.begin(), a.end());
    vector<int>sk(n);
    vector<int>sk2(n);
    build(0, 0, n, tree, b);
    for(int i=0;i<n;i++){
        if(m[a[i]][m1[a[i]]-1]==0){
            sk[m[a[i]][m1[a[i]]-1]]=0;
        }
        else{
            sk[m[a[i]][m1[a[i]]-1]]=maxx(0, 0, n, 0, m[a[i]][m1[a[i]]-1], tree);
        }
        change(0, 0, n, m[a[i]][m1[a[i]]-1], 0, tree);
        m1[a[i]]--;
    }
    reverse(a.begin(), a.end());
    build1(0, 0, n, tree, b);
    for(int i=0;i<n;i++){
        if(m[a[i]][m2[a[i]]-1]==0){
            sk2[m[a[i]][m2[a[i]]-1]]=0;
        }
        else{
            sk2[m[a[i]][m2[a[i]]-1]]=maxx(0, 0, n, 0, m[a[i]][m2[a[i]]-1], tree);
        }
        change(0, 0, n, m[a[i]][m2[a[i]]-1], 0, tree);
        m2[a[i]]--;
    }
    pref[0]=0;
    dp2[0]=h[0];
    dp3[0]=h[0];
    for(int i=1;i<n;i++){
        if(sk[i]>0){
            dp2[i]=h[i]*((pref[i]-pref[sk[i]-1]+mod)%mod)%mod;
            dp2[i]+=dp2[sk[i]-1];
            dp2[i]%=mod;
        }
        else{
            dp2[i]=((pref[i]+1)*h[i])%mod;
        }
        if(sk2[i]>0){
            dp3[i]=h[i]*((pref[i]-pref[sk2[i]-1]+mod)%mod)%mod;
            dp3[i]+=dp3[sk2[i]-1];
            dp3[i]%=mod;
        }
        else{
            dp3[i]=((pref[i]+1)*h[i])%mod;
        }
        dp1[i]=(dp2[i]-dp3[i]+mod)%mod;
        pref[i+1]=(pref[i]+dp1[i])%mod;
    }
    cout<<dp1[n-1];
}