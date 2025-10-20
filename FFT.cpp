/*Vidya vinayena shobhate*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

//-----------------------------------------------------------------------
#define JAI_SHREE_RAM cin.sync_with_stdio(false); cin.tie(0); cout.tie(0);
typedef tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> OS;
typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> MOS;
typedef tree<pair<long,long>, null_type, pair<long,long>, rb_tree_tag, tree_order_statistics_node_update> MOS1;
#define ull unsigned long long
#define ll long long
#define ld long double  
#define py cout<<"YES\n";
#define pn cout<<"NO\n";
#define all(x) x.begin(),x.end()
const ll mod = 1e9+7;
const ll mod1 = 998244353;
const ll N = 2e5 + 10;
//-----------------------------------------------------------------------
typedef complex<double> cmpl;
//constexpr double PI = 3.14159 26535 89793 23846 26433 83279 50288 41971 69399 3751
const double PI = atan2(0,-1);
/*

FFT overview , a CP guy perspective 

fast multiplication was done by anatoly karatsuba 
n^(log2(3)) ~ n^(3/2)


________________________________________________________________________
ways to represent a polynomial 

coefficient representation p0,p1,p2....pn-1,pn (n+1 coefficients)
add in o(n), multiply in o(n^2), evaluation in o(n)

roots k*(x-a1)*(x-a2)*(x-a3)...... degree d has atmost d roots
multiply in o(n), evaluation in o(n), addition is almost impossible 
This is becuase cardano's (cubic) method and ferrari's (quartic) method dont extned to quintic (galois theory)

samples (collection of pairs) degree d can be represented by d+1 points 
multiply in o(n), add in o(n), evaluation in o(n^2) 

BRIDGE coefficients to values in both sides 

coefficients -> sampling = evaluation (FFT)
sampling -> coefficients = interpolation (inverse FFT)

MAIN IDEA OF FFT

we can divide p(x) = e(x) + o(x) where e represents even terms and o the odd ones 
then we can see p(-x) = e(x) - o(x)
so we can do calculate for points 1,2,3,.... n/2 we automaticaly get the result for thier negative values in o(1)
therefore we get n points evaluation in n/2 + ((n/2)^2) 
now we can extend this again but the pitfall in the next iteration all the numbers are positive 
we can use complex number or imaginary numbers (very bad naming lol they arent really imaginary neither complex)
I reckon the complexity of imaginary arises from how late they are introduced in ones life making thier rigid brains not fathom it 
one thing that would help is think of -1 as 180 degree anticlockwise rotation in complex plane 
and multiplying by i is 90 degree anticlockwise rotation 


p(x) = v0(x) + v1(x) + v2(x) + v3(x) where i is the power mod 4 
p(-x) = v0(x) - v1(x) + v2(x) - v3(x) 
p(xi) = v0(x)i - v1(x) - v2(x)i + v3(x)
p(-xi) = -v0(x)i + v1(x) + v2(x)i -v3(x)
here in this case we get 1,2,3,...... n/4 
therefore now we get n points in 3*(n/4) + ((n/4)^2)

we cannot manualy do this , therefore we need to do something recursively 
lets say we write p(x) = a(x) + b(x) where a has even and b has even 
p = p0 + p1x + p2x^2 + p3x^3 + p4x^4 ......... 
lets p_even = p0 + p2x + p4x^2 + p6x^3 ..... 
and p_odd = p1 + p3x + p5x^2 + p7x^3 .......
a = p_even(x^2) 
b = x*p_odd(x^2) 
so p(x) = p_even(x^2) + x*p_odd(x^2)
and p(-x) = p_even(x^2) - x*p_odd(x^2) 

after one we would start needing imaginary numbers 
in short we will be dealing with values x such that x^n = 1 
these are called roots of 1 , when we use complex numbers all polynomials of degree n have exactly n roots 
x^n - 1 = 0 therefore has n roots , Its called the Fundamental Theorem of Algebra 
for the above case all values on the unit circle at angle 360/n are roots 
so we can have j from 1,2,3....n 360*j/n or 2pi*j/n 

x + iy = cosa + isina 

for using complex number in cpp 
#include<complex> 
typedef complex<double> cmpl;

and now we can do cmpl a(2,-1); or cmpl b = 2;
we can aslo get a.real() or a.imag() 



________________________________________________________________________
PROBLEM 1 
lets say we have gold bars and silver bars of weights and bag of s size
we find number of ways to fill it with gold only and silver only 
number of ways to fill with gold or silver will be equal to summation of res[i+j] += pi*pj


*/

cmpl TWO(2,0);

vector<ll> naive(vector<ll>&p,vector<ll>&q){
    // this will be n^2
    int n = p.size();
    int m = q.size();
    vector<ll>r(n+m-1,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)r[i+j] += p[i]*q[j];
    }
    return r;
}

// vector<int> multiply(vector<int>&p,vector<int>&q){
//     int n = p.size();
//     vector<int> p_eval = evaluate(P,n);
//     vector<int> q_eval = evaluate(q,n);
//     vector<int> r_eval(n);
//     for(int i=0;i<n;i++)r_eval = p_eval[i]*q_eval[i];
//     vector<int> r = interpolate(r_eval);
//     return r;
// }

vector<cmpl> fft(vector<cmpl>&p){
    int n = p.size();
    if(n==1){
        return p;
    }
    vector<cmpl> p_even(n/2),p_odd(n/2);
    for(int j=0;j<n/2;j++){
        p_even[j] = p[2*j];
        p_odd[j] = p[2*j+1];
    }
    vector<cmpl> even_eval = fft(p_even);
    vector<cmpl> odd_eval = fft(p_odd);
    vector<cmpl> val_p(n);
    for(int j=0;j<n/2;j++){
        cmpl x(cos((2*PI*j)/n),sin((2*PI*j)/n));
        val_p[j] = even_eval[j] + x*odd_eval[j];
        val_p[j+n/2] = even_eval[j] - x*odd_eval[j];
    }
    return val_p;
}

vector<cmpl> ifft(vector<cmpl>&val_p){
    int n = val_p.size();
    if(n==1){
        return val_p;
    }
    vector<cmpl> even_eval(n/2),odd_eval(n/2);
    for(int j=0;j<n/2;j++){
        cmpl x(cos((2*PI*j)/n),sin((2*PI*j)/n));
        even_eval[j] = (val_p[j]+val_p[j+n/2])/TWO;
        odd_eval[j] = (val_p[j]-val_p[j+n/2])/(x*TWO);
    }
    vector<cmpl> p_even = ifft(even_eval);
    vector<cmpl> p_odd = ifft(odd_eval);
    vector<cmpl> p(n);
    for(int j=(n/2)-1;j>-1;j--){
        p[2*j] = p_even[j];
        p[2*j+1] = p_odd[j];
    }
    return p;
}

vector<ll> multiply(vector<ll>&p,vector<ll>&q){
    ll n = 1;
    while(n<p.size()+q.size()-1)n*=2;
    vector<cmpl>p_cmpl(n);
    copy(p.begin(),p.end(),p_cmpl.begin());
    vector<cmpl>q_cmpl(n);
    copy(q.begin(),q.end(),q_cmpl.begin());
    vector<cmpl> p_eval = fft(p_cmpl);
    vector<cmpl> q_eval = fft(q_cmpl);
    vector<cmpl> r_eval(n);
    for(ll j=0;j<n;j++)r_eval[j] = p_eval[j]*q_eval[j];
    vector<cmpl> r_cmpl = ifft(r_eval);
    vector<ll>r(n);
    for(ll j=0;j<n;j++)r[j] = round(r_cmpl[j].real());
    return r;
}

int main(){
    JAI_SHREE_RAM
    int T = 1;
    //cin >> T;
    while (T--){
        ll n,m;cin>>n;
        vector<ll>a(n);
        for(ll &i:a)cin>>i;
        cin>>m;vector<ll>b(m);
        for(ll &i:b)cin>>i;
        vector<ll>r = multiply(a,b);
        for(ll i=0;i<n+m-1;i++)cout<<r[i]<<" ";
        cout<<"\n";
    }
    return 0;
}

// int main(){
//     int n,m;cin>>n>>m;
//     vector<ll>a(n),b(m);
//     for(ll &i:a)cin>>i;
//     for(ll &i:b)cin>>i;
//     auto r = multiply(a,b);
//     for(ll i:r)cout<<i<<" ";
    
//     return 0;
// }
