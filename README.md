# Entregable 2 de Estructura de Datos
Entregable en el que se compara el rendimiento de distintas tablas hash para usuarios de twitter
## Nombre integrantes del grupo
- Benjamin Alonso Espinoza Henriquez
- Daniel Ignacio Soto Salgado

## Instrucciones para la ejecución

### Compilación y Ejecución con Nombres de Usuario como Clave
1. Compilar el archivo `hashing_usernames.cpp`:
    ```bat
    g++ hashing_usernames.cpp -o hashing_usernames
    ```
2. Ejecutar el programa(en Linux):
    ```bat
    ./hashing_usernames (cantidad de datos)
    ```
3. Ejecutar el programa(en Windows):
    ```bat
    .\hashing_usernames (cantidad de datos)
    ```

### Compilación y Ejecución de Pruebas con IDs como Clave
1. Compilar el archivo `main_ids.cpp`:
    ```sh
    g++ main_ids.cpp -o main_ids
    ```
2. Ejecutar el programa:
    ```sh
    ./main_ids (cantidad de datos)
    ```
3. Ejecutar el programa(en Windows):
    ```sh
    ./main_ids (cantidad de datos)
    ```

### Ejecución del Experimento Completo

#### En Windows
Para ejecutar el experimento completo en Windows, se deben compilar ambos archivos (hashing_usernames.cpp y main_ids.cpp) y ejecutar el script `run_test.bat`:
```bat
.\run_test.bat
```
#### En Linux
Para ejecutar el experimento completo en Linux ejecutar el script `run_test.sh`:
```sh
./run_test.sh
