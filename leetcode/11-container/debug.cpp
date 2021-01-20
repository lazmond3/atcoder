#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
constexpr double eps = 1e-11;
extern bool debug;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
// #define int long long
// clang-format off
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
// clang-format on

#include "main.hpp"
#include "debug.hpp"

// #ifdef TEST
// signed main2() {
// #else
signed main() {
    // #endif
    const char *DEBUG_p = std::getenv("DEBUG");
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
        test_eq_assert(Solution().maxArea(vector<int>{2, 3, 4, 5, 18, 17, 6}),
                       (int)17, ">{2,3,4,5,18,17,6}), (int)17");
        test_eq_assert(
            Solution().maxArea(vector<int>{1, 8, 100, 2, 100, 4, 8, 3, 7}),
            (int)200, "{1,8,100,2,100,4,8,3,7}),(int)200");
        test_eq_assert(
            Solution().maxArea(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}),
            (int)25, "{10,9,8,7,6,5,4,3,2,1}),(int)25");
    }
}
