#include <string>
#include "user.h"

struct hash_table_string
{
  int size;
  User *table;
  int (*hashing_method)(const std::string &, int, int);

  hash_table_string(int size, int (*hashing_method)(const std::string &, int, int)) : size(size), hashing_method(hashing_method)
  {
    table = new User[size];
    for (int i = 0; i < size; i++)
    {
      table[i] = User();
    }
  }
  size_t memory_footprint() const
  {
    size_t size_of_struct = sizeof(size) + sizeof(table) + sizeof(hashing_method);
    size_t size_of_array = sizeof(User) * size;
    return size_of_struct + size_of_array;
  }
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