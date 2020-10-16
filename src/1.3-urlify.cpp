#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
#include <stdexcept>

void urlify(std::string& input)
{
  auto const isSpace = [](char const c){ return c == ' '; };
  
  std::size_t const spaceLeft = std::distance(input.rbegin(), std::find_if_not(input.rbegin(), input.rend(), isSpace));
  std::size_t const spaces = std::count_if(input.begin(), input.end(), isSpace);
  std::size_t const spacesBetweenWords = spaces - spaceLeft;
  if (spacesBetweenWords * 2 > spaceLeft)
    throw std::runtime_error("Not enough space at the end");
  
  std::size_t characterPos = input.size() - spaceLeft - 1;
  std::size_t currPos = characterPos + spacesBetweenWords*2;
  while(currPos != characterPos)
  {
    if (!isSpace(input[characterPos])) {
      input[currPos] = input[characterPos];
      currPos--;
    } else {
      input[currPos] = '0'; 
      input[currPos-1] = '2';
      input[currPos-2] = '%';
      currPos -= 3;
    }
    
    characterPos--;
  }
}

std::string urlifyCopy(std::string const& input)
{
  std::string result = input;
  urlify(result);
  return result;
}

int main() {
  assert(urlifyCopy("This is the test string        ") == "This%20is%20the%20test%20string");
  assert(urlifyCopy("This is the test string           ") == "This%20is%20the%20test%20string   ");
  assert(urlifyCopy("Word") == "Word");
  assert(urlifyCopy("Two  words    ") == "Two%20%20words");
}
