#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <typeinfo>
#include <tuple>

std::tuple<std::wstring, int> nombre_valor(std::vector<std::wstring> &y);

std::tuple<int, int> cantidad_precio(std::vector<std::wstring> &y);

std::string disemvowel(std::string str);

int main(void)
{
  /*
  std::wstring num1(L"3900");
  std::wstring num2(L"-1");
  std::wstring num3(L"00005");
  
  int i1 = std::stoi(num1);
  int i2 = std::stoi(num2);
  int i3 = std::stoi(num3);
  std::wcout << num1 << '\t' << i1 << std::endl;
  std::wcout << num2 << '\t' << i2 << std::endl;
  std::wcout << num3 << '\t' << i3 << std::endl;

  std::wstring ws(L"-$500");
  wchar_t signo = L'$';
  
  std::vector<std::wstring> ws1;
  ws1.push_back(num1);
  ws1.push_back(num2);
  ws1.push_back(num3);

  auto tuple = cantidad_precio(ws1);
  std::wcout << std::get<0>(tuple) << '\t' << std::get<1>(tuple) << std::endl; 
  */

  std::string str("abcdefghij...nopqrstuv  ABCEFGHIJ...NOPQRSTUV");
  std::cout << str << std::endl;
  std::string remove = disemvowel(str);
  std::cout << remove << std::endl;
  
  return 0;
}

std::string disemvowel(std::string str)
{
  for (int i = 0; i < str.length(); i++)
  {
    if (str.at(i) == 'a' || str.at(i) == 'u' ||str.at(i) == 'e' 
    || str.at(i) == 'i' || str.at(i) == 'o' )
    {
      str.erase(i,1);
    }  
    else if (str.at(i) == 'A' || str.at(i) == 'E' || str.at(i) == 'I' || 
    str.at(i) == 'O' || str.at(i) == 'U')
    {
      str.erase(i,1);
    }
   }
    return str;
}


std::tuple<int, int> cantidad_precio(std::vector<std::wstring> &y)
{
  y[0].pop_back();
  return std::make_tuple(std::stoi(y[0]), std::stoi(y[2]));
}


std::tuple<std::wstring, int> nombre_valor(std::vector<std::wstring> &y)
{
  std::wstring nombre;
  std::wstring espacio (L" "); 
  for(int i=0; i<(y.size()-1); i++){
    nombre.append(y[i] + espacio);
  }
 
  std::wstring numero = y[y.size()-1];
  for(int i=0; i<numero.length(); i++){
    if(numero.at(i)=='$'){
      numero.erase(numero.begin() + i);
      i--;
    }
  }
  int valor = std::stoi(numero);  
  
  return std::make_tuple(nombre,valor);
}

