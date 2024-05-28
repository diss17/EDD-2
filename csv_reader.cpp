#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Clase para leer archivos CSV y manipular su contenido.
 */
class csv_reader
{
public:
    /**
     * @brief Constructor que inicializa el lector CSV con el nombre del archivo.
     * @param filename Nombre del archivo CSV.
     */
    csv_reader(const string &filename) : filename(filename) {}

    /**
     * @brief Lee el archivo CSV y lo convierte en una matriz s.
     * @return Una matriz de vectores que representa el contenido del CSV.
     */
    vector<vector<string>> read_csv_to_matrix()
    {
        ifstream file(filename);
        vector<vector<string>> matrix;
        string line, word;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                stringstream s(line);
                vector<string> row;
                while (getline(s, word, ','))
                {
                    row.push_back(trim(word));
                }
                matrix.push_back(row);
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file " << filename << endl;
        }

        return matrix;
    }

    /**
     * @brief Extrae una columna específica del CSV.
     * @param column_index Índice de la columna a extraer.
     * @return Un vector de cadenas que representa la columna extraída.
     */
    vector<string> extract_column(int column_index)
    {
        vector<vector<string>> matrix = read_csv_to_matrix();
        vector<string> column;
        for (size_t i = 1; i < matrix.size(); ++i)
        { // Empieza desde 1 para saltar la cabecera
            if (matrix[i].size() > column_index)
            { // Asegurarse de que hay suficientes columnas
                column.push_back(matrix[i][column_index]);
            }
            else
            {
                cerr << "Fila " << i << " no tiene suficientes columnas." << endl;
            }
        }
        return column;
    }

    /**
     * @brief Extrae una columna específica del CSV y la convierte a unsigned long long dado que el dataset posee numero gigantes.
     * @param column_index Índice de la columna a extraer.
     * @return Un vector de unsigned long long que representa la columna extraída.
     */
    vector<unsigned long long> extract_column_as_ull(int column_index)
    {
        vector<vector<string>> matrix = read_csv_to_matrix();
        vector<unsigned long long> column;
        for (size_t i = 1; i < matrix.size(); ++i)
        { // Empieza desde 1 para saltar la cabecera
            if (matrix[i].size() > column_index)
            { // Asegurarse de que hay suficientes columnas
                try
                {
                    column.push_back(stoull(matrix[i][column_index])); // Convertir a unsigned long long
                }
                catch (const invalid_argument &e)
                {
                    cerr << "Error de conversión en la fila " << i << ": " << matrix[i][column_index] << " no es un número válido." << endl;
                }
                catch (const out_of_range &e)
                {
                    cerr << "Error de rango en la fila " << i << ": " << matrix[i][column_index] << " está fuera del rango de unsigned long long." << endl;
                }
            }
            else
            {
                cerr << "Fila " << i << " no tiene suficientes columnas." << endl;
            }
        }
        return column;
    }

private:
    string filename; ///Nombre del archivo CSV.

    /**
     * @brief Elimina los espacios en blanco al inicio y al final de una cadena.
     * @param str La cadena a recortar.
     * @return La cadena recortada.
     */
    string trim(const string &str)
    {
        size_t first = str.find_first_not_of(' ');
        if (first == string::npos)
            return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, last - first + 1);
    }
};