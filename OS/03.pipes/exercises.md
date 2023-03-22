## 03-a-0200.txt
- **Условие:**<br/>
Сортирайте /etc/passwd лексикографски по поле UserID.
- **Решение:**
```bash
sort -t ':' -k 3 /etc/passwd
```

## 03-a-0201.txt
- **Условие:**<br/>
Сортирайте /etc/passwd числово по поле UserID.
(Открийте разликите с лексикографската сортировка)
- **Решение:**
```bash
1)sort -n -t ':' -k 3 /etc/passwd
2)cat /etc/passwd | sort -n -t ':' -k 3
```
## 03-a-0210.txt
- **Условие:**<br/>
Изведете само 1-ва и 5-та колона на файла /etc/passwd спрямо разделител ":".
- **Решение:**
```bash
1)cat /etc/passwd | cut -d ':' -f 1,5
2)cut -d ':' -f 1,5 /etc/passwd
```
## 03-a-211.txt
- **Условие:**<br/>
Изведете съдържанието на файла /etc/passwd от 2-ри до 6-ти символ.

- **Решение:**
```bash
1)head -1 /etc/passwd | cut -c 2-7 #ако се иска първи ред
2)cut -c 2-7 /etc/passwd #ако се иска всеки ред от 2-7 символ
```
## 03-a-212.txt
- **Условие:**<br/>
Отпечатайте потребителските имена и техните home директории от /etc/passwd.

- **Решение:**
```bash
cut -d ':' -f 1,6 /etc/passwd
```
## 03-a-213.txt
- **Условие:**<br/>
Отпечатайте втората колона на /etc/passwd, разделена спрямо символ '/'.
- **Решение:**
```bash
cut -d "/" -f 2 /etc/passwd
```
## 03-a-1500.txt
- **Условие:**<br/>
Изведете броя на байтовете в /etc/passwd.
Изведете броя на символите в /etc/passwd.
Изведете броя на редовете  в /etc/passwd.
- **Решение:**
```bash
wc -c /etc/passwd <-> cat /etc/passwd | wc -c
wc -m /etc/passwd <-> cat /etc/passwd | wc -m
wc -l /etc/passwd <-> cat /etc/passwd | wc -l
wc -cml /etc/passwd # всички наведнъж
```
## 03-a-2000.txt
- **Условие:**<br/>
С отделни команди, извадете от файл /etc/passwd:
  - първите 12 реда
  - първите 26 символа
  - всички редове, освен последните 4
  - последните 17 реда
  - 151-я ред (или друг произволен, ако нямате достатъчно редове)
  - последните 4 символа от 13-ти ред (символът за нов ред не е част от реда)

- **Решение:**
```bash
1) head -n 12 /etc/passwd
2) head -1 /etc/passwd | head -c 26 # с cut мисля че е по-смислено
3) head -n -4 /etc/passwd
4) tail -n 17 /etc/passwd
5) head -n 151 /etc/passwd | tail -n 1
6) head -n 13 /etc/passwd | tail -n 1 | rev | head -c 4 | rev # с cut мисля че е по-смислено

```
## 03-a-3000.txt
- **Условие:**<br/>
Запаметете във файл в своята home директория резултатът от командата `df -P`.

Напишете команда, която извежда на екрана съдържанието на този файл, без първия ред (хедъра), сортирано по второ поле (numeric).

- **Решение:**
```bash
df -P > result.txt
tail -n +2 result.txt | sort -n -k 2
```
## 03-a-3100.txt
- **Условие:**<br/>
Запазете само потребителските имена от /etc/passwd във файл users във вашата home директория.

- **Решение:**
```bash
1) cat /etc/passwd | cut -d ':' -f 1
2) cat /etc/passwd | cut -d ':' -f 1 | tr '\n' ' ' #ако исакме да не са на нов ред
```
## 03-a-3500.txt
- **Условие:**<br/>
Изпишете всички usernames от /etc/passwd с главни букви.

- **Решение:**
```bash
cat /etc/passwd | cut -d ':' -f 1 | tr a-z A-Z
```
## 03-a-5000.txt
- **Условие:**<br/>
Изведете реда от /etc/passwd, на който има информация за вашия потребител.

Изведедете този ред и двата реда преди него.

Изведете този ред, двата преди него, и трите след него.

Изведете *само* реда, който се намира 2 реда преди реда, съдържащ информация за вашия потребител.
- **Решение:**
```bash
1)cat /etc/passwd | grep "$(id -un)"
2)cat /etc/passwd | grep -B 2  "$(id -un)"
3)cat /etc/passwd | grep -B 2 -A 3 "$(id -un)"
4)cat /etc/passwd | grep -B 2  "$(id -un)" | head -n 1 
```
## 03-a-5001.txt
- **Условие:**<br/>
Изведете колко потребители не изпозват /bin/bash за login shell според /etc/passwd

(hint: 'man 5 passwd' за информация какъв е форматът на /etc/passwd)
- **Решение:**
```bash
cat /etc/passwd | grep -v 'bin/bash' | wc -l
```
## 03-a-5002.txt
- **Условие:**<br/>
Изведете само имената на хората с второ име по-дълго от 6 (>6) символа според /etc/passwd
- **Решение:**
```bash
1)cat /etc/passwd | cut -d ':' -f 5 | cut -d , -f 1 | awk -F ' ' 'length($2)>12 {print $1}' # 12 защото имената са на български,а един символ от бг азбуката се брои за 2 байта
2)cat /etc/passwd | cut -d ':' -f 5 | cut -d , -f 1 | awk -F ' ' 'length($2)>6 {print $1}' # ако имената бяха на латиница
```
## 03-a-5003.txt
- **Условие:**<br/>
Изведете имената на хората с второ име по-късо от 8 (<=7) символа според /etc/passwd // !(>7) = ?
- **Решение:**
```bash
cat /etc/passwd | cut -d ':' -f 5 | cut -d , -f 1 | awk -F ' ' 'length($2)<16 {print $1}'
```
## 03-a-5004.txt
- **Условие:**<br/>
Изведете целите редове от /etc/passwd за хората от 03-a-5003
- **Решение:**
```bash
cat /etc/passwd | awk -F ":|,| " 'length($6)<16 {print $0}'
```
## 03-a-6000.txt
- **Условие:**<br/>
Копирайте <РЕПО>/exercises/data/emp.data във вашата home директория.
Посредством awk, използвайки копирания файл за входнни данни, изведете:

- 1)общия брой редове
- 2)третия ред
- 3)последното поле от всеки ред
- 4)последното поле на последния ред
- 5)всеки ред, който има повече от 4 полета
- 6)всеки ред, чието последно поле е по-голямо от 4
- 7)общия брой полета във всички редове
- 8)броя редове, в които се среща низът Beth
- 9)най-голямото трето поле и редът, който го съдържа
- 10)всеки ред, който има поне едно поле
- 11)всеки ред, който има повече от 17 знака
- 12)броя на полетата във всеки ред и самият ред
- 13)първите две полета от всеки ред, с разменени места
- 14)всеки ред така, че първите две полета да са с разменени места
- 15)всеки ред така, че на мястото на първото поле да има номер на реда
- 16)всеки ред без второто поле
- 17)за всеки ред, сумата от второ и трето поле
- 18)сумата на второ и трето поле от всеки ред
- **Решение:**
```bash
1.1)awk 'END {print NR}' emp.data
1.2)awk 'BEGIN{i = 0} {i++} END {print i}' emp.data
2.1)awk 'BEGIN{i = 0} {i++} i == 3 {print $0}' emp.data
2.2)awk 'NR == 3 {print $0}' emp.data
3)awk '{print $NF}' emp.data
4)awk 'END {print $NF}' emp.data
5)awk 'NF>4{print $0}' emp.data
6)awk '$NF>4{print $0}' emp.data
7)awk 'BEGIN {i=0} {i+=NF} END{ print i}' emp.data
8)awk '/Beth/ {print $0} ' emp.data
9)awk 'BEGIN{max = -10;current} $NF>max{max=$NF;current=$0}END{printf "%s :  %s\n",max,current}' emp.data
10)awk 'NF>0{print $0}' emp.data
11)awk 'length($R)>17' emp.data
12.1)awk '{print NF,":",$0}' emp.data
12.2)awk '{printf "%u : %s\n",NF,$0}' emp.data
13)awk '{print $2,$1}' emp.data # тук може да подадем OFS(с това се разделят колонките,тоест -v OFS='\t')
14)awk '{printf "%-6.2f %-6s   ",$2,$1;for(i=3;i<=NF;i++) print $i}' emp.data
15)awk '{printf"%d %s\n",FNR,$0}' emp.data
16.1)awk '{for(i=1;i<=NF;i++){if(i!=2){printf "%s",$i};if(i==NF){printf "\n"}else printf "   "}}' emp.data # малко sloppy
16.2)awk -v OFS='\t' '{printf "%s%s",$1,OFS}; {for(i=3; i<=NF; i++){printf "%i",$i}}; {print ""}' emp.data # този начин не работи ако имаме повече от 3 колони , защото 3тата и всички друго поред се долепват една до друга
16.3)awk -v OFS='\t' '{$2=""; print $0 }' emp.data # това е друг як начин
17)awk '{print $2+$3}' emp.data
18.1)awk 'BEGIN{SUM=0}{sum = $2+$3;SUM+=sum}END{print SUM}' emp.data
18.2)awk -v SUM=0 '{SUM += ($2 + $3)} END {print SUM}' emp.data
```
## 03-b-0300.txt
- **Условие:**<br/>
Намерете само Group ID-то си от файлa /etc/passwd.
- **Решение:**
```bash
1)cat /etc/passwd | awk -F : -v current_user = $(whoami) '$1 == current_user {print $4}'
2)cat /etc/passwd | awk -F : -v current_user=$(id -un) '$1 == current_user {print $4}'
# горните 2 ще мачнат и неща които не започват с id-to на текущия user
3)cat /etc/passwd | grep "^$(whoami):" | cut -d : -f 4
```
## 03-b-3400.txt
- **Условие:**<br/>
Колко коментара има във файла /etc/services ? Коментарите се маркират със символа #, след който всеки символ на реда се счита за коментар.
- **Решение:**
```bash
1)grep '#' /etc/services | wc -l 
```
## 03-b-3500.txt
- **Условие:**<br/>
Колко файлове в /bin са 'shell script'-oве? (Колко файлове в дадена директория са ASCII text?)
- **Решение:**
```bash
1)find -L /bin -mindepth 1 -maxdepth 1 -type f -exec file {} \; | grep 'shell' | wc -l
2)file /bin/* | grep 'shell' | wc -l
```
## 03-b-3600.txt
- **Условие:**<br/>
Направете списък с директориите на вашата файлова система, до които нямате достъп. Понеже файловата система може да е много голяма, търсете до 3 нива на дълбочина.
- **Решение:**
```bash
1)find / -maxdepth 3 -type d 2>&1 1>/dev/null | grep 'Permission denied' | wc -l #това не бачка мн защото реално листва вс в students но после не гледа дали може самия файл да се чете
2)find / -maxdepth 3 -not -readable -type d 2>/dev/null | wc -l
```
## 03-b-4000.txt
- **Условие:**<br/>
Създайте следната файлова йерархия в home директорията ви:
dir5/file1
dir5/file2
dir5/file3

Посредством vi въведете следното съдържание:
file1:
1
2
3

file2:
s
a
d
f

file3:
3
2
1
45
42
14
1
52

Изведете на екрана:
- 1)статистика за броя редове, думи и символи за всеки един файл
- 2)статистика за броя редове и символи за всички файлове
- 3)общия брой редове на трите файла

- **Решение:**
```bash
  1) wc file{1,2,3}
  2) wc -lc file{1,2,3} 
  3) cat file{1,2,3} | wc -l

```
## 03-b-4001.txt
- **Условие:**<br/>
Във file2 (inplace) подменете всички малки букви с главни.
- **Решение:**
```bash
1)cat file2 | tr a-z A-Z > ss && mv ss file2
```
## 03-b-4002.txt
- **Условие:**<br/>
Във file3 (inplace) изтрийте всички "1"-ци. 
- **Решение:**
```bash
tr -d 1 < file3 > temp && mv temp file3

```
## 03-b-4003.txt
- **Условие:**<br/>
Изведете статистика за най-често срещаните символи в трите файла.
- **Решение:**
```bash
1)sed -E  's/(.)/\1\n/g' cuttest | grep -E -v '^ *$' | sort | uniq -c | sort -nr | awk 'BEGIN{max = -1}max<=$1{max=$1;print $1,$2 }'
2)sed -E  's/(.)/\1\n/g' cuttest | head -n -1 | sort | uniq -c | sort -nr | awk 'BEGIN{max = -1}max<=$1{max=$1;print $1,$2 }'
3)cat cuttest | grep -o '[^ ]' | sort | uniq -c | sort -nr # и после се продължава
```
## 03-b-4004.txt
- **Условие:**<br/>
Направете нов файл с име по ваш избор, чието съдържание е конкатенирани
съдържанията на file{1,2,3}.
- **Решение:**
```bash
cat file{1,2,3} > concatfile
```
## 03-b-4005.txt
- **Условие:**<br/>
Прочетете текстов файл file1 и направете всички главни букви малки като
запишете резултата във file2.
- **Решение:**
```bash
1)tr a-z A-Z < file1 > file2
2)awk '{print toupper($0)}' file1 > file2
```
## 03-b-5200.txt
- **Условие:**<br/>
Намерете броя на символите, различни от буквата 'а' във файла /etc/passwd
- **Решение:**
```bash
cat /etc/passwd | grep -o '[^a]' | sort | uniq -c | sort -n
```
## 03-b-5300.txt
- **Условие:**<br/>
Намерете броя на уникалните символи, използвани в имената на потребителите от
/etc/passwd.
- **Решение:**
```bash
cat /etc/passwd | cut -d ':' -f 5 | cut -d , -f1 | grep -o '[^ ]' | sort | uniq -c | sort
```
## 03-b-5400.txt
- **Условие:**<br/>
Отпечатайте всички редове на файла /etc/passwd, които не съдържат символния низ 'ов'.
- **Решение:**
```bash
egrep -v 'ов' /etc/passwd | wc -l
```
## 03-b-6100.txt
- **Условие:**<br/>
Отпечатайте последната цифра на UID на всички редове между 28-ми и 46-ред в /etc/passwd.
- **Решение:**
```bash
awk -F ':' '{if(NR>=28 && NR<=46){print $3}}' /etc/passwd | rev | cut -c 1
```
## 03-b-6700.txt
- **Условие:**<br/>
Отпечатайте правата (permissions) и имената на всички файлове, до които имате
read достъп, намиращи се в директорията /tmp. (hint: 'man find', вижте -readable)
- **Решение:**
```bash
1)find /tmp -readable 2>/dev/null -exec stat -c "%n : %A" {} \;
2)find /tmp -readable 2>/dev/null -exec stat -c "%n : %a" {} \;
```
## 03-b-6900.txt
- **Условие:**<br/>
Намерете имената на 10-те файла във вашата home директория, чието съдържание е
редактирано най-скоро. На първо място трябва да бъде най-скоро редактираният
файл. Намерете 10-те най-скоро достъпени файлове. (hint: Unix time)
- **Решение:**
```bash
1)find . -type f -exec stat --printf "%Y\t%n\n" {} \; | sort -nr | head
2)find . -type f -exec stat --printf "%X\t%n\n" {} \; | sort -nr | head
3)find . -type f -exec stat --printf "%X\t%n\n" {} \; | sort -nr | head | cut -f 2
```
## 03-b-7000.txt
- **Условие:**<br/>
да приемем, че файловете, които съдържат C код, завършват на `.c` или `.h`.
Колко на брой са те в директорията `/usr/include`?
Колко реда C код има в тези файлове?
- **Решение:**
```bash
1)find /usr/include -type f | egrep ".*\.[ch]$" | wc -l
2)find /usr/include -type f | egrep ".*\.h$|.*\.c$" | wc -l
3)find /usr/include/ -type f -name '*.[ch]' | wc -l

```
## 03-b-7500.txt
- **Условие:**<br/>
Даден ви е ASCII текстов файл - /etc/services. Отпечатайте хистограма на 10-те най-често срещани думи.
Дума наричаме непразна последователност от букви. Не правим разлика между главни и малки букви.
Хистограма наричаме поредица от редове, всеки от които има вида:
<брой срещания> <какво се среща толкова пъти>
- **Решение:**
```bash
1)cat /etc/services | egrep -o "\b[a-zA-Z]*\b" | sort | uniq -c | sort -nr | head
# може да се направи и с tr -c [:alnum:]

```
## 03-b-8000.txt
- **Условие:**<br/>
Вземете факултетните номера на студентите (описани във файла
<РЕПО>/exercises/data/mypasswd.txt) от СИ и ги запишете във файл si.txt сортирани.

Студент е част от СИ, ако home директорията на този потребител (според
<РЕПО>/exercises/data/mypasswd.txt) се намира в /home/SI директорията.
- **Решение:**
```bash
cat /srv/fmi-os/exercises/data/mypasswd.txt | grep '/home/SI' | cut -d ':' -f 1 > si.txt #тук може да се добави опцията за tr -d 's' за да премахнем s преди реалните факултетни номера
#може да се направи и с cut -c 2-
```
## 03-b-8500.txt
- **Условие:**<br/>
За всяка група от /etc/group изпишете "Hello, <група>", като ако това е вашата група, напишете "Hello, <група> - I am here!".
- **Решение:**
```bash
cat /etc/group | cut -d ':' -f 1 | awk -v mygr="$(id -gn)" '{if(mygr!=$0){printf "Hello, %s\n",$0}else{printf"Hello, %s - I am here!\n",$0}}'
```
## 03-b-8600.txt
- **Условие:**<br/>
Shell Script-овете са файлове, които по конвенция имат разширение .sh. Всеки
такъв файл започва с "#!<interpreter>" , където <interpreter> указва на
операционната система какъв интерпретатор да пусне (пр: "#!/bin/bash",
"#!/usr/bin/python3 -u").

Намерете всички .sh файлове в директорията `/usr` и нейните поддиректории, и
проверете кой е най-често използваният интерпретатор.
- **Решение:**
```bash
1)find /usr -name "*.sh" -exec head -n 1 {} \; | grep '#!' | sort | uniq -c | sort -nr | head -n 1
```
##  03-b-8700.txt
- **Условие:**<br/>
1. Изведете GID-овете на 5-те най-големи групи спрямо броя потребители, за които
съответната група е основна (primary).

2. (*) Изведете имената на съответните групи.

Hint: /etc/passwd 
- **Решение:**
```bash
1)cat /etc/passwd | cut -d ':' -f 4 | sort -n | uniq -c | sort -nr | head -n 5 | sort -nr
2)cat /etc/passwd | cut -d ':' -f 4 | sort -n | uniq -c | sort -nr | head -n 5 | sort -n -k 2 | tr ' ' ':'| join -t ':' -1 2 -2 3 - mygroup
## опит за 2рото условие ама не се получава########################
3)getent group $(cat /etc/passwd | cut -d ':' -f 4 | sort -n | uniq -c | sort -nr | head -n 5 | sort -nr | tr -s ' ' | cut -d ' ' -f 3 | tr '\n' ' ')
# тва май по-бачка
```
## 03-b-9000.txt
- **Условие:**<br/>
Направете файл eternity. Намерете всички файлове, намиращи се във вашата home
директория и нейните поддиректории, които са били модифицирани в последните
15мин (по възможност изключете .).  Запишете във eternity името (път) на
файла и времето (unix time) на последната промяна.
- **Решение:**
```bash
find . -mindepth 1 -mmin -15 -printf "%p\t%T@\n" > eternity
```
## 03-b-9050.txt
- **Условие:**<br/>
Копирайте файл <РЕПО>/exercises/data/population.csv във вашата home директория.
- **Решение:**
```bash
cp /srv/fmi-os/exercises/data/population.csv ~
```
## 03-b-9051.txt
- **Условие:**<br/>
Използвайки файл population.csv, намерете колко е общото население на света
през 2008 година. А през 2016?
- **Решение:**
```bash
awk -F ',' -v pop_2008=0 -v pop_2016=0 '$3==2008{pop_2008+=$4}$3==2016{pop_2016+=$4}END{print pop_2008,pop_2016}' population.csv
```
## 03-b-9052.txt
- **Условие:**<br/>
Използвайки файл population.csv, намерете през коя година в България има най-много население.
- **Решение:**
```bash
grep 'Bulgaria' population.csv | awk -F ',' -v max_pop=-1 -v max_pop_year=-1 'max_pop<=$4{max_pop=$4;max_pop_year=$3}END{print max_pop_year,":",max_pop}'

```
## 03-b-9053.txt
- **Условие:**<br/>
Използвайки файл population.csv, намерете коя държава има най-много население през 2016. А коя е с най-малко население?
(Hint: Погледнете имената на държавите)
- **Решение:**
```bash
grep ',2016,' population.csv | sed 's/, / /' | awk -F ',' -v maxpop=-1 -v maxpopc='' -v minpopc=0 -v minpopc='' '$4>=maxpop{maxpop=$4;maxpopc=$1}minpop==0{minpop=$4;minpopc=$1}minpop>=$4{minpop=$4;minpopc=$1}END{printf"MIN POPULATION %s : %d\nMAX POPULATION %s : %d\n",minpopc,minpop,maxpopc,maxpop}' # излиза проблем ако примерно сложиш някоя промелива да е равна на -1 и после проверяваш в awk-a za var==-1(с 0 си работи ок)
#мсиля че на всички задачи нагоре тр да се направи командата sed заради добавените "," в имената
```
## 03-b-9054.txt
- **Условие:**<br/>
Използвайки файл population.csv, намерете коя държава е на 42-ро място по
население през 1969. Колко е населението й през тази година?
- **Решение:**
```bash
grep ',1969,' population.csv | sed 's/, / /' | sort -t ',' -nr -k 4 | head -n 41 | tail -n 1
```
## 03-b-9100.txt
- **Условие:**<br/>
В home директорията си изпълнете командата
curl -o songs.tar.gz "http://fangorn.uni-sofia.bg/misc/songs.tar.gz"
- **Решение:**
```bash

```
## 03-b-9101.txt
- **Условие:**<br/>
Да се разархивира архивът songs.tar.gz в директория songs във вашата home директория
- **Решение:**
```bash
uncompress songs.tar.gz
tar -xf songs.tar -C songs/
```
## 03-b-9102.txt
- **Условие:**<br/>
Да се изведат само имената на песните.
- **Решение:**
```bash
1)find . -mindepth 1 -printf "%f\n" | sed 's/.*-//' | sed 's/(.*//'
2)find . -type f -name '*.ogg' | awk -F/ '{print $2}' | awk -F ' \\(' '{print $1}'
3)find . -mindepth 1 -printf "%f\n" | awk -F '\-|\\(' '{print $2}'
```
## 03-b-9103.txt
- **Условие:**<br/>
Имената на песните да се направят с малки букви, да се заменят спейсовете с
долни черти и да се сортират.
- **Решение:**
```bash
  # не е довършено,по някаква причина tolower($2) цака нещата и делимитерите изчезват - '-' и '(' -> това е ако искаме да изкараме целия ред с малки букви на иманта
1)find songs -mindepth 1 -printf "%f\n" | awk -F '-|\\(' '{$2=tolower($2);print $2}' | cut -d ' ' -f 2- | sed 's/ /_/g' | sed 's/_$//'
2)find songs -mindepth 1 -printf "%f\n" | awk -F '-|\\(' '{$2=tolower($2);print $2}' | sed 's/^ //' | sed 's/ /_/g' | sed 's/_$//'
```
## 03-b-9104.txt
- **Условие:**<br/>
Да се изведат всички албуми, сортирани по година.
- **Решение:**
```bash
find songs -mindepth 1 -printf "%f\n" | awk -F '\\(|\\)' '{print $2}' | sort -t ',' -n -k 2 | uniq # на този пример отново,ако сложим "" вместо '' не излиза нищо,а с ''си бачка
```
## 03-b-9105.txt
- **Условие:**<br/>
Да се преброят/изведат само песните на Beatles и Pink.
- **Решение:** 
```bash
find songs -mindepth 1 -printf "%f\n" | egrep 'Beatles|Pink [^F]' | awk -F '-' -v beatc=0 -v pinkc=0 '{print $0}$1=="Beatles " {beatc+=1}$1=="Pink "{pinkc+=1}END{printf"Beatles songs:%d\nPink songs:%d\n",beatc,pinkc}'
# има примери където се ескейпва | -> grep 'Beatles\|Pink' защо се ескепва
```
## 03-b-9106.txt
- **Условие:**<br/>
Да се направят директории с имената на уникалните групи. За улеснение, имената
от две думи да се напишат слято:

Beatles, PinkFloyd, Madness
- **Решение:**
```bash
mkdir $(find songs -mindepth 1 -printf "%f\n" | awk -F '-' '{print $1}' | tr -d ' ' | sort | uniq)
```
## 03-b-9200.txt
- **Условие:**<br/>
Напишете серия от команди, които извеждат детайли за файловете и директориите в
текущата директория, които имат същите права за достъп както най-големият файл
в /etc директорията.
- **Решение:**
```bash
find . -mindepth 1 -maxdepth 1 -perm "$(find /etc -mindepth 1 -printf "%m\t%s\n" 2>/dev/null | sort -nrk 2 | head -n 1 | cut -f 1)"
```
## 03-b-9300.txt
- **Условие:**<br/>
Дадени са ви 2 списъка с email адреси - първият има 12 валидни адреса, а
вторията има само невалидни. Филтрирайте всички адреси, така че да останат
само валидните. Колко кратък регулярен израз можете да направите за целта?

Валидни email адреси (12 на брой):<br/>
email@example.com<br/>
firstname.lastname@example.com<br/>
email@subdomain.example.com<br/>
email@123.123.123.123<br/>
1234567890@example.com<br/>
email@example-one.com<br/>
_______@example.com<br/>
email@example.name<br/>
email@example.museum<br/>
email@example.co.jp<br/>
firstname-lastname@example.com<br/>
unusually.long.long.name@example.com<br/>

Невалидни email адреси:<br/>
#@%^%#$@#$@#.com<br/>
@example.com<br/>
myemail<br/>
Joe Smith <email@example.com><br/>
email.example.com<br/>
email@example@example.com<br/>
.email@example.com<br/>
email.@example.com<br/>
email..email@example.com<br/>
email@-example.com<br/>
email@example..com<br/>
Abc..123@example.com<br/>
(),:;<>[\]@example.com<br/>
just"not"right@example.com<br/>
this\ is"really"not\allowed@example.com<br/>
- **Решение:**
```bash
    cat valid invalid | egrep --color "^([a-zA-Z0-9_]+(\.|\-)?[a-zA-Z0-9_]+)+@([a-zA-Z0-9]+(\.|\-)[a-zA-Z0-9]+)+$"
```
## 03-b-9400.txt
- **Условие:**<br/>
Посредством awk, използвайки emp.data (от 03-a-6000.txt) за входнни данни,
изведете:

- всеки ред, като полетата са в обратен ред

(Разгледайте for цикли в awk)
- **Решение:**
```bash
1)awk '{for(i=NF;i>=1;i--){if(i==1){print $i}else{printf "%s\t",$i}}}' emp.data
2)awk '{for (i = NF; i>0; i--){printf "%s\t",$i}}{printf "\n"}' emp.data
#това е яко.демек се изпълнява вс в първите кавички и след като се изпълни всичко там се влиза във вторите където има друго условие
```
## 03-b-9500.txt
- **Условие:**<br/>
Копирайте <РЕПО>/exercises/data/ssa-input.txt във вашата home директория.
Общият вид на файла е:

- заглавна част:
	Smart Array P440ar in Slot 0 (Embedded)

- една или повече секции за масиви:
	Array A
	Array B
	...
	като буквата (A, B, ...) е името на масива

- във всяка таква секция има една или повече подсекции за дискове:
	physicaldrive 2I:0:5
	physicaldrive 2I:0:6
	...

	като 2I:0:5 е името на диска

- във всяка подсекция за диск има множество параметри във вида:
	key name: value
	като за нас са интересни само:

		Current Temperature (C): 35
		Maximum Temperature (C): 36

Напишете поредица от команди която обработва файл в този формат, и генерира
следният изход:

A-2I:0:5 35 36<br/>
A-2I:0:6 34 35<br/>
B-1I:1:1 35 50<br/>
B-1I:1:2 35 49<br/>

x-yyyyyy zz ww

където:
	- x е името на масива
	- yyyyyy е името на диска
	- zz е current temperature
	- ww е max temperature
- **Решение:**
```bash
cat ssa-input.txt  | egrep --color "Array|physicaldrive|Current Temperature|Maximum Temperature" | egrep --color -v "Smart" | sed 's/(C)//g' | tr -s " " | sed 's/t T/tT/g' | sed 's/m T/mT/g' | cut -d " " -f 2- | awk -F " " -v ca="" -v pd="" -v ct=0 -v mt=0 '$1=="Array"{ca=$2}$1=="physicaldrive"{pd=$2}$1=="CurrentTemperature"{ct=$3}$1=="MaximumTemperature"{mt=$3;printf "%s-%s %d %d\n",ca,pd,ct,mt}'
```