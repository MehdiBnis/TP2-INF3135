# Jeu de bataille navale

Ce projet contient les fichiers source, les modules, les tests unitaires et un fichier Makefile nécessaires à l'assemblage d'un jeu de bataille navale.

## Installation des modules nécessaires
```
apt-get update
apt install -y libcunit1 libcunit1-doc libcunit1-dev
apt install -y git build-essential pkg-config
apt install -y bats
```

## Importation du projet

Avant de commencer, veuillez importer ce projet sur votre branche locale:
```
cd votre_dossier
git clone https://gitlab.info.uqam.ca/bennis.mehdi/inf3135-hiver2024-tp2.git
```
## Assemblage et exécution du jeu

1. Assemblez l'exécutable `bataille_navale` avec le fichier `Makefile`: exécutez simplement la commande `make` sur le terminal.
2. Lancez le jeu en entrant sur le terminal la commande `./bataille_navale`.
3. Il est également possible de lancer le jeu avec l'option `-S` suivie d'un nom de fichier pour enregistrer les statistiques de la partie sur ce fichier. Par exemple: `./bataille_navale -S stats.txt`.
4. Pour supprimer les fichiers objets `.o` et l'exécutable `bataille_navale`, entrez sur le terminal la commande `make clean`.

## Structure du projet

    inf3135-hiver2024-tp2
    │
    ├── bats: modules de test bats
    │
    ├── include: fichiers d'entête
    │   ├── entree.h
    │   ├── jeu.h
    │   ├── navire.h
    │   ├── plateau.h
    │   ├── statistiques.h
    │   └── util.h
    │
    ├── (obj): fichiers objets générés
    │
    ├── src: fichiers source C
    │   ├── entree.c: gère les entrées de l'utilisateur
    │   ├── jeu.c: logique du jeu
    │   ├── main.c: fonction main du projet
    │   ├── navire.c: implémente la structure d'un navire
    │   ├── plateau.c: initialise et met à jour le plateau 
    │   ├── statistiques.c: sauvegarde les statistiques de la partie
    │   └── util.c: fonctions générales à utiliser
    │
    ├── test: fichiers tests CUnit
    │   ├── main.c
    │   ├── test_entree.c
    │   ├── test_entree.h
    │   ├── test_navire.c
    │   ├── test_navire.h
    │   ├── test_plateau.c
    │   ├── test_plateau.h
    │   ├── test_statistiques.c
    │   └── test_statistiques.h
    │
    ├── bataille_navale.bats
    ├── Makefile
    ├── README.md
    ├── .gitignore
    └── .gitlab-ci.yml
    
## Tests

Pour faire tester le jeu à l'aide de CUnit et Bats, entrez la commande suivante: `make test`.
