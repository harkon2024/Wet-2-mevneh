//
// Created by harry cohen on 2025-06-23.
//

#ifndef DS_WET2_SPRING_2025_PRIME_ARRAY_H
#define DS_WET2_SPRING_2025_PRIME_ARRAY_H
class PrimeArray {
public:
    static const int PRIME_COUNT = 28;


    inline static const int primes[PRIME_COUNT] = {
            17, 37, 73, 149, 293, 593, 1187, 2371,
            4751, 9533, 19013, 38053, 76109, 152219, 304433, 608861,
            1217723, 2435477, 4870979, 9741983, 19483991, 38967947, 77935993, 155871991,
            311743991, 623487977, 1246975969, 1744967231
    };

    static int get_prime(int index) {
        if (index < 0 || index >= PRIME_COUNT) return -1;
        return primes[index];
    }
};
#endif //DS_WET2_SPRING_2025_PRIME_ARRAY_H
