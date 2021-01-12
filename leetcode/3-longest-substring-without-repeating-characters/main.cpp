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
    int now_score = 1;
    int best_answer = now_score;
    int i = 0;
    int j = 1;  // なので、 j は s.size() まで可能。
    set<char> used_char;
    used_char.insert(s[i]);

    // 最初は このループに入れる。
    // ループ内部では、 i, j の増加がありうる。
    while (true) {
      // もし、 j が進めるなら進む。
      // j が s.size() を越してしまった場合は、 ...
      // s[j] が含まれてしまった場合は、 ...
      while (j <= s.size() && used_char.find(s[j]) == used_char.end()) {
        used_char.insert(s[j]);
        now_score += 1;
        chmax(now_score, best_answer);
        j += 1;
      }
      // j がすぎてしまった場合, もうやる必要はない
      // (i を動かさなくてもよかったため。)
      if (j > s.size()) {
        return best_answer;
      }
      if (used_char.find(s[j]) == used_char.end()) {
        // 上記 の条件がなくなるまで、i を進めてみる。
        // ⚡️: i を進めていい条件は j より小さいこと
        // | 逆に、どういう時に j を越してしまう？
        while (i < s.size() && used_char.find(s[j]) == used_char.end()) {
          now_score -= 1;

          // s[i] を 使った set から削除する。
          assert("s[i] は used なはず。" &&
                 used_char.find(s[i]) != used_char.end());
          used_char.erase(used_char.find(s[i]));
          i += 1;
        }
        if (i == s.size()) {
          return best_answer;
        }
        if (used_char.find(s[j]) != used_char.end()) {
          // もし、 j が入らなくなったら、次へ進んでもよい。
          // continue したい。
        }
      }
    }
  }
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