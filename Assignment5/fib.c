#include <stdio.h>
#include <stdlib.h>

int main(){

int fn_1 = 1;
int fn_2 = 1;
int fn = 1;
int n;
scanf("%d", &n);
if (n <= 0){
    printf("%d too small",n);
        } else {
            if (n <= 2 && n > 0)
                {
                     printf("f(%d) ",n);
                } else {
                     while(n > 2)
                            {
                                fn = fn_1 + fn_2;
                                fn_2 = fn_1;
                                fn_1 = fn;
                                n = n - 1;
                            }
                        printf("f(%d) ",fn);
                        }
                 }
                   


}