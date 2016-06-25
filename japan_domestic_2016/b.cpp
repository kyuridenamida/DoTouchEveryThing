#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	while(cin >> N && N ){
		map<char,int> memo;
		vector<char> c(N);
		for(int i = 0 ; i < N ; i++) cin >> c[i];
		for(int i = 0 ; i < N ; i++){
			memo[c[i]]++;
			int rem = N - i - 1;

			int cnt = 0;
			int val = -1;
			char cand;
			for(int j = 0 ; j < 26 ; j++){	
				if( val < memo[j+'A'] ){
					cnt = 1;
					val = memo[j+'A'];
					cand = j+'A';
				}else if( val == memo[j+'A'] ){
					cnt++;
				}
			}
			bool f = true;
			for(int j = 0 ; j < 26 ; j++){
				if( cand != j + 'A' and memo[j+'A'] + rem >= val ){
					f = false;
				}
			}
			if(f){
				cout << cand << " " << i+1 << endl;
				goto exit;
			}



		}
		cout << "TIE" << endl;
		exit:;

	}
}