#include <iostream>
#include "csv_reader.cpp"
#include <unordered_map>
#include <chrono>
#include <math.h>
#include "hash_table_ids.h"
#include "hash_table_ids_abierto.h"
#include "User.h"

using namespace std;
// Numero aureo
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
/// @brief Función para vaciar archivos CSV
void vaciar_csv()
{
    std::ofstream file_out("linear_insert_ids.csv", std::ios::trunc);
    file_out.close();
    file_out.open("quadratic_insert_ids.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("unorderedmap_insert_ids.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("double_insert_ids.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("linear_search_ids.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("quadratic_search_ids.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("unorderedmap_search_ids.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("double_search_ids.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
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
    csv_reader archivo(filename);
    // Definimos el tamano de la tabla hash
    int N = 21070;

    // Extraer columnas de dataset para asignar su tipo segun la estructura user.h
    vector<string> university_column = archivo.extract_column(0);
    vector<unsigned long long> id_column = archivo.extract_column_as_ull(1);
    vector<string> username_column = archivo.extract_column(2);
    vector<unsigned long long> number_column = archivo.extract_column_as_ull(3);
    vector<unsigned long long> friends_column = archivo.extract_column_as_ull(4);
    vector<unsigned long long> followers_column = archivo.extract_column_as_ull(5);
    vector<string> created_column = archivo.extract_column(6);

    hash_table_ids_abierto hta(N);

    std::ofstream file("results_ids.csv", std::ios::app);

    vector<User> usuarios(N);
    for (int i = 0; i < N; i++)
    {
        usuarios[i].university = university_column[i];
        usuarios[i].user_id = id_column[i];
        usuarios[i].user_name = username_column[i];
        usuarios[i].number_tweets = number_column[i];
        usuarios[i].friends_count = friends_column[i];
        usuarios[i].followers_count = followers_column[i];
        usuarios[i].created_at = created_column[i];
    }
    hash_table ht_linear(N, linear_probing);
    hash_table ht_quadratic(N, quadratic_probing);
    hash_table ht_double(N, double_hashing);
    unordered_map<int, User> um;
    //////////////////HASHING ABIERTO////////////////////////////

    // INSERCIONES
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        hta.insert(usuarios[i]);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_abierto_ids" << ";" << "hashing_abierto_insert" << ";" << n << ";" << duration << endl;
    // BUSQUEDAS
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        hta.search(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_abierto_ids" << ";" << "hashing_abierto_search" << ";" << n << ";" << duration << endl;

    ////////////HASHING CERRADO////////////////////////////////
    ///////////INSERCIONES/////////////////////////////////////
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = usuarios[i].user_id;
        ht_linear.insert(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "linear_insert" << ";" << n << ";" << duration << endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = usuarios[i].user_id;
        ht_quadratic.insert(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "quadratic_insert" << ";" << n << ";" << duration << endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = usuarios[i].user_id;
        ht_double.insert(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "double_insert" << ";" << n << ";" << duration << endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        um[usuarios[i].user_id] = usuarios[i];
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "unorderedmap_insert" << ";" << n << ";" << duration << std::endl;

    ///////////BUSQUEDAS/////////////////////////////////////

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = usuarios[i].user_id;
        ht_linear.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "linear_search" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = usuarios[i].user_id;
        ht_quadratic.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "quadratic_search" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = usuarios[i].user_id;
        ht_double.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "double_search" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = usuarios[i].user_id;
        um.find(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "unorderedmap_search" << ";" << n << ";" << duration << std::endl;
    return 0;
}