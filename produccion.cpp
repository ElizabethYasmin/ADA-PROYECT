#include <iostream>
#include "Nterminal.cpp"
#include <vector>

class produccion {
private:
    std::string _produccion;
    NTerminal izquierda;
    std::vector<NTerminal> derecha;
public:
    produccion(std::string);
    produccion(std::string,std::string);
    std::string getIzquierda();
    std::string getDerecha(); 
    int getlength(); 
    //devuelva la cantidad de elementos a la derecha de la produccion
    friend std::ostream& operator<<(std::ostream& os, const produccion& dt);
    friend bool operator!=(produccion const& x, produccion const& y);
};

produccion::produccion(std::string _produccion){
    int i;
    std::string izq,der;
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
    //std::cout<<"izquierda: "<<izquierda<<" break: "<<breakk<<std::endl;
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

produccion::produccion(std::string izq,std::string _der){
    std::string der;
    izquierda=NTerminal(izq);
    //std::cout<<"izquierda: "<<izquierda<<" break: "<<breakk<<std::endl;
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

std::ostream& operator<<(std::ostream& os, const produccion& dt){
    os << dt.izquierda << " => ";
    for (auto it =dt.derecha.begin(); it != dt.derecha.end(); it++)
        os << *it<<" ";
    return os;
}

/*

Tarea:

bool operator!=(produccion const& x, produccion const& y){
    //falta
}

*/

//borrar esto
/*
int main(){
    produccion A("VP[TENSE=?t,NUM=?n]","IV[TENSE=?t,NUM=?n]");
    std::cout<<A;
}*/