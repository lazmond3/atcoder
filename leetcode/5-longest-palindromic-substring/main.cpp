#include <algorithm>
#include <cassert>
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
// clang-format on

// https://leetcode.com/problems/longest-palindromic-substring/
class Solution {
   private:
    int max_i = 0;
    int max_j = 0;  // jも含めることにしよう。
    int max_score = 1;
    string this_string;

    void check_odd() {
        for (int i = 1; i < (this_string.size() - 1); ++i) {
            if (debug) {
                cout << "[check_odd] i : " << i << ", max_score = " << max_score
                     << endl;
            }
            // リセットされた。これから始まる
            int now_score = 3;  // 最初のこれが通ればスコアは 3　になる。
            int left = i - 1;
            int right = i + 1;
            while (0 <= left && right < this_string.size() &&
                   this_string[left] == this_string[right]) {
                // 達成したらスコアをあげる。
                if (now_score > max_score) {
                    if (debug) {
                        cout << "[check_odd] left: " << left
                             << ", right: " << right << ", score up!" << endl;
                    }
                    max_i = left;
                    max_j = right;
                    max_score = now_score;
                }
                // 次の left, right を作る
                left -= 1;
                right += 1;
                now_score += 2;
            }
        }
    }
    void check_even() {
        // 01234....789
        //  left_i は 0 から 8まで動ける
        // right_j は 1 から 9まで動ける
        for (int i = 0; i < (this_string.size() - 1); ++i) {
            if (debug) {
                cout << "[check_even] i : " << i
                     << ", max_score = " << max_score << endl;
            }
            int now_score = 2;
            int left_i = i;
            int right = i + 1;
            while (0 <= left_i && right < this_string.size() &&
                   this_string[left_i] == this_string[right]) {
                if (now_score > max_score) {
                    if (debug) {
                        cout << "[check_even] left: " << left_i
                             << ", right: " << right << ", score up!" << endl;
                    }
                    max_i = left_i;
                    max_j = right;
                    max_score = now_score;
                }
                left_i -= 1;
                right += 1;
                now_score += 2;
            }
        }
    }

   public:
    string longestPalindrome(string s) {
        if (s.size() == 0) return "";
        if (s.size() == 1) return s;

        this_string = s;

        if (debug) cout << "this_string: " << s << endl;
        check_odd();
        if (debug) {
            cout << "----- check odd -------" << endl;
            cout << "max_i: " << max_i << endl;
            cout << "max_j: " << max_j << ", max score: " << max_score << endl;
        }
        check_even();
        if (debug) {
            cout << "----- check even -------" << endl;
            cout << "max_i: " << max_i << endl;
            cout << "max_j: " << max_j << ", max score: " << max_score << endl;
        }

        // i
        // abbcccddd
        //   jij
        // abbcccddd
        //   jiij
        // abbcccddd
        // このように歩んでいき、左右に分割していく。
        // 中央パターンと 偶数パターンがある。
        return s.substr(max_i, max_j - max_i + 1);
    }
};

template <class T>
void eq_assert(const T val, const T answer, const string &label) {
    if (val != answer) {
        cout << "Assertion failed: "
             << "(val = " << val << ", label = " << label << ", "
             << "answer = " << answer << ") " << endl
             << flush;

        exit(1);
    }
}

signed main() {
    const char *DEBUG_p = std::getenv("DEBUG");
    debug = DEBUG_p != NULL && strnlen(DEBUG_p, 1) > 0;
    Solution a = Solution();
    // 使う部分の範囲だけっぽい
    eq_assert(string("abcd").substr(1, 3), string("bcd"), "abcd substr 1,3");
    eq_assert(string("babad").substr(0, 2 + 1), string("bab"),
              "これおちる？bab");  // x から p 文字

    eq_assert<string>(Solution().longestPalindrome("babad"), "bab",
                      "bab or aba");
    if (debug) cout << "\t\t------------------" << endl;
    eq_assert<string>(Solution().longestPalindrome("cbbd"), "bb", "cbbd");
}