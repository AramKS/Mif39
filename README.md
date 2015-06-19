# Mif39

###A faire coté serveur :
modifier le CMakeLists.txt principal pour spécifier le chemin d'accès vers QT

Copier les descriptions des mime type (les 2 fichiers xml dans le dossier Resources)
* linux : dans le dossier ~/.local/share/mime/packages
* macos : dans le dossier ~/Library/Application Support/mime/packages
* windows : dans le dossier C:/Users/<USER>/AppData/Local/mime/packages

Une fois les mime type copiés :

éxecuter la commande : update-mime-database ~/.local/share/mime

Pour lancer le serveur : simplement lancer l'exécutable GraalAssetServer
Il attendra un message comme décrit ci-dessous.

###Format des messages client :

D'abord un premier message :  type de la requete  
* 0 je demande un Mesh
* 1 j'envoie une coordonnée
* 2 je demande une image

Ensuite un 2eme message : 
* Pour le Mesh : un entier représentant l'ID du Mesh dans l'ordre du resourceHolder (c'est juste pour tester !)
* Pour les coordonnées : "x y z" avec un espace séparant les 3 coordonnées
* Pour l'image : idem que pour le mesh mais ca sert a rien on envoie toujours la même image ! (pour tester aussi !)
