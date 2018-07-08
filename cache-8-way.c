#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
char *fgets(char *s, int size, FILE *stream);
long long int convert(char *p);
int getEntry(u_int64_t x);
int getTag(u_int64_t x);
bool isHit(int y, int x);
void rearrage(int entry);
void replace(int entry, int tag);
int count[64];
int ind[64];
int cache[64][8];
int main(int argc, char *argv[])
{
  int hit=0;
  int miss=0;
  char string[20];

  while(fgets(string, 100, stdin)) {
    u_int64_t temp=convert(string);

    int entry=getEntry(temp);
    int tag=getTag(temp);

    if(isHit(entry,tag)){
      hit++;
      rearrage(entry);
    }
    else {
      miss++;
      int t = count[entry];
      if(t<8){ //if the cache[entry] is not full yet 
        cache[entry][t]=tag;
        count[entry]++;
      }
      else{ //else if the cache[entry] is full 
        replace(entry, tag); //implement LRU policy 
      }
    }
  }
  printf("the number of hit is %d\n", hit);
  printf("the number of miss is %d\n", miss);
}
//return true if it is hit and if so, set ind[entry] to the place we found it
bool isHit(int entry, int tag){
  for (int i=0; i<count[entry];i++){
    if(cache[entry][i]==tag){
      ind[entry]=i;
      return true;
    }
  }
  return false;
}
//rearrage the element in the cache so we can implement LRU policy
//the lower the index, the least recently used the item is
void rearrage(int entry){
  int temp=cache[entry][ind[entry]];
  int j=ind[entry]+1;
  //move everything from index (indx+1) to index count -2 up by 1
  while(j<count[entry]){
    cache[entry][j-1]=cache[entry][j];
    j++;
  }
  //put the item that just got accessed at the most bottom index
  cache[entry][count[entry]-1]=temp;
}
//replace the least recently used item with the new item 
void replace(int entry, int tag){
  int temp = tag;
  int j=1;
  while(j<count[entry]){
    cache[entry][j-1]=cache[entry][j];
    j++;
  }
  cache[entry][7]=temp;
}
//return the tag of a memory address
int getTag(u_int64_t x){
  x=x >>12; 
  u_int64_t mask = 0xffffff;
  int tag = x & mask;
  return tag;
}
//return the entry of a memeory address
int getEntry(u_int64_t x){
  x= x >> 6;
  u_int64_t mask = 0x3f;
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
