import sys,os
import random
debug = os.getenv("DEBUG")

if len(sys.argv) != 4:
    print ("python3 main.py m=max_range, i=test_count p=probability of o")
    exit(0)
m = int(sys.argv[1])
p = float(sys.argv[3])

# oxooooxoxxx という列を作成する。
def make_lst(m):
    a = []
    for i in range(1,m+1):
        if random.random() < p:
            a.append("o")
        else:
            a.append("x")
    return a

def main():
    # m = int(sys.argv[1])
    # 直接確認するので遅いが、確実な関数を作る。
    
    if debug:
        print(f"param: m : {m} max test count: {sys.argv[2]}")
    for i in range(1, int(sys.argv[2])):
        if debug:
            print( "=== i : ", i, " ====== ")
        fdir = f"test-{m}"
        ddir = f"debug-{m}"
        if not debug and not os.path.exists(fdir):
            os.mkdir(fdir)
        if not debug and not os.path.exists(ddir):
            os.mkdir(ddir)

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
        with open(ddir + f"/sample-{i:04}.debug", "w") as fin:
            fin.write(f"{a}\n")

        if not debug:
            with open(fdir + f"/sample-{i:04}.out", "w") as fout:            
                fout.write(f"{calc_mid(a)}\n")
        else:
            with open("/dev/null" , "w") as fout:
                fout.write(f"{calc_mid(a)}\n")
                

if __name__ == "__main__":
    main()