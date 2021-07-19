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
    NTerminal(string,map<string,string>);
    void addAtributo(string,string);
    void setAtributos(map<string,string>);
    string getLexema();
    map<string,string> getAtributos();
    void deleteAtributos();
    friend ostream& operator<<(ostream& os, const NTerminal& dt);
    //friend NTerminal operator=(NTerminal &nterminal);
    friend bool operator==(const NTerminal &t, const NTerminal &v);
};

NTerminal::NTerminal(){;}
/*
forma det[TENSE=?t,NUM=?n]
*/
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
NTerminal::NTerminal(string _lex,map<string,string> _atributos){
    this ->lexema = _lex;
    this ->atributos = _atributos;
}

ostream& operator<<(ostream& os, const NTerminal& dt){
    os <<dt.lexema;
    if(!dt.atributos.empty()){
        os <<"[";
        for (const auto &p : dt.atributos){
            os <<p.first << ":"<<p.second<<"|";
        }
        os <<"]";
    }
    return os;
}

void NTerminal::addAtributo(string atributo,string valor){
    atributos.insert(pair<string,string>(atributo, valor));
}

void NTerminal::deleteAtributos(){
    atributos.clear();
}

string NTerminal::getLexema(){
    return lexema;
}

map<string,string> NTerminal::getAtributos(){
    return atributos;
}

void NTerminal::setAtributos(map<string,string> n_atributos){
    for (const auto &p : n_atributos){
        auto itr = atributos.find(p.first); 
            if (itr != atributos.end() && (*itr).second[0]=='?'){
                (*itr).second = p.second;
        }
    }
}

/*
los atributos en comun deben ser iguales
*/
bool operator==(const NTerminal &t, const NTerminal &v){
    if ((t.lexema != v.lexema))
        return false;
    for (const auto &p : t.atributos){
        for (const auto &p2 : v.atributos){
            if(p.first==p2.first)
                if(p.second!=p2.second) 
                    return false;
        }
    }
    return true;
}

