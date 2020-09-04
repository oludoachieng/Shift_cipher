#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;
/**This is the encryption function**/
int encrypt(int x,int key){
int z=(x+key)%26;
return z;
}
/**This is the decryption function,since decryption key has been calculated(below) as (26-key) we add x+key even here**/
int decrypt(int x,int key){

int z=(x+key)%26;
return z;
}


int main()
{
   /**ENCRYPTION**/

/**Error handling, check if there is a plain text and key.**/
ifstream ifs2("plain.txt", ios::ate);
if(ifs2.tellg() == 0)
{
    cout<< "The plain.txt file is empty, please input the plain text.";
    return 0;
}
ifstream ifs("key-encrypt.txt", ios::ate);
if(ifs.tellg() == 0)
{
    cout<< "The key-encrypt.txt file is empty, please input the key.";
    return 0;
}

/**Next step is to grab the encryption key from "key-encrypt.txt" and store**/

    ifstream key_input;
    key_input.open("key-encrypt.txt");
    char k;
    int key_int;
    while (key_input >> k)
        {   key_int = static_cast<int>(k);
        if(key_int>122||key_int<97){
            cout<<"Please input key as a small letter only";
            return 0;
        }
            key_int-=97;
        }
    key_input.close();

/**Next step is to calculate the decryption key **/
int key_dec;
if(key_int!=0)
key_dec=26-key_int;
else key_dec=key_int;
key_dec+=97;
char key_dec_char=static_cast<char>(key_dec);

/**Next step is to store decryption key in "key-decrypt.txt"**/
ofstream write_decrypt_key;
write_decrypt_key.open("key-decrypt.txt");
write_decrypt_key<<key_dec_char;
write_decrypt_key.close();

/**Next step is to do the encryption using the encrypt function**/
    ifstream plain_input;
    plain_input.open("plain.txt");
    char p;
     vector<char> ciph_vector;
    while (plain_input >> p)
        {  int plain_char = static_cast<int>(p);
        if(plain_char>122||plain_char<97){
            cout<<"Please input plain text in small letters only";
            return 0;
        }
            plain_char-=97;
           int ciph=encrypt(plain_char,key_int);//call encrypt function
           ciph+=97;
           char ciph_char = static_cast<char>(ciph);
           ciph_vector.push_back(ciph_char);
        }
    plain_input.close();

/**Next step is to store the encrypted data to the "cipher.txt"**/
ofstream write_ciph;
write_ciph.open("cipher.txt");
for(int vec_siz = 0; vec_siz != ciph_vector.size(); vec_siz++)
{
write_ciph<<ciph_vector[vec_siz];
}
write_ciph.close();


/**DECRYPTION**/
/**Read the cipher text from cipher.txt and call the decrypt function**/
    key_dec-=97;
    ifstream cip_input;
    cip_input.open("cipher.txt");
    char q;
     vector<char> plain_vector;
    while (cip_input >> q)
        {  int cip_val = static_cast<int>(q);
            cip_val-=97;
           int plain=decrypt(cip_val,key_dec);//call decrypt function
           if(plain<0){
                while (plain<0)plain+=26;}
             if(plain>25){
                while (plain>25)plain-=26;}
           plain+=97;
           char plain_char = static_cast<char>(plain);
           plain_vector.push_back(plain_char);
        }
    cip_input.close();

/**Store the decrypted data in plaintext.txt**/
    ofstream write_plain;
write_plain.open("plaintext.txt");
for(int vec2_siz = 0; vec2_siz != plain_vector.size(); vec2_siz++)
{
write_plain<<plain_vector[vec2_siz];
}
write_plain.close();

/**END OF DECRYPTION**/
cout<<endl;
cout<<"ENCRYPTION AND DECRYPTION COMPLETE!";
    return 0;
}
