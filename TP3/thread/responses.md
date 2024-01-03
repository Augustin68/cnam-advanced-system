# Résultats

Voici les résultats des temps de recherche du min et du max dans un tableau de 1e8 entiers.

## Version non-threadé

On obtient en moyenne **182 ms**

## Version threadé
On obtient en moyenne :
- 2 threads: **210 ms**
- 4 threads: **222 ms**
- 8 threads: **309 ms**

## Conclusion
Je remarque que la version avec threads n'est visiblement pas plus rapide que la version séquentielle. Cela peut être du à la taille du tableau qui n'est pas suffisement grande pour remarquer une différence sur ce type d'opérations (bien que la taille utilisé ici de 1e8 soit déjà la taille maximale que je puisse utiliser). En effet, les coûts liés à la gestion des threads peuvent dépasser les gains potentiels obtenus.
Cela peut être également dûe à mon implémentation qui n'est pas assez efficace ou qui pourrait être améliorée.