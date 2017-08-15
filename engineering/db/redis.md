# Redis 开发运维实践规范

## 开发设计规范

### 数据库选择

使用以下命令切换数据库：

```redis
select db-index
```

默认数据库为0，默认数据库数量为16个。约定以下规则：

1. 使用 db0 作为共享数据库，存放内容为所有项目均可访问的共享内存信息。
2. db1 ~ db9 为私有数据库，仅项目本身之间可以共享内存信息。
3. db10 ~ db15 为群组数据库，存放指定项目组的共享内存信息。



### Key 设计

key 的格式约定为：`type:object:[attr]:[attr_value]:[field]`。其中 `:` 为分隔符，`[]` 中的内容为可选项。使用 `_` 作为单词间的连接符。键名中不能包含

> key 中除了分隔符和连接符只能包含数字和字母
>
> 不推荐使用含义不清的key，key的长度限制在 100 个字节以内

其中 type 为 key 的类型。主要有以下几种类型：

- 锁：lock
- 缓存：cache
- session：session
- 计数器：counter
- 队列：list
- 验证数据：validate

object 为对象名。如果某个对象用于多处不同目的，也在此进行区分，使用 `_` 进行分隔。

attr 为对象属性名，attr_value 为属性值。当对象名无法制定唯一对象时，使用该附加条件进行约束。该键值对可以存在多个。

field 为缓存对象属性名。如果缓存的不是整个对象而是对象的某个属性，使用该字段进行区分。

以下是对 user 表的一个例子：

| id   | name   | email          | password |
| ---- | ------ | -------------- | -------- |
| 1    | xiaoli | xiaoli@163.com | 1234     |

对 user 中的 email 字段进行缓存时，key 可以设置为 `cache:user:id:1:email`。

对 user 更新上锁时， key可以设置为 `lock:user:id:1` 。 



### 计数器设计

在对大量连续 `key` 的数据进行计数时，我们可以使用 `hash ` 来替代简单的 `string` 。因为 `hash` 结构会对其中的元素进行压缩存储，从而节约大量内存。而且经测试，当 `hash field` 的数量小于 1000 时性能最优。下面我们看一个例子，对音频的播放量进行缓存计数：

最开始，我们使用 `string` 来计数，语句为 `incr counter:sound_views:id:123456`。

当使用 `hash` 优化时，我们可以使用 `HINCRBY counter:sound_views:segids:123 456 1` 进行替代。



### 分布式锁设计

在使用 redis 做分布式锁的时候，我们最初使用简单的使用以下语句：

```redis
# 上锁
setnx lock:temp 1;
expire lock:temp 600;

# 解锁
delete lock:temp;
```



但是这里会出现一个致命的问题。如果上锁之后，进程因为某些原因突然挂掉了，那么我们就没法对该锁进行解锁。所以该方案在某些特定条件下会产生致命问题。经过重新设计，我们将该方案优化为一下版本：

```redis
# 上锁
timeout = current_time + lock_time + 1 
if (setnx lock:temp timeout || (now > get lock:temp && now > getset lock:temp timeout) {
	// 上锁成功...
}

# 解锁
if (now < get lock:temp) delete lock:temp
```

这样就完美解决之前死锁的问题。





### 临时文件

scan 可能会存在重复的值，中途添加或删除的键则不保证其是否遍历到。

randomkey 随机返回一个key

pipeline 不等待返回