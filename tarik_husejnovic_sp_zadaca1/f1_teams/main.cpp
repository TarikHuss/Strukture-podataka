#include "f1.hpp"
#include "f1_teams.hpp"
#include <algorithm>
#include <fstream>
#include <vector>

int main() {
  F1_teams tim;
  tim.ucitaj_timove("f1_teams.csv");
  std::cout << "Ucitano " << tim.size() << " tima iz fajla."<< std::endl; 
  for (auto it = tim.begin(); it < tim.end();)
    if (it->titule() ==0)
      it = tim.erase(it);
    else
      ++it;
  std::cout << "Nakon brisanja fajl ima " << tim.size() << " timova."<< std::endl;
  std::sort(tim.begin(), tim.end(), []( F1& a,  F1& b) {
    return a.titule()>b.titule();
  }); 
  std::ofstream output_file("f1_teams_sorted.csv");
  output_file<<"team_name,country_of_origin,year_founded,number_of_championships,team_budget_million_usd"<<std::endl;
  for (auto it = tim.begin(); it < tim.end(); ++it)
    output_file << *it << std::endl;
  output_file.close();
}

