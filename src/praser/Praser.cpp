//
// Created by neroyang on 2018/12/3.
//

#include <iostream>
#include "../../include/praser/Praser.h"

namespace CenoLang{
  void Praser::move() {
      this->look = this->lexer->scan();
  }

    void Praser::match(int t){
        std::cout<<"MATCH("<<look->tag<<")("<<t<<")"<<std::endl;
        if(look->tag == t){
            move();
        }else{
            error("Syntax Error",t);
        }
    }

    void Praser::error(std::string s,int t){
        std::cout<<s<<": near line "<< lexer->line<<", next char need be '"<<(char)t<<"'"<<std::endl;
    }

    void Praser::program(){
        block();
    }

    void Praser::start(){
        program();
    }

    void Praser::block(){
        match('{');
        decls();
        stmts();
        match('}');
    }

    // 变量定义
    void Praser::decls(){
        while(look->tag == Tag::BASIC_TYPE){
            type();
            match(Tag::ID);
            match(';');
        }
    }

    void Praser::type(){
        match(Tag::BASIC_TYPE);
        if(look->tag == '['){
            dims();
        }
    }

    void Praser::dims(){
        match('[');
        match(Tag::NUM);
        match(']');
        if(look->tag=='['){
            dims();
        }
    }

    void Praser::stmts(){
        if(look->tag=='}'){

        }else{
            stmt();
            stmts();
        }
    }


    void Praser::stmt(){
        switch (look->tag){
            case ';':
                move();
                return;
            case Tag::IF:
                match(Tag::IF);
                match('(');
                _bool();
                match(')');
                match(Tag::ELSE);
                stmt();
                return;
            case Tag::WHILE:
                match(Tag::WHILE);
                match('(');
                _bool();
                match(')');
                stmt();
                return;

        }
    }

    void Praser::_bool() {
        join();
        while(look->tag==Tag::OR){
            move();
            join();
        }
    }

    void Praser::join(){
        equality();
        while(look->tag==Tag::AND){
            move();
            equality();
        }
    }

    void Praser::equality(){
        rel();
        while(look->tag ==Tag::EQUAL || look->tag == Tag::N_EQUAL){
            move();
            rel();
        }
    }

    void Praser::rel(){
        expr();
        switch (look->tag){
            case '<':
            case Tag::L_EQUAL:
            case Tag::G_EQUAL:
            case '>':
                move();
                expr();
                return;
            default:
                error("Syntax Error",0);
        }
    }

    void Praser::expr(){
        term();
        while(look->tag=='+' || look->tag=='-'){
            move();
            term();
        }
    }


    void Praser::term(){
        unary();
        while(look->tag=='*' || look->tag=='/'){
            move();
            unary();
        }
    }

    void Praser::unary(){
        if(look->tag=='-'){
            move();
            unary();
        } else if(look->tag == '!'){
            move();
            unary();
        }else{
            factor();
        }
    }


    void Praser::factor(){
        switch(look->tag){
            case '(':
                move();
                _bool();
                match(')');
                return;
            case Tag::NUM:
                move();
                return;
            case Tag::REAL:
                move();
                return;
            case Tag::TRUE:
                move();
                return;
            case Tag::FALSE:
                move();
                return;
            case Tag::ID:
                move();
                if(look->tag!='['){

                }else{
                    offset();
                }
                return;
            default:
                error("c",0);
        }

    }

    void Praser::offset() {
        match('[');
        _bool();
        match(']');
        while(look->tag=='['){
            match('[');
            _bool();
            match(']');
        }
    }

};