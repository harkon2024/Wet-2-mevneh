//
// Created by harry cohen on 2025-06-21.
//

#ifndef DS_WET2_SPRING_2025_GENRE_H
#define DS_WET2_SPRING_2025_GENRE_H
class Genre {
  // key  int genre_id;
    int root_song_id = -1;
    int size = 0;

public:
    Genre() = default;



    ~Genre ()= default;


    void increase_size(){
        size++;
    }

    void decrease_size(){
        size--;
    }

    void change_size(int new_size){
        size = new_size;
    }

    int get_song_root(){
        return root_song_id;
    }

    void change_song_root(int new_root_id){
        root_song_id = new_root_id;
    }

    int get_size(){
        return size;
    }


};
#endif //DS_WET2_SPRING_2025_GENRE_H
