# 适配器（Adapter）

## 特征

* 结构性设计模式

* 使接口不兼容的对象相互合作

## 结构

### 对象适配器

构成原则：适配器实现了其中一个对象的接口，并对另一个对象进行封装。

![](https://img-blog.csdnimg.cn/20201003211847256.png)

1.client：包含当前程序业务逻辑

2.client interface：描述了其他类与client代码合作时必须遵循的协议

3.service：通常来自第三方或遗留系统。client于其接口不兼容，因此无法直接调用。

4.Adapter：可以同时与client和service交互，在实现client interface的同时封装了service对象。adapter接受client通过adapter接口发起的调用，并将其转换为适用于被封装service对象的调用。

client代码**只需要通过接口与adapter交互即可，无需与具体的适配器类耦合**。因此，你可以向程序中添加新类型的适配器而无需修改已有代码

### 类适配器

![](https://img-blog.csdnimg.cn/20201003211847233.png)

类适配器不封装任何对象，因为他同时继承client和service的行为。适配功能在重写的方法中完成，最后生成的adapter可替代已有的client进行使用。

## Sample Code

### Normal（对象适配器）

```cpp
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

int main(){
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

}
```
