//
// Created by harry cohen on 2025-06-21.
//

#ifndef DS_WET2_SPRING_2025_SONG_H
#define DS_WET2_SPRING_2025_SONG_H
class Song {
  // key is this if we need  int song_id;
    int genre = 0;
    int dad = -1;
    bool is_root = false;
    int num_of_changes = 0;
public:
    Song() = default;

    ~Song ()= default;

    void change_genre(int new_genre){
       genre = new_genre;
    }
    int get_genre(){
        return genre;
    }

    void change_root_status(bool new_status){
        is_root = new_status;
    }

    void change_dad(int new_dad){
        dad = new_dad;
    }

    void change_num_of_changes(int new_num){
        num_of_changes = new_num;
    }

    void increase_num_of_changes(){
        num_of_changes++;
    }

    int get_dad(){
        return dad;
    }
    int get_num_of_changes(){
        return num_of_changes;
    }
    bool root_status(){
        return is_root;
    }




};



#endif //DS_WET2_SPRING_2025_SONG_H
