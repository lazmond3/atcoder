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
#define RED "\033[1;31m"
#define BLU "\033[34m"
#define CLR "\033[0m"
// clang-format on
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

string check_even(const string& s) {
    int max_score = 0;
    int max_i = 0;
    int max_j = 0;

    // 01234....789
    //  left_i は 0 から 8まで動ける
    // right_j は 1 から 9まで動ける
    for (int i = 0; i < (s.size() - 1); ++i) {
        if (debug) {
            cout << "[check_even] i : " << i << ", max_score = " << max_score
                 << endl;
        }
        int now_score = 2;
        int left_i = i;
        int right = i + 1;
        while (0 <= left_i && right < s.size() && s[left_i] == s[right]) {
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
    // return max_st(max_score, max_i, max_j, s.substr(max_i, max_j - max_i +
    // 1));
    return s.substr(max_i, max_j - max_i + 1);
}

string check_odd(const string& s) {
    int max_score = 0;
    int max_i = 0;
    int max_j = 0;

    for (int i = 1; i < (s.size() - 1); ++i) {
        if (debug) {
            cout << "[check_odd] i : " << i << ", max_score = " << max_score
                 << endl;
        }
        // リセットされた。これから始まる
        int now_score = 3;  // 最初のこれが通ればスコアは 3　になる。
        int left = i - 1;
        int right = i + 1;
        while (0 <= left && right < s.size() && s[left] == s[right]) {
            // 達成したらスコアをあげる。
            if (now_score > max_score) {
                if (debug) {
                    cout << "[check_odd] left: " << left << ", right: " << right
                         << ", score up!" << endl;
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
    return s.substr(max_i, max_j - max_i + 1);
}

// https://leetcode.com/problems/longest-palindromic-substring/
class Solution {
   public:
    string longestPalindrome(string s) {
        if (s.size() == 0) return "";
        if (s.size() == 1) return s;

        // 初期のmax_string を用意する。0文字目から初めて1文字取得
        string max_string = s.substr(0, 1);

        // i
        // abbcccddd
        //   jij
        // abbcccddd
        //   jiij
        // abbcccddd
        // このように歩んでいき、左右に分割していく。
        // 中央パターンと 偶数パターンがある。
        string odd_string = check_odd(s);
        string eve_string = check_even(s);
        if (odd_string.size() > max_string.size()) {
            max_string = odd_string;
        } else
            max_string = eve_string;

        return max_string;
    }
};

template <class T>
void test_eq_assert(const T val, const T answer, const string& label) {
    if (debug && val == answer) {
        cout << "--------- [[ " << label << "]] ---------" << endl;
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
    // ❌ 使う部分の範囲だけっぽい x から n文字目だった。 .substr(x, n)
    test_eq_assert<string>(string("abcd").substr(1, 3), "bcd",
                           "abcd substr 1,3");
    // ❌ 345 ではない。
    test_eq_assert<string>(string("0123456789").substr(3, 5), "34567",
                           "0-9 の substr 3-5");
    // ❌ substr(0,2)だと ba になってしまう
    test_eq_assert<string>(string("babad").substr(0, 3), "bab",
                           "これおちる？bab");  // x から p 文字

    test_eq_assert<string>(Solution().longestPalindrome("babad"), "bab",
                           "bab or aba");
    test_eq_assert<string>(Solution().longestPalindrome("cbbd"), "bb", "cbbd");

    test_eq_assert<string>(check_odd("testse"), "estse",
                           "check odd のテスト1 testste");
    test_eq_assert<string>(check_odd("te2stse"), "sts", "check odd のテスト2");

    test_eq_assert<string>(check_even("testse"), "t",
                           "check even のテスト1 testste");
    test_eq_assert<string>(check_even("teetse"), "teet",
                           "check even のテスト2 teet");
}