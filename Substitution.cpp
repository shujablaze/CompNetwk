#include <iostream>

using namespace std;

int main()
{
    char text[100];
    cout << "Enter the text to be ciphered." << endl;
    gets(text);
    short key{0},i{0};
    
    cout << "Enter the key : ";
    cin >> (key);
    key = key % 26;
    
    while(text[i] != '\0')
    {
        if(text[i]>='A' && text[i]<='Z')
            text[i] = (text[i] + key - 65) % 26 + 65 ;
            
        else if(text[i]>='a' && text[i]<='z')
            text[i] = (text[i] + key - 97) % 26 + 97;
            
        i++;
    }
    cout << "\nCiphered Text: " << text << endl;
    
    char choice;
    cout << "\nDo you want to decipher the message(y/n): ";
    cin >> choice;
    
    



if(choice == 'y' || choice == 'Y')
    {
        i=0;
        while(text[i] != '\0')
        {
            if(text[i]>='A' && text[i]<='Z')
                text[i] = text[i]-key < 65 ? (text[i]-key) + 26 : text[i] - key;
            
            else if(text[i]>='a' && text[i]<='z')
                text[i] = text[i]-key < 97 ? (text[i]-key) + 26 : text[i] - key;
                
            i++;
        }
        cout << "\nDeciphered text : " << text <<endl;
    }
    
}

