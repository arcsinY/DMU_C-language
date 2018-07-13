#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char num[15];
	char name[15];
	char major[10];
	int classNo;
	int score[3];
}STU;

void Input(STU *p);  //创建学生信息数组
void Output(STU *p, char* num, int num_stu);    //输出所有学生信息
void Output_all(STU *p, int num_stu);  //输出所有学生信息
void Save_all(char* file_name, STU *p, int num_stu);    //保存所有学生信息
void Save(char* file_name, STU *p, char* num, int num_stu);   //保存指定学号的学生信息
void Fetch(char* file_name, STU *p, int n);   //读取第n个学生信息
void Max(STU *p, int course, int num_stu);    //求所有学生某门课程的最高分和分数最高的学生的姓名
void Sort_select(STU *p, char* major_name, int num_stu);    // 对某个专业的学生，按总平均成绩由低到高进行简单选择排序
void Sort_buble(STU *p, int classNo, int num_stu);      //对某个班级的学生，按总平均成绩由高到低进行起泡排序
void Sort_insert(STU *p, int classNo, int course, int num_stu);   //对某个班级的学生，按某门课程成绩由低到高进行直接插入排序
void Search(STU *p, int classNo, int score, int num_stu);      //实现班级和成绩的综合查找（如1班，总分240分以上同学）
void Read_from_file(char *file_path, STU *p, int num_stu);    //从文本文件中读取所有学生信息

int main()
{
	STU *arr;       //学生数组
	int num_stu;     //学生个数
	int choice;
	while(1)
	{
		printf("0.从指定文本文件中读取全部学生信息\n");
		printf("1.输入学生信息                     2.输出指定学号的学生信息\n");
		printf("3.输出全部学生信息                 4.全部学生信息存入文件\n");
		printf("5.将指定学号的学生信息存入文件        6.从文件中随机读取某个学生的信息\n");
		printf("7.求所有学生某门课程的最高分和分数最高的学生的姓名\n");
		printf("8.对某个专业的学生，按总平均成绩由低到高进行简单选择排序\n");
		printf("9.对某个班级的学生，按总平均成绩由高到低进行起泡排序\n");
		printf("10.对某个班级的学生，按某门课程成绩由低到高进行直接插入排序\n");
		printf("11.实现班级和成绩的综合查找（如1班，总分240分以上同学）\n");
		printf("请选择功能:");
		scanf("%d", &choice);
		switch(choice)
		{
		case 0:
		{
			char file_path[100];
			printf("请输入文本路径:");
			scanf("%s", file_path);
			while (1)
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
				if (flag == 0)
				{
					printf("请重新输入:");
					scanf("%s", file_path);
				}
				else
					break;
			}
			printf("请输入学生个数:");
			scanf("%d", &num_stu);
			arr = (STU*)malloc(sizeof(STU)*num_stu);
			Read_from_file(file_path, arr, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 1:
		{
			printf("请输入学生个数:");
			scanf("%d", &num_stu);
			arr = (STU*)malloc(sizeof(STU)*num_stu);
			for(int i = 0;i<num_stu;++i)
			{
				Input(&arr[i]);
			}
			Output_all(arr, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 2:
		{
			char num[15];      
			printf("请输入要找的学生学号:");
			scanf("%s", num);
			Output(arr, num, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 3:
		{
			Output_all(arr, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 4:
		{
			char file_path[100];
			printf("请输入存储路径(要用\\隔开):");
			scanf("%s", file_path);	
			while (1)
			{
				int flag = 1;       //路径正确的标志变量，等于0为不正确，重新输入
				int tag = 0;
				for (int i = 0; i < strlen(file_path) - 1; ++i)     //判断是否用\\隔开
				{
					if (file_path[i] == '\\')
						tag = 1 - tag;
					if (file_path[i] == '\\' && file_path[i + 1] != '\\' && tag)
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
				if (flag == 0)
				{
					printf("请重新输入:");
					scanf("%s", file_path);
				}
				else
					break;
			}
			Save_all(file_path, arr, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 5:
		{	
			char file_path[100];
			char num[15];
			printf("请输入存储路径(要用\\隔开):");
			scanf("%s", file_path);
			while (1)
			{
				int flag = 1;       //路径正确的标志变量，等于0为不正确，重新输入
				int tag = 0;
				for (int i = 0; i < strlen(file_path) - 1; ++i)     //判断是否用\\隔开
				{
					if (file_path[i] == '\\')
						tag = 1 - tag;
					if (file_path[i] == '\\' && file_path[i + 1] != '\\' && tag)
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
				if (flag == 0)
				{
					printf("请重新输入:");
					scanf("%s", file_path);
				}
				else
					break;
			}
			printf("请输入要存储的学生学号:");
			scanf("%s", num);
			Save(file_path, arr, num, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 6:
		{	
			char file_path[100];
			int n;
			printf("请输入读取文件路径(要用\\隔开):");
			scanf("%s", file_path);
			while (1)
			{
				int flag = 1;       //路径正确的标志变量，等于0为不正确，重新输入
				int tag = 0;
				for (int i = 0; i < strlen(file_path) - 1; ++i)     //判断是否用\\隔开
				{
					if (file_path[i] == '\\')
						tag = 1 - tag;
					if (file_path[i] == '\\' && file_path[i + 1] != '\\' && tag)
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
				if (flag == 0)
				{
					printf("请重新输入:");
					scanf("%s", file_path);
				}
				else
					break;
			}
			printf("请输入要读取的学生位置:");
			scanf("%d", &n);
			if(n > num_stu)
				printf("输入不合法!\n");
			else
				Fetch(file_path, arr, n);
			printf("\n\n\n\n");
			break;
		}
		case 7:
		{
			int n;   //课程序号(1-3)
			printf("请输入课程号(1-3):");
			scanf("%d", &n);
			while (n < 1 || n>3)
			{
				printf("\n输入不合法，请重新输入:");
				scanf("%d", &n);
			}
			Max(arr, n, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 8:
		{
			char major[10];
			printf("请输入专业名称:");
			scanf("%s", major);
			Sort_select(arr, major, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 9:
		{
			int classNo;
			printf("请输入班级号(1或2):");
			scanf("%d", &classNo);
			while (classNo < 1 || classNo > 2)
			{
				printf("\n输入不合法，请重新输入:");
				scanf("%d", &classNo);
			}
			Sort_buble(arr, classNo, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 10:
		{
			int classNo;
			int course;
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
			Sort_insert(arr, classNo, course-1, num_stu);
			printf("排序后的学生信息为:\n");
			Output_all(arr, num_stu);
			printf("\n\n\n\n");
			break;
		}
		case 11:
		{
			int classNo;
			int score;
			printf("请输入班级号(1-2):");
			scanf("%d", &classNo);
			while (classNo < 1 || classNo > 2)
			{
				printf("\n输入不合法，请重新输入:");
				scanf("%d", &classNo);
			}
			printf("请输入成绩:");
			scanf("%d", &score);
			Search(arr, classNo, score, num_stu);
			printf("\n\n\n\n");
			break;
		}
		default:
			printf("输入选择有误!\n");
			printf("\n\n\n\n");
			break;
		}
	}
	free(arr);
	return 0;
}

void Input(STU *p)
{
	printf("请输入学生学号:");
	scanf("%s", p->num);
	printf("请输入学生姓名:");
	scanf("%s", p->name);
	printf("请输入学生专业:");
	scanf("%s", p->major);
	printf("请输入学生班级(1或2):");
	scanf("%d", &p->classNo);
	printf("请输入学生三门课成绩:");
	scanf("%d %d %d", &p->score[0], &p->score[1], &p->score[2]);
}


void Output(STU *p, char* num, int num_stu)
{
	for(int i = 0;i<num_stu;++i)
	{
		if(strcmp(p[i].num, num) == 0)
		{
			printf("学号     姓名       专业       班级    成绩1    成绩2    成绩3\n");
			printf("%s    %s      %s      %d       %d       %d      %d\n", p[i].num, p[i].name, p[i].major, p[i].classNo, p[i].score[0], p[i].score[1], p[i].score[2]);
			return;
		}
	}
	printf("没有学号为%s的学生", num);
}


void Output_all(STU *p, int num_stu)
{
		printf("学号     姓名       专业       班级    成绩1    成绩2    成绩3\n");
		for(int i = 0;i<num_stu;++i)
			printf("%s    %s      %s      %d       %d       %d      %d\n", p[i].num, p[i].name, p[i].major, p[i].classNo, p[i].score[0], p[i].score[1], p[i].score[2]);
}


void Save_all(char* file_name, STU *p, int num_stu)
{
		FILE* fp = fopen(file_name, "wb");
		if(fp == NULL)
		{
			printf("打开文件错误\n");
			return;
		}
		for(int i = 0;i<num_stu;++i)
			fwrite(&p[i], sizeof(STU), 1, fp);
		fclose(fp);
}


void Save(char* file_name, STU *p, char* num, int num_stu)
{
	FILE* fp = fopen(file_name, "wb");
	if(fp == NULL)
	{
		printf("打开文件错误\n");
		return;
	}
	for(int i = 0;i<num_stu;++i)
	{
		if(strcmp(p[i].num, num) == 0)
		{
			fwrite(&p[i], sizeof(STU), 1, fp);
			fclose(fp);
			return;
		}
	}
	printf("没有学号为%s的学生\n", num);
}


void Fetch(char* file_name, STU *p, int n)
{
	STU s;
	FILE* fp = fopen(file_name, "rb");
	if(fp == NULL)
	{
		printf("打开文件错误\n");
		return;
	}
	fseek(fp, (n-1) * sizeof(STU), 0);
	fread(&s, sizeof(STU), 1, fp);
	printf("学号     姓名    专业    班级   成绩1    成绩2    成绩3\n");
	printf("%s       %s     %s      %d     %d      %d       %d", s.num, s.name, s.major, s.classNo, s.score[0], s.score[1], s.score[2]);
	fclose(fp);
}


void Max(STU *p, int course, int num_stu)
{
	int max = 0;
	char name[15];
	for(int i = 0;i<num_stu;++i)
	{
		if(p[i].score[course-1]>max)
		{
			max = p[i].score[course - 1];
			strcpy(name, p[i].name);
		}
	}
	printf("第%d号课程最高成绩学生为:%s, 成绩为:%d", course, name, max);
}


void Sort_select(STU *p, char* major_name, int num_stu)
{
	double t, *aver;
	STU a;
	int count = 0;   //对指定专业的学生计数
	STU* major_stu = (STU*)malloc(sizeof(STU)*num_stu);     //指定专业的学生单独保存一次
	for(int i = 0;i<num_stu;++i)
	{ 
		if (strcmp(p[i].major, major_name) == 0)
		{
			major_stu[count++] = p[i];
		}
	}
	if (count == 0)
	{
		printf("\n没有这个专业\n");
		return;
	}
	aver = (double*)malloc(sizeof(double)*count);
	for (int i = 0; i<count; i++)   //计算平均分
	{
		aver[i] = (major_stu[i].score[0] + major_stu[i].score[1] + major_stu[i].score[2]) / 3.0;
	}
	for (int i = 0; i<count - 1; i++)
	{
		int k = i;       //确定要比较的数，先选择第一个数进行比较。
		for (int j = i; j < count; j++)
		{
			if (aver[k] > aver[j])
				k = j;  //找到为排序的数据中最小项的位置
		}
		t = aver[i]; aver[i] = aver[k]; aver[k] = t;      //aver[i]和aver[k]交换
		a = p[i]; p[i] = p[k]; p[k] = a;          //交换对应结构体
	} 
	printf("学号     姓名       专业     班级   成绩1   成绩2   成绩3   平均成绩\n");
	for (int i = 0; i < count; i++)
		printf("%s     %s     %s    %d     %d      %d       %d      %.2lf\n", major_stu[i].num, major_stu[i].name, major_stu[i].major, major_stu[i].classNo, major_stu[i].score[0], major_stu[i].score[1], major_stu[i].score[2], aver[i]);
	free(aver);
	free(major_stu);
}


void Sort_buble(STU *p, int classNo, int num_stu)
{
	STU *stu_class_ave = (STU*)malloc(sizeof(STU) * num_stu);//按平均成绩排序后的某个班级的学生信息
	STU temp;
	double t;
	double *aver;   //保存平均分的数组
	int count = 0;//指定班级的学生个数
	for (int i = 0; i < num_stu; i++)    //找到指定班级所有人
	{
		if (p[i].classNo == classNo)
			stu_class_ave[count++] = p[i];
	}
	if (count == 0)
	{
		printf("\n这个班级没有学生\n");
		return;
	}
	aver = (double*)malloc(sizeof(double)*count);
	for (int i = 0; i<count; i++)//计算实际元素的平均分
		aver[i] = (stu_class_ave[i].score[0] + stu_class_ave[i].score[1] + stu_class_ave[i].score[2]) / 3.0;
	int flag = 1;
	for (int i = 0; i<count - 1 && flag == 1; i++) {
		flag = 0;    //标志变量，一次比较中是否进行了交换
		for (int j = 0; j<count - 1 - i; j++) {
			if (aver[j]<aver[j + 1])     //小的交换到后面
			{
				temp = stu_class_ave[j];
				stu_class_ave[j] = stu_class_ave[j+1];
				stu_class_ave[j+1] = temp;
				t = aver[j];
				aver[j] = aver[j+1];
				aver[j+1] = t;
				flag = 1;
			}
		}
	}
	printf("学号     姓名       专业       班级   成绩1   成绩2   成绩3   平均成绩\n");
	for (int i = 0; i < count; ++i)
	{
		printf("%s     %s     %s      %d     %d      %d       %d     %.2lf\n", stu_class_ave[i].num, stu_class_ave[i].name, stu_class_ave[i].major, stu_class_ave[i].classNo, stu_class_ave[i].score[0], stu_class_ave[i].score[1], stu_class_ave[i].score[2], aver[i]);
	}
	free(aver);
	free(stu_class_ave);
}


void Sort_insert(STU *p, int classNo, int course, int num_stu)
{
	int count = 0;  //实际元素个数
	STU temp;
	STU *stu_class_subject = (STU*)malloc(sizeof(STU) * num_stu);   //按某门课程成绩排序后的某个班级的学生信息
	for (int i = 0; i<num_stu; i++) 
		if (p[i].classNo == classNo)          //计数
			stu_class_subject[count++] = p[i];
	if (count == 0)
	{
		printf("\n这个班级没有学生\n");
		return;
	}
	for (int i = 1; i<count; ++i)     //插入排序
	{
		temp = stu_class_subject[i];     //临时存储要排序的元素
		int j = i - 1;       //j是已排序好的元素中最后一个元素的下标
		while (j >= 0 && temp.score[course] < stu_class_subject[j].score[course])
		{
			stu_class_subject[j + 1] = stu_class_subject[j];
			--j;
		}
		if(j >= 0 || stu_class_subject[0].score[course] > temp.score[course])
			stu_class_subject[j + 1] = temp;    //插入
	}
	Output_all(stu_class_subject, count);
	free(stu_class_subject);
}


void Search(STU *p, int classNo, int score, int num_stu)
{
	int count = 0;  //实际元素个数
	STU *search = (STU*)malloc(sizeof(STU) * num_stu);
	for (int i = 0; i < num_stu; ++i)
	{
		if (p[i].classNo == classNo)
			search[count++] = p[i];
	}
	if (count == 0)
	{
		printf("\n这个班级没有学生\n");
	}
	int *sum = (int*)malloc(sizeof(int) * count);
	printf("学号    姓名       专业    班级  成绩1   成绩2   成绩3    总分\n");
	for (int i = 0; i < count; ++i)     //计算总分
	{
		sum[i] = search[i].score[0] + search[i].score[1] + search[i].score[2];
		if (sum[i] > score)
			printf("%s   %s     %s     %d      %d      %d      %d     %d\n", search[i].num, search[i].name, search[i].major, search[i].classNo, search[i].score[0], search[i].score[1], search[i].score[2], sum[i]);
	}
}


void Read_from_file(char* file_path, STU *p, int num_stu)
{
	FILE* fp = fopen(file_path, "r");
	if (fp == NULL)
	{
		printf("无法打开文件\n");
		return;
	}
	for (int i = 0; i < num_stu; ++i)
	{
		fscanf(fp, "%s %s %s %d %d %d %d", p[i].num, p[i].name, p[i].major, &p[i].classNo, &p[i].score[0], &p[i].score[1], &p[i].score[2]);
	}
	fclose(fp);
}
