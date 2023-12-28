# Proposer un service
Le but de cet exercice est de mettre en œuvre un conteneur docker proposant un service Jenkins.

## La récupération de l’image jenkins depuis le hub docker
``` bash
docker pull jenkins/jenkins
```

## Le démarrage du conteneur proposant le service.
``` bash
docker run -p 8080:8080 -p 50000:50000 --name jenkins-container -d jenkins
```

## La vérification de la disponibilité du service.
Vérification des logs et récupération de mot de passe pour l'initialisation de jenkins
``` bash
docker logs jenkins-container
```

Tenter d'accéder au service sur localhost:8080

## L’arrêt / supression du conteneur associé.
``` bash
# arrêt
docker stop jenkins-container
# supression
docker rm jenkins-container
```