#include <stdio.h>
#include <stdlib.h>
 

int main() {
  
    int n,u;
    n = rand () % 101;
    

   while(n != u) {scanf("%d", &u);
       if (u < n) {
        printf("Zahl zu klein\n");
        }
        else if (u > n) 
        {printf("Zahl zu gross\n");     
            } else {
                 printf("Zahl %d ist richtig!\n",n);

            }
   }
        
    

    return 0;                 
}
