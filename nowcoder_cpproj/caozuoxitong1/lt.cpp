#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stdbool.h>
#include <queue>
using namespace std;

const int maxn = 1e5 + 10;

struct node
{
    int next, to, flow, cost;
};

node edge[maxn];
int head[maxn], flow[maxn], pre[maxn], dist[maxn], last[maxn];
int n, m, st, en;
int tot;
bool vis[maxn];

void add(int u, int v, int w, int c)
{
    edge[tot] = (node){head[u], v, w, c};
    head[u] = tot++;
    edge[tot] = (node){head[v], u, 0, -c};
    head[v] = tot++;
}

bool spfa()
{
    memset(flow, 0x3f, sizeof(flow));
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    queue<int> Q;
    Q.push(st);
    vis[st] = true;
    dist[st] = 0;
    pre[en] = -1;
    while (!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = edge[i].next)
        {
            if (edge[i].flow > 0 && dist[edge[i].to] > dist[now] + edge[i].cost)
            {
                dist[edge[i].to] = dist[now] + edge[i].cost;
                pre[edge[i].to] = now;
                last[edge[i].to] = i;
                flow[edge[i].to] = min(flow[now], edge[i].flow);
                if (!vis[edge[i].to])
                {
                    vis[edge[i].to] = true;
                    Q.push(edge[i].to);
                }
            }
        }
    }
    // printf("%d\n", 1322333);
    return pre[en] != -1;
}

void mcmf()
{
    long long mcost = 0, mflow = 0;
    while (spfa())
    {
        mflow += flow[en];
        mcost += dist[en] * flow[en];
        int now = en;
        while (now != st)
        {
            edge[last[now]].flow -= flow[en];
            edge[last[now] ^ 1].flow += flow[en];
            now = pre[now];
        }
        // printf("%d\n", 1321);
    }
    printf("%lld %lld\n", mflow, mcost);
}

int main()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &st, &en);
    for (int i = 0; i < m; i++)
    {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        add(u, v, w, c);
    }
    mcmf();
    return 0;
}
