#include <iostream>
using namespace std;
int func(int a, double b) { return ((a) + (b)); }
int func(double a, float b) { return ((a) + (b)); }
int func(float a, int b) { return ((a) + (b)); }
int main() { return 0; }