#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll N = 1000;

vector<vector<ll>> stu_pref(N+1), hos_pref(N+1);
vector<vector<ll>> pos_stu(N+1);
vector<vector<ll>> final_list(N+1);

priority_queue<pair<ll,ll>> acc_stu[N+1];

void solv()
{
    string s;
    getline(cin,s);     //@PartitionA; a1, a2, a3;
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
        ll st = 0;
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

    getline(cin,s);     //@PartitionB; b1(1), b2(2), b3(1);
    ll n_hos = 0;       //n_hos = Number of hospitals

    t="";
    for(ll i=0; i<s.length(); i++)      //Removing all spaces
    {
        if(s[i]!=' ')
            t.push_back(s[i]);
    }
    s = t;

    map<ll,ll> hos;
    vector<ll> hos_cap;
    hos_cap.push_back(0);
    for(ll i=0; i<s.length(); i++)
    {
        ll ho = 0;
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

        ll cap = 0;
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

    getline(cin,s);           // @PreferenceListA; a1:b1,b2,b3;
    t="";
    for(ll i=0; i<s.length(); i++)      //Removing all spaces
    {
        if(s[i]!=' ')
            t.push_back(s[i]);
    }
    s = t;
    for(ll i=0; i<n_stu+1; i++) {
        stu_pref[i].push_back(0);
    }

    for(ll i=0; i<s.length(); i++)
    {
        ll st = 0;
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
        if(s[i]!=':')
        {
            cout<<"Invalid symbol '"<<s[i]<<"' !!!\n";
            return;
        }
        else if(s[i]==':' && i==s.length()-1)
        {
            cout<<"Not Terminated!\n";
            return;
        }
        else
        {
            ll st_ind;
            if(stu[st])
            {
                st_ind = stu[st];
            }
            else
            {
                cout<<"Student not found!\n";
                return;
            }
            for(ll i=0; i<s.length(); i++)
            {
                ll ho = 0;
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
                    if(hos[ho])
                    {
                        stu_pref[st_ind].push_back(hos[ho]);
                    }
                    else
                    {
                        cout<<"Hospital not found!\n";
                        return;
                    }
                }
            }
        }
    }

    getline(cin,s);           // @PreferenceListB; b1:a1,a2,a3;
    t="";
    for(ll i=0; i<s.length(); i++)      //Removing all spaces
    {
        if(s[i]!=' ')
            t.push_back(s[i]);
    }
    s = t;
    for(ll i=0; i<n_hos+1; i++) {
        hos_pref[i].push_back(0);
    }

    for(ll i=0; i<s.length(); i++)
    {
        ll ho = 0;
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
        if(s[i]!=':')
        {
            cout<<"Invalid symbol "<<s[i]<<"!\n";
            return;
        }
        else if(s[i]==':' && i==s.length()-1)
        {
            cout<<"Not Terminated!\n";
            return;
        }
        else
        {
            ll ho_ind;
            if(hos[ho])
            {
                ho_ind = hos[ho];
            }
            else
            {
                cout<<"Student not found!\n";
                return;
            }
            for(ll i=0; i<s.length(); i++)
            {
                ll st = 0;
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
                        hos_pref[ho_ind].push_back(stu[st]);
                    }
                    else
                    {
                        cout<<"Hospital not found!\n";
                        return;
                    }
                }
            }
        }
    }




















//    ll woman;
//    ll n = 1;
//    for(ll i=0; i<n; i++)
//    {
//        for(ll j=0; j<n; j++)
//        {
//            cin>>woman;
//            man_pref[i][woman]=j;   //man_pref[i][j] stores the pref_no of the woman j in tyhe i^th man's list
//        }
//    }
//
//    ll man;
//    for(ll i=0; i<n; i++)
//    {
//        for(ll j=0; j<n; j++)
//        {
//            cin>>man;
//            woman_list[i][j]=man;
//        }
//    }

    for(ll i = 1; i <= n_hos; i++) {
        pos_stu[i].resize(hos_pref[i].size());
        for(ll j = 1; j < hos_pref[i].size(); j++) {
            pos_stu[i][hos_pref[i][j]] = j;
        }
    }

    vector<bool> rejected(n_stu+1, true);                     //rejected[i] == true if the ith woman does not have any tentative engagement
    vector<ll>  preference(n_stu+1), cap_rem = hos_cap;
    ll cnt = 0;                                        //partner[i] : current partner of ith man
    while(cnt < n_stu)                                      //preference[i] : the current preference the woman i is proposing to
    {
        for(ll j = 1; j <= n_stu; j++)
        {
            if(!rejected[j]) continue;
            ll hos = stu_pref[j][preference[j]];
            if(cap_rem[hos])
            {
                acc_stu[hos].push({pos_stu[hos][j],j});
                rejected[j] = false;
                cap_rem[hos]--;
            }
            else
            {
                acc_stu[hos].push({pos_stu[hos][j],j});
                rejected[j] = false;
                pair<ll,ll> rej_stu = acc_stu[hos].top();
                acc_stu[hos].pop();
                rejected[rej_stu.second] = true;
                preference[rej_stu.second]++;
            }
        }
    }


    for(ll i = 1; i <= n_hos; i++) {
        while(!acc_stu[i].empty()) {
            pair<ll,ll> st = acc_stu[i].top();
            acc_stu[i].pop();
            final_list[i].push_back(st.second);
        }
        final_list[i].push_back(0);
        reverse(final_list[i].begin(), final_list[i].end());
    }

    for(ll i=1; i<=n_hos; i++)
    {
        cout << i << ": ";
        for(ll j = 1; j < final_list[i].size(); j++) {
            cout << final_list[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

int main()
{
    ll test_cases=1;
//    cin>>test_cases;
    for(ll curr_case=1;curr_case<=test_cases;curr_case++)
    {
        solv();
    }
    return 0;
}
