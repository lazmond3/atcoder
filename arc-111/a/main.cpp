#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;
// const bool debug = false;
const bool debug = true;
const bool seg_debug = false;
// const bool debug = false;
const bool detail_debug = false;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define int long long
// #define massert(e, a)                                                                                \
//     do                                                                                               \
//     {                                                                                                \
//         eq_show(e, a);                                                                               \
//         (__builtin_expect(!(e == a), 0) ? __assert_rtn(__func__, __FILE__, __LINE__, #e) : (void)0); \
//     } while (0)

/*
    myassert で赤文字で出したりしたい。
*/
// for debug
/*
    ❌ 引っかかっているところ
    1 / 4 などの、循環小数にならずに終わってしまう場合。

    73, 13 などの、最後が
*/
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
// ----------

// STEP 1: ✅
void shou_and_repeated(const int M,
                       /*ref out*/ vector<int> &shou,
                       /*ref out*/ vector<int> &amari_vector,
                       /*ref out*/ vector<int> &what_is_shou_for_amari,
                       /*ref out*/ vector<int> &repeated)
{
    set<int> already_seen_amari;
    int now_num = M;
    int amari_now = 1;
    int last_amari = -1;

    what_is_shou_for_amari.resize(M + 1);
    shou.resize(0);
    amari_vector.resize(0);
    repeated.resize(0);

    while (true)
    {
        // amari_now は M 以下の状態でここに来る（はず）
        if (already_seen_amari.find(amari_now) != already_seen_amari.end())
        {
            if (debug)
            {
                cout << "again amari is : " << amari_now << ", and 商 is " << what_is_shou_for_amari[amari_now] << endl;
            }
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
    // what_is_shou_for_amari, shou の作成。
    // last_amari が 再度見たあまりとして _ に出てくる。

    // repeated の作成
    auto p = std::find(ALL(amari_vector), last_amari);
    if (amari_vector.end() != p)
    {
        for (auto v = p /* mid point*/; v < amari_vector.end(); v++)
        {
            repeated.push_back(what_is_shou_for_amari[*v]);
        }
    }

    // こんなことをする必要はないのでは
    // if (debug)
    // {
    //     show_vector(shou, "shou reset したい");
    //     show_vector(repeated, "repeated amari");
    // }
    // if (shou[shou.size() - 1] == 0 && repeated.size() == 1 and repeated[0] == 0)
    // {

    //     shou.pop_back();
    //     if (debug)
    //     {
    //         show_vector(shou, "shou reset した");
    //     }
    // }
}

// ✅ checked
void test_shou_and_repeated()
{
    // 88
    vector<int> shou_88;
    vector<int> amari_88;
    vector<int> what_amari_88;
    vector<int> repeated_88;
    cout << "--- 88 --- " << endl;
    shou_and_repeated(88,
                      /*ref out*/ shou_88,
                      /*ref out*/ amari_88,
                      /*ref out*/ what_amari_88,
                      /*ref out*/ repeated_88

    );
    show_vector(shou_88, "shou88");
    show_vector(amari_88, "amari88");
    show_vector(what_amari_88, "what amari88");
    show_vector(repeated_88, "repeated_88");
    assert_vec(shou_88, vector<int>{
                            0,
                            1,
                            1,
                            3,
                            6,
                        });
    assert_vec(repeated_88, vector<int>{3, 6});

    // 17
    vector<int> shou_17;
    vector<int> amari_17;
    vector<int> what_amari_17;
    vector<int> repeated_17;
    cout << "--- 17 --- " << endl;
    shou_and_repeated(17,
                      /*ref out*/ shou_17,
                      /*ref out*/ amari_17,
                      /*ref out*/ what_amari_17,
                      /*ref out*/ repeated_17

    );
    show_vector(shou_17, "shou17");
    show_vector(amari_17, "amari17");
    show_vector(what_amari_17, "what amari17");
    show_vector(repeated_17, "repeated_17");
    assert_vec(shou_17, vector<int>{0, 5, 8, 8, 2, 3, 5, 2, 9, 4, 1, 1, 7, 6, 4, 7});
    assert_vec(repeated_17, vector<int>{0, 5, 8, 8, 2, 3, 5, 2, 9, 4, 1, 1, 7, 6, 4, 7});

    // 23
    vector<int> shou_23;
    vector<int> amari_23;
    vector<int> what_amari_23;
    vector<int> repeated_23;
    cout << "--- 23 --- " << endl;
    shou_and_repeated(23,
                      /*ref out*/ shou_23,
                      /*ref out*/ amari_23,
                      /*ref out*/ what_amari_23,
                      /*ref out*/ repeated_23

    );
    show_vector(shou_23, "shou23");
    show_vector(amari_23, "amari23");
    show_vector(what_amari_23, "what amari23");
    show_vector(repeated_23, "repeated_23");
    assert_vec(shou_23, vector<int>{0, 4, 3, 4, 7, 8, 2, 6, 0, 8, 6, 9, 5, 6, 5, 2, 1, 7, 3, 9, 1, 3});
    assert_vec(repeated_23, vector<int>{
                                0,
                                4,
                                3,
                                4,
                                7,
                                8,
                                2,
                                6,
                                0,
                                8,
                                6,
                                9,
                                5,
                                6,
                                5,
                                2,
                                1,
                                7,
                                3,
                                9,
                                1,
                                3,
                            });
}

// repeated を割るだけ。
// return amari
// ✅
int repeated_and_amari_cycle(const int M,
                             /*const ref in*/ const vector<int> &repeated_with_amari) // repeated とは限られず、先頭にあまりが付加した形になる。
{
    int i = 0;

    if (seg_debug)
    {
        cout << "in repeated amari cycle";
        show_vector(repeated_with_amari, "repeated with amari"); // 割り切れた時？
    }

    // 提出のときにREした原因 例: eq_assert(service(78, 13), 0, "service(78, 13)");
    // 0 とは限らないので WA.
    if (repeated_with_amari.size() == 0)
    {
        // return
        // return 0;
        //
        cout << "cannot be 0 in repeaed" << endl;
        assert(false);
    }

    int target = repeated_with_amari[i++];

    while (i < repeated_with_amari.size())
    {
        target = target * 10 + repeated_with_amari[i++];
        if (target >= M)
        {
            int shou_one = target / M;
            int amari_one = target % M;
            target = amari_one;
            // shou.push_back(shou_one);
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
// ✅
void test_repeated_and_amari_cycle()
{
    // 88
    assert(repeated_and_amari_cycle(88, vector<int>{3, 6}) == 36);
    assert(repeated_and_amari_cycle(88, vector<int>{3, 6, 3, 6}) == 28);
    assert(repeated_and_amari_cycle(88, vector<int>{2, 8, 3, 6}) == 20);
    assert(repeated_and_amari_cycle(88, vector<int>{2, 0, 3, 6}) == 12);
    assert(repeated_and_amari_cycle(88, vector<int>{4, 3, 6}) == 84);
    assert(repeated_and_amari_cycle(88, num_to_vector(8436)) == 76);
    assert(repeated_and_amari_cycle(88, num_to_vector(7636)) == 68);
    assert(repeated_and_amari_cycle(88, num_to_vector(6836)) == 60);
}
// repeated を何回連結させるとあまりがゼロになるか。
// return times
// あまりがゼロにならないこともあるのか！！
// (M=88に対して、 repeated={3,6} だと、同じ(偶数条件) をループしてしまい、ゼロにはならない。)
/*
    amari:  4, times: 741889
    amari: 84, times: 741890
    amari: 76, times: 741891
    amari: 68, times: 741892
    amari: 60, times: 741893
    amari: 52, times: 741894
    amari: 44, times: 741895
    amari: 36, times: 741896
    amari: 28, times: 741897
    amari: 20, times: 741898
    amari: 12, times: 741899
    amari:  4, times: 741900
    amari: 84, times: 741901
*/
//
// テスト ✅
// times の代わりに、repeated set に対するあまりの循環を計算する関数
void repeated_mod_times(const int M,
                        const int start_amari,
                        /*ref out*/ vector<int> &amari_vector,
                        /*const ref in*/ const vector<int> &repeated)
{
    int times = 1;
    int amari = 0;
    set<int> seen_amari;

    vector<int> start_vec = num_to_vector(start_amari);
    for (auto r : repeated)
    {
        start_vec.push_back(r);
    }

    if (debug)
    {
        cout << "[mod] repated mod: "
             << "start amari: " << start_amari << endl;
        show_vector(start_vec, "start vec"); // 4 の場合、これが1,0 になる。そのため、最初のamari =
    }
    amari = repeated_and_amari_cycle(/*const int*/ M,
                                     /*const ref in*/ start_vec);

    if (debug)
    {
        // show_vector(start_vec, "[repeated mod times] start_vec:");
        // cout << "amari: " << amari << endl;
        show_variable(amari, "[repeated mod times] amari");
    }
    vector<int> not_used_amari_vector;
    // これを削除した。
    // amari_vector.push_back(amari);

    while (true)
    {
        if (seen_amari.find(amari) != seen_amari.end())
        {
            break;
        }
        seen_amari.insert(amari);
        amari_vector.push_back(amari);

        vector<int> next_repeated = num_to_vector(amari);

        for (auto r : repeated)
            next_repeated.push_back(r);

        amari = repeated_and_amari_cycle(
            /*const int*/ M,
            /*const ref in*/ next_repeated);
    }
}

// テスト ✅
// セグフォする。　=>  ✅
void test_repeated_mod_times()
{
    // 4
    vector<int> amari_vector_4;
    repeated_mod_times(4, /*start_amari*/ 1, /*ref out*/ amari_vector_4, num_to_vector(0));
    assert_vec(
        amari_vector_4,
        vector<int>{1});
    // 88
    vector<int> amari_vector_88;
    repeated_mod_times(88, /*start_amari*/ 0, /*ref out*/ amari_vector_88, num_to_vector(36));
    assert_vec(
        amari_vector_88,
        vector<int>{36, 28, 20, 12, 4, 84, 76, 68, 60, 52, 44});
    // 23
    vector<int> amari_vector_23;
    repeated_mod_times(23, /*start_amari*/ 0, /*ref out*/ amari_vector_23, num_to_vector(36));
    assert_vec(
        amari_vector_23,
        vector<int>{13, 2, 6, 15, 18, 19, 4, 22, 5, 7, 0});
    // 17
    vector<int> amari_vector_17;
    repeated_mod_times(17, /*start_amari*/ 0, /*ref out*/ amari_vector_17, num_to_vector(36));
    assert_vec(
        amari_vector_17,
        vector<int>{2, 15, 6, 7, 5, 9, 1, 0});
}

int service(const int N, const int M)
{
    if (debug)
    {
        cout << "--------- N: " << N << "------ M: " << M << "---------" << endl;
    }
    int _N = N;
    vector<int> shou, repeated, what_is_shou_for_amari;
    vector<int> amari_vector;
    shou_and_repeated(/*const int*/ M,
                      /*ref out*/ shou,
                      /*ref out*/ amari_vector,
                      /*ref out*/ what_is_shou_for_amari,
                      /*ref out*/ repeated);

    // repeated　をわるあまりの巡回
    // repeated amari loop == 0 というのは、なぜ？
    //   ->
    vector<int> repeated_amari_loop;
    vector<int> &amari_vector_repeated = repeated_amari_loop;

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

    int initial_amari = repeated_and_amari_cycle(M,
                                                 shou);

    if (debug)
    {
        cout << "   -- before call mod times -- " << endl;
        cout << "[service] initial amari: " << initial_amari << endl;
        show_vector(repeated_amari_loop, "repeated_amari_loop"); // 4 のときなど、これが .size() == 0 になる。
        show_vector(repeated, "repeated");
    }

    // shou の末尾が 0 で repeated_amari_loop == 0 のケースは、 shou の末尾の0 を削除すべき?
    repeated_mod_times(/*const int*/ M,
                       /*const int*/ initial_amari,
                       /*out*/ repeated_amari_loop,
                       /*const ref in*/ repeated);

    if (debug)
    {
        cout << "   -- after call mod times --- " << endl;
        cout << "[service] repeated amari loop: size: " << repeated_amari_loop.size() << endl;

        // show_vector(repeated_amari_loop, );
    }

    // N は桁数を意味する。
    if (detail_debug)
    {
        show_vector(repeated_amari_loop, "[service] repeated amari loop");
        /*
            28,20,12,4,84,76,68,60,52,44,36,
        */
    }

    if (N > shou.size() && repeated.size() == 1 && repeated[0] == 0)
    {
    }

    if (N > shou.size())
    {

        _N -= shou.size();

        // cout << "here off idx amari suze" << endl;
        int repeated_circular_size = repeated_amari_loop.size();

        // cout << "here off idx amari" << endl;
        // ここの部分が間違っていた。
        int _repeated_circular_amari = _N % (repeated_circular_size * repeated.size());

        if (seg_debug)
            cout << "here off idx" << endl;
        int last_repeated_set_idx = _repeated_circular_amari / repeated.size();
        if (seg_debug)

            cout << "here off: _repeated_circular_amari: " << _repeated_circular_amari << endl;
        int last_repeated_set_offset = _repeated_circular_amari % repeated.size();
        if (seg_debug)
        {

            cout << "here" << endl;

            cout << "here: last_repeated_set_idx: " << last_repeated_set_idx << endl;
        }

        int last_repeated_set_amari = 0;
        if (last_repeated_set_idx == 0)
        {
            if (seg_debug)
            {
                cout << "before: here: last_repeated_set_amari" << endl
                     << flush;
            }

            // if (debug)
            // {
            //     show_vector(amari_vector_repeated, "amari vector is zero [before segfo]");
            //     cout << flush;
            // }
            last_repeated_set_amari = amari_vector_repeated[amari_vector_repeated.size() - 1];
            if (seg_debug)

                cout << "here: last_repeated_set_amari" << endl;
        }
        else
        {
            // cout << "before here: last_repeated_set_amari" << endl;
            last_repeated_set_amari = amari_vector_repeated[last_repeated_set_idx - 1];
            // cout << "here: last_repeated_set_amari" << endl;
        }
        // concat が必要
        auto concated_vec_for_last_amari = num_to_vector(last_repeated_set_amari);
        // このoffset ってなんだっけ
        vector<int> repeated_last_used(repeated.begin(), repeated.begin() + last_repeated_set_offset);
        for (auto rlu : repeated_last_used)
        {
            concated_vec_for_last_amari.push_back(rlu);
        }
        if (debug)
        {
            cout << "-----------------" << endl;
            show_variable(repeated_circular_size, "repeated_circular_size");
            show_variable(_repeated_circular_amari, "_repeated_circular_amari");
            show_variable(last_repeated_set_idx, "last_repeated_set_idx");
            show_variable(last_repeated_set_offset, "last_repeated_set_offset");
            show_variable(last_repeated_set_amari, "last_repeated_set_amari");
            show_vector(concated_vec_for_last_amari, "concated vec for last amari");
        }
        if (seg_debug)
        {
            cout << "before ans " << endl;
        }
        int ans = repeated_and_amari_cycle(M, concated_vec_for_last_amari);
        if (seg_debug)
        {
            cout << "after  ans " << endl;
        }
        return ans;
    }
    else // Nが小さい場合:  N <= shou.size()
    {
        // cout << "NOT IMPLEMENTED" << endl;
        // assert(false);
        // exit(1);
        vector<int> subshou(shou.begin(), shou.begin() + N); // 0.25 , N == 1 だと、 2 になる。
        int ans = repeated_and_amari_cycle(M, subshou);
        if (debug)
        {
            show_vector(shou, "shou in N <= shou.size()");
            show_vector(subshou, "subshou in N <= shou.size()");
            show_variable(ans, "answer in N <= shou.size()");
        }
        return ans;
    }

    /*
        理想ケース
                        2      4
        1 / 13 = 0.076923 076923 076923
                    13
            ____________________________
                    119
                     13
            ____________________________
                      22
                      13
            ____________________________
                       93
                       13
            ____________________________
                        2 



        1 / 88 = 0.01136 .. 363636363
        0.01136 の部分で、あまりは 80.
        80 スタートの あまりの一覧を知りたい。
        8036 % 88 = 28 となる。
        あまり循環は 28,20,12,4,84,76,68,60,52,44,36, となる。

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

        // 計算過程
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

    // 1. shou 桁数よりも多いか？ -> 引き算しよう。

    if (N > shou.size())
    {
    }

    // 2. repeated 桁数 よりも多いか？ -> 何個入っているか計算しよう。

    // 3. repeated 桁数 が 何個か入っているか？

    // - 例: 88
    // 1. shou = 01136 (>>> 1 / 88 = 0.011363636363636364) である。
    //    N =  5 で shou 桁数。
    // 2. repeated 桁数は 36 で 2ケタ
    // 3. N = 100 とすると、 N - 5 = 95, 95 / 2 = 47 あまり 1となる。
    //    このとき、
    // repeated_amari_loop = {36, 28, 20, 12, 4, 84, 76, 68, 60, 52, 44}
    // となる ( 回数 = 11 で1周する。 )
    // 47 / 11 = 4 あまり 3なので、 repeated 周回分のあまりは20,
    // repeated 自体があまり 1 なので、あまり3.
    /*
        
    */

    // -------- 以前の考察

    // shou を M で割ったあまりはいくつになる？
    // 結局何桁ある？
    /*
        1 / 17 = 0.0588235294117647]
        shou = 0,5,8,8,2,3,5,2,9,4,1,1,7,6,4,7
        なので、N = 16 で最初のshouを使える。
    */
    /*
        shou を M で割ったあまり
        => 1 / 88 = 0.01136 + 36 となる。
        => あまり 80 
        (消費するNは 5)
    */
    return 1;
}

// ✅
void test_service()
{
    assert(service(58, 88) == 43);
    assert(service(57, 88) == 4);
    assert(service(1, 2) == 1);
    assert(service(2, 7) == 0);
    assert(service(5, 88) == 80);
    assert(service(6, 88) == 11);
    assert(service(10, 88) == 27);
    assert(service(30, 88) == 19);
    assert(service(31, 88) == 20);
    assert(service(32, 88) == 27);
    assert(service(33, 88) == 12);
    assert(service(34, 88) == 35);
    assert(service(35, 88) == 4);
}

void test_service2()
{
    assert(service(5, 13) == 9);
    assert(service(6, 13) == 2);
    assert(service(7, 13) == 7);
    assert(service(8, 13) == 12);
    assert(service(9, 13) == 9);
    assert(service(10, 13) == 8);
    /*[[service] repeated: ]: 
        0,7,6,9,2,3,
    s*/
    // cout << "1000000000000000000" << endl;
    // int a = 1000000000000000000; // long はちゃんとこの量を取れている。
    // cout << a << endl;
    // cout << service(1000000000000000000, 9997) << endl;
    // 9629 が出てしまった。..
    // eq_assert(service(10000, 9997), 9767);
    // eq_assert(service(10001, 9997), 7697);
    // eq_assert(service(10002, 9997), 6991);
    // eq_assert(service(10102, 9997), 56);
    // eq_assert(service(10152, 9997), 8928);
    // eq_assert(service(10202, 9997), 6475);
    // eq_assert(service(10502, 9997), 6176);
    eq_assert(service(10001, 9997), 7697, "service(10001, 9997)");
    eq_assert(service(10000, 9997), 9767, "service(10000, 9997)");
    eq_assert(service(10002, 9997), 6991, "service(10002, 9997)");
    eq_assert(service(10102, 9997), 56, "service(10102, 9997)");
    eq_assert(service(10152, 9997), 8928, "service(10152, 9997)");
    eq_assert(service(10172, 9997), 8028, "service(10172, 9997)");
    eq_assert(service(10200, 9997), 5663, "service(10200, 9997)");
    eq_assert(service(10202, 9997), 6475, "service(10202, 9997)");
    eq_assert(service(10502, 9997), 6176, "service(10502, 9997)");

    // eq_assert(service(100000, 9997), 3428); //
    // eq_assert(service(1000000, 9997), 1644);
    // eq_assert(service(10000000, 9997), 4580);
    // assert(service(1000000000000000000, 9997) == 9015);
}
void test_service3()
{
    eq_assert(service(224, 88), 3, "service(224, 88)");
    /*
        224 ケタなのだが、
        224 - 5 = 219
        219 % (2 * 11) = 21
    */
}
void test_service4()
{
    // expected 0 が落ちてしまう。
    eq_assert(service(78, 13), 0, "service(78, 13)");
    /*
        224 ケタなのだが、
        224 - 5 = 219
        219 % (2 * 11) = 21
    */
}
void test_service5()
{
    eq_assert(service(3, 4), 2, "service(3, 4)");     // 250 %4 = 2
    eq_assert(service(2, 4), 1, "service(3, 4)");     // 250 %4 = 2
    eq_assert(service(1, 4), 2, "service(1, 4)");     // 0.2 => 2 % 4
    eq_assert(service(78, 13), 0, "service(78, 13)"); // 0.2 => 2 % 4
    /*  
        多分 n が小さい領域で失敗していて、
        shou の計算とかをすべきではない。
        0.2
    */
    /*
        0.25
          250
           6 
    */
}
signed main(signed argc, char *argv[])
{
    // test_shou_and_repeated();
    // test_repeated_and_amari_cycle();
    // test_repeated_mod_times();

    // service(10, 88);
    // test_service();
    // test_service2();
    // test_service3();
    // test_service4();

    // test_repeated_mod_times();

    test_service5();
    return 0;

    long long N;
    int M;
    cin >> N >> M;

    cout << service(N, M) << endl;
}
