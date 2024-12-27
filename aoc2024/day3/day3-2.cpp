#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <regex>

std::vector<std::pair<int, int>> findMul(std::string s, bool& doMul) {
  // 5 capture groups in regex instructions
  // 1: mul(), 2: first digit, 3: second digit, 4: do(), 5: don't()
  const std::regex instructions(R"((mul\((\d+),(\d+)\))|(do\(\))|(don't\(\)))");
  std::sregex_iterator begin(s.begin(), s.end(), instructions);
  std::sregex_iterator end;

  std::vector<std::pair<int, int>> results;

  for (auto it = begin; it != end; ++it) {
    if ((*it)[1].matched) {
      if (doMul) {
        int x = std::stoi((*it)[2].str());
        int y = std::stoi((*it)[3].str());
        results.push_back(std::pair<int, int>{x, y});
      }
    } else if ((*it)[4].matched) {
      doMul = true;
    } else if ((*it)[5].matched) {
      doMul = false;
    }
  }

  return results;
}

int main (int argc, char *argv[]) {
  std::string fileName;
  std::cout << "Enter file name: ";
  std::cin >> fileName;

  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    return 1;
  }

  std::string line;
  std::vector<std::pair<int, int>> factors;
  bool doMul = true;
  while (std::getline(file, line)) {
    std::vector<std::pair<int, int>> results = findMul(line, doMul);
    factors.insert(factors.end(), results.begin(), results.end()); // concatenate results with end factors
  }

  file.close();
  
  int sum = 0; 
  for (std::pair<int, int> x : factors) {
    int product = x.first * x.second;
    sum += product;
  }

  std::cout << sum << std::endl;

  return 0;
}
