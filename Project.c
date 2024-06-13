 #include <stdio.h>
#include <string.h>
#include <conio.h>

struct student
{
    int ID;
    char name[50];
    int assignment, midterm, finalterm;
    float average;
    char grade;
};

FILE *file;

char cal_grade(float average);
void input(struct student*s);
void display(struct student st);
void write_student();
void display_all();
void display_search(int n);
void update_student();
void delete_student();
void final_result();
void result_menu();
void entry_menu();


int main()  //Author: Arpo Roy
{
    char username[15];
    char password[12];


    printf("Enter your username:\n");
    scanf("%s",&username);

    printf("Enter your password:\n");
    scanf("%s",&password);
    if(strcmp(username,"NSuER")==0) //Username: defaultNSUer
    {
        if(strcmp(password,"221")==0) //Password: 221
        {
            printf("\nWelcome. Logged in Successfully!");
        }
        else
        {
            printf("\nWrong password");
        }
    }
    else
    {
        printf("\nUser does not exist");
}

    int choice;
    do
    {
        printf("\n\nMain Menu");
        printf("\n1.Result Menu");
        printf("\n2.Entry/Edit Menu");
        printf("\n3.Exit");
        printf("\nPlease select any key between 1 to 3: ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                result_menu();
                break;
            case 2:
                entry_menu();
        }
    }
    while (choice != 3);
    return 0;
}

char cal_grade(float average)  //Author: Anindita Das Mishi
{
    if (average >= 93)
        return 'A';
    else if (average >= 90)
        return 'A-';
    else if (average >= 87)
        return 'B+';
    else if (average >= 83)
        return 'B';
    else if (average >= 80)
        return 'B-';
    else if (average >= 77)
        return 'C+';
    else if (average >= 73)
        return 'C';
    else if (average >= 70)
        return 'C-';
    else if (average >= 67)
        return 'D+';
    else if (average >= 60)
        return 'D';
    else
        return 'F';
}

void input(struct student *s) //Author: Abul Kashim
{
    printf("\nEnter the student ID: ");
    scanf("%d", &s->ID);
    fflush(stdin);
    printf("\nEnter the name of student: ");
    gets(s->name);
    printf("\nEnter the marks of Assignments: ");
    scanf("%d", &s->assignment);
    printf("\nEnter the marks of Mid term: ");
    scanf("%d", &s->midterm);
    printf("\nEnter the marks of Final term: ");
    scanf("%d", &s->finalterm);
    s->average = (s->assignment + s->midterm + s->finalterm) / 3.0;
    s->grade = cal_grade(s->average);
}

void display(struct student st)  //Author: Anindita Das Mishi
{
    printf("\nID of student : %d", st.ID);
    printf("\nName of student : %s", st.name);
    printf("\nScore of assignments : %d", st.assignment);
    printf("\nScore of Mid term : %d", st.midterm);
    printf("\nScore in Final term : %d", st.finalterm);
    printf("\nAverage score : %0.2f", st.average);
    printf("\nGrade : %c", st.grade);
}

void write_student()  //Author: Arpo Roy
{
    struct student data;
    file = fopen("student.dat", "ab");
    printf("\n\nPlease enter the details of student \n");
    input(&data);
    fwrite(&data, sizeof(data), 1, file);
    fclose(file);
    printf("\nStudent Record Has Been Created ");
}

void display_all()  //Author: Anindita Das Mishi
{
    struct student data;
    printf("\n\nDISPLAY ALL RECORD!!!\n");
    file = fopen("student.dat", "rb");
    while((fread(&data,sizeof(data),1,file))>0)
    {
        display(data);
        printf("\n====================================\n");
    } fclose(file);
}

void display_search(int n) //Author: Arpo Roy
{
    struct student data;
    int flag = 0;
    file = fopen("student.dat", "rb");
    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        if (data.ID == n)
        {
            display(data);
            flag = 1;
        }
    }
    fclose(file);
    if (flag == 0)
        printf("\nRecord does not exist");
}

void modify_student() //Author: Abul Kashim
{
    struct student data;
    int no, found = 0;

    printf("\nTo Modify ");
    printf("\nPlease Enter The roll number of student: ");
    scanf("%d", &no);
    file = fopen("student.dat", "rb+");
    while ((fread(&data, sizeof(data), 1, file)) > 0 && found == 0)
    {
        if (data.ID == no)
        {
            display(data);
            printf("\nPlease enter the new details of student \n");
            input(&data);
            fseek(file,  - (long)sizeof(data), 1);
            fwrite(&data, sizeof(data), 1, file);
            printf("\n Record Updated");
            found = 1;
        }
    }
    fclose(file);
    if (found == 0)
        printf("\n Record Not Found ");
}

void delete_student() //Author: Abul Kashim
{
    int no;
    struct student data;
    FILE *file2;
    printf("\n\nDelete Record");
    printf("\nPlease Enter The roll number you want to delete: ");
    scanf("%d", &no);
    file = fopen("student.dat", "rb");
    file2 = fopen("temp.dat", "wb");
    rewind(file);
    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        if (data.ID != no)
        {
            fwrite(&data, sizeof(data), 1, file2);
        }
    }
    fclose(file2);
    fclose(file);
    remove("student.dat");
    rename("temp.dat", "student.dat");
    printf("\nRecord deleted.");
}

void class_result() //Author: Anindita Das Mishi
{
    struct student data;
    file = fopen("student.dat", "rb");
    if (file == NULL)
    {
        printf(
            "ERROR!!! FILE COULD NOT BE OPEN\n\n Go To Entry Menu to create File");
        printf("\n\n Program is closing ....");
        return;
    }

    printf("\nALL STUDENTS RESULT \n");
    printf("==============================================================\n");
    printf("R.No.\tName\t\tTest1\tTest2\tTest3\tAverage\tGrade\n");
    printf("==============================================================\n");

    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        printf("%-7d %-15s %-7d %-7d %-7d %-7.2f  %-1c\n", data.ID,
            data.name, data.assignment, data.midterm, data.finalterm,
            data.average, data.grade);
    }
    fclose(file);
}

void result_menu()  //Author: Arpo Roy
{
    int rno, ans;
    char choice;

    printf("\n\nResult Menu");
    printf("\n1. Class Result\n2. Student Report Card\n3.Back to Main Menu");
    printf("\nEnter Choice (1-3)? ");
    scanf("%d", &ans);
    switch (ans)
    {
        case 1:
            class_result();
            break;
        case 2:
            do
            {
                char ans;
                printf("\n\nEnter roll number of student: ");
                scanf("%d", &rno);
                display_search(rno);
                printf("\nDo you want to see more result (y/n)?: ");
                fflush(stdin);
                scanf("%c", &choice);
            }while (choice == 'y' || choice == 'Y');
            break;
        case 3:
            break;
        default:
            printf("\a");
    }
}

void entry_menu()  //Author: Abul Kashim
{
    int choice;
    printf("\n\nEntry Menu");
    printf("\n1.Create Student Record");
    printf("\n2.Display all students records");
    printf("\n3.Search student record ");
    printf("\n4.Modify student record");
    printf("\n5.Delete Student record");
    printf("\n6.Back to main menu");
    printf("\nEnter your choice (1-6): ");
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
            write_student();
            break;
        case 2:
            display_all();
            break;
        case 3:
            {
                int num;
                printf("\n\nPlease enter the roll number: ");
                scanf("%d", &num);
                display_search(num);
            }
            break;
        case 4:
            modify_student();
            break;
        case 5:
            delete_student();
            break;
        case 6:
            break;
        default:
            printf("\a");
            entry_menu();
    }
}
