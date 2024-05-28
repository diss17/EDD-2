/**
 * @brief Estructura que representa una tabla hash.
 */
struct hash_table
{
  int size;                                            /// Tamaño de la tabla hash.
  int *table;                                          /// Puntero al array que representa la tabla hash.
  int (*hashing_method)(unsigned long long, int, int); /// Puntero a la función de hashing.

  /**
   * @brief Constructor de la tabla hash.
   * @param size Tamaño de la tabla hash.
   * @param hashing_method Puntero a la función de hashing.
   */
  hash_table(int size, int (*hashing_method)(unsigned long long, int, int))
      : size(size), hashing_method(hashing_method)
  {
    table = new int[size];
    for (int i = 0; i < size; i++)
    {
      table[i] = -1; ///Inicializa la tabla con -1 indicando que está vacía.
    }
  }
  /**
   * @brief Inserta una clave en la tabla hash.
   * @param key clave a insertar.
   */
  void insert(unsigned long long key)
  {
    int i = -1;
    int hashingResult = 0;
    do
    {
      hashingResult = hashing_method(key, size, i);
      i++;
    } while (table[hashingResult] != -1);

    table[hashing_method(key, size, i)] = key; ///< Inserta la clave en la posición calculada.
  }

  /**
   * @brief Busca una clave en la tabla hash.
   * @param key La clave que se va a buscar.
   * @return true si la clave se encuentra en la tabla hash, false en caso contrario.
   */
  bool search(unsigned long long key)
  {
    int i = 0;
    while (table[hashing_method(key, size, i)] != key && table[hashing_method(key, size, i)] != -1)
    {
      i++;
    }
    return table[hashing_method(key, size, i)] == key; ///< Retorna true si se encuentra la clave.
  }
};
