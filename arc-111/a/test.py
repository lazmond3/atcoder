from make_test import lst_division_for_calc_amari, make_str_lst


m = 10
for i in range(1, 10):
    str_lst = make_str_lst(m , i)
    with open("/dev/null" , "w") as fout2:
        lst_division_for_calc_amari(fout2, str_lst, m)

# この関数は、 10**N / M をした結果の整数列を生成する。
def test_make_str_lst():
    if debug:
        print("hey: ", make_str_lst(88, 10))
    assert(make_str_lst(1, 10) == [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
    assert(make_str_lst(13, 10) == [0, 0, 7, 6, 9, 2, 3, 0, 7, 6, 9])
    assert(make_str_lst(83, 10) == [0, 0, 1, 1, 3, 6, 3, 6, 3, 6, 3])

if __name__ == "__main__":
    test_make_str_lst()