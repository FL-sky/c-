#include <bits/stdc++.h>
using namespace std;
template <typename T, typename IT>
void checkxx(T dat, IT itr)
{

    printf("%s\n", typeid(T).name());
    vector<IT> v;
    // auto it;//error: declaration of 'auto it' has no initializer // auto it;
    const int k = 3;
    for (auto it = dat.begin(); it != dat.end(); it++)
    {
        v.push_back(it);
        printf("%x,%-3d", &(*it), *it);
    }
    puts("");
    int i = 0;
    for (auto it = dat.begin(); i < dat.size(); i++, it++)
    {
        if (i == k)
        {
            dat.erase(it);
            break;
        }
    }

    for (auto it = v.begin(); it != v.end(); it++)
    {
        printf("%x,%-3d", &(*(*it)), *(*it));
    }
    puts("");
    for (auto it = dat.begin(); it != dat.end(); it++)
    {
        printf("%x,%-3d", &(*it), *it);
    }
}

int main()
{
    vector<int> v = {
        0,
        1,
        2,
        3,
        4, 5, 6};
    list<int> lt = {0, 1, 2, 3, 4, 5, 6};
    // map<int, int> mp = {
    //     {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    set<int> st = {0, 1, 2, 3, 4, 5, 6};
    puts("\nfor vector");
    checkxx(v, v.begin());
    puts("\nfor list");
    checkxx(lt, lt.begin());
    puts("\nfor set");
    checkxx(st, st.end());
    return 0;
}