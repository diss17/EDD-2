#include <string>
#include <list>
#include "user.h"

struct hash_table_usernames_abierto {
  int size;
  std::list<User>* table;
  int (*hashing_method)(const std::string&, int, int);

  hash_table_usernames_abierto(int size, int (*hashing_method)(const std::string&, int, int))
                             : size(size), hashing_method(hashing_method) 
  {
    table = new std::list<User>[size];
  }

  void insert(const User& user) {
    int hashingResult;
    hashingResult = hashing_method(user.user_name, size, 1);
    table[hashingResult].push_back(user);
  }

  bool search(const User& user) {
    int hashingResult = hashing_method(user.user_name, size, 1);
    for (User u: table[hashingResult]) {
      if (u.user_name == user.user_name) {
        return true;
      }
    }
    return false;
  }
};
