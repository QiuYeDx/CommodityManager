#include"head.h"
MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

int main()
{
    system("color 3F");
	

	//_getch();
    int login_status = login();
    
	//��ʼ��
	{
		//��ʼ�����ӻ���
		if (NULL != mysql_init(&mysql)){}
			//printf("------ϵͳ���ӳɹ�------\n");
		else
		{
			//printf("\a------ϵͳ����ʧ��------\n");
			return -1;
		}

		//����mysql������(localhost)
		if (!mysql_real_connect(&mysql, HOST, USERNAME, PASSWORD, DBNAME, 3306, NULL, 0))
		{
			//printf("\a------���ݿ�����ʧ��------\n");
			return -1;
		}
		else
			//printf("------���ݿ����ӳɹ�------\n");

		//���ò�ѯ�ַ���
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
	//����
	{
		//�ͷŽ����
		mysql_free_result(res);
		//�ر�mysqlʵ��
		mysql_close(&mysql);
		//printf("\n------ϵͳ�ɹ��˳�------\n");
	}

	exit(0);
}