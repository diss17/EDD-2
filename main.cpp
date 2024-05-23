#include <iostream>
#include "csv_reader.cpp"
#include <unordered_map>
#include <chrono>
#include <math.h>
#include "hash_table.h"

float A = (sqrt(5) - 1) / 2;

unsigned long long h1(unsigned long long k, int n)
{
    return k % n;
}

unsigned long long h2(unsigned long long k, int n)
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

using namespace std;
int main()
{
    // Ruta del archivo CSV
    // archivo sin repeticiones ni numeros en notacion cientifica
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

    int N = 21070;
    hash_table ht_linear(N, linear_probing);
    hash_table ht_quadratic(N, quadratic_probing);
    hash_table ht_double(N, double_hashing);
    unordered_map<int, int> um;

    ofstream file("linear_insert.csv");
    for (int i = 0; i < second_column.size(); i++)
    {
        unsigned long long num = second_column[i];
        auto start = chrono::high_resolution_clock::now();
        ht_linear.insert(num);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file << i + 1 << ", " << duration << "\n";
    }
    file.close();
    std::cout << "Linear probing listo" << std::endl;

    file.open("quadratic_insert.csv");
    for (int i = 0; i < second_column.size(); i++)
    {
        unsigned long long num = second_column[i];
        auto start = chrono::high_resolution_clock::now();
        ht_quadratic.insert(num);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file << i + 1 << ", " << duration << "\n";
    }
    file.close();
    std::cout << "quadratic probing listo" << std::endl;

    file.open("unorderedmap_insert.csv");
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

    file.open("double_insert.csv");
    for (int i = 0; i < second_column.size(); i++)
    {
        unsigned long long num = second_column[i];
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