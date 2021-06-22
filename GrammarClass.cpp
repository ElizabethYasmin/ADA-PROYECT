#include <iostream>
#include "Nterminal.cpp"
#include "produccionClass.cpp"

class Grammar{
private:
    std::vector<produccion>producciones_terminales;
    std::vector<NTerminal>producciones_no_terminales; 
public:
    Grammar(std::string G[],int n);
    void print();
    
};

void Grammar::print(){
    std::cout<<"No terminales:\n";
    for (auto it = producciones_no_terminales.begin(); it != producciones_no_terminales.end(); it++){
        std::cout<<*it<<"."<<std::endl;
    }
    std::cout<<"Terminales:\n";
    for (auto it = producciones_terminales.begin(); it != producciones_terminales.end(); it++){
        std::cout<<*it<<"."<<std::endl;
    }

}

/*
G ->lista producciones no procesadas (forma 'izquierda' ::= 'derecha' )
n -> numero de producciones
*/
Grammar::Grammar(std::string G[],int n){
    std::vector<produccion> lista_de_producciones;
    for(int i=0;i<n;i++){
        int breakk= 0;
        std::string izquierda, temp;
        for(int j=0 ; j<G[i].length() ; j++){
            if(breakk == 0){
                if(G[i][j+1]!=':'){
                    izquierda += G[i][j];
                }
                else{
                    breakk=j;
                    izquierda += std::string(" ::= ");
                    //std::cout<<" Izquierda: "<<izquierda<<"."<<std::endl;
                    j+=4;
                    temp = izquierda;
                }
            }
            else if(G[i][j]=='|' && G[i][j+1]=='|'){
                //std::cout<<" Derecha: "<<temp<<"."<<std::endl;
                lista_de_producciones.push_back(produccion(temp));
                temp = izquierda;
                j++;
            }
            else
                temp += G[i][j];
        }
        //std::cout<<" Derecha: "<<temp<<"."<<std::endl;
        lista_de_producciones.push_back(produccion(temp));
    }
    
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
            std::string temp2 = temp1.getDerecha();
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
} 


int main(){
/*
S → a B	C
S →	a S	B C
C B	→ C	Z
C Z	→ W	Z
W Z	→ W	C
W C	→ B	C
a B	→ a	b
b B	→ b	b	
b C	→ b	c
c C	→ c	c
*/
    std::string G[] = {
        "S ::= a B C||a S B C" ,
        "C B ::= C Z" , 
        "C Z ::= W Z" ,
        "W Z ::= W C" ,
        "W C ::= B C",
        "a B ::= a b",
        "b B ::= b b",
        "b C ::= b c",
        "c C ::= c c"
    };

    //std::string xd="W C ::= B C Z";
    //NTerminal test0(xd);
    //std::cout<<std::endl<<test0;

    Grammar X(G,9);
    X.print();


}