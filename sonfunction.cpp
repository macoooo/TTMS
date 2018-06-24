#include"stdafx.h"
#include"statements.h"

int sign_judge() {//登陆判断及获取账户信息   return flag   flag表示账户类型  
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
	}if (p != NULL) {//用户名存在
		if (strcmp(password, p->element.password) == 0) {//密码正确
			//密码正确将账户信息写至当前账户信息
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
			printf("口令不对哟\n");
			go_on();
		}
	}
	else {//用户名不存在
		system("cls");
		set_position(25, 10);
		SetColor(12, 0);
		printf("没有这个账号哟\n");
		go_on();
	}
	return flag;//flag==0  表示登录失败，其他类型参见user_types
}

char *username_get(int judge) {//用户名的获取    judge!=0时进行输入检查 
	char *str=(char *)malloc(NAME*5);
	exam_NULL(str, 0);
	str[0] = '\0';
	scanf("%s", str);
	if(judge&&str)//str基于警告加入
	while (strlen(str) > 14 || strlen(str) < 4) {
		print_examinput();
		scanf("%s", str);
	}
	return str;
}

char *password_get(int judge) {//密码输入的获取        judge!=0时进行输入检查
	char *password = (char *)malloc(PASSWORD * 4 * sizeof(char));
	char str[50], c = 0, i = 0;
	do {
		while (i < 49) {
			c = getch();
			getch();//微软更新产物
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
		str[i] = '\0';//一次密码获取
	} while ((strlen(str)<6||strlen(str)>12)&&judge);
	strcpy(password,str);
	return password;
}

char *get_string(int down,int up ,int judge) {//字符串获取及检查函数    长度[down,up]   字符串字节数限制
	char *str = (char *)malloc(sizeof(char)*100);// judge 开关   是否开启数字检查、汉字检查  
	SetColor(14, 0);
	rewind(stdin);
	scanf("%s", str);
	SetColor(7, 0);
	unsigned int flag = 1, i;
	do {
		if (judge) {//进行检查检查
			if (judge == 1) {
				for (i = 0; i < strlen(str); i++) {
					if (isdigit(str[i]) == 0) {//全为数字
						flag = 0; break;
					}
				}
			}else if (judge == 2) {
				for (i = 0; i < strlen(str); i++) {
					if (0<=str[i]&&str[i]<=255) {//汉字检查
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

int get_num(int down, int up, int ndown, int nup) {//读取数字    并检查输入   范围[down,up]   位数n[ndown,nup]
	int num,flag=1;
	do {
		SetColor(14, 0);
		rewind(stdin);
		scanf("%d", &num);
		SetColor(7, 0);
		char str[25];
		sprintf(str, "%d", num);
		if (num<down || num>up || (strlen(str) > (unsigned)nup||strlen(str) < (unsigned)ndown)) {//检查大小及位数
			print_examinput();
			flag = 0;
		}
	} while (flag == 0 && (flag = 1));
	return num;
}

char *get_date() {//日期的获得与判断
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
			printf("请输入有效的日期！\n"); rewind(stdin);
		}
	} while (flag == 0 && (flag = 1));
	date.year = y, date.month = m, date.day = d;
	char  *re=(char *)malloc(sizeof(char)*40);
	sprintf(re, "%d-%02d-%02d", date.year, date.month, date.day);
	return re;
}

char *get_time() {//时间的获得及判断
	time_status time = {0,0};
	int h, m,flag=1;
	do {
		SetColor(14,0);
		rewind(stdin);
		scanf("%d:%d", &h, &m);
		SetColor(7, 0);
		if (h < 0 || h>23 || m < 0 || m>59) {
			flag = 0;
			printf("请输入合法的时间！\n"); rewind(stdin);
		}
	} while (flag == 0 && (flag = 1));
	time.hour = h, time.minute = m;
	char *str = (char *)malloc(sizeof(char) * 22);
	sprintf(str, "%02d:%02d", time.hour, time.minute);
	return str;
}

data_program get_program_infomation() {//获取剧目主要信息  并进行初始化
	catch_cursor();
	data_program tem = { 0 };
	strcpy(tem.area, "——");
	strcpy(tem.performer[0], "——");
	strcpy(tem.performer[1], "——");
	strcpy(tem.language, "中文");
	strcpy(tem.label, "——");
	tem.program_rating = (program_ratings)1;
	char *str; int flag = 1, choice;
	printf("\n1.电影   2.歌剧   3.音乐会\n");
	printf("请选择剧目类型:");
	choice = get_num(1, 3, 1, 1);
	tem.program_type = (program_types)choice;
	//printf("请输入剧目编号(6位数字):");
	//str = get_string(6, 6, 1);
	//Program *p;//ID查重
	//do {
	//	p = search_program(str, 0);
	//	if (p) {
	//		free(str);
	//		printf("该编号已被使用，推荐编号%d\n请重新输入:",atoi(list.program_tail->element.program_ID)+1);
	//		str = get_string(6, 6, 1);
	//	}
	//} while (p != NULL);
	//strcpy(tem.program_ID, str);
	//free(str);
	sprintf(tem.program_ID, "%ld", get_newkey(choice));
	printf("已为剧目分配ID为 %s\n", tem.program_ID);
	printf("请输入剧目名称(15个汉字以内):");
	str = get_string(1, 30, 0);
	strcpy(tem.program_name, str);
	free(str);
	tem.program_type == 3 ? printf("请输入指挥姓名(7个汉字以内):") : printf("请输入导演姓名(7个汉字以内):");
	str = get_string(1, 14, 0);
	strcpy(tem.director, str);
	free(str);
	printf("请输入开始日期与结束日期(year-month-day):\n");
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
		if (strcmp(end_date, end_date) < 0) { printf("请重新输入有效的起止日期："); flag = 0; }
		else { strcpy(tem.start_date, start_date); strcpy(tem.end_date, end_date); }
		free(start_date); free(end_date);
	} while (flag == 0 && (flag = 1));
	printf("请设置剧目时长(1~600)(min):");
	choice = get_num(1,600,1,3);
	tem.duration = choice;
	printf("请设置票价(5~100)(元):");
	choice = get_num(5, 100, 1, 3);
	tem.price = choice;
	printf("请设置剧目语言(2个汉字):");
	str = get_string(4, 4, 2);
	strcpy(tem.language, str);free(str);
	printf("请输入剧目放映成本(万元):");
	choice = get_num(1, 1000, 1, 3);
	tem.cost = choice;
	return tem;
}

void program_viewer() {//剧目浏览器
	Program *p1 = list.program_head->next;
	Program *p2=NULL;
	int choice, cnt = 1, pages = (list.program_head->element.cost + 1) / 2;
	print_program(p1, 1); printf("				当前第%d页，共%d页", cnt, pages);
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
				//else {//不重复输出
				//	p2 = NULL;
				//}
			}
			/*else {
				p1 = NULL;
			}*/
			print_program(p1,1); printf("				当前第%d页，共%d页", cnt, pages); print_program(p2,0);
		}
		else if (choice == -1 || choice == -2) {
			if(p1!=list.program_head&&p2!=list.program_head)
				if (p1&&p1->pre!=list.program_head) {
					p2 = p1->pre;
					if (p2&&p2->pre!=list.program_head) {
						p1 = p2->pre; cnt--;
				}
			//	else {//不重复输出
			//		p2 = NULL;
			//	}
			}
			//else {
			//	p1 = NULL;
			//}
			if (p1&&p2) {
				if (p1 != list.program_head)print_program(p1, 1); printf("				当前第%d页，共%d页",cnt,pages); if (p2 != list.program_head)print_program(p2, 0);
			}
			/*else {
				if (p1 != list.program_head)print_program(p1, 1); if (p2 != list.program_head) print_program(p2, 0);
			}*/
		}
		/*if (choice==1&&(p1 == list.program_tail || p2 == list.program_tail)) {
			printf("已经是最后一页了\n");
		}
		else if (choice == -1 && (p1 == list.program_head->next || p2 == list.program_head->next)) {
			printf("已经是第一页了\n");
		}*/
	}
}

void studio_viewer() {//放映厅查看器
	int choice, cnt = 1, pages = list.studio_head->element.seatx;
	Studio *p = list.studio_head->next;
	if (p) { print_studio(p); printf("			当前第%d个放映厅，共%d个", cnt, pages); }
	while (choice=turn_page()) {
		if (choice == 1 || choice == 2) {
			if (p->next) { p = p->next; cnt++; }
			if (p) print_studio(p);
			printf("			当前第%d个放映厅，共%d个", cnt, pages);
		}
		else if (choice == -1 || choice == -2) {
			if (p != list.studio_head->next) { p = p->pre; cnt--; }
			print_studio(p);
			printf("			当前第%d个放映厅，共%d个", cnt, pages);
		}
	}
}

void plan_viewer(Plan *head) {//演出计划浏览器
	Plan *p = head->next;
	int num = (head->element.ticketnum + 6) / 7, choice = 1, i, cnt = 0, flagend = 1, flaghead = 1;
	int re = head->element.ticketnum % 7;
	if (p == NULL) { printf("暂无计划\n"); return; }//flagend    flaghead  标识是否达到链表边界
	do {
		if (((choice == 1 || choice == 2) && cnt <= num && p->next) || ((choice == -1 || choice == -2) && cnt >= 0 && p->pre) && (flagend || flaghead)) {
			system("cls");
			printf("\n\n				      演出计划一览\n\n");
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
			printf("				    当前第%d页，共%d页\n", cnt, num);
		}
	} while (choice = turn_page());
}

void seat_changer(Studio *p) {//可视化座位修改器
	system("cls");
	if(p==NULL){ return;}
	Seat *k = p->element.seat_head->next;
	if (k == NULL) { printf("这个放映厅没有座位哟\n"); go_on(); return; }
	int i, j;
	for (i=1 ; i <=p->element.seatx ; i++) {
		for (j=1 ; j <= p->element.seaty; j++) {
			switch (k->seat_condition)
			{
			case 0:printf("  "); break;
			case 1:printf("○");  break;
			case 9:printf("●"); break;
			}k = k->next;
		}printf("\n");
	}
	if (select_seat(p)) {
		save_studio_and_seat();
	}
	else {
		printf("修改已取消\n");
	}
}

void ticket_changer(Plan *p) {//售票浏览器
	int choice;
	/*while (choice == turn_page()) {
		if()
	}*/
}

void password_change(char *obj, int i) {//  i      1 :  加密     2:解密
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

void account_appeal() {//账号申诉过程
	SetColor(7, 0);
	char *str = NULL, *str2 = NULL;
	system("CLS");
	printf("\n\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("\t\t                       账号申诉                             \n");
	printf("\n\n请确认是否进行账号申诉(1申诉2退出):");
	switch (get_num(1, 2, 1, 1)) {
	case 1: 
		printf("\n请输入你的用户名:\n");
		str = get_string(4, 14, 0);
		if (Account *t = search_account(str, 0)) {
			free(str);
			printf("请输入你的ID：\n");
			str = get_string(1, 8, 0);
			if (!strcmp(str, t->element.UID)) {
				free(str);
				printf("输入正确，你可以修改你的密码了!\n");
				printf("\n请输入新的密码: \n");
				str = password_get(1);
				printf("\n请确认密码：\n");
				str2 = password_get(1);
				if (!strcmp(str, str2)) {
					printf("\n密码设置成功！\n");
					strcpy(t->element.password, str);
				}
				else {
					printf("两次输入不一样哦，请重新申诉\n");
				}
			}
			else {
				printf("UID输入错误，请重新申诉！\n");
			}
		}
		else {
			printf("用户名输入错误!\n");
		}
		break;
	case 2:return; break;
	}

}

void timer() {//读取系统时间
	time_t t;
	time(&t);
	now = localtime(&t);
}

void clean_plan_atFirst() {//程序开始将过期的演出计划标记过期
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
		fgets(t,20000,fp);//读完一整行
	}
	fclose(fp);
}

//////////////////////////////////////赋闲函数

void clean_plan() {//检查并处理过期演出计划
	timer();
	char date[15];
	sprintf(date, "%d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	Plan *p = list.plan_head->next;
	for (p; p; p = p->next) {
		if (strcmp(date, p->element.date) > 0) {
			p->element.button = 0;
			p->next = list.plan_tem_tail->next; p->pre = list.plan_tem_tail;
			list.plan_tem_tail->next = p; list.plan_tem_tail = p;//移动p到plan_tem链表
			modify_plan_and_ticket(p);
		}
	}
}

//////////////////////////////////////赋闲函数

/////////////////////////////////////////////////music

void play_bgm() {
	switch (now->tm_sec % 5) {
	case 0:
	case 1:PlaySound(_T("C:\\Users\\HP\\source\\repos\\剧院票务管理系统\\剧院票务管理系统\\res\\银 河 骑 士 李 老 板 - 嘉 禾 天 橙 国 际 大 影 院.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	case 2:PlaySound(_T("C:\\Users\\HP\\source\\repos\\剧院票务管理系统\\剧院票务管理系统\\res\\银 河 骑 士 李 老 板 - 嘉 禾 天 橙 国 际 大 影 院.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	case 3:PlaySound(_T("C:\\Users\\HP\\source\\repos\\剧院票务管理系统\\剧院票务管理系统\\res\\银 河 骑 士 李 老 板 - 嘉 禾 天 橙 国 际 大 影 院.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	case 4:PlaySound(_T("C:\\Users\\HP\\source\\repos\\剧院票务管理系统\\剧院票务管理系统\\res\\银 河 骑 士 李 老 板 - 嘉 禾 天 橙 国 际 大 影 院.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	case 5:PlaySound(_T("C:\\Users\\HP\\source\\repos\\剧院票务管理系统\\剧院票务管理系统\\res\\银 河 骑 士 李 老 板 - 嘉 禾 天 橙 国 际 大 影 院.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT); break;
	}
}
