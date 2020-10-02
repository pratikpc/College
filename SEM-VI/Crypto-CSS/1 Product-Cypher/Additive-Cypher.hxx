#include <algorithm>
#include <string>

// Reference http://banach.millersville.edu/~bob/math171/encryption/node3.html
constexpr const char PerfromAdditiveCypherOnChar (const char p_ch, const char key, const char start, const char count_alpha)
{
   const char p_upper_dist = p_ch - start;
   const char p_upper_key = p_upper_dist + key;
   const char c_ch_dist = p_upper_key % (count_alpha + 1);
   const char c_ch = c_ch_dist + start;
   return c_ch;
}
constexpr const char PerfromAdditiveDecypherOnChar (const char c_ch, const char key, const char start, const char count_alpha)
{
   const char c_upper_dist = c_ch - start;
   const char c_upper_key = c_upper_dist - key + (count_alpha + 1);
   const char p_ch_dist = c_upper_key % (count_alpha + 1);
   const char p_ch = p_ch_dist + start;
   return p_ch;
}

std::string AdditiveCypher (const std::string& p_text, const char key)
{
   std::string c_text = "";
   c_text.reserve (p_text.size ());
   for (const char p_ch : p_text)
   {
      if (std::isupper (p_ch))
      {
         c_text.push_back (PerfromAdditiveCypherOnChar (p_ch, key, 'A', 'Z' - 'A'));
      }
      else if (std::islower (p_ch))
      {
         c_text.push_back (PerfromAdditiveCypherOnChar (p_ch, key, 'a', 'z' - 'a'));
      }
      else if (std::isdigit (p_ch))
      {
         c_text.push_back (PerfromAdditiveCypherOnChar (p_ch, key, '0', '9' - '0'));
      }
      else
      {
         // If the Character is Unknown, just add it
         // No way to encrypt it anyways
         c_text.push_back (p_ch);
      }
   }
   return c_text;
}
std::string AdditiveDecypher (const std::string& c_text, const char key)
{
   std::string p_text = "";
   p_text.reserve (c_text.size ());
   for (const char c_ch : c_text)
   {
      if (std::isupper (c_ch))
      {
         p_text.push_back (PerfromAdditiveDecypherOnChar (c_ch, key, 'A', 'Z' - 'A'));
      }
      else if (std::islower (c_ch))
      {
         p_text.push_back (PerfromAdditiveDecypherOnChar (c_ch, key, 'a', 'z' - 'a'));
      }
      else if (std::isdigit (c_ch))
      {
         p_text.push_back (PerfromAdditiveDecypherOnChar (c_ch, key, '0', '9' - '0'));
      }
      else
      {
         // If the Character is Unknown, just add it
         // No way to encrypt it anyways
         p_text.push_back (c_ch);
      }
   }
   return p_text;
}