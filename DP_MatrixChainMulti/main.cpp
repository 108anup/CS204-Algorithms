#include <bits/stdc++.h>

using namespace std;

int const size = 1000;
int const inf = (1<<31)-1;
int m[size][size];
int breakat[size][size];

void matrix_chain_multiplication_bottomUp(int p[], int n){
    for(int i= 0; i<n; i++){
	m[i][i] = 0;
    }
    for(int l = 2; l<=n; l++){
	for(int i = 0; i<n-l+1; i++){
	    int j= i+l-1;
	    m[i][j] = inf;
	    for(int k = i; k<j; k++){
		int instcost = m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];
		if(m[i][j] > instcost){
		    m[i][j] = instcost;
		    breakat[i][j] = k;
		}
	    }
	}
    }
}

int matrix_chain_multiplication_recursive(int p[], int n, int i, int j){
    if(i==j){
	m[i][j] = 0;
	return 0;
    }
    if(m[i][j] == inf){
	for(int k = i; k<j; k++){
	    int instcost = matrix_chain_multiplication_recursive(p,n,i,k) + matrix_chain_multiplication_recursive(p,n,k+1,j) + p[i]*p[k+1]*p[j+1];
	    if(m[i][j]>instcost){
		m[i][j] = instcost;
		breakat[i][j]=k;
	    }
	}
    }
    return m[i][j];
    
}

void print_mat(int n){
    for(int i = 0; i<n; i++){
	for(int j = i+1; j<n; j++){
	    cout<<m[i][j]<<" "<<"("<<i<<","<<j<<")";
	}
	cout<<"\n";
    }

    cout<<"\n\n";
    
    for(int i = 0; i<n; i++){
	for(int j = i+1; j<n; j++){
	    cout<<breakat[i][j]<<" ";
	}
	cout<<"\n";
    }
}

void build(int i, int j){
    if(i==j){
	cout<<"A"<<i+1;
    }
    else{
	cout<<"(";
	build(i,breakat[i][j]);
	build(breakat[i][j]+1,j);
	cout<<")";
    }
}

int main()
{
    int n = 6;
    int p[n+1] = {30,35,15,5,10,20,25};

    matrix_chain_multiplication_bottomUp(p,n);
    print_mat(n);
    build(0,n-1);

    for(int i= 0; i<size; i++){
	for(int j = 0; j<size; j++){
	    m[i][j] = inf;
	}
    }
    cout<<endl;
    matrix_chain_multiplication_recursive(p,n,0,n-1);
    print_mat(n);
    build(0,n-1);
    
    return 0;
}
