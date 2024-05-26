#include <iostream>
#include "csv_reader.cpp"
#include <unordered_map>
#include <chrono>
#include <math.h>
#include "hash_table.h"

using namespace std;

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
    llenar_csv("linear_insert.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_quadratic.insert(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("quadratic_insert.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_double.insert(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("doblehashing_insert.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        um[num] = num;
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("unorderedmap_insert.csv", n, duration);

///////////BUSQUEDAS/////////////////////////////////////

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_linear.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("linear_search.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_quadratic.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("quadratic_search.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        ht_double.search(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("doblehashing_search.csv", n, duration);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        unsigned long long num = id_column[i];
        um.find(num);
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    llenar_csv("unorderedmap_search.csv", n, duration);
    return 0;
}