#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define RANDOM_BUFFER_NUM         (50)
#define RANDOM_MAX_NUMBER         (256)

static uint8_t randombuffer[RANDOM_BUFFER_NUM] = {0};

static void random_generator(uint8_t* buffer, uint32_t num){
    uint32_t i = 0;
    for(i = 0; i < num; i++){
        buffer[i] = rand()%RANDOM_MAX_NUMBER;
    }
}

static int selection_sort_function(uint8_t* buffer, uint32_t num){
    uint32_t position, i;    
    uint8_t temp_position, temp;
    // 共轮询   num-2
    for(position = 0; position < (num - 1); position++){
        // 初始化min
        uint8_t cur_min = buffer[position];

        for(i = position + 1; i < num; i++){
            if(cur_min > buffer[i]){  // cur_min =>  buffer[temp_position] 
                cur_min = buffer[i];
                temp_position = i;
            }
        }
        // 获取起始位置的数据大小
        temp = buffer[position];

        // exchange
        buffer[position] = cur_min;
        buffer[temp_position] = temp;
    }
}

int main(){
    uint32_t i = 0;
    random_generator(randombuffer, RANDOM_BUFFER_NUM);
    selection_sort_function(randombuffer, RANDOM_BUFFER_NUM);
    for(i = 0; i < RANDOM_BUFFER_NUM; i++){
        printf("buffer[%d]: %d\r\n", i, randombuffer[i]);
    }
    return 0;
}