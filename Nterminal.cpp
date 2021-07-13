#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <vector>
using namespace std;
 
class NTerminal {
private:
    string lexema;
    map<string,string> atributos;
public:
    NTerminal();
    NTerminal(string);
    void addAtributo(string,string);

    friend ostream& operator<<(ostream& os, const NTerminal& dt);
    //friend NTerminal operator=(NTerminal &nterminal);
    bool operator ==(const NTerminal &t);
};

NTerminal::NTerminal(){;}
//forma [TENSE=?t, NUM=?n]
NTerminal::NTerminal(string lex){
    int i,_switch=0;
    string atrib;
    string val;
    //separando el nombre de la etiqueta
    for(i=0 ; i<lex.length() ; i++){
        if(lex[i]=='[')
            break;
        this->lexema+=lex[i];
    }
    //cout<<"Lexema: "<<lexema<<endl;
    i++; //siguiente elemento a [
    for(i ; i<lex.length() ; i++){
        if(lex[i]=='=')
            _switch=1;
        else if(lex[i]==32)
            continue;
        else if(lex[i]==']'||lex[i]==','){
            //cout<<"atrib: "<<atrib<<endl;
            //cout<<"val: "<<val<<endl;
            addAtributo(atrib,val);
            atrib = "";
            val = "";
            _switch=0;
        }
        else if(_switch==0)
            atrib+=lex[i];
        else if(_switch==1)
            val+=lex[i];
    }
}

ostream& operator<<(ostream& os, const NTerminal& dt){
    os <<dt.lexema<<"[";
    for (const auto &p : dt.atributos){
        os << p.first << ":"<<p.second<<"|";
    }
    return os <<"]";
}

void NTerminal::addAtributo(string atributo,string valor){
    atributos.insert(pair<string,string>(atributo, valor));
}


//Tareas:
//Sobrecargar operador:


bool NTerminal::operator==(const NTerminal &t) 
{
    if ((this->lexema == t.lexema) && (this->atributos == t.atributos))
        return true;
    return false;
}

/*
void NTerminal::operator==( NTerminal &nterminal ){
    //falta
    
}

void NTerminal::operator==(string ){
    //falta
    ;
}
*/
//*sobrecargar operador != para la clase estado



