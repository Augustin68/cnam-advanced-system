# Utilisation de l'image Tomcat en tant que base
FROM tomcat:9

# Copie de l'archive war de Jenkins dans le répertoire webapps de Tomcat
ADD jenkins.war /usr/local/tomcat/webapps/

# Déclaration du port d'écoute 8080
EXPOSE 8080
