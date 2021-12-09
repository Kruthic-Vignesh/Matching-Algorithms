/*    AdC_AB2    */

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int gr(int r)
{
   uniform_int_distribution<int> uid(0,r-1);
   int val = uid(rng);
   return val+1;
}

int glr(int l, int r)
{
    int dif = r-l+1;
    int x = gr(dif) + l-1;
    return x;
}

ofstream outputFile[10];
#define cout outputFile[tc]

void solv(ll tc)
{
    //Student List
    cout << "@PartitionA\n";
    ll n_stu = glr(500,1000);
    for(int i=0; i<n_stu; i++)
    {
        cout<<"a"<<i+1;
        if(i==n_stu-1)
            cout<<" ;\n";
        else
            cout<<", ";
    }
    cout << "@End\n\n";

    //Hospitals & its capacity
    cout << "@PartitionB\n";
    vector<ll> hos_cap;
    ll n_hos = glr(200,400);
    for(int i=0; i<n_hos; i++)
    {
        cout<<"b"<<i+1;
        hos_cap.push_back(glr(1,5));
        cout<<" ("<<hos_cap[hos_cap.size()-1]<<")";
        if(i==n_hos-1)
            cout<<" ;\n";
        else
            cout<<", ";
    }
    cout << "@End\n\n";

    //Student preference lists
    cout << "@PreferenceListsA\n";
    vector<ll> hos_list;
    for(int j=0; j<n_hos; j++)
    {
        hos_list.push_back(j+1);
    }
    vector<ll> h_a[1001];
    for(int i=0; i<n_stu; i++)
    {
        cout<<"a"<<i+1<<": ";
        int n = glr(1,n_hos);
        random_shuffle(hos_list.begin(),hos_list.end());
        for(int j=0; j<n; j++)
        {
            h_a[hos_list[j]].push_back(i+1);
            cout<<"b"<<hos_list[j];
            if(j==n-1)
                cout<<";\n";
            else
                cout<<", ";
        }
    }
    cout << "@End\n\n";

    //Hospital preference lists
    cout << "@PreferenceListsB\n";
    vector<ll> stu_list;
    /*for(int j=0; j<n_stu; j++)
    {
        stu_list.push_back(j+1);
    }*/
    for(int i=0; i<n_hos; i++)
    {
        cout<<"b"<<i+1<<": ";
        // int n = glr(hos_cap[i],n_stu);
        random_shuffle(h_a[i].begin(), h_a[i].end());
        for(int j=0; j<h_a[i].size(); j++)
        {
            cout<<"a"<<h_a[i][j];    
            if(j != h_a[i].size()-1)
                cout<<", ";
        }
        cout<<";\n";
    }
    cout << "@End\n";
}

int32_t main()
{
    string file[10] = {"TC1.txt", "TC2.txt", "TC3.txt", "TC4.txt", "TC5.txt", "TC6.txt", "TC7.txt", "TC8.txt", "TC9.txt", "TC10.txt"};

    for (int i=0; i<10; i++) outputFile[i].open(file[i].c_str());

    for(int tc=0; tc<10; tc++)
    {
        int t = 1;
        solv(tc);
    }
    return 0;
}
