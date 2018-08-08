#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

string word[6000];
int pre[6000] = {0};
int n = 0;
bool check[6000] = {0};
vector<int> neighbor[6000];
queue<int> q;

bool isConnected(int u, int v) {
    int diff = 0;
    for(int i=0; i<5; i++) {
        if (word[u][i]!=word[v][i]) {
            diff++;
            if (diff > 1)
                return false;
        }
    }
    return true;
}
void bfs(int u) {
    q.push(u);
    check[u] = true;
    while(!q.empty()) {
        u = q.front();
        for(int v:neighbor[u]) {
            if(check[v]==false) {
                q.push(v);
                check[v]=true;
                pre[v] = u;
            }
        }
        q.pop();
    }
}
void p1() {
    int connected, posu, posv;
    stack<int> way;
    string u, v;

    cin >> u >> v;
    for(int i=1; i<=n; i++) {
        if(word[i]==u)
            posu = i;
        else if(word[i]==v)
            posv = i;
    }

    bfs(posu);
    connected = 1;
    for(int i=0; i<n; i++) {
        if(check[i]==false) {
            connected++;
            bfs(i);
        }
    }
    cout << connected << endl;

    way.push(posv);
    while(posv!=posu) {
        posv = pre[posv];
        way.push(posv);
    }
    while(!way.empty()) {
        cout << word[way.top()] << " ";
        way.pop();
    }
}
int main() {
    ifstream inFile;
    inFile.open("sgb-words.txt");
    while (inFile >> word[n+1]) {
        n++;
    }

    for(int i=1; i<n; i++) {
        for(int j=i+1; j<=n; j++) {
            if (isConnected(i,j)) {
                neighbor[i].push_back(j);
                neighbor[j].push_back(i);
            }
        }
    }

    p1();
    return 0;
}
