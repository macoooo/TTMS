#include"stdafx.h"
#include"statements.h"

void print_re() {//����bug����
	printf("��ʵ�����仰�ǲ����ܵ�\n");
	printf("���ִ�������ϵ������qvq  \nQQ740721665��863139668"); rewind(stdin); go_on();
}

void print_examinput() {//�Ƿ����뱨��
	printf("���벻����Ҫ������������\n");
	rewind(stdin);
}

inline void go_on() {//�����������
	printf("�����������\n");
	rewind(stdin);
	getch();
	getch();
}

void exam_NULL(void *p, int choice) {//��ָ�뱨��   0 malloc   1�ļ�
	if (p == NULL) {
		if(choice == 0)printf("���ܷ�������ڴ���\n");
		else if (choice == 1) {printf("���ļ�ʧ��\n"); print_re();}
		else {print_re();}
		exit(1);
	}
}

int enquiry(int i) {//�ж��Ƿ���б��β���   i==1   enquiry   i==2 warnning
	if (i == 1)
		printf("�Ƿ�ȷ�ϱ��β���?(0/1):");
	else if (i == 2)
		printf("�ò������ɻָ����Ƿ����?(0/1):");
	else
		print_re();
	int judge = 0;
	judge = get_num(0,1,1,1);
	return judge;
}

void print_ok() {//��ʾ�����ɹ�
	printf("�����ɹ��˵�˵!\n");
	rewind(stdin);
}

void print_instruction(int i) {//��ʾ˵��
	if (i == 1) {
		hide_cursor();
		system("cls");
		set_position(20, 6);
		printf("����˵��");
		printf("\n\n		����������������������ݹ��ѡ����λ   ESC�˳�\n\n		\
���ʾ������λ  ���ʾ��λ��   �س����ı���λ״̬   \n\n		");
		go_on();
	}
}

void print_planhead() {//��ӡ�ݳ��ƻ���ͷ
	printf("    ===============================================================================\n");
	printf("    | ID  |         ��Ŀ����       |�ݳ������|��Ʊ��|��Ʊ��|  �ݳ�����  |��ʼʱ��|\n\n");
}

void ����() {//��ȥ��������������
	int ��ȥ=5;
	printf("%d", ��ȥ);
}


//����

//void print_label(int i) {//��ӡ��ǩ�б�     i  = 1 ��Ӱ       2 ���        3���ֻ�
//	if (i == 1)
//	printf("ϲ�� ���� ��� ���� ���� �ֲ�\n\
//��¼ �ƻ� ���� �ഺ ���� ����\n");
//	else if (i == 2) 
//	printf("��ѡ���ǩ:");
//	rewind(stdin);
//}
