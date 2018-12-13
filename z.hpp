#ifndef Z_H_INCLUDED
#define Z_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <typeinfo>
#include <tuple>

//Esta función lee un archivo tipo Z y separa sus caracteres que no son de tipo espacio en wstring. Además que también los separa en líneas.
std::vector<std::vector<std::wstring> > z_leer(const char* name);
//Esta función separa el archivo Z ya leído en sus partes de REG, PMG, etc.
std::vector<std::vector<std::vector<std::wstring> > > z_partes(std::vector<std::vector<std::wstring> > &y);
//Esta función guarda (en este orden) el año, el mes, el día, la hora, el minuto, el número de comprador y los productos vendidos (estos en un vector) en una tupla, la cual esta dentro de un vector para tener todo organizado. Dentro del vector que esta en la tupla habitan tuplas que contienen la información de cada venta
std::vector<std::tuple<std::wstring, std::wstring, std::wstring, std::wstring, std::wstring, int, std::vector<std::tuple<std::wstring, int, int, int> > > > z_REG(std::vector<std::vector<std::vector<std::wstring> > > &y);

std::vector<std::vector<std::wstring> > z_leer(const char* name)
{
  char *locale = setlocale(LC_ALL, "");
  FILE *pFile = fopen(name, "r");
  
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

  fclose(pFile);

  return y;
}


std::vector<std::vector<std::vector<std::wstring> > > z_partes(std::vector<std::vector<std::wstring> > &y)
{
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

  return v;
}

std::vector<std::tuple<std::wstring, std::wstring, std::wstring, std::wstring, std::wstring, int, std::vector<std::tuple<std::wstring, int, int, int> > > > z_REG(std::vector<std::vector<std::vector<std::wstring> > > &y)
{
  std::vector<std::vector<std::vector<std::wstring> > > v;
  for(int i=0; i<y.size(); i++){
    if(y[i][0][0] == L"REG"){
      v.push_back(y[i]);
    }
  }

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
}

#endif
