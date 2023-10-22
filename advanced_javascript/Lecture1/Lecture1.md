# Javascript 07-10-2023
## Introduction
- EcmaScript 5
- Netscape
- ECMAScript standard
- Node.js - gives us the ability to run js on the server,The browser is able to run js - >  да не го рънваме на браузъра а директно на терминала и да виждаме резултата.
    - How to install noje.js - > nodejs.org/en lts = long term support
    - Node Version Manager - > install the latest node
    - $ node -> влизаме в node
      - може примерно да пишем някакви израри и то ни ги evaluate-ва
      - тук можем да пишем някви неща, все едно пиша python в конзолата
    - index.js file - > node index.js - > node ни рънва файл
## Javascript
var myString = 'Hello World';
myString += 'How are you?'; // конкатенация
console.log(myString);
Типа на променливата в js се определя от стойноста на типа на променливата която assign-ваме
### **Типове данни**
атомарни типове
null,boolean,undefined,str
### **Falsy стойности**
false,0,null,'',undefined(мисля че и NaN е тук)//в лекциите казха че NaN никога не е равно на себе си ???
### **Конструктори**
var myStr = String('Hello!'); string factory function
var myStr = 'Hello!';// string literal
var myNumberFour = Number('12345');// превръша от стринг към int
### **Tricky**
'' + 3213 = '3213'
+'3213' = 3123 int
+'asdasd' = NaN
!!'asad'
В js подадем нещо което не е атомарна стойност, то се подава като референция.Атомарните стойности вече тр да си ги подаваме като референция
var aaa; -> стойност undefined
### **Масив**
var myArr = Array();
var myArr = Array(1,2,3);
var myArr = []; //array literal
var myArr = [1,2,3];
Не сме ограничени от типа на нещата в масивите, тоест те не са хомогенни
var arr = [1,2,''];// No homo
push,pop
### **Обекти/Речници**
В js явно обектите са речници ;Д
var myobj = Object();
var obj = {}; //object literal
var obj = {
    prop1:1,
    prop2:'2',
    prop3:[],
};
obj.prop10 = 10000;
разширяваме колекцията
може да нестжаме нестжаме и тн, тоест може да имаме речник в речник в речник и тн
### **Фунцкия**
function sum(a,b){
    return a+b;
} // function declaration
Function('function sum(a,b){
    return a+b;
} ');
имаме възможност от стринг да направим фунцкия, само че това горе не е синтаксисът

Типът на функциите в js е callable object
**eval**

Анонимни функции
function (a,b){
    return a+b;
} // function declaration


var sum = function (a,b){
    return a+b;
}  function expression
### **Boxing**
Атомарните стойности не са обекти, но можем да ги използваме като обекти

var num  = 4.12121
num.toFixed(2);
Не всичко в js e обект, нищо че го казват
Number.prototype - > виждаме различните фунцкии, които имат дадените обекти
### *typeof**
typeof "str" -> string

typeof null - > object - > това тук е бъг

typeof 1 - > string

typeof true - > boolean

typeof {} - > object

typeof function name (params) {} - > function

typeof undefined -> undefined <br>
### **Operator ==**
NaN == Nan - > false -> ecma -international.org - > the abstract equality comparison

== -> невидимо преобразуване от една стойнист към друго

4   == '4' -> true

null == undefined -> true

Хората избягват да правят двойно работно заради тези "подводни камъни"

Появява се string equality comparisson - > ===
### **Синтаксис**
automatic semicolon interstion ->  може да не пишем ; но понякога има проблеми
## Въпроси
var str = "hello";
var hell =  str;
- тук дали hell сочи към това което сочи str,или простосе копира стойността и не сочат към едно и също място в паметта.
## JS code
### **Цикли**
Example 1
```
var arr = [1,2,3,4];
var sum = 0 ;
for(var i = 0 ;i < arr.length;i++){
    sum+= arr[i];
}
console.log(sum);
```
Example 2
``` 
var obj = {
    prop1:100,
    prop2:200,
    prop3:300
}; 
var sum = 0
for(var a in obj){
    sum+=obj[a];//sum+= +obj[a] тук се преобразува към това число с това +
}
console.log(sum);
```
Example 3
```
function containerSum(obj){
    var sum = 0;
    for ( var a in obj){
        sum+=obj[a;]
    }
}
function isContainer(a){
    return a instanceof Array || (typeof a === 'object' && a !== null)
}
function sum(a,b){
    var sum = 0;
    if (a instanceof Array || (typeof a === 'object' && a !== null)){
        sum+=containerSum(a)
    }

    if ( b instanceof Array){ // тук тр да се направи горната проверка и е по яко да се изнесе във функция
        sum+=b;
    }
}
```

### **Debugging**
1.Слагаме breakpoint, като цъкнем отляво
2.Run and Debug - > Nodejs
 
 Debug console 0 - > 
 Може да пишем някакви неща тук примерно

 а -> изкарва стойността на а
 
 отново някви изрази дето се оценяват

 3.Watch - > тук май може динамично да гледаме стойности, по-комплексни

