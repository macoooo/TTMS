#include "stdafx.h"
#include "statements.h"


/*void choice() {//�ı��ƶ�����
	HANDLE handle_move = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(handle_move, &screen_info);
	SMALL_RECT move = {0,0,1,0};//�����ƶ�����
	COORD position = { 1,10 };//Ŀ������
	CHAR_INFO  c_fill;
	c_fill.Char.AsciiChar =' ';
	c_fill.Attributes = screen_info.wAttributes;
	printf("00000"); 
	ScrollConsoleScreenBuffer(handle_move, &move, NULL, position, &c_fill);
}*/

int choice_judge(int i) {//��ȡ�����¼�          i  // ����ѡ��   �μ�screen_clear����
	int highlight=1;                         
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;//���������¼��ṹ��
	DWORD res;//���巵�ؼ�¼
	while(true){
		ReadConsoleInput(handle, &event, 1, &res);      //��ȡ�����¼�  
		if (event.EventType == KEY_EVENT)      //�����ǰ�¼��Ǽ����¼�  
		{
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_UP&& event.Event.KeyEvent.bKeyDown == (BOOL)true) //���¡�  
			{
				highlight = screen_clear(i, highlight, -1);
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && event.Event.KeyEvent.bKeyDown == (BOOL)true) //���¡� 
			{
				highlight = screen_clear(i, highlight, 1);
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true ) //����ESC  
			{
				if (i == 1) {//������ESCֱ���˳�
					show_bye();
					system("cls");
					system("color ff");
					system("taskkill /im cmd.exe /T /F");
					//quick_exit(0);
				}
				else {
					return 0;//��Ϊ������һ��
				}
			}
			if (event.Event.KeyEvent.uChar.AsciiChar ==13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) //���»س�  
			{
				SetColor(7, 0);
				return highlight;
			}
		}
	}
}

int screen_clear(int order,int i,int change) {/*������ĸ�������  i��ʾ��ǰ����ѡ�� Ĭ��Ϊ1
									   ����change��ı���  order��ʾ�����ѡ��  �������ص�ǰѡ����*/
	i += change;
	if (order == 1) {//������
		i == 0 ? i = 3 : i = i;//��������
		i > 3 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 8); printf("��¼");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 10); printf("ע��");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 12); printf("�뿪");
	}
	else if (order==2) {
		i == 0 ? i = 5 : i = i;//��������
		i > 5 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("��Ŀ��ѯ������");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("Ӱ����ѯ������");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("�ݳ���ѯ������");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 12); printf("����ͳ�����ѯ");
		i == 5?SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 14); printf("�ҵ��˺ż�����");
	}
	else if (order >= 3 && order <= 10) {
		char obj[5];
		switch (order) {
		case 3:strcpy(obj, "��Ŀ"); break;
		case 4:strcpy(obj, "Ӱ��"); break;
		case 5:strcpy(obj, "�û�"); break;
		case 6:strcpy(obj, ""); break;
		default:
			print_re(); break;
		}
		i == 0 ? i = 5 : i = i;
		i > 5 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("��ѯ%s��Ϣ",obj);
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("�޸�%s��Ϣ",obj);
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("����%s��Ϣ",obj);
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("ɾ��%s��Ϣ",obj);
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 14); printf("�������%s",obj);
	}
	else if (order == 11) {
		i == 0 ? i = 3 : i = i;
		i > 3 ? i = 1: i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("ϵͳ�û�����");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("��¼��¼��ѯ");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("�����ҵ���Ϣ");
	}
	else if (order == 12) {
		i == 0 ? i = 5 : i = i;
		i > 5 ? i = 1 : i = i;
		set_position(35, 4);
		SetColor(10, 0);
		printf("�ݳ���ѯ������");
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("��ѯ�ݳ��ƻ�");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("�޸��ݳ��ƻ�");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("�����ݳ��ƻ�");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("ɾ���ݳ��ƻ�");
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 14); printf("������мƻ�");
	}
	else if (order == 13) {
		i == 0 ? i = 5 : i = i;//��������
		i > 5 ? i = 1 : i = i;
		set_position(36, 4);
		SetColor(10, 0);
		printf("��Ʊ��ͳ��");
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("�ݳ��������ѯ");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("Ʊ���ѯ������");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("����ͳ�����ѯ");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 12); printf("�ݳ��ƻ������");
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 14); printf("�ҵ��˺ż�����");
	}
	else {
		print_re();
	}
	return i;
}

int select_seat(Studio *p) {//�б�λ��  �� -1   �� -2   �� 1    �� 2    ESC 0   �س�3  ����ֵ��ʾ�Ƿ񱣴�
	char num[15][30] = { 0 }; int choice, i, j, flag = 0,cnt = 0;
	if (p == NULL) { return flag; }
	Seat *k = p->element.seat_head->next;
	for (i = 1; i <= p->element.seatx; i++) {
		for (j = 1; j <= p->element.seaty; j++) {
			num[i][j] = k->seat_condition; k = k->next;
		}
	}
	set_position(0, 0); catch_cursor();
	i = 1, j = 1;//  i ��ǰ����   j  ��ǰ����
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD position;
	position = info.dwCursorPosition;//����֤COORD�洢������λ��XΪ�ֽ���  YΪ����
	while ((choice = turn_page(),1)) {
		hide_cursor();
		if (choice == -1 && i != 0) {
			position.Y--; i--; set_position(position);
		}
		else if (choice == -2 && j != 0) {//�� -1   �� -2   �� 1    �� 2    ESC 0   �س�3
			position.X -= 2; j--; set_position(position);
		}
		else if (choice == 1 && i != p->element.seatx) {
			position.Y++; i++; set_position(position);
		}
		else if (choice == 2 && j != p->element.seaty) {
			position.X += 2; j++; set_position(position);
		}
		else if (choice == 0) {
			position.Y = p->element.seatx + 1; position.X = 0;
			set_position(position);
			if (enquiry(1)) {//�Ƿ񱣴�����
				flag = 1;
				k = p->element.seat_head->next;
				/*for (i = 1; i <= p->element.seatx; i++) {
					for (j = 1; j <= p->element.seaty; j++) {
						printf("%2d", num[i][j]);
					}printf("\n");
				}*///����
				for (i = 1; i <= p->element.seatx; i++) {
					for (j = 1; j <= p->element.seaty; j++) {
						k->seat_condition = (seat_conditions)num[i][j]; if (num[i][j] == 1) { cnt++; }
						k = k->next;
					}
				}
			}
			p->element.seatsum = cnt;
			return flag;
		}
		else if (choice == 3) {
			clear_seat(position, num[i][j]);
			switch (num[i][j]) {
			case 0:num[i][j] = 1; break;
			case 1:num[i][j] = 9; break;
			case 9:num[i][j] = 0; break;
			}
		}
		Sleep(100); catch_cursor();
	}
}

/*δ���*/
int select_seat(Plan *q, int limit) {//�б�λ��  �� -1   �� -2   �� 1    �� 2    ESC 0   �س�3  ����ֵ��ʾ����Ʊ��  limit �������
	char num[15][30] = { 0 }, str[20]; int choice, i, j, flag = 0, cnt = 0, cntt = 0,judge=0;
	sprintf(str, "%d", q->element.studio_ID); Studio *p = search_studio(str,0);
	if (p == NULL) { return flag; }
	Seat *k = p->element.seat_head->next;
	for (i = 1; i <= p->element.seatx; i++) {
		for (j = 1; j <= p->element.seaty; j++) {
			num[i][j] = k->seat_condition; k = k->next;//������λ 1 2   ����λ9   ����λ0
		}
	}
	Ticket *t = q->element.ticket_head->next;
	for (t; t; t = t->next) {
		if (t->ticket_status == TICKET_sold)
			num[t->seatx][t->seaty] == 1?num[t->seatx][t->seaty]=-1:num[t->seatx][t->seaty]=-2;
		//����λ��Ʊ 1 2  ����λ��Ʊ-1 -2  ����λ 0  ����λ9
	}
	set_position(0, 0); catch_cursor();
	i = 1, j = 1;//  i ��ǰ����   j  ��ǰ����
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD position;
	position = info.dwCursorPosition;//����֤COORD�洢������λ��XΪ�ֽ���  YΪ����
	while ((choice = turn_page(), 1)) {
		hide_cursor();
		if (choice == -1 && i != 0) {
			position.Y--; i--; set_position(position);
		}
		else if (choice == -2 && j != 0) {//�� -1   �� -2   �� 1    �� 2    ESC 0   �س�3
			position.X -= 2; j--; set_position(position);
		}
		else if (choice == 1 && i != p->element.seatx) {
			position.Y++; i++; set_position(position);
		}
		else if (choice == 2 && j != p->element.seaty) {
			position.X += 2; j++; set_position(position);
		}
		else if (choice == 0) {
			position.Y = p->element.seatx + 1; position.X = 0;
			set_position(position);
			if (enquiry(1)) {//�Ƿ񱣴�����
				//����λ��Ʊ 1 2  ����λ��Ʊ-1 -2  ����λ 0  ����λ9
				Ticket *t = q->element.ticket_head->next;
				for (t; t; t = t->next) {
					if (t->ticket_status != (ticket_statuses)num[t->seatx][t->seaty]) {//�������ۼ�¼

					}
					switch (num[t->seatx][t->seaty]) {
					case -2:
					case -1:t->ticket_status = TICKET_sold; break;
					case 1:
					case 2: t->ticket_status = TICKET_available; break;
					default:print_re(); break;
					}
					if (t->ticket_status == TICKET_available)cnt++;
				}
				q->element.ticket_head->price = cnt;
			}
			return flag;
		}
		else if (choice == 3) {//����λ��Ʊ 1 2  ����λ��Ʊ-1 -2  ����λ 0  ����λ9
			if (flag == limit) {
				set_position(18, 1);
				printf("��Ǹ��һ����๺��%d��Ʊ\n",limit);
				set_position(position);
			}
			clear_ticket(position, num[i][j]);
			switch (num[i][j]) {
			case -2:num[i][j] = 2; flag--; break;
			case -1:num[i][j] = 1; flag--; break;
			case 1:num[i][j] = -1; flag++; break;
			case 2:num[i][j] = -2; flag++; break;
			default:
				set_position(18,1);
				printf("��Ǹ������ѡ���λ��\n");
				set_position(position); break;
			}
		}
		Sleep(100); catch_cursor();
	}
}

inline  void clear_seat(COORD position, char status) {//COORD  ��ǰλ��   status ��λ״̬
	switch (status) {//��λ0   ����1    ��9
	case 0:printf("��"); break;
	case 1:printf("��"); break;
	case 9:printf("  "); break;
	}
	set_position(position);
}

inline  void clear_ticket(COORD position, char status) {//COORD  ��ǰλ��   status Ʊ״̬
	switch (status) {//����λ��Ʊ 1 2  ����λ��Ʊ-1 -2  ����λ 0  ����λ9
	case 1:printf("��"); break;
	case 2:printf("��"); break;
	}
	set_position(position);
}

inline int turn_page() {//��ҳ��     �� -1   �� -2   �� 1    �� 2    ESC 0   �س�3
	int highlight = 1;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;//���������¼��ṹ��
	DWORD res;//���巵�ؼ�¼
	while (true) {
		ReadConsoleInput(handle, &event, 1, &res);      //��ȡ�����¼�  
		if (event.EventType == KEY_EVENT){      //�����ǰ�¼��Ǽ����¼�  
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_UP && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//���¡�  
				return -1;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_LEFT && event.Event.KeyEvent.bKeyDown == (BOOL)true) {
				return -2;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//���¡� 
				return 1;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//���¡� 
				return 2;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true) //����ESC  
			{
				return 0;
			}
			else if (event.Event.KeyEvent.uChar.AsciiChar == 13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//���»س�  
				return 3;
			}
		}
	}
}

//0-��ɫ, 1-��ɫ,   2-��ɫ,      3-ǳ��ɫ,     4-��ɫ,   5-��ɫ,   6-��ɫ,   7-��ɫ,
//8-��ɫ, 9-����ɫ, 10-����ɫ,   11-��ǳ��ɫ   12-����ɫ 13-����ɫ 14-����ɫ 15-����ɫ*/
void SetColor(short foreColor, short backColor){
	HANDLE winHandle;                  //���
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);     //���ÿ���̨�ı�������
}

POINT get_position() {//�õ���ǰ�������
	POINT point;
	GetCursorPos(&point);
	return point;
}

void set_position(short x, short y){//���ù��λ��
	HANDLE winHandle;                  
	COORD position = { x,y };
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(winHandle, position);
	//CloseHandle(winHandle);
}

inline void set_position(COORD position) {//���ù��λ��
	HANDLE winHandle;
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(winHandle, position);
	//CloseHandle(winHandle);
}

void hide_cursor() {//���ع��
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
	//CloseHandle(hOut);
}

void catch_cursor() {//��ʾ���
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &cci);
	//CloseHandle(hOut);
}

/*
void Clear(int x, int y, int rowCount)
{
	int i, j;
	for (i = 0; i<rowCount; ++i)
	{
		SetPosition(x, y + i);
		for (j = 0; j<70; ++j)
			printf(" ");
	}
}
*/