#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *fgets(char *s, int size, FILE *stream);
long long int convert(char *p);
int getEntry(u_int64_t x);
int getTag(u_int64_t x);
int main(int argc, char *argv[])
{
  int cache[512];
  int hit=0;
  int miss=0;
  char string[20];

  while(fgets(string, 100, stdin)) {
    u_int64_t temp=convert(string);

    int entry=getEntry(temp);
    int tag=getTag(temp);

    if(cache[entry]==tag){
      hit++;
    }
    else {
      miss++;
      cache[entry]=tag;
    }
  }
  printf("the number of hit is %d\n", hit);
  printf("the number of miss is %d\n", miss);
}
//return the tag of a memory address
int getTag(u_int64_t x){
  x=x >>15; //15 because entry and offset takes 9+6=15 bits
  u_int64_t mask = 0xffffff;
  int tag = x & mask;
  return tag;
}
//return the entry of a memeory address
int getEntry(u_int64_t x){
  x= x >> 6;
  u_int64_t mask = 0x1ff;
  int entry = x & mask;
  return entry;
}
//convert the memory address which is string to integer
long long int convert (char *p){
  u_int64_t temp=0;
  int i=0;
  //while the string has not ended
  while (*(p+i+1)!=0){
    //if the character is numerical number
    if (*(p+i)<58){
      temp = *(p+i)%48+temp*16;
    }
    //if the character is "a,b,c,d,e,f"
    else if (*(p+i)>=97){
      temp = *(p+i)%97+10+temp*16;
    }
    i++;
  }
  return temp;
}
