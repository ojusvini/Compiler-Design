#include<bits/stdc++.h>
using namespace std;

map<char,int>char_to_int;
map<int,char>non_term_int;

map<char,int>check____map;
string store_t[80];

vector<string> gram_store[80];

map<int,set<char> >map_term_first;
map<int,set<char> >map_term_fol;

int n_ct;

void mp_t() {
	map_term_fol[0].insert('$');
}

void get_fol() {
	int i,j,k;
	mp_t();
	
	for( i = 0; i < n_ct; i++) {
		int gmss = 	gram_store[i].size();	
		for( j = 0; j < gmss; j++) { 
			
			for( k = 0; k < gram_store[i][j].size(); k++) {
				
				if(check____map[gram_store[i][j][k]]) {
					set<char>arr;
					
					if(k == gram_store[i][j].size()-1) {
						set<char>::iterator it = map_term_fol[i].begin();
						
						while(it != map_term_fol[i].end()) {
							map_term_fol[char_to_int[gram_store[i][j][k]]].insert(*it);
							++it;
						}
					}
					
					for(int z = k+1; z<gram_store[i][j].size(); z++) {
							
						if(check____map[gram_store[i][j][z]]) {
							
							set<char> g = map_term_first[char_to_int[gram_store[i][j][z]]];
							
							int lo = 1;
							set<char>::iterator it = g.begin();
							
							while ( it!=g.end()) {
								if(*it!='#') {
  									arr.insert(*it);
  								}
								else {
  									lo = 0;
  								}
  								++it;
  							}
  							
  							if(lo == 1) {
  								break;
  							}
  							
  							if( lo == 0 && gram_store[i][j].size() - 1 == z ) {
  								set<char>g = map_term_fol[i];
  								
  								set<char>::iterator it;
  								for (it = g.begin(); it!=g.end(); ++it) {
  									arr.insert(*it);
								}
  							}
						}
						else {
							arr.insert(gram_store[i][j][z]);
							break;
						}
						
					}
					
					set<char>::iterator it;
					
					for (it=arr.begin(); it!=arr.end(); ++it) {		
							map_term_fol[char_to_int[gram_store[i][j][k]]].insert(*it);
					}
					
				}
			}
		}
	}
}

set<char> find_first(int num)  {	
	int i, j, flag;
	char ch;
	
	if ( !map_term_first[num].empty() ) {
		return map_term_first[num];
	}
	else {	
		set <char> remm;
		for ( i = 0; i < gram_store[num].size(); i++) {
			for ( j = 0; j < gram_store[num][i].size(); j++) {
				
				ch = gram_store[num][i][j];
				if( !char_to_int[ch] ) {
					
					remm.insert(ch);
					break;
				}
				else {
					
					set <char> find_first1;
					if (ch != non_term_int[num] ) {
						find_first1 = find_first( char_to_int[ch] );
					}
					
					flag = 1;
					
					set<char>::iterator it;
					
					it = find_first1.begin();
					while(it != find_first1.end()) {
						
						if ( *it != '#') {
							remm.insert(*it);
						}
						else {
							flag = 0;
						}
						
						it++;
					}
					
					if ( flag == 0 && gram_store[num][i].size() - 1 == j ) {
								remm.insert('#');
					}
					if (flag == 1) break;
				}
			}
		}
		
		map_term_first[num] = remm;
	}
	
	return map_term_first[num];
}

int main() {
	
	string str1;
	
	ifstream myfile ("ff.txt");
	
	n_ct = 0;
	
	if (myfile.is_open())	{
		
		while ( getline (myfile,str1) )	{
			char c = str1[0];
			
			if(!char_to_int[c]) {
				char_to_int[c] = n_ct;
				check____map[c] = n_ct+1;
				non_term_int[n_ct] = c;
				
				string x = "";
				x = x + c;
				
				store_t[n_ct] = x;
				
				string remm = "";
				
				int i;
				for(i = 3;i < str1.size();i++) {
					if( str1[i] != '|') {
						remm += str1[i];
					}
					else {
						gram_store[n_ct].push_back(remm);
						remm.clear();
					}
				}
				
				gram_store[n_ct].push_back(remm);
				remm.clear();
				n_ct++;	
			}
			else {
				int g = char_to_int[c];
				string remm = "";
				int y = 3;
				while(y < str1.size()) {
					if(str1[y]!='|') {
						remm += str1[y];
					}
					else {
						gram_store[g].push_back(remm);
						remm.clear();
					}
					y++;
				}
				gram_store[g].push_back(remm);
				remm.clear();
			}
		}
	}
	
	for(int y = 0;y<n_ct;y++) {
		map_term_first[y] = find_first(y);
	}
	
	get_fol();
	get_fol();
	
	set<char>::iterator it;
	
	cout << "First and Follow\n";
	for(int i = 0;i < n_ct ;i++) {
		int j = 0;
		cout<<non_term_int[i]<<" ";
		cout<<" | ";
		
		it=map_term_first[i].begin();
		
		for (; it!=map_term_first[i].end(); ++it) {
  			cout<<*it<<" ";
  		}
  		cout<<" | ";
  		for ( it = map_term_fol[i].begin(); it != map_term_fol[i].end(); ++it) {
  			cout<<*it<<" ";
  		}
  		cout<<"\n";
	}
}
