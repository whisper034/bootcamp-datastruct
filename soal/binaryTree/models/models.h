struct Character {
  char name[255];
  char job[255];
  int level;
  int damage;
};

struct Node {
  Character c;
  Node *left, *right;
};