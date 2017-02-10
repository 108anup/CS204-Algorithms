#include <bits/stdc++.h>

using namespace std;

const int SIZE = 1e3 + 5;
int lcs[SIZE][SIZE];
int direction[SIZE][SIZE];

const int UP = 1;
const int LEFT = 2;
const int DIAG = 3;

int compute_lcs(string a, string b){
    int n= a.length();
    int m = b.length();
    
    for(int i = 0; i<=n; i++){
	lcs[i][0] = 0;
    }
    
    for(int i = 0; i<=m; i++){
	lcs[0][i] = 0;
    }

    for(int i = 1; i<=n; i++){
	for(int j = 1; j<=m; j++){
	    lcs[i][j] = lcs[i-1][j];
	    direction[i][j] = UP;

	    if(lcs[i][j-1]>lcs[i][j]){
		lcs[i][j] = lcs[i][j-1];
		direction[i][j] = LEFT;
	    }

	    if(a[i-1] == b[j-1] && (lcs[i-1][j-1] +1)>lcs[i][j]){
		lcs[i][j] = lcs[i-1][j-1] +1;
		direction[i][j] = DIAG;
	    }
	}
    }
}

void print_lcs(string a, int i, int j){
    if(i>0 && j>0){
	if(direction[i][j]==DIAG){
	    print_lcs(a,i-1,j-1);
	    cout<<a[i-1];
	}
	else if(direction[i][j] == UP){
	    print_lcs(a,i-1,j);
	}
	else{
	    print_lcs(a,i,j-1);
	}
    }
}

int main()
{

    string a = "abababcabcbabdbcbdabc";
    string b = "abcbdbhcbdbakcba";

    int n= a.length();
    int m = b.length();
    
    compute_lcs(a,b);
    print_lcs(a,n,m);
    
    return 0;
}
