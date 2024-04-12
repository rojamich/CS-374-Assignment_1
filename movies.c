#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct to hold movie data */
struct Movie {
    char *title;
    int year;
    char *languages;
    int num_languages;
    double rating;
    struct Movie* next;
};

/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct Movie *createMovie(char *currLine)
{
    struct Movie *currMovie = malloc(sizeof(struct Movie));

    // For use with strtok_r
    char *saveptr;

    // The first token is the title
    char *token = strtok_r(currLine, " ", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = atoi(token);

    // The next token is the languages
    token = strtok_r(NULL, ",", &saveptr);
    // Extract the number of languages from within square brackets
    char *start = strchr(token, '[');
    char *end = strchr(token, ']');
    if (start && end) {
        // Count the number of semicolons to determine the number of languages
        currMovie->num_languages = 1;
        for (char *c = start; c < end; c++) {
            if (*c == ';') {
                currMovie->num_languages++;
            }
        }
    } else {
        // If there are no square brackets, assume there is only one language
        currMovie->num_languages = 1;
    }
    // Allocate memory for languages string and copy the token
    currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->languages, token);

    // The last token is the rating
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = strtod(token, NULL);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    free(currLine);

    return currMovie;
}

struct Movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *file = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;

    // The head of the linked list
    struct Movie *head = NULL;
    // The tail of the linked list
    struct Movie *tail = NULL;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, file)) != -1)
    {
        // Get a new movie node corresponding to the current line
        struct Movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(file);
    return head;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./students student_info1.txt\n");
        return EXIT_FAILURE;
    }
    struct Movie *head = processFile(argv[1]);
    int num_movies = 0;
    struct Movie *current = head;
    while (current != NULL)
    {
        num_movies++;
        current = current->next;
    }
    printf("Processed file %s and parsed data for %d movies\n", argv[1], num_movies);
}