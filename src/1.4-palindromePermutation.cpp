#include <iostream>
#include <array>

struct LetterCounter
{
  void operator()(std::string_view const input)
  {
     for (char symbol : input)
     {
       if (!std::isalpha(symbol))
         continue;
       
       if (std::isupper(symbol))
         symbol += ('a' - 'A');
       
       std::uint8_t idx = static_cast<std::uint8_t>(symbol - 'a');
       counts[idx]++;
     }
  }
  
  bool isPalindrome() const
  {
    bool singleLetter = false;
    for (auto count : counts)
    {
      if (count % 2 == 0)
        continue;
      
      if (singleLetter)
        return false;
      
      singleLetter = true;
    }
    
    return true;
  }
  
private:
  std::array<std::size_t, 26> counts = {0};
};

int main()
{
  std::string_view input = "Tact Coa";
  
  LetterCounter counter;
  counter(input);
  
  std::cout << "Palindrome: " << std::boolalpha << counter.isPalindrome() << std::endl;
  
  return 0;
}