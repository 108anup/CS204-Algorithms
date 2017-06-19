#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

void lexicographic_sort(vector<string> &s){

    //PREPROCESSING START

    int lmax=-1;
    vector<pair<int,char> > pairs;
    for(int i=0; i<s.size(); i++){
	int len = s[i].length();
	for(int j=0; j<len; j++){
	    pairs.push_back(make_pair(j+1,s[i][j]));
	}
	if(len>lmax)
	    lmax = s[i].length();
    }

    vector<string> s_length[lmax+1];
    for(int i= 0; i<s.size(); i++){
	s_length[s[i].length()].push_back(s[i]);
    }
    

    //assuming the strings are made up of alphabets 
    vector<pair<int,char> > buckets_char[26];
    for(int i=0; i<pairs.size(); i++){
	buckets_char[int(pairs[i].second - 'a')].push_back(pairs[i]);
    }

    pairs.clear();
    for(int i=0; i<26; i++){
	for(int j =0; j<buckets_char[i].size(); j++){
	    pairs.push_back(buckets_char[i][j]);
	}
    }

    vector<pair<int,char> > buckets_int[lmax+1];
    for(int i=0; i<pairs.size(); i++){
	buckets_int[pairs[i].first].push_back(pairs[i]);
    }

    pairs.clear();
    for(int i=0; i<lmax+1; i++){
	for(int j =0; j<buckets_int[i].size(); j++){
	    pairs.push_back(buckets_int[i][j]);
	}
    }

    vector<char> nonempty[lmax+1];
    nonempty[pairs[0].first].push_back(pairs[0].second);
    for(int i = 1; i<pairs.size(); i++){
	if(pairs[i]!=pairs[i-1]){
	    nonempty[pairs[i].first].push_back(pairs[i].second);
	}
    }

    //PREPROCESSING DONE
    deque<string> q;
    for(int l = lmax-1; l>=0; l--){
	for(int i = 0; i<s_length[l+1].size(); i++){
	    q.push_front(s_length[l+1][i]);
	}
	vector<string> bucket[26];
	while(!q.empty()){
	    string f = q.front();
	    q.pop_front();
	    bucket[int(f[l]-'a')].push_back(f);
	}
	for(int j = 0; j<nonempty[l+1].size(); j++){
	    for(int k = 0; k<bucket[int(nonempty[l+1][j]-'a')].size(); k++){
		q.push_back(bucket[int(nonempty[l+1][j]-'a')][k]);
	    }
	}
    }

    s.clear();
    while(!q.empty()){
	string f = q.front();
	q.pop_front();
	s.push_back(f);
    }
}

int main(){

    vector <string> s;

    s.push_back("first");
    s.push_back("second");
    s.push_back("q");
    s.push_back("abc");
    s.push_back("bbb");
    s.push_back("a");
    s.push_back("anup");

    lexicographic_sort(s);

    for(int i= 0; i<s.size(); i++){
	cout<<s[i]<<endl;
    }
    
    return 0;
}
