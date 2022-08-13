#include <bits/stdc++.h>
using namespace std;

class Solution
{ //方法三：逆向双指针
public:
    void merge(vector<int> &a, int m, vector<int> &b, int n)
    {
        int pa = m - 1, pb = n - 1;
        int lst = m + n - 1;
        while (pa >= 0 && pb >= 0)
        {
            if (a[pa] > b[pb])
            {
                a[lst] = a[pa--];
            }
            else
            {
                a[lst] = b[pb--];
            }
            --lst;
        }
        if (pb >= 0)
        {
            for (int i = 0; i <= pb; i++)
                a[i] = b[i];
        }
    }
};

int main()
{
    vector<int> a = {4, 5, 6, 0, 0, 0};
    int n = 3;
    vector<int> b = {1, 2, 3};
    int m = 3;
    Solution sl;
    sl.merge(a, n, b, m);

    return 0;
}