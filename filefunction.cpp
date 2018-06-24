#include"stdafx.h"
#include"statements.h"
///////////////////////////////////////////import

void import_key() {//����������Ϣ������
	FILE *fp = fopen("key.txt", "r");
	exam_NULL(fp, 1);
	long key;int type;
	while (fscanf(fp, "%ld %d", &key, &type) != EOF) {
		Key *p = (Key *)malloc(sizeof(Key));
		p->next = list.key_tail->next;
		p->pre = list.key_tail;
		p->key = key; p->type = type;
		list.key_tail->next = p;
		list.key_tail = p;
	}
	fclose(fp);
}

void import_account() {//�����˺���Ϣ������
	int cnt = 0;
	FILE *fp = fopen(".\\account.txt","r");
	exam_NULL(fp, 1);
	int t;data_account tem;
	while (fscanf(fp,"%s %s %s %d %lld",tem.UID,tem.username,tem.password,&t,&tem.contributions)!=EOF) {
		tem.user_type = user_types(t);
		password_change(tem.password, 2);
		Account *p = (Account *)malloc(sizeof(Account));
		exam_NULL(p, 0);
		p->element = tem;//ÿ�ɹ���ȡһ��������һ����㣬���ӵ�������
		p->next = list.account_tail->next;
		p->pre = list.account_tail;
		list.account_tail->next = p;
		list.account_tail = p;
		cnt++;//����
	}
	list.account_head->element.contributions = cnt;//����
	fclose(fp);
}

void import_program() {//�����Ŀ��Ϣ������
	FILE *fp = fopen(".\\program.txt", "r");
	exam_NULL(fp, 1);
	data_program tem = {0};
	int type, rating, cnt = 0;
	while (fscanf(fp, "%s %s %d %d %s %s %s",tem.program_ID, tem.program_name, &type, &rating, tem.director,\
		tem.performer[0], tem.performer[1])==7&&fscanf(fp,"%s %s", tem.start_date, tem.end_date)== 2&&fscanf(fp,\
		"%d %s %s %s %d %d", &tem.duration, tem.label, tem.area, tem.language, &tem.price, &tem.cost)==6){
		tem.program_type = (program_types)type,tem.program_rating=(program_ratings)rating;
		Program *p = (Program *)malloc(sizeof(Program));
		exam_NULL(p, 0);
		p->element = tem;
		p->next = list.program_tail->next;
		p->pre = list.program_tail;
		list.program_tail->next = p;
		list.program_tail = p;
		cnt++;
	}
	list.program_head->element.cost = cnt;//ͷ������
	fclose(fp);
}

void import_studio_and_seat() {//�����ӳ������λ��Ϣ������
	FILE *fp = fopen(".\\studio.txt", "r");
	exam_NULL(fp, 1);
	data_studio tem;
	int i, j, t, ID;
	list.studio_head->element.seatx = 0;
	while (fscanf(fp, "%s %s %d %d %d", tem.studio_ID, tem.studio_name, &tem.seatx,&tem.seaty,&tem.seatsum) != EOF) {
		Studio *p = (Studio *)malloc(sizeof(Studio)); int cnt = 0;
		exam_NULL(p, 0);
		p->element = tem;
		p->element.seat_head = (Seat *)malloc(sizeof(Seat));
		exam_NULL(p->element.seat_head, 0);
		p->element.seat_head->pre = p->element.seat_head->next = NULL;//�������ʼ��
		p->element.seat_tail = p->element.seat_head;
		p->next = list.studio_tail->next;
		p->pre = list.studio_tail;
		list.studio_tail->next = p;
		list.studio_tail = p;
		list.studio_head->element.seatx++;//����
		//��λ�Ķ�ȡ�봦��
		ID = atoi(p->element.studio_ID);
		for (i = 1; i <= p->element.seatx; i++) {
			for (j = 1; j <= p->element.seaty; j++) {
				Seat *k = (Seat *)malloc(sizeof(Seat));
				exam_NULL(k, 0);
				k->seatx = i, k->seaty = j,k->stduio_ID=ID;
				fscanf(fp, "%d", &t); if (t == 1 || t == 2) cnt++;
				k->seat_condition = (seat_conditions)t;
				k->next = p->element.seat_tail->next;
				k->pre = p->element.seat_tail;
				p->element.seat_tail->next = k;
				p->element.seat_tail = k;
			}
		}if (p->element.seatsum != cnt) { printf("��λ�ļ�У�����\n"); print_re(); }
	}
	fclose(fp);
}

void import_plan_and_ticket() {//�����ݳ��ƻ���Ϣ������
	FILE *fp = fopen(".\\plan.txt", "r");
	exam_NULL(fp, 1);
	data_plan tem; int i, cnt = 0, cntt = 0, cnttt = 0;
	while (fscanf(fp, "%ld %s %d %s %s %d %d",&tem.plan_ID,&tem.program_name,&tem.studio_ID,\
tem.date,tem.time,&tem.ticketnum, &tem.button) != EOF) {
		Plan *p = (Plan *)malloc(sizeof(Plan)); exam_NULL(p, 0);
		p->element = tem;
		p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(p->element.ticket_head, 0);
		p->element.ticket_head->pre = p->element.ticket_head->next = NULL;
		p->element.ticket_tail = p->element.ticket_head;//Ʊ�������ʼ��
		cntt = 0;
		for (i = 1; i <= p->element.ticketnum; i++) {
			Ticket *k = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(k, 0); int t;
			fscanf(fp, "%ld %d %d %d %d", &k->ticket_ID, &k->seatx, &k->seaty, &k->price, &t);
			k->ticket_status = (ticket_statuses)t; if (k->ticket_status != TICKET_sold)cntt++;//��Ʊ����
			k->next = p->element.ticket_tail->next; k->pre = p->element.ticket_tail;
			p->element.ticket_tail->next = k; p->element.ticket_tail = k;
		}
		p->element.ticket_head->price = cntt;//
		if (p->element.button) {
			p->next = list.plan_tail->next; p->pre = list.plan_tail;
			list.plan_tail->next = p; list.plan_tail = p;  cnt++;//�����ݳ��ƻ�����
		}
		else {
			p->next = list.plan_tem_tail->next; p->pre = list.plan_tem_tail;
			list.plan_tem_tail->next = p; list.plan_tem_tail = p; cnttt++;//�����ݳ��ƻ�����
		}
	}
	list.plan_head->element.ticketnum = cnt;
	list.plan_tem_head->element.ticketnum = cnttt;
	fclose(fp);
}




//����

//void import_plan_and_ticket_tem() {//�����ѹ����ݳ��ƻ�
//	FILE *fp = fopen(".\\plantem.txt", "r");
//	exam_NULL(fp, 1);
//	data_plan tem; int cnt = 0;
//	while (fscanf(fp, "%ld %s %d %s %s %d %d", &tem.plan_ID, &tem.program_name, &tem.studio_ID, \
//		tem.date, tem.time, &tem.ticketnum, &tem.button) != EOF) {
//		Plan *p = (Plan *)malloc(sizeof(Plan)); exam_NULL(p ,0);
//		p->element = tem; cnt++;
//		p->element.ticket_tail = p->element.ticket_head = NULL;//Ʊ��������ÿ�
//		p->next = list.plan_tem_tail->next; p->pre = list.plan_tem_tail;
//		list.plan_tem_tail->next = p; list.plan_tem_tail = p;
//	}
//	list.plan_tem_head->element.ticketnum = cnt;
//	fclose(fp);
//}

void import_plan_and_ticket_bin() {//�������������������
	FILE *fp = fopen(".\\plan.bin", "rb");
	exam_NULL(fp, 1);
	int size_plan = sizeof(data_plan), size_ticket = sizeof(Ticket); data_plan tem;
	while (fread(&tem, size_plan, 1, fp) == 1) {
		Plan *p = (Plan *)malloc(sizeof(Plan)); p->element = tem;
		p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); //exam_mallocX(p->element.ticket_head);
		p->element.ticket_head->pre = p->element.ticket_head->next = NULL;
		p->element.ticket_tail = p->element.ticket_head;//Ʊ�������ʼ��
		for (int i = 1; i <= tem.ticketnum; i++) {
			Ticket *k = (Ticket *)malloc(sizeof(Ticket)); //exam_mallocX(k);
			fread(k, size_ticket, 1, fp);
			k->next = p->element.ticket_tail->next; k->pre = p->element.ticket_tail;
			p->element.ticket_tail->next = k; p->element.ticket_tail = k;
		}
		p->next = list.plan_tail->next; p->pre = list.plan_tail;
		list.plan_tail->next = p; list.plan_tail = p;
	}
	fclose(fp);
}

//////////////////////////////////////////save

void save_key() {//����������Ϣ���ļ�
	FILE *fp = fopen(".\\key.txt", "w");
	exam_NULL(fp, 1);
	Key *p = list.key_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%ld %d\n", p->key, p->type);
	}
	fclose(fp);
}

void save_program() {//�����Ŀ��Ϣ���ļ�
	FILE *fp = fopen(".\\program.txt","w+");
	exam_NULL(fp, 1);
	Program *p = list.program_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%s %s %d %d %s %s %s %s %s %d %s %s %s %d %d\n", p->element.program_ID\
		,p->element.program_name, p->element.program_type, p->element.program_rating, p->element.director,\
		p->element.performer[0], p->element.performer[1],p->element.start_date, p->element.end_date,\
		p->element.duration, p->element.label, p->element.area, p->element.language, p->element.price, p->element.cost);
	}
	fclose(fp);
}

void save_studio_and_seat() {//�����ӳ��������λ����
	int i, j;
	FILE *fp = fopen(".\\studio.txt", "w+");
	exam_NULL(fp, 1);
	Studio *p = list.studio_head->next;
	Seat *k = NULL;
	for (p; p; p = p->next) {
		fprintf(fp, "%s %s %d %d %d\n", p->element.studio_ID, p->element.studio_name, p->element.seatx, p->element.seaty,p->element.seatsum);
		k = p->element.seat_head->next;
		for (i = 1; i <= p->element.seatx; i++) {
			for (j = 1; j <= p->element.seaty; j++) {
				/*if (k->seatx > p->element.seatx || k->seaty > p->element.seaty) {
					j--,k = k->next; continue; }*/
				fprintf(fp, "%d ", k->seat_condition);
				k = k->next;
			}fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

void save_plan_and_ticket() {//�����ݳ��ƻ���Ʊ
	FILE *fp = fopen(".\\plan.txt", "w");
	exam_NULL(fp, 1);
	Plan *p = list.plan_head->next;
	for (p; p; p = p->next) {
		if (p->element.button != 1 ) { continue; }//0  ����   1����
		fprintf(fp, "%ld %s %d %s %s %d %d\n",p->element.plan_ID,p->element.program_name,p->element.studio_ID,\
		p->element.date,p->element.time,p->element.ticketnum, p->element.button);
		Ticket *k = p->element.ticket_head->next;
		for (int i = 1; i <= p->element.ticketnum; i++) {
			fprintf(fp, "%ld %d %d %d %d     ", k->ticket_ID, k->seatx, k->seaty, k->price, k->ticket_status);
			k = k->next;
			//if (i % 5 == 0) { fprintf(fp, "\n"); }
		}
		fprintf(fp, "\n");
	}
	p = list.plan_tem_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%ld %s %d %s %s %d %d\n", p->element.plan_ID, p->element.program_name, p->element.studio_ID, \
			p->element.date, p->element.time, p->element.ticketnum, p->element.button);
		Ticket *k = p->element.ticket_head->next;
		for (int i = 1; i <= p->element.ticketnum; i++) {
			fprintf(fp, "%ld %d %d %d %d     ", k->ticket_ID, k->seatx, k->seaty, k->price, k->ticket_status);
			k = k->next;
			//if (i % 5 == 0) { fprintf(fp, "\n"); }
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void save_plan_and_ticket(Plan *p) {//׷���ݳ��ƻ���Ʊ����Ϣ���ļ�
	FILE *fp = fopen(".\\plan.txt", "a+");
	exam_NULL(fp, 1);
	fprintf(fp, "%ld %s %d %s %s %d %d\n", p->element.plan_ID, p->element.program_name, p->element.studio_ID, \
		p->element.date, p->element.time, p->element.ticketnum, p->element.button);
	Ticket *k = p->element.ticket_head->next;
	for (int i = 1; i <= p->element.ticketnum; i++) {
		fprintf(fp, "%ld %d %d %d %d     ", k->ticket_ID, k->seatx, k->seaty, k->price, k->ticket_status);
		k = k->next;
		//if (i % 5 == 0) { fprintf(fp, "\n"); }
	}
	fprintf(fp, "\n");
	fclose(fp);
}

void save_plan_and_ticket_bin() {//�������ļ�
	FILE *fp = fopen(".\\plan.bin", "wb");
	exam_NULL(fp, 1);
	Plan *p = list.plan_head->next; 
	int size_plan = sizeof(data_plan), size_ticket = sizeof(Ticket);
	for (p; p; p = p->next) {
		fwrite(&(p->element),size_plan,1,fp);
		for (Ticket *k = p->element.ticket_head->next; k; k = k->next) {
			fwrite(k, size_ticket, 1, fp);
		}
	}
	fclose(fp);
}

void modify_plan_and_ticket(Plan *p) {//�ֲ���д�ļ�     ��button����
	FILE *fp = fopen(".\\plan.txt", "r+");
	exam_NULL(fp, 1);
	char t[50000]; data_plan tem;
	while (fscanf(fp, "%ld %s %d %s %s %d %d\r\n", &tem.plan_ID, &tem.program_name, &tem.studio_ID, \
		tem.date, tem.time, &tem.ticketnum, &tem.button) != EOF) {
		if (tem.plan_ID != p->element.plan_ID) {
			fgets(t,50000,fp);//����һ����
		}
		else break;
	}
	fseek(fp,-3,SEEK_CUR);
	fprintf(fp, "%d", 0);
	fseek(fp, 3, SEEK_CUR);
	fclose(fp);
}

//void modify_ticket(Plan *p) {//�ֲ���д�ļ�   �޸�Ʊ��״̬
//	FILE *fp = fopen(".\\plan.txt", "r+");
//	exam_NULL(fp, 1);
//	char t[50000]; data_plan tem;
//	while (fscanf(fp, "%ld %s %d %s %s %d %d\r\n", &tem.plan_ID, &tem.program_name, &tem.studio_ID, \
//		tem.date, tem.time, &tem.ticketnum, &tem.button) != EOF) {
//		if (tem.plan_ID != p->element.plan_ID) {
//			fgets(t, 50000, fp);//����һ����
//		}
//		else break;
//	}
//	fseek(fp, 0, SEEK_CUR);
//	Ticket *q = p->element.ticket_head->next;
//	for (q; q; q = q->next) {
//		
//	}
//	
//	fclose(fp);
//}

void save_account(Account *p)
{
	char str[13];
	FILE *fp = fopen("account.txt", "a+");
	exam_NULL(fp, 1);
	strcpy(str, p->element.password);
	password_change(str, 1);
	fprintf(fp, "%s %s %s %d %lld\n", p->element.UID, p->element.username, str, p->element.user_type, p->element.contributions);
	fclose(fp);
}

void save_account()
{
	char str[13];
	FILE *fp = fopen("account.txt", "w");
	exam_NULL(fp, 1);
	for (Account *p = list.account_head->next; p; p = p->next) {
		strcpy(str, p->element.password);
		password_change(str, 1);
		fprintf(fp, "%s %s %s %d %lld \n", p->element.UID, p->element.username, str, p->element.user_type, p->element.contributions);
	}

	fclose(fp);
}

int save_invitation_code(char *obj) {//�Ƚ� �� �ֲ��޸�������  //����ֵΪ�ȶԽ��
	FILE *fp = fopen(".\\invitation.txt", "r");
	FILE *fpp = fopen(".\\invitation_tem.txt", "w+");
	exam_NULL(fp, 1); exam_NULL(fpp, 1);
	char str[15]; int flag = 0;
	while (fscanf(fp, "%s", str) != EOF) {
		if (strcmp(str, obj) == 0) {
			flag = 1;
			continue;
		}
		fprintf(fpp, "%s\n", str);
	}
	fclose(fp);
	fclose(fpp);
	remove(".\\invitation.txt");
	rename("invitation_tem.txt", "invitation.txt");
	return flag;
}
