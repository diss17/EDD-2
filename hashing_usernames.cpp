#include <iostream>
#include <string>
#include "csv_reader.cpp"
#include <unordered_map>
#include <chrono>
#include <math.h>
#include "hash_table_strings.h"
#include "hash_table_usernames_abierto.h"
#include "user.h"

// Numero aureo
float A = (sqrt(5) - 1) / 2;
/// @brief Función de hash simplificada de Jenkins
/// @param str Cadena a la que se le aplicará el hash
/// @return Valor hash de la cadena
unsigned long long simple_hash(const std::string &str)
{
    unsigned long long hash = 0;
    for (char c : str)
    {
        hash += static_cast<unsigned long long>(c);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
/// @brief Primera función hash (método de división)
/// @param k Clave
/// @param n Tamaño de la tabla hash
/// @return Resto de dividir el hash por el tamaño de la tabla
unsigned long long h1(const std::string &k, int n)
{
    unsigned long long hash = simple_hash(k);
    return hash % n;
}

/// @brief Segunda función hash (método de multiplicación)
/// @param k Clave
/// @param n Tamaño de la tabla hash
/// @return Parte fraccionaria del producto entre el hash y el número áureo, multiplicada por el tamaño de la tabla
unsigned long long h2(const std::string &k, int n)
{
    float a = simple_hash(k) * A;
    a -= (int)a;
    return n * a;
}

/// @brief Método de manejo de colisiones (Linear probing)
/// @param k Clave a la que se le aplicará una función hash
/// @param n Tamaño de la tabla hash
/// @param i Número de intentos de indexación
/// @return Índice calculado usando el método de linear probing
int linear_probing(const std::string &k, int n, int i)
{
    return (h1(k, n) + i) % n;
}

/// @brief Método de manejo de colisiones (Quadratic probing)
/// @param k Clave para aplicar hashing
/// @param n Tamaño de la tabla
/// @param i Número de intentos de indexación
/// @return Índice calculado usando el método de quadratic probing
int quadratic_probing(const std::string &k, int n, int i)
{
    return (h1(k, n) + i + 2 * i * i) % n;
}

/// @brief Método de manejo de colisiones (Double Hashing)
/// @param k Clave para aplicar hashing
/// @param n Tamaño de la tabla
/// @param i Número de intentos de indexación
/// @return Índice calculado usando el método de double hashing
int double_hashing(const std::string &k, int n, int i)
{
    return (h1(k, n) + i * (h2(k, n) + 1)) % n;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << "<Cantidad de elementos>" << endl;
        exit(1);
    }
    int n = atoi(argv[1]);

    // Ruta del archivo_inventados CSV
    // archivo sin repeticiones ni numeros en notacion cientifica
    std::string filename = "universities_followers_int64.csv";
    csv_reader archivo(filename);

    // Extraer columnas del archivo CSV
    vector<std::string> university_column = archivo.extract_column(0);
    vector<unsigned long long> id_column = archivo.extract_column_as_ull(1);
    vector<std::string> username_column = archivo.extract_column(2);
    vector<unsigned long long> number_column = archivo.extract_column_as_ull(3);
    vector<unsigned long long> friends_column = archivo.extract_column_as_ull(4);
    vector<unsigned long long> followers_column = archivo.extract_column_as_ull(5);
    vector<std::string> created_column = archivo.extract_column(6);

    csv_reader archivo_inventados("universities_followers_random.csv");
    // Extraer columnas del archivo CSV de usuarios inventados
    vector<std::string> university_column_inventados = archivo_inventados.extract_column(0);
    vector<unsigned long long> id_column_inventados = archivo_inventados.extract_column_as_ull(1);
    vector<std::string> username_column_inventados = archivo_inventados.extract_column(2);
    vector<unsigned long long> number_column_inventados = archivo_inventados.extract_column_as_ull(3);
    vector<unsigned long long> friends_column_inventados = archivo_inventados.extract_column_as_ull(4);
    vector<unsigned long long> followers_column_inventados = archivo_inventados.extract_column_as_ull(5);
    vector<std::string> created_column_inventados = archivo_inventados.extract_column(6);

    // Crear vector de usuarios
    int N = 21070;
    vector<User> usuarios(N);
    vector<User> usuariosInventados(n);
    // Llenar el vector de usuarios
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
    // Llenar el vector de usuarios inventados
    for (int i = 0; i < n; i++)
    {
        usuariosInventados[i].university = university_column_inventados[i];
        usuariosInventados[i].user_id = id_column_inventados[i];
        usuariosInventados[i].user_name = username_column_inventados[i];
        usuariosInventados[i].number_tweets = number_column_inventados[i];
        usuariosInventados[i].friends_count = friends_column_inventados[i];
        usuariosInventados[i].followers_count = followers_column_inventados[i];
        usuariosInventados[i].created_at = created_column_inventados[i];
    }

    hash_table_usernames_abierto hta(N);
    std::unordered_map<std::string, User> um;
    std::ofstream file("results_names.csv", std::ios::app);
    //////////////////HASHING ABIERTO////////////////////////////

    ///////////INSERCIONES/////////////////////////////////////
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        hta.insert(usuarios[i]);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_abierto_usernames" << ";" << "hashing_abierto_insert" << ";" << n << ";" << duration << std::endl;

    ///////////BUSQUEDAS/////////////////////////////////////
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        hta.search(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_abierto_usernames" << ";" << "hashing_abierto_search" << ";" << n << ";" << duration << std::endl;

    //////////////////HASHING CERRADO////////////////////////////
    hash_table_string htc_linear(N, linear_probing);
    hash_table_string htc_quadratic(N, quadratic_probing);
    hash_table_string htc_double(N, double_hashing);

    ///////////INSERCIONES/////////////////////////////////////
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_linear.insert(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_usernames" << ";" << "linear_insert" << ";" << n << ";" << duration << std::endl;
    
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_quadratic.insert(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_usernames" << ";" << "quadratic_insert" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_double.insert(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_usernames" << ";" << "double_insert" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        um[usuarios[i].user_name] = usuarios[i];
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_usernames" << ";" << "unorderedmap_insert" << ";" << n << ";" << duration << std::endl;

    ///////////BUSQUEDAS/////////////////////////////////////
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_linear.search(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_usernames" << ";" << "linear_search" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_quadratic.search(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_usernames" << ";" << "quadratic_search" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_double.search(usuarios[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();    
    file << "hashing_cerrado_usernames" << ";" << "double_search" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        um.find(usuarios[i].user_name);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << "hashing_cerrado_usernames" << ";" << "unorderedmap_search" << ";" << n << ";" << duration << std::endl;
    file.close();

    std::ofstream file2("results_names_random.csv", std::ios::app);
    ///////////////BUSQUEDA USUARIOS INVENTADOS////////////////////////
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        hta.search(usuariosInventados[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file2 << "hashing_abierto_usernames" << ";" << "hashing_abierto_search_random" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_linear.search(usuariosInventados[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file2 << "hashing_cerrado_usernames" << ";" << "linear_search_random" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_quadratic.search(usuariosInventados[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file2 << "hashing_cerrado_usernames" << ";" << "quadratic_search_random" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        htc_double.search(usuariosInventados[i]);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file2 << "hashing_cerrado_usernames" << ";" << "double_search_random" << ";" << n << ";" << duration << std::endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        um.find(usuariosInventados[i].user_name);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file2 << "hashing_cerrado_usernames" << ";" << "unorderedmap_search_random" << ";" << n << ";" << duration << std::endl;

    file2.close();
    
    return 0;
}