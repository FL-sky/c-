#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct tmp2 //重写仿函数
{
    bool operator()(ListNode *&a, ListNode *&b) const
    {
        return a->val > b->val;
    }
};
class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode *rt = new ListNode;
        ListNode *tail = rt;
        priority_queue<ListNode *, vector<ListNode *>, tmp2> pq;
        for (int i = 0; i < lists.size(); i++)
        {
            if (lists[i])
            {
                pq.push(lists[i]);
            }
        }
        while (pq.size())
        {
            auto tp = pq.top();
            pq.pop();
            if (tp->next)
            {
                pq.push({tp->next});
            }
            tail->next = tp;
            tail = tp;
        }
        return rt->next;
    }
};
int main()
{

    return 0;
}