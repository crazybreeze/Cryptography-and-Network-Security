#include<NTL/ZZ.h>
#include<iostream>
using namespace std;
using namespace NTL;
#define MAX 1024
#define MIN 512
int main()
{ 
  ZZ p, q, n, N, d, e, C, M;
  e = 65537;
  //生成两个随机数p和q,长度均为512~1024位
  do {
    do {
      RandomBits(p, MAX);
    }while(NumBits(p) < MIN ||ProbPrime(p) == 0);
    do {
      RandomBits(q, MAX);
    }while(NumBits(q) < MIN ||ProbPrime(q) == 0);
    //计算n = p * q
    mul(n, p, q);
    //计算N = (p-1)*(q-1)
    mul(N, p-1, q-1);
    ZZ s, t;
    //s = N * t + e * d;计算私钥d
    XGCD(s, t, d, N, e);
 }while(GCD(N, e) != 1 || d < 0);
  cout << "*************************RSA算法******************************" <<endl;
  cout << "第一步：生成两个随机素数，长度为512～1024位." << endl;
  cout << "p为：" << endl;
  cout << p << endl << endl;
  cout << "q为：" << endl;
  cout << q << endl << endl;
  cout << "第二步：计算n = p * q." << endl;
  cout << "n为：" << endl;
  cout << n << endl << endl;
  cout << "第三步：计算N = (p - 1) * (q - 1)." << endl;
  cout << "N为：" << endl;
  cout << N << endl << endl;
  cout << "第四步：计算私钥d = e^-1 mod N,其中e默认为65537." << endl;
  cout << "d为：" << endl;
  cout << d << endl << endl;
  cout << "请输入明文:";
  cin >> M;
  //加密
  PowerMod(C, M, e, n);
  cout << "第五步：加密，C = M^e mod n." << endl;
  cout << "加密后的结果为：" << endl;
  cout << C << endl << endl;
  //解密
  PowerMod(M, C, d, n);
  cout << "第六步：解密，M = C^d mod n." << endl;
  cout << "解密后的结果为：" << endl;
  cout << M << endl << endl;
  return 0;
}

/*
使用到的NTL库函数：
1.void mul(ZZ& x, const ZZ& a, const ZZ& b); // x = a * b
2.ZZ GCD(const ZZ& a, const ZZ& b);// d = gcd(a, b) (which is always non-negative).
3.void XGCD(ZZ& d, ZZ& s, ZZ& t, const ZZ& a, const ZZ& b);//  d = gcd(a, b) = a*s + b*t.
4.void PowerMod(ZZ& x, const ZZ& a, const ZZ& e, const ZZ& n);// x = a^e % n (e may be negative)
5.long NumBits(const ZZ& a);// returns the number of bits in binary represenation of |a|;  NumBits(0) = 0
6.void RandomBits(ZZ& x, long l);// x = pseudo-random number in the range 0..2^l-1.
7.long ProbPrime(const ZZ& n, long NumTrials = 10);// performs up to NumTrials Miller-witness tests (after some trial division).
 */
