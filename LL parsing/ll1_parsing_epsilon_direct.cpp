#include<bits/stdc++.h>
using namespace std;

map<char,int>char_to_int;
map<char,int>char_to_int_terminal;
map<int,char>non_term_int;

map<char,int>check____map;
string store_t[80];

vector<string> gram_store[80];

map<int,set<char> >map_term_first;
map<int,set<char> >map_term_fol;

int n_ct;
char r1[15][10],gl[15],gr[15][10];

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
void get_first_follow() {
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

int main() {
	get_first_follow();
	char_to_int_terminal.clear();
	char gram[20][20];
    int r_n = 0;
	char terminal[100];
	char non_terminal[100];
	int c_term = 0;
	int c_nterm = 0;
	int i,j,k;
	FILE *f;
	f=fopen("ff.txt","r");

	int prod_ct = 0;
	while(!feof(f)) {
        fscanf(f,"%s\n",gram[r_n]);
        r_n++;
	}

	for(i = 0; i <r_n;i++) {
		cout<<gram[i]<<"\n";
	}

	prod_ct = 0;
	for(i = 0; i <r_n;i++) {
		int rght = 0;
		gl[prod_ct] = gram[i][0];
		for(int j = 3; gram[i][j]!='\0';j++){
			if(gram[i][j]=='|') {
				gr[prod_ct][rght] = '\0';
				prod_ct++;
				gl[prod_ct] = gl[prod_ct-1];
				rght = 0;
			}
			else {
				gr[prod_ct][rght] = gram[i][j];
				rght++;
			}

		}
		gr[prod_ct][rght]='\0';
		prod_ct++;
	}

	int n = prod_ct;
	
	cout<<"Grammar is\n";
	for(i = 0; i <n;i++) {
		cout<<gl[i]<<"->"<<gr[i]<<"\n";
	}
	
	for(i = 0; i < n; i++){
        j = 0;
        while(gr[i][j]!='\0'){
            if(!isupper(gr[i][j])) {
                int k = 0;
                int f = -1;
                while(k<c_term) {
                    if(terminal[k] == gr[i][j]) {
                        f = 0;
                        break;
                    }
                    k++;
                }
                if(f == -1) {
                    terminal[c_term] = gr[i][j];
                    c_term++;
                }
            }
            j++;
        }
	}

   terminal[c_term++] = '$';

    printf("Terminals are :\n");
    for(i=0;i<c_term;i++) {
        printf("%c ",terminal[i]);
        char_to_int_terminal[terminal[i]] = i;
    }
    printf("\n");

    for(i = 0; i < n; i++){
        int f1 = -1;
        int j =0;
        while(j<c_nterm) {
            if(non_terminal[j] == gl[i]) {
                f1 = 0;
                break;
            }
            j++;
        }
        if(f1 == -1) {
            non_terminal[c_nterm++] = gl[i];
        }
    }
    printf("Non Terminals are : \n");
    for(i = 0; i < c_nterm;i++ ){
        printf("%c ",non_terminal[i]);
    }
    printf("\n");
    
    int prod_count[c_nterm];
    int epsilon_present[c_nterm];
    memset(prod_count,0,sizeof(prod_count));
    memset(epsilon_present,-1,sizeof(epsilon_present));
    
    for(i=0;i<n;i++){
    	for(j=0;j<c_nterm;j++){
    		if(gl[i]== non_terminal[j]) {
    			if(gr[i][0]=='#') {
    				epsilon_present[j] = i;
				}
				else {
					prod_count[j]++;
				}
			}
		}
	}
	
	for(i=0;i<c_nterm;i++) {
		cout<<"Production count = "<<prod_count[i] <<" epsilon present = "<<epsilon_present[i]<<"\n";
	}
	
	int parsing_table[c_nterm][c_term];
	memset(parsing_table,-1,sizeof(parsing_table));
	
	for(i=0;i<c_nterm;i++) {
		if(prod_count[i]==1) {
			int idx = char_to_int[non_terminal[i]];
			set<char> first = map_term_first[idx];
			//cout<<first<<"\n";
			set<char>::iterator it = map_term_first[i].begin();				
			while(it != map_term_first[i].end()) {
				int non_term;
				for( j=0; j<c_term;j++) {
					if(terminal[j]==*it) {
						non_term = j;
						break;
					}
				}
				for( j=0; j<prod_ct;j++) {
					if(gl[j]==non_terminal[i]) break;
				}
				
				parsing_table[i][non_term] = j;
				++it;
			}
		}
		if(epsilon_present[i]>-1){
			int idx = char_to_int[non_terminal[i]];
			set<char> follow = map_term_fol[idx];
			set<char>::iterator it = map_term_fol[i].begin();
			for(;it != map_term_fol[i].end();++it) {
				int non_term;
				for( j=0; j<c_term;j++) {
					if(terminal[j] == *it) {
						non_term = j;
						break;
					}
				}
				
				parsing_table[i][non_term] = epsilon_present[i];
			}
		}
		if(prod_count[i]>1) {
			/*for(j=0;j<prod_ct;j++) {
				if(gl[j]==non_terminal[i]) {
					if(gr[j][0]!='#' && !isupper(gr[j][0])) {
						int idx = char_to_int_terminal[gr[j][0]];
						parsing_table[i][idx] = j;
					}
				}
			}*/
			
			set<char>::iterator it = map_term_first[i].begin();
			for(;it != map_term_first[i].end();++it) {
				for(int k=0;k<prod_ct;k++) {
					if(gl[k] == non_terminal[i]) {
						int len = strlen(gr[k]);
						//int flag = -1;
						for(int z = 0; z<len;z++) {
							if(!isupper(gr[k][z])) {				
								if(*it == gr[k][z]) {
									int loc = char_to_int_terminal[*it];
									parsing_table[i][loc] = k;
								}
								break;	
							}
							else if(isupper(gr[k][z])){
								int idx1 = char_to_int[gr[k][z]];
								bool is_in = map_term_first[idx1].find(*it) != map_term_first[idx1].end();
								
								if(is_in == true ) {
									int loc = char_to_int_terminal[*it];
									parsing_table[i][loc] = k;
								}
								
								if(map_term_first[idx1].find('#') != map_term_first[idx1].end()){
									continue;
								}
								else break;
							}
							
						}
					}
				}
			}
		}
		
	}
	
	cout<<"Parsing Table\n";
	for(j=0;j<c_term;j++) {
		if(terminal[j]!='#')
			cout<<terminal[j]<<" | ";	
	}
	cout<<"\n";
	for(i=0;i<c_nterm;i++) {
		for(j=0;j<c_term;j++) {
			if(terminal[j]!='#') {
				if(parsing_table[i][j]==-1) {
					cout<<"- | ";
				}
				else {
					cout<<parsing_table[i][j]<<" | ";
				}
			}
				
		}
		cout<<"\n";
	}
	
	printf("Input the string you want to parse\n");
	char str[25];
	scanf("%s",str);
	strcat(str,"$");
	printf("The string that will be parsed %s \n",str);
	stack <char> st;
	st.push('$');
	st.push(gl[0]);
	i = 0;
	while(!(st.top()=='$' && str[i]=='$')) {
		char cur_sym = st.top();
		st.pop();
		if(str[i]==cur_sym) {
			i++;
			cout<<"Matched "<<cur_sym<<"\n";
		}
		else {
			int i_nt = char_to_int[cur_sym];
			int i_t = char_to_int_terminal[str[i]];
			//printf("%d %d\n",i_nt,i_t);
			int r_no = parsing_table[i_nt][i_t];
			if(r_no == -1) {
				printf("Error Detected\n");
				return 0;
			}
			//cout<<r_no<<"\n";
			cout<<"output "<<gl[r_no]<<"->"<<gr[r_no]<<"\n";
			int ln = strlen(gr[r_no]);
			if(gr[r_no][0]!='#'){
				for(int z = ln-1; z>=0;z--){
					st.push(gr[r_no][z]);
				}
			}	
		}
	}
	cout<<"Accepted\n";
	return 0;
	//cout<<
}
