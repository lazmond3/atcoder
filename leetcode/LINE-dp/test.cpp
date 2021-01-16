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
#define int long long
// clang-format off
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
#define RED "\033[1;31m"
#define GRE "\033[1;32m"
#define BLU "\033[34m"
#define CLR "\033[0m"
#include "main.hpp"


signed main() {
    const char* DEBUG_p = std::getenv("DEBUG");
    debug = DEBUG_p != NULL && strnlen(DEBUG_p, 1) > 0;

    int n, m;

    cin >> n >> m;
    vector<int> a(n), b(m);
    REP(i, n) {
        int p;
        cin >> p;
        a[i] = p;
    }
    REP(i, m) {
        int p;
        cin >> p;
        b[i] = p;
    }

    cout << Solution().findMedianSortedArrays(a, b) << endl;
}