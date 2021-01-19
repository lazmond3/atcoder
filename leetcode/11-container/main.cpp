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

/*
    全探索はできる。
    高速化は、だいたいオーダーを改善しないといけないので、
*/
class Solution {
   public:
    int maxArea(const vector<int>& height) {
        int p1 = 0;
        int h1 = height[p1];
        int p2 = 1;
        int h2 = height[p2];
        int score = min(h1, h2) * abs(p1 - p2);
        for (int i = 2; i < height.size(); ++i) {
            int now_score_1 = min(height[i], h2) * abs(i - p2);
            int now_score_2 = min(h1, height[i]) * abs(p1 - i);

            if (now_score_1 > score && now_score_2 > score) {
                if (now_score_1 > now_score_2) {
                    p1 = i;
                    h1 = height[i];
                    if (debug) {
                        cout << "score1: " << now_score_1 << "[" << i << "]"
                             << " is larger than score: " << score << endl;
                    }
                    score = now_score_1;
                } else {
                    p2 = i;
                    h2 = height[i];
                    if (debug) {
                        cout << "score2: " << now_score_2 << "[" << i << "]"
                             << " is larger than score: " << score << endl;
                    }
                    score = now_score_2;
                }
                continue;
            }

            if (now_score_1 > score) {
                p1 = i;
                h1 = height[i];
                if (debug) {
                    cout << "score1: " << now_score_1 << "[" << i << "]"
                         << "is larger than score: " << score << endl;
                }
                score = now_score_1;
            }

            if (now_score_2 > score) {
                p2 = i;
                h2 = height[i];
                if (debug) {
                    cout << "score2: " << now_score_2 << "[" << i << "]"
                         << "is larger than score: " << score << endl;
                }
                score = now_score_2;
            }
        }
        return score;
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
        test_eq_assert(Solution().maxArea(vector<int>{1, 1}), (int)1,
                       "1,1 -> 1");
        test_eq_assert(Solution().maxArea(vector<int>{4, 3, 2, 1, 4}), (int)16,
                       "{4,3,2,1,4}), (int)16");
        test_eq_assert(Solution().maxArea(vector<int>{1, 2, 1}), (int)2,
                       "{1,2,1}), (int)2");
        test_eq_assert(
            Solution().maxArea(vector<int>{1, 8, 6, 2, 5, 4, 8, 3, 7}), (int)49,
            "{1,8,6,2,5,4,8,3,7}), (int)49");
        test_eq_assert(Solution().maxArea(vector<int>{
                           3,
                           2,
                           1,
                           3,
                       }),
                       (int)9, "{3,2,1,3,}), (int)9,");
        test_eq_assert(Solution().maxArea(vector<int>{1, 2, 4, 3}), (int)4,
                       "1,2,4,3 -> 4");
    }
}
