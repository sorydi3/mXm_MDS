#pragma once
#include<iostream>
#include<list>
#include<map>
#include<list>
typedef int ushort;
/**
@file Song.h
@bried class Song
@authore Ibrahima Sory Diallo
*/
class Song
{
public:
	Song(std::string tid, std::string MSD_artist_name, std::string MSD_title, std::string mXm_tid, std::string mXm_artist_name, std::string mXm_title);
	void addWord(ushort idx, ushort cnt);//pre:there is no word with index idx in this song //pos:the pair<idx,cnt> has been added to the map of words of this song
	ushort count(ushort idx)const;//pre:--;//post:says wich is the count for index idx
	std::list<ushort> mostFrequentWordsIdxs()const;//pre:-- //post:returns the indices of the most frequents words in this song
	~Song();
private:
	std::string _tid;
	std::string _MSD_artist_name;
	std::string _MSD_title;
	std::string _mXm_tid;
	std::string _mXm_artist_name;
	std::string _mXm_title;
	std::map<ushort, ushort> _words;

};
