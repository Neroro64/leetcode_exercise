#include "../advent_code.hpp"

int main() {
  std::string str = "HELLO WORLD, YOMAMA \n IS SO F A T";
  std::string_view strView(str);
  std::cout << "Original: " << str << std::endl;

  {
    std::cout << "Slow: " << str << std::endl;
    Timer timer;
    auto splitted = split_slow(str);
    std::cout << "Splitted: " << std::endl;
    for (auto s : splitted) {
      std::cout << s << " | ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "Fast: " << str << std::endl;
    Timer timer;
    VecStrView splitted = split(strView);
    std::cout << "Splitted: " << std::endl;
    for (auto s : splitted) {
      std::cout << s << " | ";
    }
    std::cout << std::endl;
  }
  return 0;
}
