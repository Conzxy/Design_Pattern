#ifndef DESIGN_PATTERN_BRIDGE_H
#define DESIGN_PATTERN_BRIDGE_H

#include <iostream>
#include <string>

class Implementation{
public:
    virtual ~Implementation()=default;
    virtual std::string OperationImplementation() const = 0;
};

class concreteImplementationA:public Implementation{
public:
    std::string OperationImplementation()const override{
        return "ConcreteImplementation A:Here's the result on the platform A.\n";
    }
};

class concreteImplementationB:public Implementation{
public:
    std::string OperationImplementation()const override{
        return "ConcreteImplementation B:Here's the result on the platform B.\n";
    }
};

class Abstraction{
protected:
    Implementation *implementation_;
public:
    Abstraction(Implementation* implementation):implementation_{implementation}{};
    virtual ~Abstraction()=default;
    virtual std::string Operation()const{
        return "Abstraction:Base Operation with:\n"+
               this->implementation_->OperationImplementation();
    }
};

class ExtendedAbstraction :public Abstraction{
public:
    ExtendedAbstraction(Implementation* implementation):Abstraction(implementation){}
    std::string Operation()const override{
        return "ExtendedAbstraction:Extended Operation with:\n"+
               this->implementation_->OperationImplementation();
    }
};

void ClientCode(Abstraction const& abstraction){
    std::cout<<abstraction.Operation();
}

/*int main(){
    unique_ptr<Implementation> implementation{new concreteImplementationA};

    unique_ptr<Abstraction> abstraction{new Abstraction(implementation.get())};

    ClientCode(*abstraction);

    implementation.reset(new concreteImplementationB);
    abstraction.reset(new ExtendedAbstraction{implementation.get()});

    ClientCode(*abstraction);
}*/
#endif //DESIGN_PATTERN_BRIDGE_H
