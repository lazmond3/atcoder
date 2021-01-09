#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)

/*
    課題点
      substr 以外の文字列操作
      set のコピー
      set の使い方
      string が遅いのか？ TLE が取れない
*/
int abs(int a)
{
    if (a > 0)
        return a;
    else
        return -a;
}

int main()
{
    int N;
    std::cin >> N;
    std::set<string> string_set;
    std::set<string> pls_string_set;
    string st;
    REP(i, N)
    {
        std::cin >> st;
        bool is_plus = false;
        if (st[0] == '!')
        {
            is_plus = true;
            st = st.substr(1);
            pls_string_set.insert(st);
        }
        else
        {
            string_set.insert(st);
        }

        auto &target = is_plus ? string_set : pls_string_set;
        if (target.find(st) != target.end())
        {
            cout << st << endl;
            return 0;
        }
    }
    cout << "satisfiable" << endl;
}