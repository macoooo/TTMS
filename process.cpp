#include"stdafx.h"
#include"statements.h"

void process_all() {//��¼����
	int choice;
	while (1) {
		show_main();
		choice = choice_judge(1);
		switch (choice) {
		case 0:break;
		case 1:process_sign(); break;
		case 2:process_register(); break;
		case 3:show_bye(); system("taskkill /im cmd.exe /T /F");
		}
	}
}

void process_sign() {//��¼����
	int re = 0, cnt = 0;
	re = sign_judge();
	while ((re <= 0 || re > 4) && cnt < 3) {
		cnt++;
		re = sign_judge();
	}
	play_bgm();
	switch (re) {
	case 0:account_appeal(); break;//�˺�����
	case 1:process_admin(); break;
	case 2:process_manager(); break;
	case 3:process_conducter(); break;
	case 4:process_customer(); break;
	default:
			print_re(); exit(1);
		break;
	}
}

///////////////////////////////////////ϵͳ����Ա����

void process_admin() {//����Ա����
	int choice;
	while (1) {
		show_admin();
		choice = choice_judge(11);
		switch (choice) {
		case 0:break;
		case 1:process_account(); break;
		}if (choice == 0)break;
	}
}

void process_account() {//�˻��������        //�����������д���������
	int choice;
	char *str = NULL;
	Account *p;
	while (1) {
		show_account();
		choice = choice_judge(5);
		switch (catch_cursor(), choice) {
		case 0: break;
		case 1: printf("\n\n������Ҫ���ҵ��˺�ID������:\n"); p = search_account(str = get_string(1, 14, 0), 1);  free(str);  print_account(p); break;
		case 2: printf("\n\n������Ҫ�޸ĵ��˺�ID������:\n"); p = search_account(str = get_string(1, 14, 0), 1);  free(str); modify_account(p); break;
		case 3: show_account_type(); choice = get_num(1, 4, 1, 1); add_account(choice); break;
		case 4: delete_account(); break;
		case 5:break;
		}
		if (choice == 0)break;if (choice < 5)go_on();
	}
}

///////////////////////////////////////��Ժ����

void process_manager() {//��Ժ�������
	int choice;
	while (1) {
		show_manager();
		choice = choice_judge(2);
		switch (choice) {
		case 0:break;
		case 1:process_program(); break;
		case 2: process_studio(); break;
		case 3:process_plan(); break;
		case 4:break;
		}if (choice == 0) {
			catch_cursor(); printf("\n�Ƿ��˳���¼?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1){go_on(); break;} go_on();
		}
	}
}

void process_program() {//��Ŀ��ѯ���������
	int choice; char *str;
	while (1) {
		show_program();
		choice = choice_judge(3);
		if (choice != 0)catch_cursor();
		switch (choice) {
		case 0:break;
		case 1:printf("\n������Ҫ��ѯ��ӰƬID������:\n"); print_program(search_program(str = get_string(1, 30, 0), 1), 1); free(str); break;
		case 2:printf("\n������Ҫ�޸ĵ�ӰƬID������:\n"); modify_program(search_program(str = get_string(1, 30, 0), 1)); free(str); break;
		case 3:add_program(); break;
		case 4:printf("\n������Ҫɾ����ӰƬID������:\n"); delete_program(search_program(str = get_string(1, 30, 0), 1)); free(str); break;
		case 5:hide_cursor(); program_viewer(); break;
		}if (choice == 0)break; if (choice < 5)go_on();
	}
}

void process_studio() {//Ӱ����ѯ���������
	int choice; char *str = NULL;
	while (1) {
		show_studio();
		choice = choice_judge(4); 
		if(choice != 0)catch_cursor();
		switch (choice){
		case 0:break;
		case 1:printf("\n������Ҫ��ѯ�ķ�ӳ��ID�����ƣ�\n"); print_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 2:printf("\n������Ҫ�޸ĵķ�ӳ��ID�����ƣ�\n"); modify_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 3:add_studio();break;
		case 4:printf("\n������Ҫɾ���ķ�ӳ��ID�����ƣ�\n"); delete_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 5:hide_cursor(); studio_viewer(); break;
		}if (choice == 0)break; if (choice < 5) go_on();
	}
}

void process_plan() {//��ӳ�ƻ���ѯ���������
	int choice, num; Plan *p = NULL;//clean_plan();
	while (1) {
		show_plan();
		choice = choice_judge(12);
		if (choice != 0)catch_cursor();
		switch (choice) {
		case 0:break;
		case 1:printf("\n\n1.��ǰ�ݳ��ƻ� 2.�����ݳ��ƻ�\n��ѡ���ѯ��Χ��");
			num = get_num(1, 2, 1, 1); if (num == 1)p = list.plan_head; else p = list.plan_tem_head; process_plan_inquiry(p); break;
		case 2:printf("������Ҫ�޸ĵ��ݳ��ƻ�ID:"); modify_plan(search_plan(get_num(1, 999999, 1, 6) , 1, list.plan_head)); break;
		case 3:add_plan(); break;
		case 4:printf("\n\n������Ҫɾ�����ݳ��ƻ�ID:"); num = get_num(1, 999999, 1, 6); p = search_plan(num, 0, list.plan_head); if (p == NULL) { p = search_plan(num, 0, list.plan_tem_head); } delete_plan(p); break;
		case 5:printf("\n\n1. �����ǰ�ƻ� 2.������ڼƻ�\n��ѡ��"); num = get_num(1, 2, 1, 1); if (num == 1)p = list.plan_head; else p = list.plan_tem_head; hide_cursor(); plan_viewer(p); break;
		}if (choice == 0)break;go_on(); 
	}
}

void process_plan_inquiry(Plan *head) {//��ѯ�ݳ��ƻ�
	int num; char *str = NULL;
	printf("1.�ݳ��ƻ�ID  2.��Ŀ����/ID 3.�ݳ�������/ID 4.����\n��ѡ�������ʽ��");
	num = get_num(1, 4, 1, 1);
	if (num < 4) {
		printf("����������/ID��");
		search_plan(str = get_string(1, 30, 0), num, head); free(str);
	}
	else {
		printf("����������:"); str = get_date();
		search_plan(str, num, head); free(str);
	}
}

///////////////////////////////////////////��ƱԱ

void process_conducter() {
	int choice; Plan *p = NULL;
	while (1) {
		show_conducter();
		choice = choice_judge(13);
		switch (choice) {
		case 0:break;
		case 1: printf("\n\n"); process_plan_inquiry(list.plan_head); break;//ticket_viewer(); break;
		case 2:printf("\n\n������Ҫ��ѯ���ݳ�ID:"); p = search_plan(get_num(1, 999999, 1, 6), 1, list.plan_head); if (p)print_ticket(p); break;
		case 3:break;
		case 4:plan_viewer(list.plan_head); break;
		case 5:break;
		}if (choice == 0)break; go_on();
	}
}

void process_customer() {
	show_customer();
}

void process_register(){
	show_register();
	char *str = NULL;
	printf("���������������:\n");
	str = get_string(1, 12, 0);
	if (save_invitation_code(str)) {
		add_account(4);
		printf("ע��ɹ���\n");
		printf("�����Ʊ������UIDŶ��\n");
	}
	else {
		printf("��Ǹ����û�������룬 ����������֮������ע�ᣡ\n");
		go_on();
	}
	free(str);
}