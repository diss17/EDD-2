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

unsigned long long h1(const std::string& k, int n) {
    unsigned long long hash = simple_hash(k);
    return hash % n;
}

unsigned long long h2(const std::string& k, int n) {
    // Utilizamos una constante A como factor de hashing
    const float A = 0.61803398875; // Phi, número áureo
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

using namespace std;
int main()
{
    // Ruta del archivo CSV
    // archivo sin repeticiones ni numeros en notacion cientifica
    string filename = "universities_followers_int64.csv";
    // Crear una instancia de CSVReader
    csv_reader csvReader(filename);

    // Extraer la segunda columna
    vector<std::string> third_column = csvReader.extract_column(2);

    // Imprimir la segunda columna para verificar el resultado
    //  for (const auto &value : second_column)
    //  {
    //      cout << value << endl;
    //      count++;
    //  }
    //  cout << count << endl;

    int N = 21070;
    hash_table_string ht_linear(N, linear_probing);
    hash_table_string ht_quadratic(N, quadratic_probing);
    hash_table_string ht_double(N, double_hashing);
    unordered_map<std::string, std::string> um;

    ofstream file("linear_insert.csv");
    for (int i = 0; i < third_column.size(); i++)
    {
        const std::string num = third_column[i];
        auto start = chrono::high_resolution_clock::now();
        ht_linear.insert(num);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file << i + 1 << ", " << duration << "\n";
    }
    file.close();
    std::cout << "Linear probing listo" << std::endl;

    file.open("quadratic_insert.csv");
    for (int i = 0; i < third_column.size(); i++)
    {
        const std::string num = third_column[i];
        auto start = chrono::high_resolution_clock::now();
        ht_quadratic.insert(num);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file << i + 1 << ", " << duration << "\n";
    }
    file.close();
    std::cout << "quadratic probing listo" << std::endl;

    file.open("unorderedmap_insert.csv");
    for (int i = 0; i < third_column.size(); i++)
    {
        const std::string num = third_column[i];
        auto start = chrono::high_resolution_clock::now();
        um[num] = num;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file << i + 1 << ", " << duration << "\n";
    }
    file.close();
    std::cout << "unordered_map listo" << std::endl;

    file.open("double_insert.csv");
    for (int i = 0; i < third_column.size(); i++)
    {
        const std::string num = third_column[i];
        auto start = chrono::high_resolution_clock::now();
        ht_double.insert(num);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file << i + 1 << ", " << duration << "\n";
    }
    file.close();
    std::cout << "double hashing listo" << std::endl;

    return 0;
}