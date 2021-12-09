#include<bits/stdc++.h>
 
using namespace std;
 
#define endl "\n"
#define mod 1000000007
 
typedef long long ll;

void sol()
{
    vector<pair<ll, string>> s;
    string x;
    int n, it;
    while(cin>>x) 
    {
        n = 0;
        it = 1;
        while(x[it] != ',')
        {
            n *= 10;
            n += x[it]-'0';
            it++;
        }
        s.push_back({n, x});
    }
    sort(s.begin(), s.end());
    for(int i = 0; i < s.size(); i++)
        cout<<s[i].second<<endl;
}
 
int main()
{
    string file[10] = {"output (1).txt", "output (2).txt", "output (3).txt", "output (4).txt", "output (5).txt", "output (6).txt", "output (7).txt", "output (8).txt", "output (9).txt", "output (1)0.txt"};
    string op[10] = {"comp1.txt", "comp2.txt", "comp3.txt", "comp4.txt", "comp5.txt", "comp6.txt", "comp7.txt", "comp8.txt", "comp9.txt", "comp10.txt"};
    for(int i=0; i<10; i++)
    {
        freopen(op[i].c_str(),"w", stdout);
        freopen(file[i].c_str(),"r", stdin);
        sol();
        fclose(stdin);
        fclose(stdout);
    }
    return 0;
}
