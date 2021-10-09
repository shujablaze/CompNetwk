#include <iostream>
#include <string>

using namespace std;

int main(){
    string text;
    int key;
    char grid[7][100];
    
    cout << "Enter the text to be ciphered: ";
    cin.sync();
    getline(cin,text);
    
    cout << "Enter the key (less than 8): ";
    cin >> key;
    
    if(key > 7){
        cout << "Resetting value of key to 7" << endl;
        key = 7;
    }
    
    //Initialize the grid
    for(int i=0 ; i < key ; ++i){
        for(int j = 0 ; j < text.length(); ++j){
            grid[i][j] = 0;
        }
    }
    
    bool goingdown = false;
    int row = 0, col = 0;
 
    for (int i=0; i < text.length(); i++)
    {
        // check the direction of inserion
        if (row == 0 || row == key-1)
            goingdown = !goingdown;
 
        grid[row][col] = text[i];
 
        if(goingdown==true) row++;
        else row--;
        col++;
    }
    
    cout << "\nCiphered Text: ";
    
    for(int i=0 ; i < key ; ++i){
        for(int j = 0 ; j < text.length(); ++j){
            if(grid[i][j] != 0) cout << grid[i][j];
        }
    }
    
    char choice;
    cout << "\n\nDo you want to decipher the text(y/n): ";
    cin >> choice;
    
    if(choice == 'y' || choice == 'Y'){
        cout << "Deciphered text : ";
        goingdown = false;
        row = col = 0;
        // Deciphering
        for (int i=0; i < text.length(); i++)
        {

            if (row == 0 || row == key-1)
                goingdown = !goingdown;
    
            cout << grid[row][col];
    
            if(goingdown==true) row++;
            else row--;
            col++;
        }
        cout << "\n\n";
    }
}