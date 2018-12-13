#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <typeinfo>

int main(void)
{
  char *locale = setlocale(LC_ALL, "");
  FILE *pFile = fopen("EJ051218.TXT", "r");
  
  wint_t c;
  std::vector<std::vector<std::wstring> > y;
  std::wstring ws;
  int i=0;
  y.push_back( std::vector<std::wstring>() );

  while((c = fgetwc(pFile)) != WEOF){
    if(c == L'\n'){
      y.push_back( std::vector<std::wstring>() );
      i++;
    }
    if(iswspace(c)){
      if(ws.length()!=0){
	y[i].push_back(ws);
      }
      ws.clear();
    }
    else{
      ws.push_back(c);
    }
  }
  
  std::vector<std::vector<std::vector<std::wstring> > > v;
  v.push_back( std::vector<std::vector<std::wstring> >() );
  int k=0;
  int l=0;
  for(int i=0; i<y.size(); i++){
    v[k].push_back( std::vector<std::wstring>() );
    for(int j=0; j<y[i].size(); j++){
      if(y[i][j] == L"REG" || y[i][j] == L"PGM" || y[i][j] == L"X" || y[i][j] == L"Z" || y[i][j] == L"_PSD" || y[i][j] == L"OFF" || y[i][j] == L"------------------------"){
	v.push_back( std::vector<std::vector<std::wstring> >() );
	k++;
	v[k].push_back( std::vector<std::wstring>() );
	l = 0;
      }
      v[k][l].push_back(y[i][j]);
    }
    l++;
  }

  v.erase(v.begin() + 0);
  
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

  fclose(pFile);

  std::wstring num1(L"3900");
  std::wstring num2(L"-1");
  std::wstring num3(L"00005");
  
  int i1 = std::stoi(num1);
  int i2 = std::stoi(num2);
  int i3 = std::stoi(num3);
  std::wcout << num1 << '\t' << i1 << std::endl;
  std::wcout << num2 << '\t' << i2 << std::endl;
  std::wcout << num3 << '\t' << i3 << std::endl;
  return 0;
}
