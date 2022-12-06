import csv
import os
import re
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials

cid='d72a125df9364ce6b1f9ab9d3a2a86f0'
secret='48ea891fe3ca4a1f86b8bf3978bb5681'

#Authentication
client_credentials_manager = SpotifyClientCredentials(client_id=cid, client_secret=secret)
sp = spotipy.Spotify(client_credentials_manager = client_credentials_manager)

playlist_link = "https://open.spotify.com/playlist/37i9dQZEVXbNG2KDcFcKOF?si=1333723a6eff4b7f"
playlist_URI = playlist_link.split("/")[-1].split("?")[0]
track_uris = [x["track"]["uri"] for x in sp.playlist_tracks(playlist_URI)["items"]]
OUTPUT_FILE_NAME = "track_info.csv"

with open(OUTPUT_FILE_NAME, "w", encoding="utf-8") as file:
    writer = csv.writer(file)
    writer.writerow(["track name", "artist name", "artist popularity", "artist genres", "album name", "track popularity","audio features"])
    for track in sp.playlist_tracks(playlist_URI)["items"]:
        # URI
        track_uri = track["track"]["uri"]

        # Track name
        track_name = track["track"]["name"]

        # Main Artist
        artist_uri = track["track"]["artists"][0]["uri"]
        artist_info = sp.artist(artist_uri)

        # Name, popularity, genre
        artist_name = track["track"]["artists"][0]["name"]
        artist_pop = artist_info["popularity"]
        artist_genres = artist_info["genres"]

        # Album
        album_name = track["track"]["album"]["name"]

        # Popularity of the track
        track_pop = track["track"]["popularity"]

        sp.audio_features(track_uri)[0]

        writer.writerow([track_name, artist_name, artist_pop, artist_genres, album_name, track_pop, sp.audio_features(track_uri)[0]])