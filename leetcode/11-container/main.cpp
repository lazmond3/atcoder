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
// #define int long long
// clang-format off
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }
// clang-format on

#ifdef DEBUG
#include "main.hpp"
#else
class Solution {
   public:
    int maxArea(const vector<int> &height);
};
#endif

/*
    全探索はできる。
    高速化は、だいたいオーダーを改善しないといけない。

    まず、過去のやつを全部見られるか、調べる。
    そのとき 自分よりも高いやつで、一番遠いやつ <- これ大変、無理かも。
    もし全てが自分より高かったら、どうやって一番遠いものを探す？
    これがlong N では不可能な気がする


    一つみて、　 p1, p2, h1, h2 でスワップする戦略
    -> もうすでに使われなくなってしまったやつを使える可能性がある。
    [ 1,2,4,3 -> 4]] というケース
    1-4 , と 2-4 で 1-4 やるんだが、
    正解は 2-3 にならなきゃいけないので、更新しておく必要があった！
    // しかし最大ではないものだとしたら...?

    状態と知識について
    新しい要素を見て、確実にこれまでよりも更新したほうがいい、というのを作れるか？
    p1, p2, h1, h2 -> 完全に内包する場合

    同じスコアが来ちゃうと大変
    でも同じスコア来ることはあんまりないから、無視してもいいんじゃないか？
    0 が来てしまうと... ?

    => ヒントもらい、両端からしゃくとるかんじ。

*/
int max_inner(const vector<int> &height) {
    const int size = height.size();
    int i = 0;
    int j = size - 1;
    int max_i = i;
    int max_j = j;
    int max_score = min(height[i], height[j]) * (j - i);
    while (i < j) {
        // h[i] で now_hi を超える高さのやつに出会いたい
        int old_i = i;
        while (i < j && height[i] <= height[old_i]) {
            i += 1;
        }
        if (i < j) {
            // now_hi を超える高さのやつに出会ったら、
            // j を現在のスコアを超えるように
            int now_score = min(height[i], height[j]) * (j - i);
            // ❌ : now_scoreが高い可能性があるので更新。最後に詰まったのはここ。
            chmax(max_score, now_score);

            while (i < j) {
                now_score = min(height[i], height[j]) * (j - i);
                if (now_score > max_score) {
                    chmax(max_score, now_score);
                    max_i = i;
                    max_j = j;
                    break;
                }
                // clang-format off
                // ❌: もし、自分以上のheight j に到達したら、それも。..
                // ❌ ここは非直感的(つまりわかってない)だったが、jとiが同じところで止める。
                // ❌ 最大値 8,18,17,9,3 のケースで jを現象させるのをギリギリまでやめたい。
                // ❌
                // clang-format on
                // 17 で止めておけば、次8->18に来た時に利用できる
                if (height[j] >= height[i]) {
                    // ~~本当はここでとめちゃだめ！！~~
                    break;
                }
                j -= 1;
            }
        }
    }
    if (debug) {
        printf("[debug] last max_score: %d, max_i: %d, max_j: %d\n", max_score,
               max_i, max_j);
    }
    return max_score;
}
int Solution::maxArea(const vector<int> &height) {
    vector<int> reversed(height);
    reverse(ALL(reversed));
    // return max(max_inner(height), max_inner(reversed));
    int a = max_inner(height);
    // return a;
    int b = max_inner(reversed);
    return max(a, b);
}
