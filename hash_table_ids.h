#include "user.h"
#include <iostream>
/**
 * @brief Estructura que representa una tabla hash.
 */
struct hash_table_ids
{
  int size;                                            /// Tamaño de la tabla hash.
  User *table;                                         /// Puntero al array que representa la tabla hash.
  int (*hashing_method)(unsigned long long, int, int); /// Puntero a la función de hashing.

  /**
   * @brief Constructor de la tabla hash.
   * @param size Tamaño de la tabla hash.
   * @param hashing_method Puntero a la función de hashing.
   */
  hash_table_ids(int size, int (*hashing_method)(unsigned long long, int, int))
      : size(size), hashing_method(hashing_method)
  {
    table = new User[size];
    for (int i = 0; i < size; i++)
    {
      table[i] = User();
    }
  }

  /**
   * @brief Metodo para calcular el tamaño de la tabla hash.
   * @return Tamaño de la tabla hash.
   */
  size_t memory_footprint() const
  {
    size_t size_of_struct = sizeof(size) + sizeof(table) + sizeof(hashing_method);
    size_t size_of_array = sizeof(User) * size;
    return size_of_struct + size_of_array;
  }
  /**
   * @brief Inserta una clave en la tabla hash.
   * @param key clave a insertar.
   */
  void insert(const User &user)
  {
    int i = -1;
    int hashingResult = 0;
    do
    {
      hashingResult = hashing_method(user.user_id, size, i);
      i++;
    } while (table[hashingResult].user_id != 0);

    table[hashingResult] = user; ///< Inserta la clave en la posición calculada.
  }

  /**
   * @brief Busca una clave en la tabla hash.
   * @param key La clave que se va a buscar.
   * @return true si la clave se encuentra en la tabla hash, false en caso contrario.
   */
  bool search(const User &user)
  {
    int i = -1;
    int hashingResult; 
    do
    {
      i++;
      hashingResult = hashing_method(user.user_id, size, i);
      if (table[hashingResult].user_id == user.user_id)
      {
        return true;
      }
    } while (table[hashingResult].user_id != 0 && i < size);
    return false;
  }
};
