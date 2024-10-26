#include "Secure.h"

Secure::Secure()
{

}

void Secure::AES_Encrypt(string& plaintext, string& encryptedText, string& cipherText, string userKey)
{
    SecByteBlock key(reinterpret_cast<const byte*>(userKey.data()), userKey.length());
    try
    {
        CBC_Mode< AES >::Encryption encryption;
        encryption.SetKeyWithIV(key, key.size(), iv);
        StringSource ss1(plaintext, true,
            new StreamTransformationFilter(encryption, new StringSink(cipherText)));
        StringSource ss2(cipherText, true, new HexEncoder(new StringSink(encryptedText)));
    }
    catch (const Exception& e)
    {
        cerr << e.what() << endl;
    }
}

void Secure::AES_Decrypt(string& plainText, string& decryptedText, string& cipherText, string userKey)
{
    SecByteBlock key(reinterpret_cast<const byte*>(userKey.data()), userKey.length());
    StringSource ss3(plainText, true, new HexDecoder(new StringSink(cipherText)));

    try
    {
        CBC_Mode< AES >::Decryption decryption;
        decryption.SetKeyWithIV(key, key.size(), iv);
        StringSource ss4(cipherText, true, new StreamTransformationFilter(decryption, new StringSink(decryptedText)));
    }
    catch (const Exception& e)
    {
        cerr << e.what() << endl;
    }
}