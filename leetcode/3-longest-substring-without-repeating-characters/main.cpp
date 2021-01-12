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

// https://leetcode.com/problems/longest-substring-without-repeating-characters/
class Solution {
   public:
    /*
     ❌ 反省点
     - find() != end() を間違えた。　これ間違えやすすぎる。

     課題としては、最初 j が j.size() まで可能と思っていたが、
     j.size()
              j
     abcdefgh .
     こうなった時点で終了する番兵的な存在にすべきだった。
     while (j < s.size())

    */
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

        if (s.length() == 0) return 0;
        // 最初は このループに入れる。
        // ループ内部では、 i, j の増加がありうる。
        while (true) {
            if (debug) {
                cout << "now : i : " << i << ", j : " << j << endl;
                cout << "\t -- " << s << endl;
                cout << "\t score: " << now_score << endl;
                cout << "\t maxscore: " << best_answer << endl;
            }
            // もし、 j が進めるなら進む。
            // j が s.size() を越してしまった場合は、 ...
            // s[j] が含まれてしまった場合は、 ...
            while (j < s.size() && used_char.find(s[j]) == used_char.end()) {
                // ❌ この時の j は size と同じ可能性がある。
                used_char.insert(s[j]);
                now_score += 1;  // jを増加させても条件を満たしているので、
                                 // スコアを増加できる。
                chmax(best_answer, now_score);
                j += 1;
            }

            // j がすぎてしまった場合, もうやる必要はない
            // (i を動かさなくてもよかったため。)
            if (j == s.size()) {
                return best_answer;
            }

            // もし、 s[j] がすでに使うところに含まれてしまっているならば...
            if (used_char.find(s[j]) != used_char.end()) {
                // 上記 の条件がなくなるまで、i を進めてみる。
                // ⚡️: i を進めていい条件は j より小さいこと
                // | 逆に、どういう時に j を越してしまう？
                while (i < s.size() && i < j &&
                       // 見つかる範囲内で
                       used_char.find(s[j]) != used_char.end()) {
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
                    continue;
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
    const char *DEBUG_p = std::getenv("DEBUG");
    debug = DEBUG_p != NULL && strnlen(DEBUG_p, 1) > 0;
    Solution a = Solution();
    eq_assert(a.lengthOfLongestSubstring("abcabcbb"), 3, "abcabcbb");
    eq_assert(a.lengthOfLongestSubstring("bbbbb"), 1, "bbbbb");
    eq_assert(a.lengthOfLongestSubstring("pwwkew"), 3, "pwwkew");
    eq_assert(a.lengthOfLongestSubstring(""), 0, "<empty>");
}