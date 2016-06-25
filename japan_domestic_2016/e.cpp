#include <bits/stdc++.h>
using namespace std;
#define int long long
struct P{
	int x,y,z;
};


int cost[2010][2010];
vector<int> g[2010];
P ps[2010];
int n,k,s;
bool check(P a,P b){
	int A = s - abs(a.x-b.x);
	int B = s - abs(a.y-b.y);
	int C = s - abs(a.z-b.z);
	return A > 0 and B > 0 and C > 0;
}
int costf(P a,P b){
	int A = s - abs(a.x-b.x);
	int B = s - abs(a.y-b.y);
	int C = s - abs(a.z-b.z);
	return 2*(A * B + B * C + C * A);
}


int done[2010];
int iscycle;
vector<int> comp;


long long f(vector<int> id){
	long long ans = -2e18;
	for(int i = 0 ; i+k-1 < id.size() ; i++){
		long long sub = 0;
		for(int j = i+1 ; j < i+k ; j++ ){
			sub += cost[id[j]][id[j-1]];
		}
		if( cost[id[i]][id[i+k-1]] > 0 and k > 2 ){
			sub += cost[id[i]][id[i+k-1]];
		}
		ans = max(sub,ans);
	}
	return ans;
}

int dfs(int p,int prv){	
	done[p] = true;
	comp.push_back(p);
	for(int i : g[p] ){
		if( prv == i ) continue;
		if( done[i] ){ iscycle = true; continue; }
		else dfs(i,p);
	}
}
signed main(){
	
	while(cin >> n >> k >> s and n){
		for(int i = 0 ; i < n ; i++) g[i].clear();
		for(int i = 0 ; i < n ; i++){
			int x,y,z;
			cin >> x >> y >> z;
			ps[i] = {x,y,z};

		}
		int in[2010] = {};
		memset(cost,0,sizeof(cost));
		
		for(int i = 0 ; i < n ; i++){
			for(int j = i+1 ; j < n ; j++){
				if( check(ps[i],ps[j]) ){
					g[i].push_back(j);
					g[j].push_back(i);
					in[i]++;
					in[j]++;
					cost[i][j] = cost[j][i] = costf(ps[i],ps[j]);
				}
			}
		}
		memset(done,0,sizeof(done));
		long long ans = -2e18;
		for(int deg = 1 ; deg <= 2 ; deg++){
			for(int i = 0 ; i < n ; i++){
				if( !done[i] and in[i] <= deg ){
					iscycle = false;
					comp.clear();
					dfs(i,-1);
					//for( auto j : comp ) cout << j << " ";
					if( comp.size() < k ) continue;

					if( iscycle ) 
							comp.insert(comp.end(),comp.begin(),comp.end());
					ans = max(ans,f(comp));

				}
			}
		}
		if( ans == -2e18 ) cout << -1 << endl;
		else cout << 6 * s * s * k - ans << endl;
		//cout << 6*s*s*k << "|" << ans << endl;

	}
}