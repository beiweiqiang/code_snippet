
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

必须在操作符之后加上 **b**, **w**, 或者 **l** 代表目的寄存器作为一个 **byte**, **word**, 或者 **longword**.

eg:

`movw %ax, %bx`


### referencing memory:

32位寻址:

`immed32(base_pointer, index_pointer, index_scale)`

地址的计算公式为:

`immed32 + base_pointer + index_pointer * index_scale`

注意, 不一定要全部元素都包含, 但是至少需要 `immed32` 或者 `base_pointer` 中的一个

eg:

- C 变量寻址:

`_booga`

前面的下划线 "\_", 对于汇编器来说是一个静态的全局的 C 变量.

- 寄存器地址寻址:

`(%eax)`

- 寄存器地址寻址, 加上一个偏移变量:

\_variable(%eax)


