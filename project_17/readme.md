<img width="555" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/b395f81f-d718-4c1b-80dd-ddda347b7207"># *Project17：比较Firefox和谷歌的记住密码插件的实现区别
## 1.浏览器版本
|浏览器|版本|
|:---|:---|
|Firefox|115.0.2 (64 位)|
|Google Chrome|114.0.5735.199（正式版本（64 位）|
## 2.记住密码的截图
Firefox:

<img width="875" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/1913843f-909d-4259-8f62-5d47425cfd01">
Chrome:

<img width="866" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/673a3a08-beed-44cf-a7d8-bd2174e8bc78">
<br>

## 
chrome就是用户系统密码将用户保存在浏览器的密码加密保存在一个SQLite数据库里，
保存在电脑里\Chrome\User Data\Default\Login Data 文件中，导出工具就是对这个文件执行一下win32crypt.CryptUnprotectData函数，调用系统解密就可以直接解密出里面保存的密码。

<img width="555" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/8fb75e1b-3660-42f3-9d13-3cc0ef6d5655">

