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
unsigned long long h3(const string &k)
{
    unsigned long long hash_num = 5381;
    for (unsigned char c : k)
    {
        hash_num = ((hash_num << 5) + hash_num) + c; // hash * 33 + c
    }
    return hash_num;
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
    vector<unsigned long long> id_column = csvReader.extract_column_as_ull(1);
    vector<string> name_column = csvReader.extract_column(2);
    vector<unsigned long long> names;
    // Se recorre el vector con todos los usernames del data set y se les aplica la funcion hash que los convierte
    // en un valor del tipo unsigned long long, para luego compactarlos e insertarlos en la tabla
    for (int i = 0; i < name_column.size(); i++)
    {
        unsigned long long num = h3(name_column[i]);
        names.push_back(num);
    }

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

    ofstream file("quadratic_insertnames.csv");
    for (int i = 0; i < names.size(); i++)
    {
        unsigned long long num = names[i];
        auto start = chrono::high_resolution_clock::now();
        ht_quadratic.insert(num);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        file << i + 1 << ", " << duration << "\n";
    }
    file.close();
    cout << "listo" << endl;
    /*     for (int i = 0; i < id_column.size(); i++)
        {
            unsigned long long num = id_column[i];
            auto start = chrono::high_resolution_clock::now();
            ht_linear.insert(num);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            file << i + 1 << ", " << duration << "\n";
        }
        file.close();
        std::cout << "Linear probing listo" << std::endl;

        file.open("quadratic_insert.csv");
        for (int i = 0; i < id_column.size(); i++)
        {
            unsigned long long num = id_column[i];
            auto start = chrono::high_resolution_clock::now();
            ht_quadratic.insert(num);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            file << i + 1 << ", " << duration << "\n";
        }
        file.close();
        std::cout << "quadratic probing listo" << std::endl;

        file.open("unorderedmap_insert.csv");
        for (int i = 0; i < id_column.size(); i++)
        {
            unsigned long long num = id_column[i];
            auto start = chrono::high_resolution_clock::now();
            um[num] = num;
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            file << i + 1 << ", " << duration << "\n";
        }
        file.close();
        std::cout << "unordered_map listo" << std::endl;

        file.open("double_insert.csv");
        for (int i = 0; i < id_column.size(); i++)
        {
            unsigned long long num = id_column[i];
            auto start = chrono::high_resolution_clock::now();
            ht_double.insert(num);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            file << i + 1 << ", " << duration << "\n";
        }
        file.close();
        std::cout << "double hashing listo" << std::endl; */

    return 0;
}