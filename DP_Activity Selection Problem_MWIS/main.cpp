#include <bits/stdc++.h>

using namespace std;

const int START = 1;
const int FINISH = 2;

struct elt{
    int time;
    int type;
    int idx;

    bool operator<(elt b) const{
	if(time == b.time){
	    if(type == FINISH)
		return true;
	}
	return time<b.time;
    }
};

void print_solution(int best_last, int prev[]){
    if(best_last>=0){
	print_solution(prev[best_last],prev);
	cout<<best_last+1<<" ";
    }
}

int main(){
    int s[] = {1,3,0,5,3,5,6,8,8,2,12};
    int f[] = {4,5,6,7,9,9,10,11,12,14,16};
    int n = sizeof(s)/sizeof(s[0]);

    vector<elt> t;
    for(int i=0; i<n; i++){
	elt e;
	
	e.time = s[i];
	e.type = START;
	e.idx = i;
	t.push_back(e);
	
	e.time = f[i];
	e.type = FINISH;
	t.push_back(e);
    }

    sort(t.begin(), t.end());

    int best_till_now = 0;
    int best_last = -1;
    int prev[n];
    int best_incl[n];

    for(int i=0; i<t.size(); i++){
	int idx = t[i].idx;
	if(t[i].type==START){
	    best_incl[idx] = best_till_now + f[idx] - s[idx];
	    prev[idx] = best_last;
	}
	else{
	    if(best_incl[idx]>best_till_now){
		best_till_now = best_incl[idx];
		best_last = idx;
	    }
	}
    }

    print_solution(best_last,prev);
    return 0;
}
