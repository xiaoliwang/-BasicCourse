# Composer Command
> 该文档包含PHP包管理系统Composer的配置文件

[TOC]

---

## 初始化及安装

在命令行中敲入如下命令

### composer init
> 生成**Composer config**文件`composer.json`

1. Package name (`<vendor>/<name>`)：这个为包名，一般前面为作者名，后面为文件夹名。
2. Description： 这个为描述，描述包的用途
3. Author： 作者，一般格式为`name <email>`。
4. Minimum Stability： 定义稳定性过滤。默认为`stable`，有以下五种未定型表示`dev`、 `alpha`、 `beta`、 `RC`、 `stable`。
5. Package Type： 包种类，默认`library`、有以下几种类型`library`、`project`、`metapackage`、`composer-plugin`
6. License: 协议，可参考下图：

![free_software_licenses](free_software_licenses.png)

### composer install
读取当前目录`composer.json`文件，处理依赖关系，并安装到vendor目录下。

- `--dev` 安装`require-dev`中列出的包
- `--no-dev` 跳过`require-dev`中列出的包

### composer require
添加新的依赖包到当前目录

### composer update
获取依赖的最新版本，如果是真对某几个的话，可以使用如下方法(支持通配符):  
`composer update vendor/package vendor/*`

### composer remove
删除以来包

### composer search
搜索依赖包

### compoer dump-autoload
重新注册自动读取文件
