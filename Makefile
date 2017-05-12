vpath %.h ./include
vpath %.c ./src

#目标文件的依赖关系
objects = main.o get_seed.o dow_data.o db_option.o err_warn.o pa_string.o

#生成最终目标文件pachong
pachong: $(objects)
	gcc -o pachong $(objects) -lcurl -lmysqlclient
	mv $(objects) ./bulid

$(objects):%.o:%.c
	gcc -c -g $< -Iinclude

.PHONY:clean
clean:
	-rm pachong ./bulid/*
