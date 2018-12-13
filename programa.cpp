#include <string>
#include "lector.hpp"
#include "z.hpp"

int main()
{/*
  std::vector<std::tuple<int, std::wstring, int, int> > vector = leer("datos.txt");

  for(int i=0; i<vector.size(); i++){
    std::wcout << std::get<0>(vector[i]) << "\t" << std::get<1>(vector[i]) << "\t" << std::get<2>(vector[i]) << "\t" << std::get<3>(vector[i]) << std::endl;
  }
 */
  std::vector<std::vector<std::wstring> > y = z_leer("EJ051218.TXT");
  std::vector<std::vector<std::vector<std::wstring> > > v = z_partes(y);

  for(int i=0; i<v.size(); i++){
    std::wcout << i << std::endl;
    for(int j=0; j<v[i].size(); j++){
      for(int k=0; k<v[i][j].size(); k++){
	std::wcout << v[i][j][k] << ' ';
      }
      std::wcout << L'\n';
    }
    std::wcout << L'\n';
  }
  
  //Esta función no está terminada.
  std::vector<std::tuple<std::wstring, std::wstring, std::wstring, std::wstring, std::wstring, int, std::vector<std::tuple<std::wstring, int, int, int> > > > z = z_REG(v);

  return 0;
}
