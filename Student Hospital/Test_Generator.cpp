#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const ll STU_LOWER_LIMIT = 500;
const ll STU_UPPER_LIMIT = 1000;

const ll HOS_LOWER_LIMIT = 500;
const ll HOS_UPPER_LIMIT = 1000;

const ll HOS_UPPER_QUOTA_L = 1;
const ll HOS_UPPER_QUOTA_U = 25;

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
    ll n_stu = glr(STU_LOWER_LIMIT,STU_UPPER_LIMIT);
    for(int i=1; i<=n_stu; i++)
    {
        cout<<"a"<<i;
        if(i==n_stu)
            cout<<" ;\n";
        else
            cout<<", ";
    }
    cout << "@End\n\n";

    //Hospitals & its capacity
    cout << "@PartitionB\n";
    vector<ll> hos_cap;
    ll n_hos = glr(HOS_LOWER_LIMIT,HOS_UPPER_LIMIT);
    for(int i=1; i<=n_hos; i++)
    {
        cout<<"b"<<i;
        hos_cap.push_back(glr(HOS_UPPER_QUOTA_L,HOS_UPPER_QUOTA_U));
        cout<<" ("<<hos_cap.back()<<")";
        if(i==n_hos)
            cout<<" ;\n";
        else
            cout<<", ";
    }
    cout << "@End\n\n";

    //Student preference lists
    cout << "@PreferenceListsA\n";
    vector<ll> hos_list;
    for(int j=1; j<=n_hos; j++)
    {
        hos_list.push_back(j);
    }

    vector<ll> h_a[n_hos+1];
    for(int i=1; i<=n_stu; i++)
    {
        cout<<"a"<<i<<": ";
        int n = glr(1,n_hos);
        random_shuffle(hos_list.begin(),hos_list.end());
        for(int j=0; j<n; j++)
        {
            h_a[hos_list[j]].push_back(i);
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
    for(int i=1; i<=n_hos; i++)
    {
        cout<<"b"<<i<<": ";
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
