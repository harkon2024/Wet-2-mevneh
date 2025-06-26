// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include <new>
#include "dspotify25b2.h"
#define MAX_SIZE 1744967231

DSpotify::DSpotify() {

}

DSpotify::~DSpotify() {

}

StatusType DSpotify::addGenre(int genreId) {
    if (genreId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (genre_table.is_in_array(genreId)) {
        return StatusType::FAILURE;
    }

        Genre new_genre = Genre();

    if (genre_table.get_num_elements() == MAX_SIZE) {
        return StatusType::ALLOCATION_ERROR;
    }
        genre_table.insert(genreId, new_genre);



    return StatusType::SUCCESS;
}


StatusType DSpotify::addSong(int songId, int genreId) {
    if (songId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (song_table.is_in_array(songId)) {
        return StatusType::FAILURE;
    }
    int genre_index = genre_table.find_index(genreId);
    if (!genre_table.is_present(genre_index)) {
        return StatusType::FAILURE;
    }
    Genre genre_data = genre_table.get_data(genre_index);
    Song new_song = Song();

    if (genre_data.get_song_root() == -1) {
        genre_data.change_song_root(songId);
        genre_data.increase_size();
        new_song.change_root_status(true);
        new_song.change_genre(genreId);
    } else {
        int dad_song_id = genre_data.get_song_root();
        int dad_index = song_table.find_index(dad_song_id);
        int changes_to_dad = song_table.get_num_of_changes_hash(dad_index);

        new_song.change_dad(dad_song_id);
        genre_data.increase_size();
        new_song.change_genre(genreId);
        new_song.change_num_of_changes(-changes_to_dad);
    }
    genre_table.change_data(genre_data, genre_index);

    if (song_table.get_num_elements() == MAX_SIZE) {
        return StatusType::ALLOCATION_ERROR;
    }
    song_table.insert(songId, new_song);

    return StatusType::SUCCESS;
}

StatusType DSpotify::mergeGenres(int genreId1, int genreId2, int genreId3) {
    if (genreId1 <= 0 || genreId2 <= 0 || genreId3 <= 0 ||
        genreId1 == genreId2 || genreId2 == genreId3 || genreId1 == genreId3) {
        return StatusType::INVALID_INPUT;
    }
    if ((!genre_table.is_in_array(genreId1)) ||
        (!genre_table.is_in_array(genreId2)) ||
        (genre_table.is_in_array(genreId3))) {
        return StatusType::FAILURE;
    }

        int genre_index1 = genre_table.find_index(genreId1);
        int genre_index2 = genre_table.find_index(genreId2);

        int size1 = genre_table.get_data(genre_index1).get_size();
        int size2 = genre_table.get_data(genre_index2).get_size();
        int root1 = genre_table.get_data(genre_index1).get_song_root();
        int root2 = genre_table.get_data(genre_index2).get_song_root();

        Genre new_genre3 = Genre();
        new_genre3.change_size(size1 + size2);

        if (root1 == -1 && root2 == -1) {
            if (genre_table.get_num_elements() == MAX_SIZE) {
                return StatusType::ALLOCATION_ERROR;
            }
            genre_table.insert(genreId3, new_genre3);
            return StatusType::SUCCESS;
        }

        if (root1 == -1) {
            new_genre3.change_song_root(root2);
            if (genre_table.get_num_elements() == MAX_SIZE) {
                return StatusType::ALLOCATION_ERROR;
            }
            genre_table.insert(genreId3, new_genre3);

            int root2_index = song_table.find_index(root2);
            Song root_song2 = song_table.get_data(root2_index);
            root_song2.change_genre(genreId3);
            root_song2.increase_num_of_changes();
            song_table.change_data(root_song2, root2_index);

            genre_index1 = genre_table.find_index(genreId1);
            genre_index2 = genre_table.find_index(genreId2);

            genre_table.change_data(Genre(), genre_index1);
            genre_table.change_data(Genre(), genre_index2);
            return StatusType::SUCCESS;

        }

        if (root2 == -1) {
            new_genre3.change_song_root(root1);
            if (genre_table.get_num_elements() == MAX_SIZE) {
                return StatusType::ALLOCATION_ERROR;
            }
            genre_table.insert(genreId3, new_genre3);

            int root1_index = song_table.find_index(root1);
            Song root_song1 = song_table.get_data(root1_index);
            root_song1.change_genre(genreId3);
            root_song1.increase_num_of_changes();
            song_table.change_data(root_song1, root1_index);

            genre_index1 = genre_table.find_index(genreId1);
            genre_index2 = genre_table.find_index(genreId2);

            genre_table.change_data(Genre(), genre_index1);
            genre_table.change_data(Genre(), genre_index2);
            return StatusType::SUCCESS;

        }

        int root1_index = song_table.find_index(root1);
        int root2_index = song_table.find_index(root2);

        Song song1_data = song_table.get_data(root1_index);
        Song song2_data = song_table.get_data(root2_index);

        int num_of_changes1_old = song1_data.get_num_of_changes();
        int num_of_changes2_old = song2_data.get_num_of_changes();


        if (size1 >= size2) {
            new_genre3.change_song_root(root1);

            song1_data.change_genre(genreId3);
            song1_data.change_num_of_changes(num_of_changes1_old + 1);

            song2_data.change_num_of_changes(num_of_changes2_old - num_of_changes1_old);
            song2_data.change_dad(root1);
            song2_data.change_root_status(false);

        } else {
            new_genre3.change_song_root(root2);

            song2_data.change_genre(genreId3);
            song2_data.change_num_of_changes(num_of_changes2_old + 1);

            song1_data.change_dad(root2);
            song1_data.change_root_status(false);
            song1_data.change_num_of_changes(num_of_changes1_old - num_of_changes2_old);
        }
    if (genre_table.get_num_elements() == MAX_SIZE) {
        return StatusType::ALLOCATION_ERROR;
    }
        genre_table.insert(genreId3, new_genre3);

        genre_index1 = genre_table.find_index(genreId1);
        genre_index2 = genre_table.find_index(genreId2);
        genre_table.change_data(Genre(), genre_index1);
        genre_table.change_data(Genre(), genre_index2);
        song_table.change_data(song1_data, root1_index);
        song_table.change_data(song2_data, root2_index);



    return StatusType::SUCCESS;
}

output_t<int> DSpotify::getSongGenre(int songId) {
    if (songId <= 0) {
        return {StatusType::INVALID_INPUT};
    }


    if (!song_table.is_in_array(songId)) {
        return {StatusType::FAILURE};
    }

    int song_index = song_table.find_index(songId);
    song_table.cluster_path(song_index);
    int genre = song_table.get_genre_hash(song_index);
    if(!song_table.hash_root_status(song_index)){

        genre = song_table.get_genre_hash_dad(song_index);
    }
    return {genre};
}

output_t<int> DSpotify::getNumberOfSongsByGenre(int genreId) {
    if (genreId <= 0) {
        return {StatusType::INVALID_INPUT};
    }

    int genre_index = genre_table.find_index(genreId);
    if (!genre_table.is_present(genre_index)) {
        return {StatusType::FAILURE};
    }

    Genre genre_data = genre_table.get_data(genre_index);
    return {genre_data.get_size()};
}

output_t<int> DSpotify::getNumberOfGenreChanges(int songId) {
    if (songId <= 0) {
        return {StatusType::INVALID_INPUT};
    }

    if (!song_table.is_in_array(songId)) {
        return {StatusType::FAILURE};
    }

    int song_index = song_table.find_index(songId);

    song_table.cluster_path(song_index);
    int dad_changes = 0;
    if(!song_table.hash_root_status(song_index)){
        dad_changes = song_table.get_num_of_changes__dad_hash(song_index);
    }
    int num_of_changes = song_table.get_num_of_changes_hash(song_index) + 1 + dad_changes ;
    return {num_of_changes};
}


