#include <iostream>
#include <cstdlib>
using namespace std;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)

long long pow(long long a, long long p)
{
    if (p == 0)
        return 1;
    return a * pow(a, p - 1);
}

int main(int argc, char *argv[])
{
    long long N, M;
    // std::cin >> N >> M;
    // std::cin >> N;
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    // M = 3;
    REP(i, N)
    {
        long long di = (pow(10, i) / M);
        cout << "10**" << i << ", M = " << M << endl;
        cout << "di: " << di << endl;
        // cout << "ans: " << di % M << endl;
    }

    // std::cout << larger(a, b) << std::endl;
}