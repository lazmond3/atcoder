#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
using namespace std;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)

int pow(int a, int p)
{
    if (p == 0)
        return 1;
    return a * pow(a, p - 1);
}
int get_min_10n(int target)
{
    int f = 1;
    while (f < target)
    {
        f *= 10;
    }
    return f;
}

/*
    STEP 1. まず、1段階目に、 10^N が計算されると、1周りどういうシーケンスが生成されるかを計算する必要がある。
        最初の方は、ループしない可能性がある。 
        例: 82 /  6  = 13.66666666 の 13 はループしない。
        例: 10 /  6 =   1.66666666 の  1 はループしない。
        -> 10^N を割るときには
*/
void assert_10_6()
{
    int M = 6;
    set<int> already_amari;
    int now_num = M;

    while (true)
    {
        // このループ 1回 で 10 を 1回 かける
        int ten = get_min_10n(now_num);
        int amari = ten % M;
    }
}

int main(int argc, char *argv[])
{
}