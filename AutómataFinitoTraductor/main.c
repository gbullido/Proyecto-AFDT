#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int imprimirMenu();//Donde se elige el apartado a probar.

void borrarConsola();//Despeja la consola.

void aperturaFichero(int opcion);//Saca el AFDT del .txt y lo mete en un array struct.

void vaciar(char temp[]);//Rellena un vector de nulos

void asignarMemoriaTransTraduDest(int n,int i);//Asignar el tamaño a los diferentes vectores dinamicos del struct AFDT, tras saber el numero de transiciones.

void rellenarVectores(char temp[],int i,int n);//rellena los vectores dinamicos con la informacion pertinente

enum Boolean//Los boleanos no existen en C tienes que crearlos.
{
	FALSE, TRUE
};

typedef struct
{
    char *traduccion;//cadena de caracteres con la traduccion
}traducciones;

typedef struct
{
     int numeroEstadosAFDT;
     enum Boolean esFinal;
     int nombreEstado;
     char *transiciones;//Guarda las transiciones que salen del estado
     traducciones *cad;//Guarda las traducciones respectivas a las transiciones
     int *destinos;//Guarda el destino de cada transicion respectivamente
}AFDT;

AFDT *traductor;//Vector dinamico de tipo AFDT cada posicion es un estado


//###################################################################################################################################################
//################################################################################# MAIN ############################################################
//###################################################################################################################################################
int main()
{
    borrarConsola();
    aperturaFichero(imprimirMenu());
    printf("---%d-----",traductor[0].numeroEstadosAFDT);
    //free(traductor);//liberamos memoria para ya que se ha elegido un automata diferente

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

void aperturaFichero(int opcion)//################## APERTURA DE FICHERO ###############################
{
  int i,j,n,cont=0;//Cuenta el numero de lineas(estados) del .txt
  char aux[1],temp[50];
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

 //Como ya conocemos el numero de estados del AFDT,asignamos al vector traductor el tamaño justo.
 traductor=(AFDT*)malloc(cont*sizeof(AFDT));
 traductor[0].numeroEstadosAFDT=cont;
 printf("---%d-----",traductor[0].numeroEstadosAFDT);//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 if(traductor==NULL)//Comprobamos que se reservo la memoria correctamente
  {
    printf("No se ha podido reservar la memoria.\n");
    exit (1);
  }
 for(i=0; !feof(F); i++)
   {
       printf("\n\n++0++%d++0++\n\n",i);
      vaciar(temp);//Primeros debemos vaciar temp.
      vaciar(aux);
      traductor[i].nombreEstado=i;
      printf("\n\n++1++%d++1++\n\n",i);
      aux[0]=fgetc(F);//Leemos el primer caracter de una linea y el cursor se queda tras ella, en este caso nos indica si esta linea/estado es final o no.
      if(aux[0]=='n') traductor[i].esFinal=FALSE;
      else if(aux[0]=='f') traductor[i].esFinal=TRUE;
      aux[0]=fgetc(F);//Leemos el segundo caracter de una linea y el cursor se queda tras ella, en este caso nos indica si esta linea/estado tiene transiciones o no.
       printf("\n\n++2++%d++2++\n\n",i);
      if(aux[0]=='-')//Esta linea/estado si tiene transiciones.
       {
           printf("\n\n++3++%d++3++\n\n",i);
         aux[0]=fgetc(F);//Leemos el tercer caracter de una linea y el cursor se queda tras ella, en este caso nos indica cuantas transiciones tiene esta linea estado.
         for(j=0;aux[0]>='0'&&aux[0]<='9';j++)//Ya que pueden existir mas de 9 transiciones
          {
             temp[j]=aux[0];
             aux[0]=fgetc(F);//Lee siguiente caracter
          }
           printf("\n\n++4++%d++4++\n\n",i);
          n=atoi(temp);
          asignarMemoriaTransTraduDest(n,i);//Como ya sabemos el numero de transiciones de esta linea/estado (mediante atoi que pasa '123'char a 123 int ya podemos asignar el tamaño a los diferentes vectores dinamicos.
          //Tras salir del for tenemos en aux el simbolo de la primera transicion, de esta linea/estado.
          vaciar(temp);//reseteamos temp.
          fgets(temp,50,F);//Lee toda la linea y deja el cursor al inicio de la siguiente o EOF
          strcat(aux,temp);
          rellenarVectores(aux,i,n);
           printf("\n\n++5++%d++5++\n\n",i);
          if(feof(F)) printf("\n\nSE CUMPLE CON i = %d\n\n",i);
          else  printf("\n\nNO SE CUMPLE CON i = %d\n\n",i);
       }
      else if(aux[0]=='*')//Esta linea estado no tiene transiciones
       {
            asignarMemoriaTransTraduDest(0,i);
            printf("\n\n dentro if *:%d-----",traductor[0].numeroEstadosAFDT);//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
       }
     printf("\n\n dentro for linea 153 :%d-----",traductor[0].numeroEstadosAFDT);//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
   }
 printf("\n\n ANTES del fclose:%d-----",traductor[0].numeroEstadosAFDT);//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 fclose(F);
  printf("\n\ndespues de fclose:%d-----",traductor[0].numeroEstadosAFDT);//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
}

void vaciar(char c[])
{
    int i;
    for(i=0;i<0;i++)
     {
        c[i]='\0';
     }
}

void asignarMemoriaTransTraduDest(int n,int i)
{
    traductor[i].transiciones = (char*)malloc(n*sizeof(char));
    if(traductor[i].transiciones==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria.\n");
        exit (1);
     }
    traductor[i].cad = (traducciones*)malloc(n*sizeof(traducciones));
    if(traductor[i].cad==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria.\n");
        exit (1);
     }
    traductor[i].destinos = (int*)malloc(n*sizeof(int));
    if(traductor[i].destinos==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria.\n");
        exit (1);
     }
}

void rellenarVectores(char temp[],int i,int n)
{
 int j,k,m,t=0;
 char numTraduccion[3];//Para guardar el numero de simbolos de una traduccion para depues transformarlo a int, y lo mismo para el caacter destino.
 for(j=0;j<n;j++)//for de numero de transiciones del estado 'i'
  {
        for(k=0;temp[k]!=','&&'\0';k++)//for para recorrer una de las 'n' transiciones de temp que empieza con '/', por lo que empezamos por la siguiente posicion que sera '!' o el numero de simbolos de traduccion
         {
            traductor[i].transiciones[j]=temp[k];//metemos el simbolo de la transicion
            if(temp[k]=='!') traductor[i].cad[j].traduccion = (char*)malloc(0*sizeof(char));//Asignamos cero memoria ya que no hay traduccion para esta transicion
            else if(temp[k]!='!'&&temp[k]!='/')//La transicion si tiene traduccion, temp[k] tiene el primer simbolo del numero de simbolos de la traduccion
             {
                vaciar(numTraduccion);
                for(m=k;temp[m]>='0'&&temp[m]<='9';m++)//Ya que pueden existir mas de 9 simbolos de traduccion
                 {
                   numTraduccion[t]=temp[m];
                   t++;
                 }
                t=0;
                traductor[i].cad[j].traduccion = (char*)malloc(atoi(numTraduccion)*sizeof(char));//Asignamos memoria ya que sabemos el numero de simbolos de traduccion para esta transicion
                //Ahora temp[m] esta en la posicion centinela '.', es decir lo proximo es analizar la traduccion, actualizamos el indice 'k' para pasar al primer simbolo de traduccion.
                for(k=m+1;temp[k]!=':';k++)
                 {
                     traductor[i].cad[j].traduccion[t]=temp[k];
                     t++;
                 }
                t=0;
                //Ahora temp[k], esta en ':', tenemos que leer el destino que esta en k+1 y guardarlo en el struct, actualizamos k.
                vaciar(numTraduccion);
                k++;
                numTraduccion[0]=temp[k];
                traductor[i].destinos[j]=atoi(numTraduccion);
                //Ahora temp[k] esta en la posicion ANTES de ',' o '\0'; dejamos 'k' asi ya que tras llegar a '}' el contador del for hara 'k++', y ya no se cumplira la condicion y saldra del for.
             }
         }
        //Ahora temp[k] esta en la posicion de ',' o '\0'; si hay otra transicion ya que 'n'>1 queremos que temp[k] sea la posicion del simbolo de la siguiente transicion para que el for de 'k' se complete con normalidad.
        k++;
  }
}


