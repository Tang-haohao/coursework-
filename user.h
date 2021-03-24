#ifndef USER__H 
#define USER__H

#include"book_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

struct reg_Account               
{ 
	char register_account[30];	  //注册者的账号
	char register_password[10];  //注册者的密码 
 	struct reg_Account *next;   //指针域 
 	int borrow[5];             //借书的id
	int Borrow;		  		  //记录借阅的书本数 
};

typedef struct reg_Account Account;
typedef Account *account;

//函数定义
int display_book(); //总览所有图书
void borrow(); //借阅模块
void account_saving(Account A); //存储账号模块 
account load_account(); //读取存储账号信息的文件 
void logon(); //创建账户模块 
int whether_register(); //判断是否注册
account loging(); //用户登录

#endif 
 
