#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <conio.h>

typedef struct booklist  
{  
    char num[20]; //学号 
    char name[20]; //姓名 
    char sex[10]; //性别 
    char fete[20]; //出生日期 
	char college[20]; //学院 
    char major[20]; //专业 
}StudentS;

typedef struct student  
{  
    StudentS onestudent; //数据域 
    struct student *next; //指针域 
}Student; 

void check();

Student *SearchStudent (Student *listptr,char num[]) ; /*返回查找学生位置*/

int StudentSearch(Student *firstptr); /*查找学生*/

int AddStudent(Student *listptr, StudentS student); /*连接写入学生信息的节点*/

int StudentAdd(Student *listptr,FILE *fp); /*添加学生信息*/

int StudentPrint(Student *listptr); /*输出所有学生信息*/

int DeleteStudent(Student *listptr,char num[]); /*查找要删除学生信息所在节点*/

int StudentDelete(Student *listptr,FILE *fp); /*删除寻找到的节点*/

int choice(); /*菜单*/

int addFile(FILE *fp,Student *firstptr);   /*主要用来加载文件中存放的学生信息*/ 


void check()  /*安全验证*/
{  
   char userName[5];//用户名 
   char userPWD[5];//密码  
   int i,sum;
   for(i = 1; i < 4; i++)        
   {  
      //用户名和密码均为abcde 
        printf("****************************************************\n");
        printf("****             (用户名和密码均为abcde)         ****\n");  
        printf("****             请输入您的用户名:               ****\n"); 
        printf("****************************************************\n"); 
        gets(userName);  
        printf("****************************************************\n"); 
        printf("****             请输入您的密码:                 ****\n");
        printf("****************************************************\n");   
        gets(userPWD);  
        if ((strcmp(userName,"abcde")==0) && (strcmp(userPWD,"abcde")==0))//验证用户名和密码  
        {  
            printf("*用户名和密码正确，显示主菜单*\n");  
            return;  
        }  
        else  
        {  
            if (i < 3)  
            {  
                printf("用户名或密码错误，提示用户重新输入");  
                printf("用户名或密码错误，请重新输入!");  
            }  
            else  
            {  
                printf("连续3次输错用户名或密码，退出系统。");  
                printf("您已连续3次将用户名或密码输错，系统将退出!");  
                exit(1);   
            }  
        }  
   }  
}

Student *SearchStudent (Student *listptr,char num[])  /*返回查找学生位置*/
{  
    while(listptr!= NULL)           //当不为空指针时继续循环 
    { 
        if(strcmp(listptr->onestudent.num,num)==0)  
            return listptr;  //返回找寻成功的节点指针 
        else  
            listptr=listptr->next;  //失败则后移指针继续 
        return  0;
    } 
}  

int StudentSearch(Student *firstptr)  /*查找学生*/
{  
    Student *ptr;  
    char studentnum[20];  
    printf("请输入学号:");  
    scanf("%s",&studentnum);  
    ptr=searchBook(firstptr,studentnum);  
    if (ptr!=NULL)  
    {  
        printf("找到了!\n");  
        printf("学号:%s\n",ptr->onestudent.num);  
        printf("姓名:%s\n",ptr->onestudent.name);  
        printf("性别:%s\n",ptr->onestudent.sex);
        printf("出生年月:%s\n",ptr->onestudent.fete); 
        printf("学院:%s\n",ptr->onestudent.college);  
        printf("专业:%s\n",ptr->onestudent.major);  
    }  
    else  
        printf("查无此人!\n"); 
	return 0; 
}

int AddStudent(Student *listptr, StudentS student) /*连接写入学生信息的节点*/ 
{  
    while(listptr->next!=0)
        listptr=listptr->next; 
    listptr->next=(Student *)malloc(sizeof(Student)); //创建动态空间  
    listptr->next->onestudent=student;  
    listptr->next->next=NULL;  
    return 0;
}  

int StudentAdd(Student *listptr,FILE *fp)   /*添加学生信息*/
{  
    int p;  
    StudentS student;  
    printf("请输入学号:\n");  
    scanf("%s",student.num);  
    printf("请输入姓名:\n");  
    scanf("%s",student.name);  
    printf("请输入性别:\n");       //写入学生信息 
    scanf("%s",student.sex);
    printf("请输入出生年月:\n");
    scanf("%s",student.fete);
    printf("请输入学院:\n");
    scanf("%s",student.college);
    printf("请输入专业:\n");
    scanf("%s",student.major);  
    p=AddStudent(listptr,student);  
    if (p==0)  
    {     
        //将加入的学生写到文件中保存 
        fprintf(fp,"%s %s %s %s %s %s\n",student.num,student.name,student.sex,student.fete,student.college,student.major);  
        printf("添加学生成功!\n");  
    }  
    else  
        printf("添加学生失败!\n");  
    return 0;
}  

int StudentPrint(Student *listptr)  /*输出所有学生信息*/
{  
    listptr=listptr->next;
    while(listptr!= NULL)
    {                                     //打印全部学生信息 
        printf("%s   %s   %s   %s   %s   %s\n",listptr->onestudent.num,listptr->onestudent.name,
        listptr->onestudent.sex,listptr->onestudent.fete,listptr->onestudent.college,listptr->onestudent.major);
        listptr=listptr->next;
    }
    return 0;
}

int DeleteStudent(Student *listptr,char num[])  /*查找要删除学生信息所在节点*/
{  
    while(listptr->next!=NULL)  
    {  
        if (strcmp(listptr->next->onestudent.num,num)==0)  //通过编号寻找要删除的结点 
        {  
            listptr->next=listptr->next->next;   //通过将后一结点前移来实现结点的删除
            return 0;  
        }  
        else  
            listptr=listptr->next;                 //未找到则继续移向下一个结点
    }  

        return -1;  
}  

int StudentDelete(Student *listptr,FILE *fp)  /*删除寻找到的节点*/
{  
    char studentnum[20];  
    int p;  
    StudentS onestudent;  
    printf("请输入编号:");  
    scanf("%s",&studentnum);  
    p=DeleteStudent(listptr,studentnum);  
    if (!p)                           //对返回值进行判断
    {  
        FILE *fpbak;  
        if ((fpbak=fopen("c:/dao","a+"))==NULL)  //返回指针为空则表示不能打开文件
            printf("文件打开失败!\n");  
        fseek(fp,0,SEEK_SET);   //移到文件开始  
        while((fscanf(fp,"%s %s %s %s %s %s\n",&onestudent.num,&onestudent.name
              ,&onestudent.sex,&onestudent.fete,&onestudent.college,&onestudent.major))!=EOF)  
        {                       //当学生信息库文件未到结束时继续循环
            if (strcmp(onestudent.num,studentnum)!=0)  
            {  
                fprintf(fpbak,"%s %s %s %s %s %s\n",onestudent.num,onestudent.name,
                        onestudent.sex,onestudent.fete,onestudent.college,onestudent.major);  
            }                   //将所有学生信息输出到指定文件中
        }  
        fclose(fp);           //关闭文件，释放内存 
        fclose(fpbak); 
          if (remove("c:/student.txt" ))   //删除失败返回非0
        {  
            printf("删除文件成功!\n");  
            return ;  
        }  
        else  
            if (rename("c:/studentsbak.txt" ,"c:/students.txt" ))  //重命名失败返回非0值
            {  
                printf("重命名失败!\n");  
                return ;  
            }  
        printf("删除成功!\n");  
    }  
    else  
        printf("查无此书!\n");  
    return 0;
}  

int choice()   /*菜单*/
{   
    int c; 
    printf("******************************************************\n");
    printf("***                                                ***\n");
    printf("***                  1.遍历图书                    ***\n"); 
    printf("***                  2.查找图书                    ***\n");  
    printf("***                  3.添加图书                    ***\n");  
    printf("***                  4.删除图书                    ***\n");  
    printf("***                  0.退出程序                    ***\n");  
    printf("***                  请选择序号:                   ***\n");
    printf("***                                                ***\n");
    printf("******************************************************\n");
    scanf("%d",&c); 
    return c ;  
    printf("\n"); 
}

int addFile(FILE *fp,Student *firstptr)  /*主要用来加载文件中存放的学生信息*/  
{  
    StudentS onestudent;  
    while((fscanf(fp,"%s %s %s %s %s %s\n",&onestudent.num,&onestudent.name
          ,&onestudent.sex,&onestudent.fete,&onestudent.college,&onestudent.major))!=EOF)  
    {  
        while(firstptr->next!=0)  
        firstptr=firstptr->next;  
        firstptr->next=( Student *)malloc(sizeof(Student)); //分配内存空间 
        firstptr->next->onestudent=onestudent;  
        firstptr->next->next=0;  
    }  
    return 0;  

}

int main()  
{
    printf("***********************图书管理系统*********************\n");
    check(); 
    int ch;  
    Student first; 
    Student *stptr; 
    first.next=0;
    Student *firstptr = &first;              
    FILE *fp;  
    if ((fp=fopen("c:/students.txt" ,"a+"))==NULL)
        printf("文件打开失败!");      //a+ 以附加方式打开可读写的文件,若文件不存在 
    addFile(fp,firstptr);           //则会建立该文件，如果文件存在，写入的数据 
    while(1)               //会被加到文件尾，即文件原先的内容会被保留。（EOF符保留）
    {  
        system("cls");   //清屏
        fflush(stdin);   //清空缓存区 
        ch=choice();  
        switch (ch)  
        {  
        case 1:
            StudentPrint(firstptr);
            break;
        case 2:  
            StudentSearch(firstptr);  
            break;  
        case 3:  
            StudentAdd(firstptr,fp);  
            break;  
        case 4:  
            StudentDelete(firstptr,fp);  
            break;  
        case 0:  
            printf("谢谢使用...\n");  
            exit(0);  
        default:  
            printf("请输入正确序号!");  
        }  
        system("pause"); /*等待用户按键并返回*/ 
    }  
    return 0;  
} 


/**

1
张三
男
1998-08
通信工程学院
信工1701
2
李四
男
1999-02
电子工程学院
微电子1703
3
王二
女
2000-07
计算机学院
计科1706



*/ 