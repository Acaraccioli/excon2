#ifndef _AST_H
#define _AST_H

#include <memory>
#include <string>
#include <iostream>

class ASTNode {
public:
    virtual std::string toString() =0;
};

using PExpr = ASTNode*;

#define BinaryExpr(nomOperacion, operador) \
class nomOperacion##Expr : public ASTNode{ \
public: \
nomOperacion##Expr(PExpr expr1, PExpr expr2): \
expr1(std::move(expr1)), expr2(std::move(expr2)){} \
std::string toString() override{ \
return "("+expr1->toString()+")"+operador+"("+expr2->toString()+")"; \
} \
PExpr expr1,expr2; \
};

BinaryExpr( And, "&&" );
BinaryExpr( Or, "||" );
BinaryExpr( GT, ">" );
BinaryExpr( GTE, ">=" );
BinaryExpr( LT, "<" );
BinaryExpr( LTE, "<=" );
BinaryExpr( EQ, "==" );
BinaryExpr( NEQ, "!=" );
BinaryExpr( Add, "+" );
BinaryExpr( Sub, "-" );
BinaryExpr( Mul, "*" );
BinaryExpr( Div, "/" );
BinaryExpr( Mod, "%" );


class NumExpr : public ASTNode{
public:
    NumExpr(int n){
        value=n;
    }

    std::string toString() override{
        return std::to_string(value);
    }

    int value;
};

class IdentExpr : public ASTNode{
public:
    IdentExpr(std::string id){
        name=id;
    }

    std::string toString() override{
        return name;
    }

    std::string name;
};

class AssignStmt : public ASTNode{
public:
    AssignStmt(std::string ide, PExpr expr1):
    expr1(std::move(expr1)){
        id=ide;
    }

    std::string toString() override{
        return id+"="+expr1->toString();
    }
    
    std::string id;
    PExpr expr1;
};

class IfStmt : public ASTNode{
public:
    IfStmt(PExpr c, PExpr t, PExpr f):
    c(std::move(c)), t(std::move(t)), f(std::move(f)){}

    std::string toString() override{
        
        return "if ("+c->toString()+") {\n"+t->toString()+"\n} else {\n"+f->toString()+"\n}";

    }


    PExpr t,f,c;
};

class WhileStmt : public ASTNode{
public:
    WhileStmt(PExpr c, PExpr b):
    c(std::move(c)), b(std::move(b)){}

    std::string toString() override{
        return "while ("+c->toString()+") {\n"+b->toString()+"\n}";
    }

    PExpr c,b;
};


#endif
