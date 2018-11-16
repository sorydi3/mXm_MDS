#include"pch.h"
#include "Song.h"
#include<iostream>
Song::Song(std::string tid, std::string MSD_artist_name, std::string MSD_title, std::string mXm_tid, std::string mXm_artist_name, std::string mXm_title)
{
	_tid = tid;
	_MSD_artist_name = MSD_artist_name;
	_MSD_title = MSD_title;
	_mXm_tid = mXm_tid;
	_mXm_artist_name = mXm_artist_name;
	_mXm_title = mXm_title;
}

void Song::addWord(ushort idx, ushort cnt)
{
	std::map<ushort, ushort>::iterator it = _words.begin();//insercion with hint position
	_words.insert(std::pair<ushort, ushort>(idx, cnt));//inserting in map
}

ushort Song::count(ushort idx) const
{
	//std::map<ushort, ushort>::iterator ret;
	auto ret = _words.find(idx);
	if (ret != _words.end()) {
		return ret->second;
	}
	else return 0;
}

std::list<ushort> Song::mostFrequentWordsIdxs() const
{
	//std::map<ushort, ushort>::reverse_iterator r_it;
	std::list<ushort> most_frq_wrd;
	for (auto r_it = _words.rbegin(); r_it != _words.rend(); r_it++) {
		most_frq_wrd.push_front(r_it->first);
	}
	return most_frq_wrd;
}


Song::~Song()
{
	//not needed yet ;
}
