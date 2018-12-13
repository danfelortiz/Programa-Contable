#include <string>
#include "lector.hpp"

int main()
{
  std::vector<std::tuple<int, std::wstring, int, int> > vector = leer("datos.txt");

  for(int i=0; i<vector.size(); i++){
    std::wcout << std::get<0>(vector[i]) << "\t" << std::get<1>(vector[i]) << "\t" << std::get<2>(vector[i]) << "\t" << std::get<3>(vector[i]) << std::endl;
  }

  return 0;
}
