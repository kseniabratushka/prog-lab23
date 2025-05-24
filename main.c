#include <stdio.h>
#include <string.h>

#define MAX_ENTERPRISES 10
#define MAX_LENGTH 100

typedef struct 
{
    char name[MAX_LENGTH];
    char location[MAX_LENGTH];
    double fundValue;
} Enterprise;

int main() 
{
    system("chcp 65001");
    Enterprise enterprises[MAX_ENTERPRISES];
    int numEnterprises;
    char searchLocation[MAX_LENGTH];
    FILE *outputFile;

    printf("Введіть кількість підприємств (максимум %d): ", MAX_ENTERPRISES);
    scanf("%d", &numEnterprises);
    getchar();

    if (numEnterprises <= 0 || numEnterprises > MAX_ENTERPRISES) 
    {
        printf("Невірна кількість підприємств!\n");
        return 1;
    }

    for (int i = 0; i < numEnterprises; i += 1) 
    {
        printf("\nПідприємство #%d\n", i + 1);

        printf("Назва: ");
        fgets(enterprises[i].name, MAX_LENGTH, stdin);
        enterprises[i].name[strcspn(enterprises[i].name, "\n")] = '\0';

        printf("Місцезнаходження: ");
        fgets(enterprises[i].location, MAX_LENGTH, stdin);
        enterprises[i].location[strcspn(enterprises[i].location, "\n")] = '\0';

        printf("Вартість фондів: ");
        scanf("%lf", &enterprises[i].fundValue);
        getchar();
    }

    printf("\nВведіть місцезнаходження для пошуку: ");
    fgets(searchLocation, MAX_LENGTH, stdin);
    searchLocation[strcspn(searchLocation, "\n")] = '\0';

    outputFile = fopen("enterprises_output.txt", "w");
    if (outputFile == NULL) 
    {
        printf("Помилка відкриття файлу для запису!\n");
        return 1;
    }

    printf("\nРезультати пошуку в місці '%s':\n", searchLocation);
    fprintf(outputFile, "Результати пошуку в місці '%s':\n", searchLocation);

    int found = 0;
    for (int i = 0; i < numEnterprises; i += 1) 
    {
        if (strcmp(enterprises[i].location, searchLocation) == 0) 
        {
            printf("Назва: %s\n", enterprises[i].name);
            printf("Місцезнаходження: %s\n", enterprises[i].location);
            printf("Вартість фондів: %.2lf\n\n", enterprises[i].fundValue);

            fprintf(outputFile, "Назва: %s\n", enterprises[i].name);
            fprintf(outputFile, "Місцезнаходження: %s\n", enterprises[i].location);
            fprintf(outputFile, "Вартість фондів: %.2lf\n\n", enterprises[i].fundValue);

            found = 1;
        }
    }

    if (!found) 
    {
        printf("Підприємств у місці '%s' не знайдено.\n", searchLocation);
        fprintf(outputFile, "Підприємств у місці '%s' не знайдено.\n", searchLocation);
    }

    fclose(outputFile);
    printf("Результати записано у файл 'enterprises_output.txt'.\n");

    return 0;
}