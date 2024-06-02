#include <list>
#include <vector>
#include "user.h"
/**
 * @brief Estructura que representa una tabla hash con el metodo de hashing abierto.
 */
struct hash_table_ids_abierto
{
    int size;               /// Tamaño de la tabla hash.
    std::list<User> *table; /// Vector de listas que representa la tabla hash./// Puntero a la función de hashing.

    hash_table_ids_abierto(int size) : size(size)
    {
        table = new std::list<User>[size];
        for (int i = 0; i < size; i++)
        {
            table[i] = std::list<User>();
        }
    }
    /**
     * @brief Ejemplo de función de hashing.
     * @param key Clave a hashear.
     * @param size Tamaño de la tabla hash.
     * @return Resultado del hash.
     */
    unsigned long long simple_hash(unsigned long long key)
    {
        return key % size;
    }

    void insert(const User &user)
    {
        int hashingResult;
        hashingResult = simple_hash(user.user_id);
        table[hashingResult].push_back(user);
    }

    bool search(const User &user)
    {
        int hashingResult = simple_hash(user.user_id);
        for (User u : table[hashingResult])
        {
            if (u.user_id == user.user_id)
            {
                return true;
            }
        }
        return false;
    }
};
