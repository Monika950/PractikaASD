#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Q_LEN 100
#define ANS_LEN 50
#define MAX_Q 15

typedef struct Question
{
  char question[Q_LEN];
  int difficulty;
  char answers[4][ANS_LEN];
  char correctAns[ANS_LEN];

} Question;

typedef struct Collection
{
  Question questions[MAX_Q];
  int size;
} Collection;

void write_questions(char *filename, Collection *collection)
{
  FILE *file = fopen(filename, "w");
  if (!file)
  {
    printf("Cannot open file\n");
    exit(0);
  }

  for( int i = 0; i < collection->size; i++ )
  {
    Question q = collection->questions[i];
    fprintf(file,"%s\n%d\n",q.question,q.difficulty);

    for (int i = 0; i < 4; i++)
    {
      fprintf(file, "%s\n", q.answers[i]);
    }

    fprintf(file, "%s\n", q.correctAns);
  }

  fclose(file);
}

void print(Collection *collection)
{
  for( int i = 0; i < collection->size; i++ )
  {
    Question q = collection->questions[i];
    printf("%s\n%d\n",q.question,q.difficulty);

    for (int i = 0; i < 4; i++)
    {
      printf( "%s\n", q.answers[i]);
    }

    printf("%s\n", q.correctAns);
  }
}

Collection* read_questions(const char *filename)
{
    Collection* col = (Collection*)calloc(1, sizeof(Collection));
    col->size = 0;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Cannot open file\n");
        exit(1);
    }

    char line[100];
    while (1)
    {
        if (fgets(line, sizeof(line), file) == NULL) break;
        line[strcspn(line, "\n")] = '\0';

        Question q;
        strcpy(q.question, line);

        if (fgets(line, sizeof(line), file) == NULL) break;
        q.difficulty = atoi(line);

        for (int i = 0; i < 4; i++)
        { 
            if (fgets(line, sizeof(line), file) == NULL) break;
            line[strcspn(line, "\n")] = '\0'; 
            strcpy(q.answers[i], line);
        }

        if (fgets(line, sizeof(line), file) == NULL) break;
        line[strcspn(line, "\n")] = '\0'; 
        strcpy(q.correctAns, line);

        col->questions[col->size]=q;
        col->size++;

        if (feof(file))
        {
            break;
        }
    }

    fclose(file);

    return col;
}


void add_question()
{
}


int main() {
    Collection col;
    col.size = 0;

    Question q1 = {"What is the capital of France?", 1, {"Paris", "Rome", "Berlin", "Madrid"}, "Paris"};
    col.questions[col.size++] = q1;

    Question q2 = {"What is the largest planet in our solar system?", 3, {"Jupiter", "Saturn", "Mars", "Earth"}, "Jupiter"};
    col.questions[col.size++] = q2;

    Question q3 = {"Who wrote 'To Kill a Mockingbird'?", 6, {"Harper Lee", "Mark Twain", "Ernest Hemingway", "J.K. Rowling"}, "Harper Lee"};
    col.questions[col.size++] = q3;

    write_questions("questions.txt", &col);
 
    Collection* col2;

    col2 = read_questions("questions.txt");
    print(col2);

    return 0;
}
