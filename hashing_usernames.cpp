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

/// @brief Función que realiza inserciones en una hash table y mide el tiempo total
/// @param hts Tabla hash en la que se realizarán las inserciones
/// @param n_inserts Número de inserciones a realizar
/// @param users_names Vector con los nombres de usuario
/// @param out_file_name Nombre del archivo de salida donde se guardará la duración de las inserciones
double test_insert(hash_table_string &hts, int n_inserts,
                   std::vector<User> users)
{

    // Hacemos las inserciones
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n_inserts; i++)
    {
        hts.insert(users[i]);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return duration;
}

/// @brief Función que realiza búsquedas en una hash table y mide la duración total
/// @param hts Tabla hash en la que se realizarán las búsquedas
/// @param n_searches Número de búsquedas a realizar
/// @param users_names Vector con los nombres de usuario
/// @param out_file_name Nombre del archivo de salida donde se guardará la duración de las búsquedas
double test_search(hash_table_string &hts, int n_searches, std::vector<User> users)
{

    // Hacemos las búsquedas
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n_searches; i++)
    {
        hts.search(users[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return duration;
}

/// @brief Función que realiza inserciones en una hash table y mide el tiempo total
/// @param hts Tabla hash en la que se realizarán las inserciones
/// @param n_inserts Número de inserciones a realizar
/// @param users_names Vector con los nombres de usuario
/// @param out_file_name Nombre del archivo de salida donde se guardará la duración de las inserciones
double test_insert(hash_table_usernames_abierto &hts, int n_inserts,
                   std::vector<User> users)
{

    // Hacemos las inserciones
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n_inserts; i++)
    {
        hts.insert(users[i]);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return duration;
}

/// @brief Función que realiza inserciones en un unordered map y mide el tiempo total
/// @param hts Tabla hash en la que se realizarán las inserciones
/// @param n_inserts Número de inserciones a realizar
/// @param users_names Vector con los nombres de usuario
/// @param out_file_name Nombre del archivo de salida donde se guardará la duración de las inserciones
double test_insert(unordered_map<std::string, User> &um, int n_inserts,
                   std::vector<User> users)
{

    // Hacemos las inserciones
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n_inserts; i++)
    {
        um[users[i].user_name] = users[i];
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return duration;
}

/// @brief Función que realiza búsquedas en una hash table y mide la duración total
/// @param hts Tabla hash en la que se realizarán las búsquedas
/// @param n_searches Número de búsquedas a realizar
/// @param users_names Vector con los nombres de usuario
/// @param out_file_name Nombre del archivo de salida donde se guardará la duración de las búsquedas
double test_search(hash_table_usernames_abierto &hts, int n_searches, std::vector<User> users)
{

    // Hacemos las búsquedas
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n_searches; i++)
    {
        hts.search(users[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return duration;
}

/// @brief Función que realiza búsquedas en un unordered map y mide la duración total
/// @param hts Tabla hash en la que se realizarán las búsquedas
/// @param n_searches Número de búsquedas a realizar
/// @param users_names Vector con los nombres de usuario
/// @param out_file_name Nombre del archivo de salida donde se guardará la duración de las búsquedas
double test_search(std::unordered_map<std::string, User> &um, int n_searches, std::vector<User> users)
{

    // Hacemos las búsquedas
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n_searches; i++)
    {
        um.find(users[i].user_name);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return duration;
}

/// @brief Función para vaciar archivos CSV
void vaciar_csv()
{
    std::ofstream file_out("linear_insert_usernames.csv", std::ios::trunc);
    file_out.close();
    file_out.open("quadratic_insert_usernames.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("unorderedmap_insert_usernames.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("double_insert_usernames.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("linear_search_usernames.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("quadratic_search_usernames.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("unorderedmap_search_usernames.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
    file_out.open("double_search_usernames.csv", std::ios::trunc);
    file_out << std::endl;
    file_out.close();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << "<Cantidad de elementos>" << endl;
        exit(1);
    }
    int n = atoi(argv[1]);

    // Ruta del archivo CSV
    // archivo sin repeticiones ni numeros en notacion cientifica
    std::string filename = "universities_followers_int64.csv";
    csv_reader archivo(filename);
    vector<std::string> university_column = archivo.extract_column(0);
    vector<unsigned long long> id_column = archivo.extract_column_as_ull(1);
    vector<std::string> username_column = archivo.extract_column(2);
    vector<unsigned long long> number_column = archivo.extract_column_as_ull(3);
    vector<unsigned long long> friends_column = archivo.extract_column_as_ull(4);
    vector<unsigned long long> followers_column = archivo.extract_column_as_ull(5);
    vector<std::string> created_column = archivo.extract_column(6);

    int N = 21070;
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

    hash_table_usernames_abierto hta(N);
    std::unordered_map<std::string, User> um;
    std::ofstream file("results_names.csv", std::ios::app);

    // INSERCIONES
    double duration = test_insert(hta, n, usuarios);
    file << "hashing_abierto_usernames" << ";" << "hashing_abierto_insert" << ";" << n << ";" << duration << std::endl;
    // BUSQUEDAS
    duration = test_search(hta, n, usuarios);
    file << "hashing_abierto_usernames" << ";" << "hashing_abierto_search" << ";" << n << ";" << duration << std::endl;

    hash_table_string htc_linear(N, linear_probing);
    hash_table_string htc_quadratic(N, quadratic_probing);
    hash_table_string htc_double(N, double_hashing);

    // INSERCIONES
    duration = test_insert(htc_linear, n, usuarios);
    file << "hashing_cerrado_usernames" << ";" << "linear_insert" << ";" << n << ";" << duration << std::endl;
    duration = test_insert(htc_quadratic, n, usuarios);
    file << "hashing_cerrado_usernames" << ";" << "quadratic_insert" << ";" << n << ";" << duration << std::endl;
    duration = test_insert(htc_double, n, usuarios);
    file << "hashing_cerrado_usernames" << ";" << "double_insert" << ";" << n << ";" << duration << std::endl;
    duration = test_insert(um, n, usuarios);
    file << "hashing_cerrado_usernames" << ";" << "unorderedmap_insert" << ";" << n << ";" << duration << std::endl;

    // BUSQUEDAS
    duration = test_search(htc_linear, n, usuarios);
    file << "hashing_cerrado_usernames" << ";" << "linear_search" << ";" << n << ";" << duration << std::endl;
    duration = test_search(htc_quadratic, n, usuarios);
    file << "hashing_cerrado_usernames" << ";" << "quadratic_search" << ";" << n << ";" << duration << std::endl;
    duration = test_search(htc_double, n, usuarios);
    file << "hashing_cerrado_usernames" << ";" << "double_search" << ";" << n << ";" << duration << std::endl;
    duration = test_search(um, n, usuarios);
    file << "hashing_cerrado_usernames" << ";" << "unorderedmap_search" << ";" << n << ";" << duration << std::endl;
    return 0;
}