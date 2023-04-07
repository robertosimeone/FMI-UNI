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
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```
## 
- **Условие:**<br/>
- **Решение:**
```bash
```