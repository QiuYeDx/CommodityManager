#include"head.h"

void menu_vip()
{
	while(1)
	{
		system("cls");
		char choice;
		head_info(4);
		printf("\t\t\t\t请选择：\n");
		printf("\t\t\t\t1.注册会员\n");
		printf("\t\t\t\t2.显示所有会员信息\n");
	   // printf("\t\t\t\t3.修改会员星级\n");
		printf("\t\t\t\t3.查找会员\n");
		printf("\t\t\t\t0.返回\n");
		printf("\t\t\t\t请选择你需要进行的操作：");
		scanf("%c", &choice);
		if ('1' == choice || '2' == choice || '3' == choice || '4' == choice || '5' == choice || '0' == choice)
		{
			switch (choice)
			{
			case '1':addv(); break;
			case '2':showv(); break;
		  //  case 3:changev(); break;
			case '3':searchv(); break;
			case '0':gotoMainmenu(); break;
			}
			break;
		}
		else printf("\n\t\t\t\t[请根据提示选择]");
		
	}
}

void menu_managestatistics()
{
	while(1)
	{
	system("cls");
    head_info(2);
    printf("\t\t\t\t1.注册新的员工账号\n");
    printf("\t\t\t\t2.删除员工信息\n");
    printf("\t\t\t\t3.展示所有员工信息\n");
    printf("\t\t\t\t4.重置员工密码\n");
  //  printf("\t\t\t\t5.添加管理员\n");
    printf("\t\t\t\t0.返回上一级\n");
    printf("\n\t\t\t\t请选择你需要进行的操作：");
    char choice;
    scanf("%c", &choice);
   
	if ('1' == choice || '2' == choice || '3' == choice || '4' == choice || '0' == choice)
	{
		switch (choice)
		{
		case '1':registerUser(1); break;
		case '2':deleteStatistics_account(); break;
		case '3':showStatistics_account(); break;
		case '4':resetPassword_admin(); break;
		case '0':mainmenu_admin(); break;
		}
		break;
		}
		else printf("\n\t\t\t\t[请根据提示选择]");
		
	}
}

//管理员主界面
void mainmenu_admin()
{
	while (1)
	{
		system("cls");
		head_info(1);
		printf("\t\t\t\t1.管理员工账号\n");
		printf("\t\t\t\t2.账目\n");
		printf("\t\t\t\t3.会员系统\n");
		printf("\t\t\t\t4.商品数据管理系统\n");
		printf("\t\t\t\t5.结账\n");
		printf("\t\t\t\t6.备份与恢复账号信息\n");
		printf("\t\t\t\t0.退出\n");
		printf("\n\t\t\t\t请选择你需要进行的操作：");
		char choice;
		scanf("%c", &choice);
		
		if ('1' == choice || '2' == choice || '3' == choice || '4' == choice || '5' == choice || '6' == choice || '0' == choice)
		{
			switch (choice)
			{
			case '1':menu_managestatistics(); break;
			case '2': menu_record(); break;
			case '3':menu_vip(); break;
			case '4':database_main(); break;
			case '5':sell(); break;
			case '6':menu_backup(); break;
			case '0':exit_program(); break;
			}
			break;
		}
		else printf("\n\t\t\t\t[请根据提示选择]");
		
	}
}

//员工主界面
void mainmenu_employee()
{
	while (1)
	{
		system("cls");
		head_info(1);
		printf("\t\t\t\t1.修改个人信息\n");
		printf("\t\t\t\t2.结账\n");
		printf("\t\t\t\t3.商品数据管理系统\n");
		printf("\t\t\t\t0.退出\n");
		printf("\n\t\t\t\t请选择你需要进行的操作：");
		char choice;
		scanf("%c", &choice);
		
		if ('1' == choice || '2' == choice || '3' == choice || '0' == choice)
		{
		switch (choice)
		{
		case '1':changeStatistics_user(); break;
		case '2':sell(); break;
		case '3':database_main(); break;
		case '0':exit_program(); break;
		}
		break;
		}
		else printf("\n\t\t\t\t[请根据提示选择]");
		
	}
}

void head_info(int i)
{
	
	printf("\n\n\n");
    char str[30];
    time_t t;
    struct tm* lt;
    t = time(NULL);
    lt = localtime(&t);
    strftime(str, 30, "%Y-%m-%d", lt);

    if (0 == strcmp(info_login->idtype, "管理员"))
        printf("\t\t\t\t尊敬的%s,你是管理员:-)\n", info_login->name);
    if (0 == strcmp(info_login->idtype, "员工"))
        printf("\t\t\t\t尊敬的%s,你是员工:-)\n", info_login->name);
	printf("\n");
	switch(i)
	{
	case 1:printf("\t\t\t\t%-22s", "·主菜单         "); break;
	case 2:printf("\t\t\t\t%-22s", "·主菜单->管理员工账号"); break;
	case 3:printf("\t\t\t\t%-22s", "·主菜单->账目"); break;
	case 4:printf("\t\t\t\t%-22s", "·主菜单->会员系统"); break;
	case 5:printf("\t\t\t\t%-22s", "·主菜单->商品数据管理"); break;
	case 6:printf("\t\t\t\t%-22s", "·主菜单->结账"); break;
	case 7:printf("\t\t\t\t%-22s", "·主菜单->修改个人信息"); break;
	case 8:printf("\t\t\t\t%-22s", "·主菜单->备份与恢复账号信息"); break;

	}
    printf("\t\t\t\t登录日期:%s", str);
    printf("\n\n\t\t\t\t");
	for (int i = 0; i < 33; i++) 
		printf("~~");
	printf("~");
	printf("\n\n");

}

void menu_record()
{
	system("cls");
	head_info(3);
    while (1)
    {
		printf("\n\t\t\t\t1.查看所有销售记录\n");
		printf("\t\t\t\t2.导出所有销售记录\n");
		printf("\t\t\t\t3.查询销售记录\n");
		printf("\t\t\t\t0.返回\n");
		printf("\n\t\t\t\t请选择你需要进行的操作：");
        char choice;
		getchar();
        scanf("%c", &choice);
		
        system("cls");
        if ('1' == choice || '2' == choice || '3' == choice ||'0' == choice)
        {
            switch (choice)
            {
            case '1':showRecord(); break;
            case '2':createExcel(); break;
            case '3':searchRecord(); break;
            case '0':gotoMainmenu(); break;
            }
            break;
        }
        else printf("\n\t\t\t\t[请根据提示选择]");
    }
}

void menu_backup()
{
	while (1)
	{
		system("cls");
		head_info(8);
		FILE*fp = fopen("C:\\mysql_backup\\b_time.bin", "a+");
		char time[25];
		if (1 == fscanf(fp, "%s", time))
			printf("\n\t\t\t\t上一次备份时间是%s\n\n", time);
		else
			printf("\n\t\t\t\t[当前无备份]\n\n");
		fclose(fp);
		printf("\t\t\t\t1.备份所有账号信息\n");
		printf("\t\t\t\t2.恢复所有账号信息\n");
		printf("\t\t\t\t0.退出\n");
		printf("\n\t\t\t\t请选择你需要进行的操作：");
		char choice;
		scanf("%c", &choice);
		system("cls");
		if ('1' == choice || '2' == choice || '0' == choice)
		{
			switch (choice)
			{
			case '1':backup_all(); break;
			case '2':recovery_all(); break;
			case '0':gotoMainmenu(); break;
			}
			break;
		}
		else printf("\n\t\t\t\t[请根据提示选择]");
	}
}