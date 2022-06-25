#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+10;
int qpow(int a,int b,int p) {
	int res=1;
	while(b) {
		if(b&1) res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}
int phi[N],prime[N],pcnt;
bool havert[N],vis[N];
void getPhi() {
	phi[1]=1;
	for(int i=2;i<=N-10;i++) {
		if(vis[i]==0) {
			prime[++pcnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=pcnt&&i*prime[j]<=N-10;j++) {
			vis[i*prime[j]]=true;
			if(i%prime[j]==0) {
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	havert[2]=havert[4]=1;
	for(int i=2;i<=pcnt;i++) {
		for(int j=1;(1LL*j*prime[i])<=N-10;j*=prime[i]) havert[j*prime[i]]=1;
		for(int j=2;(1LL*j*prime[i])<=N-10;j*=prime[i]) havert[j*prime[i]]=1;
	}
}
int zyscnt,zys[N];
void fenjie(int n) {
	zyscnt=0;
	for(int i=2;i*i<=n;i++) {
		if(n%i==0) {
			zys[++zyscnt]=i;
			while(n%i==0) n/=i; 
		}
	}
	if(n>1) zys[++zyscnt]=n;
}
bool check(int n,int p) {
	if(qpow(n,phi[p],p)!=1) return false;
	for(int i=1;i<=zyscnt;i++) {
		if(qpow(n,phi[p]/zys[i],p)==1) return false;
	}
	return true;
}
int findrt(int p) {
	for(int i=1;i<p;i++) {
		if(check(i,p)) return i;
	}
	return 0;
}
int ans[N],anscnt;
void getAll(int p,int n) {
	int pr=1;
	for(int i=1;i<=phi[p];i++) {
		pr=pr*n%p;
		if(__gcd(i,phi[p])==1) {
			ans[++anscnt]=pr;
		}
	}
}
signed main() {
	// ios::sync_with_stdio(false);
	getPhi();
	int t;cin>>t;
	while(t--) {
		int p,d;cin>>p>>d;
		if(havert[p]) {
			anscnt=0;
			fenjie(phi[p]);
			int minn=findrt(p);
			getAll(p,minn);
			sort(ans+1,ans+1+anscnt);
			cout<<anscnt<<endl;
			for(int i=1;i<=anscnt/d;i++) {
				cout<<ans[i*d]<<' ';
			}
			cout<<endl;
		} else {
			cout<<"0\n\n";
		}
	}
	return 0;
}