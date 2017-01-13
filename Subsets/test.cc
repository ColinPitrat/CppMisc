#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<set<int>> getSubsets(set<int> iVals){
   if(iVals.empty()) return {{}};
   
   vector<set<int>> ret;
   int v = *iVals.begin();
   iVals.erase(v);
   vector<set<int>>::iterator it;
   vector<set<int>> subRes = getSubsets(iVals);
   for(it = subRes.begin(); it != subRes.end(); ++it) {
       ret.push_back(*it);
       it->insert(v);
       ret.push_back(*it);
   }

   return ret;
}

string to_string(set<int> vals) {
  ostringstream result;
  result << "[";
  for(const auto &v : vals) {
    result << v << ",";
  }
  result << "]";
  return result.str();
}

string to_string(vector<set<int>> vals) {
  ostringstream result;
  result << "{";
  for(const auto &v : vals) {
    result << to_string(v) << ",";
  }
  result << "}";
  return result.str();
}


bool Test(set<int> input, vector<set<int>> output)
{
   auto result = getSubsets(input);
   bool ok = (result == output);
   std::cout << to_string(input) << " gives " << to_string(result) << (ok ? " OK " : " FAILURE ") << std::endl;
   if (!ok) {
      std::cout << " '" << to_string(result) << "' vs. '" << to_string(output) << "'" << std::endl;
   }
   return ok;
}

int main()
{
   bool result = true;
   result &= Test({}, {{}});
   result &= Test({1,2,3}, {{}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}});
   std::cout << std::endl << " ==== " << (result ? "OK" : "FAILURE") << " ==== " << std::endl << std::endl;
   return 0;
}
