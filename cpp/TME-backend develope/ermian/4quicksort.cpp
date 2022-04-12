#include <cstdio>

int a[1000]; //全局变量，方便调试
void quicksort(int left, int right)
{ /// void quicksort(int *a, int left, int right) {
    if (right <= left)
        return;
    int i = left, j = right;
    int record = a[right];
    while (i < j)
    {
        while (a[i] < record && i < j)
            i++;
        if (i < j)
        {
            a[j] = a[i];
            j--;
        }
        while (a[j] > record && i < j)
            j--;
        if (i < j)
        {
            a[i] = a[j];
            i++;
        }
    }
    a[i] = record;
    quicksort(left, i - 1);
    quicksort(i + 1, right);
}

int main()
{
    int n, i;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    quicksort(0, n - 1);
    for (i = 0; i < n; i++)
        printf("%d\t", a[i]);
    return 0;
}