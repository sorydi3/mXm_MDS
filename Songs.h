#pragma once
/**
@file Songs.h
@brief class Songs
*/
#include <iostream>
#include<set>
#include<list>
#include"Song.h"
#include<map>
#include<memory>
/**
@class Songs
@brief A set of songs, indexed by both tid and mXm_tid, and a list of words.
@author Ibrahima Sory Diallo
*/
class Songs {
public:

	std::shared_ptr<Song> addSong(const std::string tid,
		const std::string MSD_artist_name,
		const std::string MSD_title, const std::string mXm_tid,
		const std::string mXm_artist_name,
		const std::string mXm_title);
	/**
	@brief add song to the set of songs
	@pre there is no song with this tid and mXm_tid in this set of songs
	@post the song has been added and a shared pointer to it is returned
	*/


	bool deleteSong(const std::string id);
	/**
	@brief delete a song to the set given an id as a parameter
	@pre --
	@post the song with (tid == id ) or (mXm_tid == id) in this set has been deleted; Say if succeeded
	*/


	void addWord(const std::string s);
	/**
	@brief add world to the list of worlds
	@pre --
	@post s had been added as the last world in the list of worlds
	*/


	std::shared_ptr<Song> getSong(const std::string id) const;
	/**
	@brief return a song given and id as parametre
	@pre --
	@post if there is a song (tid ==id) or (mXm_tid == id) in this set then returns a pointer  to this song;otherwise return a nullptr
	*/

	std::set<std::pair<std::string, std::string>> songsWithWord(std::string w) const;
	/**
	@brief return the set of pairs of songs  with world w given a as parameter
	@pre --
	@post return the set of pair of songs with world w
	*/


	std::list<std::string> mostFrequentWordsIn(const std::string id) const;
	/**
	@brief returns the list of its most frequent words; otherwise it returns an empty list
	@pre --
	@post if there is a song (tid == id) or (mXm_tid == id) in this set
	then returns the list of its most frequent words; otherwise it
	returns an empty list
	*/

	std::set<std::string> mostFrequentN(ushort n) const;
	/**
	@brief return the n most frequent world in this set of songs
	@pre --
	@post  return the n most frequent words in this set of songs
	*/
private:

};