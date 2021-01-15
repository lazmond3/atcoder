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
    bool operator==(const left_right& rhs) const {
        return (rhs.left == this->left && rhs.right == this->right);
    }
    bool operator!=(const left_right& rhs) const { return !(*this == rhs); }
};
ostream& operator<<(ostream& os,
                    const left_right& dt) {  //}, const left_right& dt) {
    os << "(left: " << dt.left << ", right: " << dt.right << ")";
    return os;
}

struct left_right count_left_right_item_number(const vector<int>& vec,
                                               double target_number) {
    // FIXME
    auto p = lower_bound(ALL(vec), target_number);
    // もし begin のときは、 0 になってしまう。
    int left = -1;
    int right = -1;

    if (p == vec.end()) {
        left = vec.size();
        right = 0;
    } else if (eq_double(*p, target_number)) {
        // [ 1, 2 ] のとき 2　だと distance = 1 になる。
        // かといってright = 1というわけではない..
        left = distance(vec.begin(), p);
        right = vec.size() - left - 1;
        // いやーこれが怪しい気もする
        // このケース
        /*
        nput
        [76,89,104,287,566,596,660,719,879,1012,1080,1225,1304,1568,1898,1959,1965,2140,2276,2395,2634,2764,2801,2877,3009,3010,3188,3318,3356,3459,3549,3586,3793,3844,3890,4297,4328,4423,4494,4546,4570,4613,4616,4630,4680,4807,5002,5237,5245,5312,5345,5489,5606,5731,5732,5796,5816,6116,6197,6201,6204,6303,6339,6357,6395,6412,6445,6552,6584,6612,6678,6823,6825,6892,7272,7311,7534,7535,7686,7891,8032,8112,8120,8226,8239,8578,8583,8807,9214,9317,9384,9388,9447,9484,9611,9739,9753,9812,9838,9854,9905,9936,9944,9978,10033,10346,10356,10581,10583,10755,10764,10819,10845,11040,11049,11111,11169,11183,11249,11597,11640,11739,11743,11856,11925,11950,11991,12086,12175,12531,12551,12581,12721,12987,13101,13176,13259,13342,13401,13550,13635,13657,13713,13981,14014,14032,14039,14093,14152,14205,14322,14339,14361,14444,14449,14471,14536,14600,14661,14892,15034,15313,15399,15530,15553,15653,15723,15734,15767,15811,16002,16057,16066,16182,16453,16540,16629,16924,16946,17323,17339,17362,17416,17466,17629,1776
        [122,255,318,346,361,452,520,584,603,657,669,695,708,730,745,757,766,770,773,787,799,818,845,873,875,899,966,985,1103,1114,1164,1238,1243,1261,1284,1339,1351,1424,1431,1457,1468,1482,1493,1514,1584,1601,1630,1644,1683,1739,1744,1751,1793,1867,1870,1909,1912,1941,1970,2017,2137,2155,2194,2214,2236,2257,2472,2514,2548,2654,2734,2791,2798,2823,2886,2887,2919,2941,2958,2998,2999,3026,3054,3061,3174,3192,3225,3282,3358,3389,3392,3406,3427,3429,3470,3501,3555,3590,3604,3676,3718,3724,3744,3765,3796,3803,3808,3846,3883,3914,3916,4049,4092,4102,4118,4128,4159,4170,4170,4287,4296,4309,4349,4363,4374,4571,4594,4606,4621,4637,4731,4746,4775,4800,4816,4832,4837,4867,4880,4935,4942,4976,5007,5077,5106,5122,5179,5199,5237,5255,5265,5341,5370,5378,5394,5398,5467,5493,5518,5548,5630,5651,5762,5842,5867,5914,5915,5935,6013,6081,6092,6132,6178,6217,6245,6289,6409,6410,6445,6464,6478,6481,6660,6711,6711,6767,6778,6782,6788,6844,6855,6945,7036,7107,7119,7210,7229,7256,7292,7292,7355,7395,7446,7455,7472,74
        View All
        Output
        16244.50000
        Expected
        16240.00000
        こういう風にミスっているから、奇数偶数を間違えている気がする。
        */
    } else {
        // このケースのとき、
        // [1,2,3] で 2.5 が指定されると [3] に指されて、left = 2
        left = distance(vec.begin(), p);
        right = vec.size() - left;
    }

    return left_right(left, right);
}

int is_good(const vector<int>& nums1, const vector<int>& nums2,
            double target_number) {
    auto num1_lr = count_left_right_item_number(nums1, target_number);
    auto num2_lr = count_left_right_item_number(nums2, target_number);
    // ❌
    // 領域的な、単調性が必要なので、片側のほうが多いか一致する、という条件で組む必要がある。
    // target value が小さければ ok を出したいので、left のほうが少なければ ok.

    int left = num1_lr.left + num2_lr.left;
    int right = num1_lr.right + num2_lr.right;
    if (debug) {
        cout << "\t[is good] target: " << target_number
             << ",  num1_lr : " << num1_lr << ", num2_lr: " << num2_lr << endl;
    }

    if (left == right) return 2;

    if (left < right) {
        return 1;
    } else {
        return 0;
    }
}

// 別関数によって、以下の挙動をサポートする。
double sophisticate_mid(vector<int> nums1, vector<int> nums2,
                        const double target_value) {
    int n = nums1.size();
    int m = nums2.size();

    const int t = n + m;
    if (t % 2 == 0) {
        // 中間に来るケース
        // [1,2] [3,4] <= 2.5
        // 両方その数をサス[1,3,5][2,3,4] <= 3
        // 片方のみ [2,5,6,9][4,6]       <= 7.5
        // 片方との合成 [1,2,9][4]
        const auto l1 = lower_bound(ALL(nums1), target_value);
        const auto l2 = lower_bound(ALL(nums2), target_value);
        bool l1_end = l1 == nums1.end();
        bool l2_end = l2 == nums2.end();
        if (l1_end && l2_end) {
            // アサート入れるのはよさそう。
            assert("not this case" && 0);
        }

        // mid pattern
        if (l1_end) {
            if ((l2 == nums2.begin()) && (*l2 > target_value)) {
                // mid pattern
                return (*l2 + LAST(nums1)) / 2.0;
            }
        }
        if (l2_end) {
            if ((l1 == nums1.begin()) && (*l1 > target_value)) {
                // mid pattern
                return (*l1 + LAST(nums2)) / 2.0;
            }
        }

        double min_edge;

        if (!l1_end && (*l1 <= target_value)) {
            min_edge = *l1;
        }
        if (debug) {
            cout << "[sop] l1end: " << l1_end << ", l2end:  " << l2_end << endl;
            cout << "[sop] min_edge: " << min_edge << endl;
            // cout << "[sop] l1 : " << *l1;
            // cout << ", l2: " << *l2 << endl;
        }
        if (debug) {
            cout << "[sop] l2end l2 distance: " << distance(nums2.begin(), l2)
                 << endl;
            cout << flush;
        }
        if (!l2_end && (*l2 <= target_value)) {
            chmax<double>(min_edge, static_cast<double>(*l2));
        }

        chmax<double>(min_edge,
                      max(l1 != nums1.begin() && (*(l1 - 1) <= target_value)
                              ? *(l1 - 1)
                              : std::numeric_limits<double>::min(),
                          l2 != nums2.begin() && (*(l2 - 1) <= target_value)
                              ? *(l2 - 1)
                              : std::numeric_limits<double>::min()));
        if (debug) {
            cout << "[sop] min_edge: " << min_edge << endl;
            // cout << "[sop] l1 : " << *l1;
            // cout << ", l2: " << *l2 << endl;
        }

        double max_edge;
        max_edge = min(!l1_end && *l1 >= target_value
                           ? *l1
                           : std::numeric_limits<double>::max(),
                       !l2_end && *l2 >= target_value
                           ? *l2
                           : std::numeric_limits<double>::max());
        if (debug) {
            cout << "[sop] max_edge: " << max_edge << endl;
            // cout << "[sop] l1 : " << *l1;
            // cout << ", l2: " << *l2 << endl;
        }
        return (min_edge + max_edge) / 2.0;

    } else {
        // この場合はたぶんそのまんま！
        return target_value;
    }
}

/* calc median の復活 */
double calc_median(const vector<int>& vec) {
    int n = vec.size();
    int m = n / 2;
    if (n % 2 == 0) {
        return ((double)vec[m] + vec[m - 1]) / 2.0;
    } else {
        return (double)(vec[m]);
    }
}
/*
    struct かなんかで、結局最後の中央値の値を返したい。
    が、 double であるかどうかの判定というのもあるし..
    最初から全部 double でやればよさそう。
    問題の要求精度は -106 <= nums1[i], nums2[i] <= 106 であり、
    double の精度は 15ケタある。
*/
/*
    考察を変えて、 min max
   の完全な二分探索でとりえあえずサンプル通らないか実験してみる。
*/
double binary_search_median(const vector<int>& nums1,
                            const vector<int>& nums2) {
    if (nums2.size() == 0) {
        return calc_median(nums1);
    }
    if (nums1.size() == 0) {
        return calc_median(nums2);
    }

    double min_ = min(nums1[0], nums2[0]);  // min は ok とする。
    double max_ = max(nums1[nums1.size() - 1],
                      nums2[nums2.size() - 1]);  // max は ng　とする。

    double mid = 0;
    for (int i = 0; i < 100; ++i) {
        mid = (min_ + max_) / 2.0;
        int flag = is_good(nums1, nums2, mid);
        if (flag == 2) {  // これはやめる合図
                          // 別関数に飛ばす
            return sophisticate_mid(nums1, nums2, mid);
        } else if (flag == 1) {  // left < right
            min_ = mid;
        } else {
            max_ = mid;
        }
    }

    // 多分ここには来ない。
    return (min_ + max_) / 2.0;
    // たしか二分探索ってn回くらい繰り返したほうがよかった気がする

    // FIXME
    // return 0.0;
}

// https://leetcode.com/problems/median-of-two-sorted-arrays/
class Solution {
   public:
    double findMedianSortedArrays(const vector<int>& nums1,
                                  const vector<int>& nums2) {
        // ❌ 考察を削除した。
        return binary_search_median(nums1, nums2);
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
        test_double_assert(Solution().findMedianSortedArrays(vector<int>{1, 3},
                                                             vector<int>{2, 7}),
                           2.5, " solution test 13: [1,3][2,7] -> 2.5");
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

    - oj test を自分で,,, double に対応したい。　

*/
