#include <iostream>
#include <queue>
#include <set>

using namespace std;

int n;
int pruferCode[100000];
set<int> neighbor[100000];
priority_queue<int> leaves;

int main() {
    cin >> n;
    int u, v;
    for(int i=0; i<n; i++) {
        cin >> u >> v;
        neighbor[u].insert(v);
        neighbor[v].insert(u);
    }

    for(int i=1; i<=n; i++)
        if(neighbor[i].size()==1) {
            leaves.push(-i);
        }

    int a, b;
    for(int i=0; i<n-1; i++) {
        a = -leaves.top();
        leaves.pop();
        b = *(neighbor[a].begin());
        pruferCode[i] = b;
        neighbor[b].erase(a);
        if(b!=0 && neighbor[b].size()==1) {
            leaves.push(-b);
        }
    }

    for(int i=0; i<n-1; i++) {
        cout << pruferCode[i] << " ";
    }

}
