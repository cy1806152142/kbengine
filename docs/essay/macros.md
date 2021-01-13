#### define中的特殊符号\,#,##的作用

##### 1. 符号"\\"

用于多行定义,每行的最后加上"\\",  "\\" **后面不能再有其他字符**

```c++
#define MAX(a,b)  \
    if(a>b)\
  		return a;\
  	else\
  		return b;
```



##### 2. **符号"#“和”##"**

\#是把参数字符串化, ##是连接两个参数

如果字符参数加 " "，那么宏展开后就是字符串；如果字符参数没有" "，那么宏展开后就是变量名

```c++
#include <iostream>
using namespace std;

#define A(x) x
#define B(x) #x
#define C(x,y) x##y
#define D(x,y) int x##y = 0;
#define E()    \
	D(hello, world)

int main()
{
	cout << A("hello") << endl;  //hello
	cout << B(hello) << endl;    //hello
    cout << B("hello") << endl;  //"hello" 实际是 " + hello + "
	cout << C("hello", "world") << endl; //helloworld
    C(hello, world);  //Error:  未定义的变量 helloworld 
    D(a, b);         //int ab = 0;
    E(hello, world); // int helloworld = 0;
    E("hello", "world") //Error: int "helloworld" = 0;

	return 0;
}
       
```

