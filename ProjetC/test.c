// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_connect.h"
#include "db_operations.h"




int main() {
    MYSQL *conn = db_connect();
    if (!conn) {
        fprintf(stderr, "Connexion à la base de données échouée.\n");
        return 1;
    }
    load_ip_addresses(conn);

    char choice;

    do {

        printf("\nMenu principal :\n");
        printf("a - Ajouter une nouvelle adresse IP\n");
        printf("l - Lister les adresses IP\n");
        printf("s - Rechercher par masque\n");
        printf("d - Supprimer une adresse IP\n");
        printf("q - Quitter\n");
        printf("Entrez votre choix : ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                // Implémentez votre logique pour ajouter une adresse IP
                add_ip_address(conn);
                break;
            case 'l':
                // Implémentez votre logique pour lister les adresses IP
                load_ip_addresses(conn);
                list_ip_addresses();
                break;
            case 's':
                // Implémentez votre logique pour rechercher par masque
                filterBySubnet (conn);
                break;
            case 'd':
                // Implémentez votre logique pour supprimer une adresse IP
                delete_ip_address(conn);
                break;
            case 'q':
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 'q');

    db_disconnect(conn);
    return 0;
}












//const char* insert_query = "INSERT INTO reseau (adresse_ip, masque, adresse_binaire, adresse_hexa) VALUES ('192.168.1.2', '255.255.255.0', BINARY '11000000101010000000000100000010', 'C0A80102')";
//        if (mysql_query(conn, insert_query)) {
//            fprintf(stderr, "Erreur d'insertion : %s\n", mysql_error(conn));
//        } else {
//            printf("Insertion réussie.\n");
//        }

//
// Created by ssuve on 20/02/2024.
//
