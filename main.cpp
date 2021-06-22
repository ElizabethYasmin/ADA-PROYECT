/*==========================
PARSER para gramatica dependiente del contexto
============================
Implementacion por:
+Huanca Parqui Elizabeth Yasmin
+Ccorahua Lozano Rommel
+Villanueva Guerrero Luisa
*/

#include <iostream>
#include "Early_Parser.cpp"

int main(){
   /*
    //Ejemplo Wikipedia
    std::string A = "number + number * number";
    std::string G[] = {
        "P ::= S" ,
        "S ::= S + M", 
        "S ::= M" ,
        "M ::= M * T" ,
        "M ::= T" ,
        "T ::= number" 
    };
    early_parser(A,G,6);
*/
   /*
    //Ejemplo YT: https://www.youtube.com/watch?v=WNKw1tiskSM&t=1622s
    std::string A = "1 + 1";
    std::string G[] = {
        "term ::= number + term" ,
        "term ::= number", 
        "number ::= 1" 
    };
    early_parser(A,G,3);
  */
   /*
    //Ejemplo YT: https://www.youtube.com/watch?v=1j6hB3O4hAM&t=462s
    std::string A = "book that flight";
    std::string G[] = {
        "S ::= NP VP" ,
        "S ::= VP", 
        "NP ::= det nominal" ,
        "nominal ::= noun" , 
        "VP ::= verb" ,
        "VP ::= verb NP" ,
        "det ::= that" ,
        "det ::= this" ,
        "det ::= a" ,
        "det ::= the" ,
        "noun ::= book" ,
        "noun ::= flight" ,
        "noun ::= meal" ,
        "noun ::= money" ,
        "verb ::= book" ,
        "verb ::= include" ,
        "verb ::= prefer"
    };
   early_parser(A,G,17);
    */
   
    return 0;
}