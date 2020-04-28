#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long totalday(int year,int month,int day);
void runcmd(char command[],int count);
int main(int argc,char *argv[]){

  char command[100];
  printf("~~WELCOME TO PLS~~");
  while(1){
    printf("Please enter:\n");
    scanf("%s",command);
    runcmd(command,sizeof(command)/sizeof(int));

  }
return 0;
}

long totalday(int year, int month, int day)
{
  int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int i;
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
    //addPEIOD(ptr,count);
    printf("addPEIOD");
  }
  else{

    ptr=strstr(command,"addORDER");
    if(ptr != NULL){
      //addORDER(ptr,count);
      printf("addORDER");
    }
    else{
      ptr=strstr(command,"addBATCH");
      if(ptr != NULL){
        //addBATCH(ptr,count);
        printf("addBATCH");
      }
      else{
        ptr=strstr(command,"runPLS");
        if(ptr != NULL){
          //runPLS(ptr,count);
          printf("runPLS");
        }
        else{
          //exitPLS();
          printf("exit");
        }
      }
    }
  }
}
