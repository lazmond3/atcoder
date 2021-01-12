from make_test import lst_division_for_calc_amari, make_str_lst


m = 10
for i in range(1, 10):
    str_lst = make_str_lst(m , i)
    with open("/dev/null" , "w") as fout2:
        lst_division_for_calc_amari(fout2, str_lst, m)