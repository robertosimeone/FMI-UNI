# Exercises
## 05-a-2000.txt
- **Условие:**<br/>
Сменете вашия prompt с нещо по желание. После върнете оригиналния обратно.
- **Решение:**
```bash
1)using export command to temporarily change the prompt
export PS1="\u \@>"
https://phoenixnap.com/kb/change-bash-prompt-linux
```
2) editing the ./bashrc file(permanent change)
## 05-a-2100.txt
- **Условие:**<br/>
Редактирайте вашия .bash_profile файл, за да ви поздравява (или да изпълнява някаква команда по ваш избор) всеки път, когато влезете в системата.
- **Решение:**
```bash
1) edit .profile file -> echo "Welcome ${USER}" wherever u want
```
## 05-a-2200.txt
- **Условие:**<br/>
Направете си ваш псевдоним (alias) на полезна команда.
- **Решение:**
```bash
alias g="egrep --color"
```
## 05-b-2000.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приканва потребителя да въведе низ (име) и изпечатва "Hello, низ".
- **Решение:**
```bash
  1 #!/bin/bash
  2 read -p "Please enter your name: " name
  3 echo "Hello,${name}"
```
## 05-b-2800.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приема точно един параметър и проверява дали подаденият му параметър се състои само от букви и цифри.
- **Решение:**
```bash
 1 #!/bin/bash
 2 string="${1}"
 3 if echo "${string}" | grep -q '[^a-zA-Z0-9]';then
    4     echo "Not alphanumeric"
 5 else
    6     echo "Ok,Alphanumeric"
 7 fi
```
## 05-b-3100.txt 
- **Условие:**<br/>
Да се напише shell скрипт, който приканва потребителя да въведе низ - потребителско име на потребител от системата - след което извежда на стандартния изход колко активни сесии има потребителят в момента.
- **Решение:**
```bash
  1 #!/bin/bash
  2 read -p "Please enter an username: " username
  3 activeSessions="$(who | grep "${username}" | wc -l)"
  4 echo "${username} has ${activeSessions} active sessions"
```
## 05-b-3200.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приканва потребителя да въведе пълното име на директория и извежда на стандартния изход подходящо съобщение за броя на всички файлове и всички директории в нея.
- **Решение:**
```bash
  1 #!/bin/bash
  2 read -p "Enter a full path to a directory: " path
  3 dirsCount="$(find $path -mindepth 1 -type d | wc -l)"
  4 fileCount="$(find $path -mindepth 1 -type f | wc -l)"
  5 echo -e "Number of directories is : ${dirsCount}\nNumber of files is : ${fileCount}"
```
## 05-b-3300.txt
- **Условие:**<br/>
Да се напише shell скрипт, който чете от стандартния вход имената на 3 файла, обединява редовете на първите два (man paste), подрежда ги по азбучен ред и резултата записва в третия файл.
- **Решение:**
```bash
1 #!/bin/bash
2 paste ${1} ${2} | sort > ${3}
# аз поне така разбирам условието
# ако искаме да обединим редовете,смисъл да са един под друг а не да са долепените редовете на първия файл(1 ред 1 файл-1 ред втори файл) може да използваме
paste -d '\n' ${1} ${2} | sort > ${3}
# по този начин редовете излизат така
# 1ред първи файл
# 1ред втори файл
# 2ред първи файл
# 2ред втори файл
# ...

```
## 05-b-3400.txt
- **Условие:**<br/>
Да се напише shell скрипт, който чете от стандартния вход име на файл и символен низ, проверява дали низа се съдържа във файла и извежда на стандартния изход кода на завършване на командата с която сте проверили наличието на низа.

NB! Символният низ може да съдържа интервал (' ') в себе си.
- **Решение:**
```bash
  1 #!/bin/bash
  2 file=${1}
  3 string=${2}
  4 if [[ ! ${#} -eq 2 ]]; then
  5     echo "Number of params is not 2,aborting"
  6     exit 1
  7 fi
  8
  9 if [[ ! -f ${file} ]]; then
 10     echo "File does not exist"
 11     exit 1
 12 fi
 13
 14 if grep -q "${string}" "${file}";then
 15     echo ${?}
 16     echo "${file} contains ${string}"
 17 else
 18     echo "${?}"
 19     echo "${file} does not containt ${string}"
 20 fi
```
## 05-b-4200.txt
- **Условие:**<br/>
Имате компилируем (a.k.a няма синтактични грешки) source file на езика C. Напишете shell script, който да покaзва колко е дълбоко най-дълбокото nest-ване (влагане).
Примерен .c файл:

    #include <stdio.h>

    int main(int argc, char *argv[]) {

    if (argc == 1) {
            printf("There is only 1 argument");
        } else {
            printf("There are more than 1 arguments");
        }

        return 0;
    }
Тук влагането е 2, понеже имаме main блок, а вътре в него if блок.

Примерно извикване на скрипта:

./count_nesting sum_c_code.c

Изход:
The deepest nesting is 2 level
- **Решение:**
```bash
 #!/bin/bash
  2 file="${1}"
  3 max_nest=0
  4 nest_count=0
  5 grep -o "[{}]" "${file}" | while read symbol; do
  6 echo "cycle"
  7 if [[ "${symbol}" == '{' ]]; then
  8     echo "inif"
  9     nest_count=$(($nest_count + 1))
 10     echo "nest_count is : ${nest_count}"
 11     if [[ $max_nest -lt $nest_count ]]; then
 12         max_nest=$nest_count
 13     fi
 14     echo "max nest is $max_nest"
 15 else
 16     echo "inelse"
 17     nest_count=$(($nest_count-1))
 18 fi
 19 done
 #тук не принтвам накрая нещата зашото те си остават 0 по някаква причина
 # предполагам е защото дясната страна на |  се изпълнява в subshell и дргите променливи kato max_nest и nest_count  са видими там но си остават непроменени като излеземе от subshell-a.Ако ги сложа на -10 и двете и после си правя операциите с тях, те в циклите стават съответно -9 и -8 но като излезем от тях и принтна след done  $nest_count и  $max_nest те си остават -10
# За да се направи тази задача просто не тр да се използва pipe a а директно while read 
```
## 05-b-4301.txt
- **Условие:**<br/>
Напишете shell script, който автоматично да попълва файла указател от предната задача по подадени аргументи: име на файла указател, пълно име на човека (това, което очакваме да е в /etc/passwd) и избран за него nickname.
Файлът указател нека да е във формат:
<nickname, който лесно да запомните> <username в os-server>
// може да сложите и друг delimiter вместо интервал

Примерно извикване:
./pupulate_address_book myAddressBook "Ben Dover" uncleBen

Добавя към myAddressBook entry-то:
uncleBen <username на Ben Dover в os-server>

***Бонус: Ако и пореден номер >=1,
след което той да може да въведе някой от номерата (или 0 ако не си хареса никого), и само избраният да бъде добавен към указателя.
- **Решение:**
```bash
 1 #!/bin/bash
  2 popbook="${1}"
  3 etcname="${2}"
  4 nick="${3}"
  5
  6 if [[ $(grep "${etcname}" myetc | wc -l) -eq 0 ]]; then
  7     echo "There is no such person!Please try again with a different name."
  8     exit 1
  9 elif [[ $(grep "${etcname}" myetc | wc -l) -eq 1 ]]; then
 10     username="$(cat /etc/passwd | grep "${etcname}" | cut -d ':' -f 1)"
 11     echo "${nick} ${username}" >> "${popbook}"
 12     exit 0
 13 else
 14     options=$(awk -F ':' '{printf"%d:%s\n",NR,$0}' <(grep "${etcname}" myetc))
 15     echo "${options}"
 16     read -p "Multiple records found for this user.Which one would you like to choose    ?Usage(1|2|3..): " choice
 17     username=$(echo "${options}" | grep "^${choice}" | cut -d ':' -f 2)
 18     echo "${nick} : ${username}" >> "${popbook}"
 19     exit 0
 20 fi
```
## 05-b-4400.txt
- **Условие:**<br/>
Напишете shell script, който да приема параметър име на директория, от която взимаме файлове, и опционално експлицитно име на директория, в която ще копираме файлове. Скриптът да копира файловете със съдържание, променено преди по-малко от 45 мин, от първата директория във втората директория. Ако втората директория не е подадена по име, нека да получи такова от днешната дата във формат, който ви е удобен. При желание новосъздадената директория да се архивира.
- **Решение:**
```bash
 1 #!/bin/bash
  2 if [[ -z "${2}" ]]; then
  3     fileto="$(date '+%D' | sed 's/\///g')"
  4 else
  5     fileto="${2}"
  6 fi
  7 if [[ ! -d "${fileto}" ]]; then
  8     mkdir "${fileto}"
  9 fi
 10 filefrom="${1}"
 11 dirs_copy="$(find "${filefrom}" -mindepth 1 -mmin -45)"
 12 cp -r ${dirs_copy} "${fileto}/"
 13
```
## 05-b-4500.txt
- **Условие:**<br/>
Да се напише shell скрипт, който получава при стартиране като параметър в командния ред идентификатор на потребител. Скриптът периодично (sleep(1)) да проверява дали потребителят е log-нат, и ако да - да прекратява изпълнението си, извеждайки на стандартния изход подходящо съобщение.

NB! Можете да тествате по същият начин като в 05-b-4300.txt
- **Решение:**
```bash
  1 #!/bin/bash
  2 while ! grep -q "${1}" <(who | tr -s ' ' | cut -d ' ' -f 1 ); do
  3     echo "Not logged in..."
  4     sleep 1
  5 done
  6 echo "User ${1} has logged in"
```
## 05-b-4600.txt
- **Условие:**<br/>
Да се напише shell скрипт, който валидира дали дадено цяло число попада в целочислен интервал.
Скриптът приема 3 аргумента: числото, което трябва да се провери; лява граница на интервала; дясна граница на интервала.
Скриптът да връща exit status:
- 3, когато поне един от трите аргумента не е цяло число
- 2, когато границите на интервала са обърнати
- 1, когато числото не попада в интервала
- 0, когато числото попада в интервала

Примери:
$ ./validint.sh -42 0 102; echo $?
1

$ ./validint.sh 88 94 280; echo $?
1

$ ./validint.sh 32 42 0; echo $?
2

$ ./validint.sh asdf - 280; echo $?
3
- **Решение:**
```bash
  1 #!/bin/bash
  2 if [[ ! $# -eq 3 ]]; then
  3     echo "Usage <num_check> <left> <right>"
  4     exit 4
  5 fi
  6 check="${1}"
  7 left="${2}"
  8 right="${3}"
  9 check_num="^-{0,1}[0-9]+\.{0,1}[0-9]?$"
 10 if [[ "${check}" =~ ${check_num} ]] && [[ "${left}" =~ ${check_num} ]] && [[ "${right}" =~ ${check_num} ]]; then
 11     if [[ $left -gt $right ]]; then
 12         echo "Reversed limits"
 13         exit 2
 14     elif [[ $left -lt $check ]] && [[ $right -gt $check ]]; then
 15         echo "In limits"
 16         exit 0
 17     else
 18         echo "Outside of limits"
 19         exit 1
 20     fi
 21 else
 22     echo "One of them is not an integer"
 23     exit 3
 24 fi
```
## 05-b-4700.txt
- **Условие:**<br/>
Да се напише shell скрипт, който форматира големи числа, за да са по-лесни за четене.
Като пръв аргумент на скрипта се подава цяло число.
Като втори незадължителен аргумент се подава разделител. По подразбиране цифрите се разделят с празен интервал.

Примери:
$ ./nicenumber.sh 1889734853
1 889 734 853

$ ./nicenumber.sh 7632223 ,
7,632,223
- **Решение:**
```bash
#!/bin/bash
  2 number="${1}"
  3 if [[ -z "${2}" ]]; then
  4     separator=" "
  5 else
  6     separator="${2}"
  7 fi
  8 newnumber="$(echo "${number}" | rev)"
  9 newone="$(echo "${newnumber}" | sed -E 's/([0-9]{3})/\1 /g' | tr ' ' "$separator" | sed -E 's/[, ]$//g' | rev)"
 10 echo "$newone" 

 # second solution
   1 #!/bin/bash
  2 number="${1}"
  3 if [[ -z "${2}" ]]; then
  4     separator=" "
  5 else
  6     separator="${2}"
  7 fi
  8 len=$(echo ${number} | awk -F "" -v num="${number}" 'BEGIN{len=length(num);print len}')
  9 remainder=$((len%3))
 10 echo "${remainder}"
 11 first=""
 12 annumber=""
 13 from=0
 14 if [[ $len -gt 3 ]]; then
 15     if [[ ! $remainder -eq 0 ]]; then
 16         new="${number: 0 : $remainder}"
 17         annumber="$first$new$separator"
 18         len=$((len-remainder))
 19
 20         fi
 21         cycles=$((len/3))
 22         for((i=$remainder,cc=1;i<$len,cc<=$cycles;i+=3,cc++)); do
 23             if [[ $cc -eq ${cycles} ]]; then
 24                 echo "In last if"
 25                 symbols="${number: $i: 3}"
 26                 annumber="$annumber$symbols"
 27             else
 28             echo "In else"
 29             symbols="${number: $i: 3}"
 30             annumber="$annumber$symbols$separator"
 31             fi
 32         done
 33 else
 34     echo "Not greater than 3"
 35     annumber="$number"
 36 fi
 37 echo -e "$annumber"
```
## 05-b-4800.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приема файл и директория. Скриптът проверява в подадената директория и нейните под-директории дали съществува копие на подадения файл   и отпечатва имената на намерените копия, ако съществуват такива.

NB! Под 'копие' разбираме файл със същото съдържание.
- **Решение:**
```bash
  1 #!/bin/bash
  2 file="${1}"
  3 directory="${2}"
  4
  5 if [[ $# -ne 2 ]]; then
  6     echo "Wrong Usage.Usage: <file> <directory>"
  7     exit 1
  8 fi
  9 while read filename; do
 10     if cmp -s  "${filename}" "${file}" ; then
 11         basename "${filename}" # тук може и само echo
 12     fi
 13 done < <(find "${directory}" -type f)


```
## 05-b-5500.txt
- **Условие:**<br/>
Да се напише shell script, който генерира HTML таблица съдържаща описание на
потребителите във виртуалката ви. Таблицата трябва да има:
- заглавен ред с имената нa колоните
- колони за username, group, login shell, GECOS field (https://en.wikipedia.org/wiki/Gecos_field)

Пример:
$ ./passwd-to-html.sh > table.html
$ cat table.html
примерния файл си го виж,преебава структурата
- **Решение:**
```bash
```
## 05-b-6600.txt
- **Условие:**<br/>
Да се напише shell скрипт, който получава единствен аргумент директория и изтрива всички повтарящи се (по съдържание) файлове в дадената директория. Когато има няколко еднакви файла, да се остави само този, чието име е лексикографски преди имената на останалите дублирани файлове.

Примери:
```bash
$ ls .
f1 f2 f3 asdf asdf2
# asdf и asdf2 са еднакви по съдържание, но f1, f2, f3 са уникални

$ ./rmdup .
$ ls .
f1 f2 f3 asdf
# asdf2 е изтрит
```

- **Решение:**
```bash
  1 #/bin/bash
  2 if [[ "$#" -ne 1 ]]; then
  3     echo "Wrong usage: Only 1 parameter needed < directory>"
  4     exit 1
  5 fi
  6 directory="${1}"
  7 found=false
  8 currentIndex=0
  9 declare -a array
 10 while read filename; do
 11     if [[ ${#array[@]} -eq 0  ]]; then
 12         array[0]="$filename"
 13         echo "adding first element to array $filename"
 14     else
 15         found=false
 16         currentIndex=0
 17         for file in "${array[@]}"; do
 18             if cmp -s "$file" "$filename"; then
 19                 found=true
 20                 if [[ "$filename" < "$file" ]]; then
 21                     array[$currentIndex]="$filename"
 22                     rm "$file"
 23                     break
 24                 else
 25                     rm "$filename"
 26                     break
 27                 fi
 28             else
 29                 currentIndex=$((currentIndex+1))
 30             fi
 31         done
 32         if [[ "$found" == "false" ]]; then
 33             array[${#array[@]}]="$filename"
 34         fi
 35     fi
 36 echo ""
 37 echo "after $filename --------------"
 38 echo "${array[@]}"
 39 echo ""
 40
 41 done < <(find "$directory" -mindepth 1 -maxdepth 1 -type f)
```
## 05-b-6800.txt 
- **Условие:**<br/>
Да се напише shell скрипт, който получава единствен аргумент директория и отпечатва списък с всички файлове и директории в нея (без скритите).
До името на всеки файл да седи размера му в байтове, а до името на всяка директория да седи броят на елементите в нея (общ брой на файловете и директориите, без скритите).

a) Добавете параметър -a, който указва на скрипта да проверява и скритите файлове и директории.

Пример:
```bash
$ ./list.sh .
asdf.txt (250 bytes)
Documents (15 entries)
empty (0 entries)
junk (1 entry)
karh-pishtov.txt (8995979 bytes)
scripts (10 entries)
```
- **Решение:**
```bash
```
## 05-b-7000.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приема произволен брой аргументи - имена на файлове. Скриптът да прочита от стандартния вход символен низ и за всеки от зададените файлове извежда по подходящ начин на стандартния изход броя на редовете, които съдържат низа.

NB! Низът може да съдържа интервал.
- **Решение:**
```bash
```
## 05-b-7100.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приема два параметъра - име на директория и число. Скриптът да извежда на стандартния изход имената на всички обикновени файлове във директорията, които имат размер, по-голям от подаденото число.
- **Решение:**
```bash
```
## 05-b-7200.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приема произволен брой аргументи - имена на файлове или директории. Скриптът да извежда за всеки аргумент подходящо съобщение:
	- дали е файл, който може да прочетем
	- ако е директория - имената на файловете в нея, които имат размер, по-малък от броя на файловете в директорията.
- **Решение:**
```bash
```
## 05-b-7500.txt
- **Условие:**<br/>
Напишете shell script guess, която си намисля число, което вие трябва да познате. В зависимост от вашия отговор, програмата трябва да ви казва "надолу" или "нагоре", докато не познате числото. Когато го познаете, програмата да ви казва с колко опита сте успели.

./guess (програмата си намисля 5)

Guess? 22
...smaller!
Guess? 1
...bigger!
Guess? 4
...bigger!
Guess? 6
...smaller!
Guess? 5
RIGHT! Guessed 5 in 5 tries!

Hint: Един начин да направите рандъм число е с $(( (RANDOM % b) + a  )), което ще генерира число в интервала [a, b]. Може да вземете a и b като параметри, но не забравяйте да направите проверката.
- **Решение:**
```bash
```
## 05-b-7550.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приема параметър - име на потребител. Скриптът да прекратява изпълненито на всички текущо работещи процеси на дадения потребител, и да извежда колко са били те.

NB! Може да тествате по същият начин като описаният в 05-b-4300
- **Решение:**
```bash
```
## 05-b-7700.txt
- **Условие:**<br/>
Да се напише shell скрипт, който приема два параметъра - име на директория и число. Скриптът да извежда сумата от размерите на файловете в директорията, които имат размер, по-голям от подаденото число.
- **Решение:**
```bash
```
## 05-b-7800.txt
- **Условие:**<br/>
Да се напише shell скрипт, който намира броя на изпълнимите файлове в PATH.
Hint: Предполага се, че няма спейсове в имената на директориите
Hint2: Ако все пак искаме да се справим с този случай, да се разгледа IFS променливата и констуркцията while read -d
- **Решение:**
```bash
```
## 05-b-8000.txt
- **Условие:**<br/>
Напишете shell script, който получава като единствен аргумент име на потребител и за всеки негов процес изписва съобщение за съотношението на RSS към VSZ. Съобщенията да са сортирани, като процесите с най-много заета виртуална памет са най-отгоре.

Hint:
Понеже в Bash няма аритметика с плаваща запетая, за смятането на съотношението използвайте командата bc. За да сметнем нампример 24/7, можем да: echo "scale=2; 24/7" | bc
Резултатът е 3.42 и има 2 знака след десетичната точка, защото scale=2.
Алтернативно, при липса на bc ползвайте awk.
- **Решение:**
```bash
```
## 05-b-9100.txt
- **Условие:**<br/>
Опишете поредица от команди или напишете shell скрипт, които/който при известни две директории SOURCE и DESTINATION:
- намира уникалните "разширения" на всички файлове, намиращи се някъде под SOURCE. (За простота приемаме, че в имената на файловете може да се среща символът точка '.' максимум веднъж.)
- за всяко "разширение" създава по една поддиректория на DESTINATION със същото име
- разпределя спрямо "разширението" всички файлове от SOURCE в съответните поддиректории в DESTINATION
- **Решение:**
```bash
```
## 05-b-9200.txt
- **Условие:**<br/>
Да се напише shell скрипт, който получава произволен брой аргументи файлове, които изтрива.
Ако бъде подадена празна директория, тя бива изтрита. Ако подадения файл е директория с поне 1 файл, тя не се изтрива.
За всеки изтрит файл (директория) скриптът добавя ред във log файл с подходящо съобщение.

а) Името на log файла да се чете от shell environment променлива, която сте конфигурирали във вашия .bashrc.
б) Добавете параметър -r на скрипта, който позволява да се изтриват непразни директории рекурсивно.
в) Добавете timestamp на log съобщенията във формата: 2018-05-01 22:51:36

Примери:
$ export RMLOG_FILE=~/logs/remove.log
$ ./rmlog -r f1 f2 f3 mydir/ emptydir/
$ cat $RMLOG_FILE
[2018-04-01 13:12:00] Removed file f1
[2018-04-01 13:12:00] Removed file f2
[2018-04-01 13:12:00] Removed file f3
[2018-04-01 13:12:00] Removed directory recursively mydir/
[2018-04-01 13:12:00] Removed directory emptydir/
- **Решение:**
```bash
```
## 05-b-9500.txt
- **Условие:**<br/>
(Цветно принтиране) Напишете shell script color_print, който взима два параметъра.

Първият може да е измежду "-r", "-g" "-b", а вторият е произволен string.
На командата "echo" може да се подаде код на цвят, който ще оцвети текста в определения цвят.
В зависимост от първия аргумент, изпринтете втория аргумен в определения цвят:

"-r" е червено. Кодът на червеното е '\033[0;31m' (echo -e "\033[0;31m This is red")
"-g" е зелено. Кодът на зеленото е '\033[0;32m' (echo -e "\033[0;32m This is green")
"-b" е синьо. Кодът на синьото е '\033[0;34m' (echo -e "\033[0;34m This is blue")
Ако е подадена друга буква изпишете "Unknown colour", а ако изобщо не е подаден аргумент за цвят, просто изпишете текста.

Hint:

В края на скрипта си напишете:
echo '\033[0m'
,за да не се прецакат цветовете на терминала. Това е цветът на "няма цвят".
- **Решение:**
```bash
```
## 05-b-9501.txt
- **Условие:**<br/>
Този път програмата ви ще приема само един параметър, който е измежду ("-r", "-b", "-g", "-x").
Напишете shell script, който приема редовете от stdin и ги изпринтва всеки ред с редуващ се цвят. Цветовете вървят RED-GREEN-BLUE и цветът на първия ред се определя от аргумента.
 Ако е подаден аргумент "-x", то не трябва да променяте цветовете в терминала (т.е., все едно сте извикали командата cat).

Hint: Не забравяйте да връщате цветовете в терминала.
- **Решение:**
```bash
```
## 05-b-9600.txt
- **Условие:**<br/>
Да се напише shell скрипт, който получава произволен брой аргументи файлове, които изтрива.
Ако бъде подадена празна директория, тя бива изтрита. Ако подадения файл е директория с поне 1 файл, тя не се изтрива.

Да се дефинира променлива BACKUP_DIR (или друго име), в която:
- изтритите файлове се компресират и запазват
- изтритите директории се архивират, комприсират и запазват
- имената на файловете е "filename_yyyy-mm-dd-HH-MM-SS.{gz,tgz}", където filename е оригиналното име на файла (директорията) преди да бъде изтрит

а) Добавете параметър -r на скрипта, който позволява да се изтриват непразни директории рекурсивно и съответно да се запазят в BACKUP_DIR

Примери:
```bash $ export BACKUP_DIR=~/.backup/

# full-dir/ има файлове и не може да бъде изтрита без параметър -r
$ ./trash f1 f2 full-dir/ empty-dir/
error: full-dir/ is not empty, will not detele
$ ls $BACKUP_DIR
f1_2018-05-07-18-04-36.gz
f2_2018-05-07-18-04-36.gz
empty-dir_2018-05-07-18-04-36.tgz

$ ./trash -r full-dir/

$ ls $BACKUP_DIR
f1_2018-05-07-18-04-36.gz
f2_2018-05-07-18-04-36.gz
full-dir_2018-05-07-18-04-50.tgz
empty-dir_2018-05-07-18-04-36.tgz

# можем да имаме няколко изтрити файла, които се казват по един и същ начин
$ ./trash somedir/f1

$ ls $BACKUP_DIR
f1_2018-05-07-18-04-36.gz
f1_2018-05-07-18-06-01.gz
f2_2018-05-07-18-04-36.gz
full-dir_2018-05-07-18-04-50.tgz
empty-dir_2018-05-07-18-04-36.tgz
```
- **Решение:**
```bash
```
## 05-b-9601.txt
- **Условие:**<br/>
Да се напише shell скрипт, който възстановява изтрити файлове, които имат запазено копие в BACKUP_DIR (от предната задача).
При възстановяването файловете да се декомпресират, а директориите да се декомпресират и разархивират.

а) Да се дефинира параметър -l, който изрежда всички файлове, които могат да бъдат възстановени и датата на тяхното изтриване.

б) Скриптът да приема 2 параметъра. Първият е името на файла, който да се възстанови, а вторията е директорията, в която файлът да бъде възстановен. Ако вторият аргумент липсва, файлът да се възстановява в сегашната директория, където скриптът се изпълнява.

в) Когато има N > 1 запазени файла със същото име, да се изпише списък с N реда на потребителя и да се изиска той да въведе цяло число от 1 до N, за да избере кой файл да възстанови.

Примери:
```bash # BACKUP_DIR трябва да е дефинирана преди използването на скрипта
$ echo $BACKUP_DIR
~/.backup

$ ./restore.sh -l
f1  (2018/05/07 18:04:36)
f1  (2018/05/07 18:06:01)
f2  (2018/05/07 18:04:36)
full-dir    (2018/05/07 18:04:50)
empty-dir   (2018/05/07 18:04:36)

$ ls restored-dir/
# възстановяване на файл в подадена директория
$ ./restore.sh f2 target-dir/
$ ls restored-dir/
f2

# възстановяване на дублиран файл в сегашната директория
$ ./restore.sh f1
(1) f1  (2018/05/07 18:04:36)
(2) f1  (2018/05/07 18:06:01)
choose file (1, 2):
# потребителят въвежда 2

$ ls
f1

$ ./restore.sh -l
f1  (2018/05/07 18:04:36)
full-dir    (2018/05/07 18:04:50)
empty-dir   (2018/05/07 18:04:36)

# възстановяване на директория в сегашната директория
$ ./restore.sh full-dir
$ ls
f1  full-dir/
```
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
