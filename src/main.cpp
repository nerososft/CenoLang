#include <iostream>

#include "../include/clcompiler/Config.h"

#include "../include/lexer/Lexer.h"
#include "../include/praser/Praser.h"
#include "../include/praser/CPraser.h"


int main() {
    CenoLang::Lexer *lexer = new CenoLang::Lexer();
    while(true){
        std::cout<<lexer->scan()->tag<<std::endl;
    }
    CenoLang::CPraser *praser = new CenoLang::CPraser(lexer);
    praser->start();

}