#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
constexpr double eps = 1e-11;
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
    } else {
        // このケースのとき、
        // [1,2,3] で 2.5 が指定されると [3] に指されて、left = 2
        left = distance(vec.begin(), p);
        right = vec.size() - left;
    }

    return left_right(left, right);
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
/*
    これが間違っている。
    [1,3] [2]
    のとき、
    min = 1, max = 3 で mid = 2 だと ok 出してしまう。
    mid = 2.5 でも ok　出してしまうのだが、
    1,  3, => 2
    2,  3  => 2.5 // mid が右にずれるが、 ok なので min_
   のほうが出てしまう！全然ok じゃない！ 2.5 3 => 2.75 これだと、

*/
int is_good(const vector<int>& nums1, const vector<int>& nums2,
            double target_number) {
    auto num1_lr = count_left_right_item_number(nums1, target_number);
    auto num2_lr = count_left_right_item_number(nums2, target_number);
    // ❌
    // 領域的な、単調性が必要なので、片側のほうが多いか一致する、という条件で組む必要がある。
    // target value が小さければ ok を出したいので、left のほうが少なければ ok.
    /*
        ケーススタディ
        [1,2,3,8] [4,5,6,7,8]

        4.5 は？
        3 + 1 = 4   | 1 + 4 = 5
        right の方が重いなら、 min_ を切り上げて、もっと大きい数にしたい -> [4.5
       - 8]

        6.25 ( 4.5 と 8 の平均 )は？
        3+3 = 6 | 1+2 =3 で、全然左のほうが重い
        -> [4.5, 6.25]
        5.375 は？


        -> 1,2,3,4,[5],6,7,8,8
    */
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
        return binary_search_median(nums1, nums1);
    }
    if (nums1.size() == 0) {
        return binary_search_median(nums2, nums2);
    }

    double min_ = min(nums1[0], nums2[0]);  // min は ok とする。
    double max_ = max(nums1[nums1.size() - 1],
                      nums2[nums2.size() - 1]);  // max は ng　とする。

    double mid = 0;
    for (int i = 0; i < 10; ++i) {
        mid = (min_ + max_) / 2.0;
        int flag = is_good(nums1, nums2, mid);
        if (debug) {
            string label;
            if (flag == true) {
                label = "みぎの方が重い";
            } else {
                label = "左がおもい";
            }
            printf(
                "[binsearch] i = %d, min_: %f, max: %f, mid: %f flag: %d ( %s "
                ")\n",
                i, min_, max_, mid, flag, label.c_str());
        }
        if (flag == 2) {
            return mid;
        } else if (flag == 1) {  // left < right
            min_ = mid;
        } else {
            max_ = mid;
        }
    }
    if (debug) {
        printf("\t[bin search] final: min_ %f, max_: %f\n", min_, max_);
    }
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
        lbp = lower_bound(ALL(v), -1.1);
        if (debug)
            cout << "lbp distance -1.1: " << distance(v.begin(), lbp) << endl;
        assert("lower bound テスト 4 -1.1 に対して. 存在しない値は？" &&
               lbp == v.begin());

        // test_eq_assert(lbp, v.end(),
        //                "lower bound テスト 4 -1.1 に対して.
        //                存在しない値は？");
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
    - google のやつも厳密解でときたい。

*/
