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

// https://leetcode.com/problems/zigzag-conversion/
/*
        P     I    N
        A   L S  I G
        Y A   H R
        P     I

        A         K
        B       J L
        C     I   M
        D   H     N
        E G       O
        F         P

        ACE
        BDF



        row = 6
        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
        A B C D E F G H I  J  K  L  M  N  O  P  Q  R  S  T
        x         o           x              o
          p                p     p
            x           x           x
              x       x                x

*/
class Solution {
   public:
    string convert(string s, int numRows) {
        // string answer;
        if (numRows == 1) {
            return s;
        }
        if (numRows == 2) {
            string answer;
            const int size = s.size();
            vector<char> answer_vec;
            int j = 0;

            while (j < size) {
                answer_vec.push_back(s[j]);
                j += 2;
            }
            j = 1;
            while (j < size) {
                answer_vec.push_back(s[j]);
                j += 2;
            }
            return string(ALL(answer_vec));
        }
        if (numRows >= 3) {
            vector<char> answer_vec;
            // これ出た時点で、numRows == 1 を考えないのはダメすぎた..
            const int m2_wave_length = numRows * 2 - 2;
            const int size = s.size();

            // size = 2,
            // m2 = 1 * 2 - 2 == 0;
            for (int i = 0; i < numRows; ++i) {
                if (i == 0) {
                    if (debug) {
                        cout << "i == 0" << endl;
                    }
                    int j = 0;
                    while (j < size) {
                        answer_vec.push_back(s[j]);
                        j += m2_wave_length;
                    }
                }

                if (i == numRows - 1) {
                    if (debug) {
                        cout << "here ! i : " << i << endl;
                    }
                    int j = numRows - 1;
                    while (j < size) {
                        if (debug) {
                            cout << "size: " << size << ", j : " << j
                                 << ", i: " << i << "numRows: " << numRows
                                 << endl;
                        }
                        answer_vec.push_back(s[j]);
                        if (m2_wave_length == 0) break;
                        j += m2_wave_length;
                    }
                }

                if (i != 0 && i != numRows - 1) {
                    int j1 = i;
                    int j2 = m2_wave_length - i;
                    while (j1 < size) {
                        answer_vec.push_back(s[j1]);
                        if (j2 < size) {
                            answer_vec.push_back(s[j2]);
                        }
                        j1 += m2_wave_length;
                        j2 += m2_wave_length;
                    }
                }
            }
            return string(ALL(answer_vec));
        }
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
    {
        test_eq_assert(Solution().convert("PAYPALISHIRING", 3),
                       string("PAHNAPLSIIGYIR"), "test 1: PAHNAPLSIIGYIR");
        test_eq_assert(Solution().convert("PAYPALISHIRING", 4),
                       string("PINALSIGYAHRPI"), "test 2: PINALSIGYAHRPI");
        test_eq_assert(Solution().convert("A", 1), string("A"), "test 3: A");
        test_eq_assert(Solution().convert("AB", 1), string("AB"), "test 4: AB");
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
