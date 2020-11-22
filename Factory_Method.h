//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2020/8/5.
//

#ifndef DESIGN_PATTERN_FACTORY_METHOD_H
#define DESIGN_PATTERN_FACTORY_METHOD_H

#include <iostream>

/*
 * Factory Method：
 * 在父类中提供一个创建对象的方法，而子类可以决定实例化对象的类型
 */

class Product{
public:
    virtual ~Product()=default;
    virtual std::string operation()const=0;
};

class ConcreteProduct1: public Product{
public:
    std::string operation()const override{
        return "ConcreteProduct1";
    }
};

class ConcreteProduct2: public Product{
public:
    std::string operation()const override{
        return "ConcreteProduct2";
    }
};

class Creator{
public:
    virtual ~Creator()=default;
    virtual Product* FactoryMethod()const=0;
    std::string someoperation()const{
        Product* product=this->FactoryMethod();
        std::string result="Creator:The same creator's code has just work with "+product->operation();

        delete product;
        return result;
    }
};

class ConcreteCreator1: public Creator{
public:
    Product* FactoryMethod()const override{
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2: public Creator{
public:
    Product* FactoryMethod()const override{
        return new ConcreteProduct2();
    }
};

class Client{
public:
    void operator()(const Creator* crt){
        std::cout<<"Client:I'm not aware of the Creator's class,but it still works.\n"
                 <<crt->someoperation();
    }
};

/*
 * main
 * std::cout << "App: Launched with the ConcreteCreator1.\n";
    Creator* creator = new ConcreteCreator1();
    Client c1;
    c1(creator);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2();
    Client c2;
    c2(creator2);

    delete creator;
    delete creator2;
    return 0;
 */
#endif //DESIGN_PATTERN_FACTORY_METHOD_H
