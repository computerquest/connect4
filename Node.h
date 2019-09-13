using namespace std;

class Node
{
    Node *adjacent[8]; //0 is top, 1 top right, 2 top left, ...., 7 top left
    int state;         //0=none, 1=player1, 2=player2

public:
    Node();
    void mutualSet(int pos, Node &n); //called from set to make sure that the recieving node gets set in the opposite manner
    void set(int pos, Node &n);

    void setState(int i);
    int getState();

    void print();

    Node *goDown();
    Node *goUp();

    int checkWin(int count, int pos, int player);

    ~Node();
};