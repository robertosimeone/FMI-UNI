// const ball = document.getElementById("foo");
// const container = document.getElementById("cont");
// console.log(container.style.height);
// document.addEventListener("click",(ev) => {
//     f.style.transform = `translateY(${ev.clientY - 25}px)`;
//     f.style.transform += `translateX(${ev.clientX - 25}px)`;
//   },
//   true
// );

const f = document.getElementById("foo");
const d = document.getElementById("foo1");
const div = document.getElementById("cc");
div.addEventListener(
  "click",
  (ev) => {
    f.style.transform = `translateY(${ev.clientY - 25}px)`;
    f.style.transform += `translateX(${ev.clientX - 25}px)`;
    console.log("clientY",ev.clientY);
    console.log("clientX",ev.clientX);
  },
  false
);
