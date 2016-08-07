#include<bits/stdc++.h>
using namespace std;

char input_gram[100][100];
int col;
int num_of_prod;

//Store the first of all terminals
struct first_store
{
	int n;
	char firT[50];
};

//Store the follow of all non terminals
struct follow_store
{
	int n;
	char folT[50];
};
struct follow_store follow[50];
struct first_store first[50];

void follow_table_op(char ip,char row)
{   int i,j;
	for(i=0;i<num_of_prod-3;i++) {
		if(ip == follow[i].folT[0])
		{
			for(j=1;j<=follow[i].n;j++)
			{
				follow[row].folT[col] = follow[i].folT[j];
				col++;
				follow[row].n++;
			}
		}
	}
}
void first_table_operation(char ip,char row)
{
	int i,j;
	for(i=0;i<5;i++)
	{
		if(ip == first[i].firT[0])
		{
			for(j=1;j<=first[i].n;j++)
			{
				if(first[i].firT[j] != '0')
				{
					follow[row].folT[col] = first[i].firT[j];
					follow[row].n++;
					col++;
				}
				else
				{
					follow_table_op(ip,row);
				}
			}
		}
	}
}

void first_calc(char ip,char pos)
{
	int i;
	for(i=0;i<num_of_prod;i++)
	{
		if(ip == input_gram[i][0])
		{
			if(isupper(input_gram[i][3]))
			{
				first_calc(input_gram[i][3],pos);
			}
			else
			{

				first[pos].firT[col]=input_gram[i][3];
				first[pos].n++;
				col++;
			}
		}
	}
}

void findFollow(char ip,char row)
{   int i,j;
	if(row==0 && col==1)
	{
		follow[row].folT[col]= '$';
		col++;
		follow[row].n++;
	}
	for(i=0;i<num_of_prod;i++)
	{
		for(j=3;j<num_of_prod-1;j++)
		{
			if(input_gram[i][j] == ip)
			{
				if(input_gram[i][j+1] == '\0')
				{
					if(input_gram[i][j] != input_gram[i][0])
					{
						follow_table_op(input_gram[i][0],row);
					}
				}
				else if(isupper(input_gram[i][j+1]))
				{   if(input_gram[i][j+1] != input_gram[i][0])
					{
						first_table_operation(input_gram[i][j+1],row);

					}
				}
				else
				{
					follow[row].folT[col] = input_gram[i][j+1];
					col++;
					follow[row].n++;


				}
			}
		}
	}
}


int main()
{
	freopen("input.txt", "r", stdin);
	int i,j,c=0,cnt=0;
	char ip;
	scanf("%d", &num_of_prod);
	char b[num_of_prod];
	char terminal[10000];
	int term_ct = 0;
	printf("Input Grammar is : \n");
	for(i=0;i<num_of_prod;i++)
	{
		scanf("%s",input_gram[i]);
		printf("%s\n",input_gram[i]);
		int flag = 0;
		for(j = 0; input_gram[i][j]!='\0';j++) {
			if(flag == 1) {
				if(!isupper(input_gram[i][j]) && !(input_gram[i][j] == '0')) {
					terminal[term_ct++] = input_gram[i][j];
				}

			}

			if(input_gram[i][j] == '>'){
				flag = 1;
			}

		}
	}

	printf("Terminals : \n");
	for(i = 0 ; i < term_ct;i++) {
		printf("%c ",terminal[i]);
	}
	printf("\n");
	for(i=0;i<num_of_prod;i++)
	{   c=0;
		for(j=0;j<i+1;j++)
		{
			if(input_gram[i][0] == b[j])
			{
				c=1;
				break;
			}
		}
		if(c !=1)
		{
			b[cnt] = input_gram[i][0];
			cnt++;
		}

	}

	for(i=0;i<cnt;i++)
	{   col=1;
		first[i].firT[0] = b[i];
		first[i].n=0;
		first_calc(b[i],i);
	}
	for(i=0;i<cnt;i++)
	{
		col=1;
		follow[i].folT[0] = b[i];
		follow[i].n=0;
		findFollow(b[i],i);
	}

	printf("\n");
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<=first[i].n;j++)
		{
			if(j==0)
			{
				printf("FIRST(%c) : {",first[i].firT[j]);
			}
			else
			{
				printf(" %c,",first[i].firT[j]);
			}
		}
		printf(" }\n");
	}
	for(i = 0; i <term_ct;i++) {
		printf("FIRST(%c) : { %c }\n",terminal[i], terminal[i]);
	}
	printf("\n");
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<=follow[i].n;j++)
		{
			if(j==0)
			{
				printf("FOLLOW(%c) : {",follow[i].folT[j]);
			}
			else
			{
				printf(" %c,",follow[i].folT[j]);
			}
		}
		printf(" }\n");
	}

}
