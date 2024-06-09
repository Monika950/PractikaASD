#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "logic.h"
#include "encrypting_questions.c"

Question *create_question(char *question, int difficulty, char answers[4][ANS_LEN], char *correctAns)
{
  Question *q = (Question *)malloc(sizeof(Question));

  strncpy(q->question, question, Q_LEN);
  q->question[Q_LEN - 1] = '\0';

  q->difficulty = difficulty;

  for (int i = 0; i < 4; i++)
  {
    strncpy(q->answers[i], answers[i], ANS_LEN);
    q->answers[i][ANS_LEN - 1] = '\0';
  }

  strncpy(q->correctAns, correctAns, ANS_LEN);
  q->correctAns[ANS_LEN - 1] = '\0';

  return q;
}

Collection *init_collection()
{
  Collection *col = (Collection *)calloc(1, sizeof(Collection));
  if (col == NULL)
  {
    printf("Memory allocation failed\n");
    exit(1);
  }

  return col;
}

bool delete_file(char *filename)
{
  if (remove(filename) == 0)
  {
    return true;
  }
  else
  {
    printf("Failed to delete the file");
    return false;
  }
}

void write_questions(char *filename, Collection *collection)
{
    char decrypted_file[] = "decrypted.txt";
    decrypt(filename, decrypted_file);
    if (!delete_file(filename)) {
        exit(0);
    }

  FILE *file = fopen(decrypted_file, "w");
  if (!file)
  {
    printf("Cannot open file\n");
    exit(0);
  }

  for (int i = 0; i < collection->size; i++)
  {
    Question *q = collection->questions[i];
    fprintf(file, "%s\n%d\n", q->question, q->difficulty);

    for (int i = 0; i < 4; i++)
    {
      fprintf(file, "%s\n", q->answers[i]);
    }

    fprintf(file, "%s\n", q->correctAns);
  }

  fclose(file);

  encrypt(decrypted_file, filename);
  if (!delete_file(decrypted_file))
    exit(0);
}

void print(Collection *collection)
{
  for (int i = 0; i < collection->size; i++)
  {
    Question *q = collection->questions[i];
    printf("%s\n%d\n", q->question, q->difficulty);

    for (int i = 0; i < 4; i++)
    {
      printf("%s\n", q->answers[i]);
    }

    printf("%s\n", q->correctAns);
  }
}

Question *read_question(FILE *file)
{
  Question *q = (Question *)calloc(1,sizeof(Question));
  char line[Q_LEN];

  if (fgets(line, sizeof(line), file) == NULL)
    return NULL;
  line[strcspn(line, "\n")] = '\0';
  strcpy(q->question, line);

  if (fgets(line, sizeof(line), file) == NULL)
    return NULL;
  q->difficulty = atoi(line);

  for (int i = 0; i < 4; i++)
  {
    if (fgets(line, sizeof(line), file) == NULL)
      return NULL;
    line[strcspn(line, "\n")] = '\0';
    strcpy(q->answers[i], line);
  }

  if (fgets(line, sizeof(line), file) == NULL)
    return NULL;
  line[strcspn(line, "\n")] = '\0';
  strcpy(q->correctAns, line);
  return q;
}

Collection *read_file(char *filename)
{
   char decrypted_file[] = "decrypted.txt";
    decrypt(filename, decrypted_file);
    if (!delete_file(filename)) {
        exit(0);
    }

  Collection *col = (Collection *)calloc(1, sizeof(Collection));
  col->size = 0;

  FILE *file = fopen(decrypted_file, "r");
  if (!file)
  {
    printf("Cannot open file\n");
    exit(1);
  }

  while (!feof(file))
  {
    Question *q = read_question(file);
    if (q->question == NULL)
      break;

    col->questions[col->size] = q;
    col->size++;
  }

  // while (1)
  // {
  //     Question q;
  //     char line[100];

  //     if (fgets(line, sizeof(line), file) == NULL) break;
  //     line[strcspn(line, "\n")] = '\0';
  //     strcpy(q.question, line);

  //     if (fgets(line, sizeof(line), file) == NULL) break;
  //     q.difficulty = atoi(line);

  //     for (int i = 0; i < 4; i++)
  //     {
  //         if (fgets(line, sizeof(line), file) == NULL) break;
  //         line[strcspn(line, "\n")] = '\0';
  //         strcpy(q.answers[i], line);
  //     }

  //     if (fgets(line, sizeof(line), file) == NULL) break;
  //     line[strcspn(line, "\n")] = '\0';
  //     strcpy(q.correctAns, line);

  //     col->questions[col->size]=q;
  //     col->size++;

  //     if (feof(file))
  //     {
  //         break;
  //     }
  // }

  fclose(file);

  encrypt(decrypted_file, filename);
  if (!delete_file(decrypted_file))
    exit(0);

  return col;
}

void add_question(char *filename, Collection *col)
{
  if (col->size == MAX_Q - 1)
  {
    printf("Question limit exceeded\n");
    return;
  }

  char line[100];

  char question[Q_LEN];
  int difficulty;
  char answers[4][ANS_LEN];
  char correctAns[ANS_LEN];

  printf("Enter the question: ");
  fgets(line, sizeof(line), stdin);
  line[strcspn(line, "\n")] = '\0';
  strcpy(question, line);

  printf("Enter the difficulty (1-10): ");
  fgets(line, sizeof(line), stdin);
  difficulty = atoi(line);

  for (int i = 0; i < 4; i++)
  {
    printf("Enter answer %d: ", i + 1);
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';
    strcpy(answers[i], line);
  }

  printf("Enter the correct answer: ");
  fgets(line, sizeof(line), stdin);
  line[strcspn(line, "\n")] = '\0';
  strcpy(correctAns, line);

  col->questions[col->size] = create_question(question, difficulty, answers, correctAns);
  col->size++;

  write_questions(filename, col);
  printf("Question added successfully!\n");
}

void edit_question(char *filename, Collection *col)
{
  if (col->size == 0)
  {
    printf("No questions available to edit.\n");
    return;
  }

  for (int i = 0; i < col->size; i++)
  {
    printf("%d. %s\n", i + 1, col->questions[i]->question);
  }

  printf("Select the question number to edit: ");
  char choice[10];
  fgets(choice, sizeof(choice), stdin);
  int index = atoi(choice) - 1;

  if (index < 0 || index >= col->size)
  {
    printf("Invalid selection.\n");
    return;
  }

  Question *q = col->questions[index];

  printf("Editing question: %s\n", q->question);
  printf("Enter new question (leave empty to keep current): ");
  char line[100];
  fgets(line, sizeof(line), stdin);
  if (line[0] != '\n')
  {
    line[strcspn(line, "\n")] = '\0';
    strcpy(q->question, line);
  }

  printf("Enter new difficulty (leave empty to keep current): ");
  fgets(line, sizeof(line), stdin);
  if (line[0] != '\n')
  {
    q->difficulty = atoi(line);
  }

  for (int i = 0; i < 4; i++)
  {
    printf("Enter new answer %d (leave empty to keep current): ", i + 1);
    fgets(line, sizeof(line), stdin);
    if (line[0] != '\n')
    {
      line[strcspn(line, "\n")] = '\0';
      strcpy(q->answers[i], line);
    }
  }

  printf("Enter new correct answer (leave empty to keep current): ");
  fgets(line, sizeof(line), stdin);
  if (line[0] != '\n')
  {
    line[strcspn(line, "\n")] = '\0';
    strcpy(q->correctAns, line);
  }

  write_questions(filename, col);
  printf("Question updated successfully!\n");
}

