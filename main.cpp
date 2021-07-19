//==========================
//PARSER para gramatica dependiente del contexto
//============================
//Implementacion por:
//+Huanca Parqui Elizabeth Yasmin
//+Villanueva Guerrero Luisa

#include <iostream>
#include "Nterminal.cpp"
#include "produccion.cpp"
#include "estado.cpp"
#include "grammar.cpp"
#include "chart.cpp"
#include "Early_Parser.cpp"
#include "input.cpp"

/*
argumentos:
0 -> gramatica.txt
1 -> entrada a evaluar
2 -> salida.txt
*/
int main(int argc, char *argv[]){
    if(argc==1){ //ingresar los datos en el main   
        //gramatica de prueba:
        std::string entrada="these dogs walk";
        std::string G[] = {
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
            "N[NUM=pl] ::= dogs||girls||cars||children",
            "IV[TENSE=pres,NUM=sg] ::= disappears||walks",
            "TV[TENSE=pres,NUM=sg] ::= sees||likes",
            "IV[TENSE=pres,NUM=pl] ::= disappear||walk",
            "TV[TENSE=pres,NUM=pl] ::= see||like",
            "IV[TENSE=past] ::= disappeared||walked",
            "TV[TENSE=past] ::= saw||liked"
        };
        early_parser(entrada,G,19,"salida.txt");
    }
   if(argc>1){ ///si se ingresa la gramatica por .txt
        int numeroProducciones = getNumeroProducciones(argv[1]);
        std::cout<<argv[1]<<std::endl;
        std::string entrada;
        std::string salida = "salida.txt";
        std::string G[numeroProducciones];
        getGrammar(argv[1],numeroProducciones,G);
        if(argc>2){ //si se ingresa la gramatica y entrada
                entrada=argv[2];
        }
        else{
            std::cout<<"Ingresar entrada a evaluar:\n";
            std::getline (std::cin,entrada);
            std::cout<<entrada<<std::endl;
        }
        if(argc==3){
            salida=argv[3];
        }
        early_parser(entrada,G,numeroProducciones,salida);
    }
    return 1;
}