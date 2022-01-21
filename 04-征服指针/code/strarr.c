#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char name[32];
    char *names[128];
    size_t cnt = 0;
    while (scanf("%s", name) != EOF){
        if (strcmp(name, "#") == 0)
            break;
        names[cnt] = (char *)malloc(strlen(name) + 1);
        strcpy(names[cnt], name);
        cnt++;
    }
    
    // 按下Ctrl+D即可手动键入EOF
    for (int i = 0; i < cnt; i++){
        printf("Indefinite length char array: the %d-th item: %s\n", i, names[i]);
    }
    return 0;
}