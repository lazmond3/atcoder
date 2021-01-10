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

/*
- 14285714285714
のように、10^N に対して、どうやって文字列を作るか
string の繰り返し。
これの検知は？ 後回し。
*/
/*
10^N / M    - (少数部分)
M進数表示ってどうやるんだ？

10**1, M = 9997 and : 0 di: 0
10**2, M = 9997 and : 0 di: 0
10**3, M = 9997 and : 0 di: 0
10**4, M = 9997 and : 1 di: 1
10**5, M = 9997 and : 10 di: 10
10**6, M = 9997 and : 100 di: 100
10**7, M = 9997 and : 1000 di: 1000
10**8, M = 9997 and : 6 di: 10003
10**9, M = 9997 and : 60 di: 100030
10**10, M = 9997 and : 600 di: 1000300
10**11, M = 9997 and : 6000 di: 10003000
10**12, M = 9997 and : 27 di: 100030009
10**13, M = 9997 and : 270 di: 1000300090
10**14, M = 9997 and : 2700 di: 10003000900
10**15, M = 9997 and : 7008 di: 100030009002
10**16, M = 9997 and : 108 di: 1000300090027
10**17, M = 9997 and : 1080 di: 10003000900270
10**18, M = 9997 and : 803 di: 100030009002700
10**19, M = 9997 and : 8038 di: 1000300090027008
10**20, M = 9997 and : 406 di: 10003000900270082
10**21, M = 9997 and : 4056 di: 100030009002700816
10**22, M = 9997 and : 540 di: 1000300090027008128

これだと、そもそもlong long のところでループ検知できないなあ
*/
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
        cout << "10**" << i << ", M = " << M << " ";
        cout << "and : " << di % M << " ";
        cout << "di: " << di << endl;
        // cout << "ans: " << di % M << endl;
    }

    // std::cout << larger(a, b) << std::endl;
}