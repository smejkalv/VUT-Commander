// VUTCommander.cpp: Definuje vstupní bod pro aplikaci.
//

#include "VUTCommander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void listFiles(char* path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(path, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        perror("Chyba pri hledani souboru");
        exit(EXIT_FAILURE);
    }

    do {
        printf("%s\n", findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void copyFile(char* source, char* destination) {
    FILE* sourceFile, * destFile;
    char ch;

    sourceFile = fopen(source, "rb");
    destFile = fopen(destination, "wb");

    if (sourceFile == NULL || destFile == NULL) {
        perror("Chyba pri otevirani souboru");
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destFile);
    }

    printf("Soubor zkopirovan\n");

    fclose(sourceFile);
    fclose(destFile);
}

int main() {
    int choice;
    char path[100], source[100], destination[100];

    printf("Vitejte v konzolovem spravci souboru\n");

    while (1) {
        printf("1. Zobrazit obsah adresare\n");
        printf("2. Kopirovat soubor\n");
        printf("3. Konec\n");

        printf("Vyberte moznost: ");
        scanf(" %d", &choice);

        if (choice == 1) {
            if (GetCurrentDirectory(MAX_PATH, path) != 0) {
                strcat(path, "\\*");
                listFiles(path);
            }
            else {
                perror("Chyba pri ziskavani aktualniho adresare");
                printf("Zadejte cestu k adresari: ");
                scanf("%s", path);
                strcat(path, "\\*");
                listFiles(path);
            }
        }
        else if (choice == 2) {
            printf("Zadejte zdrojovy soubor: ");
            scanf("%s", source);
            printf("Zadejte cilovy soubor: ");
            scanf("%s", destination);
            copyFile(source, destination);
        }
        else if (choice == 3) {
            printf("Konec programu.\n");
            exit(EXIT_SUCCESS);
        } else {
            printf("Neplatna volba.\n");
        }
    }

    return 0;
}


