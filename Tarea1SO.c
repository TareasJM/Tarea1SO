#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

off_t fsize(const char *filename);

int main (int argc, char const *argv[])
{ 
  //Puntero al Directorio
  DIR *dp;
  struct dirent *ep;
  char *name_archive;
  char *format_archive;
  char dir[255];
  strcpy(dir, argv[1]);
  printf("%c\n", dir[strlen(argv[1])-1]);

  // Verificación de argumentos
  if (argc != 2)
  {
    printf("Usage: ./main <Directory>\n");
    return 0; //Si hay error, termina
  }
  else if (dir[strlen(argv[1])-1] != '/')
  {
    strcat(dir, "/");
  }
  dp = opendir(dir);

  if (dp != NULL)
  {
    while (ep = readdir(dp))
    { 
      //Obtiene el nombre completo del Archivo
      name_archive=(char *) malloc(sizeof(char)*256);
      strcpy(name_archive, ep->d_name);
      //Separa el Nombre del Archivo y el Formato 
      strtok_r(name_archive,".",&format_archive);
      if(strcmp(format_archive, ""))
      { 
        // Crea y prepara Strins con las rutas
        char originalDir[256];
        char finalDir[256];
        strcpy(originalDir, dir);
        strcpy(finalDir, dir);
        strcat(originalDir, ep->d_name);//->folder/filename (original file path)
        strcat(finalDir,format_archive);//->folder/ext
        
        // crea folder/ext
        mkdir(finalDir,0777);
        
        //Obtiene los bits/8 => bytes del archivo
        int size = fsize(originalDir)/8;

        // Agrega el nombre de la carpeta segun peso
        if (size < 1024*100)
        {
          strcat(finalDir,"/-100KB/");
        }
        else if (size < 1024*1024)
        {
          strcat(finalDir,"/100KB-1MB/");
        }
        else if (size < 1024*1024*100)
        {
          strcat(finalDir,"/1MB-100MB/");
        }
        else if (size < 1024*1024*1024)
        {
          strcat(finalDir,"/100MB-1GB/");
        }
        else
        {
          strcpy(finalDir,"/+1GB/");
        }//->folder/ext/sizefolder

        //Crea folder/ext/size
        mkdir(finalDir,0777);

        //Agrega el nombre del archivo al directorio final 
        strcat(finalDir, ep->d_name);//->folder/ext/sizefolder/filname

        // Imprime en consola datos
        printf("file :%s\n    -origin:%s\n    -destination:%s\n    -size:%d\n",ep->d_name, originalDir, finalDir, size);
        // if (rename(originalDir, finalDir))
        // {
        //   perror( NULL );
        // }
      }
      free(name_archive);
    }
    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");

  return 0;
}

off_t fsize(const char *filename)
{
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}