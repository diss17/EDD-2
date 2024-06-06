#include <string>
#include "user.h"

/// @brief Estructura que representa una tabla hash con hashing cerrado
struct hash_table_string
{
  int size;
  User *table;
  int (*hashing_method)(const std::string &, int, int);

  /// @brief Constructor de la tabla hash.
  /// @param size tamaño de la tabla hash.
  /// @param hashing_method metodo de hashing cerrado.
  hash_table_string(int size, int (*hashing_method)(const std::string &, int, int)) : size(size), hashing_method(hashing_method)
  {
    table = new User[size];
    for (int i = 0; i < size; i++)
    {
      table[i] = User();
    }
  }

  /// @brief Metodo para calcular el tamaño de la tabla hash
  size_t memory_footprint() const
  {
    size_t size_of_struct = sizeof(size) + sizeof(table) + sizeof(hashing_method);
    size_t size_of_array = sizeof(User) * size;
    return size_of_struct + size_of_array;
  }

  /// @brief Metodo para insertar un usuario en la tabla hash
  /// @param user usuario a insertar
  void insert(const User &user)
  {
    int i = -1;
    int hashingResult;
    do
    {
      i++;
      hashingResult = hashing_method(user.user_name, size, i);
    } while (table[hashingResult].user_name != "");

    table[hashingResult] = user;
  }

  /// @brief Metodo para buscar un usuario en la tabla hash
  /// @param user usuario a buscar
  /// @return true si el usuario se encuentra en la tabla hash, false en caso contrario
  bool search(const User &user)
  {
    int i = -1;
    int hashingResult;
    do
    {
      i++;
      hashingResult = hashing_method(user.user_name, size, i);
      if (table[hashingResult].user_name == user.user_name)
      {
        return true;
      }
    } while (table[hashingResult].user_name != "" && i < size);
    return false;
  }
};