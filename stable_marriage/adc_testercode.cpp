#include<bits/stdc++.h>

using namespace std;

const ll N = 1000;

ll woman_list[N][N], man_pref[N][N];

void solv()
{
    ll n;
    cin>>n;

    ll woman;
    for(ll i=0; i<n; i++)
    {
        for(ll j=0; j<n; j++)
        {
            cin>>woman;
            man_pref[i][woman]=j;
        }
    }

    ll man;
    for(ll i=0; i<n; i++)
    {
        for(ll j=0; j<n; j++)
        {
            cin>>man;
            woman_list[i][j]=man;
        }
    }

    vector<ll> pos(n);
    ll not_engaged = n;
    vector<bool> engaged(n);
    vector<ll> wife(n,n+1);
    while(not_engaged)
    {
        for(ll i=0; i<n; i++)
        {
            if(!engaged[i] && pos[i]<n)
            {
                man = woman_list[i][pos[i]];
                if(wife[man] == n+1)
                {
                    wife[man]=i;
                }
                else if(man_pref[man][wife[man]] > man_pref[man][i])
                {
                    wife[man]=i;
                }
                pos[i]++;
            }
            engaged[i]=false;
        }

        not_engaged = n;
        for(ll i=0; i<n; i++)
        {
            if(wife[i]!=n+1)
            {
                engaged[wife[i]]=true;
                not_engaged--;
            }
        }
    }

    for(ll i=0; i<n; i++)
    {
        cout<<i<<" "<<wife[i]<<endl;
    }
    return;
}

int main()
{
    ll test_cases=1;
    cin>>test_cases;
    for(ll curr_case=1;curr_case<=test_cases;curr_case++)
    {
        solv();
    }
    return 0;
}
