#include <iostream>
#include <string>
#include <vector>
using namespace std;

class grammar{
public:
    vector<produccion>producciones_terminales;
    vector<produccion>producciones_no_terminales; 
    vector<produccion>lista_de_producciones; 
public:
    grammar(string G[],int n);
    void print();
    
};

void grammar::print(){
    cout<<"\nNo terminales:\n";
    for (auto it = producciones_no_terminales.begin(); it != producciones_no_terminales.end(); it++){
        cout<<*it<<"."<<endl;
    }
    cout<<"\nTerminales:\n";
    for (auto it = producciones_terminales.begin(); it != producciones_terminales.end(); it++){
        cout<<*it<<"."<<endl;
    }
}

/*
G ->lista producciones no procesadas (forma 'izquierda' ::= 'derecha' )
n -> numero de producciones
*/
grammar::grammar(string G[],int n){
    for(int i=0;i<n;i++){//recorre cada produccion en la lista
        int j;
        string izquierda, derecha;
        for(j=0 ; j<G[i].length() ; j++){ //separa el lado izquierdo
            if(G[i][j+1]!=':'){
                izquierda += G[i][j];
            }
            else{
                j+=5;
                break;
            }
        }
        for(j; j<G[i].length() ; j++){
            if(G[i][j]=='|' && G[i][j+1]=='|'){
                lista_de_producciones.push_back(produccion(izquierda,derecha));
                derecha = "";
                j++;
            }
            else
                derecha += G[i][j];
        }
        lista_de_producciones.push_back(produccion(izquierda,derecha));
    }

    //clasificacion de producciones: terminales o no terminales
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
            vector<NTerminal> temp2 = temp1.getDerecha();
            //buscando en las produccion que no haya una produccion del caracter derecho
            for (int j = 0; j<lista_de_producciones.size() ; j++){
                produccion temp3 = lista_de_producciones.at(j);
                if(temp2.at(0).getLexema() == temp3.getIzquierda().getLexema()){
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
