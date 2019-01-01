
# AT&T assembly 语法


### 寄存器名字:

`%eax`


### 源/目标 的顺序:

`movl %eax, %ebx`

源总是在左边, 目标总是在右边. 上面语句表示将 %eax 寄存器的值复制到 %ebx 中


### constant value/immediate value format:

必须在 constant/immediate value 之前添加 "$"

比如, 寄存器 eax 加载变量 booga 的地址:

`movl $_booga, %eax`

比如, 寄存器 ebx 加载常量 0xd00d:

`movl $0xd00d, %ebx`


### operator size specification:

必须在操作指令之后加上 **b**, **w**, 或者 **l** 代表目的寄存器作为一个 **byte**, **word**, 或者 **longword**.

eg:

`movw %ax, %bx`


