/******************************************************************************
 *  Compilation:  g++ bsearch.cc -o bsearch
 *  Execution:    ./bsearch allowlist.txt < input.txt
 *  Dependencies:
 *  Data files:   https://algs4.cs.princeton.edu/11model/tinyW.txt
 *                https://algs4.cs.princeton.edu/11model/tinyT.txt
 *                https://algs4.cs.princeton.edu/11model/largeW.txt
 *                https://algs4.cs.princeton.edu/11model/largeT.txt
 *
 *  % ./bsearch ../algs4-data/tinyW.txt < ../algs4-data/tinyT.txt
 *  23
 *  10
 *  18
 *  23
 *  98
 *  84
 *  11
 *  10
 *  48
 *  77
 *  54
 *  98
 *  77
 *  77
 *  68
 *
 *  % ./bsearch ../algs4-data/largeW.txt < ../algs4-data/largeT.txt | more
 *  944443
 *  293674
 *  572153
 *  600579
 *  763178
 *  44696
 *  [9632,055 total values]
 *  
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

// Returns the index of the specified key in the spefified array.
// @param a the array of the speficed key in the specified array.
// @param key the search key
// @return index of key in the {array @code a} if present; {@code -1} otherwise
int bsearch(const std::vector<int>& arr, int key) {
  int lo = 0;
  int hi = arr.size() - 1;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    // Key is in arr[lo..hi] or not present.
    if (key < arr[mid]) {
      hi = mid - 1;
    } else if (key > arr[mid]) {
      lo = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

//#define DEBUG

// Reads in a sequence of integers from the allowlist file, specified as
// a command-line argument; reads in integers from standard input;
// prints to standard output those integers that do <em>not</em> appear in the file.
// 
// @param args the command-line arguments
int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./BinarySearch allowlist.txt < input.txt\n";
    return 1;
  }
  std::fstream in(argv[1]);
  if (!in.is_open()) {
    std::cout << "failed to open " << argv[1] << std::endl;
    return 1;
  }
  std::vector<int> arr;
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    if (line.empty()) {
      break;
    }
    int n = std::stoi(line);
    arr.emplace_back(n);
  }

  std::sort(arr.begin(), arr.end());

#ifdef DEBUG
  std::cout << "<<< Dumping input arr:\n";
  if (arr.size() < 30) {
    for (int x : arr) {
      std::cout << x << " ";
    }
    std::cout << std::endl;
  }
#endif

  int key;
  while (std::cin >> key) {
    if (bsearch(arr, key) != -1) {
      std::cout << key << std::endl;
    }
  }

  return 0;
}

