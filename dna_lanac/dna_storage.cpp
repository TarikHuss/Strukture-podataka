#include "dna_storage.hpp"
#include <string>
#include <ostream>

void DNAStorage::print(std::ostream & out) const {
for(auto c : data)
  out << c;
out << std::endl;
}

void DNAStorage::print(std::ostream &, int pos, int len) const {}

void DNAStorage::insert(int pos, std::string lanac) {
  if (pos > data.size())
    data.resize(pos, ' ');
  data.insert(data.begin()+ pos, lanac.begin(), lanac.end());
}

int DNAStorage::remove(int pos, int len) { 
  auto end = data.begin() + pos + len;
  if(end>data.end())
    end = data.end();
  data.erase(data.begin() + pos, end);
  return len; 
}

void DNAStorage::store(std::string filename) const {}

void DNAStorage::load(std::string filename) {}
