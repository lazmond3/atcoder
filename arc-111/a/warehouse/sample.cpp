#include <iostream>
#include <cstdlib>
using namespace std;
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)

long long pow(long long a, long long p)
{
    if (p == 0)
        return 1;
    return a * pow(a, p - 1);
}

/*
- 14285714285714
のように、10^N に対して、どうやって文字列を作るか
string の繰り返し。
しかし long long の範囲で繰り返しが出てるわけではない
*/
/*
    まず、 10^n / M (int) を計算する。
    10^N /M の結果というのは、 1/M の結果を引っ張り上げたもの
    10^N /M = 

            100 <- 合うまで桁を合わせる
       ________________
     M |  10000000
            M
       ______________
            700

        100 - M*h = P (10^n を M で割ったあまり)
        10^n * [1-9] を M で割ったあまりというのが重要そう
          M より大きいか等しい 1 \times 10^n の最小の nに対して、ここをスタートにして、はじまる

        10^n を M で割ったあまりによって、
        P * 10^n で次のあまりがはじまる。
        1*10^n1    % M = P1
        P1 * 10^n2 % M = P2
        P2 * 10^n3 % M = P3
        ...
        Pn * 10^nn % M = Pn

        で、 n <= M の範囲で、繰り返す。
        たとえば、　10 / 3 = 3.3333
        20 / 6 = 3.3333
        10 / 6 = 1.6666
        という風に、 6いかに1,2,3,4,5 があるが、これは使われない。
        10 % 6 = 4 (P1)
        P1*10 % 6 = 4 (P2)
        Pn in [4] のみで、 Pn = 1,2,3,5 になることはない。
        このように、M未満の全ての数がすべてのあまりが出るわけではない。

        繰り返すのは P1 == Pn となるタイミング ? 
        
             1.6
           ____________
        6 |  10
              6
           ___________
              40 
              36
           ___________
               4
    　　 M < 10000 なので、どのようにあまりが 接続しているか（巡回群的に) は事前に、高速に計算できる。
*/
/*
    P1P2 に対して、
    たとえば M = 13を考える。
    7.692307692307692
    なので、 769230 が　無限にループしている。
    100 % 13 =  7...  9 
    90  % 13 =  6    12  
    120 % 13 =  9     3  
    30  % 13 =  2     4  
    40  % 13 =  3     1  // たぶん、あまりだけじゃなくて商の情報も必要
    10  % 13 =  0    10 
    // ここでループ！ (同じ数が割られる数にきている。)
    100 % 13 =  7...  9

    商の情報を利用して、769230 を計算できる。  
    ちなみに、
    769230  % 13 =    7
    7       % 13 =    7  
    76      % 13 =   11
    769     % 13 =    2 (119 % 13 と同じ)
    7692    % 13 =    2
    769230  % 13 =    7
    7692307 % 13 =   12
    12|6    % 13 =    9
    9 |9    % 13 =    8
    8 |2    % 13 =    4
    4 |3    % 13 =    4
    4 |0    % 13 =    1
    1 |7    % 13 =    4
    4 |6    % 13 =    7

    769230         % 13 =                  7
    769230769230   % 13 =                  1
    769230\times 3 % 13 =   1769230 % 13 = 8
    8|769230        % 13 =                 2
    2|769230        % 13 =                 9
    9|769230        % 13 =                 3
    3|769230        % 13 =                10
   10|769230        % 13 =                 4
    4|769230        % 13 =                11
   11|769230        % 13 =                 6
    6|769230        % 13 =                 0
    769230 の塊が、 11 個回転するとあまりがゼロになる。ので、この数で割り算できる。

    // 1回数あたり余りがいくつ動くか、を計算できるのか？
*/
/*
        _ これはどうやって取得する？
        abcdefg.... というものが Nを指定する と得られる。これを、long long に おさまらない ようにstringで得られたとしても、
        {abcdefg.}        % M = 0 
                {.......} % M != 0 (maybe)
        となる場所があるはずなので、 上部を無視できる区間が存在する。 (769230 が 11個で打ち消せる。)
        
*/

/* ちょっと難しいところ
✅  STEP 1: まず、1段階目に、 10^N が計算されると、1周りどういうシーケンスが生成されるかを計算する必要がある。
        最初の方は、ループしない可能性がある。 
        例: 82 /  6  = 13.66666666 の 13 はループしない。
        例: 10 /  6 =   1.66666666 の  1 はループしない。
        -> 10^N を割るときには
        -> では、実際に 10^N 
    STEP 2: そのシーケンスは完全にピッタリ計算されるわけではない。
        6個目の 769230 の 76923 で止まる、ということがある。
*/

/*
10^N / M 

10**1, M = 9997 and : 0 di: 0
10**2, M = 9997 and : 0 di: 0
10**3, M = 9997 and : 0 di: 0
10**4, M = 9997 and : 1 di: 1
10**5, M = 9997 and : 10 di: 10
10**6, M = 9997 and : 100 di: 100
10**7, M = 9997 and : 1000 di: 1000
10**8, M = 9997 and : 6 di: 10003
10**9, M = 9997 and : 60 di: 100030
10**10, M = 9997 and : 600 di: 1000300
10**11, M = 9997 and : 6000 di: 10003000
10**12, M = 9997 and : 27 di: 100030009
10**13, M = 9997 and : 270 di: 1000300090
10**14, M = 9997 and : 2700 di: 10003000900
10**15, M = 9997 and : 7008 di: 100030009002
10**16, M = 9997 and : 108 di: 1000300090027
10**17, M = 9997 and : 1080 di: 10003000900270
10**18, M = 9997 and : 803 di: 100030009002700
10**19, M = 9997 and : 8038 di: 1000300090027008
10**20, M = 9997 and : 406 di: 10003000900270082
10**21, M = 9997 and : 4056 di: 100030009002700816
10**22, M = 9997 and : 540 di: 1000300090027008128

これだと、そもそもlong long のところでループ検知できないなあ
*/
int main(int argc, char *argv[])
{
    long long N, M;
    // std::cin >> N >> M;
    // std::cin >> N;
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    // M = 3;
    REP(i, N)
    {
        long long di = (pow(10, i) / M);
        cout << "10**" << i << ", M = " << M << " ";
        cout << "and : " << di % M << " ";
        cout << "di: " << di << endl;
        // cout << "ans: " << di % M << endl;
    }

    // std::cout << larger(a, b) << std::endl;
}