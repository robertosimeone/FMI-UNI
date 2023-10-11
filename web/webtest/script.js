var role = document.getElementsByName('role_choice');
var role_value;
const but = document.getElementById('submit');
but.addEventListener('click',()=>{
    for(var i = 0 ; i < role.length;i++){
        if(role[i].checked){
            role_value = role[i];
        }
    }
    console.log(role_value.name,role_value.value);
})
