#include <bits/stdc++.h>
using namespace std;

int h(char c){
	if( c >= 'A' ) return c - 'A' + 10;
	else return c - '0';
}

char f(string s){
	return h(s[0])*16 + h(s[1]);	
}


int main(){
	string s;
	while(cin >> s){
		for(int i = 0 ; i < s.size() ; i += 2 )
			cout << f(s.substr(i,2));
		cout << endl;
	}
}