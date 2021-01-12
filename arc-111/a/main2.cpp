#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
#include <cstring>
using namespace std;
bool debug = false;

// const bool debug = true;
const bool seg_debug = false;
// const bool debug = false;
const bool detail_debug = false;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define int long long

/*
    # やりたいこと
    保存したら make が走るようにしたい。
    myassert で赤文字で出したりしたい。
    複数の値の返却のほうが楽じゃない？structとか。
    vector の vector とか。

    python のテスト機能を活用したい。

    oj でやる。oj でやるとき、どういう流れでやるか考えておきたい。

    ✅ -Dマクロ変数でテストかどうか決める.
    ✅環境変数でデバッグON OFF したい。
*/
/* ---------------------------------------------------------------------------------- */
void show_vector(/*const ref in*/ const vector<int> &vec, const string &label)
{
    cout << "[" << label << "]: " << endl;
    for (auto v : vec)
    {
        cout << v << ",";
    }
    cout << endl;
}

void show_variable(const int val, const string &label)
{
    cout << "[" << label << "]: " << endl;
    cout << val << endl;
}

void eq_assert(const int val, const int answer, const string &label)
{
    if (val != answer)
    {

        cout << "Assertion failed: "
             << "(val = " << val << ", label = " << label << ", "
             << ", answer = " << answer << ") " << endl
             << flush;

        exit(1);
    }
}
void eq_show(const int val, const int answer)
{
    if (val != answer)
    {

        cout << "Assertion failed: "
             << "(val = " << val << ", answer = " << answer << ") " << endl
             << flush;
    }
}
// for test
void assert_vec(/*const ref in*/ const vector<int> &target, /*const ref in*/ const vector<int> &answer)
{
    cout << "target size: " << target.size() << ", answer size: " << answer.size() << endl
         << flush;
    if (debug)
    {
        show_vector(target, "target: ");
        show_vector(answer, "answer: ");
    }
    assert(target.size() == answer.size());
    for (int i = 0;
         i < target.size();
         ++i)
    {
        assert(target[i] == answer[i]);
    }
}
/* ---------------------------------------------------------------------------------- */

// 普通の循環少数の生成列を作成する。
// 疑問: 0.250 のようなケースに対しては、どうする？
// 1 / 3 = 0.3333 というケースでは、 shou = 3,  repeated  = [3] を作成。
// 1 / 4 = 0.250  というケースでは、 shou = 025 repeated  = [0] を作成する。
void generate_series(const int M,
                     /*ref out*/ vector<int> &shou,
                     /*ref out*/ vector<int> &repeated)
{
    set<int> already_seen_amari;
    int now_num = M;
    int amari_now = 1;
    int last_amari = -1;

    // local　変数にした。
    vector<int> what_is_shou_for_amari(M + 1);

    shou.resize(0);
    vector<int> amari_vector;
    repeated.resize(0);

    while (true)
    {
        // amari_now は M 以下の状態でここに来る（はず）
        if (already_seen_amari.find(amari_now) != already_seen_amari.end())
        {
            last_amari = amari_now;
            break;
        }

        already_seen_amari.insert(amari_now);
        amari_vector.push_back(amari_now);

        // ケタあげする。
        amari_now *= 10;

        // このループ 1回 で 10 を 1回 かける
        if (amari_now < now_num)
        {
            // よくミスる: ここで 10を かける必要はない。
            what_is_shou_for_amari[amari_now] = 0;
            shou.push_back(0);
            continue;
        }

        shou.push_back(amari_now / M);
        what_is_shou_for_amari[amari_now / 10] = amari_now / M;
        amari_now = amari_now % M;
    }

    // repeated の作成
    auto p = std::find(ALL(amari_vector), last_amari);
    if (amari_vector.end() != p)
    {
        for (auto v = p /* mid point*/; v < amari_vector.end(); v++)
        {
            repeated.push_back(what_is_shou_for_amari[*v]);
        }
    }
}

// repeated repeated_with_amari を M で割ったあまりを計算する。
int calc_amari_for_target_vec(const int M,
                              /*const ref in*/ const vector<int> &target_vec) // repeated とは限られず、先頭にあまりが付加した形になる。
{
    int i = 0;

    if (seg_debug)
    {
        cout << "in repeated amari cycle";
        show_vector(target_vec, "repeated with amari"); // 割り切れた時？
    }

    // 提出のときにREした原因 例: eq_assert(service(78, 13), 0, "service(78, 13)");
    // 0 とは限らない?
    if (target_vec.size() == 0)
    {
        return 0;
    }

    int target = target_vec[i++];

    while (i < target_vec.size())
    {
        target = target * 10 + target_vec[i++];
        if (target >= M)
        {
            int shou_one = target / M;
            int amari_one = target % M;
            target = amari_one;
        }
        else
        {
            // shou.push_back(0);
            // ❌ これ毎回間違える--!! _ は不要。
            // target = target * 10 + warareru[i++];
            continue;
        }
    }

    if (target >= M)
    {
        int shou_one = target / M;
        int amari_one = target % M;
        target = amari_one;
        // shou.push_back(shou_one);
    }

    // amari = target; // これって b 未満だよね？
    assert(target < M);
    return target;
}

// 便利関数
vector<int> num_to_vector(int n)
{
    vector<int> answer;
    while (n != 0)
    {
        answer.push_back(n % 10);
        n = n / 10;
    }
    reverse(ALL(answer));
    return answer;
}

// times の代わりに、repeated set に対するあまりの循環を計算する関数
// これ結構大変じゃない？
int generate_amari_series_for_repeated_set(const int M,
                                           const int initial_amari_for_shou,
                                           /*ref out*/ vector<int> &amari_series_for_repeated_set, // 名前が悪い気がする。 repeated_amari_repeated とか
                                           /*const ref in*/ const vector<int> &repeated)
{
    int times = 1;
    int amari = 0;
    set<int> seen_amari;

    vector<int> initial_amari_for_shou_vec = num_to_vector(initial_amari_for_shou);
    for (auto r : repeated)
    {
        initial_amari_for_shou_vec.push_back(r);
    }

    amari = calc_amari_for_target_vec(/*const int*/ M,
                                      /*const ref in*/ initial_amari_for_shou_vec);

    while (true)
    {
        if (seen_amari.find(amari) != seen_amari.end())
        {
            break;
        }
        seen_amari.insert(amari);
        amari_series_for_repeated_set.push_back(amari);

        vector<int> next_repeated = num_to_vector(amari);

        for (auto r : repeated)
            next_repeated.push_back(r);

        amari = calc_amari_for_target_vec(
            /*const int*/ M,
            /*const ref in*/ next_repeated);
    }
    /*
        最後のあまりが 0 のときは これはもうリピートしないんだけど、そのフラグを返したほうがよさそう。
    */
    if (debug)
    {
        show_variable(amari, "generation of series: last amari: ");
    }
    return amari;
}

int service(const int N, const int M)
{

    /*
        理想ケース

        1 / 88 = 0.01136 .. 363636363
        0.01136 の部分で、あまりは 80.
        80 スタートの あまりの一覧を知りたい。
        8036 % 88 = 28 となる。
        あまり循環は 28,20,12,4,84,76,68,60,52,44,36, となる。

        生成された循環小数に対する あまりの循環列
                      80  28 20 12  4 84 76 68 60 52 44 36   28 20 12  4 84 76 68 60 52 44 36   28 20 12  4
        1 / 88 = 0.01136  36 36 36 36 36 36 36 36 36 36 36   36 36 36 36 36 36 36 36 36 36 36   36 36 36 36 3 
                      88
            _____________________________________________________________________
                      80  36
                          88
            _____________________________________________________________________
                          28                         44 36
                                                        88
            _____________________________________________________________________
                                                        36  36
                                                            88
            _____________________________________________________________________
                                                            28 (loop detected!)

        
                      80  28 20 12  4 84 76 68 60 52 44 36   28 20 12  4 84 76 68 60 52 44 36   28 20 12  4
        1 / 88 = 0.01136  36 36 36 36 36 36 36 36 36 36 36   36 36 36 36 36 36 36 36 36 36 36   36 36 36 36 3 
        // こういう感じに、 N = 5 + 11*2*2 + 2*4 + 1 = 58 の場合, M で割ったあまりは
                 0.01136  36 36 36 36 3 
                                   88
            _____________________________________________________________________
                                    4 3
                                    8 8
            _____________________________________________________________________
                                    4 3 
                                
            となり、   あまりは 43 となる。

        // プログラムに落とす時の 計算過程
        N = 58 のとき、 N > shou.size() のため、
        N - shou.size()(=5) = 53 となる。
        53 / 11 = 44 + 9 / 11 = 4 ... 9 となる。
        9 / 2 = 4 .. 1 となる。 => 4番目のあまりは、 amari[4-1] = 4 となるので、 4 これに、repeated[0] == 3 を
        // このあまりの足し算の部分は、 repeated.begin(), repeated.begin() + amari_for_each_repeated(=1) ということになる。
        // この部分のrepeated を最後に継ぎ足す。
        
        if ( N > shou.size() ) {
            N -= shou.size();
        }
        int repeated_circular_size = 11; // 計算して求める。
        int _not_used_repeated_set_商 = N / repeated_circular_size; // => 4 // これは使わない
        int _repeated_set_count_amari = N % repeated_circular_size; // => 9
        int last_repeated_set_idx   = _repeated_set_count_amari / repeated.size(); // 9 / 2 == 4
        int afte_repeated_set_ofset = _repeated_set_count_amari % repeated.size(); // 9 % 2 == 1

        // ❌ この方針で O(1) で考えようと思ったが、結局 最後の部分は全部使うベクターで、
        // O(M(repeated_size) * M(repeated_set のあまり循環の長さ)) でいけそうだったので、そちらで AC した。
        // どちらにせよ、結局割り切れた場合分けの周りで間違えていそうだった。
        int last_repeated_set_amari = repeated_amari[last_repeated_set_idx-1];
        if (last_repeated_set_idx == 0) {
            // 36 のところで終わっているとき は、最後のあまりを36にしないといけなさそう。
            last_repeated_set_amari = 36;            
        }

        // これって本当に1charコピーできるのかな
        vector<int> repeated_used ( repeated.begin(), repeated.begin() + afte_repeated_set_ofset);

        // まだ作ってない関数
        vector<int> concated_vec_for_amari = concat(last_repeated_set_amari, repeated_used);
        int answer = amarikeisan(M, concated_vec_for_amari);

        こういう感じで計算ができるはず。
        
        // もし、 repeated で割り切れたとすると、一番最後の36になる？   => ✅ OK
                      80  28 20 12  4 84 76 68 60 52 44 36
        1 / 88 = 0.01136  36 36 36 36 36 36 36 36 36 36 36


        >>> "".join(a.strip().split(" "))
        '113636363636363636363636363636363636363636363636363636363'
        >>> b ="".join(a.strip().split(" "))
        >>> int(b)
        113636363636363636363636363636363636363636363636363636363
        >>> int(b) % 88
        43

    */

    if (debug)
    {
        cout << "--------- N: " << N << "------ M: " << M << "---------" << endl;
    }
    int _N = N;
    vector<int> shou, repeated;
    vector<int> amari_vector;
    generate_series(/*const int*/ M,
                    /*ref out*/ shou,
                    /*ref out*/ repeated);

    vector<int> amari_series_for_repeated_set;

    // shou に対する イニシャルあまり問題
    if (debug)
    {
        show_vector(repeated, "[service] repeated: ");
        show_vector(shou, "[service] shou: ");
        show_variable(shou.size(), "[service] shou size: ");
        /*
            [service shou show: ]: 
            0,1,1,3,6,
        */
    }

    int initial_amari_for_shou = calc_amari_for_target_vec(M,
                                                           shou);

    // ❌ ~~ shou の末尾が 0 で repeated_amari_loop == 0 のケースは、 shou の末尾の0 を削除すべき? ~~ <- そんなことない。
    int last_generation_amari = generate_amari_series_for_repeated_set(/*const int*/ M,
                                                                       /*const int*/ initial_amari_for_shou,
                                                                       /*out*/ amari_series_for_repeated_set,
                                                                       /*const ref in*/ repeated);

    if (N > shou.size())
    {
        _N -= shou.size();

        int repeated_circular_size = amari_series_for_repeated_set.size();
        int _repeated_circular_amari = _N % (repeated_circular_size * repeated.size());

        if (_N >= repeated_circular_size && last_generation_amari == 0)
        {
            if (debug)
            {
                cout << "------- ここで、last amari == 0 のパターンなので、あまり == 0 となる。" << endl;
            }
            return 0;
        }

        // int last_repeated_set_amari = 0;
        // ⚡️ ここの処理が怪しい
        // 前面書き換え
        // ❌ for 割り切れたとき(4とか, 2になってしまう)
        // repeated == 0 のケース

        if (debug)
        {
            show_variable(_repeated_circular_amari, "_repeated_circular_amari");
            show_variable(shou.size(), "shou size");
            show_variable(repeated_circular_size, "repeated_circular_size");
            show_vector(amari_series_for_repeated_set, "amari_series_for_repeated_set");
        }
        vector<int> target(_repeated_circular_amari + shou.size());
        int repeated_count = _repeated_circular_amari / repeated.size();
        int left = _repeated_circular_amari % repeated.size();
        for (auto s : shou)
            target.push_back(s);
        for (int i = 0;
             i < repeated_count;
             ++i)
        {
            for (auto r : repeated)
                target.push_back(r);
        }
        for (int i = 0; i < left; ++i)
        {
            target.push_back(repeated[i]);
        }

        if (debug)
        {
            show_vector(target, "target vector for wari");
        }

        return calc_amari_for_target_vec(M, target);
    }
    else // Nが小さい場合:  N <= shou.size()
    {
        // shou の一部分を取得する。 ( N文字のみ )
        vector<int> subshou(shou.begin(), shou.begin() + N); // 0.25 , N == 1 だと、 2 になる。
        int ans = calc_amari_for_target_vec(M, subshou);
        return ans;
    }

    assert("ここに来ることはない" && false);
}

#ifndef TEST
signed main(signed argc, char *argv[])
#else
signed main2(signed argc, char *argv[])
#endif
{
    const char *DEBUG_p = std::getenv("DEBUG");
    debug = DEBUG_p != NULL && strnlen(DEBUG_p, 1) > 0;

    long long N;
    int M;
    cin >> N >> M;

    cout << service(N, M) << endl;
}
