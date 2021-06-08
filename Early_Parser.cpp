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
    produccion(std::string produccion){
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
    friend ostream& operator<<(ostream& os, const produccion& dt);
    friend bool operator!=(produccion const& x, produccion const& y);
};

ostream& operator<<(ostream& os, const produccion& dt){
    os << dt.izquierda << " => " <<  dt.derecha;
    return os;
}

bool operator!=(produccion const& x, produccion const& y)
{
    if(x.izquierda == y.izquierda && x.derecha == y.derecha)
        return false;
    else 
        return true;
}

class Grammar{
private:
    std::vector<produccion>producciones_terminales;
    std::vector<produccion>producciones_no_terminales;
public:
    Grammar(std::string G[],int n);
    void print();
    
};

void Grammar::print(){
    std::cout<<"No terminales:\n";
    for (auto it = producciones_no_terminales.begin(); it != producciones_no_terminales.end(); it++){
        std::cout<<*it<<std::endl;
    }
    std::cout<<"Terminales:\n";
    for (auto it = producciones_terminales.begin(); it != producciones_terminales.end(); it++){
        std::cout<<*it<<std::endl;
    }

}

/*
G ->lista producciones no procesadas (forma 'izquierda' ::= 'derecha' )
n -> numero de producciones
*/
Grammar::Grammar(std::string G[],int n){
    std::vector<produccion> lista_de_producciones;
    for(int i=0;i<n;i++)
        lista_de_producciones.push_back(produccion(G[i]));
    
    for (int i = 0; i<lista_de_producciones.size() ; i++){
        int cont=0;
        produccion temp1 = lista_de_producciones.at(i);
        //es produccion no terminal?
        //si tiene mas de un caracter en la derecha no es terminal
        if(temp1.getlength()>1){
            cont++;
            producciones_no_terminales.push_back(temp1);
        }
        //si tiene un caracter en la derecha se verifica que este caracter no tenga produccion
        else{
            std::string temp2 = temp1.getDerecha();
            //buscando en las produccion que no haya una produccion del caracter derecho
            for (int j = 0; j<lista_de_producciones.size() ; j++){
                produccion temp3 = lista_de_producciones.at(j);
                if(temp2 == temp3.getIzquierda()){
                    cont++;
                    producciones_no_terminales.push_back(temp1);
                    break;
                }
            }
        }
        if(cont==0)
            producciones_terminales.push_back(temp1);
    }
} 

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

/*
verifica que el estado que se inserte en S no este repetido
S => verificar en chart
estdo => estado averificar
k => posicon del punto
*/
bool estaRepetido(std::vector<estado> S,estado estadoA,int k){
    for (auto it = S.begin(); it != S.end(); it++){
        estado temp = *it;
        if(temp.getProduccion() == estadoA.getProduccion() && temp.getDotPosition() == k)
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
                //std::cout<<"++ Anhadiendo "<<temp<<" al estado "<<k<<std::endl; 
                S[k].push_back(estado(temp.getProduccion(),temp.getDotPosition(),k));
            
        }
    }
}

/*
a => the next symbol in the input stream
*/

void scanneo(std::string a ,std::vector<estado> S[], int k, estado estadoA,std::vector<estado> grammar){
    std::string b = estadoA.getNextElement();
//    std::cout<<"Scanean ..."<<a<<" =? "<<b<<std::endl;
//    std::cout<<" ESTADO: "<<estadoA<<std::endl;
    // X → α • a β, j , add (X → α a • β, j) to S(k+1) 

    if((a==b) && !estaRepetido(S[k+1],estadoA,estadoA.getDotPosition()+1)){
        //caso 1= elemento no terminal sin produccion
//        std::cout<<"caso 1= elemento no terminal sin produccion"<<std::endl;
//        std::cout<<"+anadiendo: "<<estadoA.getProduccion()<<" a estado: " <<k+1<<std::endl;
        S[k+1].push_back(estado(estadoA.getProduccion(),estadoA.getDotPosition()+1,estadoA.getOrigen()));
    }
    else {
            //caso 2= elemento no terminal con produccion
//            std::cout<<"caso 2= elemento no terminal con produccion"<<std::endl;
        for (auto it = grammar.begin(); it != grammar.end(); it++){
            estado temp = *it; 
//            std::cout<<"Elemento: "<<temp.getIzquierda()<<"\n";
//            std::cout<<"Verificando que: "<<temp<< "origen en: "<<k<<" no este en estado: "<<k+1<<std::endl;
            if(temp.getIzquierda() == b && temp.getDerecha()==a && !estaRepetido(S[k+1],temp,temp.getDotPosition()+1)){
//                 std::cout<<"+anadiendo: "<<temp<<"origen en: "<<k<<" a estado: " <<k+1<<std::endl;
                S[k+1].push_back(estado(temp.getProduccion(),temp.getDotPosition()+1,k));
            }
        }
    }
}
/*
character => parte izquierda de la produccion del estado
*/
void completar(std::vector<estado> S[],int k, estado estadoA){
    for (auto it2 = S[estadoA.getOrigen()].begin(); it2 != S[estadoA.getOrigen()].end(); it2++){
            estado temp2 = *it2;
            //std::cout<<"Y: "<<temp.getIzquierda()<<" compare "<<temp2.getNextElement()<<std::endl;
            if(estadoA.getIzquierda() == temp2.getNextElement()  && !estaRepetido(S[k],temp2,temp2.getDotPosition()+1) ){
                //std::cout<<"++ Anhadiendo "<<temp2<<" al estado "<<k<<std::endl; 
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
/*
Si el punto de early esta al final de la parte derecha
*/
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
n -> numero de charts
*/
void imprimirChats(std::vector<estado>S[],int n){
    std::ofstream myfile;
    myfile.open("salida_early_parser.txt");
    if (myfile.is_open()){

        for(int i=0;i<n;i++){
            myfile<<"========================S: "<<i<<"======================="<<std::endl;
                for (int j = 0; j<S[i].size() ; j++){
                    auto temp = S[i].at(j);
                    myfile <<"Estado "<<j<<" | "<< temp <<std::endl;
                }
        }
        myfile<<"======================Terminado===================="<<std::endl;
    }
}

/*
A => entrada
G => producciones
*/
int early_parser(std::string A , std::string Grammar[],int n_proposiciones){

    int tamanoEntrada=tamanoDeEntrada(A);
    std::vector<estado> grammar;
    //std::cout<<"Creando gramatica..\n"<<n_proposiciones;
    for(int i=0 ; i<n_proposiciones ; i++){
        grammar.push_back(estado(Grammar[i],0,0));
    }
    //std::cout<<"Creando S(k). .\n";
    //creacion de estados
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
//        std::cout<<"========================S: "<<i<<"======================"<<std::endl;
        for (int j = 0; j<S[i].size() ; j++){
            auto temp = S[i].at(j);

//            std::cout<<"estado:"<<j<<" =>>>> "<<temp<<std::endl;
            //si el punto de early no esta en el final
            //myfile<<"elemento a analizar: "<<temp.getNextElement();
            if(!terminado(temp)){
                if(!esterminal(grammar,temp.getNextElement())){
//                    std::cout<<" no es terminal.\n-------Prediciendo ...\n";
                    predecir(temp,S,i,grammar);
                }
                else{
//                    std::cout<<" es terminal.\n-------Escaneando ...\n";
                    scanneo(elementoNdeEntrada(A,i),S,i,temp,grammar); 
                }
            }
            else{
//                std::cout<<"\n--------Completando ...\n";
                completar(S,i,temp);
            }
        }
    }
    imprimirChats(S,tamanoEntrada+1);
    return 0;

}


int main(){
   /*
    //Ejemplo Wikipedia
    std::string A = "number + number * number";
    std::string G[] = {
        "P ::= S" ,
        "S ::= S + M", 
        "S ::= M" ,
        "M ::= M * T" ,
        "M ::= T" ,
        "T ::= number" ,
        
    };
   // early_parser(A,G,6);
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
   // early_parser(A,G,17);
    
    /*
    produccion test0("verbo ::= the hola");
    std::cout<<test0.getDerecha();
    */
   
    Grammar test1(G,3);
    test1.print();

    return 0;
}