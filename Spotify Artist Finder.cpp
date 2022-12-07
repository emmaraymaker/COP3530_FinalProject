// Spotify Playlist Comparison.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <Windows.h>

// Iterate thtough map to find matching genres
void FindMapGenres(std::map<std::string, std::vector<std::string>> ArtistsMap, std::string& genre) {
	// Map Traversal/Search done by Emma Raymaker
	std::cout << (char)std::toupper(genre[0]) << genre.substr(1) << " Artists by Map" << std::endl;
	std::cout << "----------------------------------------" << std::endl;;
	for (std::map<std::string, std::vector<std::string> >::const_iterator ptr = ArtistsMap.begin(); ptr != ArtistsMap.end(); ptr++) {

		for (std::vector<std::string>::const_iterator ptr_2 = ptr->second.begin(); ptr_2 != ptr->second.end(); ptr_2++) {
			if (*ptr_2 == genre) {
				std::cout << ptr->first << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

void FindUnorderedGenres(std::unordered_map<std::string, std::vector<std::string>> ArtistsMap, std::string& genre) {
    // Map Traversal/Search done by Gavin Baltar
    std::cout << (char)std::toupper(genre[0]) << genre.substr(1) << " Artists by Unordered Map" << std::endl;
    std::cout << "----------------------------------------" << std::endl;;

    for (std::unordered_map<std::string, std::vector<std::string> >::const_iterator ptr = ArtistsMap.begin(); ptr != ArtistsMap.end(); ptr++) {

        for (std::vector<std::string>::const_iterator ptr_2 = ptr->second.begin(); ptr_2 != ptr->second.end(); ptr_2++) {
            if (*ptr_2 == genre) {
                std::cout << ptr->first << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

int main()
{
    std::map<std::string, std::vector<std::string>> ArtistsMap; // First data structure to be filled with Artists and their Genres 
    std::unordered_map<std::string,std::vector<std::string>> ArtistsUnordered; // Second data structure to be filled with Artists and their Genres
    // These two will be searched for Artists with the matching genres, compare their times.

    SetConsoleOutputCP(1252); // Allows accented characters
    // File Reading - by Gavin.
    // read input from csv file via spotify api, create map data structure using the Artist Name and Genre
    std::fstream inFile;
    std::string genre;


    std::cout << "Welcome to the Spotify Artist Finder! Please select a genre (please use all lower case): ";
    std::cin >> genre;

    std::cout << "Please wait as we scan the playlists for artists of the " << genre << " genre." << std::endl;

 
      
   inFile.open("track_info.csv");
	
	inFile.open("track_info.csv");
    
    if (inFile.is_open()) {
        std::string fileLine;
        std::string artistName;
        std::string artistSong;
        std::string artistAlbum;
        std::string genre;
        std::vector<std::string> artistGenres;

        std::getline(inFile, fileLine); // Gets header of csv file

        while (!inFile.eof()) {
            std::getline(inFile, fileLine, '|'); // artist id
            std::getline(inFile, fileLine, '|'); // song id
            
            // Get song name
            std::getline(inFile, fileLine, '|');
            artistSong = fileLine;
            //std::cout << artistSong << std::endl;

            // Get artist name
            std::getline(inFile, fileLine, '|');
            artistName = fileLine;
            //std::cout << artistName << std::endl;

            // Artist popularity number - not needed
            std::getline(inFile, fileLine, '|');
            //std::cout << fileLine << std::endl;
            // Song genres is from - not needed
            std::getline(inFile, fileLine, '|');
            //std::cout << fileLine << std::endl;

            std::stringstream str(fileLine);


            // Goes through genre list and adds them to vector
            while (std::getline(str, genre, ',')) {
                // Clears out the commas and ' so they aren't included in genre strings
                if (genre[0] == ' ') {
                    genre = genre.substr(1);
                }
                artistGenres.push_back(genre);
                //std::cout << genre << std::endl;
            }

             // Reaches semicolon after genre list
             std::getline(inFile, fileLine, '|');
             // Gets album song is from - not needed but stored in case we change our idea
             std::getline(inFile, fileLine, '|');
             artistAlbum = fileLine;
             //std::cout << fileLine << std::endl;
             //std::cout << std::endl;

             std::getline(inFile, fileLine); // Gets rest of the file

             ArtistsMap[artistName] = artistGenres; // Adds Artist to the map with their genre vector
             ArtistsUnordered[artistName] = artistGenres;
             artistGenres.clear(); // clears genre vector for next line/artist
        }
    }
	// Starts clock for time comparisons
    	auto start = std::chrono::high_resolution_clock::now();
    	FindMapGenres(ArtistsMap, genre);
	auto stop = std::chrono::high_resolution_clock::now();
	
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    	std::cout << duration.count() << " microseconds." << std::endl;
    	std::cout << std::endl;

    	start = std::chrono::high_resolution_clock::now();
    	FindUnorderedGenres(ArtistsUnordered, genre);
    	stop = std::chrono::high_resolution_clock::now();

    	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    	std::cout << duration.count() << " microseconds." << std::endl;
}
