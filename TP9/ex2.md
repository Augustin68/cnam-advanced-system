# Proposer une stack applicative Wordpress

## La récupération des images depuis le hub docker

Je vais sur la [page des tags](https://hub.docker.com/_/wordpress/tags) de l'image wordpress, puis je prend la dernière afin d'éviter d'utiliser le tag "latest". Pareil pour [mysql](https://hub.docker.com/_/mysql).



## La création du fichier de configuration docker-compose pour le service

Voir le fichier [docker-compose.yml](./docker-compose.yml)

## Le démarrage de la stack

```
docker-compose up -d
```

## La vérification de la disponibilité du service

Je peux accéder au service en allant sur `localhost:8080`

Je peux utiliser docker-compose ps pour voir la liste des container et leurs status.

## L'arrêt du conteneur associé

``` bash
# Stop le service
docker-compose down

# Stop le service et supprime les volumes
docker-compose down -v
```