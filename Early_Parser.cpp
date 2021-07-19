#include <iostream>
#include <vector>
#include <fstream>

/*
verifica que el estado que se inserte en S no este repetido
S => verificar en chart
estadoA => estado averificar
k => posicon del punto
*/
bool estaRepetido(chart S,estado estadoA,int punto_parser){
    for (auto it = S.estados.begin(); it != S.estados.end(); it++){
        estado temp = *it;
        if(temp.getDerecha() == estadoA.getDerecha() 
        && temp.getIzquierda() == estadoA.getIzquierda() 
        && temp.getDotPosition() == punto_parser)
            return 1;
    }
    return 0;
}

bool estaRepetido(chart S, produccion estadoA){
    for (auto it = S.estados.begin(); it != S.estados.end(); it++){
        estado temp = *it;
        if(temp.getDerecha() == estadoA.getDerecha() && temp.getIzquierda() == estadoA.getIzquierda())
            return 1;
    }
    return 0;
}

/*
busca en la gramitca
punto de early en 0
*/
void predecir(estado _temp ,chart S[], int k, grammar gramatica){
 //  form (X → α • Y β, j) , add (Y → • γ, k) 
    NTerminal Y = _temp.getNextElement();
    for (auto it = gramatica.producciones_no_terminales.begin(); it != gramatica.producciones_no_terminales.end(); it++){
        produccion temp = *it;
        if(temp.getIzquierda().getLexema()==Y.getLexema() && !estaRepetido(S[k],temp)){
            if(Y.getAtributos().empty()){  //si no tiene contexto
                temp.deleteAtributos();
                S[k].addEstado(estado(temp,0,k));
            }
            else
                S[k].addEstado(estado(temp,0,k));    
        }
    }
}

void scanneo(std::string a ,chart S[], int k, estado estadoA,grammar gramatica){
    std::string b = estadoA.getNextElement().getLexema();
    // X → α • a β, j , add (X → α a • β, j) to S(k+1) 
    if((a==b && !estaRepetido(S[k+1],estadoA,estadoA.getDotPosition()+1))){
        //caso 1= elemento no terminal sin produccion
        S[k+1].addEstado(estado(estadoA,estadoA.getDotPosition()+1,estadoA.getOrigen()));
    }
    else {
        //caso 2= elemento no terminal con produccion
        for (auto it = gramatica.producciones_terminales.begin(); it != gramatica.producciones_terminales.end(); it++){
            produccion temp = *it; 

            if(estadoA.getIzquierda().getAtributos().empty()){ //no tiene contexto
                if(temp.getIzquierda().getLexema() == b 
                && temp.getDerecha().at(0).getLexema() == a
                && !estaRepetido(S[k+1],temp)){
                    S[k+1].addEstado(estado(temp,1,estadoA.getOrigen()));
                 }
            }
            else{ //tiene contexto
                if(temp.getIzquierda()==NTerminal(b,S[k].getAtributos()) 
                && temp.getDerecha().at(0).getLexema() == a
                && !estaRepetido(S[k+1],temp)){
                    S[k+1].addEstado(estado(temp,1,estadoA.getOrigen()));
                    S[k+1].setAtributo(temp.getIzquierda().getAtributos());
                }
            }
        }
    }
}

//Si el punto de early esta al final de la parte derecha
bool terminado(estado S){
    if(S.getDotPosition()>=S.getlength())
        return 1;
    return 0;
}

/*
character => parte izquierda de la produccion del estado'
busca en el origen del estado
*/
void completar(chart S[],int k, estado estadoA){
    for (auto it2 = S[estadoA.getOrigen()].estados.begin(); it2 != S[estadoA.getOrigen()].estados.end(); it2++){
            estado temp2 = *it2;
            if(!terminado(temp2) && estadoA.getIzquierda().getLexema() == temp2.getNextElement().getLexema()  
            && !estaRepetido(S[k],temp2,temp2.getDotPosition()+1) ){
                S[k].addEstado(estado(temp2,temp2.getDotPosition()+1,temp2.getOrigen()));
            }
        }
}

bool esterminal(grammar gramatica, NTerminal caracter){
    for (auto it = gramatica.producciones_no_terminales.begin(); it != gramatica.producciones_no_terminales.end(); it++){
        produccion temp = *it;
        if(temp.getIzquierda().getLexema()==caracter.getLexema()){
            return 0;
        }
    }
    return 1;
}

//devuelva el numero de caracteres que tiene la entrada
void procesar_entrada(vector<std::string>&entrada_salida,std::string entrada_entrada){
    int cont = 0;
    std::string temp;
    for(int i = 0 ; i<entrada_entrada.size() ; i++){
        if(entrada_entrada[i]==32){
            entrada_salida.push_back(temp);
            temp="";
        }
        else
            temp+=entrada_entrada[i];
    }
    entrada_salida.push_back(temp);
}

/*
resultado = 1 -> entrada aceptada
resultado = 0 -> entrada rechazada
*/
void imprimirS(chart S[],int n,std::string salida,int resultado){
    std::ofstream myfile;
    myfile.open(salida);
    if (myfile.is_open()){
        if(resultado==1){
            for(int i=0 ; i < n ; i++){
                myfile<<"S "<<i<<":\n";
                myfile<<S[i];
            }
        }
        else{
            myfile<<"Entrada no reconocida por la gramatica";
        }
    }
    else 
        std::cout << "Unable to open file"; 
}

/*
A => entrada
Grammar => producciones
*/
int early_parser(std::string A , std::string Grammar[],int n_proposiciones,std::string salida){
    grammar gramatica(Grammar,n_proposiciones);

    vector<std::string> entrada;
    procesar_entrada(entrada,A);
    chart S[entrada.size()+1];

    //agrega todos los axiomas a S[0], axioma es la produccion con la que se empieza
    std::string axioma = gramatica.producciones_no_terminales.at(0).getIzquierda().getLexema();
    //buscando el axioma en producciones no terminales
    for (auto it = gramatica.producciones_no_terminales.begin(); it != gramatica.producciones_no_terminales.end(); it++){
        produccion temp = *it;
        if(axioma==temp.getIzquierda().getLexema()){
            S[0].addEstado(estado(temp,0,0));
        }
    }
    //buscando el axioma en producciones terminales
    for (auto it = gramatica.producciones_terminales.begin(); it != gramatica.producciones_terminales.end(); it++){
        produccion temp = *it;
        if(axioma==temp.getIzquierda().getLexema()){
            S[0].addEstado(estado(temp,0,0));
        }
    }
    //mostrar axiomas
    //std::cout<<S[0];  

    //recorre el punto en posicion i de la entrada hasta el final 
    for(int i= 0 ; i<entrada.size()+1 ; i++){//recorre S (equivale a recorrer cada espacio de la entrada)
        for (int j = 0; j<S[i].estados.size() ; j++){//recorre los estados del chart
            auto temp = S[i].estados.at(j);

            if(!terminado(temp)){
                if(!esterminal(gramatica,temp.getNextElement())){
                    predecir(temp,S,i,gramatica);
                }
                else{
                    scanneo(entrada.at(i),S,i,temp,gramatica); 
                }
            }
            else{
                completar(S,i,temp);
            }
        }
        if(S[i+1].estados.size()==0) { 
             imprimirS(S,entrada.size()+1,salida,0);
            std::cout<<"\nCadena no reconocida";
            return 0;
        }
    }
    imprimirS(S,entrada.size()+1,salida,1);
    std::cout<<"\n=============Parser_Finalizado=============\n";

    return 1;
}
