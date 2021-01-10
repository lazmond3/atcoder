#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <cassert>
using namespace std;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
const bool debug = true;
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

// step 2 では、 実際に10^N / M がどんな形になるかを考える。
void assert_10_M(int N, int M, const vector<int> &answer)
{
    vector<int> what_is_shou_for_amari;
    vector<int> shou;
    vector<int> amari_vector;
    vector<int> repeated;

    // 0 ++ shou が最初の リピート数で、
    /*
        1/17 = [0.0588235294117647: [0]++shou ]  repeat部分:[0588235294117647] となるんだけど、
        [0] ++ shou = 00588235294117647 | 
        10^N で N==0がデフォルトスタートだから、
        N =  0 ->                0
        N =  1 ->                0
        N =  2 ->                5   
        N =  3 ->               58
        N =  4 ->              588
        N =  5 ->             5882
        N =  6 ->            58823 
          ...
        N = 16 -> 0588235294117647

        という形式になる。
        N = 16 未満 
        or N = 16 ( = shou.size() ) + (16*n) + <アマリ> というパターンマッチを使う
    */
    /*
        STEP2 として、リピート部分のあまりの変化を再度行う必要がある。
    */
    calc_vec(M,
             /*ref out*/ what_is_shou_for_amari,
             /*ref out*/ shou,
             /*ref out*/ amari_vector,
             /*ref out*/ repeated);

    cout << "------------------" << endl;
}

// これ calc と何が違うの
void long_div_me(/*ref in*/ const vector<int> &warareru,
                 /*in*/ int b,
                 /*ref out*/ vector<int> &shou,
                 /*ref out*/ int &amari)
{
    shou.resize(0);
    // amari.resize(0);

    int i = 0;
    int target = warareru[i++];
    while (i < warareru.size())
    {
        target = target * 10 + warareru[i++];
        if (target >= b)
        {
            int shou_one = target / b;
            int amari_one = target % b;
            target = amari_one;
            shou.push_back(shou_one);
        }
        else
        {
            shou.push_back(0);
            // これ毎回間違える--!!
            // target = target * 10 + warareru[i++];
            continue;
        }
    }
    if (target >= b)
    {
        int shou_one = target / b;
        int amari_one = target % b;
        target = amari_one;
        shou.push_back(shou_one);
    }

    amari = target; // これって b 未満だよね？
    assert(target < b);
}

// ✅ checked.
void test_long_div_me()
{
    // 0588235294117647 0588235294117647 0588235294117647 を 17 で割ったあまりは？
    // まず、 shou を割ったあまりは何か
    const vector<int> warareru{5, 8, 8, 2, 3, 5, 2, 9, 4, 1, 1, 7, 6, 4, 7};
    vector<int> shou;
    int amari; //  (answer)
    int b = 17;
    long_div_me(/*ref const in*/ warareru,
                /*int b*/ b,
                /*ref out*/ shou,
                /*ref out*/ amari);
    const vector<int> answer{3, 4, 6, 0, 2, 0, 7, 6, 1, 2, 4, 5, 6, 7};

    if (debug)
    {
        cout << "shuo: " << endl;
        for (auto s : shou)
        {
            cout << s << ",";
        }
        cout << endl;

        cout << "answer:" << endl;
        for (auto a : answer)
        {
            cout << a << ",";
        }
        cout << "endl";
        cout << flush;
    }

    assert(answer.size() == shou.size());
    for (int i = 0;
         i < shou.size(); ++i)
    {
        assert(shou[i] == answer[i]);
    }
    assert(amari == 8);
}

void set_vec_from_num(const int num, /*out*/ vector<int> &out)
{
    out.resize(0);
    int now = num;

    while (now != 0)
    {
        int amari = now % 10;
        out.push_back(amari);
        now = now / 10;
    }
    reverse(ALL(out));
}

/*
    欲しいあまりの出し方としては、
    0588235294117647 0588235294117647 0588235294117647 
    と 1回、 2回 .. やっていくなかで、
*/
int step2(/*ref in*/ const vector<int> &repeated,
          /*ref out*/ vector<int> &amari_vector_answer,
          /*in*/ const int M)
{
    amari_vector_answer.resize(0);
    int times = 1;
    int amari = 0;
    vector<int> shou;
    long_div_me(
        /*const ref: warareru*/
        repeated,
        /*const: b*/ M,
        /*out ref */ shou,
        /*out ref*/ amari);

    amari_vector_answer.push_back(amari);
    while (amari != 0)
    {
        vector<int> new_vec;
        set_vec_from_num(/*const int*/ amari, /*ref out*/ new_vec);
        for (auto r : repeated)
        {
            new_vec.push_back(r);
        }

        times += 1;
        long_div_me(
            /*const ref: warareru*/
            /*ref intput*/ new_vec,
            /*b*/ M,
            /*out ref*/ shou,
            /*out ref*/ amari);
        amari_vector_answer.push_back(amari);
    }
    assert(amari_vector_answer.size() == times);
    return times;
}

void test_step2()
{
    int M = 17;
    vector<int> amari_vector_answer;
    vector<int> repeated{0, 5, 8, 8, 2, 3, 5, 2, 9, 4, 1, 1, 7, 6, 4, 7};
    int times = step2(
        /*const ref input*/ repeated,
        /*ref out*/ amari_vector_answer,
        /*const int*/ M);
    vector<int> answer{8, 16, 7, 15, 6, 14, 5, 13, 4, 12, 3, 11, 2, 10, 1, 9, 0};
    if (debug)
    {

        cout << "times: " << times << endl;
        cout << "answer size: " << answer.size() << endl;
        cout << "amari:" << endl;
        for (auto am : amari_vector_answer)
        {
            cout << am << ",";
        }
        cout << endl
             << flush;
    }
    assert(times == answer.size());
    assert(amari_vector_answer.size() == answer.size());

    for (int i = 0;
         i < answer.size();
         ++i)
    {
        assert(amari_vector_answer[i] == answer[i]);
    }
}

int main(int argc, char *argv[])
{
    test_step2();

    // test_long_div_me();
}