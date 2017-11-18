
#include <iostream>
#include "RBTree.h"

using namespace std;

void console(RBTree tree);

int main() {

    cout << "Starting" << endl;
    
    RBTree tree = RBTree();
    
    console(tree);
    
    return 0;
}

//(bad) input loop
//hangs if you have a wrong input
void console(RBTree tree){
    cout << "Press I to insert, D to delete, S to show, X to exit$ ";
    string input;
    cin >> input;
    
    while(input == "i" || input == "d" || input == "s" ||
            input == "I" || input == "D" || input == "s"){
        
        if(input == "i" || input == "I"){
            cout << "Enter value to insert$ ";
            int value;
            cin >> value;
            
            tree.insert(value);
            
            tree.show();
        }
        
        if(input == "d" || input == "D"){
            cout << "Enter value to delete ";
            int value;
            cin >> value;
            
            tree.remove(value);
            
            tree.show();
        }
        
        if(input == "s" || input == "S"){
            tree.show();
        }
        
        cout << "Press I to insert, D to delete, S to show, X to exit$ ";
        cin >> input;
    }
}