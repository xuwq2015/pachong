#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <get_content.h>

int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		printf("参数输入错误，请重新输入\n");
		exit(0);
	}

	int ret = pa_start(argv[1]);
	return 0;
}
