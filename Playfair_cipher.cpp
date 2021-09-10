#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

void search(char grid[5][5],int& row, int&col ,char el);

int main(){
    string key,text;
    unordered_set<char> freq;
    
    cout << "Enter the text : ";
    cin >> text;
    
    cout << "Enter the key : ";
    cin >> key;
    
    // Converting key and text to lower case
    for(int i=0;i<text.length();++i) text[i] = tolower(text[i]);
    for(int i=0;i<key.length();++i){
        key[i] = tolower(key[i]); 
        if(key[i]=='j')key[i] = 'i';
    }
    
    // Removing same adjacent characters
    for(int i=1;i<text.length();++i){
        if(text[i-1]==text[i]) text[i] = 'x';

    }
    
    // Adding 'z' if text is not divisible by 2 as we need to make pair of chars
    if(text.length() % 2 != 0) text = text + "z";
    
    char grid[5][5];
    int i = 0;
    int j = 0;
    int index = 0;
    
    // Adding characters of KEY into 5*5 Grid;
    while(j < key.length()){
        i=index/5;
        if(freq.count(key[j]) == 0){
                grid[i][index % 5] = key[j];
                freq.insert(key[j]);
                ++index;
        }
        ++j;
    }
    
    // Adding remaining characters in the 5*5 matrix excluding j as i and j are assumed to be same
    j=0;
    while(j<=25){
        i=index/5;
        if(freq.count('a' + j) == 0 && 'a'+j != 'j'){
                grid[i][index % 5] = 'a'+j;
                freq.insert('a'+j);
                ++index;
        }
        ++j;
    }
    
    // Pair of indexes of element1 and element2 in the grid
    int r1{0},c1{0},r2{0},c2{0};
    
    string encrypted = "";

    for(i=0;i<text.length()-1;i+=2){
        search(grid,r1,c1,text[i]);
        search(grid,r2,c2,text[i+1]);
        
        if(c1==c2){
            encrypted += grid[(r1+1)%5][c1];
            encrypted += grid[(r2+1)%5][c2];
        }
        else if(r1==r2){
            encrypted += grid[r1][(c1+1)%5];
            encrypted += grid[r1][(c2+1)%5];
        }
        else{
            encrypted += grid[r1][c2];
            encrypted += grid[r2][c1];
        }
    }
    
    cout <<"Encrypted text : " <<encrypted;
    
    char choice;
    
    cout << "\n\nDo you want to decrypt the message (Y/N) : ";
    cin >> choice;
    
    if(choice == 'Y' || choice == 'y'){
        string dencrypted = "";
    
        for(i=0;i<encrypted.length()-1;i+=2){
            search(grid,r1,c1,encrypted[i]);
            search(grid,r2,c2,encrypted[i+1]);
        
            if(c1==c2){
                if(r1-1<0)r1=5;
                if(r2-1<0)r2=5;
                dencrypted += grid[(r1-1)%5][c1];
                dencrypted += grid[(r2-1)%5][c2];
            }
            else if(r1==r2){
                if(c1-1<0)c1=5;
                if(c2-1<0)c2=5;
                dencrypted += grid[r1][(c1-1)%5];
                dencrypted += grid[r1][(c2-1)%5];
            }
            else{
                dencrypted += grid[r1][c2];
                dencrypted += grid[r2][c1];
            }
        }
        
    cout<<"Decrypted Text : "<<dencrypted<<"\n\n";
    }
    return 0;
}

void search(char grid[5][5],int& row, int&col ,char el){
    // AS I and J are assumed to be same
    if(el=='j') el = 'i';
    
    // returning indexes as references 
    for(int i=0;i<5;++i)
        for(int j=0;j<5;++j){
            if(el == grid[i][j]){
                col = j;
                row = i;
                return;
            }
        }
}