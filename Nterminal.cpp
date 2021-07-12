#include <iostream>
#include <map>
#include <vector>
 
class NTerminal {
private:
    std::string lexema;
    std::map<std::string,std::string> atributos;
public:
    NTerminal();
    NTerminal(std::string);
    void addAtributo(std::string,std::string);

    friend std::ostream& operator<<(std::ostream& os, const NTerminal& dt);

};

NTerminal::NTerminal(){;}
//forma [TENSE=?t, NUM=?n]
NTerminal::NTerminal(std::string lex){
    int i,_switch=0;
    std::string atrib;
    std::string val;
    //separando el nombre de la etiqueta
    for(i=0 ; i<lex.length() ; i++){
        if(lex[i]=='[')
            break;
        this->lexema+=lex[i];
    }
    //std::cout<<"Lexema: "<<lexema<<std::endl;
    i++; //siguiente elemento a [
    for(i ; i<lex.length() ; i++){
        if(lex[i]=='=')
            _switch=1;
        else if(lex[i]==32)
            continue;
        else if(lex[i]==']'||lex[i]==','){
            //std::cout<<"atrib: "<<atrib<<std::endl;
            //std::cout<<"val: "<<val<<std::endl;
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

std::ostream& operator<<(std::ostream& os, const NTerminal& dt){
    os <<dt.lexema<<"[";
    for (const auto &p : dt.atributos){
        os << p.first << ":"<<p.second<<"|";
    }
    return os <<"]";
}

void NTerminal::addAtributo(std::string atributo,std::string valor){
    atributos.insert(std::pair<std::string,std::string>(atributo, valor));
}

/*
Tareas:
Sobrecargar operador:

void NTerminal::operator==( NTerminal &nterminal ){
    //falta
    ;
}

void NTerminal::operator==(std::string ){
    //falta
    ;
}

*sobrecargar operador != para la clase estado

*/

