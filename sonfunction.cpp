#include"stdafx.h"
#include"statements.h"

int sign_judge() {//��½�жϼ���ȡ�˻���Ϣ   return flag   flag��ʾ�˻�����  
	show_sign();
	int cnt=0,flag=0;
	set_position(39, 8);
	char *username = username_get(0);
	set_position(39, 10);
	char *password = password_get(0);
	Account *p = list.account_head->next;
	for (p; p; p = p->next) {
		if (strcmp(username, p->element.username) == 0) {
			break;
		}
	}if (p != NULL) {//�û�������
		if (strcmp(password, p->element.password) == 0) {//������ȷ
			//������ȷ���˻���Ϣд����ǰ�˻���Ϣ
			strcpy(PRESENT.UID, p->element.UID);
			strcpy(PRESENT.username, username);
			strcpy(PRESENT.password, password);
			PRESENT.user_type = p->element.user_type;
			flag = PRESENT.user_type;
		}
		else {
			system("cls");
			set_position(25, 10);
			SetColor(12, 0);
			printf("�����Ӵ\n");
			go_on();
		}
	}
	else {//�û���������
		system("cls");
		set_position(25, 10);
		SetColor(12, 0);
		printf("û������˺�Ӵ\n");
		go_on();
	}
	return flag;//flag==0  ��ʾ��¼ʧ�ܣ��������Ͳμ�user_types
}

char *username_get(int judge) {//�û����Ļ�ȡ    judge!=0ʱ���������� 
	char *str=(char *)malloc(NAME*5);
	exam_NULL(str, 0);
	str[0] = '\0';
	scanf("%s", str);
	if(judge&&str)//str���ھ������
	while (strlen(str) > 14 || strlen(str) < 4) {
		print_examinput();
		scanf("%s", str);
	}
	return str;
}

char *password_get(int judge) {//��������Ļ�ȡ        judge!=0ʱ����������
	char *password = (char *)malloc(PASSWORD * 4 * sizeof(char));
	char str[50], c = 0, i = 0;
	do {
		while (i < 49) {
			c = getch();
			getch();//΢����²���
			if (c != 8 && c != '\r'&&c!=' ') {
				str[i++] = c;
				printf("*");
			}
			else if (c == 8 && i > 0) {
				printf("\b \b");
				i--;
			}
			else if (c == '\r') {
				break;
			}
		}
		str[i] = '\0';//һ�������ȡ
	} while ((strlen(str)<6||strlen(str)>12)&&judge);
	strcpy(password,str);
	return password;
}

char *get_string(int down,int up ,int judge) {//�ַ�����ȡ����麯��    ����[down,up]   �ַ����ֽ�������
	char *str = (char *)malloc(sizeof(char)*100);// judge ����   �Ƿ������ּ�顢���ּ��  
	SetColor(14, 0);
	rewind(stdin);
	scanf("%s", str);
	SetColor(7, 0);
	unsigned int flag = 1, i;
	do {
		if (judge) {//���м����
			if (judge == 1) {
				for (i = 0; i < strlen(str); i++) {
					if (isdigit(str[i]) == 0) {//ȫΪ����
						flag = 0; break;
					}
				}
			}else if (judge == 2) {
				for (i = 0; i < strlen(str); i++) {
					if (0<=str[i]&&str[i]<=255) {//���ּ��
						flag = 0; break;
					}
				}
			}
		}
		while (flag == 0 || ((int)strlen(str) < down || (int)strlen(str) > up)) {
			print_examinput();
			SetColor(14, 0);
			scanf("%s", str);
			SetColor(7, 0);
		}
	} while ((flag == 0) && (flag = 1));
	return str;
}

int get_num(int down, int up, int ndown, int nup) {//��ȡ����    ���������   ��Χ[down,up]   λ��n[ndown,nup]
	int num,flag=1;
	do {
		SetColor(14, 0);
		rewind(stdin);
		scanf("%d", &num);
		SetColor(7, 0);
		char str[25];
		sprintf(str, "%d", num);
		if (num<down || num>up || (strlen(str) > (unsigned)nup||strlen(str) < (unsigned)ndown)) {//����С��λ��
			print_examinput();
			flag = 0;
		}
	} while (flag == 0 && (flag = 1));
	return num;
}

char *get_date() {//���ڵĻ�����ж�
	date_status date = {0,0,0};
	int flag = 1,y,m,d;
	do {
		SetColor(14, 0);
		rewind(stdin);
		scanf("%d-%d-%d", &y, &m, &d);
		SetColor(7, 0);
		if (y < 2018 || y>2050) {
			flag = 0;
		}
		if (1 > m || m > 12) {
			flag = 0;
		}
		if (1 > d || d > 31) {
			flag = 0;
		}
		if (m == 2) {
			if (d > 29) {
				flag = 0;
			}
			if ((d == 29) && (y % 4 != 0)) {
				flag = 0;
			}
		}
		if ((m != 2) && (m % 2 == 0 && d > 30)) {
			flag = 0;
		}
		if (flag == 0) {
			printf("��������Ч�����ڣ�\n"); rewind(stdin);
		}
	} while (flag == 0 && (flag = 1));
	date.year = y, date.month = m, date.day = d;
	char  *re=(char *)malloc(sizeof(char)*40);
	sprintf(re, "%d-%02d-%02d", date.year, date.month, date.day);
	return re;
}

char *get_time() {//ʱ��Ļ�ü��ж�
	time_status time = {0,0};
	int h, m,flag=1;
	do {
		SetColor(14,0);
		rewind(stdin);
		scanf("%d:%d", &h, &m);
		SetColor(7, 0);
		if (h < 0 || h>23 || m < 0 || m>59) {
			flag = 0;
			printf("������Ϸ���ʱ�䣡\n"); rewind(stdin);
		}
	} while (flag == 0 && (flag = 1));
	time.hour = h, time.minute = m;
	char *str = (char *)malloc(sizeof(char) * 22);
	sprintf(str, "%02d:%02d", time.hour, time.minute);
	return str;
}

data_program get_program_infomation() {//��ȡ��Ŀ��Ҫ��Ϣ  �����г�ʼ��
	catch_cursor();
	data_program tem = { 0 };
	strcpy(tem.area, "����");
	strcpy(tem.performer[0], "����");
	strcpy(tem.performer[1], "����");
	strcpy(tem.language, "����");
	strcpy(tem.label, "����");
	tem.program_rating = (program_ratings)1;
	char *str; int flag = 1, choice;
	printf("\n1.��Ӱ   2.���   3.���ֻ�\n");
	printf("��ѡ���Ŀ����:");
	choice = get_num(1, 3, 1, 1);
	tem.program_type = (program_types)choice;
	//printf("�������Ŀ���(6λ����):");
	//str = get_string(6, 6, 1);
	//Program *p;//ID����
	//do {
	//	p = search_program(str, 0);
	//	if (p) {
	//		free(str);
	//		printf("�ñ���ѱ�ʹ�ã��Ƽ����%d\n����������:",atoi(list.program_tail->element.program_ID)+1);
	//		str = get_string(6, 6, 1);
	//	}
	//} while (p != NULL);
	//strcpy(tem.program_ID, str);
	//free(str);
	sprintf(tem.program_ID, "%ld", get_newkey(choice));
	printf("��Ϊ��Ŀ����IDΪ %s\n", tem.program_ID);
	printf("�������Ŀ����(15����������):");
	str = get_string(1, 30, 0);
	strcpy(tem.program_name, str);
	free(str);
	tem.program_type == 3 ? printf("������ָ������(7����������):") : printf("�����뵼������(7����������):");
	str = get_string(1, 14, 0);
	strcpy(tem.director, str);
	free(str);
	printf("�����뿪ʼ�������������(year-month-day):\n");
	do {
		char *start_date, *end_date;
		start_date = get_date();
		end_date = get_date();
		/*if (tem.start_date.year>tem.end_date.year||(tem.start_date.year==tem.end_date.year&&\
			tem.start_date.month>tem.end_date.month)||(tem.start_date.year == tem.end_date.year\
			&&tem.start_date.month==tem.end_date.month&&tem.start_date.day>tem.end_date.day)) {
			flag = 0;
			print_examinput();
		}*/
		if (strcmp(end_date, end_date) < 0) { printf("������������Ч����ֹ���ڣ�"); flag = 0; }
		else { strcpy(tem.start_date, start_date); strcpy(tem.end_date, end_date); }
		free(start_date); free(end_date);
	} while (flag == 0 && (flag = 1));
	printf("�����þ�Ŀʱ��(1~600)(min):");
	choice = get_num(1,600,1,3);
	tem.duration = choice;
	printf("������Ʊ��(5~100)(Ԫ):");
	choice = get_num(5, 100, 1, 3);
	tem.price = choice;
	printf("�����þ�Ŀ����(2������):");
	str = get_string(4, 4, 2);
	strcpy(tem.language, str);free(str);
	printf("�������Ŀ��ӳ�ɱ�(��Ԫ):");
	choice = get_num(1, 1000, 1, 3);
	tem.cost = choice;
	return tem;
}

void program_viewer() {//��Ŀ�����
	Program *p1 = list.program_head->next;
	Program *p2=NULL;
	int choice, cnt = 1, pages = (list.program_head->element.cost + 1) / 2;
	print_program(p1, 1); printf("				��ǰ��%dҳ����%dҳ", cnt, pages);
	if (p1) {
		p2 = p1->next;
		print_program(p2,0);
	}
	while (choice=turn_page()) {
		if (choice == 1 || choice == 2) {
			if(p1!=list.program_tail&&p2!=list.program_tail)
			if (p2) {
				p1 = p2->next;
				if (p1) {
					p2 = p1->next; cnt++;
				}
				//else {//���ظ����
				//	p2 = NULL;
				//}
			}
			/*else {
				p1 = NULL;
			}*/
			print_program(p1,1); printf("				��ǰ��%dҳ����%dҳ", cnt, pages); print_program(p2,0);
		}
		else if (choice == -1 || choice == -2) {
			if(p1!=list.program_head&&p2!=list.program_head)
				if (p1&&p1->pre!=list.program_head) {
					p2 = p1->pre;
					if (p2&&p2->pre!=list.program_head) {
						p1 = p2->pre; cnt--;
				}
			//	else {//���ظ����
			//		p2 = NULL;
			//	}
			}
			//else {
			//	p1 = NULL;
			//}
			if (p1&&p2) {
				if (p1 != list.program_head)print_program(p1, 1); printf("				��ǰ��%dҳ����%dҳ",cnt,pages); if (p2 != list.program_head)print_program(p2, 0);
			}
			/*else {
				if (p1 != list.program_head)print_program(p1, 1); if (p2 != list.program_head) print_program(p2, 0);
			}*/
		}
		/*if (choice==1&&(p1 == list.program_tail || p2 == list.program_tail)) {
			printf("�Ѿ������һҳ��\n");
		}
		else if (choice == -1 && (p1 == list.program_head->next || p2 == list.program_head->next)) {
			printf("�Ѿ��ǵ�һҳ��\n");
		}*/
	}
}

void studio_viewer() {//��ӳ���鿴��
	int choice, cnt = 1, pages = list.studio_head->element.seatx;
	Studio *p = list.studio_head->next;
	if (p) { print_studio(p); printf("			��ǰ��%d����ӳ������%d��", cnt, pages); }
	while (choice=turn_page()) {
		if (choice == 1 || choice == 2) {
			if (p->next) { p = p->next; cnt++; }
			if (p) print_studio(p);
			printf("			��ǰ��%d����ӳ������%d��", cnt, pages);
		}
		else if (choice == -1 || choice == -2) {
			if (p != list.studio_head->next) { p = p->pre; cnt--; }
			print_studio(p);
			printf("			��ǰ��%d����ӳ������%d��", cnt, pages);
		}
	}
}

void plan_viewer(Plan *head) {//�ݳ��ƻ������
	Plan *p = head->next;
	int num = (head->element.ticketnum + 6) / 7, choice = 1, i, cnt = 0, flagend = 1, flaghead = 1;
	int re = head->element.ticketnum % 7;
	if (p == NULL) { printf("���޼ƻ�\n"); return; }//flagend    flaghead  ��ʶ�Ƿ�ﵽ����߽�
	do {
		if (((choice == 1 || choice == 2) && cnt <= num && p->next) || ((choice == -1 || choice == -2) && cnt >= 0 && p->pre) && (flagend || flaghead)) {
			system("cls");
			printf("\n\n				      �ݳ��ƻ�һ��\n\n");
			print_planhead();
			if ((choice == -1 || choice == -2) && flaghead) {
				flagend = 1;
				for (int j = 1; j <= 7 + re; j++)if (p->pre != head)p = p->pre; else break;
			}
			for (i = 1; i <= 7; i++) {//(choice == 1 || choice == 2)
				if (flagend) { flaghead = 1; print_plan(p); if (p->next)p = p->next; else flagend = 0; }
				//else if ((choice == -1 || choice == -2) && flaghead) { flagend = 1; print_plan(p); if (p->pre != head)p = p->pre; else flaghead = 0; }
				else break;
			}
			if (cnt < num && choice > 0) cnt++; else if (cnt > 1 && choice < 0) cnt--;
			printf("    ===============================================================================\n");
			printf("				    ��ǰ��%dҳ����%dҳ\n", cnt, num);
		}
	} while (choice = turn_page());
}

void seat_changer(Studio *p) {//���ӻ���λ�޸���
	system("cls");
	if(p==NULL){ return;}
	Seat *k = p->element.seat_head->next;
	if (k == NULL) { printf("�����ӳ��û����λӴ\n"); go_on(); return; }
	int i, j;
	for (i=1 ; i <=p->element.seatx ; i++) {
		for (j=1 ; j <= p->element.seaty; j++) {
			switch (k->seat_condition)
			{
			case 0:printf("  "); break;
			case 1:printf("��");  break;
			case 9:printf("��"); break;
			}k = k->next;
		}printf("\n");
	}
	if (select_seat(p)) {
		save_studio_and_seat();
	}
	else {
		printf("�޸���ȡ��\n");
	}
}

void ticket_changer(Plan *p) {//��Ʊ�����
	int choice;
	/*while (choice == turn_page()) {
		if()
	}*/
}

void password_change(char *obj, int i) {//  i      1 :  ����     2:����
	if (i == 1) {
		for (i = 0; i < strlen(obj); i++) {
			obj[i] += i;
		}
	}
	else if (i == 2) {
		for (i = 0; i < strlen(obj); i++) {
			obj[i] -= i;
		}
	}
	else {
		print_re();
	}
}

void account_appeal() {//�˺����߹���
	SetColor(7, 0);
	char *str = NULL, *str2 = NULL;
	system("CLS");
	printf("\n\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("\t\t                       �˺�����                             \n");
	printf("\n\n��ȷ���Ƿ�����˺�����(1����2�˳�):");
	switch (get_num(1, 2, 1, 1)) {
	case 1: 
		printf("\n����������û���:\n");
		str = get_string(4, 14, 0);
		if (Account *t = search_account(str, 0)) {
			free(str);
			printf("���������ID��\n");
			str = get_string(1, 8, 0);
			if (!strcmp(str, t->element.UID)) {
				free(str);
				printf("������ȷ��������޸����������!\n");
				printf("\n�������µ�����: \n");
				str = password_get(1);
				printf("\n��ȷ�����룺\n");
				str2 = password_get(1);
				if (!strcmp(str, str2)) {
					printf("\n�������óɹ���\n");
					strcpy(t->element.password, str);
				}
				else {
					printf("�������벻һ��Ŷ������������\n");
				}
			}
			else {
				printf("UID����������������ߣ�\n");
			}
		}
		else {
			printf("�û����������!\n");
		}
		break;
	case 2:return; break;
	}

}

void timer() {//��ȡϵͳʱ��
	time_t t;
	time(&t);
	now = localtime(&t);
}

void clean_plan_atFirst() {//����ʼ�����ڵ��ݳ��ƻ���ǹ���
	timer();
	char date[15];
	sprintf(date, "%d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	FILE *fp = fopen(".\\plan.txt", "r+");
	exam_NULL(fp, 1);
	char t[20000]; data_plan tem;
	while (fscanf(fp, "%ld %s %d %s %s %d %d\r\n", &tem.plan_ID, &tem.program_name, &tem.studio_ID, \
		tem.date, tem.time, &tem.ticketnum, &tem.button) != EOF) {
		if (strcmp(date,tem.date)>0) {
			fseek(fp, -3, SEEK_CUR);
			fprintf(fp, "%d", 0);
			fseek(fp, 3, SEEK_CUR);
		}
		//else { fscanf(fp, "%[^\r\n]", t); fscanf(fp, "%[^\r\n]", t); }
		fgets(t,20000,fp);//����һ����
	}
	fclose(fp);
}

//////////////////////////////////////���к���

void clean_plan() {//��鲢��������ݳ��ƻ�
	timer();
	char date[15];
	sprintf(date, "%d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	Plan *p = list.plan_head->next;
	for (p; p; p = p->next) {
		if (strcmp(date, p->element.date) > 0) {
			p->element.button = 0;
			p->next = list.plan_tem_tail->next; p->pre = list.plan_tem_tail;
			list.plan_tem_tail->next = p; list.plan_tem_tail = p;//�ƶ�p��plan_tem����
			modify_plan_and_ticket(p);
		}
	}
}

//////////////////////////////////////���к���

/////////////////////////////////////////////////music

void play_bgm() {
	switch (now->tm_sec % 5) {
	case 0:
	case 1:PlaySound(_T("C:\\Users\\HP\\source\\repos\\��ԺƱ�����ϵͳ\\��ԺƱ�����ϵͳ\\res\\�� �� �� ʿ �� �� �� - �� �� �� �� �� �� �� Ӱ Ժ.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	case 2:PlaySound(_T("C:\\Users\\HP\\source\\repos\\��ԺƱ�����ϵͳ\\��ԺƱ�����ϵͳ\\res\\�� �� �� ʿ �� �� �� - �� �� �� �� �� �� �� Ӱ Ժ.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	case 3:PlaySound(_T("C:\\Users\\HP\\source\\repos\\��ԺƱ�����ϵͳ\\��ԺƱ�����ϵͳ\\res\\�� �� �� ʿ �� �� �� - �� �� �� �� �� �� �� Ӱ Ժ.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	case 4:PlaySound(_T("C:\\Users\\HP\\source\\repos\\��ԺƱ�����ϵͳ\\��ԺƱ�����ϵͳ\\res\\�� �� �� ʿ �� �� �� - �� �� �� �� �� �� �� Ӱ Ժ.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	case 5:PlaySound(_T("C:\\Users\\HP\\source\\repos\\��ԺƱ�����ϵͳ\\��ԺƱ�����ϵͳ\\res\\�� �� �� ʿ �� �� �� - �� �� �� �� �� �� �� Ӱ Ժ.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	}
}
