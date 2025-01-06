/******************
Name: Shira Cababia
ID:
Assignment: ex5
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_OPTION 1
#define SECOND_OPTION 2
#define THIRD_OPTION 3
#define EXIT_OPTION 4
// #define INITIALֹֹ_NUMֹ_OF_CELLS_FOR_PLST_ARR 1

int main();
void printMenu();
char *getString();

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

// some recommendations for functions, you may implement however you want

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
        case FIRST_OPTION:
        {
            printf("Choose a playlist:\n");
            for (int i = 0; i <= playlistsArrLength; i++)
            {
                if (i == playlistsArrLength)
                {
                    printf("%d. Back to main menu\n", (i+1));
                }
                else if (i < playlistsArrLength)
                {
                    printf("%d. %s\n", (i + 1), playlistsArr[i]->name);
                }
            }
            break;
        }

        case SECOND_OPTION:
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

        case THIRD_OPTION:
        {
            break;
        }

        case EXIT_OPTION:
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

// void deleteSong()
// {

//     printf("Song deleted successfully.\n");
// }

// void playSong()
// {
// }

// void freeSong()
// {
// }

// void freePlaylist(P)
// {
// }

// void printPlaylistsMenu()
// {
//     printf("Please Choose:\n");
//     printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
// }

// void sortPlaylist()
// {

//     printf("sorted\n");
// }
