#include"head.h"
MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

int main()
{
    system("color 3F");
	

	//_getch();
    int login_status = login();
    
	//初始化
	{
		//初始化连接环境
		if (NULL != mysql_init(&mysql)){}
			//printf("------系统连接成功------\n");
		else
		{
			//printf("\a------系统连接失败------\n");
			return -1;
		}

		//连接mysql服务器(localhost)
		if (!mysql_real_connect(&mysql, HOST, USERNAME, PASSWORD, DBNAME, 3306, NULL, 0))
		{
			//printf("\a------数据库连接失败------\n");
			return -1;
		}
		else
			//printf("------数据库连接成功------\n");

		//设置查询字符集
		mysql_query(&mysql, "set names gbk");
	}

    while (1)
    {
        if (1 == login_status)
        {	
            gotoMainmenu();	
        }
    }
    return 0;
}

void exit_program()
{
	//结束
	{
		//释放结果集
		mysql_free_result(res);
		//关闭mysql实例
		mysql_close(&mysql);
		//printf("\n------系统成功退出------\n");
	}

	exit(0);
}