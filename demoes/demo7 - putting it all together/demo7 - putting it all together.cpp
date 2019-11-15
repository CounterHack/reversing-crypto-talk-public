#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <wincrypt.h>
#include <wininet.h>

#pragma comment(lib, "crypt32.lib")

#define AES_KEY_SIZE 16

typedef struct {
    BLOBHEADER hdr;
    DWORD dwKeySize;
    BYTE rgbKeyData[AES_KEY_SIZE];
} AESKEYBLOB;

static int state;
void my_srand(int seed) {
  state = seed;
}

int my_rand()
{
	return state = (state * 1103515245 + 12345) & 0x7FFF;
}

void make_key(unsigned char buffer[AES_KEY_SIZE]) {
  size_t i;
  int timestamp = time(0);

  fprintf(stderr, "TIMESTAMP: %d\n\n", timestamp);
  my_srand(timestamp);
  for(i = 0; i < AES_KEY_SIZE; i++) {
    buffer[i] = (unsigned char)my_rand() & 0x0FF;
  }
}

void fatal_error(char *msg)
{
  char *buffer = NULL;
  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    GetLastError(),
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR) &buffer,
    0,
    NULL
  );
  fprintf(stderr, "Uh oh, something went very wrong. That's not supposed to happen.\n");
  fprintf(stderr, "Please don't tell Santa :(\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "%s: %s\n", msg, buffer ? buffer : "(unknown error)");

  exit(1);
}

void encrypt(char *in_data, char *out_file) {
  unsigned char key[AES_KEY_SIZE];

  /* Cryptographic context */
  HCRYPTPROV hProv;

  /* Key blob */
  AESKEYBLOB keyBlob;

  /* The key that we're gonna use. */
  HCRYPTKEY hKey;

  /* Length of the file data. */
  DWORD data_len = strlen(in_data);

  /* Make the buffer bigger so we can use it for encryption. */
  unsigned char *data = (unsigned char *)malloc(strlen(in_data) + 32);
  memset(data, 0, strlen(in_data) + 32);
  memcpy(data, in_data, strlen(in_data));

  fprintf(stderr, "\nINPUT: %d bytes\n\n", strlen(in_data));

  /* Get a handle to the cryptographic library. */
  if(!CryptAcquireContext(&hProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
    fatal_error("CryptAcquireContext failed");
  }

  /* Build the key blob */
  make_key(key);

  fprintf(stderr, "KEY: %d bytes => ", 16);
  for(int i = 0; i < 16; i++) {
    fprintf(stderr, "%02x", key[i]);
  }
  fprintf(stderr, "\n\n");

  keyBlob.hdr.bType = PLAINTEXTKEYBLOB;
  keyBlob.hdr.bVersion = CUR_BLOB_VERSION;
  keyBlob.hdr.reserved = 0;
  keyBlob.hdr.aiKeyAlg = CALG_AES_128;
  keyBlob.dwKeySize = AES_KEY_SIZE;
  memcpy(keyBlob.rgbKeyData, key, AES_KEY_SIZE);

  /* Convert the keyBlob to a key object */
  if(!CryptImportKey(hProv, (byte*) &keyBlob, sizeof(AESKEYBLOB), 0, CRYPT_EXPORTABLE, &hKey)) {
    fatal_error("CryptImportKey failed for AES-128-CBC key");
  }

  /* Perform the actual encyption. */
  if(!CryptEncrypt(hKey, 0, 1, 0, data, &data_len, data_len + 32)) {
    fatal_error("CryptEncrypt failed");
    exit(1);
  }

  printf("OUTPUT: %d bytes => ", data_len);

  for(int i = 0; i < data_len; i++) {
    printf("%02x", data[i]);
  }
  printf("\n\n");
}

int main(int argc, char *argv[]) {
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <data>\n", argv[0]);
    exit(1);
  }

  encrypt(argv[1], argv[2]);
}
