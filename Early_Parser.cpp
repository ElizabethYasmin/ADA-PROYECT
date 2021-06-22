#include <iostream>
#include <vector>
#include <fstream>
#include "estado.cpp"

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
                //probar cambiando a S[k].push_back(estado(temp.getProduccion(),0,k));
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
    std::cout<<"\n=============Parser_Finalizado=============\n";
    return 0;
}
