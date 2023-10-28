# Utilisation de l'image de base pour C/C++
FROM gcc:latest

# Installation de libssl-dev
RUN apt-get update && apt-get install -y libssl-dev

# Création d'un répertoire de travail
WORKDIR /app

# Copie de votre code source dans le conteneur
COPY . /app

# Compilation du projet avec make
RUN make

# Commande par défaut pour exécuter votre application (à personnaliser)
CMD ["./projetc"]