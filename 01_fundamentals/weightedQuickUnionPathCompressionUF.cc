/******************************************************************************
 *  Compilation:  g++ weightedQuickUnionPathCompressionUF.cc -o weightedQuickUnionPathCompressionUF
 *  Execution:  ./weightedQuickUnionPathCompressionUF < input.txt
 *  Dependencies:
 *  Data files:   https://algs4.cs.princeton.edu/15uf/tinyUF.txt
 *                https://algs4.cs.princeton.edu/15uf/mediumUF.txt
 *                https://algs4.cs.princeton.edu/15uf/largeUF.txt
 *
 *  Weighted quick-union algorithm (without path compression).
 *
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <stdexcept>

 /**
  * The WeightedQuickUnionPathCompressionUF class represents a union-find data type
  * (also known as the disjoint-sets data type).
  * It supports the classic union and find operations,
  * along with a count operation that returns the total number of sets.
  *
  * This implementation uses weighted quick union by size without full path compression.
  * The constructor takes theta(n) time, where n is the number of sites.
  * The find, and union operatoins take theta(log(n)) time in the worse case;
  * the count operaon takes theta(1) time.
  * Moreover, starting from an empty data structure with n sites, any
  * intermixed sequence of m union and find operatons take alpha(n) time,
  * where alpha(n) is the inverse of https://en.wikipedia.org/wiki/Ackermann_function#Inverse.
  * AKA Ackermann's function.
  *
  * For additional documentation, see https://algs4.cs.princeton.edu/15uf.
  * 
  * @author xjliang
  * @date   Fri Dec  4 15:18:43 CST 2020
  */

class WeightedQuickUnionPathCompressionUF {
 public:
  // Initializes an empty uinon-find data structure with n elements
  // 0 through n - 1. Initially, each element is in its own set.
  WeightedQuickUnionPathCompressionUF(int n) : count_(n) {
    parent_.reserve(n);
    size_.reserve(n);
    for (int i = 0; i < n; i++) {
      parent_.push_back(i);
      size_.push_back(1);
    }
  }

  ~WeightedQuickUnionPathCompressionUF() { }

  // Returns the number of sets.
  int count() const { return count_; }

  // Returns the canonical element of the set containing element p.
  int find(int p) {
    validate(p);
    int root = p;
    while (root != parent_[root]) {
      root = parent_[root];
    }
    while (p != root) {
      int newp = parent_[p];
      parent_[p] = root;
      p = newp;
    }
    return root;
  }

  // Merges the set containing element p with the set containing element q.
  void merge(int p, int q) {
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) {
      return;
    }

    // make smaller root pointer to larger one
    if (size_[root_p] < size_[root_q]) {
      parent_[root_p] = parent_[root_q];
      size_[root_q] += size_[root_p];
    } else {
      parent_[root_q] = parent_[root_p];
      size_[root_p] += size_[root_q];
    }
    count_--;
  }

 private:
  // Validates tha p is a valid index.
  void validate(int p) {
    int n = parent_.size();
    if (p < 0 || p >= n) {
      char msg[80];
      sprintf(msg, "index %d is not betwwen 0 and %d", p, n - 1);
      throw new std::out_of_range(msg);
    }
  }

 private:
  std::vector<int> parent_;   // parent_[i] = parent of i
  std::vector<int> size_;     // size_[i] = number of elements in subtree rooted in i
                              // Note: not necessarily correct if i is not a root node
  int count_;                 // number of components
}; // class WeightedQuickUnionPathCompressionUF


// Reads an integer n and a sequence of pairs of integers
// (between 0 and n - 1 from standard input, where each integer)
// in the pair represents some element;
// if the elements are in different sets, merge the two sets
// and print the pair to standard output.
int main(int argc, char* argv[]) {
  int n;
  std::cin >> n;
  WeightedQuickUnionPathCompressionUF uf(n);

  int p;
  int q;
  try {
    while (std::cin >> p >> q) {
      if (uf.find(p) == uf.find(q)) {
        continue;
      }
      uf.merge(p, q);
      std::cout << p << " " << q << std::endl;
    }
    std::cout << uf.count() << " components" << std::endl;
  } catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}

