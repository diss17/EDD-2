#include <iostream>
#include "csv_reader.cpp"
#include <unordered_map>
#include <chrono>
#include <math.h>
#include "hash_table_ids.h"

using namespace std;
//Numero áureo
float A = (sqrt(5) - 1) / 2;

/// @brief Primero funcion hash(metodo de division)
/// @param k Clave
/// @param n Tamaño tabla hash
/// @return retorna el modulo entre k y n
unsigned long long h1(unsigned long long k, int n)
{
    return k % n;
}
/// @brief Segunda funcion hash(metodo de multiplicacion)
/// @param k Clave
/// @param n Tamaño tabla hash
/// @return producto entre la parte fraccionaria de k por n
unsigned long long h2(unsigned long long k, int n)
{
    float a = (float)k * A;
    a -= (int)a;
    return n * a;
}

/// @brief Metodo de manejo de colisiones (Linear probing)
/// @param k Clave a la que se le aplicara una funcion hash
/// @param n tamaño de la tabla hash
/// @param i Numero de intentos de indexacion
/// @return Utiliza el metodo de division.
int linear_probing(unsigned long long k, int n, int i)
{
    return (h1(k, n) + i) % n;
}
/// @brief Metodo de manejo de colisiones(Quadratic probing)
/// @param k Clave para aplicar hashing
/// @param n tamaño de la tabla
/// @param i numero de intento
/// @return Utiliza el metodo de la multiplicacion
int quadratic_probing(unsigned long long k, int n, int i)
{
    return (h1(k, n) + i + 2 * i * i) % n;
}
/// @brief Metodo de manejo de colisiones(Double Hashing)
/// @param k clave para aplicar hashing
/// @param n tamaño tabla
/// @param i numero de intento
/// @return Utiliza ambas funciones hash
int double_hashing(unsigned long long k, int n, int i)
{
    return (h1(k, n) + i * (h2(k, n) + 1)) % n;
}
// Metodo para llenar el archivo con el numero de elementos a medir y su tiempo respectivo
void llenar_csv(const string &filename, int n, long long duration)
{
    ofstream file;
    file.open(filename, ios_base::app);
    file << n << "," << duration << endl;
    file.close();
}
int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << "<Cantidad de elementos>" << endl;
        exit(1);
    }
    int n = atoi(argv[1]);
    // Ruta del archivo CSV
    // archivo sin repeticiones ni numeros en notacion cientifica
    string filename = "universities_followers_int64.csv";
    // Crear una instancia de CSVReader
    csv_reader csvReader(filename);

    // Extraer la segunda columna
    vector<unsigned long long> id_column = csvReader.extract_column_as_ull(1);

    int N = 21070;
    hash_table ht_linear(N, linear_probing);
    hash_table ht_quadratic(N, quadratic_probing);
    hash_table ht_double(N, double_hashing);
    unordered_map<int, int> um;

///////////INSERCIONES/////////////////////////////////////

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_linear.search(num);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("linear_insert_ids.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_quadratic.insert(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("quadratic_insert_ids.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_double.insert(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("duoblehashing_insert_ids.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        um.insert({num,num});
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("unorderedmap_insert_ids.csv", n, duration);

///////////BUSQUEDAS/////////////////////////////////////

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_linear.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("linear_search_ids.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_quadratic.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("quadratic_search_ids.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_double.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("doublehashing_search_ids.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        um.find(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("unorderedmap_search_ids.csv", n, duration);
    return 0;
}