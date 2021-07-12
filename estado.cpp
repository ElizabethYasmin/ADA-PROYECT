#include <iostream>
#include "Nterminal.cpp"
#include <vector>
/*
estado
produccion => produccion
i => posicion del * de parser
origen = S[k]
*/
class estado{
private:
    std::string produccion;
    int punto;
    int origen;
    NTerminal izquierda;
    std::vector<NTerminal> derecha;
public: 
    estado(std::string,int,int);
    NTerminal getIzq();
    NTerminal getNextElement();
    int getlength();

    int getDotPosition(){ 
        return punto;
    }
    int getOrigen(){ 
        return origen;
    }
    std::string getProduccion(){
        return produccion;
    }
    friend std::ostream& operator<<(std::ostream& os, const estado& dt);
};

estado::estado(std::string _produccion,int _punto,int _origen){
    punto = _punto;
    origen = _origen;
    int i;
    std::string izq,der;
    this -> produccion = _produccion;
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

NTerminal estado::getNextElement(){
    return derecha.at(punto);
}

NTerminal estado::getIzq(){
    return izquierda;
}

int estado::getlength(){
    return derecha.size();
}

std::ostream& operator<<(std::ostream& os, const estado& dt){
    os << dt.izquierda << " => ";
    for (auto it =dt.derecha.begin(); it != dt.derecha.end(); it++)
        os << *it;
    os <<", Punto: "<<dt.punto <<", Origen: "<<dt.origen <<".";
    return os; 
}

/*
    tareas:
    *sobrecargar operador != para la clase estado
    *sacar los metodos de la la clase
*/

