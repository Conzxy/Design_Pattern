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

### [Normal（对象适配器）](https://github.com/Conzxy/Design_Pattern/blob/main/src/Adapter.h)

