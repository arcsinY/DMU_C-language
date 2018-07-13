#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
	char num[15];
	char name[15];
	char major[10];
	int classNo;
	int score[3];
	struct student *next;
}STU;

STU* CreateList(void);
STU* CreateList_from_file(char* file_path);
void Output(STU* p);
void Output_all(STU* pHead);
int judge_file_name_txt(char* file_path);
int judge_file_name_dat(char* file_path);
STU* save(STU* pHead, char* file_path, char* num);
void save_all(STU* pHead, char* file_path);
STU* Fetch(char* file_path);
STU* Search_num(STU* pHead, char* num);
void InsertList(STU* pHead, STU* astu);
void Delete_num(STU* pHead, char* num);
STU* Search_major_subject_score(STU* pHead, char* major, int course, int score);
void Delete_class_subject_score(STU* pHead, int classNo, int course, int score);
STU* Max(STU* pHead, int course);

int main()
{
	printf("欢迎使用学生信息管理系统!\n");
	STU* pHead = (STU*)malloc(sizeof(STU));
	int choice;
	while (1)
	{
		printf("0.从文本中读取学生信息\n");
		printf("1.从键盘输入学生信息\n");
		printf("2.输出全部学生信息\n");
		printf("3.将指定学号学生信息存入文件\n");
		printf("4.全部学生信息存入文件\n");
		printf("5.读取二进制文件中学生信息\n");
		printf("6.查找指定学号的学生\n");
		printf("7.插入学生信息\n");
		printf("8.删除指定学号学生信息\n");
		printf("9.查找某个专业的、某门课程的成绩小于某个分数的学生\n");
		printf("10.删除某个班级的、某门课程的成绩小于某个分数的学生\n");
		printf("11.查找某门课程的最高成绩\n");
		printf("请选择功能:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
		{
			char file_path[50];
			printf("请输入文本文件路径:");
			scanf("%s", file_path);
			while (judge_file_name_txt(file_path) == 0)   //判断输入文件路径是否正确
			{
				printf("请重新输入:");
				scanf("%s", file_path);
			}				
			pHead = CreateList_from_file(file_path);
			printf("\n\n\n\n");
			break;
		}
		case 1:
		{
			pHead = CreateList();
			printf("\n\n\n\n");
			break;
		}
		case 2:
		{
			Output_all(pHead);
			printf("\n\n\n\n");
			break;
		}
		case 3:
		{
			char num[15];
			char file_path[50];
			printf("请输入要保存的学生学号:");
			scanf("%s", num);
			printf("请输入保存文件路径:");
			scanf("%s", file_path);
			while (judge_file_name_dat(file_path) == 0)   //判断输入文件路径是否正确
				scanf("%s", file_path);
			STU* s = save(pHead, file_path, num);
			if (s == NULL)
				printf("没有学号为%s的学生", num);
			printf("\n\n\n\n");
			break;
		}
		case 4:
		{
			char file_path[50];
			printf("请输入保存文件路径:");
			scanf("%s", file_path);
			while (judge_file_name_dat(file_path) == 0)   //判断输入文件路径是否正确
			{
				printf("请重新输入:");
				scanf("%s", file_path);
			}
			save_all(pHead, file_path);
			printf("\n\n\n\n");
			break;
		}
		case 5:
		{
			char file_path[50];
			printf("请输入读取文件路径:");
			scanf("%s", file_path);
			while (judge_file_name_dat(file_path) == 0)   //判断输入文件路径是否正确
			{
				printf("请重新输入:");
				scanf("%s", file_path);
			}
			STU* H = (STU*)malloc(sizeof(STU));
			H = Fetch(file_path);
			printf("读出的学生信息为:\n");
			Output_all(H);
			printf("\n\n\n\n");
			break;
		}
		case 6:
		{
			char num[15]; STU* s;
			printf("请输入要查找的学号:");
			scanf("%s", num);
			s = Search_num(pHead, num);
			if (s == NULL)
				printf("没有学号为%s的学生\n", num);
			else
			{
				printf("学号\t\t姓名\t\t专业\t\t班级\t成绩1\t成绩2\t成绩3\n");
				Output(s);
			}
			printf("\n\n\n\n");
			break;
		}
		case 7:
		{
			STU* s = (STU*)malloc(sizeof(STU));
			printf("请输入学生学号:");
			scanf("%s", s->num);
			printf("请输入学生姓名:");
			scanf("%s", s->name);
			printf("请输入学生专业:");
			scanf("%s", s->major);
			printf("请输入学生班级:");
			scanf("%d", &s->classNo);
			for (int j = 0; j < 3; ++j)
			{
				printf("请输入学生第%d门课的成绩：", j + 1);
				scanf("%d", &s->score[j]);
			}
			InsertList(pHead, s);
			printf("插入后的学生信息为:\n");
			Output_all(pHead);
			printf("\n\n\n\n");
			break;
		}
		case 8:
		{
			char num[15];
			printf("请输入要删除的学生学号:");
			scanf("%s", num);
			Delete_num(pHead, num);
			printf("删除后剩余的学生信息为:\n");
			Output_all(pHead);
			printf("\n\n\n\n");
			break;
		}
		case 9:
		{
			STU* H = (STU*)malloc(sizeof(STU));
			char major[10];
			int course, score;
			printf("请输入专业:");
			scanf("%s", major);
			printf("请输入课程号(1-3):");
			scanf("%d", &course);
			while (course < 1 || course>3)
			{
				printf("\n输入不合法，请重新输入:");
				scanf("%d", &course);
			}
			printf("请输入分数:");
			scanf("%d", &score);
			H = Search_major_subject_score(pHead, major, course - 1, score);
			if (H->next)
				printf("没有找到该学生\n");
			else
			{
				printf("找到的学生有:\n");
				Output_all(H);
			}
			printf("\n\n\n\n");
			break;
		}
		case 10:
		{
			int classNo;
			int course;
			int score;
			printf("请输入班级号(1或2):");
			scanf("%d", &classNo);
			while (classNo < 1 || classNo > 2)
			{
				printf("\n输入不合法，请重新输入:");
				scanf("%d", &classNo);
			}
			printf("请输入课程号(1-3):");
			scanf("%d", &course);
			while (course < 1 || course > 3)
			{
				printf("\n输入不合法，请重新输入:");
				scanf("%d", &course);
			}
			printf("请输入成绩:");
			scanf("%d", &score);
			Delete_class_subject_score(pHead, classNo, course - 1, score);
			printf("删除后剩余学生有:\n");
			Output_all(pHead);
			printf("\n\n\n\n");
			break;
		}
		case 11:
		{
			STU* max;
			int course;
			printf("请输入课程号(1-3):");
			scanf("%d", &course);
			while (course < 1 || course > 3)
			{
				printf("\n输入不合法，请重新输入:");
				scanf("%d", &course);
			}
			max = Max(pHead, course - 1);
			printf("该学生信息为:\n");
			printf("学号\t\t姓名\t\t专业\t\t班级\t成绩1\t成绩2\t成绩3\n");
			Output(max);
			break;
		}
		default:
			printf("\n输入有错误，重新输入:");
			scanf("%d", &choice);
			printf("\n\n\n\n");
			break;
		}
	}
	return 0;
}


STU* CreateList(void)
{	
	STU* pHead = (STU*)malloc(sizeof(STU));
	STU* first = NULL;    //首节点的指针，每次插到first前面
	int n;
	printf("请输入学生人数:");
	scanf("%d", &n);
	for(int i = 0;i<n;++i)
	{
		STU* p = (STU*)malloc(sizeof(STU));
		printf("请输入学生学号(从大到小):");
		scanf("%s", p->num);
		if (i > 0)     //判断是否是由大到小输入的
		{
			if (strcmp(first->num, p->num) <= 0)
			{
				printf("学号应该是从大到小输入!\n");
				--i;
				continue;
			}
		}
		printf("\n请输入学生姓名:");
		scanf("%s", p->name);
		printf("\n请输入学生专业:");
		scanf("%s", p->major);
		printf("\n请输入学生班级:");
		scanf("%d", &p->classNo);
		for (int j = 0; j < 3; ++j)
		{
			printf("\n请输入学生第%d门课的成绩：", j+1);
			scanf("%d", &p->score[j]);
		}
		p->next = first;
		first = p;   //新插入的变为首节点
		pHead->next = p;
	}
	return pHead;
}


STU* CreateList_from_file(char* file_path)
{
	FILE* fp = fopen(file_path, "r");
	if (fp == NULL)
	{
		printf("文件打开失败!");
		return NULL;
	}
	STU* pHead = (STU*)malloc(sizeof(STU));
	STU* first = NULL;
	while (!feof(fp))
	{
		STU* p = (STU*)malloc(sizeof(STU));
		fscanf(fp, "%s %s %s %d %d %d %d", p->num, p->name, p->major, &p->classNo, &p->score[0], &p->score[1], &p->score[2]);
		if (first)
		{
			if (strcmp(first->num, p->num) <= 0)
			{
				printf("文件中的学号应该是从大到小的,请修改文件!\n");
				free(p);
				return NULL;
			}
		}
		p->next = first;
		first = p;
		pHead->next = p;
	}
	return pHead;
}


void Output(STU *p) 
{
	printf("%-15s%-15s\t%-15s\t%d\t%d\t%d\t%d\n", p->num, p->name, p->major, p->classNo, p->score[0], p->score[1], p->score[2]);
}


void Output_all(STU * pHead)
{
	STU *p;
	p = pHead->next;
	printf("学号\t\t姓名\t\t专业\t\t班级\t成绩1\t成绩2\t成绩3\n");
	while (p != NULL)
	{//依次输出学生信息
		Output(p);
		p = p->next;//将指针指向下一个结点
	}
}


int judge_file_name_txt(char* file_path)
{
	int flag = 1;       //路径正确的标志变量，等于0为不正确，重新输入
	int tag = 0;        //标志字符串中的一对'\'是第一个还是第二个，1为第一个，0为第二个
	for (int i = 0; i < strlen(file_path) - 1; ++i)
	{
		if (file_path[i] == '\\')
			tag = 1 - tag;
		if (file_path[i] == '\\' && file_path[i + 1] != '\\' && tag)  //判断是否用\\隔开
		{
			flag = 0;
			printf("路径间要用\\隔开\n");
			break;
		}
	}
	//判断后缀名，应该为.txt，其他不行
	if (file_path[strlen(file_path) - 1] != 't' || file_path[strlen(file_path) - 2] != 'x' || file_path[strlen(file_path) - 3] != 't' || file_path[strlen(file_path) - 4] != '.')
	{
		flag = 0;
		printf("后缀名错误\n");
	}
	return flag;
}


int judge_file_name_dat(char* file_path)
{
	int flag = 1;       //路径正确的标志变量，等于0为不正确，重新输入
	int tag = 0;        //标志字符串中的一对'\'是第一个还是第二个，1为第一个，0为第二个
	for (int i = 0; i < strlen(file_path) - 1; ++i)
	{
		if (file_path[i] == '\\')
			tag = 1 - tag;
		if (file_path[i] == '\\' && file_path[i + 1] != '\\' && tag)  //判断是否用\\隔开
		{
			flag = 0;
			printf("路径间要用\\隔开\n");
			break;
		}
	}
	//判断后缀名，应该为.dat，其他不行
	if (file_path[strlen(file_path) - 1] != 't' || file_path[strlen(file_path) - 2] != 'a' || file_path[strlen(file_path) - 3] != 'd' || file_path[strlen(file_path) - 4] != '.')
	{
		flag = 0;
		printf("后缀名错误\n");
	}
	return flag;
}


STU* save(STU* pHead, char* file_path, char* num)
{
	FILE* fp = fopen(file_path, "ab");     //文件是追加模式
	if (fp == NULL)
	{
		printf("文件打开失败!");
		return NULL;
	}
	STU* p = pHead->next;   //用指针p搜索链表，找到对应学号节点
	while (p)
	{
		if (strcmp(p->num, num) == 0)
		{
			fwrite(p, sizeof(STU), 1, fp);
			fclose(fp);
			return p;
		}
		p = p->next;
	}
	fclose(fp);
	return NULL;
}


void save_all(STU* pHead, char* file_path)
{
	FILE* fp = fopen(file_path, "wb");
	if (fp == NULL)
	{
		printf("文件打开失败!");
		return;
	}
	STU* p = pHead->next;
	while (p)
	{
		fwrite(p, sizeof(STU), 1, fp);
		p = p->next;
	}
	fclose(fp);
}


STU* Fetch(char* file_path)
{
	STU* pHead = (STU*)malloc(sizeof(STU));
	STU* rear = pHead;   //尾指针
	STU* temp = (STU*)malloc(sizeof(STU));
	FILE* fp = fopen(file_path, "rb");
	if (fp == NULL)
	{
		printf("文件打开失败!");
		return NULL;
	}
	fread(temp, sizeof(STU), 1, fp);    //先要事先读一个，才能判断文件是否结束
	while (!feof(fp))    //判断文件是否读取结束
	{
		STU* p = (STU*)malloc(sizeof(STU));
		*p = *temp;
		p->next = NULL;  //顺序建立链表
		rear->next = p;
		rear = p;
		fread(temp, sizeof(STU), 1, fp);
	}
	fclose(fp);
	return pHead;
}


STU* Search_num(STU* pHead, char* num)
{
	STU* p = pHead->next;
	while (p)
	{
		if (strcmp(num, p->num) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}


void InsertList(STU* pHead, STU* astu)
{
	STU* p = pHead->next;
	if (strcmp(p->num, astu->num) > 0)   //第一个节点学号就比要插入的大，插在最前面
	{
		astu->next = p;
		pHead->next = astu;
		return;
	}
	while (p->next)
	{
		if (strcmp(p->num, astu->num) < 0 && strcmp(p->next->num, astu->num) > 0)   //当前节点学号比输入的小，下一个比输入的大，输入的插在中间
		{
			astu->next = p->next;
			p->next = astu;
			return;
		}
		p = p->next;
	}
	p->next = astu;
	astu->next = NULL;
}


void Delete_num(STU* pHead, char* num)
{
	STU* pre = pHead;
	STU* p = pHead->next;
	while (p)
	{
		if (strcmp(p->num, num) == 0)
		{
			pre->next = p->next;
			free(p);
			return;
		}
		p = p->next;
		pre = pre->next;
	}
}


STU* Search_major_subject_score(STU* pHead, char* major, int course, int score)
{
	STU* H = (STU*)malloc(sizeof(STU));   //返回一个小链表的头指针
	H->next = NULL;
	STU* rear = H;    //尾指针
	STU* p = pHead->next;
	while (p)
	{   //找到一个满足要求的学生，加入到以H为头指针的链表中
		if (strcmp(p->major, major) == 0 && p->score[course] < score)
		{
			STU* temp = (STU*)malloc(sizeof(STU));
			*temp = *p;    //复制一份这个学生节点，加入到小链表中
			temp->next = NULL;
			rear->next = temp;
			rear = temp;
		}
		p = p->next;
	}
	return H;
}


void Delete_class_subject_score(STU* pHead, int classNo, int course, int score)
{
	STU* pre = pHead;   //p的前一个节点
	STU* p = pHead->next;   //p用来遍历链表
	STU* front = pHead->next->next;    //front指向p的后一个节点
	while (p)
	{
		if (p->classNo == classNo && p->score[course] < score)
		{
			pre->next = front;
			free(p);   //释放内存
			p = front;
			if(front)   //p走到最后时，front=NULL，这时不能移动front
				front = front->next;
		}
		else
		{
			p = p->next;
			if(front)
				front = front->next;
			pre = pre->next;
		}
	}
}

STU * Max(STU * pHead, int course)
{
	STU* p = pHead->next;
	STU* max = p;
	p = p->next;
	while (p)
	{
		if (p->score[course] > max->score[course])
			max = p;
		p = p->next;
	}
	return max;
}