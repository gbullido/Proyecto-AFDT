#include <stdio.h>
#include <stdlib.h>

int imprimirMenu();//Donde se elige el apartado a probar.

void borrarConsola();//Despeja la consola.

void aperturaFichero(char fichero[MaxL][MaxC],int opcion);//Saca las palabras del .txt y las copia en la matriz fichero.


//###################################################################################################################################################
//################################################################################# MAIN ############################################################
//###################################################################################################################################################
int main()
{
    printf("Hello world!\n");
    return 0;
}

//##################################################################################################################################################
//################################################################################ FUNCIONES OBLIGATORIAS ##########################################
//##################################################################################################################################################

int imprimirMenu()//######################### IMPRIMIR MENU #################################################################
{
 int opcion;

 printf("\tMENU PRINCIPAL\n\n");
 printf("\t(1) Apartado 'a)'\n\n");
 printf("\t(2) Apartado 'b)'\n\n");
 printf("\t(3) Apartado 'c)'\n\n");
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
int i=0;
FILE *F;
switch( opcion )
 {
  case 1: F = fopen ("Apartado1.txt","r");
          break;

  case 2: F = fopen ("Apartado2.txt","r");
          break;

  case 3: F = fopen ("Apartado3.txt","r");
          break;

  case 0: exit(0);//Comando para terminar la ejecucion entera del programa
          break;
 }
if (F==NULL)
 {
    printf("\n\t\tERROR:el fichero no se ha abierto correctamente\n");
    exit(0);
 }
else
 {
  //el fichero se ha abierto correctamente
  fscanf(F,"%s",fichero[i]);
  while(!feof(F))
   {
     i++;
     fscanf(F,"%s",fichero[i]);
   }
  fclose(F);
 }
}
