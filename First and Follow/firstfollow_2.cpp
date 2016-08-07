#include<bits/stdc++.h>
using namespace std;

map<char,int>mp;
map<int,char>non_term_int;
map<char,int>mpforchecking;
string terminal[80];
vector<string> production[80];

map<int,set<char> >first;
map<int,set<char> >follow;

int l;

set<char> find_first(int id) {
	if(!first[id].empty()) {
		return first[id];
	}
	else {
		set<char>tempset;
		for(int i = 0;i < production[id].size();i++) {
		//	cout<<production[id][i]<<" ";
			for(int j = 0;j < production[id][i].size();j++) {
				char s = production[id][i][j];
			//	cout<<s;
				if(!mp[s]) {
					
					tempset.insert(s);
					break;
				}
				else {
					set<char>s1;
					if(s!=non_term_int[id]) {
						s1 = find_first(mp[s]);
					}
					int kk = 1;
					for (set<char>::iterator it=s1.begin(); it!=s1.end(); ++it) {
						if(*it!='#')
						tempset.insert(*it);
						else {
							kk = 0;
						}
					}
					if(kk==0&&production[id][i].size()-1==j) {
						tempset.insert('#');
					}
					if(kk==1) {
						break;
					}
				}
			}
		}
		first[id] = tempset;
	}
	return first[id];
}

void find_follow() {
	follow[0].insert('$');
	for(int i = 0;i <l;i++) {
		for(int j = 0;j < production[i].size();j++) {
			for(int k = 0;k < production[i][j].size();k++) {
				if(mpforchecking[production[i][j][k]]) {
					set<char>tempset;
					char x = production[i][j][k];
					if(k==production[i][j].size()-1) {
						for (set<char>::iterator it=follow[i].begin(); it!=follow[i].end(); ++it) {		
							follow[mp[production[i][j][k]]].insert(*it);
						}
					}
					for(int k1 = k+1;k1<production[i][j].size();k1++) {
							
						if(mpforchecking[production[i][j][k1]]) {
							
							set<char>ss = first[mp[production[i][j][k1]]];
							int kk = 1;
							for (set<char>::iterator it=ss.begin(); it!=ss.end(); ++it) {
  								if(*it!='#') {
  									tempset.insert(*it);
  								}
  								else {
  									kk = 0;
  								}
  							}
  							if(kk==1) {
  								break;
  							}
  							if(kk==0&&production[i][j].size()-1==k1) {
  								set<char>ss = follow[i];
  								for (set<char>::iterator it=ss.begin(); it!=ss.end(); ++it) {
  									tempset.insert(*it);
								}
  							}
						}
						else {
							tempset.insert(production[i][j][k1]);
							
							break;
						}
						
					}
					for (set<char>::iterator it=tempset.begin(); it!=tempset.end(); ++it) {		
							follow[mp[production[i][j][k]]].insert(*it);
						}
				}
			}
		}
	}
}
int main() {
	string line;
	ifstream myfile ("ff.txt");
	
	l = 0;
	if (myfile.is_open())	{
		while ( getline (myfile,line) )	{
			char c = line[0];
			if(!mp[c]) {
				mp[c] = l;
				mpforchecking[c] = l+1;
				non_term_int[l] = c;
				string s = "";
				s = s + c;
				
				terminal[l] = s;
				string temp="";
				for(int i = 3;i < line.size();i++) {
					if(line[i]!='|') {
						temp += line[i];
					}
					else {
						production[l].push_back(temp);
						temp.clear();
					}
				}
				production[l].push_back(temp);
				temp.clear();
				l++;	
			}
			else {
				int g = mp[c];
				string temp="";
				for(int i = 3;i < line.size();i++) {
					if(line[i]!='|') {
						temp += line[i];
					}
					else {
						production[g].push_back(temp);
						temp.clear();
					}
				}
				production[g].push_back(temp);
						temp.clear();
			}
		}
	}
	for(int i = 0;i<l;i++) {
		first[i] = find_first(i);
	}
	
	find_follow();
	find_follow();
	
	cout << "First and Follow\n";
	for(int i = 0;i < l;i++) {
		int j = 0;
		cout<<non_term_int[i]<<" ";
		cout<<" | ";
		
		for (std::set<char>::iterator it=first[i].begin(); it!=first[i].end(); ++it) {
  			cout<<*it<<" ";
  		}
  		cout<<" | ";
  		for (std::set<char>::iterator it=follow[i].begin(); it!=follow[i].end(); ++it) {
  			cout<<*it<<" ";
  		}
		cout<<endl;	
	}
}
