#include <stdio.h>
#include <stdlib.h>
#include <dboperate.h>
#include <dboperate.h>
#include <pcurloperate.h>
#include <list>
#include <string>
#include <iostream>
#include <err_warn.h>
#include <common.h>

using namespace std;

//PaErrWarn paErrWarn;

int main(int argc, char **argv) {
	
	list<string> seed_list;

	//paErrWarn = new PaErrWarn;
	PcurlOperate pcurlOperate;
	DbOperate dbOperate;
	
	list<string>::iterator i;
	dbOperate.pa_seed_inquire(&seed_list);
	for(i = seed_list.begin(); i != seed_list.end(); ++i) {
		cout << *i << endl;
		string str = *i;
		if((pcurlOperate.down((char *)str.data())) == -1) {
			char file_name[PA_BUF_SIZE] = {'\0'};
			pcurlOperate.get_down_content(file_name);
			cout<<"文件:"<<file_name<<endl;
			cout<<pcurlOperate.err_str<<endl;
			break;
		}
		char file_name[PA_BUF_SIZE] = {'\0'};
		pcurlOperate.get_down_content(file_name);
		cout<<"文件:"<<file_name<<endl;
	}
	
	return 0;
}