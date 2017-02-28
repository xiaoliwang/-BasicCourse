# mac
该文档包含mac的一些基本使用方法和常用装机软件

---

[TOC]

## 基本使用

### [翻墙][1](基于shadowsocks, proxyChains-ng)
先安装proxychains4[^ccircumvention]  
需要[disable system integrity protection in os X][2]

1. reboot the mac and hold down command + R
2. input `csrutil disable`; 
3. reboot;

### [ssh远端服务器][3]
#### 别名登陆
SSH可以在`/etc/ssh_config`或者`~/.ssh/config`文件里给远程连接主机配置别名。在`~/.ssh/config`里添加如下配置:

```ssh
# ssh app1 相当于 ssh root@192.168.1.10
Host app1
HostName 192.168.1.10
User root
```

#### 免密码
只需要将公钥`id_rsa.pub`的内容拷贝到远程服务器`~/.ssh/authorized_keys`即可

1. 使用`ssh-keygen -t rsa`在本地生成rsa公钥
2. 将rsa公钥`id_rsa.pub`放到远程服务器[^nickname]:
	* 远程服务器有authorized_keys 的情况:  
	`cat ~/.ssh/id_rsa.pub | ssh username@example.com "cat - >> ~/.ssh/authorized_keys"`
	* 远程服务器有authorized_keys 的情况: 
	`scp ~/.ssh/id_rsa.pub username@example.com:~/.ssh/authorized_keys`
	
#### 自动补全
在`~/.bash_profile`文件末尾追加如下行[^cut][^complete]:
```shell
complete -W "$(echo `cat ~/.ssh/config | grep 'Host '| cut -f 2 -d ' '|uniq`;)" ssh
```


<!-- links -->
[1]:http://yanghui.name/blog/2015/07/19/make-all-command-through-proxy/
[2]:http://osxdaily.com/2015/10/05/disable-rootless-system-integrity-protection-mac-os-x/
[3]:http://codelife.me/blog/2012/09/01/ssh-session-profile-management-in-terminal-of-macos-x/

<!-- footnotes -->
[^ccircumvention]: 这里主要是terminal翻墙
[^nickname]: 其中的username@example.com可以使用昵称替代
[^cut]: cut -f n -d delimiter 为以delimiter为分割，取第n个
[^complete]: Split a String by IFS to get Completion Values,IFS为字段分隔符，包含空白，tab和回车等
