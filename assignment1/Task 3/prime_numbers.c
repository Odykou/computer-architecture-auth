#include<stdio.h>

int main() {
int i,j;
printf("The first ten prime numbers are:-\n");
for(i=2;i<=30;i++) {
 int c=0;
 for(j=1;j<=i;j++) {
  if(i%j==0) {
   c++;
  }
 }     
 if(c==2) {
  printf("%d ",i);
 }
}
return 0;
}
