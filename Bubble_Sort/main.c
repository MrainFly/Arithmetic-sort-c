#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define RANDOM_BUFFER_NUM         (50)
#define RANDOM_MAX_NUMBER         (100)

static uint8_t randombuffer[RANDOM_BUFFER_NUM] = {0};

static void random_generator(uint8_t* buffer, uint32_t num){
    uint32_t i = 0;
    for(i = 0; i < num; i++){
        buffer[i] = rand()%RANDOM_MAX_NUMBER;
    }
}

static int bubble_sort_function(uint8_t* buffer, uint32_t num){
    int8_t temp = 0;
    int32_t i,j;
    if(buffer == NULL){
        return -1;
    }

    if(num <= 1){
        return -2;
    }

    for(j = (num - 1); j > 0; j--){
        for(i = 0; i < j; i++){
            if(buffer[i] > buffer[i+1]){
                temp = buffer[i];
                buffer[i] = buffer[i+1];
                buffer[i+1] = temp;
            }
        }
    }

    return 0;
}

int main(){
    uint32_t i = 0;
    random_generator(randombuffer, RANDOM_BUFFER_NUM);
    bubble_sort_function(randombuffer, RANDOM_BUFFER_NUM);
    for(i = 0; i < RANDOM_BUFFER_NUM; i++){
        printf("buffer[%d]: %d\r\n", i, randombuffer[i]);
    }
    return 0;
}