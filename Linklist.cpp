#include"stdafx.h"
#include"statements.h"

void initialize_linklist() {//��ʼ������
	list.account_head = (Account *)malloc(sizeof(Account));
	list.program_head = (Program *)malloc(sizeof(Program));
	list.studio_head = (Studio *)malloc(sizeof(Studio));
	list.plan_head = (Plan *)malloc(sizeof(Plan));
	list.plan_tem_head = (Plan *)malloc(sizeof(Plan));
	//list.seat_head = (Seat *)malloc(sizeof(Seat));
	//list.ticket_head = (Ticket *)malloc(sizeof(Ticket));
	//list.record_head = (Record *)malloc(sizeof(Record));
	list.key_head = (Key *)malloc(sizeof(Key));
	list.account_head->next = list.account_head->pre = NULL;
	list.program_head->next = list.program_head->pre =  NULL;
	list.studio_head->next =list.studio_head->pre = NULL;
	list.plan_head->next = list.plan_head->pre = NULL;
	list.plan_tem_head->next = list.plan_tem_head->pre = NULL;
	//list.seat_head->next = list.seat_head->pre = NULL;
	//list.ticket_head->next = list.ticket_head->pre = NULL;
	//list.record_head->next = list.record_head->pre = NULL;
	list.key_head->next = list.key_head->pre = NULL;
	list.account_tail = list.account_head;
	list.program_tail = list.program_head;
	list.studio_tail = list.studio_head;
	list.plan_tail = list.plan_head;
	list.plan_tem_tail = list.plan_tem_head;
	//list.seat_tail = list.seat_head;
	//list.ticket_tail = list.ticket_head;
	//list.record_tail = list.record_head;
	list.key_tail = list.key_head;
}

//////////////////////////////////////////key

long get_newkey(int type) {//����judge��Ӧ��������ֵ    ������������¼
	int flag = 0;// 1  ��Ӱ    2 ���   3���ֻ�     4�ݳ��ƻ�     5���ۼ�¼   6Ʊ   7�˺�UID
	Key *p = list.key_head->next;
	for (p; p; p = p->next) {
		if (type == p->type) {
			p->key++; flag = 1; break;
		}
	}
	if (flag == 0) {
		print_re();
	}
	return p->key;
}

//////////////////////////////////////////program

void add_program() {//���Ӿ�Ŀ
	Program *p = (Program *)malloc(sizeof(Program));
	exam_NULL(p, 0);
	p->element = get_program_infomation();//��Ŀ��Ϣ��ȡ
	if (enquiry(1)) {
		printf("������Ϣ����ΪĬ��ֵ\n������Ҫ��ǵ��޸�\n");
		p->next = list.program_tail->next;
		p->pre = list.program_tail;
		list.program_tail->next = p;
		list.program_tail = p;
		save_program();
		list.program_head->element.cost += 1;
		save_key();
		print_ok();
	}
	else {
		free(p);
		printf("������ȡ��\n"); rewind(stdin);
	}
}

Program *search_program(char *obj,int judge) {//��ID�����ֲ��Ҿ�Ŀ  judge �����Ƿ�������Ʒ���
	int flag = 0;
	Program *p = list.program_head->next;
	for (p; p; p = p->next) {
		if (strcmp(p->element.program_ID, obj) == 0 || strcmp(p->element.program_name, obj) == 0) {
			flag = 1;//�ҵ�
			break;
		}
	}
	if (flag)
		return p;
	if (judge&&flag == 0) {
		printf("û�������ĿŶ\n");
		for (p = list.program_head->next; p; p = p->next) {
			if (strstr(p->element.program_ID, obj) != NULL || strstr(p->element.program_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("��  "); printf("Ҳ�������ҵ��ǣ�\n"); Sleep(1000);
					flag = 1;
				}
				printf("%s  %s\n", p->element.program_ID, p->element.program_name);
			}
		}
		if(flag==1)printf("��ȷ�Ϻ����²���\n");
	}return NULL;
}

void delete_program(Program *p) {//����ID������ɾ����Ŀ
	if (p) {
		if (enquiry(2)) {
			p->pre->next = p->next;
			if (p->next)//p��Ϊ���һ��
				p->next->pre = p->pre;
			free(p);
			save_program();
			list.program_head->element.cost -= 1;
			print_ok();
		}
		else {
			printf("ɾ����ȡ��\n"); rewind(stdin);
		}
	}
}

void print_program(Program *p , int i) {//���ĳ����Ŀ��Ϣ    i  �����Ƿ�����
	if (p) {
		if(i)system("cls");
		char rating[8],type[7],person[11];
		switch (p->element.program_rating) {
		case 1:strcpy(rating, "Child"); break;
		case 2:strcpy(rating, "Teen"); break;
		case 3:strcpy(rating, "Adult"); break;
		default:
			print_re();
		}
		switch (p->element.program_type) {
		case 1:strcpy(type, "��Ӱ"); strcpy(person,"����"); break;
		case 2:strcpy(type, "���"); strcpy(person, "����"); break;
		case 3:strcpy(type, "���ֻ�"); strcpy(person, "ָ��"); break;
		default:
			print_re();
		}
		printf("\n");
		printf("	==================================================================\n");
		printf("	||								||\n");
		printf("	||%s����:%-15s		%s:%-12s	||\n",type, p->element.program_name,person, p->element.director);
		printf("	||								||\n");
		printf("	||����:%12s	%-14s	ʱ��:%dmin		||\n", p->element.performer[0], p->element.performer[1], p->element.duration);
		printf("	||								||\n");
		printf("	||��Ŀ��ǩ:%-s                 ����:%-8s	Ʊ��:%-5d	||\n", p->element.label, p->element.area, p->element.price);
		printf("	||								||\n");
		printf("	||��ӳ�ȼ�:%-8s		����:%-10s			||\n", rating, p->element.language);
		printf("	==================================================================\n");
		rewind(stdin);
	}
}

void modify_program(Program *p) {//�޸ĵ�Ӱ��Ϣ
	if (p) {
		print_program(p,1);
		printf("��ѡ������Ҫ���ĵ�\n");
		printf("1.Ʊ�� 2.��ӳ�ȼ� 3.ʱ�� 4.���� \n5.���� 6.��Ŀ��ǩ 7.���� 8.����\n");
		int choice = 0; char *str; rewind(stdin);
		data_program tem=p->element;
		choice = get_num(1, 8, 1, 1);
		switch (choice) {
		case 1:printf("�������µ�Ʊ��(5~100):"); choice = get_num(5, 100, 1, 3); tem.price = choice; break;
		case 2:printf("�������ӳ�ȼ�(1~3):"); choice = get_num(1, 3, 1, 1); tem.program_rating = (program_ratings)choice; break;
		case 3:printf("������ӰƬʱ��(1~600):"); choice = get_num(1, 600, 1, 3); tem.duration = choice; break;
		case 4:printf("������ӰƬ����(2������):"); str = get_string(4, 4, 2); strcpy(tem.area, str); free(str); break;
		case 5:printf("������ӰƬ����(���14���ַ�):"); str = get_string(1, 15, 0); strcpy(tem.language, str); free(str); break;
		case 6:printf("������ӰƬ��ǩ(2������):"); str = get_string(4, 4, 2); strcpy(tem.label, str); free(str); break;
		case 7:if (p->element.program_type != PROGRAM_concert) {
			printf("�������һλ��������(���7������):"); str = get_string(1, 14, 0); strcpy(tem.performer[0], str); free(str);
			printf("�Ƿ��������ڶ�����?(0/1):"); rewind(stdin); if (choice = get_num(0, 1, 1, 1)) {
				printf("������ڶ�λ��������(���7������):");
				str = get_string(1, 14, 0); strcpy(tem.performer[1], str); free(str);
			}
		}else {
			printf("���������ݵ���������(���7������)��"); str = get_string(1, 14, 0); strcpy(tem.performer[0], str); free(str);
			   }break;
		case 8:printf("�����뵼������(���7������):"); str = get_string(1, 14, 0); strcpy(tem.director, str); free(str); break;
		default:
			break;
		}
		if (enquiry(1)) {
			p->element = tem;
			save_program();
			print_ok();
		}
		else {
			printf("�޸���ȡ��\n"); rewind(stdin);
		}
		printf("�Ƿ�����޸�?(0/1):");
		if (get_num(0, 1, 1, 1)) {
			modify_program(p);
		}
	}
}

///////////////////////////////////////////studio

void add_studio() {//���ӷ�ӳ��
	Studio *p = (Studio *)malloc(sizeof(Studio));
	exam_NULL(p, 0);
	printf("\n�������µķ�ӳ�����(4~6λ����):\n"); rewind(stdin);
	char *str = get_string(4, 6, 1);
	while (search_studio(str, 0)) {
		printf("�ñ���ѱ�ʹ�ã�����������\n"); rewind(stdin);free(str);
		str = get_string(4, 6, 1);
	}
	strcpy(p->element.studio_ID, str); free(str);
	printf("�������ӳ������(7����������):\n"); rewind(stdin);
	str = get_string(1,14,0);
	while (search_studio(str, 0)) {
		printf("�������ѱ�ʹ�ã�����������\n"); rewind(stdin); free(str);
		str = get_string(1, 14, 1);
	}
	strcpy(p->element.studio_name, str); free(str);
	printf("�������Ӱ����λ������(5~12):");
	int choice = get_num(5, 12, 1, 2);
	p->element.seatx=choice;
	printf("�������Ӱ����λ������(10~25):");
	choice = get_num(10, 25, 2, 2);
	p->element.seaty = choice;
	p->element.seatsum = p->element.seatx*p->element.seaty;//�����ʼ����Ŀ�����λ
	if (enquiry(1)) {
		p->next = list.studio_tail->next;
		p->pre = list.studio_tail;
		list.studio_tail->next = p;
		list.studio_tail = p;
		initialize_seat(p);
		save_studio_and_seat();
		print_ok();
		printf("������λ����Ϊ����״̬\n������Ҫ��ǵ��޸�\n");
		list.studio_head->element.seatx++;
	}
	else {
		free(p);
		printf("��ӳ��������ȡ��\n");
	}
}

Studio *search_studio(char *obj,int judge) {//��ID�����Ʋ��ҷ�ӳ��  judge  �����Ƿ�������Ʒ���
	Studio *p=list.studio_head->next;
	int flag = 0;
	for (p; p; p = p->next) {
		if (strcmp(p->element.studio_ID, obj) == 0 || strcmp(p->element.studio_name, obj) == 0) {
			flag = 1; break;
		}
	}
	if (flag) {
		return p;
	}
	if (judge&&flag == 0) {
		printf("�÷�ӳ��������Ŷ\n");
		for (p = list.studio_head->next; p; p = p->next) {
			if (strstr(p->element.studio_ID, obj) != NULL || strstr(p->element.studio_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("��  "); Sleep(1000); printf("Ҳ����Ҫ�ҵ���\n"); rewind(stdin); flag = 1;
				}printf("%s    %s\n",p->element.studio_ID,p->element.studio_name);
			}
		}if (flag)printf("��ȷ�Ϻ����²���\n");
	}
	return NULL;
}

void delete_studio(Studio *p) {//ɾ��ָ����ӳ��
	if (p) {
		if(enquiry(2)){
			p->pre->next = p->next;
			if (p->next)
				p->next->pre = p->pre;
			delete_seat(p);//ɾ���÷�ӳ��������λ
			free(p);
			list.studio_head->element.seatx--;
			save_studio_and_seat();
			print_ok();
		}
		else {
			printf("ɾ����ȡ��\n"); rewind(stdin);
		}
	}
}

void print_studio(Studio *p) {//��ӡ��ӳ������λ��Ϣ
	if (p) {
		int i, j, cnt = 0;//cnt ���������λ��
		system("cls");
		Seat *k = p->element.seat_head->next;
		printf("\n");
		printf("	====================================================================\n");
		printf("			��ӳ����ţ�%s	���ƣ�%s\n\n",p->element.studio_ID,p->element.studio_name);
		printf("			���ʾ������λ  ���ʾ����λ   ��λ %d x %d\n\n",p->element.seatx,p->element.seaty);
		printf("			�q�������������������������������������r\n");
		printf("					��ӫĻ\n\n");
		for (i = 1; i <= p->element.seatx; i++) {
			if(p->element.seaty>30)
				printf("		");
			else if(p->element.seaty>21)
				printf("		   ");
			else if(p->element.seaty>15)
				printf("			");
			else if(p->element.seaty<=15)
				printf("			    ");
			for (j = 1; j <= p->element.seaty; j++) {
				switch (k->seat_condition) {
				case 0:printf("  "); break;
				case 1:printf("��"); cnt++; break;
				case 2:printf("��"); cnt++; break;
				case 9:printf("��"); break;
				default:
					print_re(); break;
				}
				k = k->next;
			}printf("\n");
		}if(cnt == p->element.seatsum )printf("\n\n			����ӳ������%d�ſ�����λ\n", cnt);
		else { printf("��λУ�Գ�������\n"); print_re(); }
	}
}

void modify_studio(Studio *p) {//�޸�Ӱ����Ϣ����λ���
	if (p) {
		print_studio(p);
		printf("��ѡ��Ҫ�޸ĵģ�\n");
		printf("1.��ӳ������ 2.��λ���� 3.��λ���� 4.��λ����\n");//2.��λ���� 3.��λ����
		int choice = get_num(1, 4, 1, 1); char *str = NULL; data_studio tem=p->element;
		switch (choice) {
		case 1:printf("�������µķ�ӳ������"); str = get_string(1, 14, 0); strcpy(tem.studio_name, str); free(str); break;
		case 2:printf("�������µ�����(5~12)��"); choice = get_num(5, 12, 1, 2); tem.seatx = choice; break;
		case 3:printf("�������µ�����(10~25)��"); choice = get_num(10, 25, 2, 2); tem.seaty = choice; break;
		case 4:print_instruction(1); seat_changer(p); break;
		}if (choice != 4) {
			if (enquiry(1)) {
				if (tem.seatx != p->element.seatx || tem.seaty != p->element.seaty) {//��ʼ����λ
					if(tem.seatx > p->element.seatx || tem.seaty > p->element.seaty)printf("��Ĭ�������л�������λ\n");
					int i, j; Seat *k = p->element.seat_head->next;

					//�������� ����

					//char seat[13][26] = { 0 }; 
					//for (i = 1; i <= p->element.seatx; i++) {
					//	for (j = 1; j <= p->element.seaty; j++) {//¼��ԭ����λ
					//		seat[i][j] = k->seat_condition; k = k->next;
					//	}
					//}
					//delete_seat(p);//ɾ��ԭ����λ
					//int ID = atoi(p->element.studio_ID); Seat *q = NULL;
					//p->element.seat_head = (Seat *)malloc(sizeof(Seat)); exam_mallocX(p->element.seat_head);
					//p->element.seat_tail = p->element.seat_head;
					//p->element.seat_head->pre = p->element.seat_tail->next = NULL;//��ʼ����λ����
					//for (i = 1; i <= tem.seatx; i++) {
					//	for (j = 1; j <= tem.seaty; j++) {
					//		q = (Seat *)malloc(sizeof(Seat));
					//		exam_mallocX(q);
					//		q->seatx = i; q->seaty = j; q->stduio_ID = ID; q->seat_condition = (seat_conditions)seat[i][j];
					//		q->next = p->element.seat_tail->next; q->pre = p->element.seat_tail; 
					//		p->element.seat_tail->next = q; p->element.seat_tail = q;
					//	}
					//}//����ת��Ϊ����
					//tem.seat_head = p->element.seat_head; tem.seat_tail = p->element.seat_tail;

					///////////�����ʵʱ����    �ڴ����
					int tID = atoi(p->element.studio_ID);
					k = p->element.seat_head->next;
					if (tem.seatx > p->element.seatx){//��������
						for (i = p->element.seatx + 1; i <= tem.seatx; i++) {
							for (j = 1; j <= p->element.seaty; j++) {//�����½ڵ�
								if (i > p->element.seatx || j > p->element.seaty) {
									Seat *q = (Seat *)malloc(sizeof(Seat));
									q->seatx = i; q->seaty = j; q->seat_condition = (seat_conditions)0; q->stduio_ID = tID;
									q->next = p->element.seat_tail->next; q->pre = p->element.seat_tail;
									p->element.seat_tail->next = q; p->element.seat_tail = q;
								}
							}
						}
					}
					else if (tem.seaty > p->element.seaty) {//��������
						for (i = 1; i <= p->element.seatx*p->element.seaty; i++) {
							if(i%p->element.seaty==0)
								for (j = p->element.seaty + 1; j <= tem.seaty; j++) {
									Seat *q = (Seat *)malloc(sizeof(Seat));
									q->seatx = (i - 1) / p->element.seaty + 1; q->seaty = j; q->seat_condition = (seat_conditions)0; q->stduio_ID = tID;
									q->next = k->next; q->pre = k;
									k->next = q; k = q;
							}k = k->next;
						}
					}
					else if (tem.seaty < p->element.seaty) {//��������
						i = 1;
						while ( k ) {
							if (i%tem.seaty == 0) {
								j = p->element.seaty - tem.seaty;
								k = k->next;
								while (j--) {
									if (k) {
										Seat *dead = k;
										k->pre->next = k->next;
										if (k->next) {
											k->next->pre = k->pre;
										}k = k->next;
										free(dead); i = 1;
									}
								}
							}
							if(k)k = k->next; i++;
						}
					}
					else if (tem.seatx < p->element.seatx) {//��������
						for (i = 1, k; i <= tem.seatx*p->element.seaty; i++, k = k->next);
						while (k) {
							Seat *dead = k;
							k->pre->next = k->next;
							if (k->next) {
								k->next->pre = k->pre;
							}
							k = k->next;
							free(dead);
						}
					}
				}
				p->element = tem;
				save_studio_and_seat();
				print_ok();
			}	
			else {
				printf("�޸���ȡ��\n");
			}
		}
	}
}

/////////////////////////////////////////////seat

void initialize_seat(Studio *p) {//Ϊ�·�ӳ����ʼ����λ
	p->element.seat_head = (Seat *)malloc(sizeof(Seat));
	exam_NULL(p->element.seat_head, 0);
	p->element.seat_head->pre = p->element.seat_head->next = NULL;//�������ʼ��
	p->element.seat_tail = p->element.seat_head;
	int i, j;
	for (i = 1; i <= p->element.seatx; i++) {
		for (j = 1; j <= p->element.seaty; j++) {
			Seat *k = (Seat *)malloc(sizeof(Seat));
			exam_NULL(k ,0);
			k->seatx = i, k->seaty = j, k->stduio_ID = atoi(p->element.studio_ID);
			k->seat_condition = (seat_conditions)1;
			k->next = p->element.seat_tail->next;
			k->pre = p->element.seat_tail;
			p->element.seat_tail->next = k;
			p->element.seat_tail = k;
		}
	}
}

//Seat *search_seat(char *obj) {//���ݷ�ӳ�����������鿴��λ��Ϣ
//	int flag = 0;
//	Studio *k = search_studio(obj);
//	if (k) {
//		Seat *p = k->element.seat_head->next;
//		for (p; p; p = p->next) {
//			if (p->stduio_ID == atoi(obj)) {
//				flag = 1;
//				return p;
//			}
//		}
//		printf("");
//		return NULL;
//	}
//}

void delete_seat(Studio *k) {//ɾ����ӳ��ʱɾ������λ
	if (k) {
		Seat *dead = k->element.seat_head;
		Seat *p = dead->next;
		while (p) {
			free(dead);
			dead = p;
			p = p->next;
		}free(dead);
	}
}

////////////////////////////////////////////plan

void add_plan() {//�����ݳ��ƻ�
	Plan *p = (Plan *)malloc(sizeof(Plan)); char *tem;
	exam_NULL(p, 0);
	p->element.button = 1;
	p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(p->element.ticket_head, 0);
	p->element.ticket_head->next = p->element.ticket_head->pre = NULL;
	p->element.ticket_tail = p->element.ticket_head;
	char *str = NULL; Program *k = NULL; Studio *s = NULL; int flag = 1;
	p->element.plan_ID = get_newkey(PLAN_KEY);
	printf("\n��Ϊ�ݳ��ƻ�����IDΪ %ld\n", p->element.plan_ID);
	printf("�������ݳ���Ŀ��ID������:");
	do {
		if (flag == 0)printf("�þ�Ŀ�����ڣ�\n���������룺");
		str = get_string(1, 30, 0);
	} while (((k = search_program(str, 0)) == NULL)&&(free(str),flag=0,1));
	flag = 1;
	strcpy(p->element.program_name , k->element.program_name);
	printf("���������ݾ�Ŀ��Ӱ�����ƻ�ID:");
	do {
		if (flag == 0)printf("�÷�ӳ�������ڣ�\n���������룺");
		str = get_string(1, 14, 0);
	} while (((s = search_studio(str, 0)) == NULL) && (free(str), flag=0,1));
	p->element.studio_ID = atoi(s->element.studio_ID);
	p->element.ticketnum = s->element.seatsum;
	printf("�þ�Ŀ�ϼ����ڣ�%s  �¼����ڣ�%s\n",k->element.start_date,k->element.end_date);
	printf("�������ݳ�����(year-month-day):");
	do {
		if (flag == 0)printf("�ݳ��ƻ����Ŀ�ϼ����ڲ���\n����������:");
		flag = 1;
		tem = get_date();
		if (strcmp(tem, k->element.start_date) < 0 || strcmp(k->element.end_date, tem) < 0) { flag = 0; }
		else { strcpy(p->element.date, tem); }free(tem);
	} while (flag == 0);
	printf("�������ݳ���ʼʱ��(24Сʱ��)(hour:min):");
	tem = get_time(); strcpy(p->element.time, tem); free(tem);
	if (enquiry(1)) {
		initialize_ticket(p);
		p->next = list.plan_tail->next; p->pre = list.plan_tail;
		list.plan_tail->next = p; list.plan_tail = p;
		save_key();
		save_plan_and_ticket(p);
		print_ok();
		printf("���Զ���������Ʊ\n");
	}
	else {
		printf("�ݳ��ƻ�������ȡ��\n");
	}
}

void search_plan(char *obj, int choice, Plan *head) {//������ID/��������ݳ��ƻ� 1plan_ID  2program  3studio
	Plan *p = head->next;
	long objnum = atol(obj); Program *k = search_program(obj, 0); Studio *r = search_studio(obj, 0);
	if ((choice == 2 || choice ==3) && k == NULL && r == NULL) { if (choice == 2 && k == NULL) { search_program(obj, 1); } if (choice == 3 && r == NULL) { search_studio(obj, 1); } return; }
	char program_name[40]; if(k)strcpy(program_name, k->element.program_name);
	int studio_ID, flag = 0, judge = 0; if(r) studio_ID = atoi(r->element.studio_ID);
	if (choice == 1) {
		p = search_plan(objnum , 1,head);
		if (p) { print_planhead(); print_plan(p);}//judge��ʶ�Ƿ������
	}
	else {
		for (p; p; p = p->next) {
			//if (p->element.button == 0) { continue; }//button ����
			flag = 0;
			switch (choice) {
			case 2:if (strcmp(p->element.program_name, program_name) == 0)flag = 1; break;
			case 3:if (p->element.studio_ID == studio_ID)flag = 1; break;
			case 4:if (strcmp(p->element.date, obj) == 0)flag = 1; break;
			}
			if (flag) { if (judge == 0) { print_planhead(); } print_plan(p); judge = 1; }
		}
		if(judge == 0)printf("û���������ݳ��ƻ�Ӵ\n");
	}
}

Plan *search_plan(long obj, int judge, Plan *head) {//��plan_ID�����ݳ��ƻ�  judge�����Ƿ�������Ʒ���
	Plan *p = head->next;
	int flag = 0;
	for (p; p; p = p->next) {
		if (p->element.plan_ID == obj) {
			flag = 1; break;
		}
	}
	if (flag)return p;
	if (judge && flag == 0) {
		printf("û���������ݳ��ƻ�Ӵ\n"); 
		int flagnum = 0; char tem[10],objstr[10];
		sprintf(objstr, "%ld", obj);
		for (p = head->next; p; p = p->next) {
			sprintf(tem, "%ld", p->element.plan_ID);
			if (strstr(tem, objstr) != NULL) {
				if (flagnum == 0) { printf("��  "); Sleep(500); printf("��Ҳ��Ҫ�ҵ���\n"); Sleep(1000); flagnum = 1; }
				printf("%ld\n", p->element.plan_ID);
			}
		}if (flagnum) {
			printf("��ȷ�Ϻ����²���\n"); rewind(stdin);
		}
	}
	return NULL;
}

void delete_plan(Plan *p) {//���ط�ӳ�ƻ���Ʊ
	if (p) {
		printf("��Ҫɾ���ļƻ��ǣ�\n");
		print_planhead();
		print_plan(p);
		if (enquiry(2)) {
			p->element.button = 2;//   0����      1��Ч
			save_plan_and_ticket();
			p->pre->next = p->next; 
			if(p->next)
				p->next->pre = p->pre;
			//p->next = list.plan_tem_tail->next; p->pre = list.plan_tem_tail;
			//list.plan_tem_tail->next = p; list.plan_tem_tail = p;//�ƶ�p��plan_tem����
			delete_ticket(p);
			free(p);
			print_ok();
		}
		else {
			printf("ɾ����ȡ��\n");
		}
	}
}

void print_plan(Plan *p) {//��ӡ�ݳ��ƻ���Ϣ
	if (p) {
		printf("    %ld    %-20s%8d	%3d	%3d %12s%8s\n\n", p->element.plan_ID, p->element.program_name, p->element.studio_ID,\
		p->element.ticketnum,p->element.ticket_head->price,p->element.date,p->element.time);//p->element.ticket_head->price��ǰʣ��Ʊ��
	}
	else {
		printf("û���������ݳ��ƻ�Ӵ\n");
	}
}

void modify_plan(Plan *p) {//�޸��ݳ��ƻ���Ϣ
	data_plan tem = p->element;char *str = NULL;
	printf("1.�ݳ����� 2.�ݳ�ʱ�� 3.��ӳ��\n��ѡ��");
	int choice = get_num(1, 3, 1, 1), flag = 1;
	if (choice == 1) {//�ݳ�����
		Program *k = search_program(p->element.program_name, 0); if (k == NULL)print_re();
		printf("�þ�Ŀ�ϼ����ڣ�%s  �¼����ڣ�%s\n", k->element.start_date, k->element.end_date);
		printf("�������ݳ�����(year-month-day):");
		do {
			if (flag == 0)printf("�ݳ��ƻ����Ŀ�ϼ����ڲ���\n����������:");
			flag = 1;
			str = get_date();
			if (strcmp(str, k->element.start_date) < 0 || strcmp(k->element.end_date, str) < 0) { flag = 0; }
			else { strcpy(tem.date, str); }free(str);
		} while (flag == 0);
	}
	else if (choice == 2) {//�ݳ�ʱ��
		printf("�������ݳ���ʼʱ��(24Сʱ��)(hour:min):");
		str = get_time(); strcpy(tem.time, str); free(str);
	}
	if (enquiry(1)) {
		p->element = tem;
	}
	else {
		printf("�޸���ȡ��\n");
	}
	if (choice == 3) {//��ӳ��   ͬʱ��������Ʊ
		printf("���������ݾ�Ŀ��Ӱ�����ƻ�ID:");
		Studio *s = NULL; 
		do {
			if (flag == 0)printf("�÷�ӳ�������ڣ�\n���������룺");
			str = get_string(1, 14, 0);
		} while (((s = search_studio(str, 0)) == NULL) && (free(str), flag = 0, 1));
		tem.studio_ID = atoi(s->element.studio_ID);
		tem.ticketnum = s->element.seatsum;
		printf("�޸ķ�ӳ����ɾ����ǰ����Ʊ����������\n");
		if (enquiry(2)) {
			delete_ticket(p);
			p->element = tem;
			p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(p->element.ticket_head, 0);
			p->element.ticket_head->next = p->element.ticket_head->pre = NULL;
			p->element.ticket_tail = p->element.ticket_tail;
			initialize_ticket(p);
		}else{
			printf("�޸���ȡ��\n");
		}
	}
}

void sort_plan(Plan *head) {//����ð������
	Plan *p = head->next; data_plan t; int flag = 0, i = 1;
	for (i; i <= head->element.ticketnum - 1; i++) {
		for (p; p->next; p = p->next) {
			flag = 0;
			if (strcmp(p->element.date, p->next->element.date) > 0) {
				t = p->element;
				p->element = p->next->element;
				p->next->element = t;
				flag = 1;
			}
		}
		p = head->next;
		if (flag == 0)break;//ð�����������Ż�
	}
}

///////////////////////////////////////ticket

void initialize_ticket(Plan *p) {//Ϊ�ݳ��ƻ�����λ����Ʊ
	char str[20]; sprintf(str, "%s", p->element.program_name);
	int cnt = 0, price = search_program(str, 0)->element.price;
	sprintf(str, "%d", p->element.studio_ID);
	Studio *k = search_studio(str,0);
	Seat *q = k->element.seat_head->next;
	for (q; q; q = q->next) {
		if (q->seat_condition != 1 && q->seat_condition != 2) {//2����
			continue;
		}
		Ticket *r = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(r, 0);
		r->ticket_ID = get_newkey(TICKET_KEY);	save_key();
		r->seatx = q->seatx; r->seaty = q->seaty;
		r->price = price;
		r->ticket_status = (ticket_statuses)TICKET_available;
		r->next = p->element.ticket_tail->next; r->pre = p->element.ticket_tail;
		p->element.ticket_tail->next = r; p->element.ticket_tail = r;
		cnt++;
	}if (cnt != k->element.seatsum) { printf("��λ��Ʊ��У�����\n"); print_re(); }
}

void delete_ticket(Plan *p) {//ɾ���ݳ��ƻ��µ�Ʊ
	if (p) {
		Ticket *dead = p->element.ticket_head;
		Ticket *k = dead->next;
		while (k) {
			free(dead);
			dead = k;
			k = k->next;
		}free(dead);
	}
}

void print_ticket(Plan *p) {//��ӡƱ�����   ��/��δ��  ��/�����۳�  x��λ��
	char seat[100][100] = { 0 }; char ID[12] ;
	sprintf(ID, "%d", p->element.studio_ID);
	Ticket *t = p->element.ticket_head->next;
	Studio *k = search_studio(ID, 0);
	Seat *s = k->element.seat_head->next;
	for (s; s; s=s->next) {
		if (s->seat_condition == SEAT_available || s->seat_condition == SEAT_private)
			seat[s->seatx][s->seaty] = s->seat_condition;
		else if(s->seat_condition == 9)//��
			seat[s->seatx][s->seaty] = 9;
	}//������λ1   ����2  ����λ0   ��9
	for (t; t; t = t->next) {
		if (t->ticket_status == TICKET_sold)
			seat[t->seatx][t->seaty] ==1? seat[t->seatx][t->seaty] = -1: seat[t->seatx][t->seaty] = -2;
			//����λ��Ʊ Ϊ1��2  ����λ��Ʊ Ϊ-1    ����λ0   ����λ9
	}
	system("cls");
	printf("\n\n		=============================================================\n");
	printf("		   �ݳ��ƻ�ID:%-12ld�ݳ���:%-15sʣ��Ʊ��%d    \n		   �ݳ�����:%-14s��ʼʱ��:%-14s\n\n",p->element.plan_ID,k->element.studio_name\
		,p->element.ticket_head->price,p->element.date,p->element.time);
	printf("			��/���ѡ  ��/������  ������λ  ��λ %d x %d\n\n", k->element.seatx, k->element.seaty);
	printf("			�q�������������������������������������r\n");
	printf("					��ӫĻ\n\n");
	for (int i = 1; i <= k->element.seatx; i++) {
		if (k->element.seaty>30)
			printf("		");
		else if (k->element.seaty>21)
			printf("		   ");
		else if (k->element.seaty>15)
			printf("			");
		else if (k->element.seaty <= 15)
			printf("			    ");
		for (int j = 1; j <= k->element.seaty; j++) {
			switch (seat[i][j]) {
			case -2:printf("��"); break;
			case -1:printf("��"); break;
			case 0:printf("  "); break;
			case 1:printf("��"); break;
			case 2:printf("��"); break;
			case 9:printf("��"); break;
			}
		}
		printf("\n");
	}
}

void modify_ticket(Plan *p) {//��Ʊ��Ʊ
	system("cls"); int flag = 0;
	char ID[15]; sprintf(ID, "%d", p->element.studio_ID);
	Studio *s = search_studio(ID, 0); Ticket *t = p->element.ticket_head->next;
	print_ticket(p);
	printf("������������ѡ��λ��������(�ո����):");
	int x = get_num(1, s->element.seatx, 1, 2);
	int y = get_num(1, s->element.seaty, 1, 2);
	for (int i = 1; i <= (x - 1) *(s->element.seaty - 1) + y; i++) t = t->next;
	if (t->ticket_status != TICKET_available)printf("��Ǹ������ѡ���λ��\n");
	else if (enquiry(1)) { t->ticket_status = TICKET_sold; print_ok(); }
}

void draw_ticket(Plan *p,Ticket *t) {//��һ��Ʊ
	system("cls"); char ID[15]; sprintf(ID, "%d", p->element.studio_ID);
	Studio *s = search_studio(ID, 0);
	printf("	==============================================================\n");
	printf("	||�m �� �� .o�� �m  �m.. ��                �� �� �� �� �� �� Ժ||\n");
	printf("	||�m�������m ��   �� .�m �mo�y�z�|�}                           ||\n");
	printf("	||����   �� /��\\ /��\\ �m �� �m�m �� �m   %-22s  ||\n",p->element.program_name);
	printf("	|| ���|�}�~�����������~�}�|�z�y���m                           ||\n");
	printf("	||                                                          ||\n");
	printf("	||       %15s\b\b%s         �� �� �� ��            ||\n",s->element.studio_name,"��ӳ��");
	printf("	||%10s     %6s    %d ��  %d ��                       ||\n",p->element.date,p->element.time,t->seatx,t->seaty);
	printf("	=============================================================");
}

///////////////////////////////////////account

void add_account(int num)
{
	int flag = 0, tag = 0;
	char *str = NULL, *str2 = NULL;
	Account *p = (Account *)malloc(sizeof(Account));
	exam_NULL(p, 0);
	p->element.user_type = (user_types)num;
	sprintf(p->element.UID, "%ld", get_newkey(ACCOUNT_KEY));
	printf("�ѷ���UIDΪ��%s\n", p->element.UID);
	printf("��������Ҫ��ӵ��û���:\n");
	str = get_string(4, 14, 0);
	do {
		flag = 0;
		if (search_account(str, 0)) {
			flag = 1;
			printf("�û����Ѵ��ڣ����������룺\n");
			str = get_string(4, 14, 0);
		}
	} while (flag);
	strcpy(p->element.username, str);

	free(str);
	do {
		printf("\n��������Ҫ��ӵ�����: \n");
		str = password_get(1);
		printf("\n��ȷ�����룺\n");
		str2 = password_get(1);
		if (!strcmp(str, str2)) {
			printf("�������óɹ���\n");
			strcpy(p->element.password, str);
		}
		else {
			tag = 1;
			printf("�������벻һ��Ŷ,���������룡\n");
		}
	} while (tag);
	free(str);
	free(str2);
	p->element.contributions = 0;
	p->element.record_head = (Record *)malloc(sizeof(Record));
	p->element.record_head->pre = p->element.record_head->next = NULL;//�������ʼ��
	p->element.record_tail = p->element.record_head;
	if (enquiry(1)) {
		printf("������Ϣ����ΪĬ��ֵ\n������Ҫ��ǵ��޸�\n");
		p->next = list.account_tail->next;
		p->pre = list.account_tail;
		list.account_tail->next = p;
		list.account_tail = p;
		save_account(p);
		list.program_head->element.cost += 1;
		save_key();
		print_ok();
	}
	else {
		free(p);
		printf("������ȡ��\n"); rewind(stdin);
	}
}

void modify_account(Account *p)
{
	int flag = 0, tag = 0, count = 1, count1 = 1, flagnum = 1;
	char *str = NULL, *str2 = NULL;
	if (p) {
		printf("\t\t                   �޸���Ϣ      \n");
		printf("\t\t           �û����밴1�������밴2\n");
		int choice = 0;
		choice = get_num(1, 2, 1, 1);
		data_account t = p->element;
		switch (choice) {
		case 1: {
			printf("�������µ��û���:");
			str = get_string(4, 14, 0);
			do {
				flag = 0;
				if (search_account(str, 0)) {
					flag = 1;
					printf("�û����Ѵ��ڣ����������룺\n");
					str = get_string(4, 14, 0);
				}
			} while (flag);
			strcpy(t.username, str);
			break;
		}
		case 2: {
			printf("����������룺\n");
			str = password_get(1);
			while (count <= 3 && count1 <= 3 && flagnum) {
				if (!strcmp(str, t.password)) {
					do {
						printf("\n�������µ�����: \n");
						str = password_get(1);
						printf("\n��ȷ�����룺\n");
						str2 = password_get(1);
						if (!strcmp(str, str2)) {
							printf("\n�������óɹ���\n");
							strcpy(t.password, str);
							flagnum = 0;
						}
						else {
							tag = 1;
							count1++;
							printf("\n�������벻һ��Ŷ,���������룡");
						}
					} while (tag && count1 <= 3 && flagnum);
				}
				else {
					printf("\n����������������룺\n");
					free(str);
					str = password_get(1);
					count++;
				}
				if (count > 3) {
					return;
				}
			}
			free(str);
			free(str2);
			break;
		}
		}
		if (flagnum == 0 && enquiry(1)) {
			p->element = t;
			save_account();
			print_ok();
		}
		else {
			printf("�޸���ȡ��!\n");
		}
		printf("�Ƿ�����޸�?(0/1):");
		if (get_num(0, 1, 1, 1)) {
			modify_account(p);
		}
	}
	else {
		printf("������ȷ��Ҫ�޸ĵ���Ϣ!\n");
	}
}

Account* search_account(char *obj, int judge){//��UID/�û������ң�judge�����Ƿ�������Ʒ���
	Account *t;int flag = 0;
	for (t = list.account_head->next; t != NULL; t = t->next) {
		if (!strcmp(t->element.UID, obj) || !strcmp(t->element.username, obj)) {
			flag = 1;break;
		}
	}
	if (flag)
		return t;
	if (judge && flag == 0) {
		//printf("û������˺�Ŷ\n");
		for (t = list.account_head->next; t; t = t->next) {
			if (strstr(obj, t->element.UID) || strstr(obj, t->element.username)) {
				if (flag == 0) {
					Sleep(500); printf("��  "); printf("Ҳ�������ҵ��ǣ�\n"); Sleep(1000);
					flag = 1;
				}
				printf("%s %s\n", t->element.UID, t->element.username);
			}
		}
		if (flag == 1) {
			printf("��ȷ�Ϻ����²���: \n");
		}
	}
	return NULL;
}

void  delete_account(){
	char *str = NULL;
	printf("\n\n����������Ҫɾ�����˺���Ϣ��\n");
	str = get_string(1, 14, 0);
	if (Account *p = search_account(str, 1)) {
		if (enquiry(2)) {
			p->pre->next = p->next;
			if (p->next) {
				p->next->pre = p->pre;
			}
			free(p);
			save_account();
			print_ok();

		}
		else {
			printf("ɾ����ȡ��\n");
			rewind(stdin);
		}
	}
	free(str);
}

void print_account(Account *p){//��ӡ�˻���Ϣ
	if (p) {
		printf("\t\t|-------------------�˺���Ϣ-----------------|\n");
		printf("\t\t ID          �û���         ����      �˺�����\n");
		printf("\t\t %s      %s       %s      ", p->element.UID, p->element.username, p->element.password);
		switch (p->element.user_type) {
		case 1: printf("ϵͳ����Ա\n"); break;
		case 2: printf("��Ժ����\n"); break;
		case 3: printf("��ƱԱ\n"); break;
		case 4: printf("�˿�\n"); break;
		case 5: printf("����״̬\n"); break;
		}
	}
	else {
		printf("û���������˺�Ŷ\n");
	}
}