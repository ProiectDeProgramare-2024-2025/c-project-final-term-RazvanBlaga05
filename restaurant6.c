#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

typedef struct {
    int id;
    char name[20];
    char infoPath[200];
    char reviewPath[200];
    const char* hours[3];
} Sala;

Sala sali[6] = {
    {1, "Sala 1", "sala1.txt", "reviewsala1.txt", {"13:00", "16:30", "18:45"}},
    {2, "Sala 2", "sala1.txt", "reviewsala1.txt", {"11:00", "13:390", "20:35"}},
    {3, "Sala 3", "sala1.txt", "reviewsala1.txt", {"11:00", "13:30", "20:35"}},
    {4, "Sala 4", "sala1.txt", "reviewsala1.txt", {"11:00", "13:30", "20:35"}},
    {5, "Sala 5", "sala1.txt", "reviewsala1.txt", {"11:00", "13:30", "20:35"}},
    {6, "Sala 6", "sala1.txt", "reviewsala1.txt", {"11:00", "13:30", "10:35"}},
};

void clearScreen() {
    system("cls");
}

void colorizeLine(char* line) {
    char* colon = strchr(line, ':');
    if (colon) {
        *colon = '\0';
        char* key = line;
        char* value = colon + 1;
        
        while (*value == ' ') value++;
        value[strcspn(value, "\n")] = '\0';
        
        if (strstr(key, "Capacitate")) printf(BOLD CYAN "%s:" RESET CYAN " %s\n", key, value);
        else if (strstr(key, "Wifi")) printf(BOLD GREEN "%s:" RESET GREEN " %s\n", key, value);
        else if (strstr(key, "Locuri")) printf(BOLD YELLOW "%s:" RESET YELLOW " %s\n", key, value);
        else if (strstr(key, "Meniul")) printf(BOLD MAGENTA "%s:" RESET MAGENTA " %s\n", key, value);
        else if (strstr(key, "Pret")) printf(BOLD WHITE "%s:" RESET WHITE " %s\n", key, value);
        else if (strstr(key, "Oferta")) printf(BOLD BLUE "%s:" RESET BLUE " %s\n", key, value);
        else printf(WHITE "%s:%s\n", key, value);
    } else {
        printf(WHITE "%s", line);
    }
}

void afisareProgramari() {
    clearScreen();
    printf(BOLD BLUE "===== " RESET BOLD WHITE "Toate Programarile" RESET BOLD BLUE " =====\n\n" RESET);
    
    int found = 0;

    FILE *file = fopen("reviewsala1.txt", "r");
    if (file == NULL) {
        printf(RED "Nu exista programari in sistem.\n" RESET);
    } else {
        char buffer[200];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf(CYAN "%s" RESET, buffer);
            found = 1;
        }
        fclose(file);
    }

    if (!found) {
        printf(RED "Nu exista programari in sistem.\n" RESET);
    }
    
    printf(BOLD "\nApasa Enter pentru a reveni la meniu..." RESET);
    getchar();
    getchar();
}

void afisareSala(Sala sala) {
    clearScreen();
    printf(BOLD BLUE "===== " RESET BOLD WHITE "%s" RESET BOLD BLUE " =====\n" RESET, sala.name);
    printf(YELLOW "Alege o ora:\n" RESET);
    for (int i = 0; i < 3; i++) {
        printf(GREEN "[%d] " RESET CYAN "%s\n", i + 1, sala.hours[i]);
    }
    printf(BLUE "[4] " RESET WHITE "Inapoi\n");
    printf(MAGENTA "[9] " RESET YELLOW "Programeaza-te\n");
}

void programareSala(Sala sala) {
    FILE *file = fopen(sala.reviewPath, "a");
    if (file == NULL) {
        printf(RED "Eroare la deschiderea fisierului pentru programare.\n" RESET);
        return;
    }

    int ora, minut;
    clearScreen();
    printf(BOLD BLUE "===== " RESET BOLD WHITE "%s" RESET BOLD BLUE " =====\n" RESET, sala.name);
    printf(YELLOW "Introdu ora programarii (0-23): " RESET);
    scanf("%d", &ora);

    printf(YELLOW "Introdu minutul programarii (0-59): " RESET);
    scanf("%d", &minut);

    if (ora < 0 || ora > 23 || minut < 0 || minut > 59) {
        printf(RED "Eroare: Ora sau minut invalid.\n" RESET);
        fclose(file);
        return;
    }

    fprintf(file, "Programare la %s la ora %02d:%02d\n", sala.name, ora, minut);
    fclose(file);

    printf(GREEN "\nProgramare efectuata cu succes la ora %02d:%02d!\n" RESET, ora, minut);
    printf(BOLD "\nApasa Enter pentru a reveni la meniu..." RESET);
    getchar();
    getchar();
}



void meniu() {
    clearScreen();
    printf(BOLD BLUE "===== " RESET BOLD WHITE "Programare Restaurant" RESET BOLD BLUE " =====\n" RESET);
    for (int i = 0; i < 6; i++) {
        printf(YELLOW "[%d] " RESET CYAN "%s\n", sali[i].id, sali[i].name);
    }
    printf(MAGENTA "[8] " RESET YELLOW "Vezi toate programarile\n");
    printf(RED BOLD "[9] " RESET RED "EXIT\n" RESET);
}

int main() {
    int alegere = 0;
    int terminator = 0;

    meniu();

    while (!terminator) {
        if (scanf("%d", &alegere) != 1) {
            printf(RED BOLD "\nEroare: " RESET RED "Introduceti un numar valid!\n\n" RESET);
            while (getchar() != '\n');
            meniu();
            continue;
        }

        if (alegere >= 1 && alegere <= 6) {
            Sala salaSelectata = sali[alegere - 1];
            afisareSala(salaSelectata);

            int alegereSala;
            if (scanf("%d", &alegereSala) != 1) {
                printf(RED BOLD "Eroare: " RESET RED "Introduceti un numar valid!\n" RESET);
                while (getchar() != '\n');
                meniu();
                continue;
            }

            if (alegereSala >= 1 && alegereSala <= 3) {
                clearScreen();
                printf(GREEN BOLD "Programare reusita!\n" RESET);
                printf(WHITE "Sala: " RESET CYAN "%s\n", salaSelectata.name);
                printf(WHITE "Ora: " RESET YELLOW "%s\n\n", salaSelectata.hours[alegereSala-1]);
                printf(BLUE "[4] " RESET CYAN "Inapoi\n" RESET);
                scanf("%d", &alegereSala);
                if (alegereSala == 4) meniu();
            } 
            else if (alegereSala == 4) {
                meniu();
            } 
            else if (alegereSala == 9) {
                programareSala(salaSelectata);
                meniu();
            } 
            else {
                printf(RED BOLD "\nEroare: " RESET RED "Optiune invalida!\n\n" RESET);
                meniu();
            }
        }
        else if (alegere == 8) {
            afisareProgramari();
            meniu();
        }
        else if (alegere == 9) {
            clearScreen();
            printf(BOLD RED "La revedere!" RESET WHITE " :)\n" RESET);
            terminator = 1;
        }
        else {
            printf(RED BOLD "\nEroare: " RESET RED "Optiune invalida!\n\n" RESET);
            meniu();
        }
    }

    return 0;
}
