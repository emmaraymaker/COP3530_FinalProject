// Spotify Playlist Comparison.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <Windows.h>

int main()
{
    std::map<std::string, std::vector<std::string>> ArtistsMap; // First data structure to be filled with Artists and their Genres 
    std::unordered_map<std::string, std::vector<std::string>> ArtistsUnordered; // Second data structure to be filled with Artists and their Genres
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

    if (inFile.is_open()) {
        std::string fileLine;
        std::string artistName;
        std::string artistSong;
        std::string artistAlbum;
        std::string genre;
        std::vector<std::string> artistGenres;
        
        std::getline(inFile, fileLine); // Gets header of csv file

        while (!inFile.eof()) {
            // Get song name
            std::getline(inFile, fileLine, ';');
            artistSong = fileLine;
            std::cout << artistSong << std::endl;
            
            // Get artist name
            std::getline(inFile, fileLine, ';');
            artistName = fileLine;
            std::cout << artistName << std::endl;

            // Artist popularity number - not needed
            std::getline(inFile, fileLine, ';');
            std::cout << fileLine << std::endl;
            // Song genres is from - not needed
            std::getline(inFile, fileLine, '[');
            std::getline(inFile, fileLine, ']');
           // std::cout << fileLine << std::endl;

            std::stringstream str(fileLine);

            std::getline(str, genre, '\''); // Gets 1st ' from genre list.


            // Goes through genre list and adds them to vector
            while (std::getline(str, genre, '\'')) {
                // Clears out the commas and ' so they aren't included in genre strings
                if (genre == ", ") {
                    continue;
                }
                artistGenres.push_back(genre);
                std::cout << genre << std::endl;
            }

            // Reaches semicolon after genre list
            std::getline(inFile, fileLine, ';'); 
            // Gets album song is from - not needed but stored in case we change our idea
            std::getline(inFile, fileLine, ';');
            artistAlbum = fileLine;
            std::cout << fileLine << std::endl;
            std::cout << std::endl;

            std::getline(inFile, fileLine); // Gets rest of the file

            ArtistsMap[artistName] = artistGenres; // Adds Artist to the map with their genre vector
            ArtistsUnordered[artistName] = artistGenres;
            artistGenres.clear(); // clears genre vector for next line/artist
        }
    }
    
}