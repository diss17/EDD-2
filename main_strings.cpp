#include <iostream>
#include <string>
#include "csv_reader.cpp"
#include <unordered_map>
#include <chrono>
#include <math.h>
#include "hash_table_strings.h"

//funcion simplificada de hashing de jenkins
unsigned long long simple_hash(const std::string& str) {
    unsigned long long hash = 0;
    for (char c : str) {
        hash += static_cast<unsigned long long>(c);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

//funcion hash 1
unsigned long long h1(const std::string& k, int n) {
    unsigned long long hash = simple_hash(k);
    return hash % n;
}

//funcion hash 2
unsigned long long h2(const std::string& k, int n) {
    const float A = 0.61803398875;
    float a = simple_hash(k) * A;
    a -= static_cast<int>(a);
    return n * a;
}

int linear_probing(const std::string& k, int n, int i)
{
    return (h1(k, n) + i) % n;
}

int quadratic_probing(const std::string& k, int n, int i)
{
    return (h1(k, n) + i + 2 * i * i) % n;
}

int double_hashing(const std::string& k, int n, int i)
{
    return (h1(k, n) + i * (h2(k, n) + 1)) % n;
}

//Funcion que hace n_inserts inserciones, el archivo csv que genera da la duracion total despues de todas las inserciones
//Usa una hash table
void test_insert(hash_table_string& hts, int n_inserts,
        std::vector<std::string> users_names, std::string out_file_name){
    
    //Creamos el archivo .csv
    ofstream file_out(out_file_name, ios::trunc); 
    
    //Hacemos las inserciones
    for (int i = 0; i < n_inserts; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        std::string key = users_names[i];
        hts.insert(key);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file_out << i + 1 << ", " << duration << std::endl;
    }
}
//misma funcion pero que usa un unoredered_map
void test_insert(unordered_map<std::string, std::string>& um, int n_inserts,
        std::vector<std::string> users_names, std::string out_file_name){
    
    //Creamos el archivo .csv
    ofstream file_out(out_file_name, ios::trunc); 
    
    //Hacemos las inserciones
    for (int i = 0; i < n_inserts; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        std::string key = users_names[i];
        um[key] = key;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file_out << i + 1 << ", " << duration << std::endl;
    }
}

// Función que hace n_searches búsquedas y guarda la duración de cada búsqueda en un archivo CSV
void test_search(hash_table_string& hts, int n_searches, std::vector<std::string> users_names, std::string out_file_name) {
    // Creamos el archivo .csv
    std::ofstream file_out(out_file_name, std::ios::trunc);

    // Hacemos las búsquedas
    for (int i = 0; i < n_searches; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        std::string key = users_names[i];
        hts.search(key);  
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        file_out << i + 1 << ", " << duration << std::endl;
    }
}

// Misma función pero que usa un unordered_map
void test_search(std::unordered_map<std::string, std::string>& um, int n_searches, std::vector<std::string> users_names, std::string out_file_name) {
    // Creamos el archivo .csv
    std::ofstream file_out(out_file_name, std::ios::trunc);

    // Hacemos las búsquedas
    for (int i = 0; i < n_searches; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        std::string key = users_names[i];
        um.find(key);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        file_out << i + 1 << ", " << duration << std::endl;
    }
}

int main()
{
    // Ruta del archivo CSV
    // archivo sin repeticiones ni numeros en notacion cientifica
    std::string filename = "universities_followers_int64.csv";
    // Crear una instancia de CSVReader
    csv_reader csvReader(filename);

    // Extraer la tercera columna (user_name)
    vector<std::string> third_column = csvReader.extract_column(2);

    int N = 21070;
    hash_table_string ht_linear(N, linear_probing);
    hash_table_string ht_quadratic(N, quadratic_probing);
    hash_table_string ht_double(N, double_hashing);
    unordered_map<std::string, std::string> um;

    test_insert(ht_linear, N, third_column, "linear_insert_usernames.csv");
    std::cout << "Linear probing listo" << std::endl;

    test_insert(ht_quadratic, N, third_column, "quadratic_insert_usernames.csv");
    std::cout << "Quadratic probing listo" << std::endl;

    test_insert(um, N, third_column, "unorderedmap_insert_usernames.csv");
    std::cout << "Unordered_map listo" << std::endl;

    test_insert(ht_double, N, third_column, "double_insert_usernames.csv");
    std::cout << "Double hashing listo" << std::endl;

    test_search(ht_linear, N, third_column, "linear_search_usernames.csv");
    std::cout << "Search en linear listo" << std::endl;

    test_search(ht_quadratic, N, third_column, "quadratic_search_usernames.csv");
    std::cout << "Search en probing listo" << std::endl;

    test_search(um, N, third_column, "unorderedmap_search_usernames.csv");
    std::cout << "Search en unordered listo" << std::endl;

    test_search(ht_double, N, third_column, "double_search_usernames.csv");
    std::cout << "Search en double listo" << std::endl;

    return 0;
}