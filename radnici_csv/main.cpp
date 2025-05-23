#include "firma.hpp"
#include "radnik.hpp"

#include <fstream>
#include <vector>

int main() {
  Firma corp;
  corp.ucitaj_radnike("acme.txt");
  corp.ucitaj_radnike("globex.txt");
  std::cout << "Ucitano " << corp.size() << " osoba iz firmi acme i globex."
            << std::endl;
  
  std::cout << "Ukupna plata: " << corp.ukupna_plata() << std::endl;
  
  for (auto it = corp.begin(); it < corp.end();)
    if (it->godine() > 60)
      it = corp.erase(it);
    else
      ++it;
  std::cout << "Nakon brisanja firma ima " << corp.size() << " radnika."
            << std::endl;
  corp.for_each([](auto& radnik) {
    if (radnik.godineStaza() > 10)
      radnik.plata(radnik.plata() * 1.2);
    else if (radnik.godineStaza() > 5)
      radnik.plata(radnik.plata() * 1.1);
  });
  
  std::cout << "Ukupna plata: " << corp.ukupna_plata() << std::endl;
  std::ofstream output_file("corp.txt");
  for (auto it = corp.begin(); it < corp.end(); ++it)
    output_file << *it << std::endl;
  output_file.close();
}
