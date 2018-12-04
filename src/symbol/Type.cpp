//
// Created by neroyang on 2018/12/3.
//

#include "../../include/symbol/Type.h"
namespace CenoLang {
    bool Type::isNumeric(Type* p){
        return p == Types::CHAR || p == Types::INT || p == Types::FLOAT;
    }

    Type* Type::maxNubericType(Type* t1, Type* t2){
        if(!isNumeric(t1) || !isNumeric(t2)){
            return nullptr;
        }

        if(t1 == Types::FLOAT || t2 == Types::FLOAT){
            return Types::FLOAT;
        }

        if(t1 == Types::INT || t2 == Types::INT){
            return Types::INT;
        }

        return Types::CHAR;
    }
};