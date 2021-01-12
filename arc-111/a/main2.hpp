#ifndef MAIN2_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
#include <cstring>
using namespace std;
bool debug = false;

// const bool debug = true;
const bool seg_debug = false;
// const bool debug = false;
const bool detail_debug = false;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define int long long

void show_vector(/*const ref in*/ const vector<int> &vec, const string &label);
void show_variable(const int val, const string &label);
void eq_assert(const int val, const int answer, const string &label);
void assert_vec(/*const ref in*/ const vector<int> &target, /*const ref in*/ const vector<int> &answer);
void generate_series(const int M,
                     /*ref out*/ vector<int> &shou,
                     /*ref out*/ vector<int> &repeated);
// repeated repeated_with_amari を M で割ったあまりを計算する。
int calc_amari_for_target_vec(const int M,
                              /*const ref in*/ const vector<int> &target_vec); // repeated とは限られず、先頭にあまりが付加した形になる。
int generate_amari_series_for_repeated_set(const int M,
                                           const int initial_amari_for_shou,
                                           /*ref out*/ vector<int> &amari_series_for_repeated_set, // 名前が悪い気がする。 repeated_amari_repeated とか
                                           /*const ref in*/ const vector<int> &repeated);
int service(const int N, const int M);
#endif