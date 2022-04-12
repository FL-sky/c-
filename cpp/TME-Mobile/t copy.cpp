#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    typedef long long ll;
    long long maximumBeauty(vector<int> &fl, long long nf, int tgt, int ful, int part)
    {
        ll rt = 0;
        multiset<ll> mst;
        for (int i = 0; i < fl.size(); i++)
            mst.insert(fl[i]);
        ll wanshan = 0;
        while (mst.size() && *mst.rbegin() >= tgt)
        {
            wanshan++;
            mst.erase(--mst.end());
        }
        if (mst.size() <= 0)
        {
            return wanshan * ful;
        }
        //
        multiset<ll> nt = mst;
        vector<ll> ned, sum;
        ll lef = nf;
        int r = 0;
        while (nt.size())
        {
            if (tgt - *nt.rbegin() <= lef)
            {
                r++;
                lef -= tgt - *nt.rbegin();
                ned.push_back(tgt - *nt.rbegin());
                if (ned.size() == 1)
                {
                    sum.push_back(ned[0]);
                }
                else
                {
                    sum.push_back(*ned.rbegin() + *sum.rbegin());
                }
                nt.erase(--nt.end());
            }
            else
            {
                break;
            }
        }
        int l = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            ll ws = mid * ful;
            ll lef = nf - sum[mid - 1];
            map<ll, int> mp;
            auto it = mst.begin();
            for (int i = 0; i < mst.size() - mid; i++, it++)
            {
                mp[*it]++;
            }
            while (lef > 0)
            {
                        }
        }
        return rt;
    }
};

int main()
{
    Solution sl;

    return 0;
}