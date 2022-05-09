# 定义变量
# add.c sub.c main.c 都是文件名 
src=$(wildcard ./*.c)
objs=$(patsubst %.c, %.o, $(src))
target=app
$(target):$(objs)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(objs)