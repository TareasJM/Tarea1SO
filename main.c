#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
int main (int argc, char const *argv[])
{ 
  //Puntero al Directorio
  DIR *dp;
  struct dirent *ep;
  char *name_archive;
  char *format_archive;
  char *des;
 
  dp = opendir (argv[1]);

  if (dp != NULL)
  {
    while (ep = readdir (dp))
    { 
      //Obtiene el nombre completo del Archivo
      name_archive = ep->d_name;
      //Separa el Nombre del Archivo y el Formato 
      strtok_r(name_archive,".",&format_archive);
      if(format_archive != NULL)
      { 
        //Crea un directorio
        des = strcat(des,format_archive);
        mkdir(format_archive,0777);
        printf("%s\n",format_archive);
      }
    }
    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");

  return 0;
}