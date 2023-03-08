# Exercises
## 02-a-5401.txt
- <span style ="color:#88B04B"> **Условие**</span> </br>
Изведете само първите 5 реда от /etc/services
- <span style ="color:#99ccff"> **Решение**</span>
```bash
head -n 5 /etc/services
```
## 02-a-5402.txt
- <span style ="color:#88B04B"> **Условие**</span> </br>
Изведете всички обикновени ("regular") файлове, които само преките поддиректории на /etc съдържат
- <span style ="color:#99ccff"> **Решение** <br/></span>
  

<p style = "text-align:center">Първи начин</p>

```bash
find /etc/*/ -maxdepth 1 -type f
```
<br/>
<p style = "text-align:center">Втори начин</p>
<br/>

```bash
find /etc -mindepth 2 -maxdepth 2 -type f
```

## 02-a-5403.txt
- <span style ="color:#88B04B"> **Условие**</span> </br>
Изведете всички преки поддиректории на /etc
- <span style ="color:#99ccff"> **Решение**</span>
<p style = "text-align:center">Първи начин</p>

```bash
find /etc -mindepth 1 -maxdepth 1 -type d
```
<p style = "text-align:center">Втори начин</p>

```bash
    ls -d /etc/*/
```
- ## 
- <span style ="color:#88B04B"> **Условие**</span> </br>
Изведете само първите 5 реда от /etc/services
- <span style ="color:#99ccff"> **Решение**</span>
- ##
- <span style ="color:#88B04B"> **Условие**</span> </br>
Изведете само първите 5 реда от /etc/services
- <span style ="color:#99ccff"> **Решение**</span>
- ##
- <span style ="color:#88B04B"> **Условие**</span> </br>
Изведете само първите 5 реда от /etc/services
- <span style ="color:#99ccff"> **Решение**</span>
- ##
- <span style ="color:#88B04B"> **Условие**</span> </br>
Изведете само първите 5 реда от /etc/services
- <span style ="color:#99ccff"> **Решение**</span>