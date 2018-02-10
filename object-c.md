
### 成员函数

```
- (void)abc;
- (void)setCSS:(NSString *)css;
- (void)editorDidChangeWithText:(NSString *)text andHTML:(NSString *)html;
```

### 属性

```
@property (nonatomic,copy) NSString *name;
```

编译器将属性自动转换成了成员变量，并且自动生成了getter和setter方法。因此两者最直观的区别是属性会有相应的getter方法和setter方法，而成员变量没有，另外，外部访问属性可以用"."来访问，访问成员变量需要用"->"来访问



1. 如果没有为属性指定任何特性，它们默认使用nonatomic和assign

* readonly 只读
* readwrite 可以进行访问与读取
* nonatomic 非原子
* atomic 原子
* retain 一般用在对象类型, 比如我们自己写的类,还有数组NSArray中会用到
* assgin 一般用在NSInteger和CGFloat中,因为他们在栈区,不需要内存管理,所以用assgin
* copy 一般只会用在字符串中


### string Nsstring

* std::string转为 NsString

```
std::string str1 = "hello";
NSString *str= [NSString stringWithUTF8String:str1.c_str()];
```

* NsString 转为 std::string 

```
NSString *str;
[str UTF8String]
```


###  include import

```
#include是c/c++导入头文件的关键字，
#import 是oc导入头文件的关键字，#import会自动导入一次，不会重复导入，不会引起交叉编译
```
