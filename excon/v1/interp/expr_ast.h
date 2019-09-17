#ifndef _AST_H
#define _AST_H

#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>
#include <sstream>


class ASTNode {
public:
    virtual int eval(std::unordered_map<std::string, int> &vars)=0;
};

using PExpr = ASTNode*;

#define BinaryExpr(nomoperadoracion, operador) \
class nomoperadoracion##Expr : public ASTNode{ \
public: \
nomoperadoracion##Expr(PExpr expr1, PExpr expr2): \
expr1(std::move(expr1)), expr2(std::move(expr2)){} \
int eval(std::unordered_map<std::string, int> &vars){ \
return expr1->eval(vars) operador expr2->eval(vars); \
} \
PExpr expr1,expr2; };

BinaryExpr( And, && );
BinaryExpr( Or, || );
BinaryExpr( GT, > );
BinaryExpr( GTE, >= );
BinaryExpr( LT, < );
BinaryExpr( LTE, <= );
BinaryExpr( EQ, == );
BinaryExpr( NEQ, != );
BinaryExpr( Add, + );
BinaryExpr( Sub, - );
BinaryExpr( Mul, * );
BinaryExpr( Div, / );
BinaryExpr( Mod, % );


class NumExpr : public ASTNode{
public:
    NumExpr(int n){
        value=n;
    }

    int eval(std::unordered_map<std::string, int> &vars) override{
        return value;
    }
    int value;
};

class IdentExpr : public ASTNode{
public:
    IdentExpr(std::string id){
        name=id;
    }

    int eval(std::unordered_map<std::string, int> &vars) override{

        return vars[name];
    }

    std::string name;
};

class AssignStmt : public ASTNode{
public:
    AssignStmt(std::string ide, PExpr expr1):
    expr1(std::move(expr1)){
        id=ide;
    }

    int eval(std::unordered_map<std::string, int> &vars) override{
        vars[id] = expr1->eval(vars);
    }
    
    std::string id;
    PExpr expr1;
};

class IfStmt : public ASTNode{
public:
    IfStmt(PExpr c, PExpr t, PExpr f):
    c(std::move(c)), t(std::move(t)), f(std::move(f)){}

    int eval(std::unordered_map<std::string, int> &vars) override{
        
        if(c->eval(vars)){

            t->eval(vars);
        }else{

            f->eval(vars);
        }

    }


    PExpr t,f,c;
};

class WhileStmt : public ASTNode{
public:
    WhileStmt(PExpr c, PExpr b):
    c(std::move(c)), b(std::move(b)){}

    int eval(std::unordered_map<std::string, int> &vars) override{
        
        while(c->eval(vars)){
            b->eval(vars);
        }
    }

    PExpr c,b;

};


#endif
