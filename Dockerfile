# Utilisez une image Ubuntu de base
FROM ubuntu:latest

# Mettez à jour et installez les dépendances nécessaires
RUN apt-get update && apt-get install -y gcc make libssl-dev

# Copiez le contenu du répertoire src de votre projet dans le conteneur
COPY ./src /app

# Définissez le répertoire de travail
WORKDIR /app

# Compilez votre code C
RUN make

# Commande par défaut à exécuter lorsque le conteneur est lancé
CMD ["/bin/bash"]