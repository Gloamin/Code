#include <bits/stdc++.h>
#define int long long
using namespace std;
int mod;int n,x;
bool ispr(int x) {
    if(x<2) return 0;
    if(x==2) return 1;
    for(int i=2;i*i<=x;i++) {
        if(x%i==0) return 0;
    }
    return 1;
}
int qpow(int a,int b) {
    int res=1;
    while(b) {
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
bool chk(int k) {
    if(k%mod==0) return false;
    for(int i=1;i*i<=n;i++)
        if(n%i==0) {
            if(i<n&&qpow(k,i)==1)return false;
            if(qpow(k,n/i)==1&&i!=1) return false;
        }
    return true;
}
signed main() {
    cin>>n>>x;
    mod=n+1;
    if(ispr(mod)==0) {cout<< -1;return 0;}
    for(int i=x-1;i>=2;i--)
        if(chk(i)) {cout<<i;return 0;}
    cout<<-1;
    return 0;
}