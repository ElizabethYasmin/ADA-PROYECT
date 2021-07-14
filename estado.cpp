#include <iostream>
#include <string>
#include "Nterminal.cpp"
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
    string produccion;
    int punto;
    int origen;
    NTerminal izquierda;
    vector<NTerminal> derecha;
public: 
    estado(string,int,int);
    NTerminal getIzq();
    NTerminal getNextElement();
    int getlength();
    NTerminal getNextElement();
    NTerminal getIzquierda();
    int getDotPosition(){ 
        return punto;
    }
    int getOrigen(){ 
        return origen;
    }
    string getProduccion(){
        return produccion;
    }
    friend ostream& operator<<(ostream& os, const estado& dt);
    friend bool operator!=(string &a,string &b);
};

estado::estado(string _produccion,int _punto,int _origen){
    punto = _punto;
    origen = _origen;
    int i;
    string izq,der;
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
    //cout<<"izquierda: "<<izquierda<<" break: "<<breakk<<endl;
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

NTerminal estado::getIzquierda(){
    return izquierda;
}

ostream& operator<<(ostream& os, const estado& dt){
    os << dt.izquierda << " => ";
    for (auto it =dt.derecha.begin(); it != dt.derecha.end(); it++)
        os << *it;
    os <<", Punto: "<<dt.punto <<", Origen: "<<dt.origen <<".";
    return os; 
}

 bool operator!=(string &a,string &b){
 }



