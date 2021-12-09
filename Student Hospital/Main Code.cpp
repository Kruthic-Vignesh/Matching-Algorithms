#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll N = 1000;
#define LL_MAX 1<<60

class StudentHospital
{
    ll n_stu, n_hos;
    vector<vector<ll>> stu_pref, hos_pref;
    vector<vector<ll>> pos_stu, pos_hos;
    vector<vector<ll>> final_list;
    priority_queue<pair<ll,ll>> acc_stu[N+1];
    map<ll,ll> stu, hos;
    vector<ll> hos_cap;
    vector<ll> stu_rev_map, hos_rev_map;
    vector<ll> allocation;

    public: 
    StudentHospital();
    void GetStudentList();
    void GetHospitalList();
    void GetStudentPref();
    void GetHospitalPref();
    void GaleShapleyAlgo();
    void DisplayAllocation();
    void DisplayAllocationStu();
    void solv();
}SH;

StudentHospital::StudentHospital()
{
    n_stu = 0, n_hos = 0;
    stu_pref.assign(N+1, vector<ll>());
    hos_pref.assign(N+1, vector<ll>());
    pos_stu.assign(N+1, vector<ll>(N+1,LL_MAX));
    pos_hos.assign(N+1, vector<ll>(N+1,LL_MAX));
    final_list.assign(N+1,vector<ll>());
    allocation.assign(N+1,-1);

    stu_rev_map.push_back(0);
    hos_rev_map.push_back(0);
    hos_cap.push_back(0);
}

void StudentHospital::GetStudentList()
{
    string s;
    getline(cin,s);     //@PartitionA
    if(s != "@PartitionA")
    {
        cout << "Invalid Partition Name!\n";
        return;
    }
    getline(cin,s);     //a1, a2, a3, a4;
    string t="";
    for(ll i=0; i<s.length(); i++)      //Removing all spaces
    {
        if(s[i]!=' ')
            t.push_back(s[i]);
    }
    s = t;
    for(ll i=0; i<s.length(); i++)
    {
        ll st = 0;
        if(s[i]!='a')
        {
            cout << "Student tag -a- missing!\n";
            return;
        }
        i++;
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
    getline(cin,s);
    if(s != "@End")
    {
        cout << "Student List not ended!\n";
        return;
    }
}

void StudentHospital::GetHospitalList()
{
    string s,t;
    getline(cin,s);     //empty line
    if(s != "")
    {
        cout << "Spacing missing mamaaa!\n";
        return;
    }
    getline(cin,s);     //@PartitionB
    if(s != "@PartitionB")
    {
        cout << "Invalid Partition Name!\n";
        return;
    }
    getline(cin,s);                     //b1(1), b2(2), b3(1);
    t="";
    for(ll i=0; i<s.length(); i++)      //Removing all spaces
    {
        if(s[i]!=' ')
            t.push_back(s[i]);
    }
    s = t;
    for(ll i=0; i<s.length(); i++)
    {
        ll ho = 0;
        if(s[i]!='b')
        {
            cout << "Hospital tag -b- missing!\n";
            return;
        }
        i++;
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
            // cout << hos[n_hos] << ' ' << hos_cap[n_hos] << endl;
        }
    }
    getline(cin,s);
    if(s != "@End")
    {
        cout << "Student List not ended!\n";
        return;
    }
}

void StudentHospital::GetStudentPref()
{
    string s,t;
    getline(cin,s);     //empty line
    if(s != "")
    {
        cout << "Spacing missing oyaa!\n";
        return;
    }
    getline(cin,s);     //@PartitionB
    if(s != "@PreferenceListsA")
    {
        cout << "Invalid Partition Name!\n";
        return;
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
        if(ii>=s.length() || s[ii]!='a')
        {
            cout << "Student tag -a- missing!\n";
            return;
        }
        ii++;
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
        ll pref_no = 0;
        for(ll i=ii+1; i<s.length(); i++)
        {
            ll ho = 0;
            pref_no++;
            if(i>=s.length() || s[i]!='b')
            {
                cout << "Hospital tag -b- missing!\n";
                return;
            }
            i++;
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
            pos_hos[st_ind][hos[ho]] = pref_no;
        }
    }
    getline(cin,s);
    if(s != "@End")
    {
        cout << "Student List not ended!\n";
        return;
    }
}

void StudentHospital::GetHospitalPref()
{
    string s,t;
    getline(cin,s);     //empty line
    if(s != "")
    {
        cout << "Spacing missing naaye!\n";
        return;
    }
    getline(cin,s);     //@PartitionB
    if(s != "@PreferenceListsB")
    {
        cout << "Invalid Partition Name!\n";
        return;
    }
    for(ll j=1; j<=n_hos; j++)
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
        if(ii>=s.length() || s[ii]!='b')
        {
            cout << "Hospital tag -b- missing!\n";
            return;
        }
        ii++;
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
            if(i+1==s.length() && s[i]==';')
                break;

            if(i>=s.length() || s[i]!='a')
            {
                cout << "Student tag waw missing!\n";
                return;
            }
            i++;
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
            pos_stu[ho_ind][stu[st]] = pref_no;
        }
    }
    getline(cin,s);
    if(s != "@End")
    {
        cout << "Student List not ended!\n";
        return;
    }
}

void StudentHospital::GaleShapleyAlgo()
{
    vector<ll>  preference(n_stu+1,1), cap_rem = hos_cap;   //preference[i] : the current preference the student i is proposing to 
    queue<ll> waiting_list;                                  
    for(ll i = 1; i <= n_stu; i++)
    {
        waiting_list.push(i);
    }
    while(!waiting_list.empty())                                      
    {
        ll st = waiting_list.front();
        waiting_list.pop();

        if(preference[st] >= stu_pref[st].size())
            continue;

        ll ho = stu_pref[st][preference[st]];
        if(pos_stu[ho][st] == LL_MAX)
        {
            preference[st]++;
            waiting_list.push(st);
            continue;
        }

        if(acc_stu[ho].size() < hos_cap[ho])        
            acc_stu[ho].push({pos_stu[ho][st],st});
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
            allocation[st.second] = i;
            final_list[i].push_back(stu_rev_map[st.second]);
        }
        final_list[i].push_back(0);
        reverse(final_list[i].begin(), final_list[i].end());
    }
}

void StudentHospital::DisplayAllocation()
{
    for(ll i=1; i <= n_stu; i++)
    {
         if(allocation[i] == -1)     continue;

        cout << "a" << stu_rev_map[i] << ",";
        cout << "b" << hos_rev_map[allocation[i]] << ",";
        cout << pos_hos[i][allocation[i]] << endl;
    }
    return;

    for(ll i=1; i <= n_hos; i++)
    {
        cout << "b" << hos_rev_map[i] << ": ";
        for(ll j = 1; j < final_list[i].size(); j++) 
        {
            cout << "a" << final_list[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

void StudentHospital::solv()
{
    GetStudentList();
    GetHospitalList();
    GetStudentPref();
    GetHospitalPref();
    GaleShapleyAlgo();
    DisplayAllocation();
    return;
}

int main()
{
    SH.solv();
    return 0;
}
