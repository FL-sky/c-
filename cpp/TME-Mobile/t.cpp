#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<set<int>> vs;
    int H, W;
    const int inf = 1e9;
    int getid(int x, int y)
    {
        return x * W + y;
    }
    vector<int> vis;
    void bfs(int x)
    {
        queue<int> que;
        vis[x] = 0;
        que.push(x);
        while (que.size())
        {
            int tp = que.front();
            que.pop();
            for (auto it : vs[tp])
            {
                if (vis[it] == inf)
                {
                    vis[it] = vis[tp] + 1;
                    que.push(it);
                }
            }
        }
    }
    vector<int> lightSticks(int h, int w, vector<int> &indices)
    {
        H = h + 1, W = w + 1;
        vs.resize(H * W);
        int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
        for (int i = 0; i <= h; i++)
        {
            for (int j = 0; j <= w; j++)
            {
                int idx = getid(i, j);
                for (int k = 0; k < 4; k++)
                {
                    int nx = i + dir[k][0], ny = j + dir[k][1];
                    int tid = getid(nx, ny);
                    if (nx >= 0 && nx < H && ny >= 0 && ny < W)
                    {
                        vs[idx].insert(tid);
                    }
                }
            }
        }
        for (auto it : indices)
        {
            int x = it / (w + W);
            int y = it % (w + W);
            if (y < w)
            {
                int a = getid(x, y);
                int b = a + 1;
                vs[a].erase(b);
                vs[b].erase(a);
            }
            else
            {
                y -= w;
                int a = getid(x, y);
                int b = a + W;
                vs[a].erase(b);
                vs[b].erase(a);
            }
        }
        vis.resize(W * H);
        int mxt = inf;
        vector<int> rt;
        for (int i = 0; i < vis.size(); i++)
        {
            fill(vis.begin(), vis.end(), inf);
            bfs(i);
            // int tp = *max_element(vis.begin(), vis.end());
            int tp = 0;
            for (int j = 0; j < vis.size(); j++)
            {
                if (vs[j].size())
                {
                    tp = max(tp, vis[j]);
                }
            }
            if (tp <= mxt)
            {
                if (tp < mxt)
                {
                    rt.clear();
                    rt.push_back(i);
                }
                else
                {
                    rt.push_back(i);
                }
                mxt = tp;
            }
        }
        if (mxt == inf)
            rt.clear();
        return rt;
    }
};
int main()
{
    Solution sl;
    int h = 17;
    int w = 18;
    vector<int> ind = {81, 376, 558, 470, 308, 395, 386, 315, 249, 499};

    // int h = 2;
    // int w = 2;
    // vector<int> ind = {2, 5, 6, 7, 8, 10, 11};
    auto rt = sl.lightSticks(h, w, ind);
    for (auto it : rt)
    {
        printf("%d ", it);
    }
    return 0;
}