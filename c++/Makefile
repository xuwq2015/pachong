vpath %.h ./include
vpath %.cpp ./src

objects = main.o pcurloperate.o dboperate.o err_warn.o

CC = g++
CFLAGES = -g -Wall

#生成最终目标文件pachong
pachong: $(objects)
	$(CC) -o pachong $(objects) -lcurl -lmysqlclient
	mv $(objects) ./bulid
	
$(objects): %.o: %.cpp
	$(CC) -c $(CFLAGES) $< -Iinclude -o $@

.PHONY:clean
clean:
	-rm pachong ./bulid/*
