#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <set>
using namespace std;
#define ALL(x) x.begin(), x.end()
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define int long long

const bool debug = false;
signed main()
{
    int N;

    std::cin >> N;
    std::vector<int> A(N + 1);
    std::vector<int> B(N + 1);
    std::vector<int> which_is_older_index(N + 1);
    iota(ALL(which_is_older_index), 0); // 0スタートのiota
    std::vector<int> piece(N + 1, 0);   // ポイントを溜めていく。
    std::vector<std::vector<int>> childs_of_V(N + 1, std::vector<int>());
    std::vector<std::vector<int>> connectivity(N + 1, std::vector<int>());
    std::vector<int> parent(N + 1, 0);

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
    // cout << "---- after edge reading" << endl;

    // 数が小さい方が親なので、不要。 <- 必要だった。
    // 1を頂点にして、エッジを繋ぎなおしたい ( type で親に行くか/子に行くか の判定のため )
    {
        std::queue<int> mQ;
        std::set<int> done_v;
        mQ.push(1); // 1からスタート
        int kazoeage_now = 1;
        while (!mQ.empty())
        {
            // _e に対して、その子供を全部見る。
            int _e = mQ.front();
            mQ.pop();

            for (auto v : connectivity[_e])
            {
                if (done_v.find(v) != done_v.end())
                {
                    // もし見つけた場合 | すでにつなぎなおしをやった。
                    // 親である。
                    continue;
                }
                else
                {
                    mQ.push(v);
                    childs_of_V[_e].push_back(v);
                    parent[v] = _e;
                    // どちらが親かを数字の順番で高速に判定できる。
                    which_is_older_index[v] = ++kazoeage_now;
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
        cin >> t >> e >> x;

        int a, b;
        a = A[e];
        b = B[e];
        // t = 1 のとき、
        // 頂点aeiから辺をたどって頂点beiを通らずに到達できるような全ての頂点vに対して、cvをcv+xiに書き換える。
        bool is_to_upper = false;
        bool is_start_from_a = t == 1;
        // a からスタートできるようにswapする。
        if (!is_start_from_a)
        {
            swap(a, b);
        }
        // a からスタートするとき、bを通らないようにいく。
        // b のほうが数が大きければ、子 なので、子を通らないということは、上に行くということ。
        // a の他の子供にも与える必要があるが、打ち消しは b 以降で大丈夫。
        is_to_upper = (which_is_older_index[a] < which_is_older_index[b]);

        // 実際の処理
        if (is_to_upper)
        {
            piece[1] += x;
            // 打ち消しは b 以降で大丈夫。
            piece[b] -= x;
        }
        else if (!is_to_upper)
        {
            piece[a] += x;
        }
    }

    if (debug)
    {

        cout << "parent:" << endl;
        REP(i, N + 1)
        {
            cout << "parent of[" << i << "] : " << parent[i] << endl;
        }

        cout << "childs:" << endl;
        REP(i, N + 1)
        {
            cout << "children of [" << i << "] : ";
            for (auto v : childs_of_V[i])
            {
                cout << v << ", ";
            }
            cout << endl;
        }

        // cout << "IDX: " << endl;
        REP(i, N + 1)
        {
            cout << "IDX for " << i << " = " << which_is_older_index[i] << endl;
        }

        cout << "pieces: " << endl;
        REP(i, N + 1)
        {
            cout << "piece[" << i << "] = " << piece[i] << endl;
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
            now_e = parent[now_e];
        }
        score += piece[now_e];
        cout << score << endl;
    }
}

/*
ミスったっぽい。
sample: case 2 について

    
           1
        2     6
      3  4
    7      5

木の情報取得はうまくいったようだ。

wrong:
8
26
31
26
58
8
23

true:
72
8
13
26
58
72
5
*/