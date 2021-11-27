#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    int women[n][n], posw[n][n];
    int inp;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++) 
        {
            cin >> inp;         //jth preference of ith man
            posw[i][inp] = j;   //posw[i][j] : preference of jth woman in ith man's list
        }
    }
    for(int i = 0; i < n; i++) 
    {
        for(int j = 0; j < n; j++) 
        {   
            cin >> women[i][j];       //jth preference of ith woman 
        }
    }
    
    vector<bool> rejected(n, true), engaged(n, false);   //rejected[i] == true if the ith woman does not have any tentative engagement
    vector<int>  partner(n, -1), preference(n);        
    int cnt = 0;                                        //partner[i] : current partner of ith man
    while(cnt < n)                                      //preference[i] : the current preference the woman i is proposing to
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
    // cout << "Stable Matching is : " << endl;
    for(int i = 0; i < n; i++) 
    {
        cout<<i<<" "<<partner[i]<<endl;
        // cout << "Men : " << i << ", Women : " << partner[i] << endl;
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
