# HTTP-Server 1.0

					HTTP SERVER 1.0


					INSTALLATION ET DÉMARRAGE
  Tout d'abord, il faut se placer dans le dossier où se trouve "run.sh"
  Ensuite il faut entrer la commande "chmod +x run.sh" pour accorder l'autorisation d'exécution au fichier "run.sh"
  Puis exécuter "./run.sh" script en bash script
  Cela compile le programme et envoie les fichiers dans le dossier programme puis exécute le programme.

					Présentation
  Le but du projet est de créer un serveur http accessible par tous les utilisateurs du meme réseau.
  L'utilisateur hôte aura le droit de personnaliser son propre site web en ajoutant les fichier HTML nécessaires dans le
  dossier "templates".
  Pour rendre le site disponible il faut tour d'abord vérifier que la port 8080 est bien ouvert sur la machine hôte, les 
  utilisateurs auront accès au site via l'addresse IP publique ou privée de la machine.
# Attention : le serveur ne prend en compte que les requêtes http 'GET'
# RQ : le serveur donne aussi la possibilité d'afficher une image.

					Structure
  Afin de faciliter le travail en équipe et la lisibilité du projet, l'ensemble du code a été divisé en plusieurs modules.

  +  "main.c"  : la seule fonction de module est de rassembler les autres fonctions et demarrér le serveur.

  + "utils.c" : contient les fonctions générales et réutilisable qui permettent de changer la couleur du texte de sortie et d'obtenir des
  		infos sur un fichier ex: extension.

  + "server.c" :  permet de créer le serveur a traver un socket et de mettre ce même serveur en mode écoute. Le serveur utilisé ici est un serveur 
  	       dynamique avec des threads. Ce serveur permet aussi de suivre en temps réel les connexion au site web et les requêtes effectuées
  	       par les utilisateurs.

  + "http_handler.c" : fournut les fonctions permettant de décoder une requête http mais aussi d'en générer une de façon dynamique et 
  		      automatisée selon la requête du client.	

					Limitations
  + Le serveur ne gère que les requêtes 'GET'.
  + Les liens ne sont pas créer de façon intuitive et dynamique: il faudra écrire exactement le nom du fichier 
    HTML qui corréspond à la page.
  + Le serveur n'est pas capable d'aller chercher un fichier HTML dans un dossier, il fauut tout mettre dans templates.
