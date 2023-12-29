## HTTP-Server 1.0

#

### Démarrage
Pour démarrer le serveur HTTP:
```bash
chmod u+x run.sh
./run.sh
```    

## Présentation
  Le but du projet est de créer un serveur http accessible par tous les utilisateurs du même réseau.
  L'utilisateur hôte aura le droit de personnaliser son propre site web en ajoutant les fichier HTML nécessaires dans le
  dossier "templates".
  Pour rendre le site disponible il faut tour d'abord vérifier que la port 8080 est bien ouvert sur la machine hôte, les 
  utilisateurs auront accès au site via l'addresse IP publique ou privée de la machine.
> [!warning]
> le serveur ne prend en compte que les requêtes http 'GET'

### Structure
  +  **main.c**  : la seule fonction de module est de rassembler les autres fonctions et demarrér le serveur.

  + **utils.c** : contient les fonctions générales et réutilisable qui permettent de changer la couleur du texte de sortie et d'obtenir des
  		infos sur un fichier ex: extension.

  + **server.c** :  permet de créer le serveur a traver un socket et de mettre ce même serveur en mode écoute. Le serveur utilisé ici est un serveur 
  	       dynamique avec des threads. Ce serveur permet aussi de suivre en temps réel les connexion au site web et les requêtes effectuées
  	       par les utilisateurs.

  + **http_handler.c** : fournut les fonctions permettant de décoder une requête http mais aussi d'en générer une de façon dynamique et 
  		      automatisée selon la requête du client.

 ## Fonctionnalités
 Une fois le serveur démarré il permettra d'accéder à l'ensembles des fichiers de type HTML ou image qui seront placés dans le dossier
 "temaplates". 
 Pour des raisons de test le serveur possède seulement une page home accésible au lien
 [127.0.0.1:8080/home.html]
 
 ## Limitations
  + Le serveur ne gère que les requêtes 'GET'.
  + Les liens ne sont pas créer de façon intuitive et dynamique: il faudra écrire exactement le nom du fichier 
    HTML qui corréspond à la page.
  + Le serveur n'est pas capable d'aller chercher un fichier HTML dans un dossier, il fauut tout mettre dans templates.

## Licence
[MIT License](LICENSE)
