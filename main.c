#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Languages 5
#define Max_Len 20

typedef struct Movie
{
    char title[100];
    int year;
    char language[Max_Len];
    int num_of_languages;
    double rating;
    struct Movie* next;
} Movie;

Movie* createMovie(char *title, int year, char language[][Max_Languages], int num_of_languages, double rating) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (newMovie == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newMovie->title, title);
    newMovie->year = year;
    for (int i = 0; i < num_of_languages; i++) {
        strcpy(newMovie->language[i], language[i]);
    }
    newMovie->num_of_languages = num_of_languages;
    newMovie->rating = rating;
    newMovie->next = NULL;
    return newMovie;
}

void insertMovie(Movie **head, Movie *newMovie) {
    if (*head == NULL) {
        *head = newMovie;
    } else {
        Movie *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newMovie;
    }
}

Movie* parseMovie(char *line) {
    char *token;
    char *rest = line;
    char title[100];
    int year;
    char language[Max_Languages][Max_Len];
    int num_of_languages = 0;
    double rating;

    // Parse title, year, languages, and rating from the input line
    // Tokenize the line using strtok_r function
    // Copy each token into corresponding variables

    return createMovie(title, year, language, num_of_languages, rating);
}

void printMovies(Movie *head) {
    while (head != NULL) {
        printf("Title: %s\n", head->title);
        printf("Year: %d\n", head->year);
        printf("Languages: ");
        for (int i = 0; i < head->num_of_languages; i++) {
            printf("%s ", head->language[i]);
        }
        printf("\nRating: %.1f\n\n", head->rating);
        head = head->next;
    }
}
