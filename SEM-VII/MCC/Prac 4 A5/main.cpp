#include <array>
#include <bitset>
#include <vector>

using bit = std::ptrdiff_t;
using bits = std::vector<bit>;

#include <string>
[[nodiscard]]
bits StringToBitset (std::string s)
{
   bits result;
   for (auto const c : s)
   {
      for (auto const bitSingle : std::bitset<8> (c).to_string ())
      {
         result.push_back (bitSingle - '0');
      }
   }
   return result;
}
[[nodiscard]]
bits StringToEncryptedBitset (std::string s)
{
   bits result = StringToBitset (s);
   for (auto i = std::size (result); i < 64; ++i)
      result.push_back (0);
   result.resize (64);
   return result;
}

void shift (bits* x, bit const s)
{
   _ASSERT (x != nullptr);
   for (auto j = x->size () - 1; j > 0; j--)
      (*x)[j] = (*x)[j - 1];

   (*x)[0] = s;
}

[[nodiscard]]
constexpr bit maj (bit x, bit y, bit z)
{
   if (x == 0)
   {
      if (y == 0 || z == 0)
         return 0;
      return 1;
   }
   if (y == 1 || z == 1)
      return 1;
   return 0;
}

[[nodiscard]]
bit GenerateKeySetSingle (bits* x, bits* y, bits* z) noexcept
{
   auto const m = maj ((*x)[8], (*y)[10], (*z)[10]);
   if ((*x)[8] == m)
   {
      auto const s = (*x)[13] ^ (*x)[16] ^ (*x)[17] ^ (*x)[18];
      shift (x, s);
   }
   if ((*y)[10] == m)
   {
      auto const s = (*y)[20] ^ (*y)[21];
      shift (y, s);
   }
   if ((*z)[10] == m)
   {
      auto const s = (*z)[7] ^ (*z)[20] ^ (*z)[21] ^ (*z)[22];
      shift (z, s);
   }
   auto const key = (*x)[x->size () - 1] ^ (*y)[y->size () - 1] ^ (*z)[z->size () - 1];
   return key;
}

[[nodiscard]]
bits GenerateKeySet (std::size_t length, bits* x, bits* y, bits* z) noexcept
{
   bits key_set;
   for (auto i = 0; i < length; ++i)
      key_set.push_back (GenerateKeySetSingle (x, y, z));
   return key_set;
}

[[nodiscard]]
#include <iterator>
std::tuple<bits, bits, bits> SplitIntoXYZ (bits key)
{
   bits x;
   std::copy_n (std::begin (key), 19, std::back_inserter (x));
   bits y;
   std::copy_n (std::begin (key) + 19, 22, std::back_inserter (y));
   bits z;
   std::copy_n (std::begin (key) + 19 + 22, 23, std::back_inserter (z));
   return std::make_tuple (x, y, z);
}

[[nodiscard]]
bits Encrypt (bits keystream, bits text)
{
   bits code;
   for (std::size_t i = 0; i < std::size (text); i++)
      code.push_back (text[i] ^ keystream[i % std::size (keystream)]);
   return code;
}
// Convenience Function
[[nodiscard]]
bits Decrypt (bits keystream, bits encrypt)
{
   return Encrypt (keystream, encrypt);
}

#include <iostream>

std::ostream& operator<<(std::ostream& os, bits bs)
{
   for (auto const b : bs)
      os << (int) b;
   return os;
}

void Execute (std::string text, std::string key)
{
   std::cout << "Plain Text: " << text << '\n';
   auto const bin_pt = StringToBitset (text);
   std::cout << "Binary Plain Text: " << bin_pt << '\n';
   std::cout << "Encrption Key: " << key << '\n';
   auto bin_key = StringToEncryptedBitset (key);
   std::cout << "Binary Encrption Key: " << bin_key << '\n';
   auto [x, y, z] = SplitIntoXYZ (bin_key);
   auto const key_set = GenerateKeySet (std::size (bin_pt), &x, &y, &z);
   std::cout << "Keyset: " << key_set << '\n';
   auto const bin_encrypted = Encrypt (key_set, bin_pt);
   std::cout << "Binary Encrypted Text: " << bin_encrypted << '\n';
   auto const bin_decrypted = Decrypt (key_set, bin_encrypted);
   std::cout << "Binary Decrypted Text: " << bin_decrypted << '\n';

}

int main ()
{
   Execute ("hithere", "pratikchowdhurymccpracticalscode");
}

/*
Plain Text: hithere
Binary Plain Text: 01101000011010010111010001101000011001010111001001100101
Encrption Key: pratikchowdhurymccpracticalscode
Binary Encrption Key: 0111000001110010011000010111010001101001011010110110001101101000
Keyset: 10010010110110101101100100110111001100001010011011101001
Binary Encrypted Text: 11111010101100111010110101011111010101011101010010001100
Binary Decrypted Text: 01101000011010010111010001101000011001010111001001100101
*/