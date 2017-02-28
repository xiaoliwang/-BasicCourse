## 硬盘管理

[TOC]

### 磁盘管理
```shell
df -h # 查看磁盘使用情况 -h 人性化显示
df -a # 查看所有文件系统的磁盘使用情况
df -k # 以k字节为单位显示
df -i # 显示i节点信息，而不是磁盘块
df -T 分区名 # 查看文件类型 
df -t 文件类型 # 查看指定文件类型磁盘使用情况，例子 df -t ext4
df -x 文件类型 # 查看非指定文件类型磁盘使用情况，与-t相反

du -sh # 查看目录使用情况 -s 递归目录 -h 人性化显示
```

### 设备对应文件规则

#### 设备对应命名规则
|设备|文件[^1]|
|:---:|:---:|
|硬盘STAT，USB|/dev/sd[a-p]|
|软盘|/dev/fd[0-1]|
|CD/DBD|/dev/cdrom|
|打印机|/dev/lp[ 0-15 ]|

#### 分区规则
|分区|规则|
|:---:|:---:|
|主分区(primary)|命名1-4|
|扩展分区(extended)|命名1-4|
|主逻辑分区(logical)|命名5-(IDE最多59个，SATA最多11个)|

### 硬盘分区

#### 硬盘分区及挂载

```shell
fdisk -l # 查看linux硬盘分区情况

fdisk /dev/sda #对硬盘进行分区，其中/dev/sda是硬盘文件

# command>m（获取帮助）
# command>n（新建分区）
# command>p（显示分区表） 
# command>d（删除分区）
# command>q（退出）
# command>w（保存）

mkfs -t ext3(ext4) /dev/sda(分区名) #对分区进行格式化
mount /dev/sda /b #对分区硬盘进行挂载
```

#### 自动挂载

```shell
vim /etc/fstab #每次启动都挂载
# 文件格式：<file system> <dir> <type> <options> <dump> <check> 使用空格或者tab分隔
# 例子：/dev/sda /b ext4 default 0 0
# file system 为分区
# dir 为挂载点
# type：挂在类型
# options：选项，一般使用default
# dump：是否备份（2：不定期进行dump操作，1：每天进行dump操作，0：否）
# check：是否检验扇区（2，1：检验，0不检验）
```

[^1]: 文件名一般情况是这样，但是并不是一定如此

