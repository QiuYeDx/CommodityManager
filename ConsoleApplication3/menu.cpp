#include"head.h"

void menu_vip()
{
	while(1)
	{
		system("cls");
		char choice;
		head_info(4);
		printf("\t\t\t\t��ѡ��\n");
		printf("\t\t\t\t1.ע���Ա\n");
		printf("\t\t\t\t2.��ʾ���л�Ա��Ϣ\n");
	   // printf("\t\t\t\t3.�޸Ļ�Ա�Ǽ�\n");
		printf("\t\t\t\t3.���һ�Ա\n");
		printf("\t\t\t\t0.����\n");
		printf("\t\t\t\t��ѡ������Ҫ���еĲ�����");
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
		else printf("\n\t\t\t\t[�������ʾѡ��]");
		
	}
}

void menu_managestatistics()
{
	while(1)
	{
	system("cls");
    head_info(2);
    printf("\t\t\t\t1.ע���µ�Ա���˺�\n");
    printf("\t\t\t\t2.ɾ��Ա����Ϣ\n");
    printf("\t\t\t\t3.չʾ����Ա����Ϣ\n");
    printf("\t\t\t\t4.����Ա������\n");
  //  printf("\t\t\t\t5.��ӹ���Ա\n");
    printf("\t\t\t\t0.������һ��\n");
    printf("\n\t\t\t\t��ѡ������Ҫ���еĲ�����");
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
		else printf("\n\t\t\t\t[�������ʾѡ��]");
		
	}
}

//����Ա������
void mainmenu_admin()
{
	while (1)
	{
		system("cls");
		head_info(1);
		printf("\t\t\t\t1.����Ա���˺�\n");
		printf("\t\t\t\t2.��Ŀ\n");
		printf("\t\t\t\t3.��Աϵͳ\n");
		printf("\t\t\t\t4.��Ʒ���ݹ���ϵͳ\n");
		printf("\t\t\t\t5.����\n");
		printf("\t\t\t\t6.������ָ��˺���Ϣ\n");
		printf("\t\t\t\t0.�˳�\n");
		printf("\n\t\t\t\t��ѡ������Ҫ���еĲ�����");
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
		else printf("\n\t\t\t\t[�������ʾѡ��]");
		
	}
}

//Ա��������
void mainmenu_employee()
{
	while (1)
	{
		system("cls");
		head_info(1);
		printf("\t\t\t\t1.�޸ĸ�����Ϣ\n");
		printf("\t\t\t\t2.����\n");
		printf("\t\t\t\t3.��Ʒ���ݹ���ϵͳ\n");
		printf("\t\t\t\t0.�˳�\n");
		printf("\n\t\t\t\t��ѡ������Ҫ���еĲ�����");
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
		else printf("\n\t\t\t\t[�������ʾѡ��]");
		
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

    if (0 == strcmp(info_login->idtype, "����Ա"))
        printf("\t\t\t\t�𾴵�%s,���ǹ���Ա:-)\n", info_login->name);
    if (0 == strcmp(info_login->idtype, "Ա��"))
        printf("\t\t\t\t�𾴵�%s,����Ա��:-)\n", info_login->name);
	printf("\n");
	switch(i)
	{
	case 1:printf("\t\t\t\t%-22s", "�����˵�         "); break;
	case 2:printf("\t\t\t\t%-22s", "�����˵�->����Ա���˺�"); break;
	case 3:printf("\t\t\t\t%-22s", "�����˵�->��Ŀ"); break;
	case 4:printf("\t\t\t\t%-22s", "�����˵�->��Աϵͳ"); break;
	case 5:printf("\t\t\t\t%-22s", "�����˵�->��Ʒ���ݹ���"); break;
	case 6:printf("\t\t\t\t%-22s", "�����˵�->����"); break;
	case 7:printf("\t\t\t\t%-22s", "�����˵�->�޸ĸ�����Ϣ"); break;
	case 8:printf("\t\t\t\t%-22s", "�����˵�->������ָ��˺���Ϣ"); break;

	}
    printf("\t\t\t\t��¼����:%s", str);
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
		printf("\n\t\t\t\t1.�鿴�������ۼ�¼\n");
		printf("\t\t\t\t2.�����������ۼ�¼\n");
		printf("\t\t\t\t3.��ѯ���ۼ�¼\n");
		printf("\t\t\t\t0.����\n");
		printf("\n\t\t\t\t��ѡ������Ҫ���еĲ�����");
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
        else printf("\n\t\t\t\t[�������ʾѡ��]");
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
			printf("\n\t\t\t\t��һ�α���ʱ����%s\n\n", time);
		else
			printf("\n\t\t\t\t[��ǰ�ޱ���]\n\n");
		fclose(fp);
		printf("\t\t\t\t1.���������˺���Ϣ\n");
		printf("\t\t\t\t2.�ָ������˺���Ϣ\n");
		printf("\t\t\t\t0.�˳�\n");
		printf("\n\t\t\t\t��ѡ������Ҫ���еĲ�����");
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
		else printf("\n\t\t\t\t[�������ʾѡ��]");
	}
}