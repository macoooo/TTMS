#include"stdafx.h"
#include"statements.h"

/*void show_welcome() {//��ӭ����
	char str[20];
	strcpy_s(str, "����κ̴��Ժ");
	DWORD tem=0,font=2;
	COORD pos = { 10,10 };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	set_position(10,10);
	CONSOLE_FONT_INFOEX setfont;
	CONSOLE_FONT_INFO getfont;
	GetCurrentConsoleFont(handle, true,&getfont);
	//if (FillConsoleOutputAttribute(handle, , 20, pos, &tem) == 0) { printf("fail"); }
	setfont.nFont = getfont.nFont;
	//setfont.dwFontSize = GetConsoleFontSize(handle, font);
	SetCurrentConsoleFontEx(handle, true,&setfont);//��������
	for (int i = 0; i < strlen(str); i++) {//������ɫ
		SetConsoleTextAttribute(handle, (i+2 )* 0x10);  //���ÿ���̨�ı�������
		printf("%c", str[i]);
	}
	//ScrollConsoleScreenBuffer(handle);
	puts(str);
}*/

void show_welcome() {//��ӭ����
	initgraph(1070, 600);//Ĭ�ϴ��ڴ�С
	setbkcolor(WHITE);
	cleardevice();
	IMAGE yinghua, title;
	loadimage(&title, _T("jpg"), _T("title"));
	loadimage(&yinghua, _T("jpg"), _T("yinghua"));
	putimage(350, 100, &yinghua);
	Sleep(2000);
	cleardevice();
	putimage(280, 150, &title);
	Sleep(3000);
	closegraph();
}

void show_bye() {
	initgraph(1070, 600);//Ĭ�ϴ��ڴ�С
	setbkcolor(WHITE);
	cleardevice();
	IMAGE yinghua, title;
	loadimage(&title, _T("jpg"), _T("title"));
	loadimage(&yinghua, _T("jpg"), _T("yinghua"));
	putimage(280, 150, &title);
	Sleep(2000);
	cleardevice();
	putimage(350, 100, &yinghua);
	Sleep(3000);
	closegraph();
}

void show_main() {//������
	hide_cursor();
	WCHAR title[40] = TEXT("�κ����");
	SetConsoleTitle(title);
	system("color 08");
	system("cls");
	set_position(32, 5);
	SetColor(14, 0);
	printf("�� �� �� �� �� �� Ժ");
	set_position(40, 8);
	SetColor(11, 0);
	printf("��¼");
	set_position(40, 10);
	SetColor(7, 0);
	printf("ע��");
	set_position(40, 12);
	printf("�뿪");
}

void show_sign() {//��¼����
	rewind(stdin);
	system("cls");
	SetColor(10, 0);
	set_position(30,8);
	printf("�����ǳ�:");
	set_position(30, 10);
	printf("��¼����:");
	SetColor(13, 0);
	catch_cursor();//��ʾ���
}

void show_register()
{
	system("CLS");
	printf("\n\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("\t\t                     �˺�ע��                     \n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * \n");
}

void show_customer() {//�˿�������
	system("cls");

}


void abandon() {//����
	system("color f8");
	char str[90], i;
	WCHAR title[40] = TEXT("�κ���ȴ�ӰԺ");
	strcpy_s(str, "�κ���ȴ�ӰԺ��ӭ��");
	set_position(25, 10);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(title);
	//settextstyle(80, 0, _T("����"), 0, 0, 0, true, true, true);				//������ʽ
	for (i = 0; i < (char)strlen(str); i++) {
		printf("%c", str[i]);
	}
	for (i = 0; i < 2; i++) {
		system("color ff"); Sleep(300);
		system("color fe"); Sleep(300);
		system("color fa"); Sleep(300);
		system("color fc"); Sleep(300);
		system("color fd"); Sleep(300);
		system("color fb"); Sleep(300);
	}
	system("color f8");
}

/////////////////////////////////////manager

void show_manager() {//��Ժ����������
	system("cls");
	rewind(stdin);
	hide_cursor();
	set_position(36,4);
	SetColor(10,0);
	printf("��ѯ�����");
	SetColor(11, 0);
	set_position(34,6);
	printf("��Ŀ��ѯ������");
	SetColor(7, 0);
	set_position(34, 8);
	printf("Ӱ����ѯ������");
	set_position(34, 10);
	printf("�ݳ���ѯ������");
	set_position(34,12);
	printf("����ͳ�����ѯ");//���ݳ��ƻ���ѯ
	set_position(34, 14);
	printf("�ҵ��˺ż�����");
}

void show_program() {//��Ŀ��ѯ���������
	rewind(stdin);
	hide_cursor();
	system("cls");
	set_position(35, 4);
	SetColor(10, 0);
	printf("��Ŀ��ѯ������");
	SetColor(11, 0);
	set_position(36, 6);
	printf("��ѯ��Ŀ��Ϣ");
	SetColor(7, 0);
	set_position(36, 8);
	printf("�޸ľ�Ŀ��Ϣ");
	set_position(36, 10);
	printf("������Ŀ��Ϣ");
	set_position(36, 12);
	printf("ɾ����Ŀ��Ϣ");
	set_position(36, 14);
	printf("������о�Ŀ");
}

void show_studio(){//Ӱ����ѯ���������
	rewind(stdin);
	hide_cursor();
	system("cls");
	set_position(35, 4);
	SetColor(10, 0);
	printf("Ӱ����ѯ������");
	SetColor(11, 0);
	set_position(36, 6);
	printf("��ѯӰ����Ϣ");
	SetColor(7, 0);
	set_position(36, 8);
	printf("�޸�Ӱ����Ϣ");
	set_position(36, 10);
	printf("����Ӱ����Ϣ");
	set_position(36, 12);
	printf("ɾ��Ӱ����Ϣ");
	set_position(36, 14);
	printf("�������Ӱ��");
}

void show_plan() {//�ݳ��ƻ���ѯ���������
	rewind(stdin);
	hide_cursor();
	system("cls");
	set_position(35, 4);
	SetColor(10, 0);printf("�ݳ���ѯ������");
	SetColor(11, 0);set_position(36, 6);printf("��ѯ�ݳ��ƻ�");
	SetColor(7, 0);set_position(36, 8);printf("�޸��ݳ��ƻ�");
	set_position(36, 10);printf("�����ݳ��ƻ�");
	set_position(36, 12);printf("ɾ���ݳ��ƻ�");
	set_position(36, 14);printf("������мƻ�");
}

///////////////////////////////////admin

void show_admin() {//ϵͳ����Ա������
	system("cls");
	rewind(stdin);
	hide_cursor();
	set_position(35, 4);
	SetColor(10, 0);
	printf("��ѯ�����");
	SetColor(11, 0);
	set_position(34, 6);
	printf("ϵͳ�û�����");
	SetColor(7, 0);
	set_position(34, 8);
	printf("��¼��¼��ѯ");
	set_position(34, 10); 
	printf("�����ҵ���Ϣ");
}

void show_account() {//�˻���ѯ���������
	rewind(stdin);
	hide_cursor();
	system("cls");
	set_position(38, 4);
	SetColor(10, 0);
	printf("�û�����");
	SetColor(11, 0);
	set_position(36, 6);
	printf("��ѯ�û���Ϣ");
	SetColor(7, 0);
	set_position(36, 8);
	printf("�޸��û���Ϣ");
	set_position(36, 10);
	printf("�����û���Ϣ");
	set_position(36, 12);
	printf("ɾ���û���Ϣ");
	set_position(36, 14);
	printf("��������û�");
}

void show_account_type(){//�˻�����ѡ�����
	system("CLS");
	printf("\t\t|-----��ѡ����Ҫ����˻�������-----|\n");
	printf("\t\t|-----------��Ժ�����밴2----------|\n");
	printf("\t\t|------------��ƱԱ�밴3-----------|\n");
	printf("\t\t|-----------ϵͳ����Ա�밴1--------|\n");
	printf("\t\t|----------- �˿��밴4-------------|\n");
	printf("������:");
}

///////////////////////////////////conducter

void show_conducter() {//��ƱԱ������
	system("cls");
	rewind(stdin);
	hide_cursor();
	set_position(36, 4);
	SetColor(10, 0);
	printf("��Ʊ��ͳ��");
	SetColor(11, 0);
	set_position(34, 6);
	printf("�ݳ��������ѯ");
	SetColor(7, 0);
	set_position(34, 8);
	printf("Ʊ���ѯ������");
	set_position(34, 10);
	printf("����ͳ�����ѯ");
	set_position(34, 12);
	printf("�ݳ��ƻ������");
	set_position(34, 14);
	printf("�ҵ��˺ż�����");
}

//����
/*void show_program_types() {//��ʾ��Ŀ����   ���choice_judege����ѡ��
//	printf("��ѡ���Ŀ����\n");
//	int x = get_positionx(), y = get_positiony();
//	SetColor(11, 0);
//	printf("��Ӱ");
//	set_position(x + 5, y);
//}*/


