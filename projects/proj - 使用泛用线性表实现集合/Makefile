# 指定编译器
CC=gcc

# 指定编译参数
CFLAGS=-I.

# 指定需要关注的头文件，如果这些头文件发生修改也要重新编译
DEPS = LinkedList.h

# 根据.h与.c文件编译所有.o文件
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# 编译生成最终可执行程序main然后
# 清理所有中间过程生成的目标文件
main: LinkedList.o
	$(CC) main.c LinkedList.o -o  main
	rm *.o
	