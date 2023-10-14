# **Javascript 14-10-2023**
## **Python vs JS**
python - gil -> global interpreter log </br> 
## **Tricky**
Функция във функция във фунцкия във функция... и може да извикаме някакси тая най-долната
## **Typescript??**
Няма typescript,който да работи в runtime
## **Javascript code snippets**
- Hoisting - всички ключови думи като var и function се парсеват все едно в началото на кода са декларирани.
- в JS няма block-scoping,имаме function scoping,тоест функциите ни създават нова област на видимост
```
var a = 10;
if (true){
    var b = 30;
    console.log(a);
}
function test(a,b){
    console.log(a,b);
}
test(a,200)
```
```
function a(robi,bobi){
    var = a;
    console.log(a);
    {
        {
            {
                a = 10
            }
        }
    }
    console.log(a);
} # e tiq {{{}}} sa lbockove ama malko stranno kak ne sa sled if ili neshto podobno - proveri go
```
3) Проверка дали едно число е NaN
```
Number.isNan(NaN)
```
4) Област на видимост от Георги§
```
#include <iostream>

int main() {
    int x = 10; // Global scope within main()

    std::cout << "Global x: " << x << std::endl;

    {
        int x = 20; // Block scope, shadows global x
        std::cout << "Block x: " << x << std::endl;
    }

    std::cout << "Global x after block: " << x << std::endl; // Still 10

    if (true) {
        int x = 30; // New block scope in 'if'
        std::cout << "If-block x: " << x << std::endl;
    }

    std::cout << "Global x after 'if': " << x << std::endl; // Still 10

    return 0;
}
```
5)
```
function hello(a,b,c){ // a = 1,b = 2, c = 3 - > все едно тук така се декларират(hoisting)
    console.log(arguments) // всички аргументи на функцията
}
hello(1,2,3,4,5) // може да извикаме функция с повече аргументи
```
6)Closure
```
var a = 0;
function thisIsClosure(){
return a+10;
}
var result = thisIsClosure();
// Фунцкия, която взима променлива която е от по-горна област на видимост и я използва
```
```
function get(a){
    a = a || 0;
    return funciton thisIsClosure(){
        return a +10;
    }
}
var result = getThisClosure(10)();
```
```
function get(a){
    a = a || 0;
    return funciton thisIsClosure(){
        return b +10;
    }
    var b = 30;
    return thisIsClosure; // tuk b shte se vurne 40
    // mn stranno vikane na gornata  funkciq bez ();
}
```
```
function getNaturalNumber(){
    var counter = 0;
    return function naturalGenerator(){
        return counter++;
    }
    var gen = getNaturalNumberGenerator();
    console.log(gen());
    console.log(gen());
    console.log(gen()); //BRUH
}
```
```
function getNaturalNumber(){
    var counter = 0;
    return function naturalGenerator(fn){
        if(fn){fn(counter);}
        return counter++;
    }
    var gen = getNaturalNumberGenerator();
    console,log((gen(function(test)))){
        console.log(test);
    }
    console.log(gen());
    console.log(gen());
    console.log(gen()); //BRUH
    // на този пример обаче понеже работим с примитивни стойности, те се копират и няма как да манипулираме counter в функцията
    вместо fn(counter - > counter=fn(counter;))
}
```
![image](/Users/robertborisov/UNI/advanced_javascript/image.jpeg)
това тук ще гръмне(долното)
Function declaration sa dostupni abs ot nachaloto,a function declaration veche kogato e = na edi si kwo
![image](/Users/robertborisov/UNI/advanced_javascript/image3.jpeg) това тук ще гръмне

```
function myFunction2(){
    console.log(this);
}
myFunction2();
myFunction2.call('Hello from call');// this = Hello from call
// може да подаден и примерно myFunction2(a,b) и от call("hello",1,2) и то a b  ще станат  1 2
myFunction2.apply('Hello from apply');// this = Hello from apply; apply бачка със списък, вместо просто аргумент
var myFunction3 = myfunction2.bind('Hello from bind');//this = hello from bind(просто прави други функция)
myFunction3();
```
```
var context = {
    fun: myFunction2
};
context.fun();
```
![image](/Users/robertborisov/UNI/advanced_javascript/image3 2.jpeg)
## **Questions**
- Service buss?
- Защо има нужда да пишем име на генератора? - > за да може като дебъгваме да виждаме откъде идва самото нещо , иначе ще ни пише anonymous(за да знаем къде се намираме като дебъгваме)
- Методд vs Функция  in JS.
- Какво е контекст? - стойността на думата this във функцията
- каква е разликата между контекст и област на видимост? област на видимост е променливите които виждаме във функцията
## **Линкове**
https://gist.github.com/stelf/6c768875e174085c0e3ce43b564fc0bd
