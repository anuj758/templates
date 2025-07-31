#include <bits/stdc++.h>
using namespace std;

class DSU{
    vector<int> parent, difference, size;
    public:
        DSU(int n){
            for(int i = 0; i <= n; i++){
                parent.push_back(i);
                size.push_back(1);
                difference.push_back(0);
            }
        }
        
        int findPar(int node){
            if(parent[node] == node) return node;
            int par = findPar(parent[node]);
            difference[node] = difference[parent[node]] + difference[node]; // error here
            parent[node] = par;
            return par;
        }
        
        bool unionsize(int u, int v, int wt){
            int par_u = findPar(u);
            int par_v = findPar(v);
            if(par_u == par_v){
                int diff = difference[u] - difference[v];
                return diff == wt;
            }
            
            if(size[par_u] <= size[par_v]){
                size[par_v] += size[par_u];
                parent[par_u] = par_v;
                difference[par_u] = wt + difference[v] - difference[u];
            }
            else{
                size[par_u] += size[par_v];
                parent[par_v] = par_u;
                difference[par_v] = -wt + difference[u] - difference[v];
            }
            return true;
        }
        
        int diff(int u, int v){
            int par_u = findPar(u);
            int par_v = findPar(v);
            if(par_u == par_v) return difference[u] - difference[v];
            return INT_MAX;
        }
};

void solve(){
    int n, q;
    cin >> n >> q;
    DSU d(n);
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int u, v, wt;
            cin >> u >> v >> wt;
            if(d.unionsize(u, v, wt) == false) cout << u << " " << v << " " << wt << "\n";            
        }
        else{
            int u, v;
            cin >> u >> v;
            cout << d.diff(u, v) << "\n";
        }
    }
}


int main(){
  solve();
  return 0;
}
