#include <iostream>;
#include "Node.h";
#include <vector>;
using namespace std;

Vector<Node*> frontier;
Node* root;

void setup(int width, int height) {
    Node* prevRow = new Node[width];
    for(int i = 0; i < width; i++) {
        prevRow[i] = NULL;
    }

    Node* newRow = new Node[width];
    for(int a = 0; a < height; a++) {
        for(int i = 0; i < width; i++) {
            newRow[i] = new Node();

            if(i != 0) {
                newRow[i].set(6, newRow[i-1])
            }

            if(prevRow[i]) {
                newRow[i].set(0, prevRow[i]);
            } else {
                continue;
            }

            if(i > 0 && i < width-2) {
                newRow[i].set(7, prevRow[i-1]);
                newRow[i].set(1, prevRow[i+1]);
            } else if (i == width-2) {
                newRow[i].set(7, prevRow[i-1]);
            } else if (i == 0) {
                newRow[i].set(1, prevRow[i+1]);
            }
        }

        if(a == 0) {
            root = newRow[0];
        }

        prevRow = newRow;
    }

    frontier = prevRow;
}

int main() {
    while(true) {
        setup(6,7);
        int column;
        cin >> column;
        cout << "recieved: " << column << endl;

    }

    return 0;
}