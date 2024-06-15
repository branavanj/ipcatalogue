# Catalogue d'IP

## Description
Catalogue d'IP est un projet conçu pour gérer et cataloguer les adresses IP et les opérations associées. Le projet est principalement écrit en C et utilise CMake pour la gestion des builds.

## Fonctionnalités
- Gestion des adresses IP
- Connexion aux bases de données
- Exécution des opérations sur les bases de données

## Structure du répertoire
- `cmake-build-debug/`: Répertoire de build
- `CMakeLists.txt`: Fichier de configuration CMake
- `adresses-ip.txt`: Fichier de données des adresses IP
- `db_connect.c`, `db_connect.h`: Fonctions de connexion à la base de données
- `db_operations.c`, `db_operations.h`: Fonctions d'opérations sur la base de données
- `main.c`: Fichier principal du programme

## Installation
1. Clonez le dépôt :
    ```sh
    git clone https://github.com/branavanj/ipcatalogue.git
    ```
2. Accédez au répertoire du projet :
    ```sh
    cd ipcatalogue
    ```
3. Créez le build :
    ```sh
    cmake .
    make
    ```

## Utilisation
1. Exécutez le programme :
    ```sh
    ./ipcatalogue
    ```
2. Suivez les instructions à l'écran pour gérer les adresses IP et effectuer les opérations sur la base de données.

## Contribuer
Les contributions sont les bienvenues ! Veuillez ouvrir une issue ou soumettre une pull request.

## Licence
Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

