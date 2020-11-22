//
// Created by ！ on 2020/11/1.
//

#ifndef DESIGN_PATTERN_BUILDER_H
#define DESIGN_PATTERN_BUILDER_H

#include <vector>
#include <string>
#include <memory>

class Product1{
 public:
  std::vector<std::string> _parts;
  //列出产品部分
  void listParts()const{
    std::cout<<"parts of product: ";
    for(auto iter=_parts.begin();iter!=_parts.end();++iter){
      if(*iter==_parts.back())
	std::cout<<*iter;
      else
	std::cout<<*iter<<" ";
    }
    std::cout<<std::endl;
  }
};

class Builder{
 public:
  virtual ~Builder()=default;
  virtual void buildStepA()const =0;
  virtual void buildStepB()const =0;
  virtual void buildStepC()const =0;
  virtual void reset()=0;
};

class ConcreteBuilder1: public Builder{
 private:
  std::unique_ptr<Product1> product;
 public:
  ConcreteBuilder1():product{std::make_unique<Product1>()}{
  }

  ~ConcreteBuilder1(){
  }

  void buildStepA()const override{
    product->_parts.push_back("part A1");
  }

  void buildStepB()const override{
    product->_parts.push_back("part B1");
  }

  void buildStepC()const override{
    product->_parts.push_back("part C1");
  }

  void reset() override{
    product.reset(new Product1);
  }

  auto getProduct(){
    auto result=std::move(product);
    this->reset();
    return result;
  }
};

class Director{
 private:
  Builder* builder;

  void makefull(){
      builder->buildStepA();
      builder->buildStepB();
      builder->buildStepC();
  }

  void makebase(){
      builder->buildStepA();
  }
 public:
  ~Director()=default;
  Director()=default;

  void set_builder(Builder* b){
      builder=b;
  }

  void make(std::string const& s){
      builder->reset();
      if(s=="Simple"){
          makebase();
      }
      else{
          makefull();
      }
  }
};

void client(Director& director){
  //ConcreteBuilder1* build=new ConcreteBuilder1();
  auto build=std::make_unique<ConcreteBuilder1>();
  director.set_builder(build.get());

  std::cout<<"Standard basic product:\n";
  director.make("Simple");
  auto p=build->getProduct();
  p->listParts();

  std::cout<<"standard full featured product:\n";
  director.make("full");
  p=build->getProduct();
  p->listParts();

  std::cout<<"Custom product:\n";
  build->buildStepA();
  build->buildStepC();
  p=build->getProduct();
  p->listParts();
}
  
#endif //DESIGN_PATTERN_BUILDER_H
