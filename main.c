/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IP_SIZE 15
#define MAX_MASK_SIZE 3
#define MAX_LINE_SIZE (MAX_IP_SIZE + MAX_MASK_SIZE + 2)  // IP/Mask + newline

struct IPAddress {
    char ip[MAX_IP_SIZE + 1];
    char mask[MAX_MASK_SIZE + 1];
};

void loadIPAddresses(struct IPAddress *ipCatalog, int *ipCount) {
    FILE *file = fopen("adresses-ip.txt", "r");
    char line[MAX_LINE_SIZE];

    if (file == NULL) {
        printf("Impossible de trouver le fichier des adresses IP. Un nouveau fichier sera créé.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, "/");
        if (token != NULL) {
            strncpy(ipCatalog[*ipCount].ip, token, MAX_IP_SIZE);
            token = strtok(NULL, "\n");
            if (token != NULL) {
                strncpy(ipCatalog[*ipCount].mask, token, MAX_MASK_SIZE);
                (*ipCount)++;
            }
        }
    }

    fclose(file);
}

void printMenu() {
    printf("\n"
           " a - Entrez une adresse ip \n"
           " l - Afficher les adresses IP\n"
           " s - Afficher les ip par rapport au masque de sous reseau\n"
           " d - Supprimer une IP\n"
           " q - Quitter\n");
}


int validateIP(const char *ip) {
    int num, dots = 0;
    const char *ptr = ip;

    if (ip == NULL) {
        return 0;
    }

    while (*ptr) {
        if (*ptr == '.') {
            if (++dots > 3) {  // Plus de 3 points signifie plus de 4 octets
                return 0;
            }
        } else if (*ptr >= '0' && *ptr <= '9') {  // Vérifie si c'est un chiffre
            num = strtol(ptr, (char **)&ptr, 10);  // Convertit la partie numérique en entier
            if (num < 0 || num > 255) {  // Vérifie la plage de l'octet
                return 0;
            }
        } else {
            return 0;  // Caractère invalide pour une adresse IP
        }
        ptr++;
    }

    // Une adresse IP valide doit avoir exactement 3 points
    return dots == 3;
}


void addIPAddress(struct IPAddress *ipCatalog, int *ipCount) {
    char ip[MAX_IP_SIZE + 1];

    printf("Entrez une adresse IP: ");
    scanf("%15s", ip);  // Limite la saisie à 15 caractères pour éviter le débordement de tampon

    if (validateIP(ip)) {
        strcpy(ipCatalog[*ipCount].ip, ip);
        (*ipCount)++;
        printf("Adresse IP ajoutée avec succès.\n");
    } else {
        printf("Adresse IP invalide.\n");
    }
}



void printBinary(const char *ip) {
    unsigned int num;
    char binary[9];  // 8 bits + caractère nul
    const char *ptr = ip;

    while (*ptr) {
        if (*ptr == '.') {
            printf(".");
        } else {
            num = strtol(ptr, (char **)&ptr, 10);
            for (int i = 7; i >= 0; i--) {
                binary[i] = (num % 2) ? '1' : '0';
                num /= 2;
            }
            binary[8] = '\0';  // Ajoute le caractère de fin de chaîne
            printf("%s", binary);
        }
        if (*ptr != '\0') {
            ptr++;  // Passer au prochain caractère s'il n'est pas à la fin de la chaîne
        }
    }
    printf("\n");
}


void printHex(const char *ip) {

}


void printDecimal(const char *ip) {

}


void searchByMask(const struct IPAddress *ipCatalog, int ipCount) {

}
*/
/*
int main() {
    struct IPAddress ipCatalog[100];
    int ipCount = 0;



    char choice;
    do {
        printMenu();
        printf("\nSaisir une lettre: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                addIPAddress(ipCatalog, &ipCount);
                break;
            case 'l':
                break;
            case 's':
                searchByMask(ipCatalog, ipCount);
                break;
            case 'd':
                break;
            case 'q':
                break;
            default:
                printf("Choix non reconnu. Veuillez ressayer.\n");
        }
    } while (choice != 'q');



    return 0;*//*

//}
*/
