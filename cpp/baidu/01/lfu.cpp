#include <bits/stdc++.h>
using namespace std;
//双向链表+哈希
class LRUCache
{
public:
    LRUCache()
    {
        lt.clear();
        mp.clear();
    }
    struct po
    {
        int k, v;
    };
    void erase(int key)
    {
        auto it = mp[key];
        lt.erase(it);
        mp.erase(key);
        --siz;
    }
    int get(int key)
    {
        auto it = mp.find(key);
        if (it == mp.end())
        {
            return -1;
        }

        po val = *(it->second);
        lt.erase(it->second);
        lt.push_back(val);
        mp[key] = --lt.end();
        return val.v;
    }

    int erasehead()
    {
        auto pnd = lt.begin();
        int rt = pnd->k;
        mp.erase(pnd->k);
        lt.pop_front();
        return rt;
    }
    int put(int key, int val)
    {
        int rt = -1;
        auto it = mp.find(key);
        if (it == mp.end())
        {
            if (siz + 1 > cap)
            {
                rt = erasehead();
            }
            lt.push_back({key, val});
            mp[key] = --lt.end();
            ++siz;
        }
        else
        {
            lt.erase(it->second);
            lt.push_back({key, val});
            mp[key] = --lt.end();
        }
        return rt;
        // auto it = mp.insert(make_pair(key, val)); 返回 iterator和bool
    }
    list<po> lt;
    unordered_map<int, list<po>::iterator> mp;
    static int cap;
    static int siz;
};

// int LRUCache::cap = 0;
// int LRUCache::siz = 0;
class LFUCache
{
public:
    friend class LRUCache;
    LFUCache(int capacity)
    {
        mxn = capacity;
        LRUCache::cap = mxn;
        LRUCache::siz = 0;
    }

    int get(int key)
    {
        auto it = cnt.find(key);
        if (it == cnt.end())
            return -1;
        int ct = it->second;
        return ump[ct].get(key);
    }

    void add(int key, int val, int ct)
    {
        cnt[key] = ct;
        auto ij = ump.find(ct);

        if (ij == ump.end())
        {
            ump[ct] = *(new LRUCache());
        }
        int rt = ump[ct].put(key, val);
        if (rt > -1)
        {
            cnt.erase(rt);
        }
    }
    void put(int key, int value)
    {
        auto it = cnt.find(key);
        if (it == cnt.end())
        {
            add(key, value, 1);
        }
        else
        {
            int rc = it->second;
            ump[rc].erase(key);
            cnt.erase(key);
            add(key, value, rc + 1);
        }
    }
    int mxn;
    unordered_map<int, int> cnt;
    unordered_map<int, LRUCache> ump;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    unordered_map<int, int> mp;
    auto it = mp.insert(make_pair(8, 9));
    cout << (typeid(it.first) == typeid(unordered_map<int, int>::iterator)) << endl;
    return 0;
}