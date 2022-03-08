// https://leetcode-cn.com/problems/minimum-size-subarray-sum/solution/chang-du-zui-xiao-de-zi-shu-zu-by-leetcode-solutio/
// 209. 长度最小的子数组

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        typedef long long ll;
        int n = nums.size();
        vector<ll> sum(n + 1);
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        int ans = n + 1;
        for (int i = 1; i <= n; i++)
        {
            int p = lower_bound(sum.begin(), sum.end(), target + sum[i - 1]) - sum.begin();
            if (p <= n)
            {
                ans = min(ans, p - i + 1);
            }
        }
        return ans <= n ? ans : 0;
    }
};

//方法二：前缀和 + 二分查找
//方法三：滑动窗口