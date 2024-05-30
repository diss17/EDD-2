#ifndef USER_H
#define USER_H

#include <string>

struct User {
    std::string university;
    unsigned long long user_id;
    std::string user_name;
    int number_tweets;
    int friends_count;
    int followers_count;
    std::string created_at;
};

#endif