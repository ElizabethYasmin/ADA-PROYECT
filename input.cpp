#include <iostream>
#include <fstream>
#include <string>

int getNumeroProducciones(std::string grammartxt){
    std::ifstream myfile(grammartxt);
    if (myfile.is_open())
    {
        int n;
        myfile>>n; 
        return n;
    }
    else std::cout << "Unable to open file"; 
    return 0;      
}

int getGrammar(std::string grammartxt,int n,std::string G[]){
    std::ifstream myfile(grammartxt);
    if (myfile.is_open())
    {

        std::string temp;
        getline(myfile, temp); //salto de la primera linea
        for(int i=0;i<n;i++){
            getline(myfile, temp);
            G[i]=temp;
        }
    }
    else std::cout << "Unable to open file"; 
    return 0;  
}
