struct hash_table
{
  int size;
  int *table;
  int (*hashing_method)(unsigned long long, int, int);

  hash_table(int size, int (*hashing_method)(unsigned long long, int, int)) : size(size), hashing_method(hashing_method)
  {
    table = new int[size];
    for (int i = 0; i < size; i++)
    {
      table[i] = -1;
    }
  }

  void insert(unsigned long long key)
  {
    int i = 0;
    while (table[hashing_method(key, size, i)] != -1)
    {
      i++;
    }
    table[hashing_method(key, size, i)] = key;
  }

  bool search(unsigned long long key)
  {
    unsigned long long i = 0;
    while (table[hashing_method(key, size, i)] != key && table[hashing_method(key, size, i)] != -1)
    {
      i++;
    }
    return table[hashing_method(key, size, i)] == key;
  }
};