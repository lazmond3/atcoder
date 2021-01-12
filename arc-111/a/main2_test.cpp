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

void test_repeated_and_amari_cycle()
{
    // 88
    assert(calc_amari_for_target_vec(88, vector<int>{3, 6}) == 36);
    assert(calc_amari_for_target_vec(88, vector<int>{3, 6, 3, 6}) == 28);
    assert(calc_amari_for_target_vec(88, vector<int>{2, 8, 3, 6}) == 20);
    assert(calc_amari_for_target_vec(88, vector<int>{2, 0, 3, 6}) == 12);
    assert(calc_amari_for_target_vec(88, vector<int>{4, 3, 6}) == 84);
    assert(calc_amari_for_target_vec(88, num_to_vector(8436)) == 76);
    assert(calc_amari_for_target_vec(88, num_to_vector(7636)) == 68);
    assert(calc_amari_for_target_vec(88, num_to_vector(6836)) == 60);
}

signed main()
{
    const char *DEBUG_p = std::getenv("DEBUG");
    debug = DEBUG_p != NULL && strnlen(DEBUG_p, 1) > 0;
    test_shou_and_repeated();
    test_repeated_and_amari_cycle();
}