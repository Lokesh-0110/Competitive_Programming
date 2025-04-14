/*Vidya vinayena shobhate*/
#include <bits/stdc++.h>
using namespace std;

//-----------------------------------------------------------------------
#define JAI_SHREE_RAM cin.sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
#define ld long double  
#define py cout<<"YES\n";
#define pn cout<<"NO\n";
#define all(x) x.begin(), x.end()
const ll mod = 1e9+7;
const ll mod1 = 998244353;
const ll N = 5e5 + 10;
//-----------------------------------------------------------------------

ll n,mx;
vector<ll> adj[N];
ll dep[N],par[N];
ll up[N][20];

void dfs(ll node,ll p,ll d){
    dep[node] = d;
    par[node] = p;
    for(ll ne:adj[node])if(ne!=p)dfs(ne,node,d+1);
}

ll kth(ll a,ll k){
    for(ll j=0;j<mx;j++)if(k&(1LL<<j))a = up[a][j];
    return a;
}

ll lca(ll a,ll b){
    if(a==b)return a;
    if(dep[b]>dep[a])swap(a,b);
    ll k = dep[b]-dep[a];
    a = kth(a,k);
    if(a==b)return a;
    for(ll j=mx;j>-1;j--){
        if(up[a][j]!=up[b][j]){
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}   

int main(){
    JAI_SHREE_RAM
    ll T = 1;
    //cin >> T;
    while (T--){
        cin>>n;
        mx = log2(n)+1;
        for(ll i=1;i<n;i++){
            ll u,v;cin>>u>>v;u--;v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0,0,0); 
        for(ll i=0;i<n;i++)up[i][0]=par[i];
        for(ll j=1;j<mx;j++){
            for(ll i=0;i<n;i++)up[i][j]=up[up[i][j-1]][j-1];
        }
        ll a,b;cin>>a>>b;a--;b--;
        cout<<"LCA of "<<a<<" "<<b<<" is "<<lca(a,b)<<"\n";
    }
    return 0;
}
