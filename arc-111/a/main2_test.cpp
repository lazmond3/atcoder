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

void test_generate_series()
{
    // 88
    vector<int> amari_vector_88;
    vector<int> shou_88;
    generate_series(88, /*ref out*/ shou_88, /*ref out*/ amari_vector_88);
    show_vector(shou_88, "shou_88");
    show_vector(amari_vector_88, "amari_vector_88");
    assert_vec(
        shou_88,
        {0, 1, 1, 3, 6});
    assert_vec(
        amari_vector_88,
        {3, 6});

    // 23
    vector<int> amari_vector_23;
    vector<int> shou_23;
    generate_series(23, /*ref out*/ shou_23, /*ref out*/ amari_vector_23);
    show_vector(shou_23, "shou_23");
    show_vector(amari_vector_23, "amari_vector_23");
    assert_vec(
        shou_23,
        {0, 4, 3, 4, 7, 8, 2, 6, 0, 8, 6, 9, 5, 6, 5, 2, 1, 7, 3, 9, 1, 3});
    assert_vec(
        amari_vector_23,
        {0, 4, 3, 4, 7, 8, 2, 6, 0, 8, 6, 9, 5, 6, 5, 2, 1, 7, 3, 9, 1, 3});

    // // 17
    vector<int> amari_vector_17;
    vector<int> shou_17;
    generate_series(17, /*ref out*/ shou_17, /*ref out*/ amari_vector_17);
    show_vector(shou_17, "shou_17");
    show_vector(amari_vector_17, "amari_vector_17");
    assert_vec(
        shou_17,
        {0, 5, 8, 8, 2, 3, 5, 2, 9, 4, 1, 1, 7, 6, 4, 7});
    assert_vec(
        amari_vector_17,
        {0, 5, 8, 8, 2, 3, 5, 2, 9, 4, 1, 1, 7, 6, 4, 7});
}

signed main()
{
    const char *DEBUG_p = std::getenv("DEBUG");
    debug = DEBUG_p != NULL && strnlen(DEBUG_p, 1) > 0;
    test_shou_and_repeated();
    test_repeated_and_amari_cycle();
    test_generate_series();
}