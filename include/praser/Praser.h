//
// Created by neroyang on 2018/12/3.
//

#ifndef CENO_LANG_PRASER_H
#define CENO_LANG_PRASER_H

#include "../lexer/Lexer.h"

/**
 * CFG
 * PROG -> BLOCK
 * BLOCK -> {DECLS STMTS}
 * DECLS -> DECLS DECL | e
 * DECL -> TYPE id
 * TYPE -> TYPE[num] | basic_type
 * STMTS -> STMTS STMS | e
 *
 * STMS -> LOC = BOOL;
 * | if(BOOL) STMT
 * | if(BOOL) STMT else STMT
 * | while(BOOL)STMT
 * | do STMT while(BOOL)
 * | break
 * | BLOCK
 *
 * LOC -> LOC[BOOL] | id
 *
 * BOOL -> BOOL||JOIN
 * | JOIN
 *
 * JOIN -> JOIN&&EQUALITY
 * | EQUALITY
 *
 * EQUALITY -> EQUALITY==REL
 * | EQUALITY!=REL
 * | REL
 *
 * REL -> EXPR<EXPR
 * | EXPR<=EXPR
 * | EXPR>=EXPR
 * | EXPR>EXPR
 * | EXPR
 *
 * EXPR -> EXPR+TERM
 * | EXPR-TERM
 * | TERM
 *
 * TERM -> TERM * UNARY
 * | TERM/UNARY
 * | UNARY
 *
 * UNARY -> !UNARY
 * | -UNARY
 * | FACTOR
 *
 * FACTOR -> (BOOL)|LOG|num|real|true|false
 */


namespace  CenoLang {
    class Praser {
    private:
        Lexer* lexer;
        Token* look;

        void move();
        void match(int t);
        void error(std::string s,int t);
        void program();

        void block();
        void decls();

        void stmts();
        void stmt();

        void type();
        void dims();

        void _bool();

        void join();

        void equality();

        void rel();

        void expr();

        void term();

        void unary();

        void factor();

        void offset();



    public:
        Praser(Lexer* lexer){
            this->lexer = lexer;
            move();
        }

        void start();
    };
}


#endif //CENO_LANG_PRASER_H
