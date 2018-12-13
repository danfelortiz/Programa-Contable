#ifndef LECTOR_H_INCLUDED
#define LECTOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <typeinfo>
#include <tuple>

//La siguiente función me retorna el producto con la cantidad que tenga
std::tuple<int, std::string, int> elemento();
//La siguiente función lee el archivo y guarda los 3 elementos en una tupla y esta en un vector
std::vector<std::tuple<int, std::wstring, int, int> > leer(const char* name);

std::tuple<int, std::string, int> elemento()
{
  std::string s;
  int n, m;
  std::cout << "Nombre del producto: ";
  std::getline(std::cin,s);
  std::cout << "Código del producto: ";
  std::cin >> m;
  std::cout << "Cantidad del producto: ";
  std::cin >> n;

  return std::make_tuple(m,s,n);
}


std::vector<std::tuple<int, std::wstring, int, int> > leer(const char* name)
{
  char *locale = setlocale(LC_ALL, "");
  FILE *pFile = fopen("datos.txt", "r");
  
  wint_t c;
  std::vector<std::vector<std::wstring> > y;
  std::wstring ws(L"");
  int i=0;
  y.push_back( std::vector<std::wstring>() );
  while ((c = fgetwc(pFile)) != WEOF){
    if(c=='\n' || c=='\t'){
      if(c=='\n'){
	y[i].push_back(ws);
	y.push_back( std::vector<std::wstring>() );
	i++;
	ws.clear();
      }
      else{
	y[i].push_back(ws);
	ws.clear();
      }
    }
    else{
      ws.push_back(c);
    }
  }
  fclose(pFile);
  y.pop_back();

  std::vector<std::tuple<int, std::wstring, int, int> > v;
  for(int i=0; i<y.size(); i++){
    auto tuple = std::make_tuple(std::stoi(y[i][0]),y[i][1],std::stoi(y[i][2]),std::stoi(y[i][3]));
    v.push_back(tuple);
  }
  
  return v;
}


#endif
