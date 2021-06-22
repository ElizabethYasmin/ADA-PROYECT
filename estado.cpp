#include <iostream>

/*
estado
produccion => produccion
i => posicion del * de parser
origen = S[k]
*/
class estado{
private:
    std::string produccion;
    int i;
    int origen;
    std::string izquierda;
    std::string derecha;
public: 
    estado(std::string produccion, int k, int j){
        this -> produccion = produccion;
        i = k;
        origen = j;
        int breakk= 0;
        //ubica la posicion de separacion (::=)     
        for(int j=0 ; j<produccion.length() ; j++){
            if (produccion[j]==32) 
            {breakk=j; break;}
        }
        //extrae el lado izquierdo
            for(int j=0 ; j<breakk ; j++){
                izquierda += produccion[j];
        }
        //extrae el lado derecho
        for (int j=breakk+5; j<produccion.length();j++){
                derecha += produccion[j];
        }
    }
    int getDotPosition(){ 
        return i;
    }
    int getOrigen(){ 
        return origen;
    }
    std::string getProduccion(){
        return produccion;
    }
    /*Devuelve el elemento despues del '*' */
    std::string getNextElement(){ 
        std::string temp;
        int cont;
        int k;
        //cuenta los espacios
        for(k=0; cont<i && k<derecha.length();k++){
            if(derecha[k]==32){
                cont++;
            }
        }
        //extrae el elemento despues del espacio k
        for(int j=k; derecha[j]!=32 && j<derecha.length();j++){
            temp += derecha[j];
        }
        return temp;
    }
    std::string getIzquierda(){ 
        return izquierda;
    }
    std::string getDerecha(){ 
        return derecha;
    }

    //devuelva la cantidad de elementos a la derecha de la produccion
    int getlength(){
        int cont = 0;
        for(int i = 0 ; i<derecha.size() ; i++){
            if(derecha[i]==32)
                cont ++;
        }
        return cont+1;
    }
    friend std::ostream& operator<<(std::ostream& os, const estado& dt);
};

std::ostream& operator<<(std::ostream& os, const estado& dt){
    os << dt.izquierda << " => " <<  dt.derecha << " punto: " << dt.i << " origen: " << dt.origen;
    return os;
}
