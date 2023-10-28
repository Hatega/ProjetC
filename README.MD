# Projet C : Casseur de mot de passe

## Pré-Requis
OpenSSL est utilisé, il doit donc avoir les librairies nécessaire avant la compilation

_Commande d'installation:_ sudo apt install libssl-dev

## Compilation
Un MAKEFILE est présent, il faut donc se placer dans le répertoire contenant le projet et faire la commande make.

_Commande de compilation:_ make

## Utilisation
Le projet contient 3 mode d'utilisation generate, lookup et les deux précedent combiné.

### Generate
Le mode generate lit un fichier [Fichier_Input] ligne par ligne et écrit dans un autre fichier [Fichier_Output] le hash de chaque ligne et la ligne correspondante. Il est possible de choisir l'algorithme de hachage. 
Le mode generate peut donc prendre jusqu'à 3 arguments différents dans n'importe quel ordre.

_Commande generate:_ ./projetc -G -i [Fichier_Input] -o [Fichier_Output] -a [Algorithme_Hachage] 

**Argument -i :** Permet de donner le nom/chemin du fichier dictionnaire à utiliser pour généré les différents condensats. 

**Argument -o :** Permet de donner le nom/chemin du fichier de sortie où sera écrit tout les condensat générés.

**Argument -a :** (Optionel) Permet de donner l'algorithme de hachage à utiliser parmi : sha256, sha1 et md5. Par défaut : sha256.

### Lookup
Le mode lookup lit un fichier [Fichie_Input] de condensat passé en argument et récupère également une liste de hash à trouver en STDIN. 
Pour la saisie de hash à trouver :
 - écrire les hashs à trouver séparer par des retours à la ligne
 - une fois fini faire Ctrl + D pour sortir de la saisie 
Le mode lookup prend un seul argument.

_Commande lookup:_ ./projetc -L -i [Fichier_Input]

**Argument -i :** Permet de donner le nom/chemin du fichier condensat qui sera utilisé comme base de donnée pour la recherche de hash

### Generate + Lookup 
Le mode generate+lookup, enchaine le mode generate et lookup. Ainsi ce mode prend les mêmes arguments que le mode G et le fichier généré par ce mode est directement utilisé en tant que fichier d'input du mode lookup. 
Le mode generate+lookup peut prendre jusqu'à 3 arguments différents (les mêmes que le mode generate). Et prend une saisie sur STDIN comme le mode lookup (pour arreté la saisie: Ctrl+D).

_Commande generate+lookup:_ ./projetc -GL -i [Fichier_Input] -o [Fichier_Output] -a [Algorithme_Hachage] 

## Résumé des commandes

sudo apt install libssl-dev

make

./projetc -G -i dictinnaire.txt -o condensat.txt  -a md5

./projetc -L -i condensat.txt

f02368945726d5fc2a14eb576f7276c0

[Ctrl+D]

./projetc -GL -i dictinnaire.txt -o condensat.txt  -a md5

f02368945726d5fc2a14eb576f7276c0

[Ctrl+D]
