// // Пример1
// const yellow = document.getElementById("yellow");
// const green = document.getElementById("green"); 
// const red = document.getElementById("red");
// const storage = document.getElementById("background-example");
// let input = document.getElementsByClassName("donkey");
// console.log(input);

// for (i of input){
//     i.addEventListener("click",function(){ storage.style.backgroundColor = this.value;},false);
// }
// // disabling a stylesheet
// console.log(document.styleSheets.item(0).href);
// const el = document.getElementById("h");
// console.log(el.sheet.title);

// var ss = new CSSStyleSheet();
// ss.insertRule("a {color:red;}");
// ss.insertRule("b {color:red;}");
// console.log(ss.cssRules[0].cssText,ss.cssRules[1].cssText);
// ss.replace("a {color:green }");
// console.log(ss.cssRules[0].cssText);    
// console.log(ss.cssRules[1].cssText);




const box = document.getElementById("box");
const button = document.getElementById("box-button");
button.addEventListener("click",function() {
transform[0].angle.value = 0;
box.attributeStyleMap.set('transform', transform); // commit it.

});
const rotate = new CSSRotate(0, 0, 1, CSS.deg(0));
const transform = new CSSTransformValue([rotate]);

box.attributeStyleMap.set('transform', transform);

let animationId; // declare animationId outside of event listeners

box.addEventListener('mouseenter', function() {
  // start animation on mouse enter
  animationId = requestAnimationFrame(function animate() {
    box.attributeStyleMap.set('background-color','green');
    transform[0].angle.value += 5; // Update the transform's angle.
    box.attributeStyleMap.set('transform', transform); // commit it.
    animationId = requestAnimationFrame(animate); // schedule next animation frame
  });
});

box.addEventListener('mouseleave', function() {
  // stop animation on mouse leave
  cancelAnimationFrame(animationId);
  animationId = null;
  box.attributeStyleMap.set('background-color','red');
});
console.log(button.attributeStyleMap.has('opacity'));
