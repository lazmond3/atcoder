#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
const bool debug = false;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define int long long
// clang-format off
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
// clang-format on

// https://leetcode.com/problems/longest-substring-without-repeating-characters/
class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    /* i文字目 -> j文字目 (j文字目は含まない？) で進めたとき、
       この区間の set について 文字を入れたり出したりしながら、
       最良の答えを記憶する。 */
    int answer = 1;
    int best_answer = answer;
    int i = 0;
    int j = 1;  // なので、 j は s.size() まで可能。
    set<char> used_char;
    used_char.insert(s[i]);

    // もし、 j が進めるなら進む。
    // j が s.size() を越してしまった場合は、 ...
    // s[j] が含まれてしまった場合は、 ...
    while (j <= s.size() && used_char.find(s[j]) == used_char.end()) {
      used_char.insert(s[j]);
      answer += 1;
      chmax(answer, best_answer);
      j += 1;
    }

    if (j == s.size()) {
      return answer;
    }
    if () }
};
/* 連続している部分を探す必要がある。 */
/* 尺取でいけないか？ */

void eq_assert(const int val, const int answer, const string &label) {
  if (val != answer) {
    cout << "Assertion failed: "
         << "(val = " << val << ", label = " << label << ", "
         << ", answer = " << answer << ") " << endl
         << flush;

    exit(1);
  }
}

signed main() {
  Solution a = Solution();
  eq_assert(a.lengthOfLongestSubstring("abcabcbb"), 3, "abcabcbb");
  eq_assert(a.lengthOfLongestSubstring("bbbbb"), 1, "bbbbb");
  eq_assert(a.lengthOfLongestSubstring("pwwkew"), 3, "pwwkew");
  eq_assert(a.lengthOfLongestSubstring(""), 0, "<empty>");
}