#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int characterReplacement(string &str, int k)
    {
        vector<int> v[128];
        int len = str.length();
        for (int i = 0; i < len; ++i)
        {
            v[str[i]].emplace_back(i);
        }
        int ans = 0, sz = 0;
        for (int i = 'A'; i <= 'Z'; ++i)
        {
            sz = max(sz, int(v[i].size()));
        }
        vector<int> s(sz + 1);
        for (int i = 'A'; i <= 'Z'; ++i)
        {
            int uj = v[i].size();
            if (uj < 2)
            {
                ans = max(ans, min(len, 1 + k));
                continue;
            }
            s[0] = 0;
            for (int j = 1; j < uj; ++j)
            {
                s[j] = s[j - 1] + v[i][j] - v[i][j - 1] - 1;
            }
            for (int j = 0, rt = 0; j < uj; j++)
            {
                int l = rt, r = uj - 1, mid;
                while (l <= r)
                {
                    mid = (l + r) >> 1;
                    if (s[mid] - s[j] <= k)
                    {
                        l = mid + 1;
                        rt = mid;
                    }
                    else
                    {
                        r = mid - 1;
                    }
                }
                ans = max(ans, v[i][rt] - v[i][j] + 1 + k - (s[rt] - s[j]));
                if (rt == uj - 1)
                    break;
            }
        }
        return min(ans, len);
    }
};

int main()
{
    int a, b, c, d[16], e, f;
    printf("%x\n", &a);
    printf("%x\n", &b);
    printf("%x\n", &c);
    printf("%x %x %x %x %x\n", &d[0], &d[1], &d[2], &d[3], &d[15]);
    printf("%x\n", &e);
    printf("%x\n", &f);
    return 0;
}