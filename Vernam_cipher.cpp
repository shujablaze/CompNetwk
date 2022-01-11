#include <iostream>
#include <string>

using namespace std;

int main(){
    string text,key;
    
    cout << "Enter the text : ";
    getline(cin,text);
    cout << "Enter the key : ";
    getline(cin,key);
    
    // Vernam Conditions
    while(key.length()!=text.length()){
        cout<<"Please enter a valid key : ";
        getline(cin,key);
    }
    
    /* VIGENERE CONDITIONS
    string vigenere_key = key;
    while(vigenere_key.length() < text.length()){
        vigenere_key += key;
    }
    
    key = vigenere_key;
    */
    
    for(int i=0;i<text.length();++i){
        if(text[i] >= 65 && text[i] < 91){
            text[i] = (text[i]  + toupper(key[i]) - 130) % 26 + 65;
        }
        else if(text[i] >= 97 && text[i] < 123){
            text[i] = (text[i] + tolower(key[i]) - 194) % 26 + 97;
        }
    }
    
    cout <<"Ciphered text : "<< text <<endl;
    
    char choice;
    
    cout<<"\nDo you want to decipher the text(y/n) : ";
    cin>>choice;
    
    if(choice=='Y' || choice=='y'){
        for(int i=0;i<text.length();++i){
            if(text[i]>=65 && text[i] < 91){
                text[i] = (text[i]  - toupper(key[i])) % 26;
                text[i] = (text[i] < 0)? text[i] + 26 + 65 : text[i] + 65;
            }
            else if(text[i]>=97 && text[i] < 123){
                text[i] = (text[i] - tolower(key[i])) % 26;
                text[i] = (text[i] < 0)? text[i] + 26 + 97 : text[i] + 97;
            }
        }
        cout<<"\nDeciphered text : " <<text<<endl;
    }
    return 0;
}