
#include <iostream>
#include <cstdlib>
#include <exception>

using std::cout;
using std::endl;
using std::exception;

// c++ implementation of the 'quickJosephus' function in josephus.hs -
// see that file for comments.
//
// uses c++11 features, so compile with (e.g.)
//    clang++ --std=c++11 josephus.cpp

// highest pow of p that is <= n
template <typename T>
inline
T highestPowLtN(T n, T p) {
  T k = 0;
  while (n >= p) {
    n = n / p;
    k++;
  }
  return k;
}

// n ** p
template <typename T>
inline
T powInt(T n, T p) {
  T res = 1;
  for (T i = 0; i < p; i++)
    res *= n;
  return res;
}

template <typename T>
T quickJosephus(T n) {
  if (n <= 0) 
    throw std::invalid_argument("quickJosephus - n must be >= 1");

  // find the largest pow of 3 <= n, call it k
  T k = highestPowLtN<T>(n,3);
  T threeToK = powInt<T>(3, k);

  // if we're _exactly_ 3^k, just return n
  if (threeToK == n) 
    return n;

  // if we're in the inclusive range (3^k+1) .. (3^k*2):
  if (n >= threeToK + 1 && n <= threeToK * 2)
    return n - threeToK;

  // else ...
  T res = 2 * n - powInt<T>(3, k+1);
  return res;
}


int main(int argc, char ** argv) {
  argc--;
  argv++;

  if (argc != 1) {
    cout << ("need 1 arg") << endl;
    exit(1);
  }

  unsigned long n = std::stoul(argv[0]);
  if (n <= 0) {
    cout << "must be >= 1" << endl;
    exit(1);
  }

  cout << quickJosephus<unsigned long>(n) << endl;
}



