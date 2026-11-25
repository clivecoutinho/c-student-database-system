                                                                             //STUDENT DATA BASE
#include<stdio.h>          //HEADER FILES
#include<stdlib.h>
#include<conio.h>
struct Student                      // struct = collection of related members ("variables")                          
{ char Firstname[14];
  char Lastname[14];
  int class;
  int roll_no;
  char phone_number[12];
  char grade;
};
int AddStudent()                   //ADDING FUNCTION
{ FILE *pF=fopen("Student_database.dat","ab");
  if(pF==NULL)
  {
    printf("Could not open file! \n ");
    return 1;
  }
  struct Student student; 
  printf("\n\t\t\t\t\t              First name: ");
  scanf("%13s",student.Firstname);
  printf("\t\t\t\t\t              Last name : ");
  scanf("%13s",student.Lastname);
  printf("\t\t\t\t\t              Class     : ");
  scanf("%d",&student.class);
  printf("\t\t\t\t\t              Roll no   : ");
  scanf("%d",&student.roll_no);
  printf("\t\t\t\t\t              Phone number: ");
  scanf("%11s",student.phone_number);
  printf("\t\t\t\t\t              Grade     : ");
  scanf(" %c",&student.grade);
  printf("\033[2J\033[H");

  fwrite(&student, sizeof(struct Student), 1, pF);
  printf("\t\t*****************************************Student Added***********************************************\n\n");
  printf("\t\t                             Press Any Key to Exit This Operation!"); 
  fclose(pF);
  pF=NULL;
  _getch();
  printf("\033[2J\033[H");
  return 0;
}
int ReadStudent()                 //READING FUNCTION
{ struct Student student;
  int n;
  printf("\n\t\t\t\t\t              Enter student Record No: ");
  scanf("%d",&n);
  if(n<1)
  {
   printf("\033[2J\033[H");
   printf("\n\n\n\t\t**************************************Invalid Record***********************************************\n\n");
   printf("\t\t Press Any Key to Exit This Operation!");
  _getch();
   printf("\033[2J\033[H");
   return 1;
  }
  FILE *pF=fopen("Student_database.dat","rb");
  if(pF==NULL)
  {  printf("Could not open file! \n ");
    return 1;
  }
  printf("\033[2J\033[H");
  fseek(pF,(n-1)* sizeof(struct Student),SEEK_SET);
  if((fread(&student,sizeof(struct Student),1,pF)==1))
  {     printf("\t\t\t\t\t                    |RECORD NO %d|\n\n",n);
        printf("\t\t\t\t\t              Name: %s %s\n", student.Firstname, student.Lastname);
        printf("\t\t\t\t\t              Class: %d  Roll: %d\n", student.class, student.roll_no);
        printf("\t\t\t\t\t              Phone: %s  Grade: %c\n", student.phone_number, student.grade);
        printf("\n\n\n\t\t*****************************************Student Read Successfully***********************************************\n\n");
        printf("\t\t                                   Press Any Key to Exit This Operation!"); 
  }
  else{
    printf("Record not found! \n");
  }
  fclose(pF);
  pF=NULL;
  _getch();
  printf("\033[2J\033[H");
  return 0;
}
int DeleteStudent()              //DELETING FUNCTION
{ struct Student student;
  int record,found=0;
  FILE *pF=fopen("Student_database.dat","rb");
  if(pF==NULL)
  {
    printf("Couldnt Open file! \n");
    return 1;
  }
  FILE *pTemp=fopen("Temp.dat","wb");
  if(pTemp==NULL)
  { printf("Couldnt Open Temp file! \n");
    fclose(pF);
    return 1;
  }
  printf("\t\t\t\t\t              Enter Record to delete: ");
  scanf("%d",&record);
  if(record<1)
  {
   printf("\n\n\n\t\t**************************************Invalid Record***********************************************\n\n");
   printf("\t\t Press Any Key to Exit This Operation!");
   fclose(pF);
   fclose(pTemp);
   remove("Temp.dat");
   _getch();
   printf("\033[2J\033[H");
   return 1;
   }
  long skipPos=(long)(record-1)*sizeof(struct Student);   
  while(1)
  {
    long pos=ftell(pF);                                   
    if(fread(&student,sizeof(struct Student),1,pF)!=1)
      break;                                              

    if(pos==skipPos)
    {
      found=1;                                           
    }
    else{
      fwrite(&student,sizeof(struct Student),1,pTemp);
    }
  }
  
  fclose(pF);
  fclose(pTemp);
  if(found)
  {  remove("Student_database.dat");
     rename("Temp.dat","Student_database.dat");
     if(remove("Student_database.dat")==0&&rename("Temp.dat","Student_database.dat")==0)
     { printf("\n\n\n\t\t**********************************Student Deleted Successfully***********************************************\n\n");
     printf("\t\t                             Press Any Key to Exit This Operation!"); 
     }  
    else{
      printf("\n\n\n\t\t**************************************Delete Failed***********************************************\n\n");
      printf("\t\t Press Any Key to Exit This Operation!");
    }
  } 
  else{
     printf("\n\n\n\t\t****************************************Student Not Found***********************************************\n\n");
     printf("\t\t                             Press Any Key to Exit This Operation!"); 
     remove("Temp.dat");
  }
  _getch();
  printf("\033[2J\033[H");
  return 0;
}
int EditStudent()               //EDIT FUNCTION
{ struct Student student;
  int record;
  printf("\n\t\t\t\t\t                 Enter Record: ");
  scanf("%d",&record);
  if(record<1)
  {
    printf("Invalid record!\n");
    return 1;
  }
  FILE *pF=fopen("Student_database.dat","rb+");
  if(pF==NULL)
  {
    printf("Could not Edit! \n");
    return 1;
  }
  int choice=0;
      

       printf("\033[2J\033[H");
       printf("\t\t*************************************EDITING***************************************\n\n");
       printf("\t\t\t\t            1.Edit First Name.\n ");
       printf("\t\t\t\t            2.Edit Last Name.\n ");
       printf("\t\t\t\t            3.Edit Class.\n ");
       printf("\t\t\t\t            4.Edit Roll no.\n ");
       printf("\t\t\t\t            5.Edit Phone Number.\n ");
       printf("\t\t\t\t            6.Edit Grade. \n");
       printf("\t\t\t\t            7.Exit. \n\n");
       printf("\t\t\t\t            Choose operation: ");
       scanf(" %d",&choice);
       printf("\033[2J\033[H");
       fseek(pF,(record-1)*sizeof(struct Student),SEEK_SET);
       if(fread(&student,sizeof(struct Student),1,pF)!=1)
       {
        printf("Record not found!\n");
        fclose(pF);
         return 1;
        }
       fseek(pF,(record-1)*sizeof(struct Student),SEEK_SET);
       switch(choice)
       {    case 1:printf("\t\t\t\t         Existing First name: %s",student.Firstname);
                   printf("\n\t\t\t\t         New First name     : ");
                   scanf(" %13s",student.Firstname);
                   fwrite(&student,sizeof(struct Student),1,pF);
                   break;
            case 2:printf("\t\t\t\t         Existing Last name: %s",student.Lastname);
                   printf("\n\t\t\t\t         New Last name     : ");
                   scanf(" %13s",student.Lastname);
                   fwrite(&student,sizeof(struct Student),1,pF);
                   break;
                
            case 3:printf("\t\t\t\t         Existing Class: %d",student.class);
                   printf("\n\t\t\t\t         New Class name     : ");
                   scanf(" %d",&student.class);
                   fwrite(&student,sizeof(struct Student),1,pF);
                   break;
                
            case 4: printf("\t\t\t\t         Existing Roll No: %d",student.roll_no);
                   printf("\n\t\t\t\t          New Roll No     : ");
                   scanf(" %d",&student.roll_no);
                   fwrite(&student,sizeof(struct Student),1,pF);
                   break;
                
            case 5:printf("\t\t\t\t         Existing Phone No: %s",student.phone_number);
                   printf("\n\t\t\t\t         New Phone No     : ");
                   scanf(" %11s",student.phone_number);
                   fwrite(&student,sizeof(struct Student),1,pF);
                   break;
                
            case 6:printf("\t\t\t\t         Existing Grade: %c",student.grade);
                   printf("\n\t\t\t\t         New Grade     : ");
                   scanf(" %c",&student.grade);
                   fwrite(&student,sizeof(struct Student),1,pF);
                   break;
            case 7: printf("\n\n\n\t\t**************************************Exiting***********************************************\n\n");
                    printf("\t\t                              Press Any Key to Exit This Operation!");
                    fclose(pF);
                    pF=NULL;
                    _getch();
                    printf("\033[2J\033[H");
                    return 1;  
            default:printf("\033[2J\033[H");
                    printf("\n\n\n\t\t**************************************Invalid Operation***********************************************\n\n");
                    printf("\t\t Press Any Key to Exit This Operation!");
                    fclose(pF);
                    pF=NULL;
                    _getch();
                    printf("\033[2J\033[H");
                    return 1;
                           
        
      } 
    printf("\033[2J\033[H");
    printf("\n\n\n\t\t**************************************Edited Successfully***********************************************\n\n");
    printf("\t\t                              Press Any Key to Exit This Operation!"); 
    fclose(pF);
    pF=NULL;
    _getch();
    printf("\033[2J\033[H");
    return 0;
}
int list()                     //LISTING FUNCTION
{struct Student student;
  int n=1;
  FILE *pF=fopen("Student_database.dat","rb");
  if(pF==NULL)
  {  printf("Could not open file! \n ");
    return 1;
  }
        printf("\t\t ********************************************STUDENT DATABASE*********************************************");
  fseek(pF,0,SEEK_SET);
  while((fread(&student,sizeof(struct Student),1,pF)==1))
  {     printf("\n\n\t\t\t\t\t                    |RECORD NO %d|\n\n",n);
        printf("\t\t\t\t\t              Name: %s %s\n", student.Firstname, student.Lastname);
        printf("\t\t\t\t\t              Class: %d  Roll: %d\n", student.class, student.roll_no);
        printf("\t\t\t\t\t              Phone: %s  Grade: %c\n", student.phone_number, student.grade);
        printf("\n\n");
        n+=1;
  }
  printf("\n\n\n\t\t**************************************List Read Successfully***********************************************\n\n");
  printf("\t\t                              Press Any Key to Exit This Operation!"); 
  fclose(pF);
  pF=NULL;
  _getch();
  printf("\033[2J\033[H");
  return 0;

}
int main() {                  //MAIN
    FILE *pF=fopen("Student_database.dat","ab");
    if(pF==NULL)
    {
      printf("Could not create DAT file\n");
      return 1;
    }
    fclose(pF);
    int choice=0;
    while(choice!=6)
    {  

       printf("\033[2J\033[H");
       printf("\t\t*************************************STUDENT DATABASE***************************************\n\n");
       printf("\t\t\t\t            1.Add a student to the record.\n ");
       printf("\t\t\t\t            2.Search a student in the record.\n ");
       printf("\t\t\t\t            3.List all students in the record.\n ");
       printf("\t\t\t\t            4.Edit student in the record.\n ");
       printf("\t\t\t\t            5.Delete a student from the record.\n ");
       printf("\t\t\t\t            6.Exit. \n\n");
       printf("\t\t\t\t            Choose operation: ");
       scanf(" %d",&choice);
         if(choice<=0 || choice>6 )
         {
            printf("Please enter valid operation, press any key to try again!\n ");
            _getch();
         }
       printf("\033[2J\033[H");
       switch(choice)
       {    case 1:AddStudent();
                   break;
            case 2: ReadStudent();
                break;
            case 3:list();
                break;
            case 4:EditStudent();
                break;
            case 5:DeleteStudent();
                break;
            default: continue;
                           
        }
    } 
    printf("\033[2J\033[H");
    printf("\t\t\t**********************Thank You For Using this Application!!**********************\n");
    printf("\t\t\t                             Press Any Key to Exit!");
    _getch();
    printf("\033[2J\033[H");
    
    return 0;
} 