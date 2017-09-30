#include <stdio.h>
//对于无符号类型来说右移操作符是不用担心逻辑移动或者是算数移动的，所以结果都一样。 
int main(){
	int a =123;
	int b =342;
	printf("%d\n",a&b); //d表示10进制运算符 //82  & 也就是11->1 
	printf("%d\n",~a); //0->1,1->0 
	printf("%d\n",a|b); 
	printf("%d\n",a^b); //抑或运算 ，也就是0->1
	printf("%d",a<<2);
	printf("%d",a>>2);
	return 0;
}
//包括了算数移位和逻辑移位。
//算数移位就是根据移动出来的东西决定你移动进去的东西 
//不仅仅二进制存在着位运算，所有的进制都存在着位运算 

//位运算符与赋值运算符可以组成复合赋值运算符。
//   例如: &=, |=, >>=, <<=, ∧=
//   例：  a & = b相当于 a = a & b
//         a << =2相当于a = a << 2


//然后算数移位的话我觉得是这样的
//1110011右边移动的时候，由于总共的位数的不变的，所以1110011>>2  为  1111100 
