#include <string>
#include <list>
#include "user.h"

/// @brief Estructura que representa una tabla hash con hashing abierto
struct hash_table_usernames_abierto
{
  int size;
  std::list<User> *table;

  /// @brief Constructor de la tabla hash.
  /// @param size tamaño de la tabla hash.
  hash_table_usernames_abierto(int size) : size(size)
  {
    table = new std::list<User>[size];
    for (int i = 0; i < size; i++)
    {
      table[i] = std::list<User>();
    }
  }

  /// @brief Función de hash simplificada de Jenkins
  /// @param str Cadena a la que se le aplicará el hash
  /// @return Valor hash de la cadena
  unsigned long long simple_hash(const std::string &str)
  {
    unsigned long long hash = 0;
    for (char c : str)
    {
      hash += static_cast<unsigned long long>(c);
      hash += (hash << 10);
      hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % size;
  }

  /// @brief Metodo para calcular el tamaño de la tabla hash

  size_t memory_footprint() const
  {
    size_t size_of_struct = sizeof(size) + sizeof(table);
    size_t size_of_lists = 0;

    for (int i = 0; i < size; ++i)
    {
      // Overhead of the list structure itself
      size_of_lists += sizeof(std::list<User>);
      // Add the size of each element in the list
      for (const User &user : table[i])
      {
        size_of_lists += sizeof(user);
      }
    }
    return size_of_struct + size_of_lists;
  }

  /// @brief Metodo para insertar un usuario en la tabla hash
  /// @param user usuario a insertar
  void insert(const User &user)
  {
    int hashingResult;
    hashingResult = simple_hash(user.user_name);
    table[hashingResult].push_back(user);
  }

  /// @brief Metodo para buscar un usuario en la tabla hash
  /// @param user usuario a buscar
  /// @return true si el usuario se encuentra en la tabla hash, false en caso contrario
  bool search(const User &user)
  {
    int hashingResult = simple_hash(user.user_name);
    for (User u : table[hashingResult])
    {
      if (u.user_name == user.user_name)
      {
        return true;
      }
    }
    return false;
  }
};
