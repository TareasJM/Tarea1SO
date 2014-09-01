#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
off_t fsize(const char *filename);

int main (int argc, char const *argv[])
{ 
  //Puntero al Directorio
  DIR *dp;
  struct dirent *ep;
  char* name_archive;
  char* format_archive;
  char* des;
  int   size;
  dp = opendir (argv[1]);

  if (dp != NULL)
  {
    while (ep = readdir (dp))
    { 
      //Obtiene el nombre completo del Archivo
      name_archive = ep->d_name;
      size = fsize(name_archive)/8;
      printf("%s = %d bytes \n", name_archive, size);
      //Separa el Nombre del Archivo y el Formato 
      strtok_r(name_archive,".",&format_archive);
      if(format_archive != NULL)
      { 
        //Crea un directorio con el nombre de los formatos
        des = (char*)malloc(strlen(argv[1])+1+4);
        strcpy(des,argv[1]);
        strcat(des,"/");
        strcat(des,format_archive);
        mkdir(des,0777);
        printf("%s\n",format_archive);
      }
    }
    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");

  return 0;
}

off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}