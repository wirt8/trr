#include <iostream>
#include <stack>
#include <queue>

using namespace std;

const int oo = int(1e9);

int n, m;
int a, b, c, d, r;
int dist[101][101], pre[101][101];
bool check[101][101] = {0};
stack<int> way;
queue<int> q;
vector<int> neighbor[101];

void bfs(int u, int v) {
    int w;
    check[u][v] = true;
    q.push(u*n+v);
    while(!q.empty()) {
        w = q.front();
        u = w/n;
        v = w%n;
        q.pop();
        for(int k:neighbor[u])
            if(dist[k][v]>r && check[k][v]==false) {
                check[k][v] = true;
                q.push(k*n+v);
                pre[k][v] = u*n+v;
                if(k==c && v==d)
                    return;
            }
        for(int k:neighbor[v])
            if(dist[u][k]>r && check[u][k]==false) {
                check[u][k] = true;
                q.push(u*n+k);
                pre[u][k] = u*n+v;
                if(u==c && k==d)
                    return;
            }
    }
}
int main() {
    cin >> n >> m;
    int x, y, w;
    for(int i=0; i<n; i++)
        for(int j=i; j<n; j++) {
            if(i==j)
                dist[i][j] = 0;
            else {
                dist[i][j] = oo;
                dist[j][i] = oo;
            }
        }
    for(int i=0; i<m; i++) {
        cin >> x >> y >> w;
        dist[x][y] = w;
        dist[y][x] = w;
        neighbor[x].push_back(y);
        neighbor[y].push_back(x);
    }
    cin >> a >> b >> c >> d;
    cin >> r;

    //Floyd-Warshall
    for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    //
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            pre[i][j] = -1;
    bfs(a,b);
    if(check[c][d]==false)
        cout << "Khong the" << endl;
    else {
        x = c;
        y = d;
        while(pre[x][y]!=-1) {
            way.push(x*n + y);
            w = pre[x][y];
            x = w/n;
            y = w%n;
        }
        way.push(x*n + y);
        while(!way.empty()) {
            w = way.top(); way.pop();
            x = w/n;
            y = w%n;
            cout << x << " " << y << " " << dist[x][y] << endl;
        }
    }
    return 0;
}
