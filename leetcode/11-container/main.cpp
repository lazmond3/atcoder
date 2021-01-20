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
#endif

/*
    全探索はできる。
    高速化は、だいたいオーダーを改善しないといけない。

    まず、過去のやつを全部見られるか、調べる。
    そのとき 自分よりも高いやつで、一番遠いやつ <- これ大変、無理かも。
    もし全てが自分より高かったら、どうやって一番遠いものを探す？これがlong N
   では不可能な気がする

    2つめに、パターンを
*/
int Solution::maxArea(const vector<int> &height) {
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
