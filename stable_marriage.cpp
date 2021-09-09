#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    int men[n][n], women[n][n];
    int posm[n][n], posw[n][n];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++) 
        {
            cin >> men[i][j];         //jth preference of ith man
            posw[i][men[i][j]] = j;   //posw[i][j] : preference of jth woman in ith man's list
        }
    }
    for(int i = 0; i < n; i++) 
    {
        for(int j = 0; j < n; j++) 
        {
            cin >> women[i][j];       //jth preference of ith woman 
            posm[i][women[i][j]] = j; //posw[i][j] : preference of jth woman in ith man's list
        }
    }
    vector<bool> rejected(n, true), engaged(n, false);  //rejected[i] == true if the ith woman does not have any tentative engagement
    vector<int>  partner(n, -1), preference(n);         //engaged[i] == true if the ith man is tentatively engaged
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