#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll N = 1000;
ll woman_list[N][N], man_pref[N][N];

void solv()
{
    string s;
    getline(cin,s);     // @PartitionA; a1, a2, a3;
    ll n_stu=0;         //n_stu = Number of students
    string t="";
    for(ll i=0; i<s.length(); i++)      //Removing all spaces
    {                                                                  
        if(s[i]!=' ')
            t.push_back(s[i]);        
    }
    s = t;
    map<ll,ll> stu;
    for(ll i=0; i<s.length(); i++)  
    {
        int st = 0;
        while(i<s.length() && s[i]>='0' && s[i]<='9')
        {
            st = 10*st + s[i]-'0';
            i++;
        }
        if(i==s.length())
        {
            cout<<"Input not complete!\n";
            return;
        }
        if(s[i]!=',' && s[i]!=';')
        {
            cout<<"Invalid symbol "<<s[i]<<"!\n";
            return;
        }
        if(s[i]==';' && i!=s.length()-1)
        {
            cout<<"Terminated too soon!\n";
            return;
        }
        else if(s[i]==',' && i>=s.length()-1)
        {
            cout<<"Not Terminated!\n";
            return;
        }
        else
        {
            if(stu[st])
            {
                cout<<"Student "<<st<<" repeated!\n";
                return;
            }
            n_stu++;
            stu[st] = n_stu;
        }
    }
    
    getline(cin,s);     //b1(1),b2(2),b3(1);
    ll n_hos = 0;
    map<ll,ll> hos;
    vector<ll> hos_cap;
    hos_cap.push_back(0);       
    for(ll i=0; i<s.length(); i++)  
    {
        int ho = 0;
        while(i<s.length() && s[i]>='0' && s[i]<='9')
        {
            ho = 10*ho + s[i]-'0';
            i++;
        }
        if(i==s.length())
        {
            cout<<"Input not complete!\n";
            return;
        }
        if(s[i]!='(')
        {
            cout<<"Hospital capacity formatting error!\n";
            return;
        }        
        i++;

        int cap = 0;
        while(i<s.length() && s[i]>='0' && s[i]<='9')
        {
            cap = 10*cap + s[i]-'0';
            i++;
        }
        if(i==s.length())
        {
            cout<<"Input not complete!\n";
            return;
        }
        if(s[i]!=')')
        {
            cout<<"Hospital capacity formatting error!\n";
            return;
        }
        i++;

        if(i>=s.length())
        {
            cout<<"Input not complete!\n";
            return;
        }
        if(s[i]!=',' && s[i]!=';')
        {
            cout<<"Invalid symbol "<<s[i]<<"!\n";
            return;
        }
        if(s[i]==';' && i!=s.length()-1)
        {
            cout<<"Terminated too soon!\n";
            return;
        }
        else if(s[i]==',' && i==s.length()-1)
        {
            cout<<"Not Terminated!\n";
            return;
        }
        else
        {
            if(hos[ho])
            {
                cout<<"Hospital "<<ho<<" repeated!\n";
                return;
            }
            n_hos++;
            hos[ho] = n_hos;
            hos_cap.push_back(cap);
        }
    }

    string s;
    cin>>s;           // @PartitionA; a1:b1,b2,b3;
    for(ll i=0; i<s.length(); i++)      //Removing all spaces
    {                                                                  
        if(s[i]!=' ')
            t.push_back(s[i]);        
    }
    s = t;
    map<ll,ll> stu;
    for(ll i=0; i<s.length(); i++)  
    {
        int st = 0;
        while(i<s.length() && s[i]>='0' && s[i]<='9')
        {
            st = 10*st + s[i]-'0';
            i++;
        }
        if(i==s.length())
        {
            cout<<"Input not complete!\n";
            return;
        }
        if(s[i]!=',' && s[i]!=';')
        {
            cout<<"Invalid symbol "<<s[i]<<"!\n";
            return;
        }
        if(s[i]==';' && i!=s.length()-1)
        {
            cout<<"Terminated too soon!\n";
            return;
        }
        else if(s[i]==',' && i==s.length()-1)
        {
            cout<<"Not Terminated!\n";
            return;
        }
        else
        {
            if(stu[st])
            {
                cout<<"Student "<<st<<" repeated!\n";
                return;
            }
            n_stu++;
            stu[st] = n_stu;
        }
    }





















    
    ll woman;
    for(ll i=0; i<n; i++)
    {
        for(ll j=0; j<n; j++)
        {
            cin>>woman;
            man_pref[i][woman]=j;   //man_pref[i][j] stores the pref_no of the woman j in tyhe i^th man's list
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
