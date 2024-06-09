#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>

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
  Question *questions[MAX_Q];
  int size;
} Collection;

Question *create_question(char *question, int difficulty, char answers[4][ANS_LEN], char *correctAns);

Collection *init_collection();

bool delete_file(char *filename);

void write_questions(char *filename, Collection *collection);

void print(Collection *collection);

Question *read_question(FILE *file);

Collection *read_file(char *filename);

void add_question(char *filename, Collection *col);

void edit_question(char *filename, Collection *col);

#endif