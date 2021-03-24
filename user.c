#include "user.h"
#include <string.h>

//变量域 
extern pbook bookhead;
extern account logger;
char register_account[30]="",register_password[10]="";
char librarian_account[]={"librarian"};//图书管理员的账号
char librarian_password[]={"librarian"};//图书管理员的密码 
char log_account[30],log_password[10];
Account accounts;

int display_book()   //总览所有图书 
{
	system("cls");
	pbook book_head,pdisplay;
	int total=0;
	book_head=bookhead;
	printf("**************************图书总览*****************************\n");
	printf("---------------------------------------------------------------\n");
	printf("登录号        书名        作者名         出版时间          数量\n");
	printf("---------------------------------------------------------------\n");
	if(book_head==NULL)
	{
		printf("书库暂时没有书哦~赶快去添加几本吧^_^\n");
		system("pause");
		return 0;
	}
	pdisplay=book_head;
	while(pdisplay!=NULL)
	{
		printf("%d%14s%14s         %.2f%12d\n",pdisplay->id,pdisplay->title,pdisplay->authors,pdisplay->year,pdisplay->copies);
		total+=pdisplay->copies;//图书总数 
		pdisplay=pdisplay->nextbook;
	}
	printf("图书总量为：%d\n",total);
	system("pause");
	return 0;
}
//借阅模块 
void borrow()
{
	char ny;
	int d=0; 
	FILE *afile;
	pbook book_head,pfind;
	book_head = bookhead;
	unsigned int iD;
	if(logger->Borrow<5) //判断用户借阅书籍数是否已到达上限 
	{
		system("cls");
		while(1)
		{
			printf("请输入您要借阅图书的ID：\n");
			scanf("%u", &iD); 
			printf("正在查询....\n");
			pfind=book_head;
			printf("**************************图书总览*****************************\n");
			printf("---------------------------------------------------------------\n");
			printf("登录号        书名        作者名         出版时间          数量\n");
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
				printf("书库中不存在此书，请输入正确的id"); 
				break; 
			}
			else if(pfind->copies>0)
			{
				printf("您是否需要借阅此书：'Y' or 'N' \n");
				ny = getch();
				if(ny == 'Y') //让用户选择是否借阅 
				{
					pfind->copies=pfind->copies-1; 
					logger->borrow[logger->Borrow]=iD;
					logger->Borrow=logger->Borrow+1;
					printf("借阅成功，按任意键返回。。。\n");
					store_books();
					load_books();
					getch();
					break;
				}
				else 
				{
					if(ny == 'N')
					{
					printf("借阅取消，按任意键返回。。。\n");
					getch();
					}
					else 
					{
						printf("输入有错，按任意键返回。。。\n");  
						getch();
					}	
					break;
				}
			}
			else 
			{
				printf("此书数量为零，请借阅其他书籍");
				break; 
			}
		}
	}
	else{
		printf("您借阅的书籍数以达到上限，请先归还已借图书"); 
	}
}
//存储账号模块    
void account_saving(Account A)   //将用户注册账号及信息写入文件 
{
	account a = &A;
	FILE *file;    //文件指针 
	file=fopen("account_file","ab");   //以追加的方式打开文件（二进制文件）account_file 
	if(file==NULL)
	{
		printf("file can not be opened");
	}
	if(fwrite(a,sizeof(Account),1,file)!=1)   //将指针a所指向的内容写到二进制文件中 
	{
		printf("something wrong in writing");
	}
	fclose(file);    //关闭文件  
} 
//读取存储账号信息的文件 
account load_account()      //将二进制文件的内容读入到链表中，返回链表头指针 
{
	FILE *file;       //文件指针 
	int i=0;
	account account_head=NULL;
	account a2,a,ar=NULL;
	file=fopen("account_file","a");       //如果mybook文件还不存在，则新建一个
	fclose(file);
 	file=fopen("account_file","ab+");     //用读写的方式打开二进制文件 
	if(file==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(file))        //判断读取标志是否已经到达文件的末尾 
	{
	   i++;
	   	a=(account)malloc(sizeof(Account)); //用malloc给a申请一段空间 
	   fread(a,sizeof(Account),1,file);     //将file指向的文件的内容读入指针a中 
	   if(i==1)
	   {
	      account_head=a;
	      a2=a;
	    }
	    else             //创建一个链表 
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
    fclose(file);    //关闭文件 
    return account_head;   //返回头指针 
}

//创建账户模块 
void logon()
{
	Account reg_a;
	account pa = load_account();  //返回头指针 
	int x = 0, y = 0;
 	//清空屏幕 
 	system("cls");
	while(1)
 	{
 		//创建用户名
 		printf("\t\t请输入用户名[不能大于12个字符]：");
 		scanf("%s",register_account);
  		
 		//判断用户名是否正确 
 		if(strlen(register_account)<=12)		
 		{
 			if(strcmp(register_account,librarian_account)==0){
 				printf("\n\t\t用户名已存在\n");
 				continue;
			 }
 			while(pa!=NULL){
 				if(strcmp(pa->register_account,register_account)==0){
 					printf("\n\t\t用户名已存在\n");
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
    			for (x=0; x<30; ++x)	//将register_account数组中的值赋给reg_a.register_account数组 
    			{
        			reg_a.register_account[x] = register_account[x];
    			}	  				
 				//创建用户密码
 				printf("\n\t\t请输入密码[密码长度为六位]：");
 				scanf("%s",register_password);
  
 				//判断用户密码格式 
 				if(strlen(register_password)==6)
 				{
    				for (x=0; x<10; ++x)	//将register_password数组中的值赋给reg_a.register_password数组 
    				{
        				reg_a.register_password[x] = register_password[x];
    				}		 					
 					printf("\n\n\t\t注册成功，您的用户名是%s,密码是%s\n\n",register_account,register_password);
 					break;
 				}
 				else
 				{
 					printf("\n\t\t密码的长度为%d，请重新输入\n",strlen(register_password));
 				}
 			}
 			break;
 		}
 		else
 		{
 			printf("\n\t\t用户名的长度为%d，请重新输入\n\n",strlen(register_account));
 		}
 	}
	account_saving(reg_a);
}
  
//判断是否注册
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
  
//用户登录
account loging()
{
 	int x , y = 0;
 	account log_head = load_account() , current_account = NULL;
 	system("pause");
 	system("cls");
	if(whether_register()==0){
		printf("您还未注册,请先创建账号\n");
		return NULL;
	}
	
 	printf("\n\n\t\t\t欢迎使用图书馆登录系统\n\n");
 	//三次登录验证
 	for(x=1;x<=3;x++)
 	{
 		printf("\t\t请输入用户名:");
 		scanf("%s",log_account);
 		printf("\n\t\t请输入密 码:");
 		scanf("%s",log_password);
 		if(strcmp(log_account,librarian_account)==0&&strcmp(log_password,librarian_account)==0){
			printf("\t\t成功以图书馆管理员的身份登入\n"); //以图书管理员的身份登入
			current_account=&accounts;
			strcpy(current_account->register_account,"librarian");
			break; 
 		} 
 		while(log_head!=NULL)
 		{
 			if(strcmp(log_head->register_account,log_account)==0&&strcmp(log_head->register_password,log_password)==0)	
 			{
				printf("\n\n\t\t登录成功，欢迎使用腾讯QQ系统\n\n");
				current_account = log_head; 
 				y = 1; 
 				break;
 			}
 		log_head = log_head->next;
 		}
 		if(y==0)
 		{
 			printf("\n\n\t\t登录失败，请重新登录，您还有%d次机会\n\n",3-x);
 		}
 		if(y==1)
		{
 			y = 0;
			break;
 		}
 	}
  	return current_account;
}
//还书模块
void return_book(){
	pbook rebook,rebooks;
	FILE *afile;
	rebook=bookhead;
	int i;
	unsigned int return_id; 
	if(logger->Borrow!=0)
	{	
		printf("您借阅的书籍:"); 
		printf("**************************图书总览*****************************\n");
		printf("---------------------------------------------------------------\n");
		printf("登录号        书名        作者名         出版时间          数量\n");
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
		printf("\n请输入所要归还书籍的ID:\n");
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
						printf("还书成功\n");
						store_books();
						load_books();
					}
				}
			}
			rebooks=rebooks->nextbook;
		}
	}
	else{
		printf("当前用户没有借阅书籍\n");
	}
}
void terminate()       //退出软件 
{
	int i;
	system("cls");
	setxy(20,10);
	printf("-----------------------");
	setxy(20,12);
	printf("|   您确定要退出吗？  |");
	setxy(20,14);
	printf("| 1.确定     2.取消   |");
	setxy(20,16);
	printf("-----------------------\n");
	while(1)
	{
		scanf("%d",&i);         //输入选择 
		switch(i)
		{
			case 1:
			setxy(20,18);
			printf("已安全退出软件\n");
			setxy(20,20);
			printf("谢谢使用！");
			exit(0);  
			break; //结束程序 
			case 2:
			Mainmenu(); //重新进入主菜单 
			break;    
			default :break;
		}
	}
} 

