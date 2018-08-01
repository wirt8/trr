#include <iostream>
#include <set>

using namespace std;

struct Edges {
    int u;
    int v;
};

int n, m, pos = 0;
int colorQueue[100000];
bool check[100000] = {false};
bool checkColor[12];
int colorNum[100000] = {0};
string colorList[12] = {"non", "red", "green", "blue", "orange", "brown", "gray", "purple", "yellow", "black", "pink", "white"};
set<int> neighbor[100000];
Edges edges[100000];

void bfs(int u) {
    colorQueue[pos] = u;
    pos++;
    check[u] = true;
    int mark = pos-1;
    while(mark<=pos) {
        u = colorQueue[mark];
        for(int v:neighbor[u]) {
            if(check[v]==false) {
                colorQueue[pos] = v;
                pos++;
                check[v] = true;
            }
        }
        mark++;
    }
}

void coloring() {
    int u;
    for(int i = pos-1; i>=0; i--) {
        u = colorQueue[i];
        for(int j=1; j<=11; j++) {
            checkColor[j] = true;
        }
        for(int v:neighbor[u]) {
            if(colorNum[v]!=0)
                checkColor[colorNum[v]]=false;
        }
        for(int j=1; j<=11; j++) {
            if(checkColor[j]==true) {
                colorNum[u]=j;
                break;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    int u, v;
    for(int i=0; i<m; i++) {
        cin >> u >> v;
        neighbor[u].insert(v);
        neighbor[v].insert(u);
        edges[i].u = u;
        edges[i].v = v;
    }

    int start = 1;
    for(int i=1; i<=n; i++) {
        if(neighbor[i].size() < neighbor[start].size())
            start = i;
    }
    bfs(start);
    for(int i=1; i<=n; i++) {
        if(check[i]==false) {
            bfs(i);
        }
    }

    coloring();

    cout << "graph dothi" << endl << "{" << endl;
    for(int i=1; i<=n; i++) {
        cout << "\t" << i << " [fillcolor=" << colorList[colorNum[i]] << ", style=filled];" << endl;
    }
    for(int i=0; i<m; i++) {
        cout << "\t" << edges[i].u << " -- " << edges[i].v << ";" << endl;
    }
    cout << "}";
    return 0;
}
