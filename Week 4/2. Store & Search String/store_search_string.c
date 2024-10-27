#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KEYS 100000

char* database[MAX_KEYS];
int db_size = 0;

int find(const char* line) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i], line) == 0) 
            return 1;
    }
    return 0;
}

int insert(const char* line) {
    if (find(line)) return 0;
    
    database[db_size] = (char*)malloc(strlen(line) + 1);
    strcpy(database[db_size], line);
    db_size++;
    
    return 1;
}

int main() {
    char line[51], command[20];
    
    while (scanf("%s", line)) {
        if (!strcmp(line, "*")) break;
        insert(line);
    }
    
    while(scanf("%s", command)) {
        if (!strcmp(command, "***")) break;
        
        scanf("%s", line);
        if (!strcmp(command, "find")) printf("%d\n", find(line));
        else if (!strcmp(command, "insert")) printf("%d\n", insert(line));
    }
    
    return 0;
}
