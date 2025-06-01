/*Vidya vinayena shobhate*/
#include <bits/stdc++.h>
using namespace std;

//-----------------------------------------------------------------------
#define JAI_SHREE_RAM cin.sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
#define ld long double  
#define py cout<<"YES\n";
#define pn cout<<"NO\n";
#define all(x) x.begin(),x.end()
const ll mod = 1e9+7;
const ll mod1 = 998244353;
const ll N = 2e4 + 10;
//-----------------------------------------------------------------------

struct UnionFind{
    vector<ll>par;
    vector<ll>siz;
    void init(ll n){
        siz.assign(n,1);
        par.resize(n);
        for(ll i=0;i<n;i++)par[i]=i;
    }
    
    ll get(ll x){return par[x]=(par[x]==x)?x:get(par[x]);}
    
    bool unite(ll x,ll y){
        x = get(x);
        y = get(y);
        if(x==y)return true;
        if(siz[y]>siz[x])swap(x,y);
        par[y]=x;
        siz[x]+=siz[y];
        return false;
    }
};

int main(){
    JAI_SHREE_RAM
    ll T = 1;
    cin >> T;
    while (T--){
        
    }
    return 0;
}
