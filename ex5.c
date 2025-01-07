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
int optionsForPlaylist(Playlist **playlistsArr, int playlistIndx);

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
            int chosenPlylst;
            printf("Choose a playlist:\n");
            /* Going through (playlistsArrLength + 1) lines to display playlistsArrLength num of playlists plus the
            'Back to main menu' line at the end.*/
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
                optionsForPlaylist(playlistsArr, playlistIndx); //////// Func
                printf(" - - - Finished options for a playlist. \n");
                break;
            }
        }

        case ADD_PLAYLIST: // 2 - NOTES
        {
            Playlist *newPlaylist = malloc(sizeof(Playlist));
            if (!newPlaylist)
            {
                free(newPlaylist);
                printf("There isn't enough place in memory!");
                exit(1);
            }
            printf("Enter playlist's name:\n");
            scanf("%*[^\n]");
            newPlaylist->name = getString();
            newPlaylist->songs = NULL;
            newPlaylist->songsNum = 0;
            playlistsArr = realloc(playlistsArr, (playlistsArrLength + 1) * sizeof(Playlist));
            if (!playlistsArr)
            {
                free(playlistsArr);
                printf("There isn't enough place in memory!");
                exit(1);
            }
            playlistsArr[playlistsArrLength] = newPlaylist;
            playlistsArrLength++;
            break;
        }

        case REMOVE_PLAYLIST: // 3
        {
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
    char *string = NULL;
    char c;
    int strLength = 0;
    // Clear the buffer
    scanf("%*c");
    // Read every char from the input until getting an enter.
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Resize the memory block to fit the new (and longer) string.
        string = realloc(string, (strLength + 1));
        // If memory allocation failed
        if (!string)
        {
            free(string);
            printf("There isn't enough place in memory!");
            exit(1);
        }
        // Store the new char in the allocated memory and increment length for the next char.
        string[strLength] = c;
        strLength++;
    }
    // Add a null-terminator at the end of the string.
    if (string)
    {
        string = realloc(string, (strLength + 1));
        if (!string)
        {
            free(string);
            printf("There isn't enough place in memory!");
            exit(1);
        }
        string[strLength] = '\0';
    }
    // Replace '\r' with '\0' for Windows line endings.
    if (string[strLength - 1] == '\r' && strLength > 0)
    {
        string[strLength - 1] = '\0';
    }
    return string;
}

// The function prints the options for a given playlist.
void printPlaylistMenu()
{
    printf("1. Show Playlist\n"
           "2. Add Song\n"
           "3. Delete Song\n"
           "4. Sort\n"
           "5. Play\n"
           "6. exit\n");
}

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
            printf("choose a song to play, or 0 to quit:\n");
            scanf("%d", &songToPlay);
            if (playlistsArr[playlistIndx]->songsNum == 0)
            {
                break;
            }
            else if (playlistsArr[playlistIndx]->songsNum > 0)
            {
                // Will be completed next ...
            }
            break;
        }

        case ADD_SONG: // 2
        {
            // int songToPlay;
            // printf("Enter song's details\n");
            // printf("Title:\n");
            // scanf("%d", &songToPlay);
            break;
        }

        case DELETE_SONG: // 3
        {
            break;
        }

        case SORT_PLAYLIST: // 4
        {
            break;
        }

        case PLAY_PLAYLIST: // 5
        {
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
    printf("Goodbye!\n");
    return 0;
}

// void deleteSong()
// {
//     printf("Song deleted successfully.\n");
// }

// void playSong() {}

// void freeSong() {}

// void freePlaylist(P) {}

// void sortPlaylist()
// {
//     printf("sorted\n");
// }
