# Lecture 3 - 10-12-2023
## Javascript
- На синтактично ниво няма класове, но на семантично има
## Operator new
- При оператора new не е нужно фунцкията да връща нещо.То си работи и в двата случая
- 
```
function Person(fiestName,SecondName,birthDayString){
    this.firstname = firstName...
}
var ivan2 = new Person('Ivan','Ivan','2023-01-01')
```
```
Person.prototype// това тук е свойството прототип
Person.prototype.getFullName = function(){
    return this.firstName + ' ' + this.lastNmaae
}
```
```
ivan2['getFullName'] = ivan2.getFullName()
```
```
Array.prototype.log = function...
// По този начин горе всеки масив ще има тази фунцкия лог в себе си
```
```
Object.prototype.test = function
// Всеки обект ше има test  функцията
```
### Questrions
- [].slice.cal(arguments,1)
- Прототипно наследяване(това с проторип отгоре)
- Кои обекти имат прототип свойството(фунцкиите 100 про го имат)???
- scheme and lisp
- Prettier for VS Code
