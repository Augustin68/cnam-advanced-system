# Service "from scratch"

## Récupération des ressources
Récupération de l'image tomcat
``` bash
docker pull tomcat:9
```
Télécharger le .war
``` bash
wget https://get.jenkins.io/war-stable/2.426.2/jenkins.war
``` 

## Rédaction du fichier Dockerfile

Voir [ici](./Dockerfile)

## Construction de l'image
``` bash
docker build -t jenkins-from-scratch .
```

## Test du service

``` bash
docker run --name myjenkins -p 8080:8080 jenkins-from-scratch
```
Le service est maintenant accessible sur `http://localhost:8080/jenkins`

## L’arrêt / supression du conteneur.
``` bash
# arrêt
docker stop myjenkins
# supression
docker rm myjenkins
```