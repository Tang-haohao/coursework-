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
	char register_account[30];	  //ע���ߵ��˺�
	char register_password[10];  //ע���ߵ����� 
 	struct reg_Account *next;   //ָ���� 
 	int borrow[5];             //�����id
	int Borrow;		  		  //��¼���ĵ��鱾�� 
};

typedef struct reg_Account Account;
typedef Account *account;

//��������
int display_book(); //��������ͼ��
void borrow(); //����ģ��
void account_saving(Account A); //�洢�˺�ģ�� 
account load_account(); //��ȡ�洢�˺���Ϣ���ļ� 
void logon(); //�����˻�ģ�� 
int whether_register(); //�ж��Ƿ�ע��
account loging(); //�û���¼

#endif 
 
