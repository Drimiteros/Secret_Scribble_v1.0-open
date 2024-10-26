#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <aes.h>
#include <modes.h>
#include <hex.h>

using namespace std;
using namespace CryptoPP;

class Secure
{
private:
	byte iv[CryptoPP::AES::BLOCKSIZE] = { 0x00 };

public:
	Secure();
	void AES_Encrypt(string& plainText, string& encryptedText, string& cipherText, string userKey);
	void AES_Decrypt(string& plainText, string& decryptedText, string& cipherText, string userKey);
};

