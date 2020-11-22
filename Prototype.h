#ifndef DESIGN_PATTERN_PROTOTYPE_H
#define DESIGN_PATTERN_PROTOTYPE_H

#include <iostream>
#include <string>
#include <unordered_map>

enum class Type{
    PT_1=0,PT_2
};

class ProtoType{
    std::string name;
    double field;
public:
    ProtoType(std::string n):name(n){}
    virtual ~ProtoType(){}

    virtual ProtoType* clone()const =0;

    virtual void Method(double f){
        this->field=f;
        std::cout<<"Call Method from"<<name
                 <<"with field:"<<field;
    }
};

class ConcreteProtoType1:public ProtoType{
    double c_field;
public:
    ConcreteProtoType1(std::string n,double cf):ProtoType(n),c_field(cf){}

    virtual ConcreteProtoType1* clone()const override{
        return new ConcreteProtoType1(*this);
    }
};

class ConcreteProtoType2:public ProtoType{
    double c_field;
public:
    ConcreteProtoType2(std::string n,double cf):ProtoType(n),c_field(cf){}

    virtual ConcreteProtoType2* clone()const override{
        return new ConcreteProtoType2(*this);
    }
};

class ProtoTypeFactory{
    std::unordered_map<Type,ProtoType*> Pro_factory;
public:
    ProtoTypeFactory(){
        Pro_factory[Type::PT_1]=new ConcreteProtoType1("ProtoType1",50.0);
        Pro_factory[Type::PT_2]=new ConcreteProtoType2("ProtoType2",60.0);
    }

    ~ProtoTypeFactory(){
        delete Pro_factory[Type::PT_1];
        delete Pro_factory[Type::PT_2];
    }

    ProtoType* CreateProTotype(Type t){
        return Pro_factory[t]->clone();
    }

};

void ClientCode(ProtoTypeFactory &pf){
    std::cout<<"Let's create a Prototype1 \n";

    ProtoType *pp=pf.CreateProTotype(Type::PT_1);
    pp->Method(90.0);
    delete pp;

    std::cout<<std::endl;

    std::cout<<"\nLet's create a Prototype2 \n";
    pp=pf.CreateProTotype(Type::PT_2);
    pp->Method(20.0);
    delete pp;
}
#endif //DESIGN_PATTERN_PROTOTYPE_H
