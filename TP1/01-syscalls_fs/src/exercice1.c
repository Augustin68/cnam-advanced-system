#include "exercice1.h"

void copyFile(const char* src, const char* dest) {
  FILE* fd_source = fopen(src, "rb");
  if(fd_source == NULL) 
  {
    printf("Impossible d'ouvrir le fichier source.\n");
    exit(EXIT_FAILURE);
  }

  FILE* fd_destination = fopen(dest, "wb");
  if(fd_destination == NULL) 
  {
    printf("Impossible d'ouvrir le fichier de destination.\n");
    exit(EXIT_FAILURE);
  }

  char buffer[BUFFER_SIZE];
  size_t nb_char_read;

  do 
  {
    nb_char_read = fread(buffer, 1, sizeof(buffer), fd_source);

    if(nb_char_read == -1) 
    {
      printf("Erreur ?\n");
      fclose(fd_source);
      fclose(fd_destination);
      exit(EXIT_FAILURE);
    } 

    if(nb_char_read > 0) 
    {
      fwrite(buffer, 1, nb_char_read, fd_destination);
    }
  } while(nb_char_read == BUFFER_SIZE);

  printf("Le fichier %s a bien été copié dans %s.\n", src, dest);
}