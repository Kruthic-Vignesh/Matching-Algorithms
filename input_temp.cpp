#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll N = 1000;
#define LL_MAX 1<<60

class StudentHospital
{
    ll n_stu, n_hos;
    vector<vector<ll>> stu_pref(N+1), hos_pref(N+1);
    vector<vector<ll>> pos_stu(N+1,vector<ll>(N+1,LL_MAX));
    vector<vector<ll>> final_list(N+1);
    priority_queue<pair<ll,ll>> acc_stu[N+1];

    public: 
    void GetStudentList();
    void GetHospitalList();
    void GetStudentPref();
    void GetHospitalPref();
    void solv();
};

void GetStudentList()
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
    vector<ll> stu_rev_map(1);
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
            stu_rev_map.push_back(st);
        }
    }
}

void GetHospital()
{
    string s,t;
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
    vector<ll> hos_cap, hos_rev_map(1);
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
            hos_rev_map.push_back(ho);
        }
    }

    for(ll i=1; i<=n_stu; i++)      //Student's preference list of hospitals
    {
        stu_pref[i].push_back(0);       
    }

    for(ll i=0; i<n_stu; i++)
    {
        getline(cin,s);                     // @PreferenceListA; a1:b1,b2,b3;
        t="";
        for(ll i=0; i<s.length(); i++)      //Removing all spaces
        {
            if(s[i]!=' ')
                t.push_back(s[i]);
        }
        s = t;
        
        ll ii=0, st=0;
        while(ii<s.length() && s[ii]>='0' && s[ii]<='9')        //Checking if valid student given as input
        {
            st = 10*st + s[ii]-'0';
            ii++;
        }
        if(!stu[st])
        {
            cout<<"Invalid student "<<st<<endl;
            return;
        }
        if(ii>=s.length()-1 || s[ii]!=':')
        {
            cout<<"Incomplete preference list!"<<endl;
            return;
        }

        ll st_ind = stu[st];
        for(ll i=ii+1; i<s.length(); i++)
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
            if(s[i]==',' && i>=s.length()-1)
            {
                cout<<"Not Terminated!\n";
                return;
            }
            if(!hos[ho])
            {
                cout<<"Hospital not found!\n";
                return;
            }
            stu_pref[st_ind].push_back(hos[ho]);
        }
    }

    for(ll i=1; i<=n_hos; i++)
    {
        getline(cin,s);                     // @PreferenceListA; a1:b1,b2,b3;
        t="";
        for(ll i=0; i<s.length(); i++)      //Removing all spaces
        {
            if(s[i]!=' ')
                t.push_back(s[i]);
        }
        s = t;
        
        ll ii=0, ho=0;
        while(ii<s.length() && s[ii]>='0' && s[ii]<='9')        //Checking if valid hospital given as input
        {
            ho = 10*ho + s[ii]-'0';
            ii++;
        }
        if(!hos[ho])
        {
            cout<<"Invalid hospital "<<ho<<endl;
            return;
        }
        if(ii>=s.length()-1 || s[ii]!=':')
        {
            cout<<"Incomplete preference list!"<<endl;
            return;
        }

        ll ho_ind = hos[ho];
        ll pref_no = 0;
        for(ll i=ii+1; i<s.length(); i++)
        {
            pref_no++;
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
            if(s[i]==',' && i>=s.length()-1)
            {
                cout<<"Not Terminated!\n";
                return;
            }
            if(!stu[st])
            {
                cout<<"Student not found!\n";
                return;
            }
            // hos_pref[ho_ind].push_back(stu[st]);
            pos_stu[ho_ind][stu[st]] = pref_no;
        }
    }


    vector<ll>  preference(n_stu+1,1), cap_rem = hos_cap;   //preference[i] : the current preference the woman i is proposing to
    ll cnt = 0, tot_pref = 0;    
    queue<ll> waiting_list;                                  
    for(ll i = 1; i <= n_stu; i++)
    {
        waiting_list.push(i);
        tot_pref += stu_pref[i].size();
    }
    
    while(!waiting_list.empty())                                      
    {
        ll st = waiting_list.front();
        waiting_list.pop();
        ll ho = stu_pref[st][preference[st]];
        if(acc_stu[ho].size() < hos_cap[ho])
        {
            acc_stu[ho].push({pos_stu[ho][st],st});
        }
        else
        {
            acc_stu[ho].push({pos_stu[ho][st],st});
            pair<ll,ll> rej_stu = acc_stu[ho].top();
            acc_stu[ho].pop();
            preference[rej_stu.second]++;
            if(preference[rej_stu.second] < stu_pref[rej_stu.second].size())
                waiting_list.push(rej_stu.second);
        }
    }


    for(ll i = 1; i <= n_hos; i++) 
    {
        while(!acc_stu[i].empty()) 
        {
            pair<ll,ll> st = acc_stu[i].top();
            acc_stu[i].pop();
            final_list[i].push_back(stu_rev_map[st.second]);
        }
        final_list[i].push_back(0);
        reverse(final_list[i].begin(), final_list[i].end());
    }

    for(ll i=1; i <= n_hos; i++)
    {
        cout << hos_rev_map[i] << ": ";
        for(ll j = 1; j < final_list[i].size(); j++) 
        {
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
