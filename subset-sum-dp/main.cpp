#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a[] = {2,4,6,8,10};
    int W = 36;
    int n = sizeof(a)/sizeof(a[0]);

    bool dp[n][W+1];

        
    for(int i = 0; i<=W; i++){
	for(int j = 0; j<n; j++){
	    dp[j][i] = false;
	}
    }

    for(int i = 0; i<n; i++){
	for(int j = i; j<n; j++){
	    dp[j][a[i]] = true;
	}
    }

    for(int i = 0; i<=W; i++){
	for(int j = 1; j<n; j++){
	    if(i-a[j]>=0)
		dp[j][i] = dp[j][i] || dp[j-1][i-a[j]];
	    dp[j][i] = dp[j][i] || dp[j-1][i]; 
	}
    }

    cout<<dp[n-1][W]<<"\n";
    for(int i = 0; i<=W; i++){
	cout<<i<<" "<<dp[n-1][i]<<"\n";
    }
    return 0;
}
