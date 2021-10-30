#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
//#include <Windows.h>
//#include <WinSock2.h>
#pragma comment(lib,"libmysql")
#include <mysql.h>
//#define HOST "localhost"
#define HOST "39.106.58.123"
#define USERNAME "root"
#define PASSWORD "20011216"
#define DBNAME "goods_v1"


#define LEN sizeof(account)
#define LEN1 sizeof(record)
#define L sizeof(struct Shopping)
#define LENV sizeof(vip)

typedef struct Account  //员工账号信息
{
    char idtype[10];//0为管理员账号，1为员工账号
    char id[9];//工号(8位数字)
    char password[25];//密码
    char name[15];
    char sex[4];//0为女，1为男
    char phone[12];
    float achievement;
    int status;//0表示账号停用，1表示账号启用
    struct Account* next;
}account, * pNode;

typedef struct Record
{
    char time[25];//记录销售时间(八位数)
    char id[10];//记录员工
    char vip[12];//记录消费的会员
    double receive;//记录收款额
    double profit;//记录利润
    struct Record* next;
}record, * LNode;

//vip
typedef struct VIP  //vip信息
{
    char star;                     //星级，1-3（9,8,7折）
    char name[15];
    char sex[4];                      //0为女，1为男
    char phone[12];
    double cost;                       //消费额 
    struct VIP* next;
}vip, * pv;

typedef struct Shopping
{
    int id;
    char name[30];
    double cost;//Jinjia
    double price;
    int num;
    struct Shopping* next;
}*sp;


extern MYSQL mysql;
extern MYSQL_RES *res;
extern MYSQL_ROW row;
extern pNode info_login;
extern int MAX_ID;
extern char MAX_ID_STR[20];
extern char filename[250];
extern char file_time_name[250];
extern char file_temp[250];
extern char file_temp_vip[250];
extern char file_temp_account[250];
extern char file_temp_record[250];

pNode createList();
int registerUser(int);
int login();
void changeStatistics_user();
void deleteStatistics_account();
void showStatistics_account();
void mainmenu_admin();
void mainmenu_employee();
int vertify_password();
int resetPassword_admin();
void menu_managestatistics();
void Gotoxy(int x, int y);
void CursorUpOneLine();
void clearLine(int num);
void head_info(int i);
void cancelAction(char in[]);
void gotoMainmenu();
pNode rankAccount_id(pNode head, int n);

void addRecord(LNode record);
void showRecord();
LNode createList_record();
void  output(LNode head);
void searchRecord();
LNode searchRecord_vip(LNode head);
LNode searchRecord_date(LNode head);
void createExcel();
//void showRecord();
void menu_record();



/**********************************函数声明**************************************/
pv createv();
int addv();
void showv();
int changev();
int searchv();
LNode check_out();

void menu_vip();
void showShop(double sum, double pay, int star, int star_t);
sp createshop();
void Gettime_s();


//小白部分
int database_main();
bool chaxun_1(char *);
bool chaxun_sell(char *);
bool update_id();
int StrReplace(char strRes[], const char from[], const char to[]);
bool insert_1(int *);
bool update_price(int ID, char* new_price);
bool delete_ID(int ID);
bool buy_goods(int ID, int num);
bool backup();
bool recover();
void StrWhere(char strRes[], const char where[], const char xxx[]);
void StrOrder(char strRes[], const char xxx[]);
void StrLike(char strRes[], const char xxx[]);
void Gettime();
void sell();
bool show_backup_inform();
void exit_program();
void backup_all();
void recovery_all();
void Gettime_t();
void menu_backup();
void chaxun_zuhe(char *,char *);