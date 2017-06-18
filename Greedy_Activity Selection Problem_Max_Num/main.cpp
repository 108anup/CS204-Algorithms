#include <bits/stdc++.h>

using namespace std;

struct act{
    int s;
    int f;
    int idx;

    bool operator<(act b) const{
	return f<b.f;
    }
};

int main(){
    int s[] = {1,3,0,5,3,5,6,8,8,2,12};
    int f[] = {4,5,6,7,9,9,10,11,12,14,16};
    int n = sizeof(s)/sizeof(s[0]);

    vector<act> t;
    for(int i=0; i<n; i++){
	act e;
	e.s = s[i];
	e.f = f[i];
	e.idx = i;
	t.push_back(e);
    }

    sort(t.begin(), t.end());
    vector<act> selected;
    selected.push_back(t[0]);
    int last = t[0].f;
    for(int i= 1; i<t.size(); i++){
	if(t[i].s>=last){
	    selected.push_back(t[i]);
	    last = t[i].f;
	}
    }

    for(int i= 0; i<selected.size(); i++){
	cout<<selected[i].idx+1<<" ";
    }
    return 0;
}
