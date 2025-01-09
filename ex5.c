/******************
Name: Shira Cababia
ID:
Assignment: ex5
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WATCH_PLAYLISTS 1
#define ADD_PLAYLIST 2
#define REMOVE_PLAYLIST 3
#define EXIT_OPTION 4
#define SHOW_PLAYLIST 1
#define ADD_SONG 2
#define DELETE_SONG 3
#define SORT_PLAYLIST 4
#define PLAY_PLAYLIST 5
#define EXIT_PLAYLIST_OPTION 6
#define SORT_BY_YEAR 1
#define SORT_BY_STREAMS_ASCENDING 2
#define SORT_BY_STREAMS_DESCENDING 3

typedef struct Song
{
    char *title;
    char *artist;
    int year;
    char *lyrics;
    int streams;
} Song;

typedef struct Playlist
{
    char *name;
    Song **songs;
    int songsNum;
} Playlist;

int main();
void printMenu();
char *getString();
void printPlaylistMenu();
void printAllPlaylists(Playlist **playlistsArr, int playlistsArrLength);
int optionsForPlaylist(Playlist **playlistsArr, int playlistIndx);
void printSongsList(Playlist **playlistsArr, int playlistIndx);
void playSong(Playlist **playlistsArr, int playlistIndx, int songIndx);
void sortPlaylist(Playlist **playlistsArr, int playlistIndx, int sortOption);
void deleteSong(Playlist **playlistsArr, int playlistIndx, int songIndx);
void freeSong(Playlist **playlistsArr, int playlistIndx, int songIndx);
void removePlaylist(Playlist ***playlistsArr, int playlistIndx, int *playlistsArrLength);
void freePlaylist(Playlist **playlistsArr, int playlistIndx);

int main()
{
    printMenu();
    Playlist **playlistsArr = NULL;
    int playlistsArrLength = 0;
    int choice;
    scanf("%d", &choice);
    while (choice != EXIT_OPTION)
    {
        switch (choice)
        {

        case WATCH_PLAYLISTS: // 1
        {
            int chosenPlylst = 0;
            // As long as the user didn't choose the option of "Back to main menu"
            while (chosenPlylst != (playlistsArrLength + 1))
            {
                printAllPlaylists(playlistsArr, playlistsArrLength);
                scanf("%d", &chosenPlylst);
                // If the user chose to go back to main menu
                if (chosenPlylst == (playlistsArrLength + 1))
                {
                    break;
                }
                // If user's input isn't valid
                else if (chosenPlylst < 1 || chosenPlylst > (playlistsArrLength + 1))
                {
                    printf("Invalid option\n");
                }
                // If the chosen option is a valid playlist
                else
                {
                    int playlistIndx = chosenPlylst - 1;
                    // Print and implement the options for the playlist
                    optionsForPlaylist(playlistsArr, playlistIndx);
                }
            }
            break;
        }

        case ADD_PLAYLIST: // 2
        {
            // Dynamically allocate place for a new playlist and insert it to the playlists array.
            Playlist *newPlaylist = malloc(sizeof(Playlist));
            if (!newPlaylist)
            {
                free(newPlaylist);
                printf("Dynamic Memory Allocation Failed!\n!");
                exit(1);
            }
            // Getting from the user and setting default values to all the needed details for a new playlist.
            printf("Enter playlist's name:\n");
            scanf("%*[^\n]");
            newPlaylist->name = getString();
            newPlaylist->songs = NULL;
            newPlaylist->songsNum = 0;
            playlistsArr = realloc(playlistsArr, (playlistsArrLength + 1) * sizeof(Playlist));
            if (!playlistsArr)
            {
                free(playlistsArr);
                printf("Dynamic Memory Allocation Failed!\n!");
                exit(1);
            }
            playlistsArr[playlistsArrLength] = newPlaylist;
            playlistsArrLength++;
            break;
        }

        case REMOVE_PLAYLIST: // 3
        {
            // Remove the playlist from the playlists array, using a function
            int playlistToRemove;
            printAllPlaylists(playlistsArr, playlistsArrLength);
            scanf("%d", &playlistToRemove);
            // If the user chose to go back to main menu
            if (playlistToRemove == (playlistsArrLength + 1))
            {
                break;
            }
            // If user's input isn't valid
            else if (playlistToRemove < 1 || playlistToRemove > (playlistsArrLength + 1))
            {
                printf("Invalid option\n");
            }
            // If the chosen option is a valid playlist
            else
            {
                int playlistIndxToRemove = playlistToRemove - 1;
                removePlaylist(&playlistsArr, playlistIndxToRemove, &playlistsArrLength);
            }
            break;
        }

        case EXIT_OPTION: // 4
        {
            break;
        }

        default:
        {
            printf("Invalid option\n");
        }
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}

// The function prints the options in the main menu.
void printMenu()
{
    printf("Please Choose:\n"
           "1. Watch playlists\n"
           "2. Add playlist\n"
           "3. Remove playlist\n"
           "4. exit\n");
}

/* The function read chars from an inserted input and return it as a string after dynamically allocate
place for it in memory. */
char *getString()
{
    char *string = malloc(sizeof(char));
    int strLength = 0;
    char c;
    if (string == NULL)
    {
        printf("Dynamic Memory Allocation Failed!\n!");
        exit(1);
    }
    // Read every char from the input until getting an enter.
    scanf(" %c", &c);
    while (c != '\n')
    {
        string[strLength] = c;
        strLength++;
        // Resize the memory block to fit the new (and longer) string.
        string = realloc(string, (strLength + 1) * sizeof(char));
        // If memory allocation failed
        if (string == NULL)
        {
            printf("Dynamic Memory Allocation Failed!\n!");
            exit(1);
        }
        scanf("%c", &c);
    }
    string[strLength] = '\0';
    // Replace '\r' with '\0' for Windows line endings.
    if (string[strLength - 1] == '\r')
    {
        string[strLength - 1] = '\0';
    }
    return string;
}

// The function prints the options for playlist.
void printPlaylistMenu()
{
    printf("1. Show Playlist\n"
           "2. Add Song\n"
           "3. Delete Song\n"
           "4. Sort\n"
           "5. Play\n"
           "6. exit\n");
}

/* The function goes through (playlistsArrLength + 1) lines to display the names of 'playlistsArrLength' num
of playlists plus the 'Back to main menu' line at the end. */
void printAllPlaylists(Playlist **playlistsArr, int playlistsArrLength)
{
    printf("Choose a playlist:\n");
    for (int i = 0; i <= playlistsArrLength; i++)
    {
        // If there is a playlist to display
        if (i < playlistsArrLength)
        {
            /* Print the num of option and the playlist name.
            (The num of option will be (i+1) since the i started from value of 0) */
            printf("%d. %s\n", (i + 1), playlistsArr[i]->name);
        }
        /* If all is needed is to display the 'Back to main menu' line */
        else if (i == playlistsArrLength)
        {
            printf("%d. Back to main menu\n", (i + 1));
        }
    }
}

// The function implements all the different options for a given playlist.
int optionsForPlaylist(Playlist **playlistsArr, int playlistIndx)
{
    int optionForPlylst;
    printf("playlist %s:\n", playlistsArr[playlistIndx]->name);
    printPlaylistMenu();
    scanf("%d", &optionForPlylst);
    while (optionForPlylst != EXIT_PLAYLIST_OPTION)
    {
        switch (optionForPlylst)
        {
        case SHOW_PLAYLIST: // 1
        {
            int songToPlay;
            // Print the songs in the playlist if exist (implement in a function)
            printSongsList(playlistsArr, playlistIndx);
            printf("choose a song to play, or 0 to quit:\n");
            scanf("%d", &songToPlay);
            // If there are'nt any songs in playlist, go back to the menu
            if (playlistsArr[playlistIndx]->songsNum == 0)
            {
                break;
            }
            // As long as user doesn't choose to get out
            while (songToPlay != 0)
            {
                // If the user chose a valid song, play it (print implement in a function)
                if (songToPlay <= playlistsArr[playlistIndx]->songsNum && songToPlay > 0)
                {
                    playSong(playlistsArr, playlistIndx, (songToPlay - 1));
                }
                else
                {
                    printf("Invalid option\n");
                }
                printf("choose a song to play, or 0 to quit:\n");
                scanf("%d", &songToPlay);
            }
            break;
        }

        case ADD_SONG: // 2
        {
            // Dynamically allocate place for a new song and insert it to the playlist.
            Song *newSong = malloc(sizeof(Song));
            if (!newSong)
            {
                free(newSong);
                printf("Dynamic Memory Allocation Failed!\n!");
                exit(1);
            }
            // Getting from the user and setting default values to all the needed details for a new song.
            printf("Enter song's details\n");
            scanf("%*[^\n]");
            printf("Title:\n");
            newSong->title = getString();
            printf("Artist:\n");
            newSong->artist = getString();
            printf("Year of release:\n");
            scanf("%d", &newSong->year);
            printf("Lyrics:\n");
            newSong->lyrics = getString();
            newSong->streams = 0;
            playlistsArr[playlistIndx]->songs = realloc(playlistsArr[playlistIndx]->songs,
                                                        (playlistsArr[playlistIndx]->songsNum + 1) * sizeof(Song));
            if (!playlistsArr[playlistIndx]->songs)
            {
                free(playlistsArr[playlistIndx]->songs);
                printf("Dynamic Memory Allocation Failed!\n!");
                exit(1);
            }
            playlistsArr[playlistIndx]->songs[playlistsArr[playlistIndx]->songsNum] = newSong;
            playlistsArr[playlistIndx]->songsNum++;
            break;
        }

        case DELETE_SONG: // 3
        {
            // Delete the song from the playlist, using a function
            int songToDelete;
            printSongsList(playlistsArr, playlistIndx);
            printf("choose a song to delete, or 0 to quit:\n");
            scanf("%d", &songToDelete);
            int songIndx = songToDelete - 1;
            deleteSong(playlistsArr, playlistIndx, songIndx);
            break;
        }

        case SORT_PLAYLIST: // 4
        {
            int sortOption;
            printf("choose:\n"
                   "1. sort by year\n"
                   "2. sort by streams - ascending order\n"
                   "3. sort by streams - descending order\n"
                   "4. sort alphabetically\n");
            scanf("%d", &sortOption);
            sortPlaylist(playlistsArr, playlistIndx, sortOption);
            break;
        }

        case PLAY_PLAYLIST: // 5
        {
            // Play all the songs in the playlist using the function that prints the name and lyrics for every song.
            for (int i = 0; i < playlistsArr[playlistIndx]->songsNum; i++)
            {
                playSong(playlistsArr, playlistIndx, i);
                printf("\n");
            }
            break;
        }

        case EXIT_PLAYLIST_OPTION: // 6
        {
            break;
        }

        default:
        {
            printf("Invalid option\n");
        }
        }
        printPlaylistMenu();
        scanf("%d", &optionForPlylst);
    }
    return 0;
}

// The function prints all the songs in a given playlist
void printSongsList(Playlist **playlistsArr, int playlistIndx)
{
    for (int i = 0; i < playlistsArr[playlistIndx]->songsNum; i++)
    {
        printf("%d. Title: %s\n"
               "Artist: %s\n"
               "Released: %d\n"
               "Streams: %d\n\n",
               (i + 1), playlistsArr[playlistIndx]->songs[i]->title,
               playlistsArr[playlistIndx]->songs[i]->artist, playlistsArr[playlistIndx]->songs[i]->year,
               playlistsArr[playlistIndx]->songs[i]->streams);
    }
}

// The function prints the name and lyrics for a given song and playlist indexes (= play the song)
void playSong(Playlist **playlistsArr, int playlistIndx, int songIndx)
{
    playlistsArr[playlistIndx]->songs[songIndx]->streams++;
    printf("Now playing %s:\n"
           "$ %s $\n",
           playlistsArr[playlistIndx]->songs[songIndx]->title,
           playlistsArr[playlistIndx]->songs[songIndx]->lyrics);
}

// The function sorts the given playlist by the option the user chose
void sortPlaylist(Playlist **playlistsArr, int playlistIndx, int sortOption)
{
    switch (sortOption)
    {
    case SORT_BY_YEAR:
    {
        for (int i = 0; i < (playlistsArr[playlistIndx]->songsNum - 1); i++)
        {
            for (int j = 0; j < (playlistsArr[playlistIndx]->songsNum - i - 1); j++)
            {
                // If the year of the next song (j+1) is earlier than the current song's year (j)
                if (playlistsArr[playlistIndx]->songs[j + 1]->year < playlistsArr[playlistIndx]->songs[j]->year)
                {
                    // Switch values so the current song will hold the song with the earlier year.
                    Song *tempSong = playlistsArr[playlistIndx]->songs[j];
                    playlistsArr[playlistIndx]->songs[j] = playlistsArr[playlistIndx]->songs[j + 1];
                    playlistsArr[playlistIndx]->songs[j + 1] = tempSong;
                }
            }
        }
        break;
    }

    case SORT_BY_STREAMS_ASCENDING:
    {
        for (int i = 0; i < (playlistsArr[playlistIndx]->songsNum - 1); i++)
        {
            for (int j = 0; j < (playlistsArr[playlistIndx]->songsNum - i - 1); j++)
            {
                // If the streams amount of the next song (j+1) is smaller than the current's streams amount (j)
                if (playlistsArr[playlistIndx]->songs[j + 1]->streams < playlistsArr[playlistIndx]->songs[j]->streams)
                {
                    // Switch values so the current song will hold the song with the least amount of streams.
                    Song *tempSong = playlistsArr[playlistIndx]->songs[j];
                    playlistsArr[playlistIndx]->songs[j] = playlistsArr[playlistIndx]->songs[j + 1];
                    playlistsArr[playlistIndx]->songs[j + 1] = tempSong;
                }
            }
        }
        break;
    }

    case SORT_BY_STREAMS_DESCENDING:
    {
        for (int i = 0; i < (playlistsArr[playlistIndx]->songsNum - 1); i++)
        {
            for (int j = 0; j < (playlistsArr[playlistIndx]->songsNum - i - 1); j++)
            {
                // If the streams amount of the next song (j+1) is bigger than the current's streams amount (j)
                if (playlistsArr[playlistIndx]->songs[j + 1]->streams > playlistsArr[playlistIndx]->songs[j]->streams)
                {
                    // Switch values so the current song will hold the song with the most amount of streams.
                    Song *tempSong = playlistsArr[playlistIndx]->songs[j];
                    playlistsArr[playlistIndx]->songs[j] = playlistsArr[playlistIndx]->songs[j + 1];
                    playlistsArr[playlistIndx]->songs[j + 1] = tempSong;
                }
            }
        }
        break;
    }

    default:
    {
        for (int i = 0; i < (playlistsArr[playlistIndx]->songsNum - 1); i++)
        {
            for (int j = 0; j < (playlistsArr[playlistIndx]->songsNum - i - 1); j++)
            {
                // If the title of the next song (j+1) is alphabetically before the title of the current song (j)
                if (strcmp(playlistsArr[playlistIndx]->songs[j + 1]->title,
                           playlistsArr[playlistIndx]->songs[j]->title) < 0)
                {
                    // Switch values so the current song will hold the song with the alphabetically ealier title.
                    Song *tempSong = playlistsArr[playlistIndx]->songs[j];
                    playlistsArr[playlistIndx]->songs[j] = playlistsArr[playlistIndx]->songs[j + 1];
                    playlistsArr[playlistIndx]->songs[j + 1] = tempSong;
                }
            }
        }
        break;
    }
    }
    printf("sorted\n");
}

// The function deletes the given song from the playlist and free the relevant values.
void deleteSong(Playlist **playlistsArr, int playlistIndx, int songIndx)
{
    freeSong(playlistsArr, playlistIndx, songIndx);
    // Move all the songs from the deleted song - 1 place backwards to keep the continuaity of songs in the playlist.
    for (int i = songIndx; i < playlistsArr[playlistIndx]->songsNum - 1; i++)
    {
        playlistsArr[playlistIndx]->songs[i] = playlistsArr[playlistIndx]->songs[i + 1];
    }
    playlistsArr[playlistIndx]->songs = realloc(playlistsArr[playlistIndx]->songs,
                                                (playlistsArr[playlistIndx]->songsNum - 1) * sizeof(Song));
    if ((!playlistsArr[playlistIndx]->songs) && playlistsArr[playlistIndx]->songsNum > 1)
    {
        free(playlistsArr[playlistIndx]->songs);
        printf("Dynamic Memory Allocation Failed!\n!");
        exit(1);
    }
    playlistsArr[playlistIndx]->songsNum--;
    printf("Song deleted successfully.\n");
}

// The function frees the memory that's taken by the given song
void freeSong(Playlist **playlistsArr, int playlistIndx, int songIndx)
{
    free(playlistsArr[playlistIndx]->songs[songIndx]->title);
    free(playlistsArr[playlistIndx]->songs[songIndx]->artist);
    free(playlistsArr[playlistIndx]->songs[songIndx]->lyrics);
    free(playlistsArr[playlistIndx]->songs[songIndx]);
}

// The function removes the given playlist from the playlist and free the relevant values
void removePlaylist(Playlist ***playlistsArr, int playlistIndx, int *playlistsArrLength)
{
    for (int i = 0; i < (*playlistsArr)[playlistIndx]->songsNum; i++)
    {
        freeSong((*playlistsArr), playlistIndx, i);
    }
    free((*playlistsArr)[playlistIndx]->songs);
    free((*playlistsArr)[playlistIndx]->name);
    free((*playlistsArr)[playlistIndx]);
    // Move all the playlists from the removed playlist - 1 place backwards to keep the continuaity of playlists in the arr.
    for (int i = playlistIndx; i < (*playlistsArrLength) - 1; i++)
    {
        (*playlistsArr)[i] = (*playlistsArr)[i + 1];
    }
    (*playlistsArr) = realloc((*playlistsArr), ((*playlistsArrLength) - 1) * sizeof(Playlist *));
    if (!(*playlistsArr) && (*playlistsArrLength) > 1)
    {
        free((*playlistsArr));
        printf("Dynamic Memory Allocation Failed!\n!");
        exit(1);
    }
    (*playlistsArrLength)--;
    printf("Playlist deleted.\n");
}
