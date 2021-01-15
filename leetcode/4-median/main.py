import sys,os
import random
debug = os.getenv("DEBUG")

if len(sys.argv) != 3:
    print ("python3 main.py m=max_range, i=test_count")
    exit(0)
m = int(sys.argv[1])

def make_lst(m):
    a,b,c = [],[],[]
    for i in range(1,m):
        if random.random() < 0.3: continue
        elif random.random() < 0.7:
            a.append(i)
            b.append(i)
        else:
            a.append(i)
            c.append(i)
    return (a,b,c)

def calc_mid(lst):
    gth = len(lst)
    if len(lst) % 2 == 0:
         # 1,2,3,4,5,6,7,8
         # 0,1,2,3,4,5,6,7
         # 要素数8のとき、[3,4]の平均がほいい
         i=gth//2-1
         j=i+1
         return (lst[i] + lst[j])/2
    else:
        return lst[gth//2]

        

def main():
    # m = int(sys.argv[1])
    # 直接確認するので遅いが、確実な関数を作る。
    
    if debug:
        print(f"param: m : {m} max test count: {sys.argv[2]}")
    for i in range(1, int(sys.argv[2])):
        if debug:
            print( "=== i : ", i, " ====== ")
        fdir = f"test-{m}"
        if not debug and not os.path.exists(fdir):
            os.mkdir(fdir)

        a,b,c = make_lst(m)
        if debug:
            print(f"a: {a}\nb:{b}\nc:{c}")

        if not debug:
            with open(fdir + f"/sample-{i:04}.in", "w") as fin:
                fin.write(f"{len(b)} {len(c)}\n")
                for bb in b:
                    fin.write(f"{bb}\n")
                for cc in c:
                    fin.write(f"{cc}\n")
        else:
            with open("/dev/null" , "w") as fin:
                fin.write(f"{len(b)} {len(c)}\n")
                for bb in b:
                    fin.write(f"{bb}\n")
                for cc in c:
                    fin.write(f"{cc}\n")
        # with open(fdir + f"/sample-{i:04}.debug", "w") as fin:
        #     fin.write(f"{a}\n")

        if not debug:
            with open(fdir + f"/sample-{i:04}.out", "w") as fout:            
                fout.write(f"{calc_mid(a)}\n")
        else:
            with open("/dev/null" , "w") as fout:
                fout.write(f"{calc_mid(a)}\n")
                

if __name__ == "__main__":
    main()