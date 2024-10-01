#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 256
#define MAX_LINE 256


int studentCount = 0;

void menu();
void studentAdd();
void studentRemove();
void studentUpdate();
void listStudent();
int Exit();


int main(){
    int preference;
    

system("clear");
    printf("Menu \n");

    //selecting the process
    printf("1- Add Student\n");
    printf("2- Remove Student\n");
    printf("3- Update Student\n");
    printf("4- List Student\n");
    printf("5- Exit\n");
    scanf("%d",&preference);
    
    //navigate to the selected process
    switch (preference)
    {
    case 1:
        studentAdd();
        break;
    case 2:
        studentRemove();
        break;
    case 3:
        studentUpdate();
        break;
    case 4:
        listStudent();
        break;
    case 5:
        Exit();
        break;
    default:
        break;
    }




    return 0;
}
void menu(){
    //menu process
    int preference;
    printf("..................................\n");
    printf("\nMenu \n");
    printf("1- Add Student\n");
    printf("2- Remove Student\n");
    printf("3- Update Student\n");
    printf("4- List Student\n");
    printf("5- Exit\n");

    printf("Enter the preference: \n");
    scanf("%d",&preference);
    if(preference==1) studentAdd();
    else if(preference==2) studentRemove();
    else if(preference==3) studentUpdate();
    else if(preference==4) listStudent();
    else if(preference==5) Exit();
    else{
        printf("Invalid preference !\n");
        menu();
    }

}

//file process
void studentAdd(){
    system("clear");
    studentCount++;
    char fileName[150];
    printf("Enter the file name: \n");
    scanf("%s",fileName);
    int studentNo;
    char studentName[150];
    double gp;
    if(studentCount<MAX){
        printf("Enter the student no: \n");
        scanf("%d",&studentNo);
        fflush(stdin);
        printf("Enter the student name: \n");
        scanf("%s",studentName);
        fflush(stdin);
        printf("Enter the gp: \n");
        scanf("%lf",&gp);
        fflush(stdin);
    }
    else{
        printf("Limitations exceeded !\n");
        return;
    }
    FILE *file;
    file =fopen(fileName,"a");
    
    if(file==NULL){
        printf("File couldnt open !\n");
        return;
    }
    else if(file!=NULL){
        fprintf(file,"%d %s %lf\n",studentNo,studentName,gp);
    }

    fclose(file);
    menu();

}

//temp file and file process
void studentRemove(){
    system("clear");
    char fileName[150];
    char tempFileName[150];

//it will copy ordinary file to temp file except the line that will be deleted

    FILE *file,*tempFile;
    char buffer[MAX_LINE];
    int deleteLine=0;
    
    //making temperory file name
    printf("Enter the file name: \n");
    scanf("%s",fileName);
    strcpy(tempFileName,fileName);


    printf("Enter the line number to delete: \n");
    scanf("%d",&deleteLine);

    file= fopen(fileName,"r");
    tempFile = fopen(tempFileName,"w");

    if(file==NULL || tempFile==NULL){
        printf("File couldnt open !\n");
        return ;
    }
    bool keep=true;
    int currentLine=1;

    do{
        fgets(buffer,MAX_LINE,file);
        if(feof(file)) keep=false;
        else if(currentLine!=deleteLine){
            fputs(buffer,tempFile);
            currentLine++;
        }

    }while (keep);

    fclose(tempFile);
    fclose(file);

    remove(fileName);
    rename(tempFileName,fileName);
    menu();


}

void studentUpdate(){
    system("clear");
    char fileName[150];
    char tempFileName[150];

    int studentNo,updateStudentNo;
    char studentName[150],updateStudentName[150];
    double gp,updateGp;
    printf("Enter the file name: \n");
    scanf("%s",fileName);
    strcpy(tempFileName,"temp_");
    strcat(tempFileName,fileName);

    FILE *file,*file2;
    file =fopen(fileName,"r");
    file2 = fopen(tempFileName,"w");

    printf("Enter the student no you want to update: \n");
    scanf("%d",&updateStudentNo);
    fflush(stdin);
    
    int preference;
    while(fscanf(file,"%d %s %lf\n",&studentNo,studentName,&gp)!=EOF){
        if(studentNo==updateStudentNo){
            printf("\nWhat do you want to update ?\n");
            printf("\n1-Name\n");
            printf("2-GP\n");
            printf("3-No\n");
            scanf("%d",&preference);
            fflush(stdin);

            if(preference==1){
                printf("Enter the new name: \n");
                scanf("%s",updateStudentName);
                fflush(stdin);
                fprintf(file2,"%d %s %lf\n",studentNo,updateStudentName,gp);
            }
            else if(preference==2){
                printf("Enter the new gp: \n");
                scanf("%lf",&updateGp);
                fflush(stdin);
                fprintf(file2,"%d %s %lf\n",studentNo,studentName,updateGp);
            }
            else if(preference==3){
                printf("Enter the new no: \n");
                scanf("%d",&updateStudentNo);
                fflush(stdin);
                fprintf(file2,"%d %s %lf\n",updateStudentNo,studentName,gp);
            }
            else{
                return;
            }
            
        }
        else if(studentNo!=updateStudentNo){
            fprintf(file2,"%d %s %lf\n",studentNo,studentName,gp);
        }

    }
    fclose(file);
    fclose(file2);
    remove(fileName);
    rename(tempFileName,fileName);
    
    menu();
    
}
void listStudent(){
    system("clear");
    char fileName[150];
    int studentNo;
    char studentName[150];
    double gp;
    printf("Enter the file name: \n");
    scanf("%s",fileName);

    FILE *file;
    file =fopen(fileName,"r");

    printf("\nStudent No \t Student Name \t GP \n");
    while(fscanf(file,"%d %s %lf\n",&studentNo,studentName,&gp)!=EOF){
        printf("%d %s %lf\n",studentNo,studentName,gp);

    }
    fclose(file);
    menu();

}

int Exit(){
    return 0;
}