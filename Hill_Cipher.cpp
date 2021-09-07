#include <iostream>

using namespace std;

int main()
{
    int key[3][3];
    int text [10][3];
    int encrypted[10][3];
    
    string input,key_string;
    
    cout<<"Enter the text to be encrypted: ";
    cin>>input;
    
    cout<<"Enter the key (9 Characters): " ;
    cin>>key_string;
    
    // Getting key in 3*3 Matrix
    for(int i=0;i<3;++i)
        for(int j=0;j<3;++j){
            key[i][j] = tolower(key_string[3*i+j])-97;
        }
        
    // Calculating determinant (Checking if inversible)
    int determinant=0;
    for(int i= 0; i < 3; i++)
        determinant = determinant + (key[0][i] * (key[1][(i+1)%3] * key[2][(i+2)%3] - key[1][(i+2)%3] * key[2][(i+1)%3]));
        
    if(determinant==0 || key_string.length()<8){
        cout<<"This key is invalid (Not inversible)"<<endl;
        exit(0);
    }
    

    // Padding Input to be exactly Divisible by 3
    unsigned int extra=0;
    if(input.length()%3!=0){
        for(extra=0;extra<input.length()%3;++extra) input=input+"X";
    }
    
    // Storing Input in 3*3 Matrix
    for(unsigned int i=0;i<input.size()/3;++i)
    {
        for(int j=0;j<3;++j)
        {
            text[i][j] = tolower(input[3*i+j])-97;
        }
    }
    
    // Encrypting Text
    int sum;
    for(unsigned int i=0;i<input.length()/3;i++)
        for(int j=0;j<3;++j){
            sum=0;
            for(int k=0;k<3;++k){
                 sum+= text[i][k] * key[j][k];  
            }
            encrypted[i][j] = sum % 26;
        }

    // Printing Encrypted Text
    cout<<"Ciphered Text: ";
    for(unsigned int i=0;i<input.size()/3;++i)
    {
        for(int j=0;j<3;++j)
        {
           cout<<(char)(encrypted[i][j]+97);
        }
    }
    
    char choice;
    cout<<"\n\nDo you want to decrypt the message?(Y/N): ";
    cin>>choice;
    
    if(choice=='Y'||choice=='y')
    {
        // Calculating Inverse
        float keyInverse[3][3];
 
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                keyInverse[i][j] = ((key[(j+1)%3][(i+1)%3] * key[(j+2)%3][(i+2)%3]) - (key[(j+1)%3][(i+2)%3] * key[(j+2)%3][(i+1)%3])/ determinant);
            }
        }
        
        int sum2;
        int decrypted[10][3];
        for(unsigned int i=0;i<input.length()/3;i++)
            for(int j=0;j<3;++j){
                sum2=0;
                for(int k=0;k<3;++k){
                    sum2+= encrypted[i][k] * (keyInverse[j][k]);  
                }
                decrypted[i][j] = sum2 % 26;
        }
        
        // Printing Decrypted Text
        cout<<"Decrypted : ";
        for(unsigned int i=0;i<input.size()/3;++i)
        {
            for(int j=0;j<3;++j)
            {
                cout<<(char)((text[i][j]+97));
            }
        }
        cout<<"\n";
    }
}