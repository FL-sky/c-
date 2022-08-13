#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int val;
    Node *nxt;
    Node(int val = 0, Node *nxt = NULL) : val(val), nxt(nxt) {}
};

int getval(vector<int> &a, int pos)
{
    if (pos >= a.size())
        return 0;
    return a[pos];
}
Node *addlist(Node *l1, Node *l2)
{
    vector<int> a, b, c;
    Node *it;
    it = l1;
    while (it)
    {
        a.push_back(it->val);
        it = it->nxt;
    }
    it = l2;
    while (it)
    {
        b.push_back(it->val);
        it = it->nxt;
    }
    for (int i = 0; i < a.size() || i < b.size(); i++)
    {
        c.push_back(getval(a, i) + getval(b, i));
    }
    c.push_back(0);
    for (int i = 0; i < c.size(); i++)
    {
        if (c[i] > 9)
        {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
    if (c.size() > 1 && *c.rbegin() == 0)
        c.pop_back();
    Node *rt = new Node();
    rt->val = c[0];
    it = rt;
    Node *tail = rt;
    for (int i = 1; i < c.size(); i++)
    {
        it = new Node(c[i]);
        tail->nxt = it;
        tail = it;
    }
    return rt;
}

int main()
{
    Node *l1, *l2, *it, *tail;
    int n, val;
    cin >> n;
    {
        l1 = NULL;
        for (int i = 0; i < n; i++)
        {
            cin >> val;
            it = new Node(val);
            if (l1 == NULL)
            {
                l1 = it;
            }
            else
            {
                tail->nxt = it;
            }
            tail = it;
        }
    }
    //
    cin >> n;
    {
        l2 = NULL;
        for (int i = 0; i < n; i++)
        {
            cin >> val;
            it = new Node(val);
            if (l2 == NULL)
            {
                l2 = it;
            }
            else
            {
                tail->nxt = it;
            }
            tail = it;
        }
    }
    Node *rt = addlist(l1, l2);
    it = rt;
    while (it)
    {
        printf("%d ", it->val);
        it = it->nxt;
    }
    return 0;
}