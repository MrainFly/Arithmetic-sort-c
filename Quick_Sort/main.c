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

#define RANDOM_BUFFER_NUM         (50)
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

static int quick_sort_function(uint8_t* buffer, uint32_t num){
    if(num < 2){
        return 0;
    }
    // select base
    uint8_t base = buffer[0], temp;
    int32_t i, j;
    for(i = 1, j = 0; i < num; i++){
        // 如果数小于基准时，将它移动至基准左边
        if(buffer[i] < base){
            temp = buffer[i];
            buffer[i] = buffer[++j];
            buffer[j] = temp;
        }
    }

    buffer[0] = buffer[j];
    buffer[j] = base;

    // left sort
    quick_sort_function(buffer, j);
    quick_sort_function(&buffer[j+1], (num - j-1));

    return 0;
}

#define SELF_COMP(x, y)   quick_sort_function(x, y)

int main(int argc, char* argv[]) 
{
    uint32_t i = 0;

    random_generator(randombuffer, RANDOM_BUFFER_NUM);
    memcpy(dst_randombuffer, randombuffer, RANDOM_MAX_NUMBER);

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