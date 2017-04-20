vpath %.h ./include
vpath %.c ./src

#目标文件的依赖关系
objects = main.o get_content.o extract_connection.o

#生成最终目标文件pachong
pachong: $(objects)
	gcc -o pachong $(objects) -lcurl
	mv $(objects) ./bulid

$(objects):%.o:%.c
	gcc -c $< -Iinclude

.PHONY:clean
clean:
	-rm pachong ./bulid/* ./cache/*

.PHONY:cache
cache:
	-rm ./cache/*
