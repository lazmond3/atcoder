#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
/*
    ソートの基準を簡単に描けるようになりたい。
    ラムダを書くmakuro とかないかな。
    テストデータの作成 ( TLE の判定など )
*/

/*
    問題の勘違いで、高橋派は必ず投票してくれると思った。
    もし高橋派が投票しないとしたら、 ..
    1. 初期値の変更 (sum)
    2. ソート順位の変更
*/

int abs(int a)
{
    if (a > 0)
        return a;
    else
        return -a;
}

int main()
{
    long long N;

    std::cin >> N;
    std::vector<long long> AOKI(N);
    std::vector<long long> TAKAHASHI(N);
    std::vector<int> IDX(N);
    iota(ALL(IDX), 0);
    long long aoki_sum = 0;
    long long takahashi_sum = 0;

    REP(i, N)
    {
        std::cin >> AOKI[i] >> TAKAHASHI[i];
        aoki_sum += AOKI[i];
        // takahashi_sum += TAKAHASHI[i];
    }
    // 降順にソート
    // 単純にトータルでいいか
    sort(ALL(IDX), [&](auto i, auto j) {
        return (AOKI[i] * 2 + TAKAHASHI[i]) > (AOKI[j] * 2 + TAKAHASHI[j]);
    });

    // debug
    // REP(i, N)
    // {
    //     cout << "IDX[" << i << "] : " << IDX[i] << endl;
    // }
    if (aoki_sum < takahashi_sum)
    {
        cout << 0 << endl;
        return 0;
    }

    REP(i, N)
    {
        aoki_sum -= AOKI[IDX[i]];
        takahashi_sum += TAKAHASHI[IDX[i]] + AOKI[IDX[i]];
        if (aoki_sum < takahashi_sum)
        {
            cout << i + 1 << endl;
            return 0;
        }
    }

    // -> 高橋派が多ければ そこをとる必要はない。
    // 鷹八: T, 鈴木: W
    // a[i] - b[i] という基準でソートしたい。
    // b[i] - a[i] として、これが多いところから取っていきたい。
    // i を選択すると、
    // T + (b[i]), W - b[i] という遷移が起こる。
}