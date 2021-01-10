#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <cassert>
using namespace std;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
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

void calc_vec(int M)
{
    set<int> already_amari;
    int now_num = M;
    int amari_now = 1;
    vector<int> what_is_shou_for_amari(M + 1);
    int last_amari = -1;

    // ループする 商 を見つける
    vector<int> shou;         // 割り算の商
    vector<int> amari_vector; // 割り算の商

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
            cout << "amari_now: " << amari_now << endl;
        }
    }

    cout << "result string for 1 / " << M << " = ";
    int first_num = shou[0] / 10;
    if (first_num == 0)
    {
        // cout << "0.";
        cout << ((float)shou[0] / 10);

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

void assert_10_M(int M)
{
    calc_vec(M);
}

int main(int argc, char *argv[])
{
    // assert_10_6();
    // cout << 13 << endl;
    // assert_10_M(13);
    // cout << endl;

    // cout << 21 << endl;
    // assert_10_M(21);
    // cout << endl;

    cout << "last out";
    vector<int> h(9999);
    h.push_back(1);
    cout << h[10000];

    // セグフォするんだけど、どうすればすぐにわかる？
    // cout << 9997 << endl;
    // assert_10_M(9997);
    // cout << endl;

    REP(i, 100)
    {
        cout << "now loop i: " << i + 1 << endl;
        assert_10_M(i + 1);
        cout << "------------" << endl;
    }
}