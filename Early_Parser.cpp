/*==========================
EARLY PARSER  
============================
Implementacion por:
+Ccorahua Lozano Rommel
+Huanca Parqui Elizabeth Yasmin
+Villanueva Guerrero Luisa
*/


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

class produccion {
private:
    std::string izquierda;
    std::string derecha;
public:
    produccion(std::string produccion, int k, int j){
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
};

class Grammar{
private:
    std::vector<produccion>listaDeProducciones;
};


/*
estado_entrada
produccion => produccion
i => posicion del * de parser
origen = S[k]
*/
class estado{
private:
    std::string produccion;
    int i; //posicion del punto de early
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
    //b -> A * Va
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

        /*Devuelve el elemento despues del '*' */
    std::string getElement(int n){ 
        std::string temp;
        int cont=0;
        int k;
        //cuenta los espacios
        for(k=0; cont<n && k<derecha.length();k++){
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

    friend ostream& operator<<(ostream& os, const estado& dt);
};

ostream& operator<<(ostream& os, const estado& dt){
    os << dt.izquierda << " => " <<  dt.derecha << " punto: " << dt.i << " origen: " << dt.origen;
    return os;
}

//verifica que el estado_entrada que se inserte en S no este repetido
bool estaRepetido(std::vector<estado> S,estado estado_entrada,int k){
    for (auto it = S.begin(); it != S.end(); it++){
        estado temp = *it;
        if(temp.getProduccion() == estado_entrada.getProduccion() && temp.getDotPosition() == k)
            return 1;
    }
    return 0;
}

void predecir(estado temp ,std::vector<estado> S[], int k, std::vector<estado> Grammar){
   /* form (X → α • Y β, j) , add (Y → • γ, k) */
    std::string Y = temp.getNextElement();
    for (auto it = Grammar.begin(); it != Grammar.end(); it++){
        estado temp = *it;
        if(temp.getIzquierda()==Y && !estaRepetido(S[k],temp,temp.getDotPosition())){
                //std::cout<<"++ Anhadiendo "<<temp<<" al estado_entrada "<<k<<std::endl; 
                S[k].push_back(estado(temp.getProduccion(),temp.getDotPosition(),k));
            
        }
    }
}

/*
a => the next symbol in the input stream
*/

/*
a = number* + number 
estado_entrada = estado_entrada no terminal = T → • number
s = charts 
*/
void scanneo(std::string a ,std::vector<estado> S[], int k, estado estado_entrada,std::vector<estado> grammar){
    std::string b = estado_entrada.getNextElement();
    std::cout<<"Scanean ..."<<a<<" =? "<<b<<std::endl;
    // X → α • a β, j , add (X → α a • β, j) to S(k+1) 

    if((a==b) && !estaRepetido(S[k+1],estado_entrada,k+1)){
        //caso 1= elemento no terminal sin produccion
        S[k+1].push_back(estado(estado_entrada.getProduccion(),estado_entrada.getDotPosition()+1,estado_entrada.getOrigen()));
    }
    else {
        //caso 1= elemento no terminal con produccion
    for (auto it = grammar.begin(); it != grammar.end(); it++){
        estado temp = *it; 
        std::cout<<"Elemento: "<<temp.getIzquierda()<<"\n";
        if(temp.getIzquierda() == b && temp.getDerecha()==a && !estaRepetido(S[k+1],temp,k+1)){
            S[k+1].push_back(estado(temp.getProduccion(),temp.getDotPosition()+1,k));
        }
    }
    }



}
/*
character => parte izquierda de la produccion del estado_entrada
*/
void completar(std::vector<estado> S[],int k, estado estado_entrada){
    for (auto it2 = S[estado_entrada.getOrigen()].begin(); it2 != S[estado_entrada.getOrigen()].end(); it2++){
            estado temp2 = *it2;
            //std::cout<<"Y: "<<temp.getIzquierda()<<" compare "<<temp2.getNextElement()<<std::endl;
            if(estado_entrada.getIzquierda() == temp2.getNextElement()  && !estaRepetido(S[k],temp2,temp2.getDotPosition()+1) ){
                //std::cout<<"++ Anhadiendo "<<temp2<<" al estado_entrada "<<k<<std::endl; 
                S[k].push_back(estado(temp2.getProduccion(),temp2.getDotPosition()+1,temp2.getOrigen()));
            }
        }
}

bool esterminal(std::vector<estado> G, std::string caracter){
    for (auto it = G.begin(); it != G.end(); it++){
        estado temp2 = *it;
        if(temp2.getIzquierda()==caracter){
            if(temp2.getlength()!=1)
                return 0;
            else {
                for (auto it2 = G.begin(); it2 != G.end(); it2++){
                    estado temp3 = *it2;
                    if(temp3.getIzquierda()==temp2.getDerecha())
                        return 0;
                }
                return 1;
            }         
        }
    }
    return 1;
}

bool terminado(estado S){
    //std::cout<<"El punto esta al final? "<<S.getDotPosition()<<" "<<S.getlength()<<std::endl;
    if(S.getDotPosition()>=S.getlength())
        return 1;
    return 0;
}
//devuelve el elemento n de la entrada
std::string elementoNdeEntrada(std::string A,int n){
    std::string temp;
    int cont = 0;
    int i;
    //cuenta n espacios y aumenta el pivote i en la entrada
    for(i=0; cont<n && i<A.length();i++){
        if(A[i]==32){
            cont++;
        }
    }
    //a partir de la posicion i, devuelva el caracter hasta encontrar un espacio
    for(int j=i; A[j]!=32 && j<A.length();j++){
        temp += A[j];
    }
    return temp;
}
//devuelva el numero de caracteres que tiene la entrada
int tamanoDeEntrada(std::string A){
    int cont = 0;
    for(int i = 0 ; i<A.size() ; i++){
        if(A[i]==32)
            cont ++;
    }
    return cont+1;
}

/*
A => entrada
G => producciones
*/
int early_parser(std::string A , std::string Grammar[],int n_proposiciones){
    std::ofstream myfile;
    myfile.open("salida_early_parser.txt");
    if (myfile.is_open()){

    int tamanoEntrada=tamanoDeEntrada(A);
    std::vector<estado> grammar;
    //std::cout<<"Creando gramatica..\n"<<n_proposiciones;
    for(int i=0 ; i<n_proposiciones ; i++){
        grammar.push_back(estado(Grammar[i],0,0));
    }
    //std::cout<<"Creando S(k). .\n";
    //creacion de estado_entradas
    std::vector<estado> S[tamanoEntrada+1];
    //agrega todos los axiomas a S[0]
    std::string axioma = grammar.at(0).getIzquierda();
    for (auto it = grammar.begin(); it != grammar.end(); it++){
        estado temp = *it;
        if(axioma==temp.getIzquierda()){
            S[0].push_back(estado(temp.getProduccion(),0,0));
        }
    }
    //recorre el punto en posicion i de la entrada hasta el final 
    for(int i= 0 ; i<tamanoEntrada+1 ; i++){
        myfile<<"========================S: "<<i<<"======================"<<std::endl;
        for (int j = 0; j<S[i].size() ; j++){
            auto temp = S[i].at(j);
            myfile<<"estado_entrada:"<<j<<" =>>>> "<<temp<<std::endl;
            //si el punto de early no esta en el final
            //myfile<<"elemento a analizar: "<<temp.getNextElement();
            if(!terminado(temp)){
                if(!esterminal(grammar,temp.getNextElement())){
                    //myfile<<" no es terminal.\n-------Prediciendo ...\n";
                    predecir(temp,S,i,grammar);
                }
                else{
                    //myfile<<" es terminal.\n-------Escaneando ...\n";
                    scanneo(elementoNdeEntrada(A,i),S,i,temp,grammar); 
                }
            }
            else{
                //myfile<<"\n--------Completando ...\n";
                completar(S,i,temp);
            }
        }
    }

    myfile<<"=============Finalizado==============\n";
    }
    return 0;
}

int main(){
    /*
    //Ejemplo Wikipedia
    std::string A = "number *+ number * number";
    std::string G[] = {
        "P ::= *S" ,
        "S ::= S *+ M", 
        "S ::= *M" ,
        "M ::= M * T" ,
        "M ::= T" ,
        "T ::= number" ,
        
    };
    early_parser(A,G,6);
*/
   /*
    //Ejemplo YT: https://www.youtube.com/watch?v=WNKw1tiskSM&t=1622s
    std::string A = "1 + 1";
    std::string G[] = {
        "term ::= number + term" ,
        "term ::= number", 
        "number ::= 1" 
    };
    early_parser(A,G,3);
    */
   
    //Ejemplo YT: https://www.youtube.com/watch?v=1j6hB3O4hAM&t=462s
    std::string A = "book that flight";
    std::string G[] = {
        "S ::= NP VP" ,
        "S ::= VP", 
        "NP ::= det nominal" ,
        "nominal ::= noun" , 
        "VP ::= verb" ,
        "VP ::= verb NP" ,
        "det ::= that" ,
        "det ::= this" ,
        "det ::= a" ,
        "det ::= the" ,
        "noun ::= book" ,
        "noun ::= flight" ,
        "noun ::= meal" ,
        "noun ::= money" ,
        "verb ::= book" ,
        "verb ::= include" ,
        "verb ::= prefer" ,
    };
/*
    Grammar Terminales;
    Grammar NoTerminales;
*/
    early_parser(A,G,17);
    
    /*
    int tamanoEntrada=tamanoDeEntrada(A);
    std::vector<estado> grammar;
    //std::cout<<"Creando gramatica..\n"<<n_proposiciones;
    for(int i=0 ; i<17 ; i++){
        grammar.push_back(estado(G[i],0,0));
    }
    //std::cout<<getTerminal("NP",grammar).size();
    //std::cout<<esterminal(grammar,"nominal");*/
    return 0;
}