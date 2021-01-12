import sys,os
debug = os.getenv("DEBUG")

# ❌ 4 でわるときの答えが間違えている
# 例: 3 4 => int(10**3 / 4) % 4 正解は250 % 4 == 2　だけど 1 と出てしまう
# 例: 1 4 でも、 0.2 => 2 / 4 == 0 だから、 0を4で割ったあまりは0になるはずだが、いまは2が出てしまっている。
# n が小さい領域で失敗している気がする。

# リスト用の計算があったら便利なのかも、と思ったら、これだ。
def lst_division_for_calc_amari(f, lst, m):
    i = 0
    amari = lst[i]
    i += 1

    # if (len(lst) < 10, )

    seen_amari = set()
    # out
    shou = []
    result_amari_lst = []
    if debug:
        print(f"first amari: {amari}")
    while i < len(lst):
        # seen 
        # if amari in seen_amari: break

        div = amari // m
        shou.append(div)
        result_amari_lst.append(amari % m)
        old_amari = amari
        amari = amari % m

        amari = amari * 10 + lst[i]
        i += 1

        # add seen
        # seen_amari.add(old_amari)
    
    div = amari // m
    shou.append(div)
    result_amari_lst.append(amari % m)
    old_amari = amari
    amari = amari % m
    if debug:
        print(f"shou: {shou}, amarilst: {result_amari_lst} amari: {amari}")
        print(f"amari: {amari}")
    f.write(str(amari) + "\n")

# この関数は、 10**N / M をした結果の整数列を生成する。
def make_str_lst(m, count):
    str_lst = []
    amari = 1
    count += 1

    # while amari != 0 and count != 0:
    while count != 0:
        if amari >= m:
            div =amari //m
            if debug:
                print(div, end="")
            str_lst.append(div)
            amari = amari % m
        else:
            if debug:
                print(0, end="")
            str_lst.append(0)
            pass
        amari *= 10
        count -= 1
    if debug:
        print("strlst: ", str_lst)
    return str_lst

def main():
    m = int(sys.argv[1])
    # 直接確認するので遅いが、確実な関数を作る。
    # 割り算の確認
    
    for i in range(int(sys.argv[3]), int(sys.argv[4])):
        if debug:
            print( "=== i : ", i, " ====== ")
        if not debug and not os.path.exists(f"test-{sys.argv[2]}-{m}"):
            os.mkdir(f"test-{sys.argv[2]}-{m}")

        if not debug:
            with open(f"test-{sys.argv[2]}-{m}/sample-{i:04}.in", "w") as fin:
                fin.write(f"{i} {m}\n")
        str_lst = make_str_lst(m , i)
        if debug:
            print(f"str lst is ... {str_lst}")

        if not debug:
            with open(f"test-{sys.argv[2]}-{m}/sample-{i:04}.out", "w") as fout:            
                lst_division_for_calc_amari(fout, str_lst, m)
        else:
            with open("/dev/null" , "w") as fout2:
                lst_division_for_calc_amari(fout2, str_lst, m)

if __name__ == "__main__":
    if len(sys.argv) < 5:
        print("python3 make_test.py <m> directory_name, from, to")
        exit(0)

    main()