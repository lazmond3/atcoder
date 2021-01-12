#include "main2.hpp"

void test_shou_and_repeated()
{
    vector<int> shou_4;
    vector<int> repeated_4;
    generate_series(4, shou_4, repeated_4);
    show_vector(shou_4, "shou_4");         // 2 5 0
    show_vector(repeated_4, "repeated_4"); // 0

    vector<int> shou_13;
    vector<int> repeated_13;
    generate_series(13, shou_13, repeated_13);
    show_vector(shou_13, "shou_13");         // 0,7,6,9,2,3,
    show_vector(repeated_13, "repeated_13"); // 0,7,6,9,2,3,

    vector<int> shou_2;
    vector<int> repeated_2;
    generate_series(2, shou_2, repeated_2);
    show_vector(shou_2, "shou_2");         // 5 0
    show_vector(repeated_2, "repeated_2"); // 0
}

signed main()
{
    const char *DEBUG_p = std::getenv("DEBUG");
    debug = DEBUG_p != NULL && strnlen(DEBUG_p, 1) > 0;
    test_shou_and_repeated();
}