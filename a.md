# Syalis

## 开发环境

Ubuntu 20.04
gcc 9.1
cmake xmake

## 项目路径

bin ------------ 二进制
build ---------- 中间文件
camke ---------- cmake 函数文件夹
CMakeLists.txt - cmake 定义文件
lib ------------ 库的输出
Makefile ------- makefile 文件
syalis --------- 源代码
tests ---------- 测试代码

## 日志系统

1. Log4j
    Logger (定义日志类别)
      |---Formatter (日志格式)
    Appender (日志输出位置)
2. s

## 配置系统

Config -> Yaml

yaml-cpp : github
mkdir build && cd build && cmake .. && make && sudo make install
/usr/local/include，库文件在/usr/local/lib

```cpp
//YAML 加载文件，返回一个 YAML::Node 对象
YAML::Node node = YAML::LoadFile(filename);
node.IsMap();
//map结构
for(auto it = node.begin(); it != node.end(); ++it) { 
  it->first; it->second; 
}
node.IsSequence();
for(size_t i = 0; i < node.size(); ++i) {

}
node.IsScalar();
```

配置系统原则为约定优于配置

```cpp
//Template, FromStr, ToStr 转化的方法
template <T, FromStr, ToStr>
class ConfigVar;

//统一的通用模式
template <F, T>
LexicalCast

//容器偏特化 支持vector
// list, set, map, unordered_set, unordered_map
// map/unordered_map 需要支持key = std::string

// 问题: Config::Lookupo(key) , key相同, 类型不同, 不会报错

```

```yaml

logs:
  - name: root
    level: info
    formatters: %d%T%m%n
    appender:
      - type: FileLogAppender
        path: log.txt
      - type: StdoutLogAppender
  - name: system
    level: debug
    formatter: %d%T%m%n
      - type: FileLogAppender
        path: log.txt
      - type: StdoutLogAppender
#logs: object map型
#'- name' - 为数组型
```

自定义类型，需要实现sylis::LexicalCast, 偏特化
实现后就可以支持支持Config解析自定义类型, 自定义类型可以和常规STL容器一起使用

## 协程库封装

将异步的操作封装成同步

## socket 函数库

## http 协议开发

## 分布式协议库

把逻辑业务抽象成插件
把服务器交互的逻辑放在插件里
把功能、业务和系统业务分离

## 推荐系统
