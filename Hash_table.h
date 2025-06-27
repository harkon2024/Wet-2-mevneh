//
// Created by harry cohen on 2025-06-21.
//

#ifndef DS_WET2_SPRING_2025_HASH_TABLE_H
#define DS_WET2_SPRING_2025_HASH_TABLE_H

#include "Song.h"
#include "Genre.h"
#include "Prime_array.h"

template<typename T>
class Hash_table {
private:
    struct Cell {
        int key = 0;
        T data;
        bool present = false;

    };

    int prime_index = 0;
    Cell *array = nullptr;
    int num_elements = 0;
    int array_size = 0;
    float size_percent = 0.7;
    PrimeArray prime_array;

public:
    Hash_table() {
        array_size = prime_array.get_prime(prime_index);
        array = new Cell[array_size];
        for (int i = 0; i < array_size; ++i) {
            array[i].present = false;
            array[i].key = 0;
        }
    }

    ~Hash_table() {
        delete[] array;

    }


    int find_index(int x) {
        int base = hash1(x);
        int step = hash2(x);
        int index = base;
        int k = 0;

        while (array[index].present && array[index].key != x) {
            index = (base + k * step) % array_size;
            ++k;
        }
        return index;
    }

    int hash1(int x) {
        return x % array_size;
    }

    int hash2(int x) {
        return 1 + (x % (array_size - 1));
    }

    int insert(int key, const T &data) {
        if (float(num_elements + 1) / array_size >= size_percent) {
            if (array_size == 1744967231) {
                size_percent = 1.0f;
            }
           else{
               resize();
           }
        }
        int index = find_index(key);
        array[index].key = key;
        array[index].data = data;
        array[index].present = true;
        num_elements++;

        return index;
    }


    void resize() {
        prime_index++;
        int new_array_size = prime_array.get_prime(prime_index);

        Cell *old_array = array;
        int old_size = array_size;

        array = new Cell[new_array_size];
        array_size = new_array_size;
        num_elements = 0;

        for (int i = 0; i < array_size; ++i) {
            array[i].present = false;
        }

        for (int i = 0; i < old_size; ++i) {
            if (old_array[i].present) {
                insert(old_array[i].key, old_array[i].data);
            }
        }

        delete[] old_array;
    }

    bool is_present(int index) {
        return array[index].present;
    }

    void change_key(int new_key, int index) {
        array[index].key = new_key;
    }

    void change_data(const T &new_data, int index) {
        array[index].data = new_data;
    }

    void change_status(bool new_status, int index) {
        array[index].present = new_status;
    }

    bool is_in_array(int key) {
        int index = find_index(key);
        return is_present(index);
    }

    T get_data(int index) {
        return array[index].data;
    }


    void cluster_path(int index) {
        if (array[index].data.root_status()) {
            return;
        }
        int dad_id = array[index].data.get_dad();
        int dad_index = find_index(dad_id);

        if (array[dad_index].data.root_status()) {
            return;
        }
        int sum = 0;
        int sub = 0;
        int num_of_changes_current = 0;
        int root_id = 0;

        find_sum_recursive(index, sum, root_id);

        int current_index = index;
        while (!array[current_index].data.root_status()) {
            int dad_id = array[current_index].data.get_dad();
            array[current_index].data.change_dad(root_id);
            num_of_changes_current = array[current_index].data.get_num_of_changes();

            array[current_index].data.change_num_of_changes(sum - sub);
            sub += num_of_changes_current;

            current_index = find_index(dad_id);
        }
    }

    void find_sum_recursive(int index, int &sum, int &root_id) {
        if (array[index].data.root_status()) {
            root_id = array[index].key;
            return;
        }
        int num_of_changes_current = array[index].data.get_num_of_changes();
        sum += num_of_changes_current;
        int dad_id = array[index].data.get_dad();
        int dad_index = find_index(dad_id);
        return find_sum_recursive(dad_index, sum, root_id);

    }

    int get_num_of_changes_hash(int index) {
        return array[index].data.get_num_of_changes();
    }

    int get_num_of_changes__dad_hash(int index) {
        int dad_id = array[index].data.get_dad();
        int dad_index = find_index(dad_id);
        return array[dad_index].data.get_num_of_changes();
    }

    int get_genre_hash(int index) {
        return array[index].data.get_genre();
    }

    int get_genre_hash_dad(int index) {
        int dad_id = array[index].data.get_dad();
        int dad_index = find_index(dad_id);
        return array[dad_index].data.get_genre();
    }

    bool hash_root_status(int index) {
        return array[index].data.root_status();
    }

    int get_song_root_hash(int genre_id) {
        int index = find_index(genre_id);
        return array[index].data.get_song_root();
    }

  int  get_num_elements(){
        return num_elements;
    }

};


#endif //DS_WET2_SPRING_2025_HASH_TABLE_H
