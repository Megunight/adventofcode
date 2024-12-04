#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <regex>

std::vector<std::pair<int, int>> findMul(std::string s) {
  const std::regex mul(R"(mul\((\d+),(\d+)\))");
  std::sregex_iterator begin(s.begin(), s.end(), mul);
  std::sregex_iterator end;

  std::vector<std::pair<int, int>> results;

  for (auto it = begin; it != end; ++it) {
    int x = std::stoi((*it)[1].str());
    int y = std::stoi((*it)[2].str());
    results.push_back(std::pair<int, int>{x, y});
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
  while (std::getline(file, line)) {
    std::vector<std::pair<int, int>> results = findMul(line);
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
