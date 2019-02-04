# GMv5
Le gestionnaire de messages est un outil permettant de mémoriser, durant toute l'exécution du
programme, un certain nombre de messages. Chaque message peut être de longueur quelconque.
Le nombre de messages que l'on peut stocker est illimité. A tout moment, l'utilisateur doit
pouvoir demander l'affichage de tous les messages mémorisés.

Pour l'affichage, l'utilisateur doit être pouvoir demander l'affichage de tous les messages ou de
seulement ceux qui n'ont pas encore été affichés.

Dans cette ultime version du gestionnaire de messages, l'utilisateur doit pouvoir utiliser plusieurs
gestionnaires de messages.

Le gestionnaire de message va prendre la forme d'un tableau de structures alloués de manière
dynamique. Il se composera d'un certain nombre de blocs ; chaque bloc pouvant contenir un
nombre égal de messages. La taille du bloc est fixée par le programmeur. Lorsque le gestionnaire
devient trop petit, alors, on lui ajoute un nouveau bloc de messages.

Chaque message reçu ne pourra en aucun cas être mémorisé tel quel ; il va falloir réallouer
dynamiquement de la place pour le message et l'y recopier. C'est l'adresse de ce nouveau message
dynamique qui sera copié dans le tableau de pointeurs.
