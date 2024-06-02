#include <string>
#include "user.h"

struct hash_table_string
{
  int size;
  User *table;
  int (*hashing_method)(const std::string&, int, int);

  hash_table_string(int size, int (*hashing_method)(const std::string&, int, int)) : size(size), hashing_method(hashing_method)
  {
    table = new User[size];
    for (int i = 0; i < size; i++)
    {
      table[i] = User();
    }
  }

  void insert(const User& user)
  {
    int i = -1;
    int hashingResult;
    do{
      i++;
      hashingResult = hashing_method(user.user_name, size, i);
    }while (table[hashingResult].user_name != "");

    table[hashingResult] = user;
  }

  bool search(const User& user)
  {
    int i = 0;
    while (table[hashing_method(user.user_name, size, i)].user_name != user.user_name && table[hashing_method(user.user_name, size, i)].user_name != "")
    {
      i++;
    }
    return table[hashing_method(user.user_name, size, i)].user_name == user.user_name;
  }
};