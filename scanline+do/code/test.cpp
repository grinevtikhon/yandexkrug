#include<iostream> 
#include<vector> 
 
using namespace std; 
 
vector<long long> vec; 
vector<long long> t; 
 
void build(long long v, long long tl, long long tr) 
{ 
    if(tl+1==tr){ 
        t[v]=vec[tl]; 
        return; 
    } 
 
    long long tm = (tl + tr) / 2; 
 
    build(2 * v + 1, tl, tm); 
    build(2 * v + 2, tm, tr); 
 
    t[v]=t[2 * v + 1] + t[2 * v + 2]; 
} 
 
long long get(long long v, long long tl, long long tr, long long l, long long r) 
{ 
    if(tr<=l || r<=tl){ 
        return 0; 
    } 
 
    if(l<=tl && tr<=r){ 
        return t[v]; 
    } 
 
    long long tm = (tl + tr) / 2; 
 
    return get(2*v+1, tl, tm, l, r) + get(2*v+2, tm, tr, l, r); 
} 
 
int main() 
{ 
    long long n; 
    long long k; 
 
    cin >> n; 
 
    for(long long i = 0; i < n; i++){ 
        long long a; 
        cin >> a; 
        vec.push_back(a); 
    } 
 
    cin >> k; 
    t.resize(4*n); 
    build(0, 0, n); 
 
    for(long long i = 0; i < k; i++){ 
        long long l, r; 
        cin >> l >> r; 
        --l; 
        --r; 
       cout << get(0, 0, n, l, r + 1) << " ";  
    } 
 
}