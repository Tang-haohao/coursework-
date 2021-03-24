#include "user.h"
#include <string.h>

//������ 
extern pbook bookhead;
extern account logger;
char register_account[30]="",register_password[10]="";
char librarian_account[]={"librarian"};//ͼ�����Ա���˺�
char librarian_password[]={"librarian"};//ͼ�����Ա������ 
char log_account[30],log_password[10];
Account accounts;

int display_book()   //��������ͼ�� 
{
	system("cls");
	pbook book_head,pdisplay;
	int total=0;
	book_head=bookhead;
	printf("**************************ͼ������*****************************\n");
	printf("---------------------------------------------------------------\n");
	printf("��¼��        ����        ������         ����ʱ��          ����\n");
	printf("---------------------------------------------------------------\n");
	if(book_head==NULL)
	{
		printf("�����ʱû����Ŷ~�Ͽ�ȥ��Ӽ�����^_^\n");
		system("pause");
		return 0;
	}
	pdisplay=book_head;
	while(pdisplay!=NULL)
	{
		printf("%d%14s%14s         %.2f%12d\n",pdisplay->id,pdisplay->title,pdisplay->authors,pdisplay->year,pdisplay->copies);
		total+=pdisplay->copies;//ͼ������ 
		pdisplay=pdisplay->nextbook;
	}
	printf("ͼ������Ϊ��%d\n",total);
	system("pause");
	return 0;
}
//����ģ�� 
void borrow()
{
	char ny;
	int d=0; 
	FILE *afile;
	pbook book_head,pfind;
	book_head = bookhead;
	unsigned int iD;
	if(logger->Borrow<5) //�ж��û������鼮���Ƿ��ѵ������� 
	{
		system("cls");
		while(1)
		{
			printf("��������Ҫ����ͼ���ID��\n");
			scanf("%u", &iD); 
			printf("���ڲ�ѯ....\n");
			pfind=book_head;
			printf("**************************ͼ������*****************************\n");
			printf("---------------------------------------------------------------\n");
			printf("��¼��        ����        ������         ����ʱ��          ����\n");
			printf("---------------------------------------------------------------\n");
			while(pfind!=NULL)
			{
				if(pfind!=NULL&&pfind->id==iD)
				{
					printf("%d%14s%14s         %.2f%12d\n",pfind->id,pfind->title,pfind->authors,pfind->year,pfind->copies);
					break;  
				}
				pfind=pfind->nextbook;
			}	
			if(pfind==NULL)
			{
				printf("����в����ڴ��飬��������ȷ��id"); 
				break; 
			}
			else if(pfind->copies>0)
			{
				printf("���Ƿ���Ҫ���Ĵ��飺'Y' or 'N' \n");
				ny = getch();
				if(ny == 'Y') //���û�ѡ���Ƿ���� 
				{
					pfind->copies=pfind->copies-1; 
					logger->borrow[logger->Borrow]=iD;
					logger->Borrow=logger->Borrow+1;
					printf("���ĳɹ�������������ء�����\n");
					store_books();
					load_books();
					getch();
					break;
				}
				else 
				{
					if(ny == 'N')
					{
					printf("����ȡ��������������ء�����\n");
					getch();
					}
					else 
					{
						printf("�����д�����������ء�����\n");  
						getch();
					}	
					break;
				}
			}
			else 
			{
				printf("��������Ϊ�㣬����������鼮");
				break; 
			}
		}
	}
	else{
		printf("�����ĵ��鼮���Դﵽ���ޣ����ȹ黹�ѽ�ͼ��"); 
	}
}
//�洢�˺�ģ��    
void account_saving(Account A)   //���û�ע���˺ż���Ϣд���ļ� 
{
	account a = &A;
	FILE *file;    //�ļ�ָ�� 
	file=fopen("account_file","ab");   //��׷�ӵķ�ʽ���ļ����������ļ���account_file 
	if(file==NULL)
	{
		printf("file can not be opened");
	}
	if(fwrite(a,sizeof(Account),1,file)!=1)   //��ָ��a��ָ�������д���������ļ��� 
	{
		printf("something wrong in writing");
	}
	fclose(file);    //�ر��ļ�  
} 
//��ȡ�洢�˺���Ϣ���ļ� 
account load_account()      //���������ļ������ݶ��뵽�����У���������ͷָ�� 
{
	FILE *file;       //�ļ�ָ�� 
	int i=0;
	account account_head=NULL;
	account a2,a,ar=NULL;
	file=fopen("account_file","a");       //���mybook�ļ��������ڣ����½�һ��
	fclose(file);
 	file=fopen("account_file","ab+");     //�ö�д�ķ�ʽ�򿪶������ļ� 
	if(file==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(file))        //�ж϶�ȡ��־�Ƿ��Ѿ������ļ���ĩβ 
	{
	   i++;
	   	a=(account)malloc(sizeof(Account)); //��malloc��a����һ�οռ� 
	   fread(a,sizeof(Account),1,file);     //��fileָ����ļ������ݶ���ָ��a�� 
	   if(i==1)
	   {
	      account_head=a;
	      a2=a;
	    }
	    else             //����һ������ 
	    {
	    	ar=a2;
	    	a2->next=a;
	    	a2=a;
		}
    }
    if(ar!=NULL)
       ar->next=NULL;
    else
       account_head=NULL;
    fclose(file);    //�ر��ļ� 
    return account_head;   //����ͷָ�� 
}

//�����˻�ģ�� 
void logon()
{
	Account reg_a;
	account pa = load_account();  //����ͷָ�� 
	int x = 0, y = 0;
 	//�����Ļ 
 	system("cls");
	while(1)
 	{
 		//�����û���
 		printf("\t\t�������û���[���ܴ���12���ַ�]��");
 		scanf("%s",register_account);
  		
 		//�ж��û����Ƿ���ȷ 
 		if(strlen(register_account)<=12)		
 		{
 			if(strcmp(register_account,librarian_account)==0){
 				printf("\n\t\t�û����Ѵ���\n");
 				continue;
			 }
 			while(pa!=NULL){
 				if(strcmp(pa->register_account,register_account)==0){
 					printf("\n\t\t�û����Ѵ���\n");
 					pa = load_account();
 					y=1;
					break; 
				 }
				 pa = pa->next;
			 }
			if(y==1){
				y=0;
				continue;
			} 
 			while(1)
 			{
    			for (x=0; x<30; ++x)	//��register_account�����е�ֵ����reg_a.register_account���� 
    			{
        			reg_a.register_account[x] = register_account[x];
    			}	  				
 				//�����û�����
 				printf("\n\t\t����������[���볤��Ϊ��λ]��");
 				scanf("%s",register_password);
  
 				//�ж��û������ʽ 
 				if(strlen(register_password)==6)
 				{
    				for (x=0; x<10; ++x)	//��register_password�����е�ֵ����reg_a.register_password���� 
    				{
        				reg_a.register_password[x] = register_password[x];
    				}		 					
 					printf("\n\n\t\tע��ɹ��������û�����%s,������%s\n\n",register_account,register_password);
 					break;
 				}
 				else
 				{
 					printf("\n\t\t����ĳ���Ϊ%d������������\n",strlen(register_password));
 				}
 			}
 			break;
 		}
 		else
 		{
 			printf("\n\t\t�û����ĳ���Ϊ%d������������\n\n",strlen(register_account));
 		}
 	}
	account_saving(reg_a);
}
  
//�ж��Ƿ�ע��
int whether_register()
{
 	account pa = load_account();
 	if(pa==NULL)
 	{
 		return 0;
 	}
 	else
 	{
 		return 1;
 	}
}
  
//�û���¼
account loging()
{
 	int x , y = 0;
 	account log_head = load_account() , current_account = NULL;
 	system("pause");
 	system("cls");
	if(whether_register()==0){
		printf("����δע��,���ȴ����˺�\n");
		return NULL;
	}
	
 	printf("\n\n\t\t\t��ӭʹ��ͼ��ݵ�¼ϵͳ\n\n");
 	//���ε�¼��֤
 	for(x=1;x<=3;x++)
 	{
 		printf("\t\t�������û���:");
 		scanf("%s",log_account);
 		printf("\n\t\t�������� ��:");
 		scanf("%s",log_password);
 		if(strcmp(log_account,librarian_account)==0&&strcmp(log_password,librarian_account)==0){
			printf("\t\t�ɹ���ͼ��ݹ���Ա����ݵ���\n"); //��ͼ�����Ա����ݵ���
			current_account=&accounts;
			strcpy(current_account->register_account,"librarian");
			break; 
 		} 
 		while(log_head!=NULL)
 		{
 			if(strcmp(log_head->register_account,log_account)==0&&strcmp(log_head->register_password,log_password)==0)	
 			{
				printf("\n\n\t\t��¼�ɹ�����ӭʹ����ѶQQϵͳ\n\n");
				current_account = log_head; 
 				y = 1; 
 				break;
 			}
 		log_head = log_head->next;
 		}
 		if(y==0)
 		{
 			printf("\n\n\t\t��¼ʧ�ܣ������µ�¼��������%d�λ���\n\n",3-x);
 		}
 		if(y==1)
		{
 			y = 0;
			break;
 		}
 	}
  	return current_account;
}
//����ģ��
void return_book(){
	pbook rebook,rebooks;
	FILE *afile;
	rebook=bookhead;
	int i;
	unsigned int return_id; 
	if(logger->Borrow!=0)
	{	
		printf("�����ĵ��鼮:"); 
		printf("**************************ͼ������*****************************\n");
		printf("---------------------------------------------------------------\n");
		printf("��¼��        ����        ������         ����ʱ��          ����\n");
		printf("---------------------------------------------------------------\n");	
		for(i=0;i<logger->Borrow;i=i+1)
		{
			while(rebook!=NULL)
			{
				if(rebook!=NULL&&rebook->id==logger->borrow[i])
				{
					printf("%d%14s%14s         %.2f%12d\n",rebook->id,rebook->title,rebook->authors,rebook->year,rebook->copies);
				}
				rebook=rebook->nextbook;
			}
		}
		printf("\n��������Ҫ�黹�鼮��ID:\n");
		scanf("%u",&return_id);
		rebooks=bookhead;
		while(rebooks!=NULL)
		{
			if(rebooks!=NULL&&rebooks->id==return_id)
			{
				for(i=0;i<logger->Borrow;i=i+1){
					if(logger->borrow[i]==return_id){
						logger->borrow[i]=0;
						rebooks->copies=rebooks->copies+1;
						logger->Borrow=logger->Borrow-1;
						printf("����ɹ�\n");
						store_books();
						load_books();
					}
				}
			}
			rebooks=rebooks->nextbook;
		}
	}
	else{
		printf("��ǰ�û�û�н����鼮\n");
	}
}
void terminate()       //�˳���� 
{
	int i;
	system("cls");
	setxy(20,10);
	printf("-----------------------");
	setxy(20,12);
	printf("|   ��ȷ��Ҫ�˳���  |");
	setxy(20,14);
	printf("| 1.ȷ��     2.ȡ��   |");
	setxy(20,16);
	printf("-----------------------\n");
	while(1)
	{
		scanf("%d",&i);         //����ѡ�� 
		switch(i)
		{
			case 1:
			setxy(20,18);
			printf("�Ѱ�ȫ�˳����\n");
			setxy(20,20);
			printf("ллʹ�ã�");
			exit(0);  
			break; //�������� 
			case 2:
			Mainmenu(); //���½������˵� 
			break;    
			default :break;
		}
	}
} 

