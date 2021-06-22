#include <iostream>
#include <map>
#include <vector>
/*
tareas:
Leer Gramatica Dependiente del Contexto
Or
separar tokens?

pa' saber:
map es un contenedor asociativo para contener en orden una
lista de parejas de valores únicos asociados como clave/valor.

class NTerminal {
  string lexema;
  map<string,string>
}

void NTerminal::read(string | ios)
void NTerminal::operator==( NTerminal &nterminal )
void NTerminal::operator==( string )
*/

class NTerminal {
private:
  std::string lexema;
  //std::map<std::string,std::string> Map;
  std::map<int,std::string> derecha;

public:
  NTerminal(std::string);
  void read(std::string ios);
  void operator==(NTerminal &nterminal );
  void operator==(std::string );

  friend std::ostream& operator<<(std::ostream& os, const NTerminal& dt);
  friend NTerminal operator==(NTerminal&, NTerminal&);
  friend NTerminal operator==(NTerminal&, std::string&);
};

NTerminal::NTerminal(std::string produccion){
    int i,breakk;
    for(i=0 ; i<produccion.length() ; i++){
        if(produccion[i+1]==':')
            break;
        lexema+=produccion[i];
    }
    std::string temp;
    int j=0;
    for(i=i+5 ; i<produccion.length() ; i++){
        if(produccion[i]==32){
            derecha.insert({ j, temp });
            j++; temp = "";
        }
        else temp+=produccion[i];
    }
    derecha.insert({ j, temp });
}

NTerminal operator==(NTerminal& d1, std::string d2){
    
}

std::ostream& operator<<(std::ostream& os, const NTerminal& dt){
    os << dt.lexema<<". =>. ";
    for (const auto &p : dt.derecha)
    {
        /*Manera 1
        os << p.first << ": "<<p.second;
        os << std::endl;
        */
       //Manera 2
       os <<p.second<<".";
    }
    return os;
}
