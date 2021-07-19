#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
estado
produccion => produccion
i => posicion del * de parser
origen = S[k]
*/
class estado{
private:
    int punto;
    int origen;
    NTerminal izquierda;
    vector<NTerminal> derecha;
public: 
    estado(string,int,int);
    estado(produccion,int,int);
    estado(estado,int,int);
    NTerminal getIzq();
    NTerminal getNextElement();
    int getlength();
    NTerminal getIzquierda();
    vector<NTerminal> getDerecha(); 
    int getDotPosition(){ 
        return punto;
    }
    int getOrigen(){ 
        return origen;
    }
    friend ostream& operator<<(ostream& os, const estado& dt);
    friend bool operator!=(string &a,string &b);
};

estado::estado(string _produccion,int _punto,int _origen){
    punto = _punto;
    origen = _origen;
    int i;
    string izq,der;
    //this -> produccion = _produccion;
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

estado::estado(produccion _produccion,int _punto,int _origen){
    punto = _punto;
    origen = _origen;
    izquierda = _produccion.getIzquierda();
    derecha = _produccion.getDerecha();
}

estado::estado(estado _estado,int _punto,int _origen){
    punto = _punto;
    origen = _origen;
    izquierda = _estado.getIzquierda();
    derecha = _estado.getDerecha();
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

NTerminal estado::getIzquierda(){
    return izquierda;
}

vector<NTerminal> estado::getDerecha(){
    return derecha;
}

ostream& operator<<(ostream& os, const estado& dt){
    os << dt.izquierda << " => ";
    for (auto it =dt.derecha.begin(); it != dt.derecha.end(); it++)
        os << *it<<" ";
    os <<", Punto: "<<dt.punto <<", Origen: "<<dt.origen <<".";
    return os; 
}
