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
   public:
    string longestPalindrome(string s) { return ""; }
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
    eq_assert(string("abcd").substr(1, 3), string("bcd"), "abcd substr 1, 3");
}