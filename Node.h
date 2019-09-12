using namespace std;

class Node {
    Node* adjacent[8]; //0 is the top left adjacent (might want mod ring)
    int state; //0=none, 1=player1, 2=player2

public:
    Node();
    void mutualSet(int pos, Node* n);
    void set(int pos, Node* n);
}