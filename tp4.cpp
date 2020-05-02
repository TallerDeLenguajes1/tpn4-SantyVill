#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int tareaID,duracion;
    char *descripcion;
} tarea;


void cargarTareas(tarea *tareas,int n);
int realizarTareas(tarea *tareasP, tarea *tareasR,int n);
void mostrarTareas(tarea *tareasP, tarea *tareasR,int n,int c);
tarea* buscarTarea(tarea *tareasP,tarea *tareasR,int n,int c);

//=========================MIAN=========================

int main(){
    srand (time(NULL));
    int n,i,opc,c=0;
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d",&n);
    getchar();
    tarea *tareasPendientes=(tarea *)malloc(sizeof(tarea)*n);
    tarea *tareasRealizadas=(tarea *)malloc(sizeof(tarea)*n);
    cargarTareas(tareasPendientes, n);
    c=realizarTareas(tareasPendientes,tareasRealizadas,n);
    mostrarTareas(tareasPendientes,tareasRealizadas,n,c);
    getchar();
    getchar();
    free (tareasRealizadas);
    free (tareasPendientes);
    return 0;
}

//========================FUNCIONES========================

tarea* buscarTarea(tarea *tareasP,tarea *tareasR,int n,int c){
    int id,i;
    printf("Ingrese el id de la tarea que desea buscar: ");
    scanf("%d",&id);
    for (i = 0; i < c; i++)
    {
        if ((tareasR+i)->tareaID==id)
        {
            return (tareasR+i);
        }
        
    }
    
    for ( i = 0; i < n; i++)
    {
        if ((tareasP+i)->tareaID==id)
        {
            return (tareasP+i);
        }
    }
}

void mostrarTareas(tarea *tareasP, tarea *tareasR,int n,int c){
    int i;
    printf("\n\nTareas realizadas: ");
    for (i = 0; i < c; i++)
    {
            printf("\n\nTarea numero %d",(tareasR+i)->tareaID);
            printf("\nDescripcion: %s",(tareasR+i)->descripcion);
            printf("\nDuracion: %d",(tareasR+i)->duracion);
    }
    printf("\n\nTareas Pendientes: ");
    for (i = 0; i < n; i++)
    {
        if ((tareasP+i)->descripcion!=NULL)
        {
            printf("\n\nTarea numero %d",(tareasP+i)->tareaID);
            printf("\nDescripcion: %s",(tareasP+i)->descripcion);
            printf("\nDuracion: %d",(tareasP+i)->duracion);
        }
    }
    
}

void cargarTareas(tarea *tareas,int n){
    int i;
    char descr[60];
    for ( i = 0; i < n; i++)
    {
        (tareas+i)->tareaID=i+1;
        (tareas+i)->duracion=rand()%91+10;
        printf("\nIngrese la descripcion de la tarea %d: ",i+1);
        gets(descr);
        (tareas+i)->descripcion=(char *)malloc(sizeof(char)*strlen(descr));
        strcpy((tareas+i)->descripcion,descr);
    }
}

int realizarTareas(tarea *tareasP, tarea *tareasR,int n){
    int opc=0,i,c=0;
    for (i = 0; i < n; i++)
    {
        printf("\nSe realizara la tarea %d?",i+1);
        printf("\nDescripcion: %s",(tareasP+i)->descripcion);
        printf("\nDuracion: %d",(tareasP+i)->duracion);
        do
        {
            printf("\nSI --> 1.\tNO --> 2.");
            scanf("%d",&opc);
        } while (opc!=1 && opc!=2);
        if (opc==1)
        {
            *(tareasR+c)=*(tareasP+i);
            (tareasP+i)->descripcion=NULL;
            (tareasP+i)->tareaID=NULL;
            (tareasP+i)->duracion=NULL;
            c++;
        }
    }
    return c;
}