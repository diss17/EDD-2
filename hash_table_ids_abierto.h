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
    /**
     * @brief Metodo para calcular el tamaño de la tabla hash.
     * @return Tamaño de la tabla hash.
     */
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
    /**
     * @brief Metodo para insertar un usuario en la tabla hash.
     * @param user Usuario a insertar.
     */
    void insert(const User &user)
    {
        int hashingResult;
        hashingResult = simple_hash(user.user_id);
        table[hashingResult].push_back(user);
    }

    /**
     * @brief Metodo para buscar un usuario en la tabla hash.
     * @param user Usuario a buscar.
     * @return true si el usuario se encuentra en la tabla hash, false en caso contrario.
     */
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
