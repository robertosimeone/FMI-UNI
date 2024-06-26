## 04-a-5000.txt
- **Условие:**<br/>
Намерете командите на 10-те най-стари процеси в системата.
- **Решение:**
```bash
1)ps -e --sort=start -o comm= | head
```
## 04-a-6000.txt
- **Условие:**<br/>
Намерете PID и командата на процеса, който заема най-много виртуална памет в системата.
- **Решение:**
```bash
1)ps -e  --sort=vsz -o pid=,comm=,vsz= | head -n 1 | awk '{print $1,$2}'
#тук awk си се оправя с white space-овете 
2)ps -e  --sort=vsz -o pid=,comm=,vsz= | head -n 1 | tr -s ' ' | sed 's/^ //g' | cut -d ' ' -f 1,2
```
## 04-a-6300.txt
- **Условие:**<br/>
Изведете командата на най-стария процес
- **Решение:**
```bash
1)ps -e --sort=start -o  comm= | head -n 1
```
## 04-b-5000.txt
- **Условие:**<br/>
Намерете колко физическа памет заемат всички процеси на потребителската група root.
- **Решение:**
```bash
1)ps -g root -o rss= | awk '{sum+=$1}END{print sum}'
2)echo "$(ps -g root -o rss= | sed "s/^ *//g" | tr '\n' "+" | head -c -1)" | bc
3)bc < <(echo "$(ps -g root -o rss= | sed "s/^ *//g" | sed -z  's/\n/+/g' | head -c -1)") #тук не съм сигурен защо sed "s/\n/\+/g". "s/\n/\+/g" също не бачка.
```
## 04-b-6100.txt
- **Условие:**<br/>
Изведете имената на потребителите, които имат поне 2 процеса, чиято команда е vim (независимо какви са аргументите й)
- **Решение:**
```bash
ps -e --sort=user -o comm=,user= | grep "^vim" | uniq -c | sed "s/^ *//g" | tr -s " " | awk '$1==2{print $3}'
```
## 04-b-6200.txt
- **Условие:**<br/>
Изведете имената на потребителите, които не са логнати в момента, но имат живи процеси
- **Решение:**
```bash
1)comm -12  <(egrep -v  $(who | cut -d ' ' -f 1 | tr '\n' '\|' | head -c -1) /etc/passwd | cut -d ':' -f 1 | sort -n) <(ps -e -o user= | sort)
```
## 04-b-7000.txt
- **Условие:**<br/>
Намерете колко физическа памет заемат осреднено всички процеси на потребителската група root. Внимавайте, когато групата няма нито един процес.
- **Решение:**
```bash
1) ps -g root -o rss= | sed 's/^ *//g' | awk '{sum+=$1}END{if(NR!=0){print sum/NR}}'
```
## 04-b-8000.txt
- **Условие:**<br/>
Намерете всички PID и техните команди (без аргументите), които нямат tty, което ги управлява. Изведете списък само с командите без повторения.
- **Решение:**
```bash
1)ps -e -o tty=,comm=,pid= | egrep "^\?" | awk '{print $2,$3}' | cut -d ' ' -f 1 | sort | uniq
2)ps -e -o tty=,comm=,pid= | egrep "^\?" | awk '{print $2,$3}'
3)ps -e -o tty=,comm=,pid= | egrep "^\?" | awk '{print $2}' | sort | uniq | wc -l
```
## 04-b-9000.txt
- **Условие:**<br/>
Да се отпечатат PID на всички процеси, които имат повече деца от родителския си процес.
- **Решение:**
```bash
1)
```