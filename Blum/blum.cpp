#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define changeAt 6

void insertionSort(vector<int> &a){

    for(int i= 0; i<a.size(); i++){
	int mini = i;
	for(int j=i+1; j<a.size(); j++){
	    if(a[mini]>a[j]){
		mini = j;
	    }
	}
	int temp = a[mini];
	a[mini] = a[i];
	a[i] = temp; 
    }
}

//Find kth smallest element from an array having distinct elements
int Blum(vector<int> a, int k){

    int n = a.size();
    if(k>n){
	return -1;
    }
    if(n<changeAt){
	insertionSort(a);
	return a[k-1];
    }
    else{
	//Thanks to Buddy Rohan, I forgot to sort the elements taken 5 at a time
	//Without this the complexity is screwed up.
	vector<int> aux;
	int my2d[a.size()/5 + 1][5];
	int row=-1;
	for(int i = 0; i<a.size(); i++){
	    if(i%5==0)
		row++;
	    my2d[row][i%5] = a[i];
	}
	for(int i= 0; i<=row; i++){
	    sort(my2d[i],my2d[i]+5);
	}
	
	for(int i = 0; i<=row; i++){
	    aux.push_back(my2d[i][2]);
	}
	//The algo works even without sorting but takes more time

	int m = Blum(aux,ceil(n/10.0));

	vector<int> lower, upper;

	for(int i=0; i<n; i++){
	    if(a[i]<m){
		lower.push_back(a[i]);
	    }
	    else if(a[i]>m){
		upper.push_back(a[i]);
	    }
	    else{
		//a[i] == m: true => Do Nothing
	    }
	}
	int sl = lower.size();
	int su = n - sl - 1; 
	if(k==sl+1){
	    return m;
	}
	else if(k <= sl){
	    return Blum(lower,k);
	}
	else{
	    //k > sl+1
	    return Blum(upper, k-sl-1);
	}
    }
}

void displayvec(vector<int> x){

    for(int i= 0; i<x.size(); i++){
	cout<<x[i]<<" ";
    }
}

int main(){

    static const int arr[] = {16,2,77,29,33,1,5,7,8};
    vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );

    cout<<Blum(vec,1)<<endl;
    cout<<Blum(vec,2)<<endl;
    cout<<Blum(vec,3)<<endl;
    cout<<Blum(vec,4)<<endl;
    cout<<Blum(vec,5)<<endl;
    cout<<Blum(vec,6)<<endl;
    cout<<Blum(vec,7)<<endl;
    cout<<Blum(vec,8)<<endl;
    cout<<Blum(vec,9)<<endl;
    
    return 0;
}
