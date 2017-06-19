
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include <cstdint>

using std::cout;
using std::endl;
using std::vector;
using std::reverse;
using std::unique_ptr;
using std::string;

typedef vector<int8_t> cvec;

// do the "replacement" described in the puzzle, for "b"
void replace(cvec &vec) {
  for (auto i = vec.begin(); i != vec.end(); i++) {
    if (*i == 1) {
      *i = 0;
    } else {
      *i = 1;
    }
  }
}

// given a state, make the next state
void step(const cvec &a, cvec &out) {
  cvec b { a };
  reverse( b.begin(), b.end() );
  replace(b);

  // copy a into out
  out.insert( out.end(), a.begin(), a.end() );
  // a 0
  out.push_back( 0 );
  // copy b into out
  out.insert( out.end(), b.begin(), b.end() );
}

// obtain the checksum for xs
void checksum(const cvec &xs, cvec &out) {
  assert ( xs.size() % 2 == 0);

  // we ensure we have the right checksum before we
  // copy it to out.
  cvec tmpRes { };

  for(auto i = xs.begin(); i != xs.end(); i++, i++) {
    // get next pos
    auto inext = i; inext++;

    char c = *i;
    char c_next = *inext;
    if (c == c_next) {
      tmpRes.push_back(1);
    } else {
      tmpRes.push_back(0);
    }
  }

  if (tmpRes.size() % 2 == 0) {
    // get a checksum that _does_ have len 2
    cvec len_2_csum { };
    checksum(tmpRes, len_2_csum);
    // copy to out
    out.insert( out.end(), len_2_csum.begin(), len_2_csum.end() );
  } else {
    // our checksum if fine, so copy it
    out.insert( out.end(), tmpRes.begin(), tmpRes.end() );
  }  
}

// using /state/ as a start-state, create enough data
// to fill up a disk of size /desiredLen/. 
//  Return the checksum of the data in /csum/.
//
// comments: A bit memory-hoggy, no doubt one could make better 
// use of resources. But it runs in under 4 secs on my PC with no
// optimizations flags, and in less than a second at -O3, and that's
// good enough for me.
//
// ... I mean ... we don't even need to actually physically _construct_
// the string, just have a way of iterating over it. 
// So you could iterate along a string, "see" a zero, then
// iterate back again, this time "seeing" ones where there are 
// zeros, and zeros where there are ones.
//
// And we know the length at each stage - 2x + 1, where x is the
// length of the previous stage - so we could quickly calculate
// at which iteration we'd achieve the depth we wanted.
// Hm.. Ah well, maybe later. 
void fill_and_check(const cvec &state, int desiredLen, cvec &csum) {
  assert(desiredLen % 2 == 0);

  unique_ptr<cvec> currState { new cvec( state ) };
  unique_ptr<cvec> nextState { new cvec{ }  };

  while( currState->size() < desiredLen ) {
    // get next state
    cout << "currState sz: " << currState->size() << endl;
    step(*currState, *nextState);
    currState = std::move(nextState);
    nextState = unique_ptr<cvec> { new cvec{ }  };
  }

  currState->resize(desiredLen); 
  checksum(*currState, csum);
}

void solve_sample() {
  cvec start_state { 1, 0, 0, 0, 0 };
  int desiredLen = 20;

  cvec csum { };
  fill_and_check(start_state, desiredLen, csum);

  cout << "finished solve_sample" << endl;
  cout << "checksum is:\n  " << endl;
  for (auto i = csum.begin(); i != csum.end(); i++) {
    cout << (int) *i << ", ";
  }
  cout << endl;

}

void solve_part_A() {
  string inputStr { "10111011111001111" };
  cvec start_state { };    

  for (auto i = inputStr.begin(); i != inputStr.end(); i++) {
    char currChar = *i;
    char newChar = currChar - '0';
    start_state.push_back( newChar );
  }

  int desiredLen = 272;
  cvec csum { };
  fill_and_check(start_state, desiredLen, csum);

  cout << "finished pt A" << endl;
  cout << "checksum is:\n  " << endl;
  for (auto i = csum.begin(); i != csum.end(); i++) {
    cout << (int) *i ;
  }
  cout << endl;
}

// same as part A but with different desired len
void solve_part_B() {
  string inputStr { "10111011111001111" };
  cvec start_state { };    

  for (auto i = inputStr.begin(); i != inputStr.end(); i++) {
    char currChar = *i;
    char newChar = currChar - '0';
    start_state.push_back( newChar );
  }

  int desiredLen = 35651584;
  cvec csum { };
  fill_and_check(start_state, desiredLen, csum);

  cout << "finished pt B" << endl;
  cout << "checksum is:\n  " << endl;
  for (auto i = csum.begin(); i != csum.end(); i++) {
    cout << (int) *i ;
  }
  cout << endl;
}


int main() {
  solve_part_B();
}




