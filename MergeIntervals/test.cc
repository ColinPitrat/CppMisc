#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Interval {
  public:
    Interval(int min, int max) : min_(min), max_(max) {}

    // Intervals are ordered based on their minimum element
    bool operator<(const Interval &other) const { return this->min_ < other.min_; }

    int getMin() const { return min_; }
    int getMax() const { return max_; }

  private:
    int min_, max_;
};

string toString(vector<int> &v)
{
  ostringstream result;
  result << "{";
  for(const auto &e : v)
  {
    result << e << ",";
  }
  result << "}";
  return result.str();
}

int countMergedIntervals(vector<int> &A, vector<int> &B)
{
  if (A.size() != B.size()) {
    throw "Error: mergeInterval expects two vectors of same size";
  }
  if (A.empty()) return 0;

  vector<Interval> intervals;
  for(int i = 0; i < A.size(); ++i)
  {
    intervals.push_back(Interval(A[i], B[i]));
  }
  sort(intervals.begin(), intervals.end());

  int nb_gaps = 0;
  auto it = intervals.begin();
  int current_max = it->getMax();
  while(it != intervals.end()) {
    if (it->getMin() <= current_max) {
      // The two sets overlap, 'merge' them
      current_max = max(it->getMax(), current_max);
    } else {
      // The two sets do not overlap, i.e we found a new gap
      // Continue with the next set
      current_max = it->getMax();
      nb_gaps++;
    }
    it++;
  }
  // The number of intervals is the number of gaps + 1 (each gaps is between two intervals)
  return nb_gaps + 1;
}

bool Test(vector<int> A, vector<int> B, int expected)
{
  auto result = countMergedIntervals(A, B);
  if (result != expected) {
    cout << "countMergedIntervals(" << toString(A) << ", " << toString(B) << ") == " << result << " != " << expected << endl;
    return false;
  }
  return true;
}

int main()
{
   bool result = true;
   result &= Test({}, {}, 0);
   result &= Test({3}, {12}, 1);
   result &= Test({1, 12, 42, 70, 36, -4, 43, 15}, {5, 15, 44, 72, 36, 2, 69, 24}, 5);
   int max_n = 100;
   vector<int> a;
   vector<int> b;
   a.reserve(2*max_n);
   b.reserve(2*max_n);
   for(int i = -max_n; i<max_n; i++)
   {
    a.push_back(i);
    b.push_back(i+1);
   }
   result &= Test(a, a, 2*max_n);
   result &= Test(a, b, 1);
   std::cout << std::endl << " ==== " << (result ? "OK" : "FAILURE") << " ==== " << std::endl << std::endl;
   return 0;
}
