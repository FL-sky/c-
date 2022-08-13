#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20;
const ll MOD = 1e9 + 7;
ll mz[N][N];
ll gauss(int n)
{ //求矩阵K的n-1阶顺序主子式
    ll res = 1;
    for (int i = 1; i <= n - 1; i++)
    { //枚举主对角线上第i个元素
        for (int j = i + 1; j <= n - 1; j++)
        { //枚举剩下的行
            while (mz[j][i])
            { //辗转相除
                int t = mz[i][i] / mz[j][i];
                for (int k = i; k <= n - 1; k++) //转为倒三角
                    mz[i][k] = (mz[i][k] - t * mz[j][k] + MOD) % MOD;
                swap(mz[i], mz[j]); //交换i、j两行
                res = -res;         //取负
            }
        }
        res = (res * mz[i][i]) % MOD;
    }
    return (res + MOD) % MOD;
}
struct po
{
    int x, y;
} a[50];
int la;
int n, m;
ll K[N][N];
ll mx;
int iter = 0;
int fin = 0;
void dfs(int u, int us)
{
    if (fin)
        return;
    if (m == us)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                mz[i][j] = K[i][j];
            }
        }
        ll rt = gauss(n);
        if (mx < rt)
        {
            puts("\n---\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (K[i][j] < 0)
                        printf(" %d", 1);
                    else
                        printf(" %d", 0);
                }
                puts("");
            }
            puts("\n---\n");
            // fin = 1;
        }
        mx = max(mx, rt);
        ++iter;
        // if (iter % la == 0)
        //     printf("iter=%d\tmx=%lld\n", iter, mx);
        return;
    }
    if (u + m - us > la)
        return;
    int x = a[u].x, y = a[u].y;
    K[x][x]++;
    K[y][y]++;
    K[x][y]--;
    K[y][x]--;
    dfs(u + 1, us + 1);
    K[x][x]--;
    K[y][y]--;
    K[x][y]++;
    K[y][x]++;
    dfs(u + 1, us);
}
int main()
{
    while (scanf("%d%d", &n, &m) != EOF)
    {
        // ll mx = 0;
        // memset(K, 0, sizeof(K));
        // for (int i = 1; i <= m; i++)
        // {
        //     int x, y;
        //     scanf("%d%d", &x, &y);
        //     K[x][x]++;
        //     K[y][y]++;
        //     K[x][y]--;
        //     K[y][x]--;
        // }
        // ll rt = gauss(n);
        // mx = max(mx, rt);
        //
        mx = 0;
        la = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                a[la++] = {i, j};
            }
        }
        fin = 0;
        dfs(0, 0);
        cout << mx << endl;
    }
    return 0;
}