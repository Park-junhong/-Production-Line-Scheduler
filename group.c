#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

struct Schedule{
    char orderNum[10];
    char dueDate[11];
    int quantity;
    char productName[100];
};

int startDate[3], endDate[3], numOrders = 0;
struct Schedule schedule[100];
const int SIZE = 80;

long totalday(int year,int month,int day);
void runcmd(char command[],int count);
void addPEIOD(char arr[]);
void addDate(char input[3][SIZE], int x, int start, int end, bool stDate);
void addORDER(char arr[]);
void addBATCH(char arr[], int count);
void runPLS(char arr[],int count);

int main(int argc,char *argv[]){
  char command[100];
  printf("~~WELCOME TO PLS~~\n\n");
  printf("Please enter:\n");
  while(1){
      fgets(command, 100, stdin);
      if(strncmp(command, "exit", 4) == 0){
          printf("Bye-bye!\n");
            break;
      }
      if(strncmp(command, "-1", 2) != 0){
          runcmd(command,sizeof(command)/sizeof(int));
          strcpy(command, "-1");
          printf("Please enter:\n");
      }
  }
  return 0;
}

long totalday(int year, int month, int day)
{
  int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int i = 0;
  long total = 0L;
  total = (year - 1) * 365L + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
  if (!(year % 4) && year % 100 || !(year % 400))
          months[i]++;
  for (i = 0; i < month - 1; i++)
    total += months[i];
  total += day;
  return total;
}

void runcmd(char command[],int count){
  char *ptr = strstr(command,"addPEIOD");
  if(ptr != NULL){
    addPEIOD(command);
  }
  else{
    ptr=strstr(command,"addORDER");
    if(ptr != NULL){
      addORDER(command); //count
    }
    else{
      ptr=strstr(command,"addBATCH");
      if(ptr != NULL){
        addBATCH(command, count);
      }
      else{
        ptr=strstr(command,"runPLS");
        if(ptr != NULL){
          runPLS(ptr,count);
          //printf("runPLS");
        }
        else{
          //exitPLS();
          printf("exit");
        }
      }
    }
  }
}

void addDate(char input[3][SIZE], int x, int start, int end, bool stDate){
    int i, j = 1;
    char temp[5];
    if(stDate == false)
        j=2;
    for (i = start; i < end; i++) {
        temp[i-start] = input[j][i];
    }
    temp[i-start] = '\0';
    if(stDate == true)
        startDate[x] = atoi(temp);
    else
        endDate[x] = atoi(temp);
}

void addPEIOD(char arr[]){
    int i=0;
    char input[3][SIZE];
    char * token = strtok(arr, " ");
    while(token != NULL){
        strcpy(input[i++], token);
        token = strtok(NULL, " ");
    }
    // Add Start Date
    addDate(input, 0, 0, 4, true);
    addDate(input, 1, 5, 7, true);
    addDate(input, 2, 8, 10, true);
    //Add End Date
    addDate(input, 0, 0, 4, false);
    addDate(input, 1, 5, 7, false);
    addDate(input, 2, 8, 10, false);
    //printf("total days: %d\n",totalday(endDate[0],endDate[1],endDate[2])-totalday(startDate[0],startDate[1],startDate[2]));
}

void addORDER(char arr[]){
    strtok(arr, " ");
    char * token = strtok(NULL, " ");

    strcpy(schedule[numOrders].orderNum, token);

    token = strtok(NULL, " ");
    strcpy(schedule[numOrders].dueDate, token);

    token = strtok(NULL, " ");
    schedule[numOrders].quantity = atoi(token);

    token = strtok(NULL, " ");
    strcpy(schedule[numOrders].productName, token);

    //printf("%s %s %d %s\n", schedule[numOrders].orderNum, schedule[numOrders].dueDate, schedule[numOrders].quantity, schedule[numOrders].productName);
    numOrders++;
}

void addBATCH(char arr[], int count){
    int i;
    char a[100], buf[150], line[100] = "";
    FILE *fp;
    for (i = 9; i < count; i++) {
        a[i-9] = arr[i];
    }
    a[i] = '\0';

    strtok(arr, " ");
    char * token = strtok(NULL, " ");

    strcat(line, a);
    char* filename = line;
    fp = fopen(filename ,"r");
    while(fgets(buf, 150, (FILE*)fp) != NULL){
        addORDER(buf);
    }
    fclose(fp);
}

void runPLS(char arr[],int count){
    int i=0,sum=0,plant[3]={500,400,300}; //Z,Y,X
    int peiod=totalday(endDate[0],endDate[1],endDate[2])-totalday(startDate[0],startDate[1],startDate[2]); // number of days
    double timeCons[numOrders];
    char plant_name[3][20]={"Plant_Z","Plant_Y","Plant_X"};
    char input[5][SIZE]; // 1:algorithm type, 2:| , 3:printREPORT , 4: >, 5: file name
    char * token = strtok(arr, " ");
    while(token != NULL){
        strcpy(input[i++], token);
        token = strtok(NULL, " ");
    }
    if(strcmp(input[1],"FCFS")){
        for(int i=0;i<numOrders;i++){
            timeCons[i]=(schedule[i].quantity/(double)plant[i%3]);
            if(timeCons[i]-(int)timeCons[i]!=0)
                timeCons[i]=(int)timeCons[i] +1;
            printf("%d: %s is used for %0.1f days\n",i,plant_name[i%3],timeCons[i]);
        }
            
        
    }
    else if(strcmp(input[1],"other")){
        for(int i=0;i<numOrders;i++){//I use plant_Z for this which can produce 500 product a day
            timeCons[i]=((double)schedule[i].quantity)/500;
            if(timeCons[i]-(int)timeCons[i]!=0)
                timeCons[i]=(int)timeCons[i] +1;
            sum+=timeCons[i];
        }
        if(sum<peiod)// if the period is enough to handle all work, just use plant_Z
        {
            for(int i=0;i<numOrders;i++)
                printf("Plant_X is used for %0.1f days\n",timeCons[i]);
        }
        else{ //use plant_Z and Y
            int quantity_Z=schedule[i].quantity ,quantity_Y=400;
            int temp_Z,temp_Y;
            sum=0;
            while(1){
                for(int i=0;i<numOrders;i++){
                    temp_Z=((double)quantity_Z)/500;
                    temp_Y=((double)quantity_Y)/400;
                    timeCons[i]=((double)quantity_Z)/500+((double)quantity_Y)/400;
                    if(temp_Z-(int)temp_Z!=0)
                        temp_Z=(int)temp_Z +1;
                    if(temp_Y-(int)temp_Y!=0)
                        temp_Y=(int)temp_Y +1;
                    timeCons[i]=temp_Z+temp_Y;
                    sum+=timeCons[i];
                }
                if(sum<peiod){
                    for(int i=0;i<numOrders;i++)
                        printf("Plant_X is used for %0.1f days\n",timeCons[i]);
                }
                else{//use XYZ
                    
                }
            }
        }
    }
    
}
