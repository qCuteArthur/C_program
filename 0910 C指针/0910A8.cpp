C语言中指针是个非常麻烦的事件，本人大学学了几年指针，用起来还是丈二和尚，摸不着头脑，特别是在函数中作为参数传递，申请空间什么的，一头雾水，看到这篇文件写的还比较详尽，因此转载存档！！！！！！！！！

为什么？ 
-----------------------------------------------
1.被分配内存的是行参s，p没有分配内存 
2.被分配内存的是行参s指向的指针p，所以分配了内存 
------------------------------------------------
不是指针没明白，是函数调用的问题！看看这段： 
7.4指针参数是如何传递内存的？ 
如果函数的参数是一个指针，不要指望用该指针去申请动态内存。示例7-4-1中，Test函数的语句GetMemory(str, 200)并没有使str获得期望的内存，str依旧是NULL，为什么？ 
void GetMemory(char *p, int num) 
{ 
p = (char *)malloc(sizeof(char) * num); 
}
 
void Test(void) 
{ 
char *str = NULL; 
GetMemory(str, 100); // str 仍然为 NULL 
strcpy(str, "hello"); // 运行错误 
}
 
示例7-4-1 试图用指针参数申请动态内存 
毛 病出在函数GetMemory中。编译器总是要为函数的每个参数制作临时副本，指针参数p的副本是 _p，编译器使 _p = p。如果函数体内的程序修改了_p的内容，就导致参数p的内容作相应的修改。这就是指针可以用作输出参数的原因。在本例中，_p申请了新的内存，只是把 _p所指的内存地址改变了，但是p丝毫未变。所以函数GetMemory并不能输出任何东西。事实上，每执行一次GetMemory就会泄露一块内存，因 为没有用free释放内存。 
如果非得要用指针参数去申请内存，那么应该改用“指向指针的指针”，见示例7-4-2。 
void GetMemory2(char **p, int num) 
{ 
*p = (char *)malloc(sizeof(char) * num); 
} 
void Test2(void) 
{ 
char *str = NULL; 
GetMemory2(&str, 100); // 注意参数是 &str，而不是str 
strcpy(str, "hello"); 
cout<< str << endl; 
free(str); 
} 
示例7-4-2用指向指针的指针申请动态内存 
由于“指向指针的指针”这个概念不容易理解，我们可以用函数返回值来传递动态内存。这种方法更加简单，见示例7-4-3。 
char *GetMemory3(int num) 
{ 
char *p = (char *)malloc(sizeof(char) * num); 
return p; 
} 
void Test3(void) 
{ 
char *str = NULL; 
str = GetMemory3(100); 
strcpy(str, "hello"); 
cout<< str << endl; 
free(str); 
} 
示例7-4-3 用函数返回值来传递动态内存 
用函数返回值来传递动态内存这种方法虽然好用，但是常常有人把return语句用错了。这里强调不要用return语句返回指向“栈内存”的指针，因为该内存在函数结束时自动消亡，见示例7-4-4。 
char *GetString(void) 
{ 
char p[] = "hello world"; 
return p; // 编译器将提出警告 
} 
void Test4(void) 
{ 
char *str = NULL; 
str = GetString(); // str 的内容是垃圾 
cout<< str << endl; 
} 
示例7-4-4 return语句返回指向“栈内存”的指针 
用调试器逐步跟踪Test4，发现执行str = GetString语句后str不再是NULL指针，但是str的内容不是“hello world”而是垃圾。 
如果把示例7-4-4改写成示例7-4-5，会怎么样？ 
char *GetString2(void) 
{ 
char *p = "hello world"; 
return p; 
} 
void Test5(void) 
{ 
char *str = NULL; 
str = GetString2(); 
cout<< str << endl; 
} 
示例7-4-5 return语句返回常量字符串 
函 数Test5运行虽然不会出错，但是函数GetString2的设计概念却是错误的。因为GetString2内的“hello world”是常量字符串，位于静态存储区，它在程序生命期内恒定不变。无论什么时候调用GetString2，它返回的始终是同一个“只读”的内存 块。 
--------------------------------------------------------------- 
看看林锐的《高质量的C/C++编程》呀，上面讲得很清楚的 
--------------------------------------------------------------- 
对于1和2： 
如果传入的是一级指针S的话， 
那么函数中将使用的是S的拷贝， 
要改变S的值，只能传入指向S的指针，即二级指针 
--------------------------------------------------------------- 
程序1： 
void myMalloc(char *s) //我想在函数中分配内存,再返回 
{ 
s=(char *) malloc(100); // s是值参， 函数返回后就回复传递前的数值，无法带回分配的结果 
} 
这个和调用 void func (int i) {i=1;}; 一样，退出函数体，i指复原的 
程序2：void myMalloc(char **s) 
{


*s=(char *) malloc(100); // 这个是可以的 
} 
等价于 
void int func(int * pI) {*pI=1;} pI指针不变，指针指向的数据内容是变化的 
值参本身不变，但是值参指向的内存的内容发生了变化。 
程序3： 
void fun(int *p) 
{ 
int b=100; 
p=&b; // 等同于第一个问题， b的地址并没有被返回 
} 
程序4： 
void fun(int *p) 
{ 
*p=100; // okay 
} 
--------------------------------------------------------------- 
其实楼主的问题和指针没有多大关系，就是行参和值参的问题 
函数调用的时候，值参传递的是数值，是不会返回的 
这个数值，在函数体内部相当于一个变量，是可以改变，但是这个改变是无法带出函数体外部的 
--------------------------------------------------------------- 
程序1： 
void myMalloc(char *s) //我想在函数中分配内存,再返回 
{ 
s=(char *) malloc(100);//传过来的是P所指的地址,并不是P的地址,所以改变S不会改变P 
} 
void main() 
{ 
char *p=NULL; 
myMalloc(p); //这里的p实际还是NULL,p的值没有改变，为什么？ 
if(p) free(p); 
} 
程序2：void myMalloc(char **s) 
{ 
*s=(char *) malloc(100);//S指向的是P的地址,所以改变了P所指的内存单元. 
} 
void main() 
{ 
char *p=NULL; 
myMalloc(&p); //这里的p可以得到正确的值了 
if(p) free(p); 
} 
程序3： 
#include<stdio.h> 
void fun(int *p) 
{ 
int b=100; 
p=&b; 
} 
main() 
{ 
int a=10; 
int *q; 
q=&a; 
printf("%d/n",*q); 
fun(q);////道理同第一个程序. 
printf("%d/n",*q); 
return 0; 
} 
结果为 
10 
10 
程序4： 
#include<stdio.h> 
void fun(int *p) 
{ 
*p=100;//参数P和实参P所指的内存单元是相同的.所以改变了参数P的内存单元内容,就改变了实参 
//的内存单元内容 
} 
main() 
{ 
int a=10; 
int *q; 
q=&a; 
printf("%d/n",*q); 
fun(q); 
printf("%d/n",*q); 
return 0; 
} 
结果为 
10 
100 
为什么？ 
--------------------------------------------------------------- 
void main() 
{ 
char *p=NULL; 
myMalloc(p); //这里的p实际还是NULL,p的值没有改变，为什么？ 
if(p) free(p); 
} 
void myMalloc(char *s) //我想在函数中分配内存,再返回 
{ 
s=(char *) malloc(100); 
} 
myMalloc(p)的执行过程: 
分配一个临时变量char *s，s的值等于p，也就是NULL，但是s占用的是与p不同的内存空间。此后函数的执行与p一点关系都没有了！只是用p的值来初始化s。 
然后s=(char *) malloc(100)，把s的值赋成malloc的地址，对p的值没有任何影响。p的值还是NULL。 
注意指针变量只是一个特殊的变量，实际上它存的是整数值，但是它是内存中的某个地址。通过它可以访问这个地址。 
程序2：void myMalloc(char **s) 
{ 
*s=(char *) malloc(100); 
} 
void main() 
{ 
char *p=NULL; 
myMalloc(&p); //这里的p可以得到正确的值了 
if(p) free(p); 
} 
程序2是正确的，为什么呢？看一个执行过程就知道了： 
myMalloc(&p);将p的地址传入函数，假设存储p变量的地址是0x5555，则0x5555这个地址存的是指针变量p的值，也就是Ox5555指向p。 
调用的时候同样分配一个临时变量char **s，此时s 的值是&p的值也就是0x5555，但是s所占的空间是另外的空间，只不过它所指向的值是一个地址：Ox5555。 
*s=(char *) malloc(100);这一句话的意思是将s所指向的值，也就是0x5555这个位置上的变量的值赋为(char *) malloc(100)，而0x5555这个位置上存的是恰好是指针变量p，这样p的值就变成了(char *) malloc(100)的值。即p的值是新分配的这块内存的起始地址。 
这个问题理解起来有点绕，关键是理解变量作函数形参调用的 时候都是要分配一个副本，不管是传值还是传址。传入后就和形参没有关系了，它不会改变形参的值。myMalloc(p)不会改变p的值，p的值当然是 NULL，它只能改变p所指向的内存地址的值。但是myMalloc(&p)为什么就可以了，它不会改变(&p)的值也不可能改变，但是 它可以改变(&p)所指向内存地址的值，即p的值。 
--------------------------------------------------------------- 
你要弄清楚的是指针变量和指针所指的变量（可能是一片内存）。 
指针变量和普通变量一样存储的，

//////////////////////////////////////////////////////////////////


1.如果是函数内进行内存申请，很简单，标准用法就可以了：
test()
{
int *array;
array=(int *)malloc(sizeof(int)*10);//申请10*4 bytes，即10个单位的int内存单元
}
注意，malloc使用简单，但是注意参数和返回值，参数是申请内存的字节数，多字节的类型如int，short,float等需要乘上类型字节数，返回值是没有定义类型的指针，使用时需要自己指定。
2.使用一级指针实现内存申请，通过函数返回值带出malloc的地址：
char *my_malloc(int m)
{
char *p;
p=malloc(m);
return p;
}
test()
{
char * buff=NULL; //指针如果在函数内没有赋值，注意开始赋值为NULL
buff=my_malloc(10);
printf("buff adress is %x/n",buff);
free(buff); 
}
3.使用二级指针实现内存申请，通过指针值传递：
void my_malloc1(char **p1)
{
*p1=(char *)malloc(100);
}
test()
{
char *buffer=NULL;
my_malloc1(&buffer);
printf("buffer adress is %x/n",buffer);
free(buffer);
}
小结：一级指针和二级指针在做形参时的不同：指针用作形参，改变指针地址则值不能传回，改变指针内容而地址不变则值可以传回。（特殊情况：改变指针地址采用返回值也可以传回地址）
对于一级指针，做形参时传入地址，如果函数只改变该指针内容，OK，该指针可以正常返回，如果函数改变了指针地址，除非返回该指针，否则该指针不能正常返回，函数内对指针的操作将无效。
对于二级指针，做形参时传入地址（注意此时传入的是二级指针的地址），如果改变该二级指针地址（**p），对该指针的操作也将无效，但是改变二级指针的内容（例如*p），则该二级指针可以正常返回。
总之，指针使用最关键的是弄清地址和内容，指针做形参时只有改变其内容时才能正常返回。
4.编程实例：
/*
date:20100823
file name:my_pointer.c
description:指针作为形参的值传递分析
result：
1.指针作为形参时，如果只需要改变指针指向的值，可以使用一级指针，如果需要改变指针本身的地址
，则需要使用二级指针,相当于改变的是一级指针指向的值。
2.指针作为形参时，指针指向的内容变化是可以带回的，指针地址的变化是不可带回的，即指针作为参
数，其地址不可改变，否则形参就无法传回实参的值。
*/
/*********************************************************************************/
//指针作为形参，指针指向的内容改变，函数返回时这种变化是可以带回的
void change(int *p)
{
*p+=5; 
}
test1() 
{
int a=1;
change(&a);
printf("After change a is %d/n",a); //结果为6
}
/*********************************************************************************/
//指针作为形参，指针本身的地址改变，函数返回时这种变化将无效
void my_malloc(char *pp,int num) 
{
pp=(char *)malloc(num); 
}
test2() 
{
char *buf=NULL;
my_malloc(buf,100);
printf("After my_malloc buf adress is %x/n",buf); //函数返回后,buf的地址依然为NULL 
strcpy(buf,"hello"); //这里会出错，运行出现段错误，程序直接退出了，下面的输
出也没有了
puts(buf);
}
main()
{
test1();
//test2();
