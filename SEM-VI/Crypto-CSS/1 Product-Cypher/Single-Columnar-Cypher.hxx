#include <string>
#include <numeric>
#include <vector>
template<typename T>
std::vector<std::size_t> tag_sort (const T& v)
{
   std::vector<std::size_t> result (v.size ());
   std::iota (std::begin (result), std::end (result), 0);
   std::sort (std::begin (result), std::end (result),
      [&v](const auto& lhs, const auto& rhs)
   {
      return v[lhs] < v[rhs];
   }
   );
   return result;
}

std::string SingleColumnarCypher (std::string p_text, const std::string key)
{
   auto const pad = (p_text.size () / key.size () + 1) * key.size ();
   p_text.reserve (pad);
   for (std::size_t i = p_text.size(); i < pad; ++i)
      p_text.push_back(' ');

   std::string c_text;
   c_text.reserve (p_text.size ());

   auto const sorted_indexes = tag_sort (key);

   for (std::size_t i = 0; i < key.size (); ++i)
   {
      auto const column = sorted_indexes[i];
      for (std::size_t j = 0; j < ((p_text.size () / key.size ()) + 1); j += 1)
      {
         auto const row_col = j * key.size () + column;
         if (row_col >= p_text.size ())
            break;
         c_text.push_back (p_text[row_col]);
      }
   }

   return c_text;
}

std::string SingleColumnarDecypher (const std::string& c_text, const std::string& key)
{
   std::string p_text;
   p_text.resize (c_text.size ());

   auto const sorted_indexes = tag_sort (key);

   for (std::size_t column = 0; column < key.size (); ++column)
   {
      for (std::size_t j = 0; j < c_text.size () / key.size (); j += 1)
      {
         auto const row_col_ins = j * key.size () + sorted_indexes[column];
         auto const row_col = column * c_text.size () / key.size () + j;
         if (row_col >= c_text.size ())
            break;
         p_text[row_col_ins] = (c_text[row_col]);
      }
   }
   return p_text;
}