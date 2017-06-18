#include <bits/stdc++.h>

using namespace std;

const int max_size = 1e3+10;
const double eps = 1e-7;

void print_tree(int **root, int i, int j){
	if(i>=j){
		if(i==j){
			cout<<i;
		}
		else{
			int r = root[i][j];
			cout<<"(";
			print_tree(root, i, r-1);
			cout<<")"<<r<<"(";
			print_tree(root, r+1, j);
			cout<<")";
		}
	}
}

int main(){
	double p[] = {-1.0,0.15,0.10,0.05,0.10,0.20};
	double q[] = {0.05,0.10,0.05,0.05,0.05,0.10};
	int n = sizeof(p)/sizeof(p[0])-1;
	
	double e[n+2][n+1];
	double pi[n+2][n+1];
	int **root = new int*[n+1];
	for (int i = 0; i <= n; ++i){
		root[i] = new int[n+1];
	}

	for (int i = 1; i <= n+1; ++i){
		e[i][i-1] = q[i-1];
		pi[i][i-1] = q[i-1];
	}

	for (int l = 1; l <= n; ++l) for (int i = 1; i <= n-l+1; ++i){
		int j = i+l-1;
		pi[i][j] = pi[i][j-1] + p[j] + q[j];
		e[i][j] = INT_MAX;
		for (int r = i; r <=j; ++r){
			double current = pi[i][j] + e[i][r-1] + e[r+1][j];
			if(current < e[i][j] - eps){
				root[i][j] = r;
				e[i][j] = current;
			}
		}
	}

	print_tree(root, 1, n);
	cout<<"\nSearch Cost: "<<e[1][n]<<endl;

	for (int i = 1; i <= n+1; ++i){
		for (int j = i-1; j <=n; ++j){
			cout<<e[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<endl;
	for (int i = 1; i <= n+1; ++i){
		for (int j = i-1; j <=n; ++j){
			cout<<pi[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<endl;
	for (int i = 1; i <= n; ++i){
		for (int j = i; j <=n; ++j){
			cout<<root[i][j]<<" ";
		}
		cout<<"\n";
	}

	return 0;
}