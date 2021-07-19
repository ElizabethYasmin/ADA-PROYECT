#include <iostream>
#include <vector>
#include <string>
#include <vector>
using namespace std;

class produccion {
private:
    string _produccion;
    //NTerminal izquierda;
    vector<NTerminal> derecha;
public:
    NTerminal izquierda;
    produccion(string);
    produccion(string,string);
    NTerminal getIzquierda();
    vector<NTerminal> getDerecha(); 
    int getlength(); 
    bool compare(std::string,std::map<std::string,std::string>);
    void deleteAtributos();
    //devuelva la cantidad de elementos a la derecha de la produccion
    friend ostream& operator<<(ostream& os, const produccion& dt);
    friend bool operator!=(produccion const& x, produccion const& y);
};

produccion::produccion(string _produccion){
    int i;
    string izq,der;
    this -> _produccion = _produccion;
    int breakk= 0;
    //ubica la posicion de separacion (::=)     
    for(int i=0 ; i<_produccion.length() ; i++){
        if (_produccion[i]==':') {
            breakk=i; 
            break;
        }
    }
    //extrae el lado izquierdo
    for(i ; i<breakk ; i++){
            izq += _produccion[i];
    }
    izquierda=NTerminal(izq);

    //extrae el lado derecho
    for (i=breakk+4; i<_produccion.length();i++){
        if(_produccion[i]==32){
            derecha.push_back(NTerminal(der));
            der="";
        }
        else der += _produccion[i];
    }
    derecha.push_back(NTerminal(der));
}

produccion::produccion(string izq,string _der){
    string der;
    izquierda=NTerminal(izq);

    //extrae el lado derecho
    for(int i=0; i<_der.length();i++){
        if(_der[i]==32){
            derecha.push_back(NTerminal(der));
            der="";
        }
        else der += _der[i];
    }
    derecha.push_back(NTerminal(der));
}

int produccion::getlength(){
    return derecha.size();
}


NTerminal produccion::getIzquierda(){
    return izquierda;
}

vector<NTerminal> produccion::getDerecha(){
    return derecha;
}

void produccion::deleteAtributos(){
    izquierda.deleteAtributos();
}

ostream& operator<<(ostream& os, const produccion& dt){
    os << dt.izquierda << " => ";
    for (auto it =dt.derecha.begin(); it != dt.derecha.end(); it++)
        os << *it<<" ";
    return os;
}
