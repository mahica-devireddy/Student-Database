/*Mahica Devireddy
Intro to C
Final Project*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include "leak_detector_c.h"

#define LEN 51
#define FILELEN 31
#define MAX 100

char file1[FILELEN]; 
char file2[FILELEN];
char file3[FILELEN]; 

typedef struct Student{
  
  int sID; 
  char *fname; //DMA
  char *lname; //DMA
  int day; 
  int month; 
  int year; 
  
} Student; 

typedef struct Course{ 

  char cID[LEN];
  char cname[LEN]; 
  float credit; 

} Course; 

typedef struct Enrollment{ 

  int sID;
  char cID[LEN];
  char semester[LEN]; 
  float score;

} Enrollment;

  //student file size is not known before - use memory allocation for the size
  //courses file size is not known before - use memory allocation for the size
  //enrollment file size is not known before - use memory allocation for the size
  
  
  Student* loadStudents(int *numStudents) {
  
    FILE *students = fopen(file1, "r"); 
     
    int i = 0;  
    Student *studs; 
    
    int sID; 
    char fn[LEN];
    char ln[LEN];
    int day; 
    int month; 
    int year; 
    
    fscanf(students, "%d", numStudents); //scanf num of studs
  
    studs = (Student*) malloc (*numStudents * sizeof(Student));
    //allocates memory for *numStudent of Student
    //use dot to access the structure members because it is used like an array
  
    for (i = 0; i<*numStudents; i++) {
      fscanf(students, "%d %s %s %d %d %d", &sID, fn, ln, &day, &month, &year);
  
      int fnLen = strlen(fn) + 1;
      int lnLen = strlen(ln) + 1;
  
      studs[i].fname = (char*) malloc (sizeof(char) * fnLen);
      studs[i].lname = (char*) malloc (sizeof(char) * lnLen);
      //allocate memory for first and last name cause string length is unknown
  
      studs[i].sID = sID; 
      strcpy(studs[i].fname, fn); 
      strcpy(studs[i].lname, ln);
      studs[i].day = day; 
      studs[i].month = month; 
      studs[i].year = year; 
      
    }

     fclose(students);
      return studs; 
   
  }
  
  Course* loadCourses(int *numCourses) {
  
    FILE *courses = fopen(file2, "r");
    fscanf(courses, "%d", numCourses);  
    
    Course* cList; 
  
    char cID[LEN];
    char cname[LEN]; 
    float credit; 
  
    cList = (Course*) malloc (*numCourses * sizeof(Course)); //allocate space for course array
  
    for (int i = 0; i < *numCourses; i++) {
  
      fscanf(courses, "%s %s %f", cID, cname, &credit);
  
      strcpy(cList[i].cID, cID);
      strcpy(cList[i].cname, cname); 
      cList[i].credit = credit; 
      
    }
  
    fclose(courses);
    return cList; 
    
  }
  
  Enrollment* loadEnrollment(int *numEnrollments) {
  
    FILE *enroll = fopen(file3, "r"); 
    fscanf(enroll, "%d", numEnrollments); 
    
    Enrollment* enrollList; 
  
    int sID;
    char cID[LEN];
    char semester[LEN]; 
    float score;
    
    enrollList = (Enrollment*) malloc (*numEnrollments * sizeof(Enrollment)); //allocate space for enrollment array
  
    for (int i = 0; i < *numEnrollments; i++) {
  
      fscanf(enroll, "%d %s %s %f", &sID, cID, semester, &score);
  
      enrollList[i].sID = sID; 
      strcpy(enrollList[i].cID, cID); 
      strcpy(enrollList[i].semester, semester); 
      enrollList[i].score = score; 
  
    }
  
    fclose(enroll); 
    return enrollList;
  
  }

  void student_semester(Student *ArrayOfStudents, int amountStudents, Course *ArrayOfCourses, int amountCourses, Enrollment *ArrayOfEnrollments, int amountEnrolls) {       
    char completed_list[MAX][LEN]; 
    int tracker = 0; 
    int check = 0; 
    int stud_count[amountEnrolls];
        
    for (int i = 0; i < amountEnrolls; i++) {
      stud_count[i] = 0;
    }

    for (int i = 0; i < amountEnrolls; i++) {
      for (int j = 0; j < amountEnrolls; j++) {
        if (strcmp(ArrayOfEnrollments[i].semester, completed_list[j]) == 0) {
          check = 1;
          break; 
        }
      }  
      if (check == 0) {
        strcpy(completed_list[tracker], ArrayOfEnrollments[i].semester);
        tracker++;
      }
      check = 0; 
    }
    for (int i = 0; i < amountEnrolls; i++) {
      for (int j = 0; j < tracker; j++) {
        if (strcmp(ArrayOfEnrollments[i].semester, completed_list[j]) == 0){
          stud_count[j]++;
        }
      } 
    }
    for (int i = 0; i < tracker; i++) {
      printf("%s %d\n", completed_list[i], stud_count[i]); 
    }  
  }
  
  char gradeCalculator(float grade) {
  
    if (grade >= 90) {
      return 'A';
    } else if (grade >= 80) {
      return 'B';
    } else if (grade >= 70) {
      return 'C';
    } else if (grade >= 60){ 
      return 'D';
    } 
      return 'F';
  
  }

  Course* add_course(int *numCourses, Course *courseList) {

    char courseID[LEN]; 
    char courseName[LEN]; 
    float credit; 
    int x = 0; 
  
    scanf("%s %s %f", courseID, courseName, &credit); 

    int c = 0;

    for (int i = 0; i < *numCourses; i++) {
      if (strcmp(courseList[i].cID, courseID) == 0) {
        c++;
        x = 1;
        printf("\n------------------\n");
      
        printf("\nviolation of course id uniqueness. cannot add the record.\n");
      
        printf("\n------------------\n");
      }
    }
    
    if (x != 1) {

      courseList = realloc(courseList, (*numCourses+1) * sizeof(Course));
      strcpy(courseList[*numCourses].cID, courseID); 
      strcpy(courseList[*numCourses].cname, courseName);
      courseList[*numCourses].credit = credit; 
      (*numCourses)++;

      FILE *courses = fopen(file2, "r+"); //open file again to allow writing abilities

      fprintf(courses, "%d\n", *numCourses);
      
      fseek(courses, 0, SEEK_END); //goes to the end of the file

      fprintf(courses, "\n%s %s %0.0f", courseID, courseName, credit); 

      fclose(courses);
      

      printf("\n------------------\n");
      
      printf("record added");

      printf("\n------------------\n");
    
    }
    printf("\n==================\n"); 
    return courseList; 
  }

  void free_memory(Student *ArrayOfStudents, int amountStudents, Course *ArrayOfCourses, int amountCourses, Enrollment *ArrayOfEnrollments, int amountEnrolls) {

    for (int i = 0; i < amountStudents; i++) {
  
      free(ArrayOfStudents[i].fname);
      free(ArrayOfStudents[i].lname);
      //free the arrays of names first before the overall ArrayOfStudents
      
    }
    free(ArrayOfStudents);
  
    free(ArrayOfCourses);
  
    free(ArrayOfEnrollments); 
    
  }
    
  
  void menu(Student *ArrayOfStudents, int amountStudents, Course *ArrayOfCourses, int amountCourses, Enrollment *ArrayOfEnrollments, int amountEnrolls) {

    bool activate = true; 
    while (activate){
    char type[LEN];
    
    char identification[LEN];
    
    char lname[LEN]; 
    int sID; 
    int year; 
    
    scanf("%s", type); 

    if (strcmp(type, "search_students") == 0) {
      int c = 0; 
     
      scanf("%s", identification); 
      
      if (strcmp(identification, "lname") == 0) {
        scanf("%s", lname); 
  
        for (int i = 0; i < amountStudents; i++) {
          
          if (strcmp(ArrayOfStudents[i].lname, lname) == 0) {

            printf("\n------------------\n");
          
            printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].sID, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year); 
  
            //print out list of courses, semester, score, and letter grade
            for (int j = 0; j < amountEnrolls; j++) {
  
              if (ArrayOfStudents[i].sID == ArrayOfEnrollments[j].sID) {
  
                char letter = gradeCalculator(ArrayOfEnrollments[j].score); 
  
                printf("%s ", ArrayOfEnrollments[j].cID); 
  
                for (int k = 0; k < amountCourses; k++) {
  
                  if (strcmp(ArrayOfEnrollments[j].cID, ArrayOfCourses[k].cID) == 0 ) {
  
                    printf("%s %s %0.0f %c\n", ArrayOfCourses[k].cname, ArrayOfEnrollments[j].semester, ArrayOfEnrollments[j].score, letter);
                    
                  }
        
                }
                
              }
              
            } 
            
          } 
          else {
            c++; 
          }
          
        }
        
        if (c == amountStudents) {
          printf("\n------------------\n");
          printf("not found");
        }
         printf("\n------------------\n");
        printf("\n==================\n");
      } 
      
      else if (strcmp(identification, "id") == 0) {
        scanf("%d", &sID);
        printf("\n------------------\n");

        int c = 0;
    
        for (int i = 0; i < amountStudents; i++) {
    
          if (ArrayOfStudents[i].sID == sID) {
  
    
            printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].sID, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year);
    
            for (int j = 0; j < amountEnrolls; j++) {
    
              if (ArrayOfStudents[i].sID == ArrayOfEnrollments[j].sID) {
    
                char letter = gradeCalculator(ArrayOfEnrollments[j].score); 
    
                printf("%s ", ArrayOfEnrollments[j].cID);
                  
                for (int k = 0; k < amountCourses; k++) {
    
                  if (strcmp(ArrayOfEnrollments[j].cID, ArrayOfCourses[k].cID) == 0 ) {
    
                    printf("%s %s %0.0f %c\n", ArrayOfCourses[k].cname, ArrayOfEnrollments[j].semester, ArrayOfEnrollments[j].score, letter);
                      
                  }
                    
                } 
                  
              }
                
            }
              
          } 
          else {
            c++;
          }
            
        }
        if (c == amountStudents) {
          printf("not found");
        }
        printf("\n------------------\n");
        printf("\n==================\n");
      } 
    
      else if (strcmp(identification, "byear") == 0) {
        scanf("%d", &year);
  
        int c = 0;
        printf("\n------------------\n");
        for (int i = 0; i < amountStudents; i++) {
    
          if (ArrayOfStudents[i].year == year) { 
  
    
            printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].sID, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year);
    
            for (int j = 0; j < amountEnrolls; j++) {
    
              if (ArrayOfStudents[i].sID == ArrayOfEnrollments[j].sID) {
    
                char letter = gradeCalculator(ArrayOfEnrollments[j].score); 
    
                printf("%s ", ArrayOfEnrollments[j].cID);
                  
                for (int k = 0; k < amountCourses; k++) {
    
                  if (strcmp(ArrayOfEnrollments[j].cID, ArrayOfCourses[k].cID) == 0 ) {
    
                    printf("%s %s %0.0f %c\n", ArrayOfCourses[k].cname, ArrayOfEnrollments[j].semester, ArrayOfEnrollments[j].score, letter);
 
                  }
                    
                } 
                  
              }
                
            }

            printf("\n------------------\n");
              
          } 
          else {
            c++;
          }
            
        }
        if (c == amountStudents) { 
          printf("not found");
          printf("\n------------------\n");
        }
        printf("\n==================\n");
      }
      //**********where search_students ends**********
    }
    
    else if (strcmp(type, "search_course") == 0) {
      
      char category[LEN]; 
  
      char cID[LEN];
      char semester[LEN];
      
      scanf("%s", category); 
      if (strcmp(category, "cid") == 0) {
  
        scanf("%s", cID);
  
        int c = 0; 

        for (int i = 0; i < amountCourses; i++) { 
          if (strcmp(ArrayOfCourses[i].cID, cID) == 0) {
            printf("\n------------------\n");

            printf("%s %0.0f\n", ArrayOfCourses[i].cname, ArrayOfCourses[i].credit);
  
            for (int j = 0; j < amountEnrolls; j++) {
              if (strcmp(ArrayOfCourses[i].cID, ArrayOfEnrollments[j].cID) == 0) {
  
                for (int k = 0; k < amountStudents; k++) {
                  if (ArrayOfEnrollments[j].sID == ArrayOfStudents[k].sID) {
  
                    char letter = gradeCalculator(ArrayOfEnrollments[j].score);
                    
                    printf("%s %s %s %0.0f %c\n", ArrayOfStudents[k].fname, ArrayOfStudents[k].lname, ArrayOfEnrollments[j].semester, ArrayOfEnrollments[j].score, letter);
                    
                  }
                  
                }
                
              }
              
            }
          
          }
          else {
            c++;
          }
        }
        if (c == amountCourses) {
          printf("\n------------------\n");
          printf("not found");
        }
        printf("\n------------------\n");
        printf("\n==================\n");
      }
      
  // intro_to_C 3
  // edward travis fall22 80 B
  // coral akagbosu fall22 70 C
      else if (strcmp(category, "cid_semester") == 0) {
  
        scanf("%s %s", cID, semester);

        printf("\n------------------\n");

        //if the course id exists then 
        int i; 
        int j; 
        int c = 0; 
        
        for(i = 0; i < amountCourses; i++) {
          if (strcmp(ArrayOfCourses[i].cID, cID) == 0 ) {
            break; 
          } 
          else {
            c++;
          }
        }
        if (c == amountCourses) {
          printf("not found");
          printf("\n------------------\n");
          printf("\n==================\n");
        } 
        else {
          
        printf("%s %0.0f\n", ArrayOfCourses[i].cname, ArrayOfCourses[i].credit); 
        for (j = 0; j < amountEnrolls; j++) {
          if (strcmp(ArrayOfCourses[i].cID, ArrayOfEnrollments[j].cID) == 0 && strcmp(ArrayOfEnrollments[j].semester, semester) == 0) {
           
            for (int k = 0; k < amountStudents; k++) {
              if (ArrayOfEnrollments[j].sID == ArrayOfStudents[k].sID) {
                  
                char grade = gradeCalculator(ArrayOfEnrollments[j].score);
                printf("%s %s %s %0.0f %c\n", ArrayOfStudents[k].fname, ArrayOfStudents[k].lname, ArrayOfEnrollments[j].semester, ArrayOfEnrollments[j].score, grade);
              }
            }
          }
        }
        printf("\n------------------\n");
        printf("\n==================\n");
      }
    }
  }
  //**********where search_courses ends**********
  else if (strcmp(type, "add_course") == 0) {

    ArrayOfCourses = add_course(&amountCourses, ArrayOfCourses);
    
  }

  else if (strcmp(type, "count") == 0) {
    char option[LEN];

    scanf("%s", option); 

    if (strcmp(option, "students") == 0) { 

      printf("\n------------------\n");
      printf("\ntotal students %d\n", amountStudents); 
      printf("\n------------------\n");
      printf("\n==================\n"); 
      
    }
    else if (strcmp(option, "students_course") == 0) {
      
      printf("\n------------------\n");

      for (int i = 0; i < amountCourses; i++) {
        int c = 0; 
        
        for (int j = 0; j < amountEnrolls; j++) {

          if (strcmp(ArrayOfCourses[i].cID, ArrayOfEnrollments[j].cID) == 0) {
            c++; 
          }
          
        }
        
        printf("%s %d\n", ArrayOfCourses[i].cID, c);
        
      }    
      printf("\n------------------\n");
      printf("\n==================\n"); 
    }
      
    else if (strcmp(option, "students_semester") == 0) {
      printf("\n------------------\n");
      student_semester(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls); 
      printf("\n------------------\n");
      printf("\n==================\n");
    }
  }
  else if (strcmp(type, "sort") == 0) {
    printf("\n------------------\n");
    Student temp;
    for (int i = 0; i < amountStudents-1; i++) {
      for (int j = 0; j < amountStudents-i-1; j++) {
          
        if (ArrayOfStudents[j].sID > ArrayOfStudents[j+1].sID) {
             
          temp = ArrayOfStudents[j];
          ArrayOfStudents[j] = ArrayOfStudents[j+1];
          ArrayOfStudents[j+1] = temp;
             
        }
      }
    }
    for (int i = 0; i < amountStudents; i++) {
      printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].sID, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year);
    }
    printf("\n------------------\n");
    printf("\n==================\n");
  }
    
  else if (strcmp(type, "exit") == 0) {
      free_memory(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls);
      
      activate = false; 
       
  }
}

}
    
  

    


int main(void) {

  atexit(report_mem_leak); //add this line to your code
  
    Student *studsList; 
    Enrollment *enrollList; 
    Course *courList; 
    
    int numStudents;
    int numEnrollments;
    int numCourses; 
  
    scanf("%s %s %s", file1, file2, file3);
  
    FILE *students = fopen(file1, "r");
    fscanf(students, "%d", &numStudents);

    FILE *courses = fopen(file2, "r");
    fscanf(courses, "%d", &numCourses);
    
    FILE *enrollment = fopen(file3, "r");
    fscanf(enrollment, "%d", &numEnrollments);
  
    studsList = loadStudents(&numStudents);
    courList = loadCourses(&numCourses); 
    enrollList = loadEnrollment(&numEnrollments); 
  
    printf("\n==================\n");

    
  
      menu(studsList, numStudents, courList, numCourses, enrollList, numEnrollments); 

      printf("\n------------------\n");
      printf("Bye!");
     

      
    return 0;
  }