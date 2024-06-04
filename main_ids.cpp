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

/// @brief Metodo par calcular el tamaño de un string
/// @param str string para calcular su tamaño
/// @return tamaño del string
size_t stringSize(const std::string& str) {
    return sizeof(str) + str.capacity();
}

/// @brief Metodo para calcular el tamaño de un usuario
/// @param user usuario al que calcular su tamaño
/// @return tamaño del usuario
size_t userSize(const User& user) {
    return sizeof(user.user_id) + sizeof(user.number_tweets) + sizeof(user.friends_count) +
           sizeof(user.followers_count) + stringSize(user.university) +
           stringSize(user.user_name) + stringSize(user.created_at);
}

/// @brief Metodo para calcular el tamaño de un vector
/// @param vector vector al que calcular su tamaño
/// @return tamaño del vector
size_t vectorSize(const std::vector<User>& vector) {
    size_t totalSize = sizeof(vector) + vector.capacity() * sizeof(User);
    for (User user : vector) {
        totalSize += userSize(user);
    }
    return totalSize;
}

/// @brief Metodo para calcular el tamaño de una tabla hash
/// @param hashTable hashTable al que calcular su tamaño
/// @return tamaño de la tabla hash
size_t hashTableSize(const hash_table_ids& hashTable) {
    size_t totalSize = sizeof(hashTable.size) + sizeof(hashTable.table) + sizeof(hashTable.hashing_method) + hashTable.size * sizeof(User);
    for (int i = 0; i < hashTable.size; i++) {
        totalSize += userSize(hashTable.table[i]);
    }
    return totalSize;
}

/// @brief Metodo para calcular el tamaño de una tabla hash
/// @param hashTable hashTable al que calcular su tamaño
/// @return tamaño de la tabla hash
size_t hashTableSize(const hash_table_ids_abierto& hashTable) {
    size_t totalSize = sizeof(hashTable.size) + sizeof(hashTable.table) + hashTable.size * sizeof(std::list<User>);
    for (int i = 0; i < hashTable.size; i++) {
        for(User user : hashTable.table[i]) {
            totalSize += userSize(user);
        }
    }
    return totalSize;
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
    string random = "universities_followers_int64.csv";
    // Crear una instancia de CSVReader
    csv_reader archivo(filename);
    csv_reader archivo_random(random);
    // Definimos el tamano de la tabla hash

    // Extraer columnas de dataset para asignar su tipo segun la estructura user.h
    vector<string> university_column = archivo.extract_column(0);
    vector<unsigned long long> id_column = archivo.extract_column_as_ull(1);
    vector<string> username_column = archivo.extract_column(2);
    vector<unsigned long long> number_column = archivo.extract_column_as_ull(3);
    vector<unsigned long long> friends_column = archivo.extract_column_as_ull(4);
    vector<unsigned long long> followers_column = archivo.extract_column_as_ull(5);
    vector<string> created_column = archivo.extract_column(6);

    // Extraer columnas generadas random para asignar su tipo segun la estructura user.h
    vector<string> university_column_random = archivo_random.extract_column(0);
    vector<unsigned long long> id_column_random = archivo_random.extract_column_as_ull(1);
    vector<string> username_column_random = archivo_random.extract_column(2);
    vector<unsigned long long> number_column_random = archivo_random.extract_column_as_ull(3);
    vector<unsigned long long> friends_column_random = archivo_random.extract_column_as_ull(4);
    vector<unsigned long long> followers_column_random = archivo_random.extract_column_as_ull(5);
    vector<string> created_column_random = archivo_random.extract_column(6);


    vector<User> usuarios(n);
    vector<User> usuarios_randoms(n);
    for (int i = 0; i < n; i++)
    {
        usuarios[i].university = university_column[i];
        usuarios[i].user_id = id_column[i];
        usuarios[i].user_name = username_column[i];
        usuarios[i].number_tweets = number_column[i];
        usuarios[i].friends_count = friends_column[i];
        usuarios[i].followers_count = followers_column[i];
        usuarios[i].created_at = created_column[i];
    }

    for (int i = 0; i < n; i++)
    {
        usuarios_randoms[i].university = university_column_random[i];
        usuarios_randoms[i].user_id = id_column_random[i];
        usuarios_randoms[i].user_name = username_column_random[i];
        usuarios_randoms[i].number_tweets = number_column_random[i];
        usuarios_randoms[i].friends_count = friends_column_random[i];
        usuarios_randoms[i].followers_count = followers_column_random[i];
        usuarios_randoms[i].created_at = created_column_random[i];
    }
    
    hash_table_ids_abierto hta(n);
    std::ofstream file("results_ids.csv", std::ios::app);

    std::ofstream file1("results_ids_random.csv", std::ios::app);

    hash_table_ids ht_linear(n, linear_probing);
    hash_table_ids ht_quadratic(n, quadratic_probing);
    hash_table_ids ht_double(n, double_hashing);
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

    // BUSQUEDAS DE USERS NO EXISTENTES CON HASHING ABIERTO

        start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        hta.search(usuarios_randoms[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file1 << "hashing_abierto_ids" << ";" << "hashing_abierto_searchrandom" << ";" << usuarios_randoms.size() << ";" << duration << endl;
    ///////////INSERCIONES/////////////////////////////////////

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        ht_linear.insert(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "linear_insert" << ";" << n << ";" << duration << endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        ht_quadratic.insert(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "quadratic_insert" << ";" << n << ";" << duration << endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        ht_double.insert(usuarios[i]);
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
        ht_linear.search(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "linear_search" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        ht_quadratic.search(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_ids" << ";" << "quadratic_search" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        ht_double.search(usuarios[i]);
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

    //////////////////BUSQUEDAS DE USUARIOS NO EXISTENTES EN LA TABLA HASH////////////////////////////////////
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        ht_linear.search(usuarios_randoms[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file1 << "hashing_cerrado_ids" << ";" << "linear_randomsearch" << ";" << usuarios_randoms.size() << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        ht_quadratic.search(usuarios_randoms[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file1 << "hashing_cerrado_ids" << ";" << "quadratic_randomsearch" << ";" << usuarios_randoms.size() << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        ht_double.search(usuarios_randoms[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file1 << "hashing_cerrado_ids" << ";" << "double_randomsearch" << ";" << usuarios_randoms.size() << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        um.find(usuarios_randoms[i].user_id);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file1 << "hashing_cerrado_ids" << ";" << "unorderedmap_randomsearch" << ";" << usuarios_randoms.size() << ";" << duration << std::endl;

    file.close();
    file1.close();

    std::ofstream file3("memory.csv", std::ios::app);
    file3 << "vector_usuarios" << ";" << "usuarios" << ";" << n << ";" << vectorSize(usuarios) / 1024.0 << std::endl;
    file3 << "hashing_ids" << ";" << "hashing_abierto" << ";" << n << ";" << hashTableSize(hta) / 1024.0 << std::endl;
    file3 << "hashing_ids" << ";" << "hashing_cerrado" << ";" << n << ";" << hashTableSize(ht_linear) / 1024.0 << std::endl;
    file3.close();    

    return 0;
}