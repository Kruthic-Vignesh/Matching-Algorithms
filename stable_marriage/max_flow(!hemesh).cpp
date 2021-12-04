#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int nn = 2e3+5;
ll adj[nn][nn];

bool bfs(vector<ll> &parent, ll s, ll t)
{
    queue<ll> nodes;
    vector<bool> visited(t+1, false);
    nodes.push(s);
    visited[s] = true;

    while(!nodes.empty() && !visited[t])
    {
        ll curr_node = nodes.front();
        nodes.pop();
        ll cap;
        for(ll i = 0; i <= t; i++)
        {
            cap = adj[curr_node][i];
            if(!visited[i] && cap)
            {
                visited[i] = true;
                parent[i] = curr_node;
                nodes.push(i);
            }
        }
    }

    return visited[t];
}

void sol()
{
    ll flowmax = 0;
    ll nx, ny;
    cin>>nx>>ny;
    for(ll i = 0; i <= nx+ny+1; i++)
    {
        for(ll j = 0; j <= nx+ny+1; j++)
        {
            adj[i][j] = 0;
        }
    }
    const ll s = 0;         //source node
    const ll t = nx+ny+1;   //sink node
    ll k, node;
    for(ll i = 1; i <= nx; i++)
    {
        cin>>k;
        adj[s][i] = 1;
        for(ll j = 0; j < k; j++)
        {
            cin>>node;
            node += nx;
            adj[i][node] = 1;
        }
    }
    for(ll j = nx+1; j <= nx+ny; j++)
    {
        adj[j][t] = 1;
    }
    vector<ll> parent(t+1);
    while(bfs(parent, s, t))
    {
        ll v = t, add = 1e18, u;
        while(v != s)
        {
            u = parent[v];
            add = min(add, adj[u][v]);
            v = u;
        }
        flowmax += add;
        v = t;
        while(v != s)
        {
            u = parent[v];
            adj[u][v] -= add;
            adj[v][u] += add;
            v = u;
        }
    }
    cout<<flowmax<<endl;
    for(ll i = 1; i <= nx; i++)
    {
        for(ll j = nx+1; j <= t-1; j++)
        {
            if(!adj[i][j] && adj[j][i])
            {
                cout<<i<<" "<<j-nx<<endl;
            }
        }
    }
}

int main()
{
    ll t = 1;
    //cin>>t;
    for(ll i = 0; i < t; i++) 
        sol();
    return 0;
}
