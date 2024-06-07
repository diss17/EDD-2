#!/bin/bash

g++ hashing_usernames.cpp -o hashing_usernames
g++ main_ids.cpp -o main_ids

quantities=(1000 2500 5000 7500 10000 12500 15000 17500 20000 21070)

executable="./main_ids"
executable1="./hashing_usernames"

for i in {1..1}
do
    echo "Running test $i"
    for n in "${quantities[@]}"
    do
        $executable $n
        $executable1 $n
    done
done

echo "Pruebas completadas"
