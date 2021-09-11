#include<bits/stdc++.h>

using namespace std;

#define endl "\n"
#define mod 1000000007

typedef long long ll;

int randf(int n)
{
    return rand()%n;
}

int main()
{
    freopen("myoutfile2.txt", "w", stdout);
    ll t = 4;
    cout<<t<<endl;
    for(ll z = 0; z < t; z++)
    {
        int n = rand()%100;
        cout<<n<<endl;
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
                cout<<men[i][j]<<" ";  
            }
            cout<<endl;
        }
        for(int i = 0; i < n; i++) 
        {
            random_shuffle(women[i], women[i]+n, randf);
            for(int j = 0; j < n; j++) 
            {
                cout<<women[i][j]<<" "; 
            }
            cout<<endl;
        }
    }
    fclose(stdout);
    return 0;
}
