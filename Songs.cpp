#include "pch.h"
#include "Songs.h"
/**
@file Songs.h
@brief class Songs
*/

/**
@class Songs
@brief A set of songs, indexed by both tid and mXm_tid, and a list of words.
@author Ibrahima Sory Diallo
*/
std::shared_ptr<Song> Songs::addSong(const std::string tid, const std::string MSD_artist_name,
	const std::string MSD_title, const std::string mXm_tid, const std::string mXm_artist_name, const std::string mXm_title)
{
	Song song(tid, MSD_artist_name, MSD_title, mXm_tid, mXm_artist_name, mXm_title);
	std::shared_ptr<Song> sharedSong =std::make_shared<Song>(song);
	_mapSongsO.insert(std::make_pair(mXm_tid, sharedSong));
	_mapSongs.insert(std::make_pair(tid, sharedSong));
	return std::shared_ptr<Song>(sharedSong);
}

bool Songs::deleteSong(const std::string id)
{

	return false;
}

void Songs::addWord(const std::string s)
{
	_vWords.push_back(s);
}

std::shared_ptr<Song> Songs::getSong(const std::string id) const
{ 

	return std::shared_ptr<Song>();
}

std::set<std::pair<std::string, std::string>> Songs::songsWithWord(std::string w) const
{
	return std::set<std::pair<std::string, std::string>>();
}

std::list<std::string> Songs::mostFrequentWordsIn(const std::string id) const
{
	return std::list<std::string>();
}

std::set<std::string> Songs::themostFrequentN(ushort n) const
{
	return std::set<std::string>();
}
