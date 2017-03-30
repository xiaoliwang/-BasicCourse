# HTML

```shell
yum install nmap-ncat -y # 安装nc

curl -i # 查看完整response报文

nc -l 8000 # 监听8000端口
nc localhost:8000 # 与localhost建立连接
```

HTTP/1.1 200 ok
Content-Length: 500
Content-Type: text/html

<h1>Hello Wolrd</h1>