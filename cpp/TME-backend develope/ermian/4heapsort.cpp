//#include<iostream>
//#include<cstring>
//#include<stdio.h>
// using namespace std;
// const int MAX=100005;
// int heapn;
// struct DATA { int n; };
// struct NODE { DATA data;  int val; };
// bool cmp(NODE a, NODE b)//TRUE 为顶
//{
//	if (a.val == b.val)
//		return a.data.n < b.data.n;
//	return a.val < b.val;
//}
// NODE heap[MAX];
// void doheap() {
//	int now = heapn >> 1;
//	while (now)  {
//		int temp = now;
//		while ((temp << 1) <= heapn && !cmp(heap[temp], heap[temp << 1]) || (temp << 1) + 1 <= heapn && !cmp(heap[temp], heap[(temp << 1) + 1]))   {
//			int c = temp << 1;
//			if (c + 1 <= heapn && !cmp(heap[c], heap[c + 1]))
//				c++;
//			NODE a = heap[temp];
//			heap[temp] = heap[c];
//			heap[c] = a;
//			temp = c;
//		}
//		now--;
//	}
//}
//
// void add(NODE a) {///构造小根堆
//	heap[++heapn] = a;
//	int now = heapn;
//	while (now > 1 && cmp(heap[now], heap[now >> 1]))  {
//		NODE temp = heap[now];
//		heap[now] = heap[now >> 1];
//		heap[now >> 1] = temp;
//		now = now >> 1;
//	}
//}
//
// void del() {
//	heap[1] = heap[heapn];
//	heapn--;
//	int temp = 1;
//	while ((temp << 1) <= heapn && !cmp(heap[temp], heap[temp << 1]) || (temp << 1) + 1 <= heapn && !cmp(heap[temp], heap[(temp << 1) + 1])){
//		int c = temp << 1;
//		if (c + 1 <= heapn && !cmp(heap[c], heap[c + 1]))
//			c++;
//		NODE a = heap[temp];
//		heap[temp] = heap[c];
//		heap[c] = a;
//		temp = c;
//	}
//}
////堆排序是不稳定的。
// int main() {
//	heapn = 0;
//	int n;
//	cin >> n;
//	for (int i = 1; i <= n; i++)  {
//		NODE a;
//		cin >> a.val;
//		a.data.n = a.val;
//		add(a);
//	}
//	doheap();
//	while (heapn)  {
//		cout << heap[1].val << ' ' << heap[1].data.n << '\t';//cout << heap[1].val << ' ' << heap[1].data.n << endl;
//		del();
//	}
// }

#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
using namespace std;
const int MAX = 100005;
int heapn;

int heap[MAX];
void doheap()
{
    int now = heapn >> 1;
    while (now)
    {
        int temp = now;
        while ((temp << 1) <= heapn && !(heap[temp] < heap[temp << 1]) || (temp << 1) + 1 <= heapn && !(heap[temp] < heap[(temp << 1) + 1]))
        {
            int c = temp << 1;
            if (c + 1 <= heapn && !(heap[c] < heap[c + 1]))
                c++;
            swap(heap[c], heap[temp]);
            temp = c;
        }
        now--;
    }
}

void add(int a)
{ ///构造小根堆
    heap[++heapn] = a;
    int now = heapn;
    while (now > 1 && (heap[now] < heap[now >> 1]))
    {
        swap(heap[now], heap[now >> 1]);
        now = now >> 1;
    }
}

void del()
{
    heap[1] = heap[heapn];
    heapn--;
    int temp = 1;
    while ((temp << 1) <= heapn && !(heap[temp] < heap[temp << 1]) || (temp << 1) + 1 <= heapn && !(heap[temp] < heap[(temp << 1) + 1]))
    {
        int c = temp << 1;
        if (c + 1 <= heapn && !(heap[c] < heap[c + 1]))
            c++;
        swap(heap[c], heap[temp]);
        temp = c;
    }
}
//堆排序是不稳定的。
int main()
{
    int n;
    cin >> n;
    heapn = n;
    for (int i = 1; i <= n; i++)
    {
        /*int a;
        cin >> a;
        add(a);*/
        cin >> heap[i];
    }
    doheap(); //堆排序的两种方法 ： 1.插入建堆   1.全部读入调整建堆   2.删除
    while (heapn)
    {
        cout << heap[1] << endl;
        del();
    }
}