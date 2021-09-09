#include <bits/stdc++.h>

using namespace std;

int randf(int n)
{
    return rand()%n;
}

void solve()
{
    srand(unsigned(time(0)));
    int n;
    cin >> n;
    int men[n][n], women[n][n];
    int posm[n][n], posw[n][n];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            men[i][j] = j;
            women[i][j] = j;
        }
    }
    for(int i = 0; i < n; i++)
    {
        random_shuffle(men[i], men[i]+n, randf);        
        for(int j = 0; j < n; j++) 
        {
            posw[i][men[i][j]] = j;   
        }
    }
    for(int i = 0; i < n; i++) 
    {
        random_shuffle(women[i], women[i]+n, randf);
        for(int j = 0; j < n; j++) 
        {
            posm[i][women[i][j]] = j; 
        }
    }

    cout << "Preference list of men : " << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << men[i][j] << " ";
        }
        cout<<endl;
    }
    
    cout << "Preference list of women : " << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << women[i][j] << " ";
        }
        cout<<endl;
    }

    vector<bool> rejected(n, true), engaged(n, false);  
    vector<int>  partner(n, -1), preference(n);         
    int cnt = 0;                                        
    while(cnt < n)                                      
    {
        for(int j = 0; j < n; j++) 
        {
            if(!rejected[j]) continue;
            int man = women[j][preference[j]];
            if(engaged[man]) 
            {
                if(posw[man][partner[man]] > posw[man][j]) 
                {
                    rejected[j] = false;
                    rejected[partner[man]] = true;
                    preference[partner[man]]++;
                    partner[man] = j;
                }
                else 
                {
                    preference[j]++;
                }
            }
            else 
            {
                partner[man] = j;
                engaged[man] = true;
                rejected[j] = false;
                cnt++;
            }
        }
    }
    cout << "Stable Matching is : " << endl;
    for(int i = 0; i < n; i++) 
    {
        cout << "Men : " << i << ", Women : " << partner[i] << endl;
    }
    return;
}

int main()
{
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}       