#include"head.h"
char str_now_time_t[25];

LNode createList_record()
{
    LNode pHead = (LNode)malloc(LEN1);
    pHead->next = NULL;
    FILE* fp = fopen(file_temp_record, "ab+");
    fclose(fp);
    fp = fopen(file_temp_record, "rb");
    LNode cur = pHead;
    while (1)
    {
        LNode temp = (LNode)malloc(LEN1);
        if (!temp) exit(-1);
        if (!fread(temp, LEN1, 1, fp))
        {
            free(temp);
            break;
        }
        cur->next = temp;
        cur = temp;
        cur->next = NULL;
    }
   
    fclose(fp);
    return pHead;
}

void addRecord(LNode Record)
{
	strcpy(Record->id, info_login->id);
	FILE* fp = fopen(file_temp_record, "ab+");
	fwrite(Record, LEN1, 1, fp);
	fclose(fp);
}

LNode searchRecord_vip(LNode head)
{
    char vip[15];
    while (1)
    {
        printf("\n\n\n\t\t\t请输入需要查询记录的会员账号：");
        scanf("%s", vip);
        LNode temp = head->next;
        int flag0 = 0;
	
        while (temp)
        {
            if (0 == strcmp(temp->vip, vip) )
            {
				if (2 != flag0)
					flag0 = 1;
				if (1 == flag0)
				{
					printf("\n\n\n\t\t\t+");
					for (int i = 0; i < 20; i++) printf("——");
					printf("+\n");

					printf("\t\t\t|   消费时间\t\t会员卡号\t收款员工\t 收款额\t    利润\t |\n");

					printf("\t\t\t+");
					for (int i = 0; i < 20; i++) printf("——");
					printf("+\n");
				}
				flag0 = 2;
				printf("\t\t\t| %-15s  \t%-12s\t%-9s\t%.2f\t    %.2f\t |\n", temp->time, temp->vip, temp->id, temp->receive, temp->profit);
            }
            temp = temp->next;
        }
		printf("\t\t\t+");
		for (int i = 0; i < 20; i++) printf("——");
		printf("+\n");
        if (0 == flag0)
        {
            printf("\n\t\t\t\t:-(  查无消费记录");
        }
        printf("\n\n\t\t\t(请按任意键返回...)");
        _getch();
        system("cls");
        menu_record();
    }
}

LNode searchRecord_date(LNode head)
{
	char date[15];
	while (1)
	{
		printf("\n\n\n\t\t\t请输入需要查询记录的日期（格式例：20200101）：");
		scanf("%s", date);
		LNode temp = head->next;
		
		int flag0 = 0;
		char t_date[9] = { 0 };
		while (temp)
		{
			for (int i = 0; i < 4; i++)    t_date[i] = temp->time[i];
			for (int i = 5; i < 7; i++)    t_date[i - 1] = temp->time[i];
			for (int i = 8; i < 10; i++)   t_date[i - 2] = temp->time[i];
			t_date[8] = '\0';

			if (0 == strcmp(t_date, date))
			{
				if(2 != flag0)
					flag0 = 1;
				if (1 == flag0)
				{
					printf("\n\n\n\t\t\t+");
					for (int i = 0; i < 20; i++) printf("——");
					printf("+\n");

					printf("\t\t\t|   消费时间\t\t会员卡号\t收款员工\t 收款额\t    利润\t |\n");

					printf("\t\t\t+");
					for (int i = 0; i < 20; i++) printf("——");
					printf("+\n");
				}
				flag0 = 2;
				printf("\t\t\t| %-15s  \t%-12s\t%-9s\t%.2f\t    %.2f\t |\n", temp->time, temp->vip, temp->id, temp->receive, temp->profit);
			}
			temp = temp->next;
		}
		printf("\t\t\t+");
		for (int i = 0; i < 20; i++) printf("——");
		printf("+\n");
		if (0 == flag0)
		{
			printf("\n\t\t\t\t:-(  查无消费记录");
		}
		printf("\n\n\t\t\t(请按任意键返回...)");
		_getch();
		system("cls");
		menu_record();
	}
}

void output(LNode head)
{
    LNode temp = head;
	
	printf("\n\n\n\t\t\t+");
	for (int i = 0; i < 20; i++) printf("——");
	printf("+\n");

    printf("\t\t\t|   消费时间\t\t会员卡号\t收款员工\t 收款额\t    利润\t |\n");

	printf("\t\t\t+");
	for (int i = 0; i < 20; i++) printf("——");
	printf("+\n");

    while (temp)
    {
        printf("\t\t\t| %-15s  \t%-12s\t%-9s\t%.2f\t    %.2f\t |\n", temp->time, temp->vip, temp->id, temp->receive, temp->profit);
        temp = temp->next;
    }
	printf("\t\t\t+");
	for (int i = 0; i < 20; i++) printf("——");
	printf("+\n");
    printf("\n\n\t\t\t请按任意键返回...");
    _getch();
    system("cls");
    menu_record();
}

void searchRecord()
{
    LNode head = createList_record();
    LNode temp = head->next;
    int choice;
    while (1)
    {
        printf("\n\n\n\t\t\t\t请选择查找的方式 \n\t\t\t\t（1）日期\n\t\t\t\t（2）会员账号\n\t\t\t\t（0）返回\n\t\t\t\t请输入你的选择：");
        scanf("%d", &choice);
        system("cls");
        if (1 == choice || 2 == choice)
        {
            switch (choice)
            {
            case 1: searchRecord_date(head); break;
            case 2: searchRecord_vip(head); break;
			case 0:gotoMainmenu(); break;
            }
            output(head);
            break;
        }
        else printf("\t\t\t\t请选择 1 或 2 ！");
    }
	gotoMainmenu();
}

void showRecord()
{
    LNode head = createList_record();
    LNode temp = head->next;
    output(temp);
}

void createExcel()
{
    LNode head = createList_record();
    LNode temp = head->next;
    FILE*fp = fopen("C:\\Users\\86187\\desktop\\record.xls", "w");
    fprintf(fp, "消费时间\t会员卡号\t收款员工\t收款额\t单笔利润\n");
    while (temp)
    {
        fprintf(fp,"%s\t%s\t%s\t%.02lf\t%.02lf\n", temp->time, temp->vip, temp->id, temp->receive, temp->profit);
        temp = temp->next;
    }
    fclose(fp);
    printf("已导出为 record.xls ，请查看！");
    Sleep(300);
    system("cls");
    menu_record();
}

void backup_all()
{
	FILE*fp = fopen("C:\\mysql_backup\\b_time.bin", "r");
	char time[25];
	if (fscanf(fp, "%s", time))
	{
		remove("C:\\mysql_backup\\backup\\account.bin");
		remove("C:\\mysql_backup\\backup\\vip.bin");
		remove("C:\\mysql_backup\\backup\\record.bin");

	}
	fclose(fp);
	system("copy C:\\mysql_backup\\account.bin C:\\mysql_backup\\backup ");
	system("copy C:\\mysql_backup\\record.bin  C:\\mysql_backup\\backup");
	system("copy C:\\mysql_backup\\vip.bin  C:\\mysql_backup\\backup");
	printf("\n\t\t\t\t[备份成功！]");
	fp = fopen("C:\\mysql_backup\\b_time.bin", "w");
	Gettime_t();
	fprintf(fp, "%s", str_now_time_t);
	fclose(fp);
	Sleep(900);
	gotoMainmenu();
}


void Gettime_t()
{
	time_t t;
	struct tm* lt;
	t = time(NULL);
	lt = localtime(&t);
	strftime(str_now_time_t, 25, "%Y年%m月%d日%H:%M:%S", lt);
}

void recovery_all()
{
	FILE*fp = fopen("C:\\mysql_backup\\b_time.bin","r");
	char time[25];
	if (fscanf(fp, "%s", time))
	{
		remove("C:\\mysql_backup\\account.bin");
		remove("C:\\mysql_backup\\vip.bin");
		remove("C:\\mysql_backup\\record.bin");
		system("copy C:\\mysql_backup\\backup\\account.bin C:\\mysql_backup ");
		system("copy C:\\mysql_backup\\backup\\record.bin  C:\\mysql_backup");
		system("copy C:\\mysql_backup\\backup\\vip.bin C:\\mysql_backup");
		printf("\n\t\t\t\t[恢复成功]");
	}
	else
		printf("\n\t\t\t\t[查无备份！]");
	fclose(fp);
	Sleep(900);
	gotoMainmenu();
}