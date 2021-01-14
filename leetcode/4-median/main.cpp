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

        */
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
    Solution a = Solution();
    // // ❌ 使う部分の範囲だけっぽい x から n文字目だった。 .substr(x, n)
    // test_eq_assert<string>(string("abcd").substr(1, 3), "bcd",
    //                        "abcd substr 1,3");
}