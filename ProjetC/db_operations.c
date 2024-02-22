#include "db_operations.h"
#include <stdio.h>
#include <string.h>
#include <regex.h>


// Structure pour stocker les informations d'une adresse IP
#define MAX_MASK_SIZE 15 // Ajustement pour contenir "255.255.255.255"

typedef struct {
    char adresse_ip[MAX_IP_SIZE + 1];
    char masque[MAX_MASK_SIZE + 1]; // Ajusté pour le masque complet
    char adresse_binaire[33]; // 32 bits + '\0'
    char adresse_hexa[9]; // 8 caractères + '\0'
} AdresseIP;

// Tableau global pour stocker les adresses IP (ajustez la taille selon les besoins)
AdresseIP adresses_ip[100];
int nombre_adresses_ip = 0;
//permet de charger et stocker les ip
void load_ip_addresses(MYSQL *conn) {
    nombre_adresses_ip = 0;
    if (mysql_query(conn, "SELECT adresse_ip, masque, adresse_binaire, adresse_hexa FROM reseau")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)) && nombre_adresses_ip < 100) {
        strncpy(adresses_ip[nombre_adresses_ip].adresse_ip, row[0], MAX_IP_SIZE);
        strncpy(adresses_ip[nombre_adresses_ip].masque, row[1], MAX_MASK_SIZE + 1);
        strncpy(adresses_ip[nombre_adresses_ip].adresse_binaire, row[2], 32);
        strncpy(adresses_ip[nombre_adresses_ip].adresse_hexa, row[3], 8);
        adresses_ip[nombre_adresses_ip].adresse_ip[MAX_IP_SIZE] = '\0';
        adresses_ip[nombre_adresses_ip].masque[MAX_MASK_SIZE] = '\0';
        adresses_ip[nombre_adresses_ip].adresse_binaire[32] = '\0';
        adresses_ip[nombre_adresses_ip].adresse_hexa[8] = '\0';
        nombre_adresses_ip++;
    }

    mysql_free_result(result);
}
//permet d'afficher les adresses
void list_ip_addresses() {
    for (int i = 0; i < nombre_adresses_ip; i++) {
        printf("Adresse IP: %s, Masque: %s, Binaire: %s, Hexa: %s\n",
               adresses_ip[i].adresse_ip,
               adresses_ip[i].masque,
               adresses_ip[i].adresse_binaire,
               adresses_ip[i].adresse_hexa);
    }
}

__attribute__((unused)) void conversation_binary(const char *ip, char *binary) {
    unsigned int octet[4];
    sscanf(ip, "%u.%u.%u.%u", &octet[0], &octet[1], &octet[2], &octet[3]);

    sprintf(binary, "%08u%08u%08u%08u",
            1 << 7 & octet[0], 1 << 7 & octet[1], 1 << 7 & octet[2], 1 << 7 & octet[3]);
}


void ip_to_binary(const char *ip, char *binary) {
    unsigned int octet[4];
    sscanf(ip, "%u.%u.%u.%u", &octet[0], &octet[1], &octet[2], &octet[3]);

    // Conversion de l'adresse IP en binaire
    int index = 0;
    for (int i = 3; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            binary[index++] = ((octet[i] >> j) & 1) + '0';
        }
        if (i > 0) {
            binary[index++] = '.';
        }
    }
    binary[index] = '\0';
}

void ip_to_hexadecimal(const char *ip, char *hex) {
    unsigned int octet[4];
    sscanf(ip, "%u.%u.%u.%u", &octet[0], &octet[1], &octet[2], &octet[3]);

    // Conversion de l'adresse IP en hexadécimal
    snprintf(hex, 13, "%02X.%02X.%02X.%02X", octet[0], octet[1], octet[2], octet[3]);
}


void add_ip_address(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char adresse_ip[16];
    char masque[MAX_MASK_SIZE + 1];
    char adresse_binaire[41];
    char adresse_hexa[13];
    int valid;


    do {
        printf("Entrez l'adresse IP: ");
        scanf("%15s", adresse_ip);
        valid = validate_ip_address(adresse_ip);
        if (!valid) {
            printf("Adresse IP invalide, veuillez réessayer.\n");
        }
    } while (!valid);

    do {
        printf("Entrez le masque: ");
        scanf("%15s", masque);
        valid = validate_subnet_mask(masque);
        if (!valid) {
            printf("Masque de sous-réseau invalide, veuillez réessayer.\n");
        }
    } while (!valid);

    ip_to_binary(adresse_ip, adresse_binaire);
    ip_to_hexadecimal(adresse_ip, adresse_hexa);

    char query[512];
    snprintf(query, sizeof(query),"INSERT INTO reseau (adresse_ip, masque, adresse_binaire, adresse_hexa) VALUES ('%s', '%s', '%s', '%s')", adresse_ip, masque, adresse_binaire, adresse_hexa);


    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed\n");
    }

}

    int validate_ip_address(char *ipAddress) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char *pattern = "^([0-9]{1,3}\\.){3}[0-9]{1,3}$";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "regex n'a pas reussi a compiler\n");
        exit(1);
    }
    reti = regexec(&regex, ipAddress, 0, NULL, 0);
    if (reti == REG_NOMATCH) {
        puts("pas le bon format d'IP");
        regfree(&regex);
        return 0;
    }
    regfree(&regex);

    // Vérification de chaque octet
    char *token = strtok(ipAddress, ".");
    while (token != NULL) {
        int octet = atoi(token);
        if (octet < 0 || octet > 255) {
            puts("pas le bon range pr l'IP (1-254)");
            return 0;
        }
        token = strtok(NULL, ".");
    }

    puts("c'est valide");
    return 1;
}

int validate_subnet_mask(char *subnetMask) {
    char *token = strtok(subnetMask, ".");
    while (token != NULL) {
        int octet = atoi(token);
        if (octet < 0 || octet > 255) {
            puts("Le masque de sous-réseau n'est pas valide.");
            return 0;
        }
        token = strtok(NULL, ".");
    }

    puts("Le masque de sous-réseau est valide.");
    return 1;
}

void delete_ip_address(MYSQL *conn) {
    char ip[MAX_IP_SIZE + 1];
    printf("Entrez l'adresse IP à supprimer : ");
    scanf("%s", ip);

    char query[128];
    snprintf(query, sizeof(query), "DELETE FROM reseau WHERE adresse_ip = '%s'", ip);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erreur de suppression : %s\n", mysql_error(conn));
    } else if (mysql_affected_rows(conn) == 0) {
        printf("Aucune adresse IP correspondante trouvée dans la base de données.\n");
    } else {
        printf("Adresse IP supprimée avec succès.\n");
    }
}


void filterBySubnet(MYSQL* conn) {
    char adresse_ip[MAX_IP_SIZE + 1];
    char masque[MAX_MASK_SIZE + 1];
    char userNetwork[MAX_IP_SIZE + 1];

    // Demander à l'utilisateur une adresse réseau
    printf("Entrez une adresse réseau (format xxx.xxx.xxx.xxx) : ");
    scanf("%s", userNetwork);

    // Demander à l'utilisateur un masque
    printf("Entrez un masque de sous-réseau (format xxx.xxx.xxx.xxx) : ");
    scanf("%s", masque);

    char query[256];
    // Utilisation de la fonction INET_ATON pour convertir l'adresse réseau et le masque en entiers
    sprintf(query, "SELECT adresse_ip FROM reseau WHERE (INET_ATON(adresse_ip) & INET_ATON('%s')) = INET_ATON('%s') & INET_ATON('%s')", masque, userNetwork, masque);

    printf("Requête SQL : %s\n", query);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erreur lors de l'exécution de la requête : %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Erreur lors de la récupération des résultats : %s\n", mysql_error(conn));
        return;
    }

    printf("Adresses IP du même sous-réseau que %s avec le masque %s :\n", userNetwork, masque);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("%s\n", row[0]);
    }

    mysql_free_result(result);
}






