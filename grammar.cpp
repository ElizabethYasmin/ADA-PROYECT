#include <iostream>
#include "produccion.cpp"
#include <string>
#include <vector>
using namespace std;

class Grammar{
public:
    //vector<produccion>producciones_terminales;
    //vector<produccion>producciones_no_terminales; 
    vector<produccion>lista_de_producciones; 
public:
    Grammar(string G[],int n);
    void print();
    
};

void Grammar::print(){
    /*
    cout<<"No terminales:\n";
    for (auto it = producciones_no_terminales.begin(); it != producciones_no_terminales.end(); it++){
        cout<<*it<<"."<<endl;
    }
    cout<<"Terminales:\n";
    for (auto it = producciones_terminales.begin(); it != producciones_terminales.end(); it++){
        cout<<*it<<"."<<endl;
    }*/
    cout<<"Terminales:\n";
    for (auto it = lista_de_producciones.begin(); it != lista_de_producciones.end(); it++){
        cout<<*it<<"."<<endl;
    }

}

/*
G ->lista producciones no procesadas (forma 'izquierda' ::= 'derecha' )
n -> numero de producciones
*/
Grammar::Grammar(string G[],int n){
    //vector<produccion> lista_de_producciones;
    for(int i=0;i<n;i++){//recorre cada produccion en la lista
        int j;
        string izquierda, derecha;
        for(j=0 ; j<G[i].length() ; j++){ //separa el lado izquierdo
            if(G[i][j+1]!=':'){
                izquierda += G[i][j];
            }
            else{
                //cout<<" Izquierda: "<<izquierda<<"."<<endl;
                j+=5;
                break;
            }
        }
        for(j; j<G[i].length() ; j++){
            if(G[i][j]=='|' && G[i][j+1]=='|'){
                //cout<<" derecha:."<<derecha<<"."<<endl;
                lista_de_producciones.push_back(produccion(izquierda,derecha));
                derecha = "";
                j++;
            }
            else
                derecha += G[i][j];
        }
        //cout<<" derecha:."<<derecha<<"."<<endl;
        lista_de_producciones.push_back(produccion(izquierda,derecha));
    }
    /*
    //clasificacion de producciones: terminales o no terminales
    for (int i = 0; i<lista_de_producciones.size() ; i++){
        int cont=0;
        produccion temp1 = lista_de_producciones.at(i);
        //es produccion no terminal?
        //si tiene mas de un caracter en la derecha no es terminal
        if(temp1.getlength()>1){
            cont++;
            producciones_no_terminales.push_back(temp1.producci0n);
        }
        //si tiene un caracter en la derecha se verifica que este caracter no tenga produccion
        else{
            string temp2 = temp1.getDerecha();
            //buscando en las produccion que no haya una produccion del caracter derecho
            for (int j = 0; j<lista_de_producciones.size() ; j++){
                produccion temp3 = lista_de_producciones.at(j);
                if(temp2 == temp3.getIzquierda()){
                    cont++;
                    producciones_no_terminales.push_back(temp1.producci0n);
                    break;
                }
            }
        }
        if(cont==0)
            producciones_terminales.push_back(temp1);
            
    }
    */
} 


int main(){

    string G[] = {
        "S ::= NP[NUM=?n] VP[NUM=?n]",
        "NP[NUM=?n] ::= N[NUM=?n]",
        "NP[NUM=?n] ::= PropN[NUM=?n]",
        "NP[NUM=?n] ::= Det[NUM=?n] N[NUM=?n]",
        "NP[NUM=pl] ::= N[NUM=pl]",

        "VP[TENSE=?t,NUM=?n] ::= IV[TENSE=?t,NUM=?n]",
        "VP[TENSE=?t,NUM=?n] ::= TV[TENSE=?t,NUM=?n] NP",

        "Det[NUM=sg] ::= this||every",
        "Det[NUM=pl] ::= these||all",
        "Det ::= the||some||several",
        "PropN[NUM=sg] ::= Kim||Jody",
        "N[NUM=sg] ::= dog||girl||car||child",
        "N[NUM=pl] ::= dogs||girls||cars||children'",
        "IV[TENSE=pres,NUM=sg] ::= disappears||walks'",
        "TV[TENSE=pres,NUM=sg] ::= sees||likes",
        "IV[TENSE=pres,NUM=pl] ::= disappear||walk",
        "TV[TENSE=pres,NUM=pl] ::= see||like",
        "IV[TENSE=past] ::= disappeared||walked'",
        "TV[TENSE=past] ::= saw||liked"
    };

    Grammar X(G,19);
    X.print();
 
}