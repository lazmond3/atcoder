#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;
const bool debug = true;
const bool seg_debug = false;
const bool detail_debug = false;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define ALL(x) x.begin(), x.end()
#define int long long
class Solution
{
public:
    long long reverse(long long x)
    {
        std::vector<int> stock;
        bool flag = x < 0;
        if (flag)
        {
            x *= -1;
        }

        while (x != 0)
        {
            stock.push_back(x % 10);
            x /= 10;
        }
        long long ans = 0;
        int i = 0;
        for (auto v : stock)
        {
            ans += v;
            i += 1;
            if (i != stock.size())
            {
                if (!flag && (((long long)ans * 10) > ((1L << 31) - 1)))
                    return 0;
                else if (flag && (((long long)ans * 10 * -1) < ((1L << 31) * -1)))
                    return 0;
                ans *= 10;
            }
        }

        if (flag)
            ans *= -1;
        return ans;
    }
};

signed main()
{
    Solution a = Solution();
    cout << (1L << 31) << endl;
    cout << (1L << 31) << endl;
    cout << a.reverse(123) << endl;
    // cout << a.reverse(1534236469) << endl;
    // assert(a.reverse(1534236469) == 9646324351);
    assert(a.reverse(-123) == -321);
    cout << a.reverse(-2147483412) << endl;
    assert(a.reverse(-2147483412) == -2143847412);
    assert(a.reverse(1463847412) == 2147483641);
}