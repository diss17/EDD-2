#include <iostream>
#include "csv_reader.cpp"
#include <unordered_map>
#include <chrono>
#include <math.h>
#include "hash_table.h"

using namespace std;

float A = (sqrt(5) - 1) / 2;

int h1(unsigned long long k, int n)
{
    return k % n;
}

int h2(unsigned long long k, int n)
{
    float a = (float)k * A;
    a -= (int)a;
    return n * a;
}

int linear_probing(unsigned long long k, int n, int i)
{
    return (h1(k, n) + i) % n;
}

int quadratic_probing(unsigned long long k, int n, int i)
{
    return (h1(k, n) + i + 2 * i * i) % n;
}

int double_hashing(unsigned long long k, int n, int i)
{
    return (h1(k, n) + i * (h2(k, n) + 1)) % n;
}
int main()
{
    // Ruta del archivo CSV
    string filename = "universities_followers_int64.csv";
    // Crear una instancia de CSVReader
    csv_reader csvReader(filename);

    // Extraer la segunda columna
    vector<unsigned long long> second_column = csvReader.extract_column_as_ull(1);

    // Imprimir la segunda columna para verificar el resultado
    //  for (const auto &value : second_column)
    //  {
    //      cout << value << endl;
    //      count++;
    //  }
    //  cout << count << endl;

    int N = 100000;
    hash_table ht_linear(N, linear_probing);
    hash_table ht_quadratic(N, quadratic_probing);
    hash_table ht_double(N, double_hashing);
    unordered_map<int, int> um;

    ofstream file("a.csv");
    file.open("unordered_map_insert.csv");
    for (int i = 0; i < second_column.size(); i++)
    {
        unsigned long long num = second_column[i];
        auto start = chrono::high_resolution_clock::now();
        um[num] = num;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file << i + 1 << ", " << duration << "\n";
    }
    file.close();
    std::cout << "unordered_map listo" << std::endl;
    // for (int64_t i = 0; i < second_column.size(); i++)
    // {
    //     unsigned long long num = second_column[i];
    //     auto start = chrono::high_resolution_clock::now();
    //     ht_linear.insert(num);
    //     auto end = chrono::high_resolution_clock::now();
    //     auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //     file << i + 1 << ", " << duration << "\n";
    // }
    // file.close();
    // std::cout << "Linear probing listo" << std::endl;

    // // Search in ht_linear
    // file.open("linear_search.csv");
    // for (int i = 10; i <= 15; i++)
    // {
    //     for (int j = pow(2, i); j < pow(2, i + 1); j++)
    //     {
    //         auto start = chrono::high_resolution_clock::now();
    //         ht_linear.search(j);
    //         auto end = chrono::high_resolution_clock::now();
    //         auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //         file << j << ", " << duration << "\n";
    //     }
    // }
    // file.close();
    // std::cout << "linear busqueda listo" << std::endl;

    // file.open("quadratic_insert.csv");
    // for (int i = 0; i < second_column.size(); i++)
    // {
    //     unsigned long long num = second_column[i];
    //     auto start = chrono::high_resolution_clock::now();
    //     ht_quadratic.insert(num);
    //     auto end = chrono::high_resolution_clock::now();
    //     auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //     file << i + 1 << ", " << duration << "\n";
    // }
    // file.close();
    // std::cout << "quadratic probing listo" << std::endl;

    return 0;
}
