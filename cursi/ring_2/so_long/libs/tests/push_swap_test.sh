#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Uso: $0 <COUNT> [<ITERATIONS>]"
    exit 1
fi

COUNT=$1

if [ $# -eq 1 ]; then
    ITERATIONS=1
else
    ITERATIONS=$2
fi

if ! [[ "$COUNT" =~ ^[1-9][0-9]*$ ]]; then
    echo "El primer argumento debe ser un número entero positivo"
    exit 1
fi

if ! [[ "$ITERATIONS" =~ ^[1-9][0-9]*$ ]]; then
    echo "El segundo argumento debe ser un número entero positivo"
    exit 1
fi

for (( i=1; i<=$ITERATIONS; i++ )); do
    ARG=$(shuf -i 1-$COUNT -n $COUNT | tr '\n' ' ')
    MOVES=$(./push_swap $ARG | wc -l)
    
    if [ "$COUNT" -eq 3 ] && [ "$MOVES" -gt 3 ]; then
        echo "$MOVES, Error: límite de 3"
    elif [ "$COUNT" -eq 5 ] && [ "$MOVES" -gt 12 ]; then
        echo "$MOVES, Error: límite de 12"
    elif [ "$COUNT" -eq 100 ] && [ "$MOVES" -gt 700 ]; then
        echo "$MOVES, Error: límite de 700"
    elif [ "$COUNT" -eq 500 ] && [ "$MOVES" -gt 5500 ]; then
        echo "$MOVES, Error: límite de 5000"
    else
        echo "$MOVES"
    fi
done

ARG="5 4 3 2 1"
./push_swap $ARG 
./push_swap $ARG | wc -l 
./push_swap $ARG | ./checker $ARG
