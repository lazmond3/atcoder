#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;
const bool debug = false;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define int long long

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

// repeated を割ったループ
// return amari
int repeated_and_amari_cycle(const int M,
                             /*ref out*/ vector<int> &amari_vector,
                             /*const ref in*/ const vector<int> &repeated_with_amari) // repeated とは限られず、先頭にあまりが付加した形になる。
{
    int i = 0;
    int target = repeated_with_amari[i++];
    int amari = 0;
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
    return amari;
}

// repeated を何回連結させるとあまりがゼロになるか。
int repeated_mod_times(const int M,
                       /*ref out*/ vector<int> &amari_vector,
                       /*const ref in*/ const vector<int> &repeated)
{
    int times = 1;
    int amari = 0;

    amari = repeated_and_amari_cycle(/*const int*/ M,
                                     /*ref out*/ amari_vector,
                                     /*const ref in*/ repeated);

    vector<int> not_used_amari_vector;
    amari_vector.push_back(amari);
    while (amari != 0)
    {
        vector<int> next_repeated;
        int _amari = amari;

        while (_amari != 0)
        {
            next_repeated.push_back(_amari % 10);
            _amari = _amari / 10;
        }

        for (auto r : repeated)
            next_repeated.push_back(r);

        amari = repeated_and_amari_cycle(
            /*const int*/ M,
            /*ref out*/ not_used_amari_vector,
            /*const ref in*/ next_repeated);
        amari_vector.push_back(amari);
        times += 1;
    }
    return times;
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
    int times = repeated_and_amari_cycle(
        /*const int*/ M,
        /*ref out*/ amari_vector_repeated,
        /*const ref in*/ repeated);

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
}

signed main(int argc, char *argv[])
{
    long long N;
    int M;
    cin >> N >> M;

    service(N, M);
}
