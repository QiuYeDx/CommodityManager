
#include "head.h"



char file_temp_vip[250] = "C:\\mysql_backup\\vip.bin";
char file_temp_account[250] = "C:\\mysql_backup\\account.bin";
char file_temp_record[250] = "C:\\mysql_backup\\record.bin";

/**********************************����****************************************/

pv createv()     //���ڽ��ļ����ݶ��붯̬������
{
    pv pHead = (pv)malloc(LENV);
    pHead->next = NULL;
    FILE* fp = fopen(file_temp_vip, "a+");
    fclose(fp);
    fp = fopen(file_temp_vip, "rb");
    pv cur = pHead;
    while (1)
    {
        pv temp = (pv)malloc(LENV);
        if (!temp) exit(-1);
        if (!fread(temp, LENV, 1, fp))     //���û����
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

int addv()        //�������vip
{
    system("cls");
    pv head = createv();
    pv temp = head->next;
    if (NULL == temp)
    {
        temp = (pv)malloc(LENV);
        head->next = temp;
    }
    else
    {
        while (temp->next)
        {
            temp = temp->next;
        }
        pv last = (pv)malloc(LENV);
        temp->next = last;
        temp = last;
    }
    temp->next = NULL;
    printf("\n\n\n\t\t***********��������ӻ�Ա����ӹ����п���ʱ�� # ����س���ȡ����ӣ�*********\n");
    //����
    printf("\n\n\t\t\t>>�������Ա����:");
    scanf("%s", temp->name);
    cancelAction(temp->name);
    //�Ա�
    while (1)
    {
        getchar();
        printf("\n\t\t\t>>�������Ա�Ա���/Ů��:");
        scanf("%s", temp->sex);
        cancelAction(temp->sex);
        if (0==strcmp(temp->sex,"��") || 0 == strcmp(temp->sex, "Ů")) break;//�ж������Ƿ�Ϸ�
        else printf("\n\t\t\t>>�����롰�С���Ů����");
        clearLine(-3);
    }
    //�绰����
    while (1)
    {
        printf("\n");
        clearLine(0);
        printf("\t\t\t>>�������Ա�ĵ绰���룺");
        scanf("%s", temp->phone);
        cancelAction(temp->phone);
        if (11 == strlen(temp->phone)) break;
        else printf("\n\t\t\t>>������һ��11λ���ֻ��ţ�");
        clearLine(-3);
    }
    
	temp->star = '1';
    temp->cost = 0;          //���ѶĬ��Ϊ0
    //������¼���ļ���
    FILE* fp = fopen(file_temp_vip, "ab+");
    fwrite(temp, LENV, 1, fp);
    fclose(fp);
    printf("\t\t\t[��Ϣ¼��ɹ�]\n");
    Sleep(200);
    printf("\t\t\t[���ѳɹ����]\n");
    Sleep(500);
    system("cls");
    menu_vip();
    return 1;
}

void showv()     //����������л�Ա��Ϣ
{
    system("cls");
    printf("\n\n\n\t\t\t����vip��Ϣ���£�\n");
    pv head = createv();
    pv temp = (pv)malloc(LENV);
    temp = head->next;
	printf("\n\t\t\t+");
	for (int i = 0; i < 20; i++) printf("����");
	printf("+\n");

    printf("\t\t\t| �Ǽ�\t\t����\t\t�绰����\t\t�Ա�\t\t���Ѷ�\t |\n");
	printf("\t\t\t+");
	for (int i = 0; i < 20; i++) printf("����");
	printf("+\n");
    while (temp)
    {
		printf("\t\t\t|  %c\t\t%-7s  \t%s\t\t%s\t\t%.2f\t |\n", temp->star, temp->name, temp->phone, temp->sex, temp->cost);
        temp = temp->next;
    }
	printf("\t\t\t+");
	for (int i = 0; i < 20; i++) printf("����");
	printf("+\n");
	printf("\n\n\t\t\t[�����������]");
    _getch();
    system("cls");
    menu_vip();
}

int changev()     //�����޸��Ǽ�
{
    clearLine(0);
    int cost;    //���޸����Ѷ��й�
    vip v;
    int i = 0, find = 0;    //��������Ƿ��ҵ�
    char star, choose, yes;
    FILE* fp = fopen(file_temp_vip, "rb+");
    char phone[12];
    while (1)
    {
        printf("\n\t\t\t>>��������Ҫ�޸ĵĻ�Ա�ĵ绰���룺");
        scanf("%s", phone);
        cancelAction(phone);
        if (11 == strlen(phone)) break;
        else
        {
            printf("\n\t\t\t[������һ����ȷ��11λ�绰����]");
            clearLine(-3);
        }
    }
    getchar();
    pv head = createv();
    pv temp = head->next;
    do
    {
        if (strcmp(temp->phone, phone) == 0)
        {
            find = 1;    //��ʾ���ҵ���
            break;
        }
        i++;
    } while (temp = temp->next);
    if (find == 0)
    {
        printf("\t[δ�ҵ����û�]\n");
        return 0;
    }
    while (1)
    {
        printf("\t>>�������޸ĺ���Ǽ���");
        scanf("%c", &star);
        if (star >= '1' && star <= '3') break;
        else if (star == '#') return 0;
        else printf("\t[������1-3֮���ֵ]\n");
    }
    fseek(fp, i * LENV, 0);
    fwrite(&star, 1, 1, fp);
    printf("[�޸ĳɹ�]\n");
    Sleep(100);
    fclose(fp);
    menu_vip();
    return 0;
}

int searchv()     //���ݵ绰��������ض�vip����Ϣ��
{
    system("cls");
    int find = 0;    //��������Ƿ��ҵ�
    char phone[12];
    while (1)
    {
        printf("\n\t>>��������Ҫ���ҵĻ�Ա�ĵ绰���룺");
        scanf("%s", phone);
        if (11 == strlen(phone)) break;
        else if (phone[0] == '#' && phone[1] == '\0')
        {
            printf("\t\t\t[����ȡ��]\n");
            Sleep(1000);
            system("cls");
            return 0;
        }
        else printf("\t[������һ����ȷ��11λ�绰����]\n");
    }
    getchar();
    pv head = createv();
    pv temp = head->next;
    do
    {
        if (strcmp(temp->phone, phone) == 0)
        {
            find = 1;    //��ʾ���ҵ���
            break;
        }
    } while (temp = temp->next);
    if (find == 0)
    {
        printf("\t[δ�ҵ����û�]\n");
        menu_vip();
        return 0;
    }
    printf("\t���Ǽ���%c\n\t��������%s\n", temp->star, temp->name);
    if (temp->sex == 0) printf("\t���Ա�Ů\n");
    else printf("\t���Ա���\n");
    printf("\t�����Ѷ%.2f\n", temp->cost);
	_getch();
    menu_vip();
}
    
sp createshop()      //���ڽ��ļ����ݶ��붯̬������
{
    sp pHead = (sp)malloc(L);
    pHead->next = NULL;
    FILE*fp = fopen(file_temp, "r+");
    sp cur = pHead;
    while (1)
    {
        sp temp = (sp)malloc(L);
        if (!temp) exit(-1);
        if (5!=fscanf(fp, "%d%s%lf%lf%d", &temp->id, temp->name,  &temp->price, &temp->cost, &temp->num))     //���û����
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


LNode check_out()      //����shopping�ṹ�巵�غ�����Ӧ����ȵĽṹ��
{
	getchar();
	char yes;                   //�Ƿ���vip
	double sumj = 0, sums = 0;       //���ۺͣ��ۼۺ�
	double money = 0, profit = 0;    //Ӧ�������
	char phone[12];             //vip�ĵ绰
	int star_t = 0;
	int star_f = 0;

	sp head = createshop();
	sp temp = head->next;
	do
	{
		sumj += (temp->num) * (temp->cost);
		sums += (temp->num) * (temp->price);

	} while (temp = temp->next);

	while (1)
	{
		for (int i = 0; i < 30; i++) printf("\n");
		for (int i = 0; i < 30; i++) CursorUpOneLine();
		printf("\n\t��[�س�]�Խ��н���");
		_getch();
		system("cls");
		printf("\n\t\t\t>>VIP������1����vip������0:");
		scanf("%c", &yes);
		if (yes == '1' || yes == '0') {}
		else
		{
			printf("\n\t\t\t[������ 0 �� 1 ]");
			clearLine(-3);
			continue;
		}

		if (yes == '1')              //����ǻ�Ա��������������ۺ��Ӧ����
		{
			int flag = 0;
			FILE* fp = fopen(file_temp_vip, "rb+");
			pv t = (pv)malloc(LENV);
			while (1)
			{
				printf("\n\t\t\t>>�������Ա�ĵ绰���룺");
				scanf("%s", phone);
				if (11 == strlen(phone)) {}
				else
				{
					printf("\n\t\t\t>>������һ����ȷ��11λ�绰���룡");
					Sleep(900);
					clearLine(0);
					clearLine(-3);
					continue;
				}
				while (fread(t, LENV, 1, fp))
				{
					if (0 == strcmp(t->phone, phone))
					{
						if (t->star == '1') { money = 0.9 * sums; }
						else if (t->star == '2') { money = 0.8 * sums; }
						else { money = 0.7 * sums; }
						t->cost =t->cost + money;
						star_t = t->star;
						if (t->cost >= 2000) t->star = '2';
						if (t->cost >= 8000) t->star = '3';
						star_f = t->star;
						int len = LENV;
						fseek(fp, -len, SEEK_CUR);
						fwrite(t, LENV, 1, fp);
						flag = 1;
						fclose(fp);
						break;
					}
				}
				if (0 == flag)
				{
					printf("\n\t\t\t[δ�ҵ����˺ţ�����������]");
					Sleep(800);
					clearLine(0);
					clearLine(-3);
					fclose(fp);
					continue;
				}
				else
					break;
			}
			break;
		}
		else break;
	}
	system("cls");
	profit = money - sumj;
	LNode r = (LNode)malloc(LEN1);                    //һ�᷵������ṹ��ָ��
	time_t t;
	struct tm* lt;
	t = time(NULL);
	lt = localtime(&t);
	strftime(r->time, 25, "%Y-%m-%d %H:%M:%S", lt);

	if ('1' == yes)
	{
		r->profit = money - sumj;
		strcpy(r->vip, phone);
		r->receive = money;

		printf("\n\n\t\t\t  ��Ա��:%s\n\n", r->vip);
	}
	else
	{
		r->profit = sums - sumj;
		r->receive = sums;
		strcpy(r->vip, "NULL");
	}

	r->next = NULL;
	showShop(sums, r->receive,star_f,star_t);
	addRecord(r);
	return r;
}


void showShop(double sum,double pay,int star,int star_t)
{
    sp head = createshop();
    sp temp = head->next;
    printf("\t\t\t+");
    for (int i = 0; i < 16; i++) printf("����");
    printf("+\n");
    printf("\t\t\t|     ��Ʒ���\t     ��Ʒ����\t      ��Ʒ����\t      ����\t |\n");
    
    printf("\t\t\t+");
    for (int i = 0; i < 16; i++) printf("����");
    printf("+\n");
    while (temp)
    {
        printf("\t\t\t|\t%d\t    %-18s%.2f\t\t%d\t |\n",temp->id,temp->name,temp->price,temp->num);
        temp = temp->next;
    }

    printf("\t\t\t+");
    for (int i = 0; i < 16; i++) printf("����");
    printf("+\n");

    printf("\t\t\t|\t\t\t\t\t �ܼۣ�%.2f\t\t |\n",sum);
    printf("\t\t\t|\t\t\t\t\t �ۿۣ�%.2f\t\t |\n",sum-pay);
    printf("\t\t\t|\t\t\t\t\t Ӧ����%.2f\t\t |\n",pay);
    printf("\t\t\t+");
    for (int i = 0; i < 16; i++) printf("����");
    printf("+\n");
	if (star != star_t) printf("\n\n\t\t\t���Ļ�Ա�ȼ���������%c��", star);
    _getch();
    system("cls");
}

