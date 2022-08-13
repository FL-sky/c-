#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<string> ans;
    string str;
    char stk[20];
    void dfs(int u, int ct, int ls)
    {
        if (u == str.length() || ct > 4)
        {
            if (ct == 4)
            {
                stk[ls - 1] = 0;
                ans.push_back(stk);
            }
            return;
        }
        if (str[u] == '0')
        {
            stk[ls] = '0', stk[ls + 1] = '.';
            dfs(u + 1, ct + 1, ls + 2);
        }
        else
        {
            int t = 0;
            for (int i = 1; i <= 3; i++)
            {
                t = t * 10 + str[u + i - 1] - '0';
                if (t >= 0 && t < 256)
                {
                    for (int j = 0; j < i; j++)
                    {
                        stk[ls + j] = str[u + j];
                    }
                    stk[ls + i] = '.';
                    dfs(u + i, ct + 1, ls + i + 1);
                }
                else
                {
                    break;
                }
            }
        }
    }
    vector<string> restoreIpAddresses(string &s)
    {
        str = s;
        dfs(0, 0, 0);
        return ans;
    }
};

int main()
{

    return 0;
}