#ifndef DESIGN_PATTERN_PROTOTYPE_H
#define DESIGN_PATTERN_PROTOTYPE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

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

    static ProtoType* getPrototype(std::string const& resc);

    virtual void Method(double f){
        this->field=f;
        std::cout<<"Call Method from "<<name
                 <<" with field: "<<field;
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

void ClientCode2(){
    auto p=ProtoType::getPrototype("Prototype1");
    p->Method(4.0);
    delete p;
    std::cout<<std::endl;

    p=ProtoType::getPrototype("Prototype2");
    p->Method(5.0);
    delete p;
    std::cout<<std::endl;

    p=ProtoType::getPrototype("Prototype2");
    p->Method(1.0);
    delete p;
}

//请在执行文件定义
ProtoType * ProtoType::getPrototype(const std::string &resc) {
    if(resc=="Prototype1"){
        static std::unique_ptr<ProtoType> p1
        =std::make_unique<ConcreteProtoType1>("Prototype1",20.0);
        return p1->clone();
    }
    else if(resc=="Prototype2"){
        static std::unique_ptr<ProtoType> p2
        =std::make_unique<ConcreteProtoType2>("Prototype2",30.0);
        return p2->clone();
    }
    else{
        return nullptr;
    }
}
#endif //DESIGN_PATTERN_PROTOTYPE_H
