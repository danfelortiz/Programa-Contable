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
//Esta función obtiene la hora y el minuto de la compra.
std::vector<std::wstring> hora_minuto(std::wstring &ws);
//Esta función me dice si el wstring ws contien el caracter signo.
bool deteccion(std::wstring ws, wchar_t signo);
//Esta función me genera una tuple con el nombre y el valor del producto.
std::tuple<std::wstring, int> nombre_valor(std::vector<std::wstring> &y);
//Esta función me guarda en una tupla la cantidad y el precio del producto.
std::tuple<int, int> cantidad_precio(std::vector<std::wstring> &y);
//Esta función guarda (en este orden) el año, el mes, el día, la hora, el minuto, el número de comprador y los productos vendidos (estos en un vector) en una tupla, la cual esta dentro de un vector para tener todo organizado. Dentro del vector que esta en la tupla habitan tuplas que contienen la información de cada venta
std::vector<std::tuple<std::wstring, std::wstring, int, std::vector<std::tuple<std::wstring, int, int, int> > > > z_REG(std::vector<std::vector<std::vector<std::wstring> > > &y);


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

  for(int i=0; i<v.size(); i++){
    v[i].pop_back();
  }

  return v;
}

std::vector<std::tuple<std::wstring, std::wstring, int, std::vector<std::tuple<std::wstring, int, int, int> > > > z_REG(std::vector<std::vector<std::vector<std::wstring> > > &y)
{
  std::vector<std::vector<std::vector<std::wstring> > > v;
  for(int i=0; i<y.size(); i++){
    if(y[i][0][0] == L"REG"){
      v.push_back(y[i]);
    }
  }

  for(int i=0; i<v.size(); i++){
    for(int j=0; j<v[i].size(); j++){
      for(int k=0; k<v[i][j].size(); k++){
	std::wcout << v[i][j][k] << ' ';
      }
      std::wcout << std::endl;
    }
    std::wcout << std::endl;
  }

  std::vector<std::tuple<std::wstring, std::wstring, int, std::vector<std::tuple<std::wstring, int, int, int> > > > venta;
  std::vector<std::wstring> tiempo;
  int comprador;
  std::tuple<std::wstring, int> producto;
  std::tuple<int, int> cantidad;

  for(int i=0; i<v.size(); i++){
    std::vector<std::tuple<std::wstring, int, int, int> > vect;
    for(int j=0; j<v[i].size(); j++){
      if(j==0){
	tiempo = hora_minuto(v[i][j][2]);
      }
      else if(j==1){
	comprador = std::stoi(v[i][j][0]);
      }
      else if(v[i][j][0] == L"ANULAR"){
	vect.pop_back();
	j += 2;
      }
      else if(v[i][j][0]!=L"EFECTIVO" && v[i][j][0]!=L"CAMBIO" && v[i][j][0].at(0)!='_' && v[i][j][0].at(0)!='#'){
	if(deteccion(v[i][j][v[i][j].size()-1],'$')){
	  producto = nombre_valor(v[i][j]);
	  cantidad = std::make_tuple(1,std::get<1>(producto)); 
	}
	else{
	  producto = nombre_valor(v[i][j+1]);
	  cantidad = cantidad_precio(v[i][j]);
	  j++;
	}
	//Aquí genero la tupla donde (en orden) aparecen el nombre, cantidad, precio unitario y valor total del producto.
	auto tuple = std::make_tuple(std::get<0>(producto), std::get<0>(cantidad), std::get<1>(cantidad), std::get<1>(producto));
	vect.push_back(tuple);
      }
    }
    auto informacion = std::make_tuple(tiempo[0],tiempo[1],comprador,vect);
    venta.push_back(informacion);
  }
  
  return venta;
}


std::vector<std::wstring> hora_minuto(std::wstring &ws)
{
  std::wstring delimiter = L":";
  size_t pos = ws.find(delimiter);
  std::wstring token = ws.substr(0, pos);
  std::vector<std::wstring> y;

  y.push_back(token);
  ws.erase(0, pos + delimiter.length());
  y.push_back(ws);
  
  return y;
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


std::tuple<std::wstring, int> nombre_valor(std::vector<std::wstring> &y)
{
  std::wstring nombre;
  std::wstring espacio (L" "); 
  for(int i=0; i<(y.size()-1); i++){
    nombre.append(y[i] + espacio);
  }
 
  std::wstring numero = y[y.size()-1];
  for(int i=0; i<numero.length(); i++){
    if(numero.at(i)=='$' || numero.at(i)==','){
      numero.erase(numero.begin() + i);
      i--;
    }
  }
  int valor = std::stoi(numero);  
  
  return std::make_tuple(nombre,valor);
}


std::tuple<int, int> cantidad_precio(std::vector<std::wstring> &y)
{
  y[0].pop_back();
  
  for(int i=0; i<y[2].length(); i++){
    if(y[2].at(i)==','){
      y[2].erase(y[2].begin() + i);
      i--;
    }
  }
  
  return std::make_tuple(std::stoi(y[0]), std::stoi(y[2]));
}


#endif
