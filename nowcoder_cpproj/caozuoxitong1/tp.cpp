#include <stdio.h> //
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

const int inf = 1000000000;
const int N = 20000, M = 500000;
struct Edge
{
    int v, f, nxt;
};
int n, src, sink;
int g[N + 10], nume;
Edge e[N * 2 + 10];

void addedge(int u, int v, int c)
{
    e[++nume].v = v;
    e[nume].f = c;
    e[nume].nxt = g[u];
    g[u] = nume;

    e[++nume].v = u;
    e[nume].f = 0;
    e[nume].nxt = g[v];
    g[v] = nume;
}

void init()
{
    memset(g + 1, 0, sizeof(int) * n);
    nume = 1;
    //
}

queue<int> que;
bool vis[N + 10];
int dist[N + 10];

void bfs()
{
    memset(dist + 1, 0, sizeof(int) * n);
    while (!que.empty())
        que.pop();
    vis[src] = true;
    que.push(src);
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        for (int i = g[u]; i; i = e[i].nxt)
        {
            if (e[i].f && !vis[e[i].v])
            {
                que.push(e[i].v);
                dist[e[i].v] = dist[u] + 1;
                vis[e[i].v] = true;
            }
        }
    }
}

int dfs(int u, int delta)
{
    if (u == sink)
        return delta;
    int ret = 0;
    for (int i = g[u]; i; i = e[i].nxt)
    {
        if (e[i].f && dist[e[i].v] == dist[u] + 1)
        {
            int dd = dfs(e[i].v, min(e[i].f, delta));
            e[i].f -= dd;
            e[i ^ 1].f += dd;
            delta -= dd;
            ret += dd;
        }
    }
    return ret;
}

int maxflow()
{
    int ret = 0;
    while (true)
    {
        memset(vis + 1, 0, sizeof(bool) * n);
        bfs();
        if (!vis[sink])
            return ret;
        ret += dfs(src, inf);
    }
    return ret;
}
int main()
{
    int m, u, v, w;
    while (~scanf("%d%d", &m, &n))
    {
        init();
        while (m--)
        {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
        }
        src = 1, sink = n;
        printf("%d\n", maxflow());
    }
    return 0;
}