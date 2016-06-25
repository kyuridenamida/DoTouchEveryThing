#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i = 0 ; i < (n) ; i++)
char c1[200][200];
char c2[200][200];
int w1,h1,w2,h2;

struct NODE{
	vector<NODE*> ch;
};

struct P{
	int x,y;
};

int dx[8] = {1,0,-1,0,-1,1,-1,1};
int dy[8] = {0,1,0,-1,-1,1,1,-1};
// white == '.'
int done[200][200];

int px,py;
void get_component(int x,int y,vector<P> &look,char c[200][200],char color){
	if( x < 0 || y < 0 || x >= 200 || y >= 200 || c[y][x] != color ) return;
	if( done[y][x] ) return;
	done[y][x] = true;
	look.push_back({x,y});
	for(int i = 0 ; i < 4 * (1+c[y][x]) ; i++ )
		get_component(x+dx[i],y+dy[i],look,c,color);
}
NODE* dfs(int x,int y,char c[200][200],char color){
	vector<P> look;
	NODE *root = new NODE();
	px = x;
	py = y;
	get_component(x,y,look,c,color);
	//cout << x << " " << y << " " << look.size() << "(" << (int)color << ")" << endl;
	//if( x != 0 or y != 0 )
	//for( auto p  : look )
	//	cout << p.x << " " << p.y << endl;
	for( auto p : look ){
		
		for(int i = 0 ; i < 8 ; i++ ){
			int tx = p.x+dx[i];
			int ty = p.y+dy[i];
			//if( p.x == 5 and p.y == 1 )  cout << tx << " " << ty << "|" << done[ty][tx] << endl;
			//cout << tx << " " << ty << "|" << (int)c[ty][tx] << endl;
			if( !(tx < 0 || ty < 0 || tx >= 200 || ty >= 200) and !done[ty][tx] and c[ty][tx] != color){
				//assert(c[ty][tx] != color );
				root->ch.push_back(dfs(tx,ty,c,color^1));
			}
		}
	}
	return root;
}
string f(NODE *root){
	vector<string> ans;

	for( auto c : root->ch ){
		ans.push_back(f(c));
	}

	sort(ans.begin(),ans.end());
	string r;
	for( auto t : ans) r += t;
	return "(" + r + ")";
}
int main(){
	while( cin >> h1 >> w1 && h1 ){
		for(int i = 0 ; i < 200 ; i++)
			for(int j = 0 ; j < 200 ; j++)
				c1[i][j] = c2[i][j] = 0;
		for(int i = 0 ; i < h1 ; i++)
			for(int j = 0 ; j < w1 ; j++)
				cin >> c1[i+1][j+1], c1[i+1][j+1] = c1[i+1][j+1] == '#';
		cin >> h2 >> w2;
		for(int i = 0 ; i < h2 ; i++)
			for(int j = 0 ; j < w2 ; j++)
				cin >> c2[i+1][j+1], c2[i+1][j+1] = c2[i+1][j+1] == '#';
		memset(done,0,sizeof(done));
		NODE *root = dfs(0,0,c1,0);
		//return 0;
		//cout << "====" << endl;
		memset(done,0,sizeof(done));
		NODE *root2 = dfs(0,0,c2,0);
		if( f(root) == f(root2) ){
			cout << "yes" << endl;
		}else{
			cout << "no" << endl;
		}

	}
}