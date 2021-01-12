import sys
debug = False

# リスト用の計算があったら便利なのかも、と思ったら、これだ。
def lst_division_for_calc_amari(lst, m):
    i = 0
    amari = lst[i]
    i += 1

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
        

def main():
    m = int(sys.argv[1])
    count = int(sys.argv[2])+1
    amari = 1


    # 直接確認するので遅いが、確実な関数を作る。

    # 割り算の確認
    # count = 1000
    str_lst = []
    while amari != 0 and count != 0:
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
        print(f"str lst: {str_lst}")
    lst_division_for_calc_amari(str_lst, m)


    # target_str = str(1/m)[2:][:n]
    # target = int(target_str)

    # print(target)
    # print("answer: " , target % m)

if __name__ == "__main__":
    main()