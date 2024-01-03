# Proposer un service d'infrastructure via conteneur

## 1 - La récupération de l’image networkboot/dhcpd depuis le hub docker
``` bash
docker pull networkboot/dhcpd
```

## 2 - La création du fichier configuration pour le service

Le fichier de configuration dhcp.conf est [ici](./dhcpd.conf) !

## 3 - Le démarrage du conteneur avec les paramètres appropriés
```
docker run --name dhcp_service -v $(pwd):/data -d --network host networkboot/dhcpd
```

## 4 - La vérification de la disponibilité du service
```
docker logs dhcp_service
```

## 5 - L'arrêt du conteneur associé
```
docker stop dhcp_service
```