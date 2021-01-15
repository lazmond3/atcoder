#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
bool debug = false;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define int long long
// clang-format off
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
#define RED "\033[1;31m"
#define GRE "\033[1;32m"
#define BLU "\033[34m"
#define CLR "\033[0m"
// clang-format on

// 🎄⭐️🎅 欲しいもの
// - string の ゼロフィル関数

/*
// http://en.wikipedia.org/wiki/ANSI_escape_code
https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47
*/

struct left_right {
    int left;
    int right;

    left_right(int l, int r) : left(l), right(r) {}
};
/*
    判定関数
    左側に何要素、右側に何要素
    .. これは lower_bound
   を使いたいんだけど、もし一致してしまう場合はどうするの？
   たとえば、
   [1,2,3,4,5,6,7,8,9] [4,5,6,7,8,9,0,-,] みたいんた感じで5.0 が指定されたとき、
   // 1,2,3,4,5 (left)  6,7,8,9 (right)
   // ということになるの？本当は
   // 1,2,3,4,5 (left) 5,6,7,8,9 (right)
   // にしたいの？ しかしこれだと全体の個数の中で、が乱れてくる？

   // もしleft-の最高の値が 5.0 と十分近い値だったら、一致とみなしてright
   にも入れるの？

   // こういうケースで中央の I になる場合, [I] にとっては、
   // 上記のように両方に入れなきゃいけなかったりする。
   OOOIIIOOO
       o   x
   OOOII I OOOO
   もしかしてこういうことを考えなくても、二分探索の単調性を利用して
   片側に範囲を削り続けることで、 正解になるんじゃないの？

      ○     ●
   OOOOI [I] IOOOI

   // 考えてなかったケース
   数字の重複について考える必要はあるか？
*/
struct left_right count_left_right_item_number(const vector<int>& vec,
                                               double target_number) {
    // FIXME
    return left_right(0, 100);
}

// 二分探索用判定関数

/*
    もし全体の合計が奇数個だとしたら、これは作れなくない？
    [1,2,3,4,5]
    で、4.00 だとしたら、厳密に 4 で止まってくれる？
    // テストが必要
          4.5   _  7.6 ここに止まりたい、ってことはできんのかね
                |
    OOIIIOOIIIIIOOOOOOOIIOOOIO
*/
bool is_good(const vector<int>& nums1, const vector<int>& nums2,
             double target_number) {
    return false;
}

/*
    struct かなんかで、結局最後の中央値の値を返したい。
    が、 double であるかどうかの判定というのもあるし..
    最初から全部 double でやればよさそう。
    問題の要求精度は -106 <= nums1[i], nums2[i] <= 106 であり、
    double の精度は 15ケタある。
*/
double binary_search_median(const vector<int>& nums1, const vector<int>& nums2,
                            const double _start, const double _end) {
    double start = _start;
    double end = _end;

    // たしか二分探索ってn回くらい繰り返したほうがよかった気がする

    // FIXME
    return 0.0;
}

double calc_median(const vector<int>& vec) {
    if (vec.size() % 2 == 1) {
        // 7 要素あったら index = 3 にしたい。
        return vec[vec.size() / 2];
    }
    // 8 要素あったら、 3と4にしたい。
    // 012 34 567
    auto a = vec[vec.size() / 2 - 1];
    auto b = vec[vec.size() / 2];
    return static_cast<double>((a + b) / 2.0);
}

// https://leetcode.com/problems/median-of-two-sorted-arrays/
class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        /*
            考察:
            中央値の問題は、順序だけが大事なので、個別の数字は無視できる。
            数字はあとから振り直すことができる。

            O: 配列1に入っている数字
            I: 配列2に入っている数字
            OOOIIIOOOOOOOIIOOOOOIIOOOOIIOO : 1 が完全に2を包んでいる場合

                              ○     ⭕️              ●
            0   1   2   3   4   5   6   7   8   9  10  11  12
            O   O   O   O   I   I   O   O   O   O   I   I   I

            理想としては、         ●   ○
    などで停止してほしい？(停止条件から決める) 0   1   2   3   4   5   6   7   8
    9  10  11  12 O   O   O   O   I   I   O   O   O   O   I   I   I
    相互にズレている場合。
    O:      0   1   2   3           4   5   6   7
    I:                      0   1                   2   3   4

    STEP 1(7.25)                       ○ x


            O の中央値は ○
            I の中央値は ●
            全体の中央値は ⭕️

            エンドポイントの順番はそうだけど、中央値の順番は逆転するケース
            0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 (16)
            O I I I I I O O O O O O O O O O I
    O:      0           1 2 3 4 5 6 7 8 9 0 (11)
    I:        0 1 2 3 4                     5
                   ●        ⭕️   ○

             // endpoint でスワップしたほうがいい？
            それぞれの中央値は簡単に計算できる。

            n + m == 偶数のとき、中央値はdouble
            奇数のとき、中央値はちょうど定まる。
        */

        /*
            「a,bそれぞれの中央値の中間に全体の中央値が存在する」

            このケースにも当てはまりそう
            OOOOOOIIIIIIIIIIOOOOO

            証明:
            I にとってみると、中央値の右側のほう
            O にとってみると、中央値より、やや左
            必ず、2つの間に存在するか？ ( これに違反するケースを考える )
            OOOOOOOOOIIIIIIII => 中間にある。
            OIIIIIIIIIOO      => 中間にある。
            ai ai+1,,... am
            bi bi+1,,... bn   => ai, bj がそれぞれの中央値のとき、
            ai,bj の双方の右側に全体の中央値 c があると仮定すると、
            ai < c
            bj < c かつ、
              // ここ雑
            ai の右側には、 M(a)/2 個のaの要素が存在する。
            bj の右側には、 N / 2 個の bの要素が存在する。
            ai,bj < c ということは、 c は
                ai+1 <= c
                bj+1 <= c
            であるが、この場合、ai+1 の右側には、 M/2 - 1個のaの要素が、
            bj+1 の右側には、多くても N/2 - 1 個の b の要素しか存在しない。
            一方で、 ai+1 の左側には、 ai を含めて、 M/2+1 個のaの要素が、
                    bj+1 の左側には、 bj を含めて、 N/2+1
           個のbの要素が存在する。 両側で数に差があるので、 ai,bj < c
           という中央値はありえない。◇
        */
        /*
            以下の条件を利用して、二分探索をしたいが、
            二分探索の条件としては、判定がO(1)でできる必要がある
                  (
                      判定については単調性が必要だが、
                      上記の cを移動させると、さらに
                      両側の要素の偏りが大きくなるので、
                      単調性は存在するといえる。
                  )
                 （必要はないが、O(log(m))でできるらしいので)

             以下のケースにおいて、 適当なインデックスを定めたとき、
             どうやってそれを全体中央値だと判定する？

            Ans.
                => a の中で二分探索をして、
                   インデックスの位置を計算することによって。
                => b の中でさらに二分探索をして、
                   インデックスの位置を計算することによって。
                doubleの位置は計算できないが、それより大きい数が何個あり,,
           というのは わかるはず。 それぞれのインデックスを ap, bq としたとき、
                ap, bq の値から、両側に ある要素の個数は計算できるはずなので、
                これを利用して判定できる。
                   o          x
             OOOOOOIIIIIIIIIIIIIIIIOOOOIIIII
        */

        // 8 の場合、インデックスは 4 となる。
        // 9 の場合、インデックスは 4となる (中央値)
        double nums1_med = calc_median(nums1);  // FIXME nums1 の 中央値
        double nums2_med = calc_median(nums2);  // FIXME nums2 の 中央値

        // binary_search_median()
        return 0.0;
    }
};

template <class T>
void test_eq_assert(const T val, const T answer, const string& label) {
    if (debug && val == answer) {
        cout << GRE;
        cout << "--------- [[ " << label << "]] ---------" << endl;
        cout << CLR;
    }
    if (val != answer) {
        cout << RED;
        cout << "--------- [[ " << label << "]] ---------" << endl;
        cout << CLR;
        cout << "Assertion failed: "
             << "(val = " << RED << val << CLR << ", label = " << label << ", "
             << "answer = " << BLU << answer << CLR << ") " << endl
             << flush;
        cout << CLR;

        exit(1);
    }
}

signed main() {
    const char* DEBUG_p = std::getenv("DEBUG");
    debug = DEBUG_p != NULL && strnlen(DEBUG_p, 1) > 0;

    // STL swap のテスト　
    {
        int a = 10;
        int b = 100;
        swap<int>(a, b);
        test_eq_assert<int>(a, 100, "swapテスト1 a == 100");
        test_eq_assert<int>(b, 10, "swapテスト2 b == 10");
    }

    // STL lower_bound という2分探索
    {
        vector<int> v = {1, 2, 3, 4, 5};
        double d = 4.00;
        double d2 = 4.00000000001;
        double d3 = 3.99;
        auto lbp = lower_bound(ALL(v), d);
        test_eq_assert<int>(*lbp, 4, "lower bound テスト 1 4.00 に対して");
        lbp = lower_bound(ALL(v), d2);
        test_eq_assert<int>(*lbp, 5,
                            "lower bound テスト 2 4.00000000001 に対して");
        lbp = lower_bound(ALL(v), d3);
        test_eq_assert<int>(*lbp, 4, "lower bound テスト 3 3.99 に対して");
    }
    // STL upper_bound という2分探索
    {
        vector<int> v = {1, 2, 3, 4, 5};
        double d = 4.00;
        double d2 = 4.00000000001;
        double d3 = 3.99;
        auto lbp = upper_bound(ALL(v), d);
        // ❌ ここがポイントで、自分自身を入れない。
        test_eq_assert<int>(*lbp, 5, "upper bound テスト 1 4.00 に対して");
        lbp = upper_bound(ALL(v), d2);
        test_eq_assert<int>(*lbp, 5,
                            "upper bound テスト 2 4.00000000001 に対して");
        lbp = upper_bound(ALL(v), d3);
        test_eq_assert<int>(*lbp, 4, "upper bound テスト 3 3.99 に対して");
    }

    // calc median のテスト
    {
        vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        test_eq_assert(calc_median(vec), 5.0, "calc median のテスト1 9要素");
        vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
        test_eq_assert(calc_median(vec), 5.5, "calc median のテスト2 10要素");
        vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        test_eq_assert(calc_median(vec), 5.5, "calc median のテスト3 10要素");
    }

    // // ❌ 使う部分の範囲だけっぽい x から n文字目だった。 .substr(x, n)
    // test_eq_assert<string>(string("abcd").substr(1, 3), "bcd",
    //                        "abcd substr 1,3");
}

/* TODO
    - test_eq じゃなくて test_double_eq も必要そう。
    abs を使えばいい？

    - めぐる式にぶんたんさくをググル

    - atcoder double の十分小さい数ってどうやって使ってる?
    10^-10 くらい用意したほうがよさそう？

    作れそうな関数
    - count_left_right_item_number
    - calc_median
    - is_good
    - めぐる式のあと: binary_search_median

    - テストをかけるようになりたい。厳密解で。

*/