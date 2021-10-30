#include"head.h"

pNode info_login = (pNode)malloc(LEN);   //全局变量，用于记录成功登录账号的信息
//移动光标
void Gotoxy(int x, int y)
{
    int xx = 0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X = x;
    loc.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc); return;
}
void CursorUpOneLine() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;	//控制台屏幕缓冲区信息
    COORD coord;	//设置屏幕上的坐标
    coord.X = 10;	//设置光标坐标
    coord.Y = 10;

    HANDLE hout;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);		//获取标准输出设备的句柄
    GetConsoleScreenBufferInfo(hout, &csbi);	//获取屏幕缓冲的光标位置,然后把当前光标位置赋给COORD
    coord.X = csbi.dwCursorPosition.X;			//得到坐标x的值
    coord.Y = csbi.dwCursorPosition.Y;			//y值

    coord.Y--;
    SetConsoleCursorPosition(hout, coord);//定位光标
}
void clearLine(int num)//num表示要清空的行数，flag记录清除的方向
{
    if (0 > num)
    {
        num *= -1;
        for (int i = 0; i < num; i++)
        {
            CursorUpOneLine();
            printf("\r");
            for (int j = 0; j < 100; j++)
                printf(" ");
            printf("\r");
        }
    }
    else if (0 < num)
    {
        for (int i = 0; i < num; i++)
        {
            printf("\n\r");
            for (int j = 0; j < 100; j++)
                printf(" ");
            printf("\r");
        }
    }
    else if (0 == num)
    {
        printf("\r");
        for (int j = 0; j < 100; j++)
            printf(" ");
        printf("\r");
    }
}

//用于将文件数据读入动态链表中(check)
pNode createList()
{
    pNode pHead = (pNode)malloc(LEN);
    pHead->next = NULL;
    FILE* fp = fopen(file_temp_account, "a+");
    fclose(fp);
    fp = fopen(file_temp_account, "rb");
    pNode cur = pHead;
    while (1)
    {
        pNode temp = (pNode)malloc(LEN);
        if (!temp) exit(-1);
        if (!fread(temp, LEN, 1, fp))
        {
            free(temp);
            break;
        }
        if (1 == temp->status)//将启用的账号添加至链表
        {
            cur->next = temp;
            cur = temp;
            cur->next = NULL;
        }
    }
    fclose(fp);
    return pHead;
}

//用于管理员注册员工账号,返回值为1表示注册成功，返回值为0表示取消注册。（已添加返回功能、清屏 check）
int registerUser(int initia)
{
    pNode head = createList();
    pNode temp = head->next;
    if (NULL == temp)
    {
        temp = (pNode)malloc(sizeof(struct Account));
        head->next = temp;
    }
    else
    {
        while (temp->next)
        {
            temp = temp->next;
        }
        pNode last = (pNode)malloc(sizeof(struct Account));
        temp->next = last;
        temp = last;
    }
    temp->next = NULL;
    if (0 == initia)
    {
        printf("\n\n\t\t\t开始注册您的管理员账号:-)\n");
        strcpy(temp->idtype ,"管理员");
        temp->achievement = 0;
    }
    if (1 == initia)
    {
        printf("\n\n\t\t\t[您正在注册员工的账号，注册过程中可随时按 # 键后回车以取消注册]\n");
        Sleep(600);
        //新注册的帐号默认为员工账号
        strcpy(temp->idtype, "员工");
        temp->achievement = 0;
    }
    //工号
    while (1)
    {
        printf("\n\n\t\t\t\t请输入需要注册的8位数字工号：");
        scanf("%s", temp->id);

        cancelAction(temp->id);
        pNode t = head->next;//检查是否有重复账号
        int flag0 = 0;
        while (t->next)
        {
            if (0 == strcmp(t->id, temp->id))
            {
                flag0 = 1;
                break;
            }
            t = t->next;
        }
        if (flag0)
        {
            printf("\n\t\t\t\t此账号已经存在，请重新输入!");
            clearLine(-4);
            continue;
        }
        if (8 == strlen(temp->id)) break;
        else
        {
            printf("\n\t\t\t\t请输入一个8位工号！");
            clearLine(-4);
        }
    }
    //密码
    while (1)
    {
        clearLine(0);
        printf("\n\t\t\t\t请设置您的密码，密码应不少于8位：");
        scanf("%s", temp->password);
      
        cancelAction(temp->password);
        if (8 > strlen(temp->password))
        {
            printf("\n\t\t\t\t请设置一个不少于8位的密码！");
            clearLine(-3);
            continue;
        }
        char check[25];
        clearLine(2);
        clearLine(-2);
        printf("\n\t\t\t\t请确认密码：");
        scanf("%s", check);
        cancelAction(check);
        if (0 == strcmp(check, temp->password)) break;
        else
        {
            printf("\t\t\t\t两次输入的密码不一致，请重新输入！");
            clearLine(-4);
           
        }
        memset(temp->password, 0, sizeof(temp->password));
    }
    //姓名
    printf("\n\t\t\t\t请输入姓名:");
    scanf("%s", temp->name);
    cancelAction(temp->name);
    //性别
    while (1)
    {
        getchar();
        printf("\n");
        clearLine(0);
        printf("\t\t\t\t请输入性别（男/女）:");
        scanf("%s", temp->sex);
        cancelAction(temp->sex);
        if (0==strcmp(temp->sex,"男") || 0 == strcmp(temp->sex, "女")) break;//判断数据是否合法
        else
        {
            printf("\n\t\t\t\t请输入“男”或“女”！");
            clearLine(-3);
        }
    }
    //电话号码
    while (1)
    {
        clearLine(1);
        printf("\t\t\t\t请输入你的电话号码：");
        scanf("%s", temp->phone);
        cancelAction(temp->phone);
        if (11 == strlen(temp->phone)) break;
        else
        {
            printf("\n\t\t\t\t请输入一个11位的手机号！");
            clearLine(-3);
        }
    }
    temp->status = 1;
    //将数据录入文件中
    FILE* fp = fopen(file_temp_account, "ab+");
    fwrite(temp, LEN, 1, fp);
    fclose(fp);
    clearLine(4);
    clearLine(-4);
    printf("\n\t\t\t\t信息录入成功！\n");
    Sleep(200);
	if (0 == initia)
	{
		printf("\t\t\t\t您已成功注册，现在返回登录界面...\n");
		system("cls");
		login();
	}
    else printf("\t\t\t\t正在返回主菜单...\n");
    Sleep(2000);
    system("cls");
	gotoMainmenu();
    return 1;
}

//登录(已添加返回功能/格式正确 /梅花)
int login()
{
    int inputchance = 5;
    pNode head = createList();
    if (NULL == head->next)//第一次使用该系统，引导用户创建账户
    {
		printf("\n\t\t\t\t\t\t+————————————————————+\n");
		printf("\t\t\t\t\t\t|                                        |\n");
		printf("\t\t\t\t\t\t|           超 市 管 理 系 统            |\n");
		printf("\t\t\t\t\t\t|                                        |\n");
		printf("\t\t\t\t\t\t+————————————————————+\n");
        printf("\n\n\t\t\t\t\t\t你好！\n");
        Sleep(200);
        printf("\t\t\t\t\t\t感谢您选择本系统 (^_^)\n");
        Sleep(200);
        printf("\t\t\t\t\t\t第一次使用时，我们将引导您进行新用户的管理员账号注册......\n");
        Sleep(2500);
        system("cls");
        registerUser(0);
    }
    head = createList();
    pNode temp = head->next;
    int judge = 0;//后门
	printf("\n\t\t\t\t\t\t+————————————————————+\n");
	printf("\t\t\t\t\t\t|                                        |\n");
	printf("\t\t\t\t\t\t|           超 市 管 理 系 统            |\n");
	printf("\t\t\t\t\t\t|                                        |\n");
	printf("\t\t\t\t\t\t+————————————————————+\n");
    printf("\n\n\t\t\t\t\t\t欢迎回来，请按任意键以继续:-)");
    _getch();
	clearLine(0);
	clearLine(-1);
    while (1)
    {
        char id[10];
        printf("\n\t\t\t\t\t\t请输入8位工号以登录:");
        scanf("%s", id);

        //此处为后门！！！！！！！！！

        if ('@' == id[0])
        {
            for (int i = 0; i < 8; i++) id[i] = i+1+'0';
            judge = 1;
            break;
        }

        //检查账号是否存在
        temp = head->next;
        int flag0 = 0;
        while (temp)
        {
            if (0 == strcmp(temp->id, id) && 1 == temp->status)
            {
                flag0 = 1;
                break;
            }
            temp = temp->next;
        }
        if (0 == flag0)
        {
            printf("\n\t\t\t\t\t\t:-(  查无此工号，请重新输入！");
            clearLine(-3);
            continue;
        }
        else break;
    }
    //后门
    if (1 == judge)
    {
        memmove(info_login, temp, LEN);
        printf("\n\t\t\t\t\t\t恭喜你%s，登录成功！\n", temp->name);
        Sleep(1000);
        system("cls");
        return 1;
    }

    //检查密码是否正确

    while (1)
    {
        char password[25];
        
        clearLine(1);
        printf("\t\t\t\t\t\t请输入密码:");
        scanf("%s", password);
        if ('#' == password[0] && password[1] == '\0')      //用于取消操作
        {
            system("cls");
            login();
            break;
        }
        if (0 == strcmp(password, temp->password))
        {
            clearLine(1);
            printf("\t\t\t\t\t\t●▽●恭喜你%s，登录成功！\n", temp->name);
            memmove(info_login, temp, LEN);
            Sleep(1800);
            system("cls");
            break;
        }
        inputchance--;
        if (inputchance == 0)
        {
            printf("\t\t\t\t\t\t对不起，你以连续输错密码五次，即将退出...\n");
            Sleep(1800);
            exit(0);
        }//多次输错密码，退出程序！
        else
        {
            printf("\n\t\t\t\t\t\t密码输入错误，请重新输入！你还有 %d 次机会", inputchance);
            clearLine(-3);
            
        }
    }
	//gotoMainmenu();
    return 1;

}

//修改数据的函数  (已添加返回功能)
void changeStatistics_user()
{
	system("cls");
    FILE* fp = fopen(file_temp_account, "rb+");
    pNode temp = (pNode)malloc(LEN);
    char choice;
    printf("\n\n\t\t\t\t请选择需要修改的数据类型\n\t\t\t\t1.密码\n\t\t\t\t2.电话号码\n\t\t\t\t0.返回\n\n\t\t\t\t请选择：");
    getchar();
    scanf("%c", &choice);

    if ('#' == choice)
    {
        char t[3] = "#";
        cancelAction(t);
    }
	if('0'==choice)
	{
		printf("\n");
		char t[3] = "#";
		cancelAction(t);
	}
        
    if ('1' == choice)
    {
		printf("\n\n\t\t\t需要验证密码：");
		if (vertify_password()) {}
        char new_pass[25];
        while (1)
        {
            printf("\n\t\t\t请输入新密码：");
            scanf("%s", new_pass);
            if ('#' == new_pass[0] && new_pass[1] == '\0')      //用于取消操作
            {
                printf("\t\t\t您已取消此次操作，正在返回\n");
                Sleep(2000);
                system("cls");
                changeStatistics_user();
            }
            char check[25];
            printf("\t\t\t请确认密码：");
            scanf("%s", check);
            if ('#' == check[0] && check[1] == '\0')      //用于取消操作
            {
                printf("\t\t\t您已取消此次操作，正在返回\n");
                Sleep(2000);
                system("cls");
                changeStatistics_user();
            }
            if (0 == strcmp(check, new_pass)) break;
			else
			{
				printf("\t\t\t两次输入的密码不一致，请重新输入！\n");
				Sleep(1500);
				clearLine(-5);
			}
            strcpy(info_login->password, new_pass);
        }
    }
    if ('2' == choice)
    {
        char new_phone[12];
        while (1)
        {
            printf("\n\t\t\t请输入新的电话号码：");
            scanf("%s", new_phone);
            cancelAction(new_phone);
            if (11 == strlen(new_phone)) break;
            else
            {
                printf("\n\t\t\t请输入一个正确的11位电话号码！\n");
                clearLine(-4);
            }
        }
        strcpy(info_login->phone, new_phone);
    }
    int len = LEN;
    fseek(fp, -len, SEEK_CUR);
    temp = info_login;
    fwrite(temp, LEN, 1, fp);
	Sleep(1300);
	system("cls");
    if ('1' == choice)
    {
        printf("\n\n\t\t\t[你已修改密码，请重新登陆]\n");
        Sleep(1000);
        login();
    }
    fclose(fp);
	gotoMainmenu();
}

//用于管理员删除数据(已添加返回功能)
void deleteStatistics_account()
{
    FILE* fp = fopen(file_temp_account, "rb+");
    pNode temp = (pNode)malloc(LEN);
    char id0[10] = { 0 };

    int inputchance = 3;    //验证管理员密码，共三次输入机会
    printf("\n\n\t\t\t此项操作需要验证管理员身份，");
    if (vertify_password());

    int flag0 = 0;
    while(1)
    { 
        printf("\t\t\t请输入需要删除的账号：");
        scanf("%s", id0);
        cancelAction(id0);
        while (fread(temp, LEN, 1, fp))
        {
            if (0 == strcmp(id0, temp->id))
            {
                if (0 == strcmp(id0, info_login->id))
                {
                    printf("\n\t\t\t您不能删除您自己！\n");
                    break;
                }
                flag0 = 1;
                int flag = 0;   //用于用户确认是否删除
                printf("\n\t\t\t确定要删除%s这个账号吗？ 1.删除  0.取消 :", temp->id);
                scanf("%d", &flag);

                if (1 == flag)    //清除此项数据
                {
                    memset(temp, 0, LEN);
                    temp->status = 0;
                    int len = LEN;
                    fseek(fp, -len, SEEK_CUR);
                    fwrite(temp, LEN, 1, fp);
                    printf("\n\t\t\t您已成功删除！\n");
                }
                else printf("\t\t\t您已取消此次操作，账号未删除.\n");
                printf("\t\t\t[正在返回主菜单...]\n");
                Sleep(1800);
                system("cls");
                break;
            }
            if (0 == flag0)
            {
                printf("\t\t\t查无此账号，请重新输入\n");
                system("cls");
                continue;
            }
            else break;
        }
		break;
    }
    fclose(fp);
	gotoMainmenu();
	return;
}

int resetPassword_admin()
{
    FILE* fp = fopen(file_temp_account, "rb+");
    pNode temp = (pNode)malloc(LEN);
    char id0[10] = { 0 };

    int flag0 = 0;
    while (1)
    {
        printf("\n\n\t\t\t请输入需要重置密码的账号：");
        scanf("%s", id0);
        cancelAction(id0);
        while (fread(temp, LEN, 1, fp))
        {

            if (0 == strcmp(id0, temp->id))
            {
                flag0 = 1;
                printf("\n\t\t\t此项操作需要验证管理员身份，");
                if (vertify_password());

                int flag = 0;   //用于用户确认是否删除
                printf("\n\t\t\t确定要重置%s的密码吗？0.取消  1.确认:", temp->id);
                scanf("%d", &flag);

                if (1 == flag)    //清除此项数据
                {
                    memset(temp->password, 0, sizeof(temp->password));
                    for (int i = 1; i <= 8; i++)
                        temp->password[i - 1] = i + '0';
                    int len = LEN;
                    fseek(fp, -len, SEEK_CUR);
                    fwrite(temp, LEN, 1, fp);
                    printf("\t\t\t您已成功重置工号为 %s 的员工密码！新密码为12345678，请提示员工及时修改\n", temp->id);
                }
                else printf("\t\t\t您已取消此次操作\n");
                printf("\t\t\t正在返回主菜单...\n");
                Sleep(1800);
                system("cls");
                break;
            }
        }
        if (0 == flag0)
        {
            printf("\t\t\t未找到此账号，请重新输入！\n");
            system("cls");
            continue;
        }
        else break;
    }
    fclose(fp);
	gotoMainmenu();
    return 1;
}

//用于输出所有员工信息
void showStatistics_account()
{
	system("cls");
    pNode head = createList();
    pNode temp = head->next;
    int num = 0;
    while (temp)
    {
        num++;
        temp = temp->next;
    }
	printf("\n\n\n\t\t\t所有员工信息如下：\n");
    temp = rankAccount_id(head, num);
	printf("\n\t\t\t+");
	for (int i = 0; i < 20; i++) printf("——");
	printf("+\n");
    printf("\t\t\t| 账号类型\t    账号\t    姓名\t    电话号码\t\t性别\t |\n");
	printf("\t\t\t+");
	for (int i = 0; i < 20; i++) printf("——");
	printf("+\n");
    while (temp)
    {
        printf("\t\t\t|  %-6s\t  %-10s        %-10s\t    %11s\t\t %-8s|\n", temp->idtype, temp->id, temp->name,  temp->phone, temp->sex);
        temp = temp->next;
    }
	printf("\t\t\t+");
	for (int i = 0; i < 20; i++) printf("——");
	printf("+\n");
	printf("\n\n\t\t\t（按任意键返回...）");
    _getch();
    system("cls");
	gotoMainmenu();
}
/*
int addAdmin()
{
    pNode temp = (pNode)malloc(LEN);
    char id0[10];
    FILE* fp = fopen(file_temp_account, "ab+");
    fclose(fp);
    fp = fopen(file_temp_account, "rb+");
    printf("您正在添加管理员:\n");
    Sleep(200);
    printf("此项操作需要验证管理员身份，");
    if (vertify_password());
    int flag0 = 0;
    while (1)
    {
        printf("请输入需要添加为管理员的账号：");
        scanf("%s", id0);
        cancelAction(id0);
        while (fread(temp, LEN, 1, fp))
        {
            if (0 == strcmp(id0, temp->id))
            {
                flag0 = 1;
                int flag = 0;   //用于用户确认是否删除
                printf("确定要添加%s这个账号为管理员吗？0.否  1.是:", temp->id);
                scanf("%d", &flag);

				if (1 == flag)                                            
				{
					strcpy(temp->idtype, "管理员");
					printf("您已成功添加！\n");
					int len = LEN;
					fseek(fp, -len, SEEK_CUR);
					fwrite(temp, LEN, 1, fp);
					fclose(fp);
				}
				else 
				{
					printf("您已取消此次操作，账号未添加为管理员.\n");
					fclose(fp);
				}
                printf("正在返回主菜单...\n");
                Sleep(1800);
                system("cls");
                break;
            }
            if (0 == flag0)
            {
                printf("查无此账号，请重新输入\n");
                system("cls");
				fclose(fp);
                continue;
            }
            else break;
        }
		break;
    }
	gotoMainmenu();
	return 0;
}
*/
//用于关键操作中认证用户身份，要求输入密码(已添加返回功能)
int vertify_password()
{
    int inputchance = 3;    //验证密码，共三次输入机会
    while (1)
    {
        char password[25] = { 0 };
        printf("\n\t请输入您的密码或按 # 取消操作：");
        scanf("%s", password);
        cancelAction(password);
        if (0 == strcmp(password, info_login->password))
        {
            printf("\t密码正确！\n");
            Sleep(1500);
            system("cls");
            break;
        }
        inputchance--;
        if (inputchance == 0)
        {
            printf("\t密码输错次数过多，即将退出您的账号，请重新登录您账号！\n");
            Sleep(1800);
            login();
        }
        else printf("\t密码输入错误，请重新输入！\n共有3次机会，您还有%d次机会\n", inputchance);
    }
    return 1;
}


void gotoMainmenu()
{
    int flag = 0;
    if (0==strcmp(info_login->idtype, "员工"))
        flag = 1;
    switch (flag)
    {
    case 0: mainmenu_admin(); break;
    case 1: mainmenu_employee(); break;
    }
}

pNode rankAccount_id(pNode head, int n)
{
    pNode temp = head;
    for (int k = 0; k < n - 1; k++)
    {
        temp = head;
        for (int i = 0; i < n - 1; i++)
        {
            if (0 < strcmp(temp->next->id, temp->next->next->id))
            {
                pNode t1 = temp->next;
                pNode t2 = t1->next;
                pNode t3 = t2->next;
                temp->next = t2;
                t2->next = t1;
                t1->next = t3;
            }
            temp = temp->next;
        }
    }
    return head->next;
}

void cancelAction(char in[])
{
    if ('#' == in[0] && '\0' == in[1])  //取消注册
    {
        printf("\t\t\t\t您已取消！\n");
        Sleep(20);
        printf("\t\t\t\t正在返回主菜单\n");
        Sleep(2000);
        system("cls");
        gotoMainmenu();
    }
}


