#include"stdafx.h"
#include"statements.h"

void import_all() {//����������Ϣ
	import_key();
	import_account();
	import_program();
	import_studio_and_seat();
    import_plan_and_ticket();
	//import_plan_and_ticket_bin();
}

void initialize() {//ȫ����ʼ��
	initialize_window();
	initialize_linklist();
	initialize_present();
	clean_plan_atFirst();
	import_all();
	sort_plan(list.plan_head);
	sort_plan(list.plan_tem_head);
}

void initialize_present() {//��ʼ����ǰ�˻�
	PRESENT.UID[0] = '\0';
	PRESENT.username[0] = PRESENT.password[0] = '\0';
	PRESENT.user_type = USER_frozen;
}

void initialize_window() {//��ʼ�����ڴ�С//�������С
	system("mode 88, 25");
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD font = { 12,24 };
	//GetConsoleScreenBufferInfo;
}