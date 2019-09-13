#include <iostream>
#include "Node.h"
#include <vector>
using namespace std;

vector<Node *> frontier;  //the top of the columns which are available
Node *root;               //the root node of the game (top left)
vector<Node *> playerOne; //nodes that player one has
vector<Node *> playerTwo; //nodes that player two has

/*
OVERALL STRATEGY
The board is composed of nodes for each square. All the nodes are connected in any valid direction (up down left right topleft .....) by pointers.
The frontier is how nodes are accessed for placement. It is a list of pointers, so when a piece is played in the column the respective index on the
frontier is removed and replaced by node->up (which can be nullptr). To check for a winner, the list of pieces placed is checked for the respective player
This is done by recursivly crawling through the pointers between nodes (making sure no repeats using an unordered set) in a particular direction.
Once there is a winner everything is doconstructed and then setup again for the next game.

This was pretty fun.
*/

//This is used to setup the game board
void setup(int width, int height)
{
    vector<Node *> prevRow;
    prevRow.reserve(width + 1);
    prevRow.push_back(new Node());
    root = prevRow[0];

    for (int i = 1; i < width; i++)
    {
        prevRow.push_back(new Node());
        prevRow[i]->set(6, *prevRow[i - 1]);
    }

    int a = 0;

    do
    {
        int i = 0;

        vector<Node *> newRow;
        newRow.reserve(width + 1);
        do
        {
            newRow.push_back(new Node());

            newRow[i]->set(0, *prevRow[i]);

            if (i > 0)
            {
                newRow[i]->set(7, *prevRow[i - 1]);
                newRow[i]->set(6, *newRow[i - 1]);
            }

            if (i < width - 1)
            {
                newRow[i]->set(1, *prevRow[i + 1]);
            }

            if (i < width - 2 && i != 0)
            {
                newRow[i]->set(7, *prevRow[i - 1]);
            }

            i++;
        } while (i < width);

        for (int i = 0; i < prevRow.size(); i++)
        {
            prevRow[i] = newRow[i];
        }

        a++;
    } while (a < height - 1);

    frontier = prevRow;
}

//prints the board
void printBoard()
{
    Node *start = root;
    cout << "board:" << endl;
    while (start)
    {
        cout << "|";
        start->print();
        cout << endl;
        start = start->goDown();
    }
}

//checks if the player has won
int checkWin(int player)
{
    if (player == 1)
    {

        for (int a = 0; a < 8; a++)
        {
            for (int i = 0; i < playerOne.size(); i++)
            {
                if (playerOne[i]->checkWin(0, a, 1) >= 4)
                {
                    return 1;
                }
            }
        }
    }
    else
    {
        for (int a = 0; a < 8; a++)
        {
            for (int i = 0; i < playerTwo.size(); i++)
            {
                if (playerTwo[i]->checkWin(0, a, 2) >= 4)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

//deletes nodes
void deleteNodes(Node *root)
{
    while (root->goDown())
    {
        deleteNodes(root->goDown());
        return;
    }
}

int main()
{
    int width = 6;
    int height = 7;
    //this makes sure games loop
    while (true)
    {
        cout << "Hello There!" << endl;

        setup(width, height);

        int column;
        int player = 1;

        //makes sure that moves loop until win
        while (true)
        {
            printBoard();

            cout << "Player " << player <<", which column would you like to use? ";
            cin >> column;

            //puts the input in [1,6] and checks validity
            column--;
            if (column < 0 || column > 5)
            {
                cout << "Sorry, that is not a valid option." << endl;
                continue;
            }

            //checks if there is room on the column
            if (frontier[column])
            {
                frontier[column]->setState(player);

                if (player == 1)
                {
                    playerOne.push_back(frontier[column]);
                }
                else
                {
                    playerTwo.push_back(frontier[column]);
                }

                frontier[column] = frontier[column]->goUp();

                if (checkWin(player))
                {
                    cout << "Congratuations you won!!!" << endl;
                    printBoard();
                    break;
                }
                else if (playerOne.size() + playerTwo.size() == width * height)
                {
                    cout << "Draw" << endl;
                    break;
                }

                player = player == 1 ? 2 : 1;
            }
            else
            {
                cout << "Sorry, that is not a valid option." << endl;
                continue;
            }
        }

        //this is deletion for the reset
        deleteNodes(root);
        playerOne.clear();
        playerTwo.clear();
        frontier.clear();

        cout << "Done resetting" << endl;
    }

    return 0;
}