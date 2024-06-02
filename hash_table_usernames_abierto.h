#include <string>
#include <list>
#include "user.h"

struct hash_table_usernames_abierto {
  int size;
  std::list<User>* table;

  hash_table_usernames_abierto(int size) : size(size)
  {
    table = new std::list<User>[size];
    for (int i = 0; i < size; i++) {
      table[i] = std::list<User>();
    }
  }

  /// @brief Función de hash simplificada de Jenkins
  /// @param str Cadena a la que se le aplicará el hash
  /// @return Valor hash de la cadena
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
      return hash % size;
  }

  void insert(const User& user) {
    int hashingResult;
    hashingResult = simple_hash(user.user_name);
    table[hashingResult].push_back(user);
  }

  bool search(const User& user) {
    int hashingResult = simple_hash(user.user_name);
    for (User u: table[hashingResult]) {
      if (u.user_name == user.user_name) {
        return true;
      }
    }
    return false;
  }
};
