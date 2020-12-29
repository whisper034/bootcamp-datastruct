#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../controllers/controllers.h"

void title();
void menu();

int main() {
  bool inGame = true;
  Node *baseRoot = NULL;

  while(inGame) {
    menu();

    int input;
    do {
      printf("Input: ");
      scanf("%d", &input); getchar();
      system("clear");
      if(input < 1 || input > 4) {
        menu();
        puts("Please input numbers above.");
        int a = getchar();
      }
    } while(input < 1 || input > 4);

    switch(input) {
      case 1: {
        if(!baseRoot) {
          title();
          puts("--- There is no character in the tree. ---");
          int a = getchar();
          system("clear");
        }
        else {
          printData(baseRoot);
          int a = getchar();
          system("clear");
        }
        break;
      }

      case 2: {
        Character dummy;
        bool isValidName, isValidJob, isValidLevel;

        isValidName = true;
        do {
          title();
          isValidName = true;
          printf("Input Character's Name [3..20] [non space char]: ");
          scanf("%s", dummy.name); getchar();
          int len = strlen(dummy.name);

          for(int i = 0; i < len; i++) {
            if(dummy.name[i] == ' ') {
              isValidName = false;
              puts("Please input Character's Name from 3 to 20 characters without 'space'.");
              int a = getchar();
              system("clear");
            }
          }
        } while(!isValidName);
        
        isValidJob = false;
        do {
          isValidJob = false;
          printf("Input Character's Job [fighter/rogue/mage]: ");
          scanf("%s", dummy.job); getchar();

          if(strcmp(dummy.job, "fighter") != 0 || strcmp(dummy.job, "rogue") != 0 || strcmp(dummy.job, "mage") != 0) {
            isValidJob = true;
          }
        } while(!isValidJob);

        isValidLevel = true;
        do {
          isValidLevel = true;
          printf("Input Character's Level [1..105]: ");
          scanf("%d", &dummy.level); getchar();

          if(dummy.level < 1 || dummy.level > 105) {
            isValidLevel = false;
          }
        } while(!isValidLevel);

        srand(time(NULL));
        int randomNumber = -1;

        if(strcmp(dummy.job, "fighter") == 0) dummy.damage = rand() % 50;
        else if(strcmp(dummy.job, "rogue") == 0) dummy.damage = rand() % 25;
        else dummy.damage = rand() % 75;

        dummy.damage = dummy.level + randomNumber;
        baseRoot = insertNode(baseRoot, dummy);
        puts("\n--- Character Added. ---");
        int a = getchar();
        system("clear");
        break;
      }

      case 3: {
        printDamage(baseRoot);
        break;
      }

      case 4: {
        inGame = false;
        popAll(baseRoot);
        break;
      }
    }
  }
  return 0;
}


void title () {
  puts("BLUE-LUNA ONLINE");
  puts("________________\n");
}

void menu() {
  title();
  puts("1. View All Characters");
  puts("2. Add New Character");
  puts("3. Inorder, Preorder, Postorder Character's Damage");
  puts("4. Exit and PopAll\n");
}