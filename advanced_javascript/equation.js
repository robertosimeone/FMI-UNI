var str = "1 + 4 = 5";
var x = str.split('=');
console.log(typeof(x));
//"7 - 3 * 2 + 1 = 4 * 2 + 1 = 8 + 1 = 9" => "2 / 3"
var priority = ["*",'/','+','-'];
function replace_occurances(c,str){
    new_str = ""
    for(var i = 0;i<str.length;i++){
        if(str[i]!=' '){
        new_str+=str[i];
        }
    }
    return new_str;
}
for(var i = 0 ; i < x.length;i++){
    x[i] = replace_occurances(" ",x[i]);
}

// for(var i = 0 ; i < x.length;i++){
//     console.log(x[i]);
// }
for(var i = 0 ; i < x.length-1;i++){
    first = x[i].split('');
    second = x[i+1].split('');
    
}
function calculate_result(arr){
    var priority = ["*",'/','+','-'];
    for(var j = 0; j < priority.length;j++){
        var current_symbol = priority[j];
        
    }
}
var str = "1+3-2*4/5";
// var x = str.split(/[\+\-\*\/]/);
var x = str.split("");
for(var i = 0 ; i < x.length;i++){
    console.log(x[i]);
}
//splice index,number of elements;

var str = "1 + 2"
