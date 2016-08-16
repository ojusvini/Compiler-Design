#include <iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

int main() {
	char gram[20][20];
	char gl[20];
	char gr[20][20];
	int n = 0;
	FILE *f;
	f=fopen("slr.txt","r");

	int r_n = 0;

	while(!feof(f)) {
        fscanf(f,"%s\n",gram[r_n]);
        r_n++;
	}

	for(int i = 0; i <r_n;i++) {
		cout<<gram[i]<<"\n";
	}

	//r_n = r_n-1;
	int prod_ct = 0;
	for(int i = 0; i <r_n;i++) {
		int rght = 0;
		gl[prod_ct] = gram[i][0];
		for(int j = 3; gram[i][j]!='\0';j++){
			if(gram[i][j]=='|') {
				gr[prod_ct][rght] = '\0';
				//cout<<gl[prod_ct]<<" "<<gr[prod_ct]<<"\n";
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

	for(int i = 0; i< prod_ct;i++) {
		cout<<gl[i]<<"->"<<gr[i]<<"\n";
	}
}
