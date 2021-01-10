#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <cassert>
using namespace std;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
const bool debug = false;
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
/*
    1.666 だから、 どこから始まるか, をメモする必要がある。
*/
/*
    実装できた。あとは引数に結果を渡す。
*/
// repeated_string は商 の羅列なので、対応するamari がほしい
void calc_vec(int M,
              /*out*/ vector<int> &what_is_shou_for_amari,
              /*out*/ vector<int> &shou,
              /*out*/ vector<int> &amari_vector,
              /*out*/ vector<int> &repeated)
{
    set<int> already_amari;
    int now_num = M;
    int amari_now = 1;
    int last_amari = -1;

    what_is_shou_for_amari.resize(M + 1);
    shou.resize(0);
    amari_vector.resize(0);
    repeated.resize(0);

    // ループする 商 を見つける
    ; // 割り算の商
    ; // 割り算のあまりの配列

    while (true)
    {
        // amari_now は M 以下の状態でここに来る（はず）
        if (already_amari.find(amari_now) != already_amari.end())
        {
            cout << "again amari is : " << amari_now << ", and 商 is " << what_is_shou_for_amari[amari_now] << endl;
            last_amari = amari_now;
            break;
        }

        already_amari.insert(amari_now);
        amari_vector.push_back(amari_now);

        // ケタあげする。
        amari_now *= 10;

        // このループ 1回 で 10 を 1回 かける
        if (amari_now < now_num)
        {
            what_is_shou_for_amari[amari_now] = 0;
            shou.push_back(0);
            // ここでかける必要はない。
            continue;
        }

        shou.push_back(amari_now / M);
        what_is_shou_for_amari[amari_now / 10] = amari_now / M;
        amari_now = amari_now % M;

        if (debug)
        {
            // cout << "amari_now: " << amari_now << endl;
        }
    }

    cout << "result string for 1 / " << M << " = ";
    int first_num = shou[0] / 10;
    float first_num_float = (float)shou[0] / 10;
    if (first_num == 0)
    {
        // cout << "0.";
        if (first_num_float < 0.1)
        {
            cout << "0.0";
        }
        else
        {
            cout << ((float)shou[0] / 10);
        }

        // cout << first_num;
    }
    else
    {
        // このケースは M == 1 のときのみ
        cout << first_num << endl;
        return;
    }

    vector<int> new_vec_sub_under_1(shou.begin() + 1, shou.end());
    for (auto s : new_vec_sub_under_1)
    {
        cout << s;
    }
    cout << endl;
    cout << "repeat_string : ";
    // auto p = .find(last_amari);
    auto p = std::find(ALL(amari_vector), last_amari);
    if (amari_vector.end() != p)
    {
        for (auto v = p /* mid point*/; v < amari_vector.end(); v++)
        {
            int sho_repeated_i = what_is_shou_for_amari[*v];
            repeated.push_back(sho_repeated_i);
            cout << sho_repeated_i;
        }
        cout << endl;
    }
    else
    {
        cout << "cannot find..";
    }

    if (debug)
    {
        cout << "amari for what is shou for .." << endl;
        for (auto w : what_is_shou_for_amari)
        {
            cout << w << ",";
        }
        cout << endl;

        cout << "shou: " << endl;
        for (auto s : shou)
        {
            cout << s << ",";
        }
        cout << endl;

        cout << "amari:" << endl;
        for (auto a : amari_vector)
        {
            cout << a << ",";
        }
        cout << endl;
    }
}

void assert_10_M(int M, const vector<int> &answer)
{
    vector<int> what_is_shou_for_amari;
    vector<int> shou;
    vector<int> amari_vector;
    vector<int> repeated;

    calc_vec(M,
             /*ref out*/ what_is_shou_for_amari,
             /*ref out*/ shou,
             /*ref out*/ amari_vector,
             /*ref out*/ repeated);

    if (debug)
    {
        cout << "repeated: vec" << endl;
        for (auto v : repeated)
        {
            cout << v << ",";
        }
        cout << endl;
    }
    assert(repeated.size() == answer.size());
    REP(i, repeated.size())
    {
        assert(repeated[i] == answer[i]);
    }
    cout << "------------------" << endl;
}

int main(int argc, char *argv[])
{
    vector<int> vec13{0, 7, 6, 9, 2, 3};
    assert_10_M(13, /*ref*/ vec13);

    vector<int> vec19{0, 5, 2, 6, 3, 1, 5, 7, 8, 9, 4, 7, 3, 6, 8, 4, 2, 1};
    assert_10_M(19, /*ref*/ vec19);

    vector<int> vec23{0, 4, 3, 4, 7, 8, 2, 6, 0, 8, 6, 9, 5, 6, 5, 2, 1, 7, 3, 9, 1, 3};
    assert_10_M(23, /*ref*/ vec23);
}