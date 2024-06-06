#ifndef USER_H
#define USER_H

#include <string>

/// @brief Estructura que representa un usuario
struct User {
    std::string university;
    unsigned long long user_id;
    std::string user_name;
    int number_tweets;
    int friends_count;
    int followers_count;
    std::string created_at;
    User() : university(""), user_id(0), user_name(""), number_tweets(0), friends_count(0), followers_count(0), created_at("") {}
};

#endif