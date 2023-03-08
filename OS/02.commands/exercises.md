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
- ## 
- **Условие:**<br/>
Изведете само първите 5 реда от /etc/services
- **Решение:**
- ##
- **Условие:**<br/>
Изведете само първите 5 реда от /etc/services
- **Решение:**
- ##
**Условие:**<br/>
Изведете само първите 5 реда от /etc/services
- <span style ="color:#99ccff"> **Решение**</span>
- ##
- **Условие:**<br/>
Изведете само първите 5 реда от /etc/services
- <span style ="color:#99ccff"> **Решение**</span>