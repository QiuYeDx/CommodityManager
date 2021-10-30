#include "head.h"
char zl[200] = "select * from goods_v1.goods";
char zl_get_id[50] = "select count(ID) from goods_v1.goods";
char update_key1[50] = "alter table goods_v1.goods drop ID";
char update_key2[80] = "alter table goods_v1.goods add ID int(11) primary key auto_increment first";
char filename[250] = "C:\\mysql_backup\\backup.sql";
char file_time_name[250] = "C:\\mysql_backup\\time.bin";
char file_temp[250] = "C:\\mysql_backup\\temp.bin";
char file_temp_backup[250] = "C:\\mysql_backup\\backup.bin";
char zl_backup[300] = "select * from goods_v1.goods INTO OUTFILE '/var/lib/mysql/goods_v1/#'";
char str_now_time[30];
char str_now_time_s[30];
int MAX_ID = 0;
char MAX_ID_STR[20] = { 0 };
// STAFF goods_v1.staff
// GOODS goods_v1.goods
// CUSTOMER goods_v1.customer
//执行一个sql语句, 添删查改的sql语句都可以
//int mysql_query(MYSQL *mysql, const char *query);
//UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值

//数据库主菜单
int database_main() {
	system("cls");
	int choice;
	int flag_while = 1;
	int flag_7 = 1;
	int flag_delete;
	char fw[200] = { 0 };
	//进入主菜单
	while (flag_while)
	{
		/*printf("\t\b\b>>您想……？\n");
		printf("\t(1)显示所有商品数据.\t(2)按名称查询商品.\n");
		printf("\t(3)按类型查询商品.  \t(4)按日期查询商品.\n");
		printf("\t(5)上架商品.        ");
		printf("\t(6)数据备份与恢复.  \n\t(7)返回主菜单.\n\n");
		printf("\t请输入选项前数字:  ");*/
		/*printf("\n\n\n\t\t\t\t+——————————————————+\n");
		printf("\t\t\t\t|        ->商品数据管理系统<-        |\n");
		printf("\t\t\t\t+——————————————————+\n");*/
		head_info(5);
		printf("\t\t\t\t1.显示所有商品数据\n");
		printf("\t\t\t\t2.按名称查询商品\n");
		printf("\t\t\t\t3.按类型查询商品\n");
		printf("\t\t\t\t4.按日期查询商品\n");
		printf("\t\t\t\t5.组合查询\n");
		printf("\t\t\t\t6.上架商品\n");
		printf("\t\t\t\t7.数据备份与恢复\n");
		printf("\t\t\t\t0.返回主菜单\n");
		printf("\n\t\t\t\t请选择你需要进行的操作：");
		scanf("%d", &choice);
		getchar();
		switch(choice) {
			case 1:
				system("cls");
				chaxun_1(zl);
				{
					int flag_order = 1;
					while (flag_order)
					{
						printf("\n\n\t输入数据条目或对应序号以进行排序显示(输入#返回):  ");
						char ord[200] = "select * from goods_v1.goods";
						char rep[200] = { 0 };
						scanf("%s", rep);
						getchar();
						system("cls");
						if (rep[0] == '#')
						{
							system("cls");
							flag_order = 0;
						}
						else
						{
							StrOrder(ord, rep);
							chaxun_1(ord);
						}
					}
				}
				break;
			case 2:
			{
				char ord[200] = "select * from goods_v1.goods";
				char rep[200] = { 0 };
				system("cls");
				chaxun_1(zl);
				printf("\n\n\t\b\b>>请输入欲查询商品的名称:  ");
				scanf("%s", rep);
				getchar();
				system("cls");
				StrLike(ord,rep);
				if (!chaxun_1(ord))
				{
					Sleep(2000);
					system("cls");
					break;
				}
				int flag_order = 1;
				while (flag_order)
				{
					printf("\n\n\t\b\b>>请选择操作(输入#返回):  \n\t1.修改售价.\t2.删除商品.\n\t");
					char ord[200] = "select * from goods_v1.goods";
					char rep[200] = { 0 };
					scanf("%s", rep);
					getchar();
					if (rep[0] == '#')
					{
						system("cls");
						flag_order = 0;
					}
					else if(rep[0] == '1')
					{
						int ID;
						char NewPrice[20] = { 0 };
						printf("\t\b\b>>请输入待修改商品的相关数据: \n\tID: ");
						scanf("%d",&ID);
						printf("\t售价: ");
						scanf("%s", NewPrice);
						update_price(ID, NewPrice);
					}
					else if (rep[0] == '2') 
					{
						int ID;
						printf("\t请输入待删除商品的ID: \n\tID: ");
						scanf("%d", &ID);
						delete_ID(ID);
					}
				}
			}
				break;
			case 3:
			{
				char ord[200] = "select * from goods_v1.goods";
				char rep[200] = { 0 };
				system("cls");
				chaxun_1(zl);
				printf("\n\n请输入欲查询商品的类型:  ");
				scanf("%s", rep);
				getchar();
				system("cls");
				StrWhere(ord, "类型", rep);
				chaxun_1(ord);
				printf("\n\n\t(按任意键返回)");
				fgets(fw, 100, stdin);
				system("cls");
			}
				break;
			case 4:
			{
				char ord[200] = "select * from goods_v1.goods";
				char rep[200] = { 0 };
				system("cls");
				chaxun_1(zl);
				printf("\n\n请输入欲查询商品的日期:  ");
				scanf("%s", rep);
				getchar();
				system("cls");
				StrWhere(ord, "日期", rep);
				chaxun_1(ord);
				printf("\n\n\t(按任意键返回)");
				fgets(fw, 100, stdin);
				system("cls");
			}
				break;
			case 0:	//退出系统
				gotoMainmenu();
				break;
			case 6:	//录入数据
			{
				int flag_insert = 1;
				while (1)
				{
					insert_1(&flag_insert);
					if (!flag_insert)
					{
						system("cls");
						break;
					}
					printf("\n\t[按下回车键返回]");
					getchar();
					getchar();
					system("cls");
				}
			}
				
				break;
			/*case 6: //售出商品
				sell();
				system("cls");
				break;*/
			case 7: //备份与恢复
				flag_7 = 1;
				while(flag_7)
			{
				int choice;
				system("cls");
				printf("\n\n\n\t\t\t");
				show_backup_inform();
				printf("\n\t\t\t\t\b\b>>请选择: \n");
				printf("\t\t\t\t1.数据备份.");
				printf("\n\t\t\t\t2.数据恢复.\n\t\t\t\t3.返回.\n\t\t\t\t");
				scanf("%d", &choice);
				switch (choice) {
				case 1:
				{
					backup();
					flag_7 = 0;
					system("cls");
				}
					break;
				case 2:
				{
					recover();
					flag_7 = 0;
					system("cls");
				}
				break;
				case 3:
					flag_7 = 0;
					system("cls");
					break;
				default:
					flag_7 = 1;
					printf("\n\t\t\t\t[请输入1-3以进行选择]\n");
					system("cls");
					break;
				}
			}
				break;
			case 5:
			{	char ord[200] = "select * from goods_v1.goods";
				char name[50] = { 0 };
				char type[50] = { 0 };
				system("cls");
				chaxun_1(ord);
				printf("\n\t请输入商品名称和类型: (输入#返回)\n\t");
				scanf("%s", name);
				if (name[0] == '#')
					continue;
				scanf("%s", type);
				chaxun_zuhe(name,type);
				{
					int flag_order = 1;
					while (flag_order)
					{
						printf("\n\n\t\b\b>>请选择操作(输入#返回):  \n\t1.修改售价.\t2.删除商品.\n\t");
						char ord[200] = "select * from goods_v1.goods";
						char rep[200] = { 0 };
						scanf("%s", rep);
						getchar();
						if (rep[0] == '#')
						{
							system("cls");
							flag_order = 0;
						}
						else if (rep[0] == '1')
						{
							int ID;
							char NewPrice[20] = { 0 };
							printf("\t\b\b>>请输入待修改商品的相关数据: \n\tID: ");
							scanf("%d", &ID);
							printf("\t售价: ");
							scanf("%s", NewPrice);
							update_price(ID, NewPrice);
						}
						else if (rep[0] == '2')
						{
							int ID;
							printf("\t请输入待删除商品的ID: \n\tID: ");
							scanf("%d", &ID);
							delete_ID(ID);
						}
					}
				}
			}
				
				break;
			default:
				system("cls");
				printf("\t\t\t\t[请输入1-7中的一个数字哦]\n");
				continue;
		}
	}
	
	return 0;
}

// 将strRes中的t替换为s，替换成功返回1，否则返回0。
int StrReplace(char strRes[], const char from[], const char to[]) {
	int i, flag = 0;
	char *p, *ts;
	const char * q;
	for (i = 0; strRes[i]; ++i) {
		if (strRes[i] == from[0]) {
			p = strRes + i;
			q = from;
			while (*q && (*p++ == *q++));
			if (*q == '\0') {
				ts = (char *)malloc(strlen(strRes) + 1);
				strcpy(ts, p);
				strRes[i] = '\0';
				strcat(strRes, to);
				strcat(strRes, ts);
				free(ts);
				flag = 1;
			}
		}
	}
	return flag;
}
//自编万能查询(并输出结果)
bool chaxun_1(char * query) {
	//查询
	if (mysql_real_query(&mysql, query, (unsigned long)strlen(query)))
	{
		printf("\a\t[查询失败---请输入合法数据]\n");
		return false;
	}
	//存储结果集(结构体地址)
	res = mysql_store_result(&mysql);
	if (NULL == res)
	{
		printf("\a\t[结果集获取失败]\n");
		return false;
	}

	// 参数: 调用 mysql_store_result() 得到的返回值
	// 返回值: MYSQL_FIELD* 指向一个结构体
	// 通过查询官方文档, 返回是一个结构体的数组
	// 通过这个函数得到结果集中所有列的名字
	MYSQL_FIELD *mysql_fetch_fields(MYSQL_RES *result);
	// 得到存储头信息的数组的地址
	MYSQL_FIELD* fields = mysql_fetch_fields(res);
	// 得到列数
	int num = mysql_num_fields(res);
	// 遍历得到每一列的列名
	printf("\n\t+———————————————————————————————————————————————————————————————+\n");
	printf("\t|");
	for (int i = 0; i < num; ++i)
	{
		printf("%-16s", fields[i].name);
	}
	printf("\b\b|\n\t+———————————————————————————————————————————————————————————————+\n");
	//遍历结果集
	int flag_row = 0;
	while (row = mysql_fetch_row(res))
	{
		flag_row = 1;
		printf("\t|");
		for (int i = 0; i < num; i++)
			printf("%-16s", row[i]);
			
		printf("\b\b|\n");
	}
	printf("\t+———————————————————————————————————————————————————————————————+\n");
	if (!flag_row)
	{
		system("cls");
		printf("\a\t[没有找到相关商品]\n");
		return false;
	}
	return true;
}
//自编数据插入 INSERT INTO table_name(列1，列2，...) VALUES (值1，值2，...)
bool insert_1(int * Flag_insert) {
	char zl[200] = "INSERT INTO goods_v1.goods (ID,名称,类型,库存,售价,进价,日期,销量) VALUES (#,\"$\",\"+\",&,*,-,CURDATE(),0)";
	char MC[40] = { 0 };
	char LX[40] = { 0 };
	char KC[40] = { 0 };
	char SJ[40] = { 0 };
	char JJ[40] = { 0 };
	system("cls");
	printf("\n\n\n\n\t\t请输入：[商品名称] [类型] [库存] [售价] [进价] (输入#返回)\n\t\t     >>");
	scanf("%s", MC);
	if (MC[0] == '#')
	{
		*Flag_insert = 0;
		return false;
	}
		
	scanf("%s %s %s %s",LX,KC,SJ,JJ);
	if (update_id())
	{
		StrReplace(zl,"#", MAX_ID_STR);
		StrReplace(zl,"$", MC);
		StrReplace(zl,"+", LX);
		StrReplace(zl,"&", KC);
		StrReplace(zl,"*", SJ);
		StrReplace(zl,"-", JJ);
		if (!mysql_query(&mysql, zl))
		{
			system("cls");
			printf("\n\n\n\n\t[数据录入成功]\n\t以下是成功录入的数据: \n");
			{	//输出录入的数据
				char ord[200] = "select * from goods_v1.goods";
				char rep[30] = { 0 };
				for (int i = 0; i < strlen(MAX_ID_STR); i++)
					rep[i] = MAX_ID_STR[i];
				StrWhere(ord, "ID", rep);
				chaxun_1(ord);
			}
			return true;
		}
		else
		{
			printf("\n\n\n\n\t\t[数据录入失败，请联系系统管理员](a)\n");
			return false;
		}
	}
	else
	{
		printf("\t\t\t\t[数据录入失败，请联系系统管理员]\n");
		return false;
	}
}
//获取最新MAX_ID值   while (!update_id());
bool update_id() {
	if (mysql_real_query(&mysql, zl_get_id, (unsigned long)strlen(zl_get_id)))
		return false;
	//存储结果集(结构体地址)
	res = mysql_store_result(&mysql);
	if (NULL == res)
		return false;
	//遍历结果集
	int flag_row = 0;
	while (row = mysql_fetch_row(res))
	{
		flag_row = 1;
		sscanf(row[0], "%d", &MAX_ID);
	}
	_itoa(++MAX_ID,MAX_ID_STR,10);
	/*for (int i = 0; i < strlen(row[0]); i++)
		MAX_ID_STR[i] = row[0][i];*/	//ERROR(NEED++)
	if (!flag_row)
		return false;
	return true;
}
//在基础查询语句"select * from goods_v1.goods"后加上" where 列名称 = "搜索对象""
void StrWhere(char strRes[],const char where[],const char xxx[]) {
	int len = (int)strlen(strRes);
	char str_where[30] = " where # = \"@\"";
	for (int i = 0; i < 16; i++)
		strRes[len + i] = str_where[i];
	StrReplace(strRes, "#", where);
	StrReplace(strRes, "@", xxx);
}
//排序
void StrOrder(char strRes[], const char xxx[]) {
	int len = (int)strlen(strRes);
	char str_order[30] = " order by @";
	for (int i = 0; i < 11; i++)
		strRes[len + i] = str_order[i];
	StrReplace(strRes, "@", xxx);
}
//模糊搜索
void StrLike(char strRes[], const char xxx[]) {
	int len = (int)strlen(strRes);
	char str_where[30] = " where 名称 REGEXP '[@]'";
	for (int i = 0; i < 24; i++)
		strRes[len + i] = str_where[i];
	StrReplace(strRes, "@", xxx);
}
//更新售价
bool update_price(int ID, char* new_price) {
	char zl[250] = "UPDATE goods_v1.goods SET 售价 = # WHERE ID = $";
	char str_ID[40] = { 0 };
	_itoa(ID, str_ID, 10);
	StrReplace(zl, "#", new_price);
	StrReplace(zl, "$", str_ID);
	if (!mysql_query(&mysql, zl))
	{
		system("cls");
		printf("\n\n\n\n\t[数据更新成功]\n\t以下是成功更新的数据: \n");
		{	//输出更新的数据
			char ord[200] = "select * from goods_v1.goods";
			StrWhere(ord, "ID", str_ID);
			chaxun_1(ord);
		}
		return true;
	}
	else
	{
		printf("\n\n\n\n\t\t[数据更新失败]\n");
		printf("\n错误代码:%s", zl);
		return false;
	}
	return true;
}
//删除商品
bool delete_ID(int ID) {
	char zl[250] = "DELETE FROM goods_v1.goods WHERE ID = #";
	char str_ID[40] = { 0 };
	_itoa(ID, str_ID, 10);
	printf("%d --- %s", ID, str_ID);
	StrReplace(zl, "#", str_ID);
	if (!mysql_query(&mysql, zl))
	{
		system("cls");
		printf("\n\n\n\n\t[商品删除成功]\n");
		mysql_query(&mysql, update_key1);
		mysql_query(&mysql, update_key2);
		return true;
	}
	else
	{
		printf("\n\n\n\n\t\t[商品删除失败,请联系系统管理员]\n");
		printf("\t错误代码:%s", zl);
		return false;
	}
	return true;
}
//售出商品
bool buy_goods(int ID, int num) {
	char zl_1[250] = "update goods_v1.goods set 库存 = 库存 - # where ID = $";
	char zl_2[250] = "update goods_v1.goods set 销量 = 销量 + # where ID = $";
	char str_ID[40] = { 0 };
	char str_num[40] = { 0 };
	_itoa(ID, str_ID, 10);
	_itoa(num, str_num, 10);
	StrReplace(zl_1, "$", str_ID);
	StrReplace(zl_1, "#", str_num); 
	StrReplace(zl_2, "$", str_ID);
	StrReplace(zl_2, "#", str_num);
	if (!mysql_query(&mysql, zl_1) && !mysql_query(&mysql,zl_2))
	{
		printf("\n\t[商品售出成功]\n\t售出商品的数据: \n");
		{	//输出更新的数据
			char ord[200] = "select * from goods_v1.goods";
			StrWhere(ord, "ID", str_ID);
			chaxun_sell(ord);
			printf("\n\t[输入回车以继续]");
			Sleep(800);
			getchar();
			getchar();
		}
		return true;
	}
	else
	{
		printf("\n\t[商品售出失败]\n");
		printf("\t###请检查库存是否充足###\n\n");
		//printf("\n错误代码:%s\n%s", zl_1,zl_2);
		return false;
	}
	return true;
}
//数据备份
bool backup() 
{
	char zl[250] = "select * from goods_v1.goods INTO OUTFILE '/var/lib/mysql/goods_v1/#.sql'";
	Gettime_s();
	StrReplace(zl, "#", str_now_time_s);
	FILE*fp = fopen(file_temp_backup, "w");
	fprintf(fp, "%s", str_now_time_s);
	fclose(fp);

	/*if (remove(filename) != 0)
	{
		//printf("\t[备份文件更新失败]\n");
		//Sleep(2500);
	}*/
	if (!mysql_query(&mysql, zl))
	{
		system("cls");
		printf("\n\n\n\n\t\t[数据备份成功]\n");
		FILE*pt = fopen(file_time_name, "wb");
		Gettime();
		int len = sizeof(str_now_time);
		fwrite(str_now_time, len, 1, pt);	//写入备份时间
		fclose(pt);
		
		Sleep(2000);
		return true;
	}
	else
	{
		system("cls");
		printf("\n\n\n\n\t\t[数据备份失败,请联系系统管理员]\n");
		printf("\n\t\b\b>>错误代码:%s\n", zl);
		Sleep(2500);
		return false;
	}
	return true;
}
//数据恢复
bool recover() 
{
	char zl1[300] = "delete from goods_v1.goods;";
	char zl2[300] = "LOAD DATA INFILE '/var/lib/mysql/goods_v1/#.sql' INTO TABLE goods_v1.goods";
	FILE*fp = fopen(file_temp_backup, "r");
	char temp = fscanf(fp, "%s", str_now_time_s);
	StrReplace(zl2, "#", str_now_time_s);
	fclose(fp);
	mysql_query(&mysql, zl1);
	if (!mysql_query(&mysql,zl2))
	{
		system("cls");
		printf("\n\n\n\n\t\t[数据恢复成功]\n");
		Sleep(2000);
		return true;
	}
	else
	{
		printf("\n\n\n\n\t\t[数据恢复失败，请联系系统管理员]\n");
		Sleep(2000);
		return false;
	}
	return true;
}
//更新时间
void Gettime()
{
	time_t t;
	struct tm* lt;
	t = time(NULL);
	lt = localtime(&t);
	strftime(str_now_time, 25, "%Y年%m月%d日 %H:%M:%S", lt);
} 
//更新时间——备份文件用
void Gettime_s()
{
	time_t t;
	struct tm* lt;
	t = time(NULL);
	lt = localtime(&t);
	strftime(str_now_time_s, 25, "%Y%m%d%H%M%S", lt);
}
//显示上次备份时间
bool show_backup_inform() 
{
	FILE*pt = fopen(file_time_name, "ab+");
	if (fread(str_now_time, 28, 1, pt))
		printf("\t上一次备份的时间是：%s\n", str_now_time);
	else {
		printf("\t[当前没有备份]\n");
		fclose(pt);
		return false;
	}
	fclose(pt);
	return true;
}
//售出函数配套查询&写入已售数据
bool chaxun_sell(char *query) {
	if (mysql_real_query(&mysql, query, (unsigned long)strlen(query)))
	{
		printf("\a\t[查询失败---请输入合法数据]\n");
		return false;
	}
	//存储结果集(结构体地址)
	res = mysql_store_result(&mysql);
	if (NULL == res)
	{
		printf("\a\t[结果集获取失败]\n");
		return false;
	}

	// 参数: 调用 mysql_store_result() 得到的返回值
	// 返回值: MYSQL_FIELD* 指向一个结构体
	// 通过查询官方文档, 返回是一个结构体的数组
	// 通过这个函数得到结果集中所有列的名字
	MYSQL_FIELD *mysql_fetch_fields(MYSQL_RES *result);
	// 得到存储头信息的数组的地址
	MYSQL_FIELD* fields = mysql_fetch_fields(res);
	// 得到列数
	int num = mysql_num_fields(res);
	// 遍历得到每一列的列名
	printf("\n\t+———————————————————————————————————————————————————————————————+\n");
	printf("\t|");
	for (int i = 0; i < num; ++i)
	{
		printf("%-16s", fields[i].name);
	}
	printf("\b\b|\n\t+———————————————————————————————————————————————————————————————+\n");
	//遍历结果集
	int flag_row = 0;
	while (row = mysql_fetch_row(res))
	{
		flag_row = 1;
		printf("\t|");
		for (int i = 0; i < num; i++)
		{
			printf("%-16s", row[i]);
			if (i == 0 || i == 1 || i == 4 || i == 5) {
				FILE*fp = fopen(file_temp, "a+");
				fprintf(fp, "%s ", row[i]);		//写入文件格式
				fclose(fp);
			}
		}
		printf("\b\b|\n");
	}
	printf("\t+———————————————————————————————————————————————————————————————+\n");
	if (!flag_row)
	{
		system("cls");
		printf("\a\t[没有找到相关商品]\n");
		return false;
	}
	return true;
}
//售出函数
void sell() {
	int ID, num,flag=1;
	char str_ID[30] = { 0 };
	system("cls");
	remove(file_temp);
	while (1){
		system("cls");
		chaxun_1(zl);
		printf("\t\b\b>>请输入将要售出的商品的相关信息：(输入#返回)\n\tID: ");
		scanf("%s", &str_ID);
		if (str_ID[0] == '#')
		{
			printf("\t[输入完毕]\n");
			if(!flag)
				check_out();
			return;
		}
		ID = atoi(str_ID);
		printf("\t数量: ");
		scanf("%d", &num);
		flag = 0;
		if (num <= 0) {
			printf("\t[请输入正确的购买数量]\n\t");
			printf("[按下回车以继续]\n");
			getchar();
			getchar();
			continue;
		}
		if (!buy_goods(ID, num))
		{
			Sleep(2500);
			continue;
		}
		{
			FILE*fp = fopen(file_temp, "a+");
			fprintf(fp, "%d ", num);		//写入文件格式
			fclose(fp);
		}
	}
}
//组合查询
void chaxun_zuhe(char * name, char * type) {
	char zl[250] = "select * from goods_v1.goods where 名称 REGEXP '[#]' and 类型 = '$'";

	putchar('\n');
	StrReplace(zl, "#", name);
	StrReplace(zl, "$", type);
	chaxun_1(zl);
	//printf("\n\t[输入回车返回]");
	//getchar();
	//getchar();
	//system("cls");
}