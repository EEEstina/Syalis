# 环境搭建

yum install glibc-static
yum install glibc-devel
yum install boost-devel
yum install mysql-devel
git

---

以下是 CentOS/RHEL 的 `yum` 包在 Ubuntu/Debian 系统中的对应关系及安装命令：

---

### **1. `glibc-static` ➔ `libc6-dev-static`
```bash
sudo apt-get install libc6-dev-static  # 提供 glibc 静态库
```

### **2. `glibc-devel` ➔ `build-essential` + `libc6-dev`
```bash
sudo apt-get install build-essential libc6-dev  # 包含 C/C++ 基础开发工具链
```

### **3. `boost-devel` ➔ `libboost-all-dev`
```bash
sudo apt-get install libboost-all-dev  # Boost 全组件开发包
```

### **4. `mysql-devel` ➔ `libmysqlclient-dev`
```bash
sudo apt-get install libmysqlclient-dev  # MySQL 客户端开发库
```

### **5. `git` ➔ `git`（同名）
```bash
sudo apt-get install git  # Git 版本控制系统
```

---

### **一键安装所有包**
```bash
sudo apt-get update && \
sudo apt-get install -y \
  libc6-dev-static \
  build-essential \
  libc6-dev \
  libboost-all-dev \
  libmysqlclient-dev \
  git
```

---

### **关键差异说明**
| CentOS 包名          | Ubuntu 包名               | 功能差异                                                                 |
|----------------------|---------------------------|------------------------------------------------------------------------|
| `glibc-static`       | `libc6-dev-static`        | 提供静态链接的 C 标准库（如 `libc.a`）                                     |
| `build-essential`    | 无直接对应                | 元包，包含 `gcc/g++/make` 等基础编译工具（CentOS 需要手动安装 `gcc` 等）       |
| `libboost-all-dev`   | `boost-devel`             | Ubuntu 的 Boost 开发包默认包含全组件，CentOS 需单独安装如 `boost-thread-devel` |

---

### **验证安装结果**
```bash
# 检查 C 库开发文件
ls /usr/include/stdio.h      # 头文件存在性验证
ls /usr/lib/x86_64-linux-gnu/libc.a  # 静态库验证

# 检查 Boost 开发文件
ls /usr/include/boost/version.hpp

# 检查 MySQL 开发文件
ls /usr/include/mysql/mysql.h

# 检查 Git
git --version
```

---

### **扩展说明**
- 如果只需要 **部分 Boost 组件**，可指定安装（例如只安装线程和系统库）：
  ```bash
  sudo apt-get install libboost-thread-dev libboost-system-dev
  ```
- 若需 **最新版本的 Boost**，需通过源码编译或第三方 PPA 安装。

---

在 C++ 中，将源代码文件编译为可执行文件的过程可以分为 **4 个核心阶段**。以下是每个阶段的详细说明和实际示例：

---

### **1. 预处理（Preprocessing）**
**作用**：处理源代码中的预处理指令，生成**纯 C++ 代码**。  
**关键操作**：
- `#include` 头文件展开
- `#define` 宏替换
- 条件编译（`#ifdef`、`#endif` 等）

**示例**：
```cpp
// main.cpp
#include <iostream>
#define PI 3.1415

int main() {
    std::cout << "PI = " << PI << std::endl;
    return 0;
}
```

**手动执行预处理**：
```bash
g++ -E main.cpp -o main.ii  # 生成预处理后的文本文件
```

**预处理后的文件片段**：
```cpp
// main.ii（展开后的 iostream 头文件内容）
...
extern ostream cout;  // 来自 iostream 的代码
...
int main() {
    std::cout << "PI = " << 3.1415 << std::endl;  // 宏被替换
    return 0;
}
```

---

### **2. 编译（Compilation）**
**作用**：将预处理后的代码翻译成**汇编代码**（Assembly）。  
**关键操作**：
- 语法和语义检查
- 生成中间汇编代码
- 代码优化（如 `-O2` 优化级别）

**生成汇编代码**：
```bash
g++ -S main.ii -o main.s  # 从预处理文件生成汇编
# 或直接一步到位
g++ -S main.cpp -o main.s
```

**汇编文件示例（main.s）**：
```assembly
.LC0:
    .string "PI = "
main:
    pushq   %rbp
    movq    %rsp, %rbp
    movl    $.LC0, %esi
    movl    std::cout, %edi
    call    std::basic_ostream<char, ...>& std::operator<< <...>(std::basic_ostream<...>&, char const*)
    ...
```

---

### **3. 汇编（Assembly）**
**作用**：将汇编代码转换为**机器码（二进制目标文件）**。  
**关键产物**：
- `.o` 或 `.obj` 目标文件
- 符号表（函数和变量地址信息）

**生成目标文件**：
```bash
g++ -c main.s -o main.o  # 从汇编生成目标文件
# 或直接一步到位
g++ -c main.cpp -o main.o
```

**查看目标文件信息**：
```bash
nm main.o  # 查看符号表
```
输出示例：
```
0000000000000000 T main
                 U _GLOBAL_OFFSET_TABLE_
                 U __gxx_personality_v0
                 U std::cout
                 U std::basic_ostream<char,...>& std::operator<< <...>(...)
```

---

### **4. 链接（Linking）**
**作用**：合并多个目标文件和库文件，生成**最终可执行文件**。  
**关键操作**：
- 解析符号引用（如 `std::cout` 的实现）
- 静态链接（`.a` 库）或动态链接（`.so`/`.dll` 库）

**生成可执行文件**：
```bash
g++ main.o -o my_program  # 单文件链接
# 多文件示例
g++ main.o utils.o -o my_program
```

**链接过程示意图**：
```
main.o (你的代码) 
  ↓ 
+ libstdc++.so (C++ 标准库) 
  ↓ 
= my_program（可执行文件）
```

---

### **完整编译流程示例**
```bash
# 一步完成所有阶段（开发常用）
g++ main.cpp -o my_program

# 分步执行（调试时使用）
g++ -E main.cpp -o main.ii  # 预处理
g++ -S main.ii -o main.s    # 编译
g++ -c main.s -o main.o     # 汇编
g++ main.o -o my_program    # 链接
```

---

### **常见问题与调试技巧**
| **问题类型**         | **调试命令**                     | **解决方案**                     |
|---------------------|--------------------------------|--------------------------------|
| 预处理错误（如头文件丢失） | `g++ -E main.cpp`             | 检查头文件路径或安装缺失的库        |
| 编译错误（语法错误）    | `g++ -Wall -Wextra main.cpp`  | 根据错误信息修正代码逻辑           |
| 链接错误（未定义符号）  | `nm main.o \| grep function`  | 确保所有函数实现已编译并参与链接    |

---

### **工具链扩展**
- **Makefile**：自动化编译流程
  ```makefile
  CXX = g++
  TARGET = my_program
  OBJS = main.o utils.o

  $(TARGET): $(OBJS)
      $(CXX) -o $@ $^

  %.o: %.cpp
      $(CXX) -c $<
  ```
- **CMake**：跨平台构建工具
  ```cmake
  cmake_minimum_required(VERSION 3.10)
  project(MyProgram)
  add_executable(my_program main.cpp utils.cpp)
  ```

---

通过理解这些阶段，您可以更高效地排查编译问题并优化构建过程。
