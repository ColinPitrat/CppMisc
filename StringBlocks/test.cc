#include <iostream>
#include <algorithm>

std::string formatStringOld(std::string input)
{
   input.erase(std::remove_if(input.begin(), input.end(),
         [](char c) -> bool {
         return (c < 'A' || c > 'Z') &&
                (c < 'a' || c >'z') &&
                (c < '0' || c> '9');
                }), input.end());

   size_t strlen = input.length();
   size_t stop_at = strlen;
   switch(input.length() % 3)
   {
      case 1:
         stop_at -= 4;
         break;
      case 2:
         stop_at -= 2;
         break;
      default:
         break;
   }
   size_t i = 3;
   while(i < stop_at) {
      input = input.insert(i, " ");
      strlen++;
      stop_at++;
      i += 4;
   }
   while(i < strlen) {
      input = input.insert(i, " ");
      i += 3;
   }
   return input;
}

std::string formatStringOld2(std::string input)
{
   input.erase(std::remove_if(input.begin(), input.end(),
         [](char c) -> bool {
         return (c < 'A' || c > 'Z') &&
                (c < 'a' || c >'z') &&
                (c < '0' || c> '9');
                }), input.end());

   std::string result;
   result.reserve(input.length()*4/3);
   auto stop_at = input.end();
   switch(input.length() % 3)
   {
      case 1:
         stop_at -= 4;
         break;
      case 2:
         stop_at -= 2;
         break;
      default:
         break;
   }
   auto it = input.begin();
   while(it != stop_at) {
      for (int i = 0; i < 3; ++i) {
         result.push_back(*it);
         it++;
      }
      if(it == input.end()) break;
      result.push_back(' ');
   }
   while(it != input.end()) {
      for (int i = 0; i < 2; ++i) {
         result.push_back(*it);
         it++;
      }
      if(it == input.end()) break;
      result.push_back(' ');
   }
   return result;
}

void copyInBlock(std::string::iterator& src, std::string& dst, int block_size, int nb_blocks)
{
   for(int i = 0; i < nb_blocks; i++)
   {
      for(int j = 0; j < block_size; j++)
      {
         dst.push_back(*src);
         src++;
      }
      dst.push_back(' ');
   }
}

std::string formatString(std::string input)
{
   input.erase(std::remove_if(input.begin(), input.end(),
         [](char c) -> bool {
         return (c < 'A' || c > 'Z') &&
                (c < 'a' || c >'z') &&
                (c < '0' || c> '9');
                }), input.end());

   std::string result;
   result.reserve(input.length()*4/3);

   auto stop_at = input.length();
   switch(input.length() % 3)
   {
      case 1:
         stop_at -= 4;
         break;
      case 2:
         stop_at -= 2;
         break;
      default:
         break;
   }

   int block_of_3 = stop_at / 3;
   int block_of_2 = (input.length() - stop_at) / 2;

   auto it = input.begin();
   copyInBlock(it, result, 3, block_of_3);
   copyInBlock(it, result, 2, block_of_2);
   return result.substr(0, result.length()-1);
}


bool Test(std::string input, std::string output)
{
   auto result = formatString(input);
   bool ok = (result == output);
   std::cout << input << " gives " << result << (ok ? " OK " : " FAILURE ") << std::endl;
   if (!ok) {
      std::cout << " '" << result << "' vs. '" << output << "'" << std::endl;
   }
   return ok;
}

int main()
{
   bool result = true;
   result &= Test("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AAA AA AA"); 
   result &= Test("AA-44 BB 55CD 83FG", "AA4 4BB 55C D83 FG");
   result &= Test("00-44 48 5555 8361", "004 448 555 583 61");
   result &= Test("0 - 22 1985--324", "022 198 53 24");
   result &= Test("ABC372654", "ABC 372 654");
   std::cout << std::endl << " ==== " << (result ? "OK" : "FAILURE") << " ==== " << std::endl << std::endl;
   return 0;
}
