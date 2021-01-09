#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
/*
問題文 N 頂点 N − 1 辺から成る木があり、 (木は全てそう)
頂点には 1 , 2 , … , N の番号が、辺には 1 , 2 , … , N − 1 の番号がついています。
辺 i は頂点 a i と頂点 b i を結びます。 この木の各頂点には 1 つの整数が書かれています。
頂点 i に書かれている整数を c i とします。はじめ、 c i = 0 です。 Q 個のクエリが与えられます。 
i 番目のクエリでは、整数 t i , e i , x i が与えられます。クエリの内容は以下の通りです。 
t i = 1 のとき : 頂点 a e i から辺をたどって頂点 b e i を通らずに到達できるような全ての頂点 v に対して、 c v を c v + x i に書き換える。
t i = 2 のとき : 頂点 b e i から辺をたどって頂点 a e i を通らずに到達できるような全ての頂点 v に対して、 c v を c v + x i に書き換える。 
すべてのクエリを処理した後、各頂点に書かれた整数を出力してください。
*/

/* 
疑問としては、
2≤N≤2×10^5
1≤ai,bi≤N与えられるグラフは木である
1≤Q≤2×10^5
という制約的に、最悪ケースでは10^10 になるから、TLEしない？と思った
(1クエリに対して O(N)で更新できるとしても、(簡単にどの頂点をスキップすればいいかがO(1) で取得できたとして ) *Q するので、O(NQ)になる。 )
合計とかじゃなくて 個別に 追加する時点で、結局どのクエリに対しては省かれるとかあるから、
逆に加算しないものだけを積み上げる戦略で行ったとしても、失敗しうる

事前にいける場所のリストを作成しておく。 
*/

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