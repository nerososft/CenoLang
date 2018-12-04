//
// Created by neroyang on 2018/12/4.
//

#ifndef CENO_LANG_NEWPRASER_H
#define CENO_LANG_NEWPRASER_H


#include "../lexer/Lexer.h"

namespace  CenoLang {
    class CPraser {
    private:
        Lexer* lexer;
        Token* look;

        void move();
        void match(int t);
        void error(std::string s,int t);
        void program();

        /**
         *  translation_unit    : external_decl
         * | translation_unit external_decl
         * ;
         */
        void translation_unit();


        /**
         *  external_decl       : function_definition
         * | decl
         * ;
         */
        void external_decl();


        /**
         * function_definition : decl_specs declarator decl_list compound_stat
         * |       declarator decl_list compound_stat
         * | decl_specs declarator     compound_stat
         * |       declarator  compound_stat
         * ;
         */
        void function_definition();

        /**
         * decl            : decl_specs init_declarator_list ';'
         * | decl_specs            ';'
         * ;
         */
        void decl();

        /**
         * decl_list       : decl
         * | decl_list decl
         * ;
         */
        void decl_list();


        /**
         * decl_specs      : storage_class_spec decl_specs
         * | storage_class_spec
         * | type_spec decl_specs
         * | type_spec
         * | type_qualifier decl_specs
         * | type_qualifier
         * ;
         */
        void decl_specs();

        /**
         * storage_class_spec  : 'auto' | 'register' | 'static' | 'extern' | 'typedef'
         * ;
         */
        void storage_class_spec();

        /**
         *  type_spec       : 'void' | 'char' | 'short' | 'int' | 'long' | 'float'
         *                 | 'double' | 'signed' | 'unsigned'
         *                 | struct_or_union_spec
         *                 | enum_spec
         *                 | typedef_name
         * ;
         */
        void type_spec();

        /**
         * type_qualifier      : 'const' | 'volatile'
         * ;
         */
        void type_qualifier();

        /**
         * struct_or_union_spec    : struct_or_union id '{' struct_decl_list '}'
         * | struct_or_union   '{' struct_decl_list '}'
         * | struct_or_union id
         * ;
         */
        void struct_or_union_spec();

        /**
         *  struct_or_union     : 'struct' | 'union'
         * ;
         */
        void struct_or_union();

        /**
         * struct_decl_list    : struct_decl
         * | struct_decl_list struct_decl
         * ;
         */
        void struct_decl_list();


        /**
         * init_declarator_list    : init_declarator
         * | init_declarator_list ',' init_declarator
         * ;
         */
        void init_declarator_list();

        /**
         * init_declarator     : declarator
         * | declarator '=' initializer
         * ;
         */
        void init_declarator();

        /**
         * struct_decl     : spec_qualifier_list struct_declarator_list ';'
         * ;
         */
        void struct_decl();

        /**
         * spec_qualifier_list : type_spec spec_qualifier_list
         * | type_spec
         * | type_qualifier spec_qualifier_list
         * | type_qualifier
         * ;
         */
        void spec_qualifier_list();


        /**
         *  struct_declarator_list  : struct_declarator
         * | struct_declarator_list ',' struct_declarator
         * ;
         */
        void struct_declarator_list();

        /**
         *  struct_declarator   : declarator
         * | declarator ':' const_exp
         * |       ':' const_exp
         * ;
         */
        void struct_declarator();

        /**
         * enum_spec       : 'enum' id '{' enumerator_list '}'
         * | 'enum'    '{' enumerator_list '}'
         * | 'enum' id
         * ;
         */
        void enum_spec();

        /**
         *  enumerator_list     : enumerator
         * | enumerator_list ',' enumerator
         * ;
         */
        void enumerator_list();

        /**
         * enumerator      : id
         * | id '=' const_exp
         * ;
         */
        void enumerator();

        /**
         *  declarator      : pointer direct_declarator
         * |   direct_declarator
         * ;
         */
        void declarator();

        /**
         * direct_declarator   : id
         * | '(' declarator ')'
         * | direct_declarator '[' const_exp ']'
         * | direct_declarator '['     ']'
         * | direct_declarator '(' param_type_list ')'
         * | direct_declarator '(' id_list ')'
         * | direct_declarator '('     ')'
         * ;
         */
        void direct_declarator();

        /**
         *  pointer         : '*' type_qualifier_list
         * | '*'
         * | '*' type_qualifier_list pointer
         * | '*'           pointer
         * ;
         */
        void pointer();

        /**
         *  type_qualifier_list : type_qualifier
         * | type_qualifier_list type_qualifier
         * ;
         */
        void type_qualifier_list();

        /**
         * param_type_list     : param_list
         * | param_list ',' '...'
         * ;
         */
        void param_type_list();

        /**
         *  param_list      : param_decl
         * | param_list ',' param_decl
         * ;
         */
        void param_list();

        /**
         *  param_decl      : decl_specs declarator
         * | decl_specs abstract_declarator
         * | decl_specs
         * ;
         */
        void param_decl();


        /**
         *  id_list         : id
         * | id_list ',' id
         * ;
         */
        void id_list();

        /**
         * initializer     : assignment_exp
         * | '{' initializer_list '}'
         * | '{' initializer_list ',' '}'
         * ;
         */
        void initializer();

        /**
         *  initializer_list    : initializer
         * | initializer_list ',' initializer
         * ;
         */
        void initializer_list();


        /**
         *  type_name       : spec_qualifier_list abstract_declarator
         * | spec_qualifier_list
         * ;
         */
        void type_name();

        /**
         * abstract_declarator : pointer
         * | pointer direct_abstract_declarator
         * |   direct_abstract_declarator
         * ;
         */
        void abstract_declarator();

        /**
         *  direct_abstract_declarator: '(' abstract_declarator ')'
         * | direct_abstract_declarator '[' const_exp ']'
         * |               '[' const_exp ']'
         * | direct_abstract_declarator '['    ']'
         * |               '[' ']'
         * | direct_abstract_declarator '(' param_type_list ')'
         * |               '(' param_type_list ')'
         * | direct_abstract_declarator '('        ')'
         * |               '('     ')'
         * ;
         */
        void direct_abstract_declarator();


        /**
         *  typedef_name        : id
         * ;
         */
        void typedef_name();

        /**
         * stat            : labeled_stat
         * | exp_stat
         * | compound_stat
         * | selection_stat
         * | iteration_stat
         * | jump_stat
         * ;
         */
        void stat();

        /**
         * labeled_stat        : id ':' stat
         * | 'case' const_exp ':' stat
         * | 'default' ':' stat
         * ;
         * exp_stat        : exp ';'
         * |   ';'
         * ;
         */
        void labeled_stat();

        /**
         * compound_stat       : '{' decl_list stat_list '}'
         * | '{'       stat_list '}'
         * | '{' decl_list     '}'
         * | '{'           '}'
         * ;
         */
        void compound_stat();

        /**
         *  stat_list       : stat
         * | stat_list stat
         * ;
         */
        void stat_list();

        /**
         * selection_stat      : 'if' '(' exp ')' stat
         * | 'if' '(' exp ')' stat 'else' stat
         * | 'switch' '(' exp ')' stat
         * ;
         */
        void selection_stat();

        /**
         * iteration_stat      : 'while' '(' exp ')' stat
         * | 'do' stat 'while' '(' exp ')' ';'
         * | 'for' '(' exp ';' exp ';' exp ')' stat
         * | 'for' '(' exp ';' exp ';' ')' stat
         * | 'for' '(' exp ';' ';' exp ')' stat
         * | 'for' '(' exp ';' ';' ')' stat
         * | 'for' '(' ';' exp ';' exp ')' stat
         * | 'for' '(' ';' exp ';' ')' stat
         * | 'for' '(' ';' ';' exp ')' stat
         * | 'for' '(' ';' ';' ')' stat
         * ;
         */
        void iteration_stat();

        /**
         *  jump_stat       : 'goto' id ';'
         * | 'continue' ';'
         * | 'break' ';'
         * | 'return' exp ';'
         * | 'return'  ';'
         * ;
         */
        void jump_stat();

        /**
         *  exp         : assignment_exp
         * | exp ',' assignment_exp
         * ;
         */
        void exp();

        /**
         *  assignment_exp      : conditional_exp
         * | unary_exp assignment_operator assignment_exp
         * ;
         */
        void assignment_exp();


        /**
         * assignment_operator : '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<='
                              | '>>=' | '&=' | '^=' | '|='
         * ;
         */
        void assignment_operator();

        /**
         * conditional_exp     : logical_or_exp
         * | logical_or_exp '?' exp ':' conditional_exp
         * ;
         */
        void conditional_exp();

        /**
         *  const_exp       : conditional_exp
         * ;
         */
        void const_exp();

       /**
        *  logical_or_exp      : logical_and_exp
        * | logical_or_exp '||' logical_and_exp
        * ;
        */
        void logical_or_exp();

        /**
         * logical_and_exp     : inclusive_or_exp
         * | logical_and_exp '&&' inclusive_or_exp
         * ;
         */
        void logical_and_exp();

        /**
         * inclusive_or_exp    : exclusive_or_exp
         * | inclusive_or_exp '|' exclusive_or_exp
         * ;
         */
        void inclusive_or_exp();

        /**
         * exclusive_or_exp    : and_exp
         * | exclusive_or_exp '^' and_exp
         * ;
         */
        void exclusive_or_exp();

        /**
         * and_exp         : equality_exp
         * | and_exp '&' equality_exp
         * ;
         */
        void and_exp();

        /**
         *  equality_exp        : relational_exp
         * | equality_exp '==' relational_exp
         * | equality_exp '!=' relational_exp
         * ;
         */
        void equality_exp();

        /**
         *  relational_exp      : shift_expression
         * | relational_exp '<' shift_expression
         * | relational_exp '>' shift_expression
         * | relational_exp '<=' shift_expression
         * | relational_exp '>=' shift_expression
         * ;
         */
        void relational_exp();

        /**
         * shift_expression    : additive_exp
         * | shift_expression '<<' additive_exp
         * | shift_expression '>>' additive_exp
         * ;
         */
        void shift_expression();

        /**
         *  additive_exp        : mult_exp
         * | additive_exp '+' mult_exp
         * | additive_exp '-' mult_exp
         * ;
         */
        void additive_exp();

        /**
         *  mult_exp        : cast_exp
         * | mult_exp '*' cast_exp
         * | mult_exp '/' cast_exp
         * | mult_exp '%' cast_exp
        ;
         */
        void mult_exp();

        /**
         * cast_exp        : unary_exp
         * | '(' type_name ')' cast_exp
         * ;
         */
        void cast_exp();

        /**
         * unary_exp       : postfix_exp
         * | '++' unary_exp
         * | '--' unary_exp
         * | unary_operator cast_exp
         * | 'sizeof' unary_exp
         * | 'sizeof' '(' type_name ')'
         * ;
         */
        void unary_exp();

        /**
         *  unary_operator      : '&' | '*' | '+' | '-' | '~' | '!'
         * ;
         */
        void unary_operator();

       /**
        * postfix_exp     : primary_exp
        * | postfix_exp '[' exp ']'
        * | postfix_exp '(' argument_exp_list ')'
        * | postfix_exp '('           ')'
        * | postfix_exp '.' id
        * | postfix_exp '->' id
        * | postfix_exp '++'
        * | postfix_exp '--'
        * ;
        */
        void postfix_exp();

        /**
         * primary_exp     : id
         * | const
         * | string
         * | '(' exp ')'
         * ;
         */
        void primary_exp();

        /**
         *  argument_exp_list   : assignment_exp
         * | argument_exp_list ',' assignment_exp
         * ;
         */
        void argument_exp_list();

        /**
         * const           : int_const
         * | char_const
         * | float_const
         * | enumeration_const
         * ;
         */
        void _const();



    public:
        CPraser(Lexer* lexer){
            this->lexer = lexer;
            move();
        }

        void start();
    };
};


#endif //CENO_LANG_NEWPRASER_H
