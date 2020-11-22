#ifndef DESIGN_PATTERN_ABSTRUCTFACTORY_H
#define DESIGN_PATTERN_ABSTRUCTFACTORY_H

#include <iostream>

//AbstructProduct
class AbstructProductA{
public:
    virtual ~AbstructProductA()=default;
    virtual std::string UsefulFunctionA()const=0;
};

class ConcreteProductA1:public AbstructProductA{
public:
    std::string UsefulFunctionA()const override{
        return "The result of the product A1.";
    }
};

class ConcreteProductA2:public AbstructProductA{
public:
    std::string UsefulFunctionA()const override{
        return "The result of the product A2.";
    }
};

class AbstructProductB{
public:
    virtual ~AbstructProductB()=default;
    virtual std::string UsefulFunctionB()const=0;
    virtual std::string AnotherUsefulFunctionB(AbstructProductA const&)const=0;
};

class ConcreteProductB1:public AbstructProductB{
public:
    std::string UsefulFunctionB()const override{
        return "The result of product B1.";
    }

    std::string AnotherUsefulFunctionB(AbstructProductA const& coll)const override {
        std::string const result = coll.UsefulFunctionA();
        return "The result of B1 collaborating with (" + result + ")";
    }
};

class ConcreteProductB2:public AbstructProductB{
public:
    std::string UsefulFunctionB()const override{
        return "The result of product B2.";
    }

    std::string AnotherUsefulFunctionB(AbstructProductA const& coll)const override{
        std::string const result=coll.UsefulFunctionA();
        return "The result of product B2 with ("+result+")";
    }
};

//Factory
class AbstructFactory{
public:
    virtual AbstructProductA* createProductA()const=0;
    virtual AbstructProductB* createProductB()const=0;
};

class ConcreteFactory1:public AbstructFactory{
public:
    AbstructProductA* createProductA()const override{
        return new ConcreteProductA1{};
    }

    AbstructProductB* createProductB()const override{
        return new ConcreteProductB1{};
    }
};

class ConcreteFactory2:public AbstructFactory{
public:
    AbstructProductA* createProductA()const override{
        return new ConcreteProductA2{};
    }

    AbstructProductB* createProductB()const override{
        return new ConcreteProductB2{};
    }
};

class client{
public:
    void operator()(AbstructFactory const& factory)const{
        AbstructProductA const* product_a=factory.createProductA();
        AbstructProductB const* product_b=factory.createProductB();
        std::cout<<product_b->UsefulFunctionB()<<"\n";
        std::cout<<product_b->AnotherUsefulFunctionB(*product_a)<<"\n";
        delete product_a;
        delete product_b;
    }
};

/*
 * int main(){
    std::cout<<"Client:Testing client code with the first factory type:\n";
    client Client;
    ConcreteFactory1* f1=new ConcreteFactory1{};
    Client(*f1);
    std::cout<<std::endl;
    std::cout<<"Client:Testing client code with the second factory type:\n";
    ConcreteFactory2* f2=new ConcreteFactory2{};
    Client(*f2);
    delete f2;
}
 */
#endif //DESIGN_PATTERN_ABSTRUCTFACTORY_H
