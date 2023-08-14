# Serveur IRC en C++98 - Projet 42

Bienvenue dans le README du projet **ircserv** réalisé dans le cadre de l'école 42. Ce projet consiste à développer un serveur IRC (Internet Relay Chat) en C++98, permettant la communication en temps réel entre plusieurs clients.

## Présentation du Projet

Le serveur IRC que nous avons développé permet aux utilisateurs de se connecter, de discuter en direct dans des canaux, d'envoyer des messages privés et de gérer différents aspects des canaux. Le projet met l'accent sur une gestion efficace et non bloquante de multiples clients grâce à des opérations d'entrées/sorties non bloquantes et un mécanisme de gestion des événements.

## Fonctionnalités

- **Authentification des Clients**: Les utilisateurs doivent se connecter au serveur en fournissant le bon mot de passe.
- **Gestion des Canaux**: Les utilisateurs peuvent rejoindre des canaux, envoyer des messages dans les canaux et recevoir les messages des autres utilisateurs.
- **Messages Privés**: Les utilisateurs peuvent échanger des messages privés avec d'autres utilisateurs.
- **Opérateurs de Canal & Global**: Les canaux ont des opérateurs avec des privilèges spéciaux pour gérer le canal. Les opérateurs globaux ont des permissions qui surpassent celle des opérateurs de canaux.
- **Commandes de Canal**: Implémentation de commandes spécifiques aux canaux, telles que KICK, INVITE, TOPIC et MODE.

**Utilisation**

1. **Clonage du Repository**:
   Clonez ce repository en utilisant la commande suivante :
   ```shell
   git clone https://github.com/jalevesq/ft_irc.git

2. **Compilation du Projet**:
Naviguez dans le répertoire du projet et compilez-le en utilisant la commande suivante 
   ```shell
   make

3. **Démarrer le Serveur**:
Après compilation, exécutez le serveur avec la commande suivante :
Pour démarrer le serveur, exécutez la commande suivante :
./irc <port> <password>

- `<port>` : Numéro du port sur lequel le serveur écoutera les connexions entrantes.
- `<password>` : Mot de passe requis pour s'identifier auprès du serveur IRC.

Ce projet a été réalisé en collaboration avec [@Dave demers.](https://github.com/Producks)
