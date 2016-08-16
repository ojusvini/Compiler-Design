/* Author - Rupesh Maity ([theMighty] deathsurgeon) - RIT2013066
 * LR(0) Parser implementation
 * Copy at your own risk, bas mujhe mat phasa dena
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<string> > states; // contains the dot position in each of the productions
vector<string> arr;
string parsingTable[50][50];
char graph[50][50];
vector<string> productions;
int numProductions;

bool valid(vector<string> v, string str)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == str)
            return false;
    }
    return true;
}

void gen(vector<string> v, char c)
{
    arr.clear();

    for (int i = 0; i < v.size(); i++)
    {
        int p = (int)v[i].find('.');
        ++p;
        if (p != v[i].size() && v[i][p] == c)
        {
            arr.push_back(v[i]);
            swap(arr[arr.size() - 1][p], arr[arr.size() - 1][p-1]);
        }
    }
}

int valid()
{
    for (int i = 0; i < states.size(); i++)
    {
        if (states[i] == arr)
        {
            return i;
        }
    }
    return -1;
}

void extend(int idx)
{
    // add NTproductions
    for (int i = 0; i < states[idx].size(); i++)
    {
        int p = (int)states[idx][i].find('.');
        ++p;
        if (p != states[idx][i].size() && states[idx][i][p] <= 'Z')
        {
            char z = states[idx][i][p];
            for (int j = 0; j < productions.size(); j++)
            {
                if (productions[j][0] == z)
                {
                    if (valid(states[idx], productions[j]))
                    {
                        states[idx].push_back(productions[j]);
                    }
                }
            }
        }
    }

    sort(states[idx].begin(), states[idx].end());
}

void extend()
{
    for (int i = 0; i < arr.size(); i++)
    {
        int p = (int)arr[i].find('.');
        ++p;
        if (p != arr[i].size() && arr[i][p] <= 'Z')
        {
            char z = arr[i][p];
            for (int j = 0; j < productions.size(); j++)
            {
                if (productions[j][0] == z)
                {
                    if (valid(arr, productions[j]))
                    {
                        arr.push_back(productions[j]);
                    }
                }
            }
        }
    }

    sort(arr.begin(), arr.end());
}

void play(int idx)
{
    for (int i = 0; i < states[idx].size(); i++)
    {
        int p = (int)states[idx][i].find('.');
        ++p;
        if (p != states[idx][i].size() && states[idx][i][p] != '$')
        {
            char z = states[idx][i][p];
            gen(states[idx], z);
            extend();
            int t = valid();
            if (t == -1)
            {
                graph[idx][states.size()] = z;
                states.push_back(arr);
                play(states.size() - 1);
            } else {
                graph[idx][t] = z;
            }
        }
    }
}

int main()
{
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            graph[i][j] = -1;
        }
    }
    freopen("inputlr0_1.cpp", "r", stdin);

    cout << "Enter the number of productions: ";
    cin >> numProductions;

    // Creating augmented grammer
    productions.push_back("!->.S$");

    for (int i = 0; i < numProductions; i++)
    {
        string str;
        cin >> str;

        for (int j = 3; j < str.size(); j++)
        {
            string p = "";
            p += str[0];
            p += "->.";
            p += str[j];
            ++j;
            if (j < str.size() && str[j] != '|')
            {
                p += str[j];
                ++j;
            }

            productions.push_back(p);
        }
    }

    states.push_back(productions); // initial state pushed
    extend(0);
    play(0);

    cout << "Printing out all the Item-sets:" << endl;

    for (int i = 0; i < states.size(); i++)
    {
        cout << "Item-set " << i + 1 << ":" << endl;

        for (int j = 0; j < states[i].size(); j++)
        {
            cout << states[i][j] << endl;
        }

        cout << endl;
    }

    map<char, bool> mp;
    vector<char> terminals;
    vector<char> Nterminals;

    for (int i = 0; i < states.size(); i++) {
        for (int j = 0; j < states.size(); j++) {
            if (graph[i][j] != -1) {
                if (!mp[graph[i][j]]) {
                    mp[graph[i][j]] = true;
                    if (graph[i][j] <= 'Z') {
                        // Non-terminal detected
                        Nterminals.push_back(graph[i][j]);
                    } else {
                        terminals.push_back(graph[i][j]);
                    }
                }
            }
        }
    }
    terminals.push_back('$');

    printf(" ");
    for (int i = 0; i < terminals.size(); i++) {
        printf("%8c", terminals[i]);
    }
    for (int i = 0; i < Nterminals.size(); i++) {
        printf("%8c", Nterminals[i]);
    }
    cout << endl;

    for (int idx = 0; idx < states.size(); idx++) {
        printf("%d", idx + 1);
        if (states[idx][0] == "!->S.$") {
            printf("   error   error  accept\n");
            continue;
        }

        // find R's now
        vector<int> R;
        for (int i = 0; i < states[idx].size(); i++) {
            for (int j = 0; j < productions.size(); j++) {
                if (states[idx][i].substr(0, states[idx][i].size() - 1) == productions[j].substr(0, 3) + productions[j].substr(4, productions.size())) {
                    R.push_back(j+1);
                }
            }
        }

        // find S's now
        for (int i = 0; i < terminals.size(); i++) {
            int S = -1;
            for (int j = 0; j < states.size(); j++) {
                if (graph[idx][j] == terminals[i]) {
                    S = j + 1;
                    break;
                }
            }

            string ans = "";
            if (R.size() == 0 && S == -1) {
                ans = "-";
            } else {
                for (int i = 0; i < R.size(); i++) {
                    ans += "R";
                    ans += (char)(R[i] + '0');
                    ans += ",";
                }
                if (S != -1) {
                    ans += "S";
                    ans += (char)(S + '0');
                }
            }

            char p[50];
            for (int l = 0; l < ans.size(); l++) {
                p[l] = ans[l];
            }
            p[ans.size()] = 0;
            printf("%8s", p);
        }

        for (int i = 0; i < Nterminals.size(); i++) {
            bool b = false;
            for (int j = 0; j < states.size(); j++) {
                if (graph[idx][j] == Nterminals[i]) {
                    printf("%8d", j + 1);
                    b = true;
                    break;
                }
            }

            if (!b) {
                printf("       -");
            }
        }

        cout << endl;
    }

    return 0;
}
