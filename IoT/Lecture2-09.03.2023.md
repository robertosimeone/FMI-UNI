# Lecture 2 - 09.03.2023 - IoT - Sensors
Основната разлика между сензорите е начина по който се свързваме с тях(различни протоколо)
<br/>
<p style="color:red">usb kum microusb data transmition</p>
<br/>
VL53LOX
esp32
<br/>
Трябва да му кажеме кой крак да използва за SDA i кой за SCL
<br/>
SCL SDA
g23 g22
<br/>
няма значение какво е g d ...
<br/>
Wire.begin(23,22)
<br/>
Stttings -> show verbose output during both ticks
<br/>
Boot режим - 
<br/>
лявото ресет дясното боот
<br/>
Като натиснем и двете се пуска буута,първо пускаме ресета и после пускаме боота
<br/>
като натиснем просто ресета си се пуска норнамлно
<br/>
-> тази стрелка е upload
<br/>
винаги тр да ги връзваме тия крана на конректното  устройство Wire.begin(23,22)
<br/>
Е2C шина , как точно работи шината??
compile scetch >> how to
 <br/>
 status = bme.begin.. тук тр да е тази линия и после да следва : 
 <br/>
 if(!status)..
 <br/>
 Кондензатор
 <br/>
 Button pin 0
 <br/>
 Button_pin,input_pullup знае че на този пи ще получи петте волта (ако ги има волтовете е натиснато,иначе не)
 <br/>
 lastDebounceTime = millis(); това за да се спре непрекъсантото боунсване(излизане на повече не ша от необходимо)
 


