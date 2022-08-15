#include <bits/stdc++.h>
using namespace std;
//双向链表+哈希
class LRUCache
{
public:
    LRUCache(int capacity)
    {
        cap = capacity;
        lt.clear();
        mp.clear();
    }
    struct po
    {
        int k, v;
    };
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

    void put(int key, int val)
    {
        auto it = mp.find(key);
        if (it == mp.end())
        {
            if (lt.size() + 1 > cap)
            {
                auto pnd = lt.begin();
                mp.erase(pnd->k);
                lt.pop_front();
            }
            lt.push_back({key, val});
            mp[key] = --lt.end();
        }
        else
        {
            lt.erase(it->second);
            lt.push_back({key, val});
            mp[key] = --lt.end();
        }
        // auto it = mp.insert(make_pair(key, val)); 返回 iterator和bool
    }
    int cap;
    list<po> lt;
    unordered_map<int, list<po>::iterator> mp;
};

// LRUCache* obj = new LRUCache(capacity);
// int param_1 = obj->get(key);
// obj->put(key,value);

int main()
{
    unordered_map<int, int> mp;
    auto it = mp.insert(make_pair(8, 9));
    cout << (typeid(it.first) == typeid(unordered_map<int, int>::iterator)) << endl;
    return 0;
}