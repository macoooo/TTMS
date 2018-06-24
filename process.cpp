#include"stdafx.h"
#include"statements.h"

void process_all() {//登录过程
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

void process_sign() {//登录过程
	int re = 0, cnt = 0;
	re = sign_judge();
	while ((re <= 0 || re > 4) && cnt < 3) {
		cnt++;
		re = sign_judge();
	}
	play_bgm();
	switch (re) {
	case 0:account_appeal(); break;//账号申诉
	case 1:process_admin(); break;
	case 2:process_manager(); break;
	case 3:process_conducter(); break;
	case 4:process_customer(); break;
	default:
			print_re(); exit(1);
		break;
	}
}

///////////////////////////////////////系统管理员过程

void process_admin() {//管理员过程
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

void process_account() {//账户管理过程        //在这里调用你写的链表操作
	int choice;
	char *str = NULL;
	Account *p;
	while (1) {
		show_account();
		choice = choice_judge(5);
		switch (catch_cursor(), choice) {
		case 0: break;
		case 1: printf("\n\n请输入要查找的账号ID或名称:\n"); p = search_account(str = get_string(1, 14, 0), 1);  free(str);  print_account(p); break;
		case 2: printf("\n\n请输入要修改的账号ID或名称:\n"); p = search_account(str = get_string(1, 14, 0), 1);  free(str); modify_account(p); break;
		case 3: show_account_type(); choice = get_num(1, 4, 1, 1); add_account(choice); break;
		case 4: delete_account(); break;
		case 5:break;
		}
		if (choice == 0)break;if (choice < 5)go_on();
	}
}

///////////////////////////////////////剧院经理

void process_manager() {//剧院经理过程
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
			catch_cursor(); printf("\n是否退出登录?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1){go_on(); break;} go_on();
		}
	}
}

void process_program() {//剧目查询及管理过程
	int choice; char *str;
	while (1) {
		show_program();
		choice = choice_judge(3);
		if (choice != 0)catch_cursor();
		switch (choice) {
		case 0:break;
		case 1:printf("\n请输入要查询的影片ID或名称:\n"); print_program(search_program(str = get_string(1, 30, 0), 1), 1); free(str); break;
		case 2:printf("\n请输入要修改的影片ID或名称:\n"); modify_program(search_program(str = get_string(1, 30, 0), 1)); free(str); break;
		case 3:add_program(); break;
		case 4:printf("\n请输入要删除的影片ID或名称:\n"); delete_program(search_program(str = get_string(1, 30, 0), 1)); free(str); break;
		case 5:hide_cursor(); program_viewer(); break;
		}if (choice == 0)break; if (choice < 5)go_on();
	}
}

void process_studio() {//影厅查询及管理过程
	int choice; char *str = NULL;
	while (1) {
		show_studio();
		choice = choice_judge(4); 
		if(choice != 0)catch_cursor();
		switch (choice){
		case 0:break;
		case 1:printf("\n请输入要查询的放映厅ID或名称：\n"); print_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 2:printf("\n请输入要修改的放映厅ID或名称：\n"); modify_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 3:add_studio();break;
		case 4:printf("\n请输入要删除的放映厅ID或名称：\n"); delete_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 5:hide_cursor(); studio_viewer(); break;
		}if (choice == 0)break; if (choice < 5) go_on();
	}
}

void process_plan() {//放映计划查询及管理过程
	int choice, num; Plan *p = NULL;//clean_plan();
	while (1) {
		show_plan();
		choice = choice_judge(12);
		if (choice != 0)catch_cursor();
		switch (choice) {
		case 0:break;
		case 1:printf("\n\n1.当前演出计划 2.过期演出计划\n请选择查询范围：");
			num = get_num(1, 2, 1, 1); if (num == 1)p = list.plan_head; else p = list.plan_tem_head; process_plan_inquiry(p); break;
		case 2:printf("请输入要修改的演出计划ID:"); modify_plan(search_plan(get_num(1, 999999, 1, 6) , 1, list.plan_head)); break;
		case 3:add_plan(); break;
		case 4:printf("\n\n请输入要删除的演出计划ID:"); num = get_num(1, 999999, 1, 6); p = search_plan(num, 0, list.plan_head); if (p == NULL) { p = search_plan(num, 0, list.plan_tem_head); } delete_plan(p); break;
		case 5:printf("\n\n1. 浏览当前计划 2.浏览过期计划\n请选择："); num = get_num(1, 2, 1, 1); if (num == 1)p = list.plan_head; else p = list.plan_tem_head; hide_cursor(); plan_viewer(p); break;
		}if (choice == 0)break;go_on(); 
	}
}

void process_plan_inquiry(Plan *head) {//查询演出计划
	int num; char *str = NULL;
	printf("1.演出计划ID  2.剧目名称/ID 3.演出厅名称/ID 4.日期\n请选择检索方式：");
	num = get_num(1, 4, 1, 1);
	if (num < 4) {
		printf("请输入名称/ID：");
		search_plan(str = get_string(1, 30, 0), num, head); free(str);
	}
	else {
		printf("请输入日期:"); str = get_date();
		search_plan(str, num, head); free(str);
	}
}

///////////////////////////////////////////售票员

void process_conducter() {
	int choice; Plan *p = NULL;
	while (1) {
		show_conducter();
		choice = choice_judge(13);
		switch (choice) {
		case 0:break;
		case 1: printf("\n\n"); process_plan_inquiry(list.plan_head); break;//ticket_viewer(); break;
		case 2:printf("\n\n请输入要查询的演出ID:"); p = search_plan(get_num(1, 999999, 1, 6), 1, list.plan_head); if (p)print_ticket(p); break;
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
	printf("请输入你的邀请码:\n");
	str = get_string(1, 12, 0);
	if (save_invitation_code(str)) {
		add_account(4);
		printf("注册成功！\n");
		printf("请妥善保存你的UID哦！\n");
	}
	else {
		printf("抱歉，您没有邀请码， 请获得邀请码之后再来注册！\n");
		go_on();
	}
	free(str);
}