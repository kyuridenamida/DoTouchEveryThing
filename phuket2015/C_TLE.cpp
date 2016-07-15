#include <bits/stdc++.h>
using namespace std;
#define int long long
int uf[100010];
int root(int x){
	return x == uf[x] ? x : uf[x] = root(uf[x]);
}

int unite(int x,int y){
	x = root(x);
	y = root(y);
	if( x == y ) return 0;
	if( rand() & 1 ) swap(x,y);
	uf[x] = y;
	return 1;
}


int parent[1<<18][18];
int cost[1<<18][18];
int depth[1<<18];

vector< pair<int,int> > G[100010];
struct Edge{
	int a,b,c;
};
int N,M,Q;

int make_tree(int x,int d=0,int p=-1,int cst=0){
	parent[x][0] = p;
	depth[x] = d;
	cost[x][0] = cst;
	for(auto e : G[x] ){
		if( p != e.first ) make_tree(e.first,d+1,x,e.second);
	}
}
void init(){
	for(int i = 1 ; i < 18 ; i++){
		for(int j = 0 ; j < N ; j++){
			if( parent[j][i-1] != -1 ){
				parent[j][i] = parent[parent[j][i-1]][i-1];
				cost[j][i] = cost[j][i-1] + cost[parent[j][i-1]][i-1];
			}
		}
	}
}

int src[100010];

int id[100010];

int dist(int x,int y){
	if( depth[x] < depth[y] ) swap(x,y);
	
	int ans = 0;
	for(int i = 17 ; i >= 0 ; i--){
		if( (depth[x] - depth[y]) >> i & 1 ){
			ans += cost[x][i];
			x = parent[x][i];
		} 
	}
	if( x == y ) return ans;
	for(int i = 17 ; i >= 0 ; i--){
		if( parent[x][i] != parent[y][i] ){
			ans += cost[x][i];
			ans += cost[y][i];
			x = parent[x][i];
			y = parent[y][i];
		}
	}
	ans += cost[x][0];
	ans += cost[y][0];	
	return ans;
}

signed main(){
	int T;
	cin >> T;
	int tt = 1;
	while(T--){
		cout << "Case " << tt++ << ":" << endl;
		cin >> N >> M >> Q;
		for(int i = 0 ; i < N ; i++) uf[i] = i, G[i].clear();
		memset(parent,-1,sizeof(parent));
		memset(cost,0,sizeof(cost));
	
		int g[110][110];
		for(int i = 0 ; i < 110 ; i++)
			for(int j = 0 ; j < 110 ; j++)
				g[i][j] = 1e9;
		
		set<int> lp;
		vector< array<int,3> > es;
		for(int i = 0 ; i < M ; i++){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			--a,--b;
			if( unite(a,b) ){
				G[a].push_back({b,c});
				G[b].push_back({a,c});
				//cout << a+1 << "->" << b+1 << " " << c << endl;
			}else{
				es.push_back({a,b,c});
				lp.insert(a);
				lp.insert(b);
			}
		}
	
		int k = 0;
		for( auto j : lp ) id[j] = k, src[k] = j, k++;
		make_tree(0);
		
		init();
		for( auto e : es ){
			int a = id[e[0]];
			int b = id[e[1]];
			int c = e[2];
			g[a][b] = min(g[a][b],c);
			g[b][a] = min(g[b][a],c);				
		}
		//cout << dist(3-1,2-1) << "<<" << endl;
		for(int i = 0 ; i < k ; i++)
			for(int j = 0 ; j < k ; j++)
				g[i][j] = min(g[i][j],dist(src[i],src[j]));
		
		for(int i = 0 ; i < k ; i++)
			for(int j = 0 ; j < k ; j++)
				for(int x = 0 ; x < k ; x++)
					g[j][x] = min(g[j][i]+g[i][x],g[j][x]);
		//return 0;
		
		int da[110],db[110] = {};
		for(int i = 0 ; i < Q ; i++){
			int a,b;
			scanf("%d%d",&a,&b);
			--a,--b;
			if( a > b ) swap(a,b);
			/*if( memo.count({a,b}) ){
				cout << memo[{a,b}] << endl;
				continue;
			}*/
			long long ans = dist(a,b);
			//cout << a+1 << " " << b+1 << endl;
			
			for(int i = 0 ; i < k ; i++)
				da[i] = dist(a,src[i]),
				db[i] = dist(b,src[i]);
			for(int i = 0 ; i < k ; i++){
				for(int j = 0 ; j < k ; j++){
					ans = min(ans,(long long)da[i] + g[i][j] + db[j]);
				}
			}
			printf("%d\n",ans);
		}

	}
}