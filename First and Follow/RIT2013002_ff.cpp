#include<stdio.h>
#include<ctype.h>
#include <string.h>
#include <iostream>

using namespace std;

/*epsilon denoted by 0*/

char prod[100][100];

struct first_arr {
    int n;
    char fir[50];
};

struct follow_arr {
    int n;
    char foll[50];
};

int n;
int col;
char nt[200];

struct follow_arr follow[50];
struct first_arr first[50];
void find_first(char x, char y);
void find_follow(char x, char y);
void follow_op(char x, char y);
void first_op(char x, char y);


int main()
{
    int i, j, c, ctr;
    char ip;
    char b[100]; 
    
	printf("Enter the No. of Productions: ");
	scanf("%d", &n);

    printf("Enter the Productions in Format E->F+G\n");
    
	for (i = 0; i < n; i++) {
    	scanf("%s",prod[i]);  
    }
    
    for (i = 0; i < 200; i++) {
    	nt[i] = '-1';
    }
    
    int k = 0;
    for (i = 0; i < n; i++) {
    	for (j = 0; j < strlen(prod[i]); j++) {
    		if (!isupper(prod[i][j]) && (prod[i][j] != '-') && (prod[i][j] != '>') && (prod[i][j] != '0'))  {
    			if (nt[prod[i][j] - '0'] != -1)
    				nt[k++] = prod[i][j];
    		}			
    	}
    }
    
    c = 0;
	ctr = 0;
    for (i = 0; i < n; i++) {
		c = 0;
		for (j = 0; j <= i; j++) {
			if(prod[i][0] == b[j]) {
				c = 1;    
				break;
		    }    
        }
	    if(c !=1) {
	      b[ctr] = prod[i][0];
	      ctr++;
	    }               
    }

    for (i = 0; i < ctr; i++) {
		col = 1;
    	first[i].fir[0] = b[i];
    	first[i].n = 0;
    	find_first(b[i], i);
    }
    
    for (i = 0; i < ctr; i++) {
    	col = 1;
    	follow[i].foll[0] = b[i];
    	follow[i].n = 0;
    	find_follow(b[i], i);
     }

   printf("\n");
   for (i = 0;i < ctr; i++) {
	    for (j = 0; j <= first[i].n; j++) {
	            if (j == 0)
	                printf("FIRST (%c) = {",first[i].fir[j]);
	            else
	                printf("%c,",first[i].fir[j]);
	    }
	    printf("}\n");
    } 
    
    for (i = 0; i < k; i++) {
		printf("FIRST (%c) = {%c}\n", nt[i], nt[i]);
	}
	
	printf("\n");
   
   for (i = 0;i < ctr; i++) {
	    for (j = 0; j <= follow[i].n; j++) {
	            if (j == 0)
	                printf("FOLLOW (%c) = {",follow[i].foll[j]);
	            else
	                printf("%c,", follow[i].foll[j]);
	    }
	    printf("}\n");
   } 

}

void find_first(char ip, char pos)
{
    int i;
    for (i = 0; i < n; i++) {
        if(ip == prod[i][0]) {
            if(isupper(prod[i][3])) {
                find_first(prod[i][3], pos);
            }
            else {
		        first[pos].fir[col]=prod[i][3];
		        first[pos].n++;
		        col++;
	    	}
        }
    }
}

void find_follow(char ip, char row)
{   
	int i, j;
	
    if (row == 0 && col == 1) {
        follow[row].foll[col]= '$';
        col++;
        follow[row].n++;
    }

    for (i = 0; i < n; i++) {
        for (j = 3; j < 7; j++) {
            if (prod[i][j] == ip) {
                if(prod[i][j+1] == '\0') {
                    if(prod[i][j] != prod[i][0]) {
                        follow_op(prod[i][0],row);
                    }
                }
                else if(isupper(prod[i][j+1])) {
					if(prod[i][j+1] != prod[i][0])
                        first_op(prod[i][j+1],row);                                     
                }
                else {
                    follow[row].foll[col] = prod[i][j+1];  
                    col++;
                    follow[row].n++;
                }   
            }
        }
    }   
}

void follow_op(char ip, char row)
{   
	int i, j;
	
    for (i = 0; i < 5; i++) {
        if (ip == follow[i].foll[0]) {
            for (j = 1; j <= follow[i].n;j++) {
                follow[row].foll[col] = follow[i].foll[j];
                col++;
                follow[row].n++;
            }
        }
    }   
}

void first_op(char ip, char row)
{   
	int i, j;
	
    for (i = 0;i < 5; i++) {
        if (ip == first[i].fir[0]) {
            for (j = 1;j <= first[i].n;j++) {
                if(first[i].fir[j] != '0') {
                    follow[row].foll[col] = first[i].fir[j];
                    follow[row].n++;
                    col++;                  
                }
                else
                    follow_op(ip, row);
            }
        }
    }
}




