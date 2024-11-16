//Jimmy Pham
//COMP 2131

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//struct to hold all student information
struct Student
{
    char studentID[10];
    char studentName[30];
    char emailID[30];
    char courseID[10];
    char grade[5];
};

FILE *studentRecord;
bool exitMenu = false;

//Function declaration
void displayMenu();
int enterChoice();
void createFile();
void displayRecord();
void seekRecord();
int fileExists(const char *fileName);
void updateRecord();
void deleteRecordbyID();


int main()
{
    // start as exit = false , exits program when the user wants to exit
    while (!exitMenu)
    {
        displayMenu();
        enterChoice();
    }
    return 0;
}

void displayMenu()
{
    printf("\n\tM A I N M E N U\n");
    printf("1. Create the Binary File\n");
    printf("2. Display the conents of the file\n");
    printf("3. Seek a specific record\n");
    printf("4. Update the contents of the record\n");
    printf("5. Delete a record for a specific name\n");
    printf("6. Exit\n");
    printf("\n\t\tPlease Enter your Choice . . . .\n");

}

int fileExists(const char* fileName)
{
    FILE* file;

    if (file = fopen("studentFile.bin", "r"))
    {
        fclose(file);
        return 1;
    }

    printf("\nFile does not exist. Create a new File first.");
    return 0;
}

int enterChoice() {

    int choice = 0;
    scanf("%d", &choice);
    while (getchar() != '\n');

    while (choice < 1 || choice > 6)
    {
        printf("Invalid choice, Enter a number between 1 to 6: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
    }


    //switch statement for options 
    switch (choice)
    {
    case 1:
        createFile();
        break;
    case 2:
        if (fileExists("studentFile.bin") == 1)
        {
            displayRecord();
        }
    case 3:
        if (fileExists("studentFile.bin") == 1)
        {
            seekRecord();
        }

        break;
    case 4:
        if (fileExists("studentFile.bin") == 1)
        {
            updateRecord();
            displayRecord();
        }
        break;
    case 5:
        if (fileExists("studentFile.bin") == 1)
        {
            deleteRecordbyID();
            displayRecord();
        }
        break;
    case 6:
        exitMenu = true;
    default:
        break;
    }
    return choice;
}

void createFile()
{   // create the file of 5 records
    studentRecord = fopen("studentFile.bin", "ab");
    struct Student student;

    printf("Enter Student ID: ");
    scanf("%s", student.studentID);
    while (getchar() != '\n');

    printf("Enter Student Name: ");
    scanf("%s", student.studentName);
    while (getchar() != '\n');

    printf("Enter Email ID: ");
    scanf("%s", student.emailID);
    while (getchar() != '\n');

    printf("Enter Course ID: ");
    scanf("%s", student.courseID);
    while (getchar() != '\n');

    printf("Enter Grade: ");
    scanf("%s", student.grade);
    while (getchar() != '\n');

    //write information entered into the studentRecord file
    fwrite(&student, sizeof(student), 1, studentRecord);
    fclose(studentRecord);

}

void displayRecord() {

    studentRecord = fopen("studentFile.bin", "rb");
    struct Student student;

    while (fread(&student, sizeof(student), 1, studentRecord))
    {
        printf("Student ID: %s\n", student.studentID);
        printf("Student Name: %s\n", student.studentName);
        printf("Email ID: %s\n", student.emailID);
        printf("Course ID: %s\n", student.courseID);
        printf("Grade: %s\n", student.grade);
    }

    fclose(studentRecord);
}

void seekRecord()
{
    struct Student student;
    char seekID[30];

    printf("Enter Student ID: ");
    scanf("%s", seekID);
    while (getchar() != '\n');

    studentRecord = fopen("studentFile.bin", "rb");

    //if no match, keep bool as false
    bool recordFound = false;

    while (fread(&student, sizeof(student), 1, studentRecord))
    {
        //only print if student ID matches the one on file
        if (strcmp(student.studentID, seekID) == 0)
        {
            printf("Student ID: %s\n", student.studentID);
            printf("Student Name: %s\n", student.studentName);
            printf("Email ID: %s\n", student.emailID);
            printf("Course ID: %s\n", student.courseID);
            printf("Grade: %s", student.grade);

            //turn recordFound to be true
            recordFound = true;

            break;
        }

    }

    if (!recordFound)
    {
        printf("There is no record under that Student ID");
    }
}

void updateRecord()
{   
    //temp file to obtain updated info
    FILE* studentRecord_temp;
    char id[30];
    printf("Enter Student ID: ");
    scanf("%s", id);
    while (getchar() != '\n');


    studentRecord = fopen("studentFile.bin", "rb");
    studentRecord_temp = fopen("studentRecord_temp.bin", "wb");

    struct Student student;

    while (fread(&student, sizeof(student), 1, studentRecord))
    {
        if (strcmp(student.studentID, id) == 0)
        {
            printf("Enter New Student ID: ");
            scanf("%s", student.studentID);
            while (getchar() != '\n');

            printf("Enter New Student Name: ");
            scanf("%s", student.studentName);
            while (getchar() != '\n');

            printf("Enter New Email ID: ");
            scanf("%s", student.emailID);
            while (getchar() != '\n');

            printf("Enter New Course ID: ");
            scanf("%s", student.courseID);
            while (getchar() != '\n');

            printf("Enter New Grade: ");
            scanf("%s", student.grade);
            while (getchar() != '\n');

            fwrite(&student, sizeof(student), 1, studentRecord_temp);
        }
        else {
            fwrite(&student, sizeof(student), 1, studentRecord_temp);
        }
    }

    //rewrite studentRecord to temp record info
    fclose(studentRecord);
    fclose(studentRecord_temp);
    remove("studentFile.bin");
    rename("studentRecord_temp.bin", "studentFile.bin");
}

void deleteRecordbyID()
{

    FILE* studentRecord_temp;
    char id[30];
    printf("Enter Student ID: ");
    scanf("%s", id);
    while (getchar() != '\n');


    studentRecord = fopen("studentFile.bin", "rb");
    if (!studentRecord)
    {
        printf("Unable to open file");
    }

    studentRecord_temp = fopen("studentRecord_temp.bin", "wb");
    if (!studentRecord_temp)
    {
        printf("Unable to open temp file.");
    }

    struct Student student;

    while (fread(&student, sizeof(student), 1, studentRecord))
    {
        if (strcmp(id, student.studentID) == 0)
        {
            printf("A record with requested ID has been found and deleted \n\n");
        }
        else {
            fwrite(&student, sizeof(student), 1, studentRecord_temp);
        }
    }

    fclose(studentRecord);
    fclose(studentRecord_temp);
    remove("studentFile.bin");
    rename("studentRecord_temp.bin", "studentFile.bin");
}

