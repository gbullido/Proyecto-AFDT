#include <stdio.h>
#include <stdlib.h>
#define MaxL 50 //Lineas max de fichero.
#define MaxC 25 //Maximos caracteres por linea.

int imprimirMenu();//Donde se elige el apartado a probar.

void borrarConsola();//Despeja la consola.

void aperturaFichero(char fichero[MaxL][MaxC],int opcion);//Saca el AFDT del .txt y lo mete en un array struct.

void vaciar(char temp[]);//Rellena un vector de nulos

enum Boolean//Los boleanos no existen en C tienes que crearlos.
{
	FALSE, TRUE
};

typedef struct
{
     enum Boolean esFinal;
     int numeroEstado;
     char *transiciones;//Guarda las transiciones que salen del estado
     char *traducciones;//Guarda las traducciones respectivas a las transiciones
     int *destinos;//Guarda el destino de cada transicion respectivamente
}AFDT;

AFDT *traductor;


//###################################################################################################################################################
//################################################################################# MAIN ############################################################
//###################################################################################################################################################
int main()
{
    char fichero[MaxL][MaxC];//La matriz fichero es donde se guardaran los automatasb.txt
    borrarConsola();

    aperturaFichero(fichero,imprimirMenu());
    return 0;
}

//##################################################################################################################################################
//################################################################################ FUNCIONES OBLIGATORIAS ##########################################
//##################################################################################################################################################

int imprimirMenu()//######################### IMPRIMIR MENU #################################################################
{
 int opcion;

 printf("\tMENU PRINCIPAL\n\n");
 printf("\t(1) Apartado 'A'\n\n");
 printf("\t(2) Apartado 'B'\n\n");
 printf("\t(3) Apartado 'C'\n\n");
 printf("\t(0) Salir\n\n");//Por si el usuario queria finalizar pero se equivoca y elige volver al menu principal.
 printf("\nElija el apartado que quiera probar mediante '1', '2', '3', o '0' para salir: ");
 scanf("%d",&opcion);
 while(opcion>3 || opcion<0)
  {
   printf("\nHa introducido una opcion que no esta en el menu, porfavor introduzca una viable: ");
   fflush( stdin );
   scanf("%d",&opcion);
  }
return opcion;
}

void borrarConsola()//#### BORRAR CONSOLA #######################################################################################
{
  system("cls");
}

void aperturaFichero(char fichero[MaxL][MaxC],int opcion)//################## APERTURA DE FICHERO ###############################
{
  int i,j,cont=0;//Cuenta el numero de lineas(estados) del .txt
  char aux,temp[50];
  FILE *F;
  switch( opcion )
   {
    case 1: F = fopen ("Apartado1.txt","r");
          break;

    case 2: F = fopen ("Apartado2.txt","r");
          break;

    case 3: F = fopen ("Apartado.txt","r");
          break;

    case 0: exit(0);//Comando para terminar la ejecucion entera del programa
          break;
   }
 if (F==NULL)
  {
    printf("\n\t\tERROR:el fichero no se ha abierto correctamente\n");
    exit (EXIT_FAILURE);
  }
 //el fichero se ha abierto correctamente
 while(!feof(F))
  {
   fgets(temp,50,F);//Lee una linea hasta encontrar'\n' o llegar a 50 en este caso y deja el puntero al inicio de la siguiente
   cont++;//Cada aumento es una linea/estado más.
   //Cada ciclo del while sobreescribe temp añadiendo al final un nulo.
  }
 rewind(F);//Devuelve el puntero F al principio del fichero

 //Como ya conocemos el numero de estados del AFDT,crearemos un vector de ese tamaño justo.
 traductor=(AFDT*)malloc(cont*sizeof(AFDT));
 if(traductor==NULL)//Comprobamos que se reservo la memoria correctamente
  {
    printf("No se ha podido reservar la memoria.\n");
    exit (1);
  }

  for(i=0; !feof(F); i++)
   {
      //Primeros debemos vaciar temp.
      vaciar(temp);
      aux='0';//Ya que no esta inicializada
      for(j=0;aux!='-'&&'*';j++)
       {
           aux=fgetc(F);//Lee letra a letra

       }
   }
}

void vaciar(char temp[])
{
    int i;
    for(i=0;i<0;i++)
     {
        temp[i]='\0';
     }
}

