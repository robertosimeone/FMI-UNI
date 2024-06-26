# Exercises
## 02-a-5401.txt
- **Условие:**<br/>
Изведете само първите 5 реда от /etc/services
- **Решение:**
```bash
head -n 5 /etc/services
```
## 02-a-5402.txt
- **Условие:**<br/>
Изведете всички обикновени ("regular") файлове, които само преките поддиректории на /etc съдържат
- **Решение:**
  

Първи начин

```bash
find /etc/*/ -maxdepth 1 -type f
```
<br/>
Втори начин
<br/>

```bash
find /etc -mindepth 2 -maxdepth 2 -type f
```

## 02-a-5403.txt
- **Условие:**<br/>
Изведете всички преки поддиректории на /etc
- **Решение:**

Първи начин

```bash
find /etc -mindepth 1 -maxdepth 1 -type d
```
Втори начин

```bash
    ls -d /etc/*/
```
## 02-a-5504.txt
- **Условие:**<br/>
Изведете всички обикновени файлове в директорията /tmp които са от вашата група, които имат write права за достъп за група или за останалите(o=w)
- **Решение:**
```bash
find /tmp -perm -022 -group "$(id -g -n)"
```
## 02-a-5505.txt
- **Условие:**<br/>
Изведете всички файлове, които са по-нови от practice/01/f1 ( би трябвало да е създаден като част от по-ранна задача ).
- **Решение:**
```bash
find . -newer practice/01/f1
```
## 02-a-5506.txt
- **Условие:**<br/>
Изтрийте файловете в home директорията си по-нови от practice/01/f3 (подайте на rm опция -i за да може да изберете само тези които искате да изтриете).
- **Решение**
```bash
find .  -mindepth 1  -newer now.txt -type f -exec rm -i {} \;
```
## 02-a-9500.ext
- **Условие:**<br/>
Използвайки едно извикване на командата find, отпечатайте броя на редовете във всеки обикновен файл в /etc директорията.    
- **Решение**
```bash
find /etc -maxdepth 1 -type f -exec wc -l {} \;
```
## 02-b-4000.txt
- **Условие:**<br/>
Копирайте най-малкия файл от тези, намиращи се в /etc, в home директорията си.
- **Решение**
```bash
cp "$(find /etc -printf "%s %p\n" 2> /dev/null | sort -n | tail -n 1 | cut -d ' ' -f 2)" ~
```