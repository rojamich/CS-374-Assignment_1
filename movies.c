#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to hold movie data
struct movie {
    char *title;
    int year;
    char *languages;
    int num_languages;
    double rating;
    struct movie* next;
};

/* Parse the current line which is comma delimited and create a
*  movie struct with the data in this line
*/
struct movie *createMovie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));
    
    // For use with strtok_r
    char *saveptr;

    // The first token is the title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = strdup(token);
    
    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = atoi(token);

    // The next token is the languages
    token = strtok_r(NULL, ",", &saveptr);
    // Take the number of languages from within square brackets
    // Count the number of semicolons to determine the number of languages
        currMovie->num_languages = 1;
        char *c;
        for (c = token; *c; c++) {
            if (*c == ';') {
                currMovie->num_languages++;
            }
        }

    // Set memory for languages string and copy the token
    currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->languages, token);

    // The last token is the rating
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = strtod(token, NULL);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    return currMovie;
}

struct movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *file = fopen(filePath, "r");
    
    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;

    /* Skip the first line (header)  **CHECK**
    if (getline(&currLine, &len, file) == -1) {
        fclose(file);
        perror("Error reading file");
        return NULL;
    }*/

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, file)) != -1)
    {
        // Get a new movie node corresponding to the current line
        struct movie *newMovie = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newMovie;
            tail = newMovie;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newMovie;
            tail = newMovie;
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
        printf("Example usage: ./movies movies_sample_1.csv\n");
        return EXIT_FAILURE;
    }
    struct movie *head = processFile(argv[1]);
    int num_movies = 0;
    struct movie *current = head;

    // Skip the header row
    if (current != NULL) {
        current = current->next;
    }

    while (current != NULL)
    {
        num_movies++;
        current = current->next;
    }
    printf("Processed file %s and parsed data for %d movies\n", argv[1], num_movies);

    //Interactive Menu
    int choice;
    int year;
    char language;
    do
    {
        printf("\n1. Show movies released in the specified year\n");
        printf("2. Show highest rated movie for each year\n");
        printf("3. Show the title and year of release of all movies in a specific language\n");
        printf("4. Exit from the program\n");
        printf("\nEnter a choice from 1 to 4: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nEnter the year for which you want to see movies: ");
                scanf("%d", &year);
                //***ENTER NEW FUNCTION TO SHOW MOVIES IN YEAR FROM LL****
                printf("No data about movies released in the year %d\n", year);
                break;
            case 2:
                printf("\nShowing the highest rated movies");
                //***ENTER NEW FUNCTION TO SHOW HIGHEST RATED MOVIES IN LL****
                break;
            case 3:
                printf("\nEnter the language for which you want to see movies: ");
                scanf("%c", &language);
                //***ENTER NEW FUNCTION TO SHOW MOVIES IN LANGUAGE FROM LL****
                printf("\nThese are all the movies in %c", language);
                break;
            default:
                printf("You entered an incorrect choice. Try again.\n");
                break;
        }
    } while (choice != 4);
}