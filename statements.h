#pragma once
//////////////////////////////////////��̬ȫ�ֱ���\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const int NAME = 15, PASSWORD = 12;


//////////////////////////////////////ö�����Ͷ���\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef enum {
	FILM_KEY = 1,
	OPERA_KEY = 2,
	CONCERT_KEY = 3,
	PLAN_KEY = 4,
	RECORD_KEY = 5,
	TICKET_KEY = 6,
	ACCOUNT_KEY = 7,
}Key_status;

typedef enum {//�����Ŀö������
	PROGRAM_movie = 1,//��Ӱ
	PROGRAM_opera = 2,//���
	PROGRAM_concert = 3//���ֻ�
}program_types;

typedef enum {//�����˻�ö������
	USER_admin = 1,
	USER_manager = 2,
	USER_conductor = 3,
	USER_customer = 4,
	USER_frozen = 5,//����״̬
}user_types;

typedef enum {//�����Ӱ�ּ�ö������
	RATING_child = 1,//��ͯ�ɹۿ�
	RATING_teens = 2,//������ɹۿ�
	RATING_adult = 3//���˿ɹۿ�
}program_ratings;

typedef enum {//������λ���ö������
	SEAT_none = 0,	//��λ
	SEAT_available = 1,//����λ
	SEAT_private=2,//����
	SEAT_unrepaired = 9//�𻵵���λ
}seat_conditions;

typedef enum {
	TICKET_available=0,//����
	TICKET_sold = 1,//����
	TICKET_reserve = 2,//Ԥ��
}ticket_statuses;

typedef enum {
	SALE_sold=1,//��Ʊ
	SALE_return=2,//��Ʊ
}sale_types;

//////////////////////////////////////�ṹ����\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct {
	int year;
	int month;
	int day;
}date_status;//���ڽṹ��

typedef struct {
	int hour;
	int minute;
}time_status;//ʱ��ṹ��

////////////////////////////////////////���ж���

typedef struct linklist_key {
	long key;
	char type;//ʵ������    1  ��Ӱ    2 ���   3���ֻ�     4�ݳ��ƻ�     5���ۼ�¼
	struct linklist_key  *pre, *next;
}Key;

typedef struct linklist_seat {
	int stduio_ID;//��λ���ڷ�ӳ�����
	int seatx;//��λ������
	int seaty;//��λ������
	seat_conditions seat_condition;//λ��״̬   �μ�enum seat_conditions
	struct linklist_seat *pre, *next;
}Seat;

typedef struct linklist_ticket {
	long ticket_ID;//�볡ȯ���
	int seatx;//��λ������
	int seaty;//��λ������
	int price;//Ʊ��    ��Ŀ����
	ticket_statuses ticket_status;//Ʊ��״̬     �μ�enum tickets_statuses
	struct linklist_ticket *pre, *next;
}Ticket;

typedef struct linklist_record{//���׼�¼
	long record_ID;//���׼�¼ID
	int conductor_ID;//��ƱԱID      ��Ա�˻�
	int plan_ID;//�ݳ��ƻ�ID
	int ticket_ID;//ƱID
	date_status date;//��������
	time_status time;//����ʱ��
	int price;//Ʊ��
	sale_types sale_type;//��������
	struct linklist_record *pre, *next;
}Record;

//////////////////////////////////////ʵ����������\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct em{//��Ŀ������
	char program_ID[NAME/2+1];//  ��Ŀ���
	char program_name[NAME * 2 + 1];//15����    ��Ŀ����
	program_types program_type;//��Ŀ����  �μ�enum program_typesö�ٶ���
	program_ratings program_rating;//��Ŀ�ȼ� �μ�program_ratingsö�ٶ���
	char director[NAME];//7������     ����   ���ֻ�Ϊָ��
	char performer[2][NAME];//7������      ����   ����
	char start_date[11]; //��ӳ����   ��ʽ2018-05-12 ����Ϊ10
	char end_date[11]; //��������   ��ʽ2018-05-12 ����Ϊ10s
	int duration;//��Ŀʱ��       minute   [1,600]
	char  label[5];//��Ŀ��ǩ   ����  ϲ��  ����   ��� 
	char area[5];//����   2������
	char language[NAME];//����
	int price;//Ʊ��   [5,100]
	int cost;//��ӳ�ɱ�    ����Ԫ)
}data_program;

typedef struct emm {
	char studio_ID[NAME/2];//�����λ����   ��ӳ�����
	char studio_name[NAME];//����߸�����    ��ӳ������
	int seatsum;//������λ����
	int seatx;//5~12
	int seaty;//10~25  ��ӳ����λ ���к���    ��������   �������ö�ά����
	Seat *seat_head, *seat_tail;//������
}data_studio;

typedef struct emmm {//�ݳ��ƻ�������
	long plan_ID;//�ݳ��ƻ����
	char program_name[NAME * 2 + 1];//�ݳ���Ŀ����
	int studio_ID;//��ӳ�����
	char date[11]; //�ݳ�����   ��ʽ2018-05-12 ����Ϊ10
	char time[6];//��ʼʱ��    ��ʽhh:mm  ����Ϊ5 24Сʱ��
	int ticketnum;//�ƻ��е�ǰ��Ʊ��
	int button;//�ƻ�����Ч��   ɾ�����ֵ��Ϊ0    ����ʱΪ0��ֵ����
	Ticket *ticket_head, *ticket_tail;//������
}data_plan;

typedef struct emmmm {//�˺�������
	char UID[NAME-6];//�˺ű��   8λ   �����޸�������һ�����
	char username[NAME];//�û���   4~14���ַ�/2~7������
	char password[PASSWORD+1];//��¼����  6~12
	user_types user_type;//�˺�����     �μ�enum user_typesö�ٶ���
	long long contributions;//       ҵ��\�����
	Record *record_head, *record_tail;//���ۼ�¼�������¼ ����
}data_account;

/////��ȡ���ۼ�¼ʱ����ҵ��      �������ۼ�¼ʱʵʱ����     ��������ʱ�������¼���
////////////////////////////////////////ʵ�嶨��\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


typedef struct linklist_program {//��Ŀ
	data_program element;
	struct linklist_program *pre,*next;
}Program;

typedef struct linklist_studio {//��ӳ��
	data_studio element;
	struct linklist_studio *pre, *next;
}Studio;

typedef struct linklist_plan {//�ݳ��ƻ�
	data_plan element;
	struct linklist_plan *pre, *next;
}Plan;

typedef struct linklist_account {//�˺�
	data_account element;
	struct linklist_account *pre, *next;
}Account;



typedef struct ctrl {//��������
	Program *program_head,*program_tail;
	Studio *studio_head,*studio_tail;
	Plan *plan_head,*plan_tail;
	Plan *plan_tem_head, *plan_tem_tail;
	Account *account_head,*account_tail;
	Key *key_head, *key_tail;
}List;

////////////////////////////////////////ȫ�ֱ���\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

extern List list;
extern data_account PRESENT;
extern struct tm *now;

/////////////////////////////////////////����\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int choice_judge(int i);//��ȡ�����¼�  �ж�ѡ��
void set_position(short x, short y);//���ù��λ��
void set_position(COORD position);//���ù��λ��
void SetColor(short foreColor, short backColor);//����������ɫ
void hide_cursor();//���ع��
void catch_cursor();//��ʾ���
POINT get_position();//�õ���ǰ���y����
int screen_clear(int order, int i, int change);/*������ĸ�������  i��ʾ��ǰ����ѡ�� Ĭ��Ϊ1
										����change��ı���  order��ʾ�����ѡ��  �������ص�ǰѡ����*/
int turn_page();//��ҳ��
int select_seat(Studio *p);//�б�λ��  �� -1   �� -2   �� 1    �� 2    ESC 0   �س�3  ����ֵ�ж��Ƿ��޸�
int select_seat(Plan *p, int limit);//��Ʊѡ��λ��  ESC 0   �س�3  ����ֵ��ʾ����Ʊ��  limit �������
void clear_seat(COORD position, char status);//�ı���λ��ʾ  COORD  ��ǰλ��   status ��λ״̬
void clear_ticket(COORD position, char status);//COORD  ��ǰλ��   status Ʊ״̬

//window.cpp

void show_welcome();//��ӭ����
void show_main();//������
void show_sign();//��¼����
void show_bye();//�ټ�����
void show_customer();//�˿�������
void show_manager();//��Ժ����������
void show_program();//��Ŀ��ѯ���������
void show_studio();//Ӱ����ѯ���������
void show_plan();//�ݳ��ƻ���ѯ������

void show_admin();//ϵͳ����Ա������
void show_account();//�˻��������
void show_account_type();//�˻�����ѡ�����

void show_conducter();//��ƱԱ�������

//welcom.cpp

void print_re();//��÷���
void print_examinput();//�Ƿ����뱨��
void go_on();//�����������
void exam_NULL(void *p, int choice);//��ָ�뱨��   0 malloc   1�ļ�
int enquiry(int i);//�ж��Ƿ���б��β���   i==1   enquiry   i==2 warnning
void print_ok(); //��ʾ�����ɹ�
void print_instruction(int i);//��ʾ����˵��
void print_planhead();//��ӡ�ݳ��ƻ���ͷ
//friendly.cpp

void process_all();//�������
void process_sign();//��¼����
void process_admin();//����Ա����
void process_account();//�˻��������

void process_manager();//��Ժ�������
void process_program();//��Ŀ��ѯ���������
void process_studio();//Ӱ����ѯ���������
void process_plan();//��ӳ�ƻ���ѯ���������
void process_plan_inquiry(Plan *head); //��ѯ�ݳ��ƻ�����

void process_conducter();//��ƱԱ����
void process_customer();//�˿͹���

void account_appeal();//�˺����߹���
//process.cpp

char *username_get(int judge);//�û����Ļ�ȡ
int sign_judge();//��½�ɹ����˻����͵��ж�
char *password_get(int judge);//�û�����Ļ�ȡ
char *get_string(int down, int up,int judge);//�ַ�����麯��    down~up   �ַ����ֽ�������
int get_num(int down, int up, int ndown, int nup);//��ȡ����    ���������   ��Χ[down,up]   λ��n[ndown,nup]
char *get_date();//���ڵĻ�ȡ���ж�
char *get_time();//ʱ��Ļ�ȡ���ж�
data_program get_program_infomation();//��ȡ��Ŀ��Ҫ��Ϣ  �����г�ʼ��
void program_viewer();//��Ŀ�����
void studio_viewer();//��ӳ���鿴��
void seat_changer(Studio *p);//���ӻ���λ�޸���
void plan_viewer(Plan *head);//�ݳ��ƻ������
void ticket_changer(Plan *p);//��Ʊ�����

void timer();//��ȡϵͳʱ��
void clean_plan_atFirst();//�����ڵ��ݳ��ƻ���ǹ���
void clean_plan();//��鲢��������ݳ��ƻ�

void password_change(char *obj, int i);//����ļ��ܽ��ܴ���1 :  ����     2:����
void play_bgm();
//sonfunction.cpp

void import_key();//����������Ϣ������
void import_account();//�����˺���Ϣ������
void import_program();//�����Ŀ��Ϣ������
void import_studio_and_seat();//�����ӳ������λ��Ϣ������
void import_plan_and_ticket();//�����ݳ��ƻ���Ϣ������
void import_plan_and_ticket_bin();// �����ݳ��ƻ���Ϣ������
//void import_plan_and_ticket_tem();//�����ѹ����ݳ��ƻ�������


void save_key();//����������Ϣ���ļ�
void save_program();//�����Ŀ��Ϣ���ļ�
void save_studio_and_seat();//�����ӳ������λ���ļ�
void save_plan_and_ticket();//�����ݳ��ƻ���Ʊ���ļ�
void save_plan_and_ticket(Plan *p); //׷���ݳ��ƻ���Ʊ����Ϣ���ļ�
void save_plan_and_ticket_bin();//�����ݳ��ƻ���Ʊ���������ļ�
void save_account();//�����˺�������Ϣ���ļ�
void save_account(Account *p);//׷���˺���Ϣ���ļ�

void modify_plan_and_ticket(Plan *p);//�ֲ���д�ļ�    ��button����


//filefunction.cpp

void initialize_linklist();//��ʼ������

long get_newkey(int judge);//����judge��Ӧ��������ֵ  1  ��Ӱ    2 ���   3���ֻ�     4�ݳ��ƻ�     5���ۼ�¼

Program *search_program(char *obj, int judge);//��ID�����Ʋ��Ҿ�Ŀ judge �����Ƿ�������Ʒ���
void add_program();//���Ӿ�Ŀ
void delete_program(Program *p);//����ID������ɾ����Ŀ
void print_program(Program *p , int i);////���ĳ��ӰƬ��Ϣ
void modify_program(Program *p);//�޸�ӰƬ��Ϣ

Studio *search_studio(char *obj, int judge);//��ID�����Ʋ��ҷ�ӳ��    judge �����Ƿ�������Ʒ���
void add_studio();//���ӷ�ӳ��
void print_studio(Studio *p);////��ӡ��ӳ������λ��Ϣ

//Seat *search_seat(char *obj);//���ݷ�ӳ����Ų�����λ
void delete_studio(Studio *p);//ɾ��ָ����ӳ��
void modify_studio(Studio *p);//�޸ķ�ӳ�����Ƽ���λ

void initialize_seat(Studio *p);//Ϊ�·�ӳ����ʼ����λ
void delete_seat(Studio *k);//ɾ����ӳ��ʱɾ������λ
void initialize_ticket(Plan *p);//Ϊ�ݳ��ƻ�����λ����Ʊ

void add_plan();//�����ݳ��ƻ�
void print_plan(Plan *p);//��ӡ�ݳ��ƻ���Ϣ
Plan *search_plan(long obj, int judge, Plan *head);//��plan_ID�����ݳ��ƻ�
void search_plan(char *obj, int choice, Plan *head);//������ID/��������ݳ��ƻ� 1plan_ID  2program  3studio
void delete_plan(Plan *p);//�����ݳ��ƻ�
void modify_plan(Plan *p);//�޸��ݳ��ƻ�
void sort_plan(Plan *head);//����ð�ݡ�������

void delete_ticket(Plan *p);//ɾ���ݳ��ƻ��µ�Ʊ
void print_ticket(Plan *p);//��ӡ�ݳ��ƻ���Ʊ�����
void modify_ticket(Plan *p);//��Ʊ��Ʊ

void print_account(Account *p);//��ӡ�˺���Ϣ
void add_account(int num);//�����˻���Ϣ
void modify_account(Account *p);//�޸��˻���Ϣ
void delete_account();//ɾ���˻���Ϣ
Account* search_account(char *obj, int judge);//�����˻���Ϣ
void draw_ticket(Plan *p, Ticket *t);//��һ��Ʊ
//Linklist.cpp

void import_all();//�����˻���Ϣ
void initialize();//��ʼ��׼��
void initialize_present();//��ʼ����ǰ�˻�
void initialize_window();//��ʼ����ʾ����

//initialize.cpp
void show_register();
int save_invitation_code(char *obj);
void process_register();//�Ƚ� �� �ֲ��޸�������  //����ֵΪ�ȶԽ��




//void ShowListByPage(int listSize);
//int listSize();
//List.h