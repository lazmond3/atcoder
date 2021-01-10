#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;
const bool debug = true;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define int long long

// for debug
void show_vector(/*const ref in*/ const vector<int> &vec, const string &label)
{
    cout << "[" << label << "]: " << endl;
    for (auto v : vec)
    {
        cout << v << ",";
    }
    cout << endl;
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
void repeated_mod_times(const int M,
                        /*ref out*/ vector<int> &amari_vector,
                        /*const ref in*/ const vector<int> &repeated)
{
    int times = 1;
    int amari = 0;
    set<int> seen_amari;

    amari = repeated_and_amari_cycle(/*const int*/ M,
                                     /*const ref in*/ repeated);

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
void test_repeated_mod_times()
{
    // 88
    vector<int> amari_vector_88;
    repeated_mod_times(88, /*ref out*/ amari_vector_88, num_to_vector(36));
    assert_vec(
        amari_vector_88,
        vector<int>{36, 28, 20, 12, 4, 84, 76, 68, 60, 52, 44});
    // 23
    vector<int> amari_vector_23;
    repeated_mod_times(23, /*ref out*/ amari_vector_23, num_to_vector(36));
    assert_vec(
        amari_vector_23,
        vector<int>{13, 2, 6, 15, 18, 19, 4, 22, 5, 7, 0});
    // 17
    vector<int> amari_vector_17;
    repeated_mod_times(17, /*ref out*/ amari_vector_17, num_to_vector(36));
    assert_vec(
        amari_vector_17,
        vector<int>{2, 15, 6, 7, 5, 9, 1, 0});
}

int service(const int N, const int M)
{
    vector<int> shou, repeated, what_is_shou_for_amari;
    vector<int> amari_vector;
    shou_and_repeated(/*const int*/ M,
                      /*ref out*/ shou,
                      /*ref out*/ amari_vector,
                      /*ref out*/ what_is_shou_for_amari,
                      /*ref out*/ repeated);

    vector<int> amari_vector_repeated;
    repeated_and_amari_cycle(
        /*const int*/ M,
        /*const ref in*/ repeated);

    // repeated　をわるあまりの巡回
    vector<int> repeated_amari_loop;

    repeated_mod_times(/*const int*/ M,
                       /*out*/ repeated_amari_loop,
                       /*const ref in*/ repeated);

    // N は桁数を意味する。

    // 1. shou 桁数よりも多いか？ -> 引き算しよう。

    // 2. repeated 桁数 よりも多いか？ -> 何個入っているか計算しよう。

    // 3. repeated 桁数 が 何個か入っているか？

    // - 例: 88
    // 1. shou =

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

signed main(signed argc, char *argv[])
{
    test_shou_and_repeated();
    test_repeated_and_amari_cycle();
    test_repeated_mod_times();

    // long long N;
    // int M;
    // cin >> N >> M;

    // service(N, M);
}
