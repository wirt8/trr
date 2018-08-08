#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

const int oo = 6000;

int n = 0, pos = 0, connected = 0;
vector<int> neighbor[6000];
bool check[6000] = {0};
int num[6000], low[6000], count[123] = {0}, mark[6000], pre[6000] = {0};
stack<int> st, way;
string word[6000];

void dfs(int u) {
    check[u] = true;
    pos++;
    num[u] = pos;
    low[u] = pos;
    st.push(u);
    for(int v:neighbor[u]) {
        if(check[v]) {
            if(low[u]>num[v])
                low[u] = num[v];
        } else {
            dfs(v);
            if(low[u]>low[v])
                low[u] = low[v];
        }
    }
    if(num[u] == low[u]) {
        connected++;
        int v;
        do {
            v = st.top();
            st.pop();
            num[v] = oo;
            low[v] = oo;
            mark[v] = connected;
        } while(v!=u);
    }
}

void bfs(int u, int v) {
    int q[6000];
    bool c[6000];
    int s = 0, e = 0;

    q[e] = u;
    c[u] = true;
    while(s<=e) {
        for(int y:neighbor[q[s]])
            if(c[y]==false) {
                e++;
                q[e] = y;
                c[y] = true;
                pre[y] = q[s];
                if(y==v)
                    return;
            }
        s++;
    }
}
bool isConnected(int u, int v) {
    int bias = 0;
    for(int i=1; i<5; i++)
        count[word[u][i]]++;
    for(int i=0; i<5; i++) {
        if(count[word[v][i]]==0)
            bias++;
        else
            count[word[v][i]]--;
    }
    for(int i=1; i<5; i++)
        count[word[u][i]] = 0;
    if(bias == 1)
        return true;
    return false;
}

void pa() {
    for(int i=1; i<=n; i++)
        if(check[i]==false) {
            dfs(i);
        }
    cout << connected << endl;
}

void pb() {
    string u;
    int posu = 0;
    cin >> u;
    for(int i=1; i<=n; i++)
        if(word[i]==u) {
            posu = i;
            break;
        }
    for(int i=1; i<=n; i++)
        if(mark[i]==mark[posu])
            cout << word[i] << " ";
    cout << endl;
}

void pc() {
    string u, v;
    int posu, posv;
    cin >> u >> v;
    for(int i=1; i<=n; i++)
        if(word[i]==u)
            posu = i;
        else if(word[i]==v)
            posv = i;

    bfs(posu, posv);

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
    while(inFile >> word[n+1]) {
        n++;
    }

    for(int i=1; i<n; i++)
        for(int j=i+1; j<=n; j++) {
            if(isConnected(i,j)) {
                neighbor[i].push_back(j);
            }
            if(isConnected(j,i)) {
                neighbor[j].push_back(i);
            }
        }

    pa();
    pb();
    pc();

    return 0;
}
