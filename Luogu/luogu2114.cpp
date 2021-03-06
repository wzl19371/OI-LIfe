#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,m,t[50],ct,ans;
struct Action{
	int op,t;	//1:AND, 2:OR, 3:XOR
}a[maxn];
int solve(int dep,int x){
	int ret=x;
	for(int i=1;i<=n;i++){
		if(a[i].op==1) ret&=(a[i].t>>(dep-1))&1;
		else if(a[i].op==2) ret|=(a[i].t>>(dep-1))&1;
		else ret^=(a[i].t>>(dep-1))&1;
	}
	return ret;
}
void dfs(int dep,bool full){
	if(!dep) return;
	int up=full?t[dep]:1,r[2]={-1,-1};
	for(int i=0;i<=up;i++) r[i]=solve(dep,i);
	ans+=max(r[0],r[1])<<(dep-1);
	if(!full) dfs(dep-1,false);
	else dfs(dep-1,t[dep]?r[1]>r[0]:true);
}
int main(){
	scanf("%d%d",&n,&m);
	{
		char op[5]; int t;
		for(int i=1;i<=n;i++){
			scanf("%s%d",op,&t);
			if(op[0]=='A') a[i].op=1;
			else if(op[0]=='O') a[i].op=2;
			else a[i].op=3;
			a[i].t=t;
		}
	}
	while(m){
		t[++ct]=m&1;
		m>>=1;
	}
	while(ct<30) t[++ct]=0;
	dfs(ct,true);
	printf("%d\n",ans);
	return 0; 
}
