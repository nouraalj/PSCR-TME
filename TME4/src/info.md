# Réponses des questions du TME4

### Q2 : 

Oui pas de data race car on a bien protégé l'emplacement mémoire de la variable **solde** pour que les threads n'essaient pas d'écrire en même temps.

### Q5 :

On lock les threads des comptes débiteurs et créditeurs, pour ne pas avoir un thread qui viendrait changer le solde  du débiteur après la condition. Puis ces mêmes threads (/comptes) essaient d'appeler des fonctions sur leur compte. Les threads sont alors bloqué sur leur propre verrou. Il faut permettre la réacquisition d'un verrou par le même thread.

### Q6 :

Dead-lock ou interblocage des threads. Pour empêcher cela, on impose un ordre d'acquisition des verrous avec l'ordre croissant des indices de comptes.

### Q7 :

