// 剧院票务管理系统.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"statements.h"
List list; 
data_account PRESENT;//当前用户
struct tm *now;
int main(){
	//show_welcome();
	//play_bgm();
	initialize();
	//print_instruction(1);
	process_all();
	draw_ticket(list.plan_head->next,list.plan_head->next->element.ticket_head->next);
	//plan_viewer(list.plan_head);
	//print_ticket(list.plan_head->next); go_on();
	//process_conducter();
    return 0;
}

