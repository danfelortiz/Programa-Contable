#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <typeinfo>

bool deteccion(std::wstring ws, wchar_t signo);

int main(void)
{
  std::wstring num1(L"3900");
  std::wstring num2(L"-1");
  std::wstring num3(L"00005");
  
  int i1 = std::stoi(num1);
  int i2 = std::stoi(num2);
  int i3 = std::stoi(num3);
  std::wcout << num1 << '\t' << i1 << std::endl;
  std::wcout << num2 << '\t' << i2 << std::endl;
  std::wcout << num3 << '\t' << i3 << std::endl;

  std::wstring ws(L"$500");
  wchar_t signo = L'$';

  if(deteccion(num3,signo)){
    std::wcout << "true" << std::endl;
  }
  else {
    std::wcout << "false" << std::endl;
  }

  return 0;
}


bool deteccion(std::wstring ws, wchar_t signo)
{
  for(int i=0; i<ws.length(); i++){
    if(ws.at(i)==signo){
      return true;
    }
  }

  return false;
}
