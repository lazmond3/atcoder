#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>
using namespace std;
constexpr double eps = 1e-11;
bool debug = false;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define LAST(x) x[x.size() - 1]
#define FAST(x) x[0]
#define int long long
// clang-format off
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }
#define RED "\033[1;31m"
#define GRE "\033[1;32m"
#define BLU "\033[34m"
#define CLR "\033[0m"
// clang-format on

// 🎄⭐️🎅 欲しいもの
// - string の ゼロフィル関数

bool eq_double(double a, double b) {
    if (abs(a - b) < eps) return true;
    return false;
}

// https://leetcode.com/problems/median-of-two-sorted-arrays/
class Solution {
   public:
    int calc_line_majime(const string& linestring, const int count) {
        // xxxx 1
        // ooox が最適

        // xxxx 2
        // ooox となったあとに、もう一度使う
        // oooo となり、 4が答え。

        // c 回 できるとする。
        //        xoooxoxxooooooox
        // c,0    x
        // c,2    xoo
        // c-1,2  ooo
        // c,8    xoooxoxx
        // c,5    xoooxo
        // c,6    xoooxox
        // c,7    xoooxoxx
        // c-1,6  ooooxox <OR>
        // c-1,6  xooooox
        // c-1,5  ooooxo   <OR> ->
        // c-1,5  xooooo   になるんですよね score = 6
        // これって、 score 更新したときに
        // 単純に入れ替えるわけには　いかなそう。
        // マイナス10くらいから見た方がいいというのと、x
        // の位置に押したとすると、その先も反転できる、これが...
        // だから先頭以外のところ

        return 0;
    }
};

template <class T>
void test_eq_assert(const T& val, const T& answer, const string& label) {
    if (debug && val == answer) {
        cout << GRE;
        cout << "--------- [[ " << label << "]] ---------" << endl;
        cout << CLR;
        cout << flush;
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

template <class T>
void test_double_assert(const T& val, const T& answer, const string& label) {
    if (debug && eq_double(val, answer)) {
        cout << GRE;
        cout << "--------- [[ " << label << "]] ---------" << endl;
        cout << CLR;
        cout << flush;
    }
    if (!eq_double(val, answer)) {
        cout << RED;
        cout << "--------- [[ " << label << "]] ---------" << endl;
        cout << CLR;
        cout << "Assertion failed: "
             << "(val = " << RED << val << CLR << ", label = " << label << ", "
             << "answer = " << BLU << answer << CLR << ") " << endl
             << flush;
        cout << CLR;

        // cout << flush;
        exit(1);
    }
}

#ifdef TEST
signed main2() {
#else
signed main() {
#endif
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
        lbp = lower_bound(ALL(v), -1.1);
        if (debug)
            cout << "lbp distance -1.1: " << distance(v.begin(), lbp) << endl;
        assert("lower bound テスト 4 -1.1 に対して. 存在しない値は？" &&
               lbp == v.begin());
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
    // 🚦 ❌ 廃止
    // {
    //     vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    //     test_eq_assert(calc_median(vec), 5.0, "calc median のテスト1 9要素");
    //     vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
    //     test_eq_assert(calc_median(vec), 5.5, "calc median のテスト2
    //     10要素"); vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //     test_eq_assert(calc_median(vec), 5.5, "calc median のテスト3
    //     10要素");
    // }

    // count_left_right_item_number のテスト
    {
        vector<int> vec = {1, 2, 3};
        assert(left_right(0, 0) == left_right(0, 0));

        test_eq_assert<struct left_right>(
            count_left_right_item_number(vec, 2.5), left_right(2, 1),
            "count left のテスト 1 {1,2,3}, 2.5");
        test_eq_assert(count_left_right_item_number(vec, 2), left_right(1, 1),
                       "count left のテスト 2 {1,2,3}, 2.0");

        // 6),
        //                "count left のテスト1 3.4");
    }

    // solution のテスト
    {
        test_double_assert(Solution().findMedianSortedArrays(vector<int>{1, 3},
                                                             vector<int>{2}),
                           2.00, " solution test 1: [1,3][2] -> 2.00");
        test_double_assert(Solution().findMedianSortedArrays(vector<int>{1, 2},
                                                             vector<int>{3, 4}),
                           2.500, " solution test 2: [1,2][3,4] -> 2.500");
        test_double_assert(Solution().findMedianSortedArrays(vector<int>{0, 0},
                                                             vector<int>{0, 0}),
                           0.0, " solution test 3: [0,0][0,0] -> 0.0");
        test_double_assert(
            Solution().findMedianSortedArrays(vector<int>{}, vector<int>{1}),
            1.0, " solution test 4: [][1] -> 1.0");
        test_double_assert(
            Solution().findMedianSortedArrays(
                vector<int>{1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                            12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22},
                vector<int>{0, 6}),
            10.50000, " solution test 5:  -> 10.50");
        test_double_assert(Solution().findMedianSortedArrays(
                               vector<int>{1, 3, 5}, vector<int>{2, 3, 4}),
                           3.0, " solution test 6: [1,3,5][2,3,4] -> 3.0");
        test_double_assert(Solution().findMedianSortedArrays(vector<int>{3, 6},
                                                             vector<int>{2, 8}),
                           4.5, " solution test 7: [3,6][2,8] -> 4.5");
        test_double_assert(Solution().findMedianSortedArrays(
                               vector<int>{1, 2, 3}, vector<int>{5, 7, 8}),
                           4.0, " solution test 8: [1,2,3][5,7,8] -> 4");
        test_double_assert(Solution().findMedianSortedArrays(
                               vector<int>{2, 5, 7}, vector<int>{4}),
                           4.5, " solution test 9: [2,5,7][4] -> 4.5");
        test_double_assert(Solution().findMedianSortedArrays(vector<int>{1, 2},
                                                             vector<int>{3, 4}),
                           2.5, " solution test 10: [1,2][3,4] -> 2.5");
        test_double_assert(Solution().findMedianSortedArrays(
                               vector<int>{1}, vector<int>{2, 3, 4}),
                           2.5, " solution test 10: [1,2][3,4] -> 2.5");
        test_double_assert(Solution().findMedianSortedArrays(
                               vector<int>{1, 3, 4, 6, 9}, vector<int>{8}),
                           5.0, " solution test 11: [1,3,4,6,9][8] -> 5.0");
        test_double_assert(
            Solution().findMedianSortedArrays(vector<int>{1, 4, 5, 8, 9},
                                              vector<int>{2, 6, 7}),
            5.5, " solution test 12: [1,4,5,8,9][2,6,7] -> 5.5");
    }
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

    - LINE のやつ DP で書きたい。
    - Union find を自分でゼロから書く。
    - google のやつも厳密解でときたい。
    - vector last もほしい。

*/
