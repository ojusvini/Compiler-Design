#include<iostream>  
#include<cstring>
#include<algorithm>
#include<string>
#include <cstdio>
#include<cassert>
#include<iomanip>
using namespace std;

#define MAX 100
#define for(i,a,b) for(i=a;i<b; i++)

string gram[MAX][MAX];
string dpr[MAX];
int p, np;

inline string concatenate(string a, string b)
{
	int i;
	string r = a;
	for (i, 0, b.length())
	if (r.find(b[i]) > r.length())
		r += b[i];
	return (r);
}

inline void break_gram(string a)
{
	int i;
	p = 0;
	while (a.length())
	{
		i = a.find("|");
		if (i>a.length())
		{
			dpr[p++] = a;
			a = "";
		}
		else
		{
			dpr[p++] = a.substr(0, i);
			a = a.substr(i + 1, a.length());
		}
	}
}

inline int left_chomsky(string a)
{
	if (a.length() == 1 && a[0] >= 'A' && a[0] <= 'Z')
		return 1;
	return 0;
}

inline int right_chomsky(string a)
{
	if (a.length() == 1 && a[0] >= 'a' && a[0] <= 'z')
		return 1;
	if (a.length() == 2 && a[0] >= 'A' && a[0] <= 'Z' && a[1] >= 'A' && a[1] <= 'Z')
		return 1;
	return 0;
}

inline string search_prod(string p)
{
	int j, k;
	string r = "";
	for (j, 0, np)
	{
		k = 1;
		while (gram[j][k] != "")
		{
			if (gram[j][k] == p)
			{
				r = concatenate(r, gram[j][0]);
			}
			k++;
		}
	}
	return r;
}

inline string gen_comb(string a, string b)
{
	int i, j;
	string pri = a, re = "";
	for (i, 0, a.length())
	for (j, 0, b.length())
	{
		pri = "";
		pri = pri + a[i] + b[j];
		re = re + search_prod(pri);
	}
	return re;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int i, pt, j, l, k;
	string a, str, r, pr, start;
	cin >> start;
	cin >> np;
	for (i, 0, np)
	{
		cin >> a;
		pt = a.find("->");
		gram[i][0] = a.substr(0, pt);
		if (left_chomsky(gram[i][0]) == 0)
		{
			cout << "\nGrammar is not in Chomsky Form";
			return 0;
		}
		a = a.substr(pt + 2, a.length());
		break_gram(a);
		for (j, 0, p)
		{
			gram[i][j + 1] = dpr[j];
			if (right_chomsky(dpr[j]) == 0)
			{
				cout << "\nGrammar is not in Chomsky Form";
				abort();
			}
		}
	}
	string matrix[MAX][MAX], st;
	cin >> str;
	for (i, 0, str.length())
	{
		r = "";
		st = "";
		st += str[i];
		for (j, 0, np)
		{
			k = 1;
			while (gram[j][k] != "")
			{
				if (gram[j][k] == st)
				{
					r = concatenate(r, gram[j][0]);
				}
				k++;
			}
		}
		matrix[i][i] = r;
	}
	int ii, kk;
	for (k, 1, str.length())
	{
		for (j, k, str.length())
		{
			r = "";
			for (l, j - k, j)
			{
				pr = gen_comb(matrix[j - k][l], matrix[l + 1][j]);
				r = concatenate(r, pr);
			} 
			matrix[j - k][j] = r;
		}
	}

	for (i, 0, str.length())
	{
		k = 0;
		l = str.length() - i - 1;
		for (j, l, str.length())
		{
			cout << setw(5) << matrix[k++][j] << " ";
		}
		cout << endl;
	}

	int f = 0;
	for (i, 0, start.length())
	if (matrix[0][str.length() - 1].find(start[i]) <= matrix[0][str.length() - 1].length())
	{
		cout << "Success, string accepted\n";
		return 0;
	}
	cout << "Not Possible\n";
	return 0;
}
/*
S->EF|AF|EB|AB
X->AY|BY|a|b
Y->AY|BY|a|b
E->AX
F->BX
A->a
B->b

*/
/*
S->AB|BC
A->BA|a
B->CC|b
C->AB|a
*/