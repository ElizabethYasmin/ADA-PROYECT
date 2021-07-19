#include <iostream>
#include <string>
#include <vector>
#include <map>

class chart{
public:
    std::vector<estado> estados;
    std::map<std::string,std::string> atributos;    
    chart(){
    }
    void addAtributo(std::string,std::string);
    void setAtributo(map<string,string>);
    void addEstado(estado);
    int getSizeEstados();
    map<string,string> getAtributos();
    friend std::ostream& operator<<(std::ostream& os, const chart& dt);
};

void chart::addAtributo(std::string atributo,std::string valor){
    atributos.insert(std::pair<std::string,std::string>(atributo, valor));
}

void chart::addEstado(estado nuevo_estado){
    estados.push_back(nuevo_estado);
}

int chart::getSizeEstados(){
    return estados.size();
}

map<string,string> chart::getAtributos(){
    return atributos;
}

void chart::setAtributo(map<string,string> nuevo_atrib){
    atributos=nuevo_atrib;
}


std::ostream& operator<<(std::ostream& os, const chart& dt){
    if(!dt.atributos.empty()){
        os <<"Atributos:\n";
        for (const auto &p : dt.atributos){
            os <<"ATRIBUTO: " <<p.first << ", valor: "<<p.second<<std::endl;
        }
    }
    os <<"Estados:\n";
    for (int j = 0; j<dt.estados.size() ; j++){
        auto temp = dt.estados.at(j);
        os <<"Estado "<<j<<" : "<< temp <<std::endl;
    }
    return os;
}