#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

int main (int argc, char *argv[]) {
  std::string filename;
  std::cout << "Enter the file name: ";
  std::cin >> filename;

  std::ifstream file(filename);
  if (!file) {
      std::cerr << "Error: Could not open the file \"" << filename << "\"." << std::endl;
      return 1;
  }

  std::vector<std::string> input;
  std::string line;

  while (std::getline(file, line)) {
      input.push_back(line);
  }

  file.close();

  // input is stored as a list of strings with each string having format string   string (3 spaces)
  // separate into two lists
  std::vector<int> list1, list2;
  for (std::string s : input) {
    std::vector<std::string> temp;
    size_t pos = s.find("   ");
    std::string firstHalf, secondHalf;

    firstHalf = s.substr(0, pos);
    secondHalf = s.substr(pos + 3);
    
    list1.push_back(std::stoi(firstHalf));
    list2.push_back(std::stoi(secondHalf));
  }

  std::unordered_map<int, int> numOfOccurences;
  for (int x : list2) {
    numOfOccurences[x]++;
  }

  int sum = 0;
  for (int x : list1) {
    sum += numOfOccurences[x] * x;
  }

  std::cout << sum << "\n";

  return 0;
}
