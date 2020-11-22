# 桥接模式（Bridge）

## 特征

* 结构性设计模式

* 可将一个大类或一系列紧密相关的类拆分为`抽象`或`实现`两个独立的层次结构，从而能在开发时分别使用

## 问题

![](https://img-blog.csdnimg.cn/20201004142538918.png)

现有一个shape类，他能扩展出两个子类：Circle和Square，我们希望对这样的类层次结构进行扩展使其包含颜色，第一想到的可能是创建红色和蓝色的shape子类，但是全部覆盖需要四个类才行。  

在层次结构中新增形状和颜色只会导致代码复杂度指数上升，如果你打算增加三角形，则需要新增两个子类，你如果还打算加入新的颜色，则新增三个子类，依次类推，只会越来越糟糕。

## 解决方案

我们在处理类继承时，常常会试图在多个独立维度上进行扩展——形状和颜色就是两个独立的维度。桥接模式通过`改继承为组合`，抽取其中一个维度并使之成为独立的类层次，这样在初始类中引用新层次的对象，从而使得一个类不必拥有所有的状态和行为。

![](https://img-blog.csdnimg.cn/20201004142620785.png)

这样一来，我们将颜色相关的代码抽取到了`红色`和`蓝色`两个子类的`颜色`类中，然后在形状类中添加一个指向某一颜色对象的`引用成员变量`。这样形状类可以将所有与颜色相关的工作委派给连入的颜色对象。这样的引用就成为了`形状`和`颜色`的`桥梁`。此后，**新增颜色就不需要修改形状的类层次**，反之亦然。

## 抽象部分和实现部分

四人帮的著作中在桥接定义中提出了**抽象部分**和**实现部分**两个术语。  

**抽象部分**（亦称**接口**）是某些实体的高阶控制层。该层自身不完成任何具体工作，它需要将工作委派给**实现部分**层（亦称**平台**）。

PS：这里提高的接口等内容与编程语言中的**接口**或**抽象类**无关。

## 结构

![](https://img-blog.csdnimg.cn/202010041616147.png)1.**抽象部分**（Abstraction）：提供高层控制逻辑，依赖于完成底层实际工作的**实现对象**。

2.**实现部分**（implementation）：为所有具体实现声明通用接口。**抽象部分仅能通过在这里声明的方法与实现对象交互**。

3.**具体实现**（Concrete Implementation）：包括特定于平台的代码

4.**精确抽象**（Refined Abstration）：提供控制逻辑的`变体`。与父类一样，它们都是通过通用实现接口与不同的实现进行交互。

客户端（Client）只需要关心如何与抽象部分合作，但是得需要将抽象对象与一个实现对象连接起来。

## Sample Code

```cpp
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

int main(){
    unique_ptr<Implementation> implementation{new concreteImplementationA};

    unique_ptr<Abstraction> abstraction{new Abstraction(implementation.get())};

    ClientCode(*abstraction);

    implementation.reset(new concreteImplementationB);
    abstraction.reset(new ExtendedAbstraction{implementation.get()});

    ClientCode(*abstraction);
}
```

## 适合应用场景

* 拆分或重组一个具有**多重功能**的庞杂类

* 希望在几个**独立维度**上扩展一个类

* 需要在运行时切换不同**实现方法**
  
  桥接模式可以替换抽象部分的实现对象，具体操作上面Sample Code也给出了，和给成员变量赋新值一样简单。

## 实现方式

* 明确类中独立的维度

* 了解客户端的业务需求并在抽象基类（并不是指`抽象类`，而是作为抽象部分的基类）中定义它们

* 确定在所有平台上都可执行的业务，并在**通用实现接口**中声明抽象部分所需的业务

* 为你域内的所有平台创建**具体实现类**，确保它们遵循实现部分的接口

* 在抽象类中添加**指向实现类型的引用成员变量**。抽象部分会将大部分工作委派给该成员变量所指向的实现对象

* 如果你的高层逻辑有多个变体，则可以通过扩展抽象基类为每个变体创建一个精确抽象

* 客户端代码必须把**实现对象传递给抽象部分的构造函数**才能使其相互关联；i.e 客户端只需与抽象对象进行交互，而无需和实现对象打交道
