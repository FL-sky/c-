#include <bits/stdc++.h>
using namespace std;

const int MU = 1 << 14, MOD = MU - 1;
class LRUCache
{
    struct LST
    {
        int x, y;
        int prev, nxt;
        LST()
        {
            x = -1;
        }
    } lt[MU + 2];
    int hsh[10002];
    int cap, siz, sq;
    const static int head = MU, tail = MU + 1;

public:
    LRUCache(int capacity)
    {
        cap = capacity;
        lt[head].nxt = tail;
        lt[tail].prev = head;
        siz = 0;
        memset(hsh, -1, sizeof(hsh));
        sq = 0;
    }
    void remov(int nd)
    {
        LST &ld = lt[nd];
        lt[ld.nxt].prev = ld.prev;
        lt[ld.prev].nxt = ld.nxt;
    }
    void pushFront(int nd)
    {
        lt[nd].prev = head;
        lt[nd].nxt = lt[head].nxt;
        lt[lt[head].nxt].prev = nd;
        lt[head].nxt = nd;
    }
    void pushBack(int nd)
    {
        lt[lt[tail].prev].nxt = nd;
        lt[nd].prev = lt[tail].prev;
        lt[nd].nxt = tail;
        lt[tail].prev = nd;
    }
    int get(int key)
    {
        int ptr = hsh[key];
        if (ptr != -1)
        {

            remov(ptr);
            pushBack(ptr);

            return lt[ptr].y;
        }
        return -1;
    }
    int newnode(int x, int y)
    {
        while (lt[sq].x != -1)
            sq = (sq + 1) & MOD;
        lt[sq].x = x, lt[sq].y = y;
        return sq;
    }
    void put(int key, int value)
    {
        int hsk = hsh[key];
        if (hsh[key] != -1)
        {
            remov(hsk);
            pushBack(hsk);
            lt[hsk].y = value;
            return;
        }
        if (cap < ++siz)
        {
            int frt = lt[head].nxt;
            hsh[lt[frt].x] = -1;
            lt[frt].x = -1;
            remov(frt);
        }
        pushBack(hsh[key] = newnode(key, value));
    }
};

int main()
{

    vector<string> op = {"LRUCache", "put", "put", "get", "put", "put", "get"};
    vector<vector<int>> val = {{2}, {2, 1}, {2, 2}, {2}, {1, 1}, {4, 1}, {2}};

    // LRUCache* obj = new LRUCache(capacity);
    // int param_1 = obj->get(key);
    // obj->put(key,value);
    LRUCache obj(2);
    for (int i = 0; i < op.size(); i++)
    {
        int rt = -4;
        if (op[i] == "LRUCache")
        {
            obj = LRUCache(LRUCache(val[i][0]));
        }
        else if (op[i] == "put")
        {
            obj.put(val[i][0], val[i][1]);
        }
        else if (op[i] == "get")
        {
            rt = obj.get(val[i][0]);
        }
        printf("%4d", rt);
    }
    return 0;
}