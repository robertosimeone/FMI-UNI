const box = document.getElementById("box");
const button = document.getElementById("box-button");
const measurer = document.getElementById("measurer");
button.addEventListener("click",function() {
transform[0].angle.value = 0;
box.attributeStyleMap.set('transform', transform); // commit it.
measurer.innerHTML = "0";

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
    measurer.innerHTML = "Rotating " + transform[0].angle;
  });
});

box.addEventListener('mouseleave', function() {
  // stop animation on mouse leave
  cancelAnimationFrame(animationId);
  measurer.innerHTML =  transform[0].angle;
  animationId = null;
  box.attributeStyleMap.set('background-color','red');
});
console.log(button.attributeStyleMap.has('opacity'));


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const ball = document.getElementById("bll");
const div = document.getElementById("bc");
function getPosition(el) {
    var xPosition = 0;
    var yPosition = 0;
   
    while (el) {
      if (el.tagName == "BODY") {
        // deal with browser quirks with body/window/document and page scroll
        var xScrollPos = el.scrollLeft || document.documentElement.scrollLeft;
        var yScrollPos = el.scrollTop || document.documentElement.scrollTop;
   
        xPosition += (el.offsetLeft - xScrollPos + el.clientLeft);
        yPosition += (el.offsetTop - yScrollPos + el.clientTop);
      } else {
        xPosition += (el.offsetLeft - el.scrollLeft + el.clientLeft);
        yPosition += (el.offsetTop - el.scrollTop + el.clientTop);
      }
   
      el = el.offsetParent;
    }
    return {
      x: xPosition,
      y: yPosition
    };
  }
div.addEventListener("click",getClickPosition,false);
function getClickPosition(e){
    var parentPosition = getPosition(div);
    var xPosition = e.clientX - parentPosition.x - (ball.offsetWidth/2);
    var yPosition = e.clientY -parentPosition.y -(ball.offsetHeight/2);
    var translate3dValue = "translate3d(" + xPosition + "px," +yPosition + "px,0)";
    ball.style.transform = translate3dValue;
}