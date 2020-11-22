#ifndef DESIGN_PATTERN_ADAPTER_H
#define DESIGN_PATTERN_ADAPTER_H

#include <string>
#include <iostream>
#include <algorithm>


//client interface:
//The Target defines the domain-specific interface used by the ClientCode
class Target{
public:
    virtual ~Target()=default;

    virtual std::string Request()const{
        return "Target:The default target's behavior:";
    }
};

//service:The Adaptee contains some useful behavior,与ClientCode不兼容，所以需要在使用前提供adapter
class Adaptee{
public:
    std::string SpecificRequest()const{
        return ".eetpadA eht fo roivaheb laicepS:";
    }
};

//Adapter：封装adaptee，并实现Target的接口，ClientCode通过Adapter接口的调用转换为适用于被封装adaptee的调用,这样Target的接口就与Adaptee的接口兼容了

class Adapter:public Target{
private:
    Adaptee* adaptee_;

public:
    Adapter(Adaptee* adaptee):adaptee_{adaptee}{}
    std::string Request()const override{
        std::string to_reverse=this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(),to_reverse.end());
        return "Adapter:(TRANSLATED)"+to_reverse;
    }
};

//client code
void ClientCode(Target const* target){
    std::cout<<target->Request();
}

/*int main(){
    cout<<"Client I can work just fine with the Target objects:\n";
    Target *target=new Target;
    ClientCode(target);
    cout<<"\n\n";
    Adaptee* adaptee=new Adaptee;
    cout<<"Client:The Adaptee class has a weird interface.See,I don't understand it:\n";
    cout<<"Adaptee:"<<adaptee->SpecificRequest();
    cout<<"\n\n";
    cout<<"Client:But I can work with it via the Adapter:\n";
    Adapter* adapter=new Adapter(adaptee);
    ClientCode(adapter);
    cout<<endl;

    delete target;
    delete adaptee;
    delete adapter;
}*/
#endif //DESIGN_PATTERN_ADAPTER_H
