#ifndef DESIGN_PATTERN_PROXY_H
#define DESIGN_PATTERN_PROXY_H

#include <iostream>

class Subject{
public:
    virtual void Request()const=0;
};

class RealSubject:public Subject{
public:
    void Request()const override{
        std::cout<<"ReadSubject:Handing request.\n";
    }
};

class Proxy:public Subject{
private:
    RealSubject *real;

    bool CheckAccess()const{
        std::cout<<"Proxy:Checking access prior to firing a real request.\n";
        return true;
    }

    void LogAccess()const {
        std::cout << "Proxy:Logging the time of request.\n";
    }
public:
    Proxy(RealSubject* real_):real(new RealSubject(*real_)){}
    ~Proxy(){ delete real; }

    void Request()const override{
        if(CheckAccess()){
            real->Request();
            LogAccess();
        }
    }
};

void ClientCode(Subject const& subject){
    subject.Request();
}

/*
 * int main() {
    std::cout<<"Client:Executing the client code with a real subject:\n";
    RealSubject* real_subject=new RealSubject;
    ClientCode(*real_subject);
    std::cout<<"\n";
    std::cout<<"Client:Executing the same client code with a proxy:\n";
    Proxy* proxy=new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
}
 */
#endif //DESIGN_PATTERN_PROXY_H
