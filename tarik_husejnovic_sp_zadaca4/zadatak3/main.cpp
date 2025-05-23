#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

void processText(const std::string& filename, std::map<std::string, std::vector<int>>& wordMap) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Could not open the file!" << std::endl;
    return;
  }

  std::string word;
  int position = 1;
  while (file >> word) {
    wordMap[word].push_back(position);
    position += 1;
  }

  file.close();
}

void printWordPositions(const std::map<std::string, std::vector<int>>& wordMap) {
  for (const auto& entry : wordMap) {
    std::cout << "Rijec je '" << entry.first << "' i nalazi se na sljedecim pozicijama:" << std::endl;
    for (const auto& pos : entry.second) {
      std::cout << pos << ", ";
    }
    std::cout << std::endl;
  }
}

int main() {
  std::map<std::string, std::vector<int>> wordMap;
  processText("story.txt", wordMap);
  printWordPositions(wordMap);
  return 0;
}
