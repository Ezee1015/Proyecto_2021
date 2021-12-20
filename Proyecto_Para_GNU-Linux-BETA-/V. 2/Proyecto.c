/*****
*   PROYECTO DE LABORATORIO
*   MATERIA: Laboratorio de Aloritmos y Estructuras de Datos
*   ALUMNOS: Lautaro - Ezee1015
*   CURSO: 4º Computacion
*   AÑO: 2021
*****/

///se llaman las librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///se declaran variables y se les asigna 0 para que no tengan valor basura
int Cantidad_Pelis=0;
int Precio_Total_Carrito=0;

///se crea el struct donde entran los datos del archivo
struct Peliculas {
  char ID[100];
  char Nombre[100];
  char Actor[100];
  char Director[100];
  char Pais[100];
  char Fecha[100];
  char Genero[100];
  char Recaudacion[100];
  char Empresa[100];
  char Precio[100];
} Pelicula[100];

///se declara la variable y su capacidad
int Peliculas_Carrito[100];

int Menu_Proyecto ();
int Listar_Peliculas (int );
void Escribir () ;
int Editor_Peliculas() ;
void Listar_Carrito();
int Carrito() ;
int Salir_Menu() ;
void Limpiar_Carrito () ;
void Ir_A_Linea(FILE *, int );
int Cargar_Archivo_en_Struct ();
int Agregar_Pelicula ();
int Eliminar_Pelicula ();
int Carrito_Terminado();
int Login_Manager(int *);


///se crea una funcion que permite limpiar la pantalla salteando lineas
void Limpiar_Pantalla() { printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); }

///se crea el menu principal con printf y getch
int Menu_Proyecto () {
  int Eleccion;
  Limpiar_Pantalla();
  printf("                             MENU PRINCIPAL\n");
  printf("********************************************************************\n");
  printf("    1.- Listado de los Nombres de las Peliculas Disponibles\n");
  printf("    2.- Editar Cantidad de las Peliculas (ADMINISTRATIVO)\n");
  printf("    3.- Entrar al Carrito\n");
  printf("    4.- Salir y Deshacer Compra (Borrar Carrito)\n");
  printf("********************************************************************\n\n");
  printf(" Ingrese su eleccion>  ");
  fflush(stdin);
  Eleccion=getchar();
  fflush(stdin);

///este switch lleva al usuario a las distintas opciones
  switch (Eleccion) {
    case '1' :
      Limpiar_Pantalla();
      Listar_Peliculas(1);
      Menu_Proyecto();
      return 0;
      break;
    case '2' :
      Limpiar_Pantalla();
      Editor_Peliculas();
      break;
    case '3' :
      Carrito();
    break;
    case '4' :
      Limpiar_Pantalla ();
      Salir_Menu();
    break;
    case 27:
        Salir_Menu();
    break;
    default :
      Limpiar_Pantalla();
       printf("\n\n        ERROR. INGRESE DE VUELTA LA OPCION A ELEGIR.\n                   LA OPCION NO EXISTE\n\n\n\n\n\n\n\n\n");
      getc(stdin);
      Limpiar_Pantalla();
      Menu_Proyecto();
      return 0;
    break;
  }
}

///se crea una funcion que muestre todas las peliculas y los campos del struct
int Listar_Peliculas (int Limitar_en_Pantalla) {
  char Texto[9999];
  int i;
  int Peliculas_en_Pantalla=5; // CAMBIA EL VLOR PARA CAMBIAR LA CANTIDAD DE REGISTROS EN PANTALLA
  printf("Peliculas Disponibles...\n\n\n");

///este for sirve para que se muestren todas las peliculas
  for(i=1; i<Cantidad_Pelis ; i++){
    printf("   %s - %s\n\n", Pelicula[i].ID, Pelicula[i].Nombre);
    printf("      ACTOR: %s\n",Pelicula[i].Actor);
    printf("      DIRECTOR: %s\n",Pelicula[i].Director);
    printf("      FECHA ESTRENO: %s\n",Pelicula[i].Fecha);
    printf("      GENERO: %s\n",Pelicula[i].Genero);
    //printf("      EMPRESA: %s\n",Pelicula[i].Empresa);
    printf("      PRECIO: %s\n",Pelicula[i].Precio);
    printf("---------------\n\n");
    if (Limitar_en_Pantalla==1) { if((i%Peliculas_en_Pantalla)==0) { printf("\nPresione una Tecla para Continuar ... \n\n");fflush(stdin); getchar(); } }

  }
    return 0;
}

///se crea una funcion que abre el archivo en modo escribir  e imprime todo el struct en el archivo
void Escribir () {
  int i;
  FILE* Archivo=fopen("Peliculas.txt", "w");
  for(i=0;i<Cantidad_Pelis;i++) {
    //printf("ANTES: %i - %s\n", i, Pelicula[i].ID);
    fprintf(Archivo,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", Pelicula[i].ID, Pelicula[i].Nombre, Pelicula[i].Actor, Pelicula[i].Director, Pelicula[i].Pais, Pelicula[i].Fecha, Pelicula[i].Genero, Pelicula[i].Recaudacion, Pelicula[i].Empresa, Pelicula[i].Precio);
    if((i+1)!=Cantidad_Pelis) { fprintf(Archivo,"\n"); } ///si no es el ultimo registro agrega un salto de linea. Asi se evita error con el strtok
  }
  fclose(Archivo);
}

///se crea una funcion que permite editar los campos de las peliculas del archivo
int Editor_Peliculas() {
  int Entrada=0;
  Login_Manager(&Entrada);
    if (Entrada==1){
    char Nuevo_Campo[100];
    int opcion_campo, opcion_registro;
    Listar_Peliculas(0);
    printf("Que Registro desea modificar? (del 1 al %i o 0 para Salir) > ", Cantidad_Pelis-1);
    scanf("%i", &opcion_registro);

///si se ingresa un 0 se vuelve al menu
    if (opcion_registro==0) { Menu_Proyecto(); return 0; }

///si se ingresa un numero de registro que no existe, avisa y se vuelve al menu
    if((opcion_registro)>=Cantidad_Pelis || opcion_registro<0){
      printf("\n   La Pelicula seleccionada no existe...\n\n");
      fflush(stdin);
      getchar();
      Limpiar_Pantalla();
      Menu_Proyecto();
      return 0;
    }

///aparecen los distintos campos a modificar y se deja al usuario elegir
    Limpiar_Pantalla();
    printf("0.Salir\n\n1.ID_Pelicula\n2.Nombre_Pelicula\n3.Actor_Actriz\n4.Director\n5.Pais_de_Origen\n6.Fecha_de_Lanzamiento\n7.Genero\n8.Recaudacion\n9.Empresa\n10.Precio\n\n  Que campo desea editar?>  ");
    scanf("%i", &opcion_campo);
    if (opcion_campo==0) { Menu_Proyecto(); return 0; }///si se ingresa 0 se vuelve al menu

    Limpiar_Pantalla();

///se muestran valores clave de las peliculas
      printf(" %s   %s                   Campo a Modificar\n", Pelicula[0].ID, Pelicula[0].Nombre);
      printf("     %s           %s                      ", Pelicula[opcion_registro].ID, Pelicula[opcion_registro].Nombre);

///este switch imprime el campo a modificar
  switch (opcion_campo){
    case 1:
      printf("%s\n",Pelicula[opcion_registro]. ID);
    break;
    case 2:
      printf("%s\n",Pelicula[opcion_registro]. Nombre);
    break;
    case 3:
      printf("%s\n",Pelicula[opcion_registro]. Actor);
    break;
    case 4:
      printf("%s\n",Pelicula[opcion_registro]. Director);
    break;
    case 5:
      printf("%s\n",Pelicula[opcion_registro]. Pais);
    break;
    case 6:
      printf("%s\n",Pelicula[opcion_registro]. Fecha);
    break;
    case 7:
      printf("%s\n",Pelicula[opcion_registro]. Genero);
    break;
    case 8:
      printf("%s\n",Pelicula[opcion_registro]. Recaudacion);
    break;
    case 9:
      printf("%s\n",Pelicula[opcion_registro]. Empresa);
    break;
    case 10:
      printf("%s\n",Pelicula[opcion_registro]. Precio);
    break;
  }

///se permite al usuario ingresar el valor con el que reemplazar el campo seleccionado
    printf("\nCon que desea reemplazar ese campo? >  ");
    fflush(stdin);
    /* gets(Nuevo_Campo); */
    scanf("%s", &Nuevo_Campo);
  //AHORA HAY QUE PONER UN SWITCH QUE GUARDE EL NUEVO CONTENIDO EN EL CAMPO DESEADO Y EN EL REGISTRO PEDIDO



  //ACA HAY QUE LLAMAR  LA FUNCION ESCRIBIR PARA QUE SOBREESCRIBA TODO, SI, TODO EL ARCHIVO CON LO QUE YA TIENE CARGADO EN EL STRUCT


///este switch es el que reemplaza el campo actual por el valor ingresado por el usuario en el struct
    switch (opcion_campo) {
      case 1 :
      strcpy(Pelicula[opcion_registro].ID,Nuevo_Campo);
      break;

      case 2 :
      strcpy(Pelicula[opcion_registro].Nombre,Nuevo_Campo);
      break;

      case 3 :
      strcpy(Pelicula[opcion_registro].Actor,Nuevo_Campo);
      break;

      case 4 :
      strcpy(Pelicula[opcion_registro].Director,Nuevo_Campo);
      break;

      case 5 :
      strcpy(Pelicula[opcion_registro].Pais,Nuevo_Campo);
      break;

      case 6 :
      strcpy(Pelicula[opcion_registro].Fecha,Nuevo_Campo);
      break;

      case 7 :
      strcpy(Pelicula[opcion_registro].Genero,Nuevo_Campo);
      break;

      case 8 :
      strcpy(Pelicula[opcion_registro].Recaudacion,Nuevo_Campo);
      break;

      case 9 :
      strcpy(Pelicula[opcion_registro].Empresa,Nuevo_Campo);
      break;
      case 10:
      strcpy(Pelicula[opcion_registro].Precio,Nuevo_Campo);
      break;
    }
    //printf("%s  %s  %s  %s  %s  %s  %s  %s  %s",Pelicula[2].Actor,Pelicula[2].Director, Pelicula[2].Empresa, Pelicula[2].Fecha, Pelicula[2].Genero, Pelicula[2].ID, Pelicula[2].Nombre , Pelicula[2].Pais, Pelicula[2].Recaudacion);

    ///se llama a reescribir el archivo y se vuelve al menu
    Escribir();
    Menu_Proyecto();
    return 0;
  }
}

///se crea una funcion para mostrar los articulos del carrito
void Listar_Carrito() {
  int x;
  int SWAP;
  Precio_Total_Carrito=0;
  printf("Peliculas en el Carrito...\n\n");
  for (x=0;x<100;x++) {///este for hace que el if de abajo se repita hasta que ya no haya mas peliculas
    if (Peliculas_Carrito[x] == 1) {///solo se muestran las peliculas que tienen un "1" osea que estan en el carrito

///se muestran datos clave de cada pelicula del carrito
      printf("   %s     %s                      $%s\n\n", Pelicula[x].ID, Pelicula[x].Nombre, Pelicula[x].Precio);
      SWAP=atoi(Pelicula[x].Precio);
      Precio_Total_Carrito=Precio_Total_Carrito+SWAP;///se hace la cuenta del precio total

    }
  }
}

///se muestra el menu del carrito
int Carrito() {
  char Eleccion;
  Limpiar_Pantalla();
  printf("                           CARRITO DE COMPRAS\n");
  printf("********************************************************************\n");
  printf("    1.- LISTAR el Carrito\n");
  printf("    2.- AGREGAR al Carrito\n");
  printf("    3.- ELIMINAR del Carrito\n");
  printf("    4.- LIMPIAR el Carrito\n");
  printf("    5.- TERMINAR Compra (Comprar)\n");
  printf("    6.- Volver al Menu\n");
  printf("********************************************************************\n\n");
  printf(" Ingrese su eleccion>  ");

  ///se ingresa la eleccion
  fflush(stdin);
  Eleccion=getchar();
  fflush(stdin);

  ///en este switch se ingresa que hace cada eleccion
  switch (Eleccion) {
    case '1' :
      Limpiar_Pantalla();
      Listar_Carrito();
      printf("\nPresione una Tecla para Continuar ... ");
      getchar();
      Carrito();
      break;
    case '2' :
      Limpiar_Pantalla();
      Agregar_Pelicula();
      break;
    case '3' :
      Limpiar_Pantalla ();
      Eliminar_Pelicula();
    break;
    case '4' :
        Limpiar_Pantalla();
        Limpiar_Carrito();
        return 0;
    break;
    case '5' :
      Limpiar_Pantalla ();
      Carrito_Terminado();
    break;
    case '6' :
      Limpiar_Pantalla ();
      Menu_Proyecto();
      return 0;
    break;
    case 'p' :
      Limpiar_Pantalla ();
      printf("EASTER EGG\n\n");
      printf("------------Oooo---\n");
      printf("-----------(----)---\n");
      printf("------------)--/----\n");
      printf("------------(_/-\n");
      printf("----oooO----\n");
      printf("----(---)----\n");
      printf("-----(--(--\n");
      printf("------(_)-\n");
      printf("------------Oooo---\n");
      printf("-----------(----)---\n");
      printf("------------)--/----\n");
      printf("------------(_/-\n");
      printf("----oooO----\n");
      printf("----(---)----\n");
      printf("-----(--(--\n");
      printf("------(_)-\n");
      fflush(stdin);
      getchar();
      Carrito();
    break;
    case 'l' :
        Limpiar_Pantalla();
        printf("EASTER EGG\n\n");
        printf("                 c0d.                                      'x0c.\n");
        printf("             .:xKOoxKOo;.                              .;o0KxlOKkc.\n");
        printf("         .;o0Kd;. 'c;,cd0Kkoc,..                ..,cdOKOd:,;c' .;dK0o;.\n");
        printf("      'lOKkc. 'cxKOdOXkl;,,;ldk0K0OkxdoooodxkOKK0kdl;,,;oOKOokXkc' .ckXOl'\n");
        printf("  .:xKOo' .:dK0o;.    'cdOK0xoc;;;,;,,,;;,,,,,;;:cdk0KOo:'     ,o0Kd:. 'lOKx:.\n");
        printf(":0Xx;..;dKKd:.             .';coxkOKKK0OOKKK0Okdoc;'.             .:dKKd:..;xN0c\n");
        printf(" lXk..dXX;                            ....                            :KXd..OXc\n");
        printf("  .xXd..kXd.                                                        .kNx..dXd.\n");
        printf("    ,OK; lNk                                                        kN: ;XO'\n");
        printf("     :Nl cNd                       INSTITUTO                        dN; lN:\n");
        printf("     lN: dNl                                                        lNo :Nl\n");
        printf("     dN, kN;       _            ____        _      _   _            ;Nx ,Nd\n");
        printf("     ON. 0N'      | |    __ _  / ___|  __ _| | ___| |_| |_ ___      'N0 .NO\n");
        printf("     KX .NX.      | |   / _` | (___ ( / _` | |/ _ ) __| __/ _ )     .XN. KK\n");
        printf("    .XO 'N0       | |__| (_| |  ___) | (_| | |  __/ |_| ||  __/      0N' OX.\n");
        printf("    'Nd ;Nk       |_____(__,_| |____/ (__,_|_|(___|(__|(__(___|      kN; dN'\n");
        printf("    :Nl cNl                                                          dNl lN:\n");
        printf("    lN: dN:                 .;                                       cNd :Nl\n");
        printf("    xN, kN'                cl                                        ;Nk ,Nd\n");
        printf("    ON. KX.               c:   ,;                                    'NK .NO\n");
        printf("    KK .NO                k   'lo.                                   .XN. KK\n");
        printf("   .XO 'Nx               .x  'lkkc,                                   0N' OX.\n");
        printf("   'Nd ;No                d, .lXXl.          ;odxxxdo;                xN; dN'\n");
        printf("   :Nl cN:                 ;lllddl;        oKO:.    ,kd               lNc lN:\n");
        printf("   lN: dN,                 .0XXXKKKKK000OOOOkxxdddo. l0.              ;Nd :Nl\n");
        printf("   xN, kN.                   cOK00000OOOkkkxdxddo;  'Ol               'Nk ,Nx\n");
        printf("   ON. 0X.                     :0WWWWWWNXKK0OOkoccldd,                .X0 .NO\n");
        printf("   KK .N0                        ,kOOOOkxxxxxd, ...                    ON. KK\n");
        printf("  .XO 'Nx                        'XNNNNXK00OOk.                        xN' ON.\n");
        printf("  ,Nd ,No                         ............                         oN; dN,\n");
        printf("  :Nl cNc                                                              cNc lN:\n");
        printf("  lNc cN:                                                              :Nc cNl\n");
        printf("  cNl ;Nk.                            A-479                           .kX, lNc\n");
        printf("  .KK. ,xXOdl:;'..                                            ..';clx0Kx' .KK.\n");
        printf("   .OKl.  .,:ldxkOKK0Okxdol:;,..                ..,;clodxO0KKKOkxoc:,.  .lKO.\n");
        printf("     ,dOK0kxoc:,'......',;:lodkKKko,       .;okK0kdoc:;,'......';:ldxO0KOo,\n");
        printf("         ..';cldxk0KK0Oxdoc:,.. .'ckXk:..:kXkc'  ..,:lodkOKKKOkxol:;'..\n");
        printf("                     ..',;cldOKKkl, .;xXXx;..,lkKKkdlc;,...\n");
        printf("                               .,ckXx:.  .:kXkc'.\n");
        printf("                                   .:xXkkXx;.\n");
        printf("                                      .kx.\n");
        fflush(stdin);
        getchar();
        Carrito();
    break;
    case 27:
      Limpiar_Pantalla();
      Menu_Proyecto();
    break;
    default :
      Limpiar_Pantalla();
       printf("\n\n        ERROR. INGRESE DE VUELTA LA OPCION A ELEGIR.\n                   LA OPCION NO EXISTE\n\n\n\n\n\n\n\n\n");
       getc(stdin);
      Carrito();
    break;
  }

return 0;
}


///se crea una funcion para salir del menu
int Salir_Menu() {
  int Borrar_Carrito=0, x;
  char Eleccion;

///se fija si hay peliculas en el carrito
  for(x=0 ; x < Cantidad_Pelis ; x++) {
    if (Peliculas_Carrito[x] == 1) { Borrar_Carrito=1; x=100; }
  }

  ///este if es el que se concretamente de salir del programa
  if(Borrar_Carrito==1) {
    char Elecciones;
    Limpiar_Pantalla();
    printf("    SE BORRARA EL CONTENIDO DEL CARRITO! \n\n ");
    printf("Esta seguro que quiere salir? (S/N) >  ");
    fflush(stdin);
    Eleccion=getchar(); // scanf(" %c", &Elecciones);
    if (Eleccion=='s' || Eleccion=='S' || Eleccion=='1' || Eleccion==13) return 0; else { Menu_Proyecto(); return 0; }
  }
}

///esta funcion limpia el carrito
void Limpiar_Carrito () {
    int x;
    char Eleccion;

    Limpiar_Pantalla();

    printf("\n\nDesea Borrar el Carrito? (S/N) > ");
    fflush(stdin);
    Eleccion=getchar();

///este les coloca un 0 a las peliculas del carrito para hacer que ya no aparezcan
    if(Eleccion=='S' || Eleccion=='s' || Eleccion=='1' || Eleccion==13) {
        for(x=0;x<100;x++){
            Peliculas_Carrito[x]=0;
        }
    }
    Carrito();
    return;
}

///esta funcion se coloca en cierta linea del archivo
void Ir_A_Linea(FILE *Archivo, int Registro) {
  int i;
  for(i=0;i<Registro;i++){
    fgets(NULL,9999,Archivo);
  }
}

///esta funcion separa los campos y los ingresa en el struct del registro ingresado
void Extrae_Campos (char Texto[999], int Registro) { //TEXTO ES LA LINEA EN LAS QUE SE VA SEPARAR LOS CAMPOS

  strcpy(Pelicula[Registro].ID,strtok(Texto,"\t\n"));
  //printf("\nID: %s del registro %i",Pelicula[Registro].ID, Registro);
  strcpy(Pelicula[Registro].Nombre,strtok(NULL,"\t\n"));
  //printf("\nLeo Nombre: %s", Pelicula[Registro].Nombre);
  strcpy(Pelicula[Registro].Actor,strtok(NULL,"\t\n"));
  //printf("\nLeo actor: %s", Pelicula[Registro].Actor);
  strcpy(Pelicula[Registro].Director,strtok(NULL,"\t\n"));
  //printf("\nLeo Director: %s", Pelicula[Registro].Director);
  strcpy(Pelicula[Registro].Pais,strtok(NULL,"\t\n"));
  //printf("\nLeo Pais: %s", Pelicula[Registro].Pais);
  strcpy(Pelicula[Registro].Fecha,strtok(NULL,"\t\n"));
  //printf("\nLeo Fecha: %s", Pelicula[Registro].Fecha);
  strcpy(Pelicula[Registro].Genero,strtok(NULL,"\t\n"));
  //printf("\nLeo Genero: %s", Pelicula[Registro].Genero);
  strcpy(Pelicula[Registro].Recaudacion,strtok(NULL,"\t\n"));
  //printf("\nLeo Recaudacion: %s", Pelicula[Registro].Recaudacion);
  strcpy(Pelicula[Registro].Empresa,strtok(NULL,"\t\n"));
  //printf("\nLeo Empresa: %s", Pelicula[Registro].Empresa);
  strcpy(Pelicula[Registro].Precio,strtok(NULL,"\t\n"));
  //printf("\nLeo Precio: %s", Pelicula[Registro].Precio);

    //printf("\n\n%s | \t%s | \t%s | \t%s | \t%s | \t%s | \t%s | \t%s | \n", Pelicula[Registro].ID, Pelicula[Registro].Nombre, Pelicula[Registro].Actor, Pelicula[Registro].Director, Pelicula[Registro].Pais, Pelicula[Registro].Fecha, Pelicula[Registro].Genero, Pelicula[Registro].Recaudacion);
}

///esta funcion abre el archivo en modo leer
int Cargar_Archivo_en_Struct () {
 char Linea[999];

 FILE* Archivo=fopen("Peliculas.txt","r");

 if(Archivo!=NULL){

 //fgets(Linea,999,Archivo);
 //Extrae_Campos(Linea,Cantidad_Pelis); //SE LA LLEVA A LA FUNCION EXTRAE_CAMPOS

 ///este while se encarga especificamente de leer el archivo
    while(!feof(Archivo)){
        fgets(Linea,9999,Archivo); //LEE LA LINEA
        Extrae_Campos(Linea,Cantidad_Pelis); //SE LA LLEVA A LA FUNCION EXTRAE_CAMPOS
        Cantidad_Pelis++;
    }
    fclose(Archivo);
 } else {
   printf("ERROR FATAL: No se ha podido abrir el archivo. Revise su estado.\n");
   printf("                   Se Saldra del Programa. Pulse una Tecla...");
   fflush(stdin);
   getchar();
   return 1;
 }
 return 0;
}


///esta funcion permite agregar peliculas al carrito
int Agregar_Pelicula (){
  int Eleccion;
  Listar_Peliculas(0);
  printf("\n  Que Pelicula desea Agregar al Carrito? (Ingrese 0 para Salir) > ");
  scanf("%i", &Eleccion);

  ///si se ingresa 0 se vuelve hacia atras
  if (Eleccion==0) { Carrito(); return 0; }

  ///por si se ingresa una pelicula que no existe...
  if(Eleccion>=Cantidad_Pelis || Eleccion<1){
    printf("\n   La Pelicula seleccionada no existe...\n\n");
    fflush(stdin);
    getchar();
    Carrito();
    return 0;
  }

  ///por si la pelicula ya se encuentra en el carrito...
  if (Peliculas_Carrito[Eleccion]==1) {
    printf("\n\n    Esa Pelicula ya esta en el carrito.\n");
    fflush(stdin);
    getchar();
    Carrito();
    return 0;
  } else {
    Peliculas_Carrito[Eleccion]=1;
    Carrito();
    return 0;
  }

}

///esta funcion le permite al usuario eliminar una pelicula del carrito
int Eliminar_Pelicula () {
  int Eleccion;
  Listar_Carrito();
  printf("\n  Que Pelicula desea Eliminar del Carrito? (Ingrese 0 para Salir) > ");
  scanf("%i", &Eleccion);

  if (Eleccion==0) { Carrito(); return 0; }

  ///si la pelicula no existe en el archivo
  if(Eleccion>=Cantidad_Pelis || Eleccion<=0){
    printf("\n   La Pelicula seleccionada no existe...\n\n");
    fflush(stdin);
    getchar();
    Limpiar_Pantalla();
    Carrito();
    return 0;
  }

  ///le coloca un 0 a la pelicula seleccionada para sacarla del carrito
  if (Peliculas_Carrito[Eleccion]==1) {
    Peliculas_Carrito[Eleccion]=0;
    Carrito();
    return 0;
  }

  ///por si se ingresa una pelicula que no esta en el carrito
  if (Peliculas_Carrito[Eleccion]==0) {
    printf("\n\n    Esa Pelicula no esta en el carrito.\n");
    fflush(stdin);
    getchar();
    Carrito();
    return 0;
  }
}

///esta funcion permite finalizar la compra
int Carrito_Terminado(){
    char Eleccion;
    int x;
    int SWAP;

    ///se pide una confirmacion para terminar la compra
      Listar_Carrito();
      printf("\n-------------------------------------------- PRECIO BRUTO: $%i",Precio_Total_Carrito);
      printf("\n\nDesea finalizar la compra? Borrara el Carrito (S/N) > ");
      fflush(stdin);
      Eleccion=getchar();
      printf("%c",Eleccion);

      if(Eleccion=='S' || Eleccion=='s' || Eleccion=='1' || Eleccion==13) {

        // VERIFICA QUE HAYA PELICULAS PARA IMPRIMIR, O SEA QUE EL TICKET NO ESTE EN BLANCO
       for(x=0;x<100;x++){
            if (Peliculas_Carrito[x]==1) { SWAP=1; x=101; }
        }

       if (SWAP==1) {

       // TERMINA LA COMPROBACION DE TICKET VACIO

        printf("\nQuiere imprimir un ticket?(S/N) > ");
        fflush(stdin);
        Eleccion=getchar();

        if (Eleccion=='s' || Eleccion=='S' || Eleccion=='1' || Eleccion==13) {


          ///////////////////////
            FILE* Archivo=fopen("ticket.txt","w");

            fprintf(Archivo,"        * * * VideoLandia * * *\n\n");
            fprintf(Archivo,"    Direccion: Av. Rivadavia 2110\n");
            fprintf(Archivo,"    Telefono: +54 11 4951 1673\n");
            fprintf(Archivo,"    Mail: Central@VideoLandia.com\n\n\n");
            fprintf(Archivo," ***************************************** \n\n");


            Precio_Total_Carrito=0;
            for (x=0;x<100;x++) {
              if (Peliculas_Carrito[x] == 1) {
                fprintf(Archivo," %s | %s  \n                            Precio: $%s\n\n", Pelicula[x].ID, Pelicula[x].Nombre, Pelicula[x].Precio);
                SWAP=atoi(Pelicula[x].Precio);
                Precio_Total_Carrito=Precio_Total_Carrito+SWAP;
              }
            }

            fprintf(Archivo, "\n *******************  PRECIO BRUTO: $%i", Precio_Total_Carrito);
            fclose(Archivo);
          ///////////////////////
        /*
            FILE* Impresora=fopen("lpr","w");
            Archivo=fopen("ticket.txt","r");
            char Caracter;

                if(Archivo!=NULL){
                    while(!feof(Archivo)){
                        Caracter=fgetc(Archivo);
                        fputc(Caracter, Impresora);
                    }
                }

            fclose(Impresora);*/
            fclose(Archivo);

            Limpiar_Pantalla();
            for(x=0;x<100;x++){
              Peliculas_Carrito[x]=0;
            }
            Menu_Proyecto();
            return 0;

        } else {
            Limpiar_Pantalla();
            for(x=0;x<100;x++){
              Peliculas_Carrito[x]=0;
            }
            Menu_Proyecto();
            return 0;
        }
       } else {// Cierra el ticket
        Carrito();
        return 0;
       }

      } else {// Cierra el ticket
        Carrito();
        return 0;
      }
}

///este struct asigna espacios para los usuarios y sus contraseñas
struct Usuarios{
  char Usuario[100], Contrasena[100];
} Usu_Reg[5];


///esta funcion crea una forma de loguearse con un usuario y contraseña
int Login_Manager(int *Entrada){
  int Eleccion, x;
  char UsuarioIng[100]="Vacio", ContrasenaIng[100]="Vacio";


/// DECLARACION DE USUARIOS ADMINISTRATIVOS

strcpy(Usu_Reg[0].Usuario,"belen");
strcpy(Usu_Reg[0].Contrasena,"hipolito");

strcpy(Usu_Reg[1].Usuario,"capia");
strcpy(Usu_Reg[1].Contrasena,"aguanteriver");

strcpy(Usu_Reg[2].Usuario,"leonardo");
strcpy(Usu_Reg[2].Contrasena,"alt-f4");

strcpy(Usu_Reg[3].Usuario,"lautaro");
strcpy(Usu_Reg[3].Contrasena,"asce");

strcpy(Usu_Reg[4].Usuario,"daniel");
strcpy(Usu_Reg[4].Contrasena,"platense");


  printf("(Ingrese 'cancelar' como Usuario para Salir)\n\n");
  printf("*******************************************************\n**\n");
  printf("**    Usuario: ");
  fflush(stdin);
  /* gets(UsuarioIng); */
  scanf("%s", &UsuarioIng);
  if (strcmp(UsuarioIng,"cancelar")==0) { Menu_Proyecto(); return 0; }
  fflush(stdin);
  printf("**    Contrasena: ");
  // if (strcmp(ContrasenaIng,"cancelar")==0) { Menu_Proyecto(); return 0; }
  fflush(stdin);
  /* gets(ContrasenaIng); */
  scanf("%s", ContrasenaIng);
  fflush(stdin);/*
  printf("**     \n");
  printf("********************************************************\n\n");
*/
  // COMPROBACION
  for (x=0; x < 5; x++){/*
        printf("\n%s - %s\n", UsuarioIng, Usu_Reg[x]. Usuario);
        printf("\n%s - %s\n\n", ContrasenaIng, Usu_Reg[x]. Contrasena);
*/
    if(strcmp(UsuarioIng , Usu_Reg[x]. Usuario)==0) {
      if (strcmp(ContrasenaIng , Usu_Reg[x]. Contrasena)==0) {
        *Entrada=1;
      }
    }
  }

  if (*Entrada!=1) {
    printf("\n\n ERROR: USUARIO O CONTRASENIA INCORRECTA");
    fflush(stdin);
    getchar();
    Menu_Proyecto();
    return 0;

  }

  return 0;

}

int main () {
    /* system("mode con cols=80 lines=50 "); //REGULA LA PANTALLA */
    int x, Comprobacion_Carga_en_Struct=2;
    for(x=0;x<100;x++){
      Peliculas_Carrito[x]=0;
    }
    Comprobacion_Carga_en_Struct=Cargar_Archivo_en_Struct();
    if (Comprobacion_Carga_en_Struct==1) return 0;
    Menu_Proyecto();
    return 0;
}

