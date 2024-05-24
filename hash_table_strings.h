#include <string>
struct hash_table_string
{
  int size;
  std::string *table;
  int (*hashing_method)(const std::string&, int, int);

  hash_table_string(int size, int (*hashing_method)(const std::string&, int, int)) : size(size), hashing_method(hashing_method)
  {
    table = new std::string[size];
    for (int i = 0; i < size; i++)
    {
      table[i] = "";
    }
  }

  void insert(const std::string& key)
  {
    int i = -1;
    int hasingResult = 0;
    do{
      hasingResult = hashing_method(key, size, i);
      i++;
    }while (table[hasingResult] != "");

    table[hashing_method(key, size, i)] = key;
  }

  bool search(const std::string& key)
  {
    unsigned long long i = 0;
    while (table[hashing_method(key, size, i)] != key && table[hashing_method(key, size, i)] != "")
    {
      i++;
    }
    return table[hashing_method(key, size, i)] == key;
  }
};