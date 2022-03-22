#include <bits/stdc++.h>
using namespace std;

// class LRUCache
// {
//     list<pair<int, int>> cache;                             //创建双向链表
//     unordered_map<int, list<pair<int, int>>::iterator> map; //创建哈希表
//     int cap;

// public:
//     LRUCache(int capacity)
//     {
//         cap = capacity;
//     }

//     int get(int key)
//     {
//         if (map.count(key) > 0)
//         {
//             auto temp = *map[key];
//             cache.erase(map[key]);
//             map.erase(key);
//             cache.push_front(temp);
//             map[key] = cache.begin(); //映射头部
//             return temp.second;
//         }
//         return -1;
//     }

//     void put(int key, int value)
//     {
//         if (map.count(key) > 0)
//         {
//             cache.erase(map[key]);
//             map.erase(key);
//         }
//         else if (cap == cache.size())
//         {
//             auto temp = cache.back();
//             map.erase(temp.first);
//             cache.pop_back();
//         }
//         cache.push_front(pair<int, int>(key, value));
//         map[key] = cache.begin(); //映射头部
//     }
// };

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int tk[200002], ti; // time-key;
class LRUCache
{
public:
    int cap, idx, siz;
    int kv[10002]; // key-value
    int kt[10002]; // key-time
    LRUCache(int capacity)
    {
        cap = capacity;
        siz = idx = ti = 0;
        memset(kv, -1, sizeof(kv));
        memset(kt, -1, sizeof(kt));
    }

    int get(int key)
    {
        if (kv[key] == -1)
            return -1;
        tk[kt[key]] = -1;
        kt[key] = ++idx;
        tk[idx] = key;
        return kv[key];
    }
    int tk_begin(int &pos)
    {
        while (++pos < 200002)
        {
            if (tk[pos] != -1)
            {
                return tk[pos];
            }
        }
        return -1;
    }
    void put(int key, int value)
    {
        if (kv[key] == -1)
        {
            if (cap < ++siz)
            {
                int ke = tk_begin(ti);
                tk[ti] = kt[ke] = kv[ke] = -1;
            }
            kv[key] = value;
            kt[key] = ++idx;
            tk[idx] = key;
        }
        else
        {
            tk[kt[key]] = -1;
            kt[key] = ++idx;
            tk[idx] = key;
            kv[key] = value;
        }
    }
};

int main()
{

    vector<string> op = {"LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"};
    vector<vector<int>> val = {{2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {4, 4}, {1}, {3}, {4}};

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
    puts("---");
    list<int>::iterator it[500];
    for (int i = 0; i < 50; i++)
        cout << &(*it[i]) << endl;
    return 0;
}