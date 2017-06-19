#include <bits/stdc++.h>

using namespace std;

#define DISJOINT

int const N_MAX = 105;

struct task{
    int idx;
    int deadline;
    int profit;

    friend bool operator<(task &A, task &B){
	return A.profit > B.profit;
    }
};

int t;
int n;
task taskList[N_MAX];

#ifdef DISJOINT
struct node{
    node* parent;
    int rank;
    int time;
};

class disjointSet{
public:
    node **slotList;
    int num;

    disjointSet(int totalTime){
	slotList = new node*[totalTime+1];
	for(int i = 0; i<totalTime+1; i++){
	    slotList[i] = makeSet(i);
	}
	num = totalTime+1;
    }
    
    node* makeSet(int t){
	node *p = new node;
	p->parent = p;
	p->rank = 0;
	p->time = t;
    }

    node* findSet(node *n){
	if(n->parent == n)
	    return n;
	else
	    return n->parent = findSet(n->parent);
    }

    node* unionSet(node *x, node *y){
	y->parent = x;
	return x;
    }
    
    void clear(){
	for(int i = 0; i<num; i++){
	    slotList[i]->parent = slotList[i];
	}
    }
};

disjointSet sl(N_MAX);

bool independent(task A){
    int deadline = A.deadline;
    node* latest = sl.findSet(sl.slotList[deadline]);
    if(latest->time == 0)
	return false;
    else{
	sl.unionSet(sl.slotList[latest->time-1], latest);
	return true;
    }
}

#endif

#ifndef DISJOINT
bool dead[N_MAX];

bool independent(task A){
    int deadline = A.deadline;
    while(dead[deadline]){
	deadline--;
    }
    if(deadline == 0)
	return false;
    else{
	dead[deadline] = true;
	return true;
    }
}
#endif

int main()
{
    cin>>t;

    while(t--){
#ifndef DISJOINT
	memset(dead, false, sizeof(dead));
#endif
#ifdef DISJOINT
	sl.clear();
#endif
	cin>>n;
	task A;
	int idx, deadline, profit;
	for(int i = 0; i<n; i++){
	    cin>>idx>>deadline>>profit;
	    A.idx = idx;
	    A.deadline = deadline;
	    A.profit = profit;
	    taskList[i] = A;
	}

	sort(taskList, taskList + n);

	int totalProfit = 0;
	int numTasks = 0;
	
	for(int i = 0; i<n; i++){
	    if(independent(taskList[i])){
		numTasks++;
		totalProfit+=taskList[i].profit;
	    }
	}
	cout<<numTasks<<" "<<totalProfit<<"\n";
    }
    return 0;
}
