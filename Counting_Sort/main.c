#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
// 空间复杂度为 O(1)，因为采用in-place的方式
// 空间复杂度为 O(n^2)

// 系统自己的compare函数
static int comp (const void * elem1, const void * elem2) 
{
    return ( *(uint8_t*)elem1 - *(uint8_t*)elem2 );
}

#define COMP(x)  qsort (x, sizeof(x)/sizeof(*x), sizeof(*x), comp)

#define RANDOM_BUFFER_NUM         (10000)
#define RANDOM_MAX_NUMBER         (100)

// 参考数组和计算数组
static uint8_t randombuffer[RANDOM_BUFFER_NUM] = {0};
static uint8_t dst_randombuffer[RANDOM_BUFFER_NUM] = {0};

static void random_generator(uint8_t* buffer, uint32_t num){
    uint32_t i = 0;
    srand(time(0));
    for(i = 0; i < num; i++){
        buffer[i] = rand()%RANDOM_MAX_NUMBER;
    }
}

static int counting_sort_function(uint8_t* buffer, uint32_t num){
    // select the max and min number of the array
    int32_t i = 1;
    uint8_t max = buffer[0],min = buffer[0];
    while(i != num){
        if(buffer[i] > max){
            max = buffer[i];
        }
        if(buffer[i] < min){
            min = buffer[i];
        }
        i++;
    }

    // 创造统计数组
    uint32_t* statistics_buffer = (uint32_t*)malloc(sizeof(uint32_t) * (max - min + 1));
    memset(statistics_buffer, 0, (max - min + 1)*4);

    i = 0;

    while(i != num){
        // 统计每一个数出现的次数
        statistics_buffer[buffer[i++] - min]++;
    }    
    
    int j = 0;
    uint32_t pointer = 0;
    // 遍历统计数组
    for(i = 0; i < (max - min + 1); i++){
        // 根据统计数组来判断需要向原有数组中填充多少次该数
        for(j = 0; j < statistics_buffer[i]; j++){
            buffer[pointer++] = (i + min);            
        }
    }

    free(statistics_buffer);
    return 0;
}

#define SELF_COMP(x, y)   counting_sort_function(x, y)

int main(int argc, char* argv[]) 
{
    uint32_t i = 0;

    random_generator(randombuffer, RANDOM_BUFFER_NUM);
    memcpy(dst_randombuffer, randombuffer, RANDOM_BUFFER_NUM);

    COMP(dst_randombuffer);

    SELF_COMP(randombuffer, RANDOM_BUFFER_NUM);

    for(i = 0; i < RANDOM_BUFFER_NUM; i++){
        printf("result buffer[%d]: %d  ==>  dst buffer[%d]: %d\r\n", i, randombuffer[i], i, dst_randombuffer[i]);
    }

    if(memcmp(dst_randombuffer, randombuffer, RANDOM_BUFFER_NUM) == 0){
        printf("Memory compare success!!!\r\n");
    } else
    {
        printf("Memory compare failed!!!\r\n");
    }

    return 0;
}