#include "base.h"


char* clear_vokable(char* value){

char* temp = xmalloc(sizeof(char));
int i = 0;
int j = 0;
    while( i < strlen(value)){
        if( value[i] == 'a' || value[i] == 'e' || value[i] == 'i' || value[i] == 'o' || value[i] == 'u' || value[i] == 'A' || value[i] == 'E' || value[i] == 'I' || value[i] == 'O' || value[i] == 'U'  ){
        i++;
        } else {
            temp[j] = value[i];
            j++;
            i++;
        }
    }
    return temp;
}


bool x3(char* value){
    for (int i = 0; value[i] != '\0'; i++){
        int j = 0;
        if (value[i] >= '0' &&  value[i] <= '9' ){
            while(value[i] >= '0' &&  value[i] <= '9'  ){
                i++;
                j++;
            }
            if( j % 3 == 0){
                return true;
            }
        }else {
            i++;
        }
    }
    return false;
}


char* find_and_replace(char* text, char* replace, char* replacement){
    char* textg = xmalloc(sizeof(char));
    for(int i = 0; text[i] != '\0'; i++){
        int j = 0;
        while(replace[j] != '\0'){
            if (text[i] == replace[j]){
                j++;
                i++;
            } else {
                break;
            }
        }
        if( j == strlen(replace)){
            for(int k = 0; k < i; k++){
                textg[k] = text[k];
            }
        }
    }
    return textg;
}
  

char* add(char* a, char* b){
    char* c = xcalloc(strlen(a) + strlen(b) + 1, sizeof(char));
    int i = 0;
    while(i < strlen(a)){
        c[i] = a[i];
        i++;
    }
    for (int j = 0; j < strlen(b); j++){
        c[i] = b[j];
        i++;
    }
    return c;
}

typedef struct Aray{
    char* S1;
    char* S2;
}Aray;

void split(char* text, char point){
  
    int i = 0;
    while (text[i] != point) {
        i++;
    }
    char* ss = xcalloc(i + 1 ,sizeof(char));
    char* sc = xcalloc(strlen(text) - 1,sizeof(char));
    for(int k = 0; k < i; k++ ){
        ss[k] = text[k];
    }
    ss[i + 1] = '\0';
    int t = 0;
    for(int j = i + 1; j < strlen(text); j++ ){
        sc[t] = text[j];
        t++;
    }
    printf("%s  |  %s", ss, sc);
}

void gem(char* t1, char* t2 ){
    int i = 0;
    while ( t1[i] == t2[i]){
        i++;
    }
    char* text = xcalloc(i + 1, sizeof(char));
    for(int b = 0; b < i - 1  ; b++){
        text[b] = t1[b];
    }
    printf("%s.", text);
}

typedef struct zen{
    char* S1;
    char* S2;
    char* S3;
}zen;

void zensur(char* text, zen* z){
    
    for(int i = 0; i < strlen(text); i++){
        int a = 0;
        while ( a < strlen(z->S1)){
            if(text[i + a ] == z->S1[a]){
                a++;
            }else {
                break;
            }
        }
        if (a == strlen(z->S1) ){
           for(int b = 1; b < strlen(z->S1); b++){
               text[i + b] = '*';
           }
        }
    }
    for(int i = 0; i < strlen(text); i++){
    int a = 0;
    while ( a < strlen(z->S2)){
        if(text[i + a ] == z->S2[a]){
            a++;
        }else {
            break;
        }
    }
    if (a == strlen(z->S2) ){
        for(int b = 1; b < strlen(z->S2); b++){
            text[i + b] = '*';
        }
    }
    }
    for(int i = 0; i < strlen(text); i++){
    int a = 0;
    while ( a < strlen(z->S3)){
        if(text[i + a ] == z->S3[a]){
            a++;
        }else {
            break;
        }
    }
    if (a == strlen(z->S3) ){
        for(int b = 1; b < strlen(z->S3); b++){
            text[i + b] = '*';
        }
    }
    }
    printf ("%s.",text);
}

int main(void){
    zen* zen = xcalloc(1,sizeof(zen));
    zen->S1 = "doof";
    zen->S2 = "bescheuert";
    zen->S3 = "idiotisch";
    char* text = s_input(100);

    zensur(text  ,zen);

    return 0;
}
