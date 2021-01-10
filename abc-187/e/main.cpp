#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <set>
using namespace std;
#define ALL(x) x.begin(), x.end()
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)

int main()
{
    int N;

    std::cin >> N;
    std::vector<int> A(N + 1);
    std::vector<int> B(N + 1);
    std::vector<int> IDX(N + 1);
    iota(ALL(IDX), 0);                // 0スタートのiota
    std::vector<int> piece(N + 1, 0); // ポイントを溜めていく。
    std::vector<std::vector<int>> childs_of_V(N + 1, std::vector<int>());
    std::vector<std::vector<int>> connectivity(N + 1, std::vector<int>());
    std::vector<int> parent(N + 1);

    REP(_i, N - 1)
    {
        int i = _i + 1;
        std::cin >> A[i] >> B[i];
        // 接続性追加

        int minV = A[i] < B[i] ? A[i] : B[i];
        int largerV = A[i] > B[i] ? A[i] : B[i];

        // 相互に接続
        connectivity[minV].push_back(largerV);
        connectivity[largerV].push_back(minV);

        // 下のパートに書く
        // 子供の追加
        // B[i] にとっての親は？
        // これ意味ないのでは？
        // childs_of_V[minV].push_back(largerV);
        // parent[largerV] = A[minV];

        /*
            この条件だと、A[i] B[i] が親、子と言い切れない可能性が出てくる？
              0
              1
            2  3 
            だとして、
            2 1 (2->1)
            0 1 (0->1) だと、矛盾する。
            本来の連結性としては 0 を root にすればよいはずだった。

            対策:
            小さい数を常に親とすればよい。 -> 不可能なケースがある。
        */
        /*
                1
                ^
                |
                3
                ^
                |
                2
                みたいになっている場合は、どうするの？親にはなれないけど...
       */
    }

    // 数が小さい方が親なので、不要。
    // 1を頂点にして、エッジを繋ぎなおしたい ( type で親に行くか/子に行くか の判定のため )
    {
        std::queue<int> mQ;
        std::set<int> done_v;
        mQ.push(1); // 1からスタート
        while (!mQ.empty())
        {
            int _e = mQ.front();
            // _e に対して、その子供を全部見る。
            mQ.pop();
            for (auto v : connectivity[_e])
            {
                if (done_v.find(v) != done_v.end())
                {
                    // もし見つけた場合 | すでにつなぎなおしをやった。
                    continue;
                }
                else
                {
                    mQ.push(v);
                    childs_of_V[_e].push_back(v);
                    parent[v] = _e;
                }
            }
            done_v.insert(_e);
        }
    }

    int Q;
    cin >> Q;
    REP(i, Q)
    {
        int t, e, x;
        cin >> t >> e >> x; // Ai が親、 Bi が

        // t = 1 のとき、
        // 頂点aeiから辺をたどって頂点beiを通らずに到達できるような全ての頂点vに対して、cvをcv+xiに書き換える。
        if (t == 1)
        {
            int a, b;
            a = A[e];
            b = B[e]; // B を通らない。 B は親か？
            // 問題: どっちが親かすぐ判定できないと、困る
            if (a < b)
            {
                // a が親のとき、 b を通らずに到達できるのは
                // a の一番のroot まで戻り、足し算をして、
                // b 以下に対しては、マイナスする。
                // int now_e = a;
                // while (parent[now_e] != 0)
                // {
                //     now_e = parent[now_e];
                // }
                // この時点で、now_e にはrootが入っている。 (1のことでは？)
                // 1なので計算は不要
                piece[1] += x;
                piece[b] -= x;
            }
            else
            {
                // b が親のとき、 a を通らずに到達できるのは
                // b の子供だけ
                piece[b] += x;
            }
        }
        else
        {
            // t=2のとき
            // // 頂点beiから辺をたどって頂点aeiを通らずに到達できるような全ての頂点vに対して、cvをcv+xiに書き換える。
            int a, b;
            a = A[e];
            b = B[e]; // B を通らない。 B は親か？
            if (a < b)
            {
                piece[b] += x;
            }
            else
            {
                piece[b] -= x;
                piece[1] += x;
            }
        }
    }

    REP(_i, N)
    {
        int i = _i + 1;
        int score = 0;
        int now_e = i;
        while (parent[now_e] != 0)
        {
            score += piece[now_e];
        }
        score += piece[now_e];
        cout << score << endl;
    }
}