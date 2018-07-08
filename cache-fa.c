#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
char *fgets(char *s, int size, FILE *stream);
long long int convert(char *p);
int getTag(u_int64_t x);
bool isHit(int tag);
void rearrage(int *p);
void replace(int *p, int tag);
int count =0; //keep track of how many items we have put in the cache
int indx; //keep trach of which item in the cache got hit
int cache[512];
int main(int argc, char *argv[])
{
  int hit=0;
  int miss=0;
  char string[20];

  while(fgets(string, 100, stdin)) {
    u_int64_t temp=convert(string);
    int tag=getTag(temp);

    if(isHit(tag)==true){
      hit++;
      rearrage(cache);
    }
    else{
      miss++;
      if(count<512){  //if the cache is not full yet
        cache[count]=tag;
        count++;
      }
      else { //else if the cache is full
        replace(cache, tag); //implement LRU policy
      }
    }
  }
  printf("the number of hit is %d\n", hit);
  printf("the number of miss is %d\n", miss);
}
//return true if it is hit and if so, set indx to the place we found it
bool isHit(int tag){
  for (int i=0; i<count;i++){
    if(cache[i]==tag){
      indx=i;
      return true;
    }
  }
  return false;
}
//rearrage the element in the cache so we can implement LRU policy
//the lower the index, the least recently used the item is
void rearrage(int *p){
  int temp=cache[indx];
  int j=indx+1;

  //move everything from index (indx+1) to index count -2 up by 1
  while(j<count){
    cache[j-1]=cache[j];
    j++;
  }
  //put the item that just got accessed at the most bottom index
  cache[count-1]=temp;
}
//replace the least recently used item with the new item
void replace(int *p, int tag){
  int temp=tag;
  int j=1;
  while(j<count){
    cache[j-1]=cache[j];
    j++;
  }
  cache[511]=temp;
}
//return the tag of a memory address for a fa cache
int getTag(u_int64_t x){
  x=x >>6;
  u_int64_t mask = 0xffffffff;
  int tag = x & mask;
  return tag;
}
//convert the memory address which is string to integer
long long int convert (char *p){
  u_int64_t temp=0;
  int i=0;
  //while the string has not ended
  while (*(p+i+1)!=0){
    if (*(p+i)<58){ //if the character is numerical number
      temp = *(p+i)%48+temp*16;
    }
    else if (*(p+i)>=97){ //if the character is "a,b,c,d,e,f"
      temp = *(p+i)%97+10+temp*16;
    }
    i++;
  }
  return temp;
}
