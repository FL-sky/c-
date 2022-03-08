#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    const static int N = 1001;
    int lx[N], rx[N], li[N], ri[N];
    long long subArrayRanges(vector<int> &a)
    {
        long long rt = 0;
        int n = a.size();
        lx[0] = -1;
        li[0] = -1;
        for (int i = 1; i < n; ++i) //一个取等，一个不取等~我以为是自己写的bug，结果对了
        {
            int j = i - 1;
            while (j > -1 && a[i] >= a[j])
            {
                j = lx[j];
            }
            lx[i] = j;
            //
            j = i - 1;
            while (j > -1 && a[i] <= a[j])
            {
                j = li[j];
            }
            li[i] = j;
        }
        //
        rx[n - 1] = n;
        ri[n - 1] = n;
        for (int i = n - 2; i >= 0; --i)
        {
            int j = i + 1;
            while (j < n && a[i] > a[j])
            {
                j = rx[j];
            }
            rx[i] = j;
            //
            j = i + 1;
            while (j < n && a[i] < a[j])
            {
                j = ri[j];
            }
            ri[i] = j;
        }
        for (int i = 0; i < n; ++i)
        {
            rt = rt + ((long long)(rx[i] - i) * (i - lx[i]) - (long long)(ri[i] - i) * (i - li[i])) * a[i];
        }
        return rt;
    }
};
int main()
{
    Solution sl;
    vector<int> v = {4, -2, -3, 4, 1};
    int ans = sl.subArrayRanges(v);
    cout << ans << endl;

    return 0;
}