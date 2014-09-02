#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

off_t fsize(const char *fileName);

int main (int argc, char const *argv[])
{ 
  //Puntero al Directorio y archivo
  DIR *dp;
  struct dirent *ep;
  //Strings para nombres y extenciones
  char *fileName;
  char *fileExt;
  char dir[255];

  // Verificación de argumentos
  if (argc != 2)
  {
    printf("Usage: ./Tarea1SO <Directory>\n");
    return 0; //Si hay error, termina
  }
  else if (argv[1][strlen(argv[1])-1] != '/')
  {
    strcpy(dir, argv[1]);//->folder/
    strcat(dir, "/");//-> Si el directorio no termina en /, lo agrega
  }
  else
  {
    strcpy(dir, argv[1]);//->folder/
  }

  //Abre el directorio
  dp = opendir(dir);

  if (dp != NULL)
  {
    while (ep = readdir(dp))
    { 
      //Obtiene el nombre completo del Archivo
      fileName=(char *) malloc(sizeof(char)*256);
      strcpy(fileName, ep->d_name);
      //Separa el Nombre del Archivo y el Formato 
      strtok_r(fileName,".",&fileExt);
      if(strcmp(fileName, "") != 0 && strcmp(fileName, "..") != 0 && strcmp(fileName, ".") != 0)
      { 
        if (strcmp(fileExt, "") == 0)
        {
          strcpy(fileExt, "Otros");
        }
        // Crea y prepara Strins con las rutas
        char originalDir[256];
        char finalDir[256];
        strcpy(originalDir, dir);
        strcpy(finalDir, dir);
        strcat(originalDir, ep->d_name);//->folder/fileName (original file path)
        strcat(finalDir,fileExt);//->folder/ext
        
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
        printf("file: %s\n     -name:%s\n     -ext:%s\n     -size:%d\n     -origin:%s\n     -destination:%s\n",ep->d_name, fileName, fileExt, size, originalDir, finalDir);
        if (rename(originalDir, finalDir))
        {
          perror( NULL );
        }
      }
      free(fileName);
    }
    (void) closedir (dp);
  }
  else
    perror ("Directorio Inválido");

  return 0;
}

off_t fsize(const char *fileName)
{
    struct stat st; 

    if (stat(fileName, &st) == 0)
        return st.st_size;

    return -1; 
}