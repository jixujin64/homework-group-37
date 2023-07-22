# *Project17：比较Firefox和谷歌的记住密码插件的实现区别
## 1.浏览器版本
|浏览器|版本|
|:---|:---|
|Firefox|115.0.2 (64 位)|
|Google Chrome|114.0.5735.199（正式版本（64 位）|
## 2.记住密码的功能和截图
Firefox和谷歌浏览器都支持自动提示保存密码的功能，当用户在登录表单中输入用户名和密码时，浏览器会弹出一个提示框询问是否保存密码。用户选择保存密码后，浏览器会将用户名和密码保存到本地密码管理器中。

Firefox:

<img width="875" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/1913843f-909d-4259-8f62-5d47425cfd01">
Chrome:

<img width="866" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/673a3a08-beed-44cf-a7d8-bd2174e8bc78">
<br>

## 
chrome就是用户系统密码将用户保存在浏览器的密码加密保存在一个SQLite数据库里，
保存在电脑里\Chrome\User Data\Default\Login Data 文件中，导出工具就是对这个文件执行一下win32crypt.CryptUnprotectData函数，调用系统解密就可以直接解密出里面保存的密码。

<img width="555" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/8fb75e1b-3660-42f3-9d13-3cc0ef6d5655">
比较：

API支持：

Firefox使用WebExtensions API作为插件开发的标准。
谷歌浏览器使用Chrome插件API作为插件开发的标准。

功能限制：

Firefox的WebExtensions API功能较为有限，对于密码管理方面的功能提供不够丰富。
谷歌浏览器的Chrome插件API功能相对更加强大，提供了更多的密码管理相关的API。

用户界面：

Firefox的记住密码功能是通过浏览器自身的密码管理器实现的，所以用户界面较为简洁。
谷歌浏览器的记住密码功能以及插件界面相对更加丰富和复杂，支持更多的自定义选项。

Firefox登录信息存储：

<img width="614" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/b0d90430-5990-4a90-b53d-5e96720a4b89">

Firefox 3.x确实将Cookies储存在以下文件夹中:

C:\Documents and Settings\{your username}
\Application Data\Mozilla\Firefox\Profiles\{random mix char}.default

cookie信息存储在文件“ cookies.sqlite”和“ permissions.sqlite”中。

加密算法：

Firefox使用一个称为"Login Manager"的密码管理器来存储和管理用户的密码。在密码存储方面，Firefox使用基于主机操作系统的加密技术，如Windows上的DPAPI（Data Protection Application Programming Interface）或Mac上的Keychain。这意味着密码被安全地存储在操作系统的加密存储区域中。Firefox还使用称为"Master Password"的功能，让用户设置一个主密码来保护保存在密码管理器中的其他密码。这个主密码使用高强度的加密算法进行保护，通常是基于PBKDF2（Password-Based Key Derivation Function 2）的派生密钥算法。

Chrome使用Google账户来同步和存储用户的密码数据。这些密码在用户登录Google账户后通过加密方式上传到Google的服务器，并在用户在其他设备上登录Chrome时进行解密同步。这种同步机制使用了Google的加密和安全技术来保护用户的密码数据。相比于Firefox的主密码功能，Chrome没有直接提供类似的密钥保护功能。用户的密码数据主要受到Google账户的安全性和加密保护的影响。






## 参考资料：
[1] https://blog.csdn.net/cyan20115/article/details/106554264

