#include <iostream>
#include<stdio.h>
#include<string.h>
#include <stack>

using namespace std;

int i,j,k,m,n=0,o,p,ns=0,tn=0,rr=0,ch=0;
int prod_ct = 0;
char read[15][10],gl[15],gr[15][10],temp,templ[15],tempr[15][10],*ptr,temp2[5],dfa[15][15];
int reduce[15];

struct states
{
    char lhs[15],rhs[15][10];
    int n;
}I[15];

int compstruct(struct states s1,struct states s2)
{
    int t;
    if(s1.n!=s2.n)
        return 0;
    if( strcmp(s1.lhs,s2.lhs)!=0 )
        return 0;
    for(t=0;t<s1.n;t++)
        if( strcmp(s1.rhs[t],s2.rhs[t])!=0 )
            return 0;
    return 1;
}

void get_reduction()
{
    memset(reduce,0,sizeof(reduce));

    for(i=0;i<ns;i++){

        //printf("I %d ",i);
        int f2 = 0;
        for(j=0;j<I[i].n;j++) {
        if(f2 == 1) break;
            if(reduce[i]!=0 && reduce[i]!=-1) break;
            //printf("%s\n",I[i].rhs[j]);
            int len = strlen(I[i].rhs[j]);
            if(I[i].rhs[j][len-1]=='.'){
                //printf("%s\n",I[i].rhs[j]);
                for(int k = 0; k < prod_ct;k++) {
                    int flag = 0;
                    if(len-1 != strlen(gr[k])) {
                        flag = 1;
                    }
                    else {
                        for(int z = 0; z < len-1;z++) {
                            if(I[i].rhs[j][z]!=gr[k][z] ) {
                                flag = 1;
                            }
                        }
                    }
                    if(flag == 0) {
                        if(I[i].lhs[j] == gl[k]) {
                            f2 = 1;
                            reduce[i] = k;
                            //printf("reduce %d\n",reduce[i]);
                        }
                        /*f2 = 1;
                        reduce[i] = k;
                        printf("reduce %d\n",reduce[i]);*/
                    }
                    /*else {
                        reduce[ns] = -1;
                        printf("reduce %d\n",reduce[ns]);
                    }*/
                    //printf("%s\n",gr[k]);
                }
            }
        }
        if(f2 == 0) {
            reduce[i] = -1;
        }
    }
    reduce[1] = -2;
    /*for(i=0;i<ns;i++) {
        printf("I %d Reduce %d\n",i,reduce[i]);
    }*/
}
void moreprod()
{
    int r,s,t,l1=0,rr1=0;
    char *ptr1,read1[15][10];

    for(r=0;r<I[ns].n;r++)
    {
        ptr1=strchr(I[ns].rhs[l1],'.');
        t=ptr1-I[ns].rhs[l1];
        if( t+1==strlen(I[ns].rhs[l1]) )
        {
            l1++;
            continue;
        }
        temp=I[ns].rhs[l1][t+1];
        l1++;
        for(s=0;s<rr1;s++)
            if( temp==read1[s][0] )
                break;
        if(s==rr1)
        {
            read1[rr1][0]=temp;
            rr1++;
        }
        else
            continue;

        for(s=0;s<n;s++)
        {
            if(gl[s]==temp)
            {
                I[ns].rhs[I[ns].n][0]='.';
                I[ns].rhs[I[ns].n][1]='\0';
                strcat(I[ns].rhs[I[ns].n],gr[s]);
                I[ns].lhs[I[ns].n]=gl[s];
                I[ns].lhs[I[ns].n+1]='\0';
                I[ns].n++;
            }
        }
    }
}

void canonical(int l)
{
    int t1;
    char read1[15][10],rr1=0,*ptr1;
    for(i=0;i<I[l].n;i++)
    {
        temp2[0]='.';
        ptr1=strchr(I[l].rhs[i],'.');
        t1=ptr1-I[l].rhs[i];
        if( t1+1==strlen(I[l].rhs[i]) )
            continue;

        temp2[1]=I[l].rhs[i][t1+1];
        temp2[2]='\0';

        for(j=0;j<rr1;j++)
            if( strcmp(temp2,read1[j])==0 )
                break;
        if(j==rr1)
        {
            strcpy(read1[rr1],temp2);
            read1[rr1][2]='\0';
            rr1++;
        }
        else
            continue;

        for(j=0;j<I[0].n;j++)
        {
            ptr=strstr(I[l].rhs[j],temp2);
            if( ptr )
            {
                templ[tn]=I[l].lhs[j];
                templ[tn+1]='\0';
                strcpy(tempr[tn],I[l].rhs[j]);
                tn++;
            }
        }

        for(j=0;j<tn;j++)
        {
            ptr=strchr(tempr[j],'.');
            p=ptr-tempr[j];
            tempr[j][p]=tempr[j][p+1];
            tempr[j][p+1]='.';
            I[ns].lhs[I[ns].n]=templ[j];
            I[ns].lhs[I[ns].n+1]='\0';
            strcpy(I[ns].rhs[I[ns].n],tempr[j]);
            I[ns].n++;
        }

        moreprod();
        for(j=0;j<ns;j++)
        {
            //if ( memcmp(&I[ns],&I[j],sizeof(struct states))==1 )
            if( compstruct(I[ns],I[j])==1 )
            {
                I[ns].lhs[0]='\0';
                for(k=0;k<I[ns].n;k++)
                    I[ns].rhs[k][0]='\0';
                I[ns].n=0;
                dfa[l][j]=temp2[1];
                break;
            }
        }
        if(j<ns)
        {
            tn=0;
            for(j=0;j<15;j++)
            {
                templ[j]='\0';
                tempr[j][0]='\0';
            }
            continue;
        }

        dfa[l][j]=temp2[1];
        printf("\n\nI%d :",ns);
        for(j=0;j<I[ns].n;j++)
            printf("\n\t%c -> %s",I[ns].lhs[j],I[ns].rhs[j]);
        ns++;
        tn=0;
        for(j=0;j<15;j++)
        {
            templ[j]='\0';
            tempr[j][0]='\0';
        }
    }
}

int main()
{
    FILE *f;
    int l;
    char terminal[100];
	char non_terminal[100];
	int c_term = 0;
	int c_nterm = 0;

    for(i=0;i<15;i++)
    {
        I[i].n=0;
        I[i].lhs[0]='\0';
        I[i].rhs[0][0]='\0';
        dfa[i][0]='\0';
    }

    f=fopen("slr5.txt","r");

    char gram[20][20];
    int r_n = 0;

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

	n = prod_ct;

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

    printf("THE GRAMMAR IS AS FOLLOWS\n");
    for(i=0;i<n;i++)
        printf("\t\t\t\t%c -> %s\n",gl[i],gr[i]);

    I[0].lhs[0]='Z';
    char ab[3];
	ab[0] = '.';
	ab[1] = gl[0];
	ab[2] = '\0';
	strcpy(I[0].rhs[0],ab);
    I[0].n++;
    l=0;
    for(i=0;i<n;i++)
    {
        temp=I[0].rhs[l][1];
        l++;
        for(j=0;j<rr;j++)
            if( temp==read[j][0] )
                break;
        if(j==rr)
        {
            read[rr][0]=temp;
            rr++;
        }
        else
            continue;
        for(j=0;j<n;j++)
        {
            if(gl[j]==temp)
            {
                I[0].rhs[I[0].n][0]='.';
                strcat(I[0].rhs[I[0].n],gr[j]);
                I[0].lhs[I[0].n]=gl[j];
                I[0].n++;
            }
        }
    }
    ns++;

    printf("\nI%d :\n",ns-1);
    for(i=0;i<I[0].n;i++)
        printf("\t%c -> %s\n",I[0].lhs[i],I[0].rhs[i]);

    for(l=0;l<ns;l++)
        canonical(l);
	printf("\n");

    printf("\nDFA TABLE IS AS FOLLOWS\n\n\n");
    for(i=0;i<ns;i++)
    {
        printf("I%d : ",i);
        for(j=0;j<ns;j++)
            if(dfa[i][j]!='\0')
                printf("'%c'->I%d | ",dfa[i][j],j);
        printf("\n\n\n");
    }

    get_reduction();

    printf("\nPARSING TABLE IS AS FOLLOWS\n");
    printf("    ");
    for(i = 0; i < c_term;i++ ){
        printf("%c \t",terminal[i]);
    }
    printf("|\t");
    for(i = 0; i < c_nterm;i++ ){
        printf("%c \t",non_terminal[i]);
    }
    printf("\n");

    int dfa1[ns][c_term];
    int dfa2[ns][c_nterm];
    memset(dfa1,-1,sizeof(dfa1));
    memset(dfa2,-1,sizeof(dfa2));

    for(i=0;i<ns;i++)
    {
        printf("I%d:",i);
        int k  = 0;
        while(k<c_term) {
            int flag = 0;
            for(j=0;j<ns;j++) {
                if(dfa[i][j]!='\0') {
                    if(terminal[k] == dfa[i][j]) {
                        printf("s%d\t",j);
                        dfa1[i][k] = j;
                        flag = 1;
                    }
                }
            }
            if(flag == 0) {
                if(reduce[i]==-2 && k == c_term-1) {
                    printf("ac\t");
                }
                else if(reduce[i]==-2) {
                   printf("- \t");
                }
                else if(reduce[i]!=-1) {
                    printf("r%d\t",reduce[i]);
                }
                else {
                    printf("- \t");
                }
            }

            k++;
        }

        printf("|\t");

        k = 0;
        while(k<c_nterm) {
            int flag = 0;
            for(j=0;j<ns;j++) {
                if(dfa[i][j]!='\0') {
                    if(non_terminal[k] == dfa[i][j]) {
                        dfa2[i][k] = j;
                        printf(" %d\t",j);
                        flag = 1;
                    }
                }
            }
            if(flag == 0) {
                printf("- \t");
            }
            k++;
        }
        printf("\n");
    }

    //int reduce[ns];
    /*for(i=0;i<ns;i++) {
        for(j=0;j<c_term;j++) {
            printf("%d ",dfa1[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<ns;i++) {
        for(j=0;j<c_nterm;j++) {
            printf("%d ",dfa2[i][j]);
        }
        printf("\n");
    }*/

    char str[20];
    printf("Enter the string you want to parse : \n");
    scanf("%s",str);
    strcat(str,"$");
    // = "i+i";
    printf("Parsing : %s\n",str);
    //cout<<strlen(str);

    stack<int> state;
    stack<char> symbol;
    //stck.push('$');
    state.push(0);
    int i = 0;

    while(!(str[i]=='$'&&state.top()==1)) {

        int cur_st = state.top();

        //Position of terminal in j
        for( j = 0; j < c_term;j++) {
            if(str[i] == terminal[j]) {
                break;
            }
        }


        if(!isupper(str[i]) && dfa1[cur_st][j]!=-1) {
            printf("Shift\n");
            symbol.push(str[i]);
            state.push(dfa1[cur_st][j]);
            i++;
        }
        else if(reduce[cur_st]>-1){
            int prod_item = reduce[cur_st];
            printf("Reduce by %c -> %s\n",gl[prod_item],gr[prod_item]);
            int ct = strlen(gr[prod_item]);
            int z = 0;
            while(z<ct){
                symbol.pop();
                state.pop();
                z++;
            }
            symbol.push(gl[prod_item]);
            //state.push()
            int jj;
            for( jj = 0; jj < c_nterm;jj++) {
                if(gl[prod_item] == non_terminal[jj]) {
                    break;
                }
            }

            state.push(dfa2[state.top()][jj]);
        }
        else {
            printf("Error Detected\n");
            return 0;
        }
    }
	printf("Accepted\n");
    return 0;
}
