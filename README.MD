# Projet C : Casseur de mot de passe

## Docker
Assurez-vous d'avoir Docker installé sur votre machine.

Téléchargez le contenu de ce dépôt sur votre machine. Le Dockerfile se situe à la racine.

Ouvrez un terminal dans le répertoire où se trouve le dépôt téléchargé. Ajoutez dans le répertoire src les différents fichiers que vous voudrez utiliser par la suite (fichier de dictionnaire/condensat, fichier de hash à trouver). Ensuite, exécutez la commande suivante pour construire l'image Docker :

```shell
sudo docker build -t mon_image .
```

Cette commande crée une image Docker nommée "mon_image" à partir du Dockerfile.

Après avoir construit l'image, exécutez-la avec la commande suivante :

```shell
sudo docker run -it mon_image
```

Vous serez connecté à un terminal interactif dans l'image Docker.

À l'intérieur du terminal Docker, vous pouvez utiliser le projet comme normal. Il est déjà compilé, vous pouvez donc exécuter les commandes spécifiques du projet (voir partie Utilisation), par exemple :

```shell
./project -G -i fichier.txt -o fichier_result.txt -a md5
```

Pour quitter le terminal Docker et revenir à votre système local, tapez simplement :

```shell
exit
```
## Sans Docker
### Instalation de libraire
Le projet utilise OpenSSL, il est donc nécessaire d'installer les bibliothèques requises avant de procéder à la compilation.

_Commande d'installation :_ 
```shell
sudo apt install libssl-dev
```

### Compilation
Un fichier MAKEFILE est fourni pour simplifier le processus de compilation. Assurez-vous d'être dans le répertoire contenant le projet et exécutez la commande suivante pour compiler le programme.

_Commande de compilation :_ 
```shell
make
```

## Utilisation
Le projet propose trois modes d'utilisation : "generate," "lookup," et une combinaison des deux.

### Generate
Le mode "generate" lit un fichier d'entrée ([Fichier_Input]) ligne par ligne et écrit le hachage de chaque ligne ainsi que la ligne correspondante dans un autre fichier ([Fichier_Output]). Vous pouvez choisir l'algorithme de hachage à utiliser.

Le mode "generate" accepte jusqu'à trois arguments différents, dans n'importe quel ordre.

_Commande "generate" :_ 
```shell
./projetC -G -i [Fichier_Input] -o [Fichier_Output] -a [Algorithme_Hachage]
```

- Argument `-i` : Permet de spécifier le nom/chemin du fichier dictionnaire à utiliser pour générer les différents condensats.
- Argument `-o` : Permet de spécifier le nom/chemin du fichier de sortie où tous les condensats générés seront écrits.
- Argument `-a` : (Optionnel) Permet de spécifier l'algorithme de hachage à utiliser parmi : sha256, sha1 et md5. Par défaut, l'algorithme est sha256.

### Lookup
Le mode "lookup" lit un fichier d'entrée ([Fichier_Input]) contenant des condensats en tant que base de données et récupère une liste de hachages à rechercher depuis l'entrée standard (STDIN). Pour entrer les hachages à rechercher :

- Écrivez les hachages à rechercher, en les séparant par des retours à la ligne.
- Une fois que vous avez terminé, appuyez sur Ctrl + D pour terminer la saisie.

Le mode "lookup" prend un seul argument.

_Commande "lookup" :_ 
```shell
./projetC -L -i [Fichier_Input]
```

- Argument `-i` : Permet de spécifier le nom/chemin du fichier contenant les condensats qui serviront de base de données pour la recherche de hachages.

### Generate + Lookup
Le mode "generate+lookup" enchaîne le mode "generate" suivi du mode "lookup." Ce mode accepte les mêmes arguments que le mode "generate" pour la génération des condensats. Le fichier généré par le mode "generate" est utilisé directement en tant que fichier d'entrée pour le mode "lookup." Le mode "generate+lookup" peut également prendre une saisie sur STDIN (pour arrêter la saisie : Ctrl+D).

_Commande "generate+lookup" :_ 
```shell
./projetC -GL -i [Fichier_Input] -o [Fichier_Output] -a [Algorithme_Hachage]
```

## Résumé des commandes

Docker : 

```shell
sudo docker build -t mon_image .
sudo docker run -it mon_image
```

Sans Docker :

```shell
sudo apt install libssl-dev
make
```

Pour utiliser le mode "generate" :
```shell
./projetC -G -i dictionnaire.txt -o condensat.txt -a md5
```

Pour utiliser le mode "lookup" :
```shell
./projetC -L -i condensat.txt
```

Pour utiliser le mode "generate+lookup" :
```shell
./projetC -GL -i dictionnaire.txt -o condensat.txt -a md5
```
