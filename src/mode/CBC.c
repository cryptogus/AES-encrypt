#include "CBC.h"

void CBC_enc(void (*cipher)(uint8_t *, uint8_t *, uint8_t *) , uint8_t *IV, uint8_t *key, size_t block_size, size_t len, unsigned char *src, unsigned char *des) {

    uint8_t key2[16];
	
	
    for (size_t i = 0; i < len/block_size; i++)
    {
        //AES 키 바이트 16 -> 만약 AES key 크기가 달라지면 16을 바꿔야함
        memcpy(key2, key, 16); // key 변수만 사용하면 on-the-fly로 encryption 코드를 짜서 key값이 계속 갱신되어 마스터키 값이 달라짐
        int tmp = (i << 4);
        for (int j = 0; j < 16; j++)
	    {
		    src[tmp + j] ^= IV[j];
	    }
        
        cipher(des + tmp ,src + tmp, key2);
        
        for (int j = 0; j < 16; j++)
	    {
		    IV[j] = des[j + tmp];
	    }
    }
}

void CBC_dec(void (*cipher)(uint8_t *, uint8_t *, uint8_t *) , uint8_t *IV, uint8_t *key, size_t block_size, size_t len, unsigned char *src, unsigned char *des) {

    uint8_t key2[16];
	
	
    for (size_t i = 0; i < len/block_size; i++)
    {
        //AES 키 바이트 16 -> 만약 AES key 크기가 달라지면 16을 바꿔야함
        memcpy(key2, key, 16); // key 변수만 사용하면 on-the-fly로 encryption 코드를 짜서 key값이 계속 갱신되어 마스터키 값이 달라짐
        
        int tmp = (i << 4);
        
        cipher(des + tmp , src + tmp, key2);
        
        for (int j = 0; j < 16; j++)
	    {
		    des[j + tmp] ^= IV[j];
            IV[j] = src[j + tmp];
	    }
    }
}