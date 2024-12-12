#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int carID;
    char brand[50];
    char model[50];
    float rentalCostPerDay;
    float originalRentalCostPerDay;
    int available;
} Car;

#define FILE_NAME "cars.txt"
#define MAX_CARS 40

Car cars[MAX_CARS];
int carCount = 0;


void clearScreen() {
    system("clear || cls");
}


void loadCarsFromFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s.\n", FILE_NAME);
        exit(1);
    }

    carCount = 0;
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%d\n",
                  &cars[carCount].carID,
                  cars[carCount].brand,
                  cars[carCount].model,
                  &cars[carCount].rentalCostPerDay,
                  &cars[carCount].originalRentalCostPerDay,
                  &cars[carCount].available) != EOF) {
        carCount++;
    }
    fclose(file);
}


void saveCarsToFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s pour ecrire.\n", FILE_NAME);
        exit(1);
    }

    for (int i = 0; i < carCount; i++) {
        fprintf(file, "%d,%s,%s,%.2f,%.2f,%d\n",
                cars[i].carID,
                cars[i].brand,
                cars[i].model,
                cars[i].rentalCostPerDay,
                cars[i].originalRentalCostPerDay,
                cars[i].available);
    }
    fclose(file);
}

// FONCTION POUR L'AFFICHAGE DU MENU PRINCIPAL
void afficherMenu() {
    printf("===========================================================\n");
    printf("Bienvenue dans M.Y-Cars - Application de location de voitures\n");
    printf("===========================================================\n");
    printf("1. Afficher les voitures disponibles\n");
    printf("2. Louer une voiture\n");
    printf("3. Retourner une voiture\n");
    printf("4. Afficher les offres disponibles\n");
    printf("5. Appliquer une offre\n");
    printf("6. Supprimer une offre\n");
    printf("7. Afficher les services supplementaires\n");
    printf("8. Quitter\n");
    printf("Choisissez une option : ");
}

// FONCTION D'AFFICHAGE DES VOITURES DISPONIBLES
void afficherVoituresDisponibles() {
    printf("Voitures disponibles :\n");
    for (int i = 0; i < carCount; ++i) {
        if (cars[i].available == 1) {
            printf("Car ID: %d\n", cars[i].carID);
            printf("Brand: %s\n", cars[i].brand);
            printf("Model: %s\n", cars[i].model);
            printf("Rental Cost Per Day: %.2f\n", cars[i].rentalCostPerDay);
            printf("\n");
        }
    }
}

// FONCTION POUR LOUER UNE VOITURE
void louerVoiture() {
    int carID, days;
    printf("Entrez l'ID de la voiture que vous souhaitez louer : ");
    scanf("%d", &carID);
    printf("Entrez le nombre de jours de location : ");
    scanf("%d", &days);

    for (int i = 0; i < carCount; ++i) {
        if (cars[i].carID == carID && cars[i].available == 1) {
            cars[i].available = 0;
            float cost = cars[i].rentalCostPerDay * days;
            printf("Voiture louee :\n");
            printf("Car ID: %d\n", cars[i].carID);
            printf("Brand: %s\n", cars[i].brand);
            printf("Model: %s\n", cars[i].model);
            printf("Days Rented: %d\n", days);
            printf("Total Cost: %.2f\n", cost);
            saveCarsToFile();
            return;
        }
    }
    printf("La voiture demandee n'est pas disponible ou n'existe pas.\n");
}

// FONCTION POUR RETOURNER UNE VOITURE
void retournerVoiture() {
    int carID;
    printf("Entrez l'ID de la voiture à retourner : ");
    scanf("%d", &carID);

    for (int i = 0; i < carCount; ++i) {
        if (cars[i].carID == carID) {
            cars[i].available = 1;
            printf("Voiture retournee avec succes :\n");
            printf("Car ID: %d\n", cars[i].carID);
            printf("Brand: %s\n", cars[i].brand);
            printf("Model: %s\n", cars[i].model);
            saveCarsToFile();
            return;
        }
    }
    printf("La voiture avec l'ID spécifie n'existe pas.\n");
}

// FONCTION POUR AFFICHER LES OFFRES DISPONIBLES
void afficherOffresDisponibles() {
    printf("Offres disponibles :\n");
    const char *offers[5] = {"OFFER1: 10%", "OFFER2: 15%", "OFFER3: 20%", "OFFER4: 25%", "OFFER5: 30%"};
    for (int i = 0; i < 5; i++) {
        printf("%s\n", offers[i]);
    }
}

// FONCTION POUR APPLIQUER UN OFFRE
void appliquerOffre() {
    printf("Entrez l'ID de la voiture pour appliquer une offre : ");
    int carID;
    scanf("%d", &carID);
    for (int i = 0; i < carCount; i++) {
        if (cars[i].carID == carID) {
            printf("Choisissez une offre (10%%, 15%%, 20%%): ");
            float discount;
            scanf("%f", &discount);
            cars[i].rentalCostPerDay -= cars[i].rentalCostPerDay * (discount / 100);
            printf("Nouveau prix journalier: %.2f\n", cars[i].rentalCostPerDay);
            saveCarsToFile();
            return;
        }
    }
    printf("Voiture introuvable pour appliquer une offre.\n");
}

//FONCTION POUR SUPPRIMER UN OFFRE
void supprimerOffre() {
    printf("Entrez l'ID de la voiture pour supprimer une offre : ");
    int carID;
    scanf("%d", &carID);
    for (int i = 0; i < carCount; i++) {
        if (cars[i].carID == carID) {
            cars[i].rentalCostPerDay = cars[i].originalRentalCostPerDay;
            printf("L'offre a été supprimée. Le prix journalier est revenu à %.2f\n", cars[i].rentalCostPerDay);
            saveCarsToFile();
            return;
        }
    }
    printf("Voiture introuvable pour supprimer une offre.\n");
}

// FONCTION POUR AFFICHER LES SERVICES SUPPLEMENTAIRE
void afficherServicesSupplementaires() {
    printf("Services supplementaires disponibles :\n");
    printf("1. Assurance (15.00 par jour)\n");
    printf("2. GPS (10.00 par jour)\n");
    printf("3. Siege enfant (5.00 par jour)\n");
    printf("4. Livraison (30.00 fixe)\n");
    printf("\n");
}

// PROGRAMME PRINCIPALE
int main() {
    loadCarsFromFile();
    int choix;
    do {
        clearScreen();
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                clearScreen();
                afficherVoituresDisponibles();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar();
                break;
            case 2:
                clearScreen();
                louerVoiture();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar();
                break;
            case 3:
                clearScreen();
                retournerVoiture();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar();
                break;
            case 4:
                clearScreen();
                afficherOffresDisponibles();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar();
                break;
            case 5:
                clearScreen();
                appliquerOffre();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar();
                break;
            case 6:
                clearScreen();
                supprimerOffre();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar();
                break;
            case 7:
                clearScreen();
                afficherServicesSupplementaires();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar();
                break;
            case 8:
                clearScreen();
                printf("Merci d'avoir utilise M.Y-Cars. Au revoir !\n");
                getchar(); getchar();
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
                getchar(); getchar();
                break;
        }
    } while (choix != 8);

    return 0;
}
