vpath %.h ./include
vpath %.cpp ./src

SRC = main.cpp
#目标文件的依赖关系
objects = $($SRC:.cpp=.o)

#生成最终目标文件pachong
pachong: $(objects)
	g++ -o pachong $(objects) -lcurl -lmysqlclient
	mv $(objects) ./bulid

$(objects):%.o:%.cpp
	g++ -c -g $< -Iinclude

.PHONY:clean
clean:
	-rm pachong ./bulid/*
