vpath %.h ./include
vpath %.c ./src

objects = main.o get_content.o

pachong: $(objects)
	gcc -o $(objects)

$(objects):%.o:%.c
	gcc -c $< -I./include
