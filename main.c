#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura Alumno
typedef struct {
    char nombre[50];
    float promedio;
    char carrera[50];
} Alumno;

// Variables globales
#define MAX_ALUMNOS 100
Alumno alumnos[MAX_ALUMNOS];
int totalAlumnos = 0;
const char *archivo = "alumnos.txt";

// Función para cargar datos desde el archivo
void cargarDatos() {
    FILE *fp = fopen(archivo, "r");
    if (fp != NULL) {
        totalAlumnos = 0;
        while (fscanf(fp, "%49[^,],%f,%49[^\n]\n",
                      alumnos[totalAlumnos].nombre,
                      &alumnos[totalAlumnos].promedio,
                      alumnos[totalAlumnos].carrera) == 3) {
            totalAlumnos++;
        }
        fclose(fp);
    }
}

// Función para guardar datos en el archivo
void guardarDatos() {
    FILE *fp = fopen(archivo, "w");
    if (fp != NULL) {
        for (int i = 0; i < totalAlumnos; i++) {
            fprintf(fp, "%s,%.2f,%s\n", alumnos[i].nombre, alumnos[i].promedio, alumnos[i].carrera);
        }
        fclose(fp);
    }
}

// Función para buscar un alumno por nombre
int buscarAlumno(const char *nombre) {
    for (int i = 0; i < totalAlumnos; i++) {
        if (strcmp(alumnos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

// Función para agregar un nuevo alumno
void agregarAlumno(const char *nombre, float promedio, const char *carrera) {
    if (totalAlumnos < MAX_ALUMNOS) {
        strcpy(alumnos[totalAlumnos].nombre, nombre);
        alumnos[totalAlumnos].promedio = promedio;
        strcpy(alumnos[totalAlumnos].carrera, carrera);
        totalAlumnos++;
        guardarDatos();
    } else {
        printf("Error: no se pueden agregar más alumnos.\n");
    }
}

// Función para mostrar todos los alumnos
void mostrarAlumnos() {
    for (int i = 0; i < totalAlumnos; i++) {
        printf("Nombre: %s, Promedio: %.2f, Carrera: %s\n",
               alumnos[i].nombre, alumnos[i].promedio, alumnos[i].carrera);
    }
}

// Menú principal
int main() {
    cargarDatos();

    while (1) {
        printf("\n1. Agregar nuevo alumno\n");
        printf("2. Buscar alumno\n");
        printf("3. Ver todos los alumnos\n");
        printf("4. Salir\n");
        printf("Selecciona una opción: ");

        int opcion;
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        if (opcion == 1) {
            char nombre[50], carrera[50];
            float promedio;

            printf("Nombre: ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar salto de línea

            printf("Promedio: ");
            scanf("%f", &promedio);
            getchar();

            printf("Carrera: ");
            fgets(carrera, sizeof(carrera), stdin);
            carrera[strcspn(carrera, "\n")] = '\0';

            agregarAlumno(nombre, promedio, carrera);

        } else if (opcion == 2) {
            char nombre[50];
            printf("Nombre a buscar: ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0';

            int index = buscarAlumno(nombre);
            if (index != -1) {
                printf("Alumno encontrado: Nombre: %s, Promedio: %.2f, Carrera: %s\n",
                       alumnos[index].nombre, alumnos[index].promedio, alumnos[index].carrera);
            } else {
                printf("Alumno no encontrado.\n");
            }

        } else if (opcion == 3) {
            mostrarAlumnos();
        } else if (opcion == 4) {
            break;
        } else {
            printf("Opción no válida.\n");
        }
    }

    return 0;
}
