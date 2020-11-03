#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
// 空间复杂度为 O(1)，因为采用in-place的方式
// 空间复杂度为 O(n^(1.3))

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
    for(i = 0; i < num; i++){
        buffer[i] = rand()%RANDOM_MAX_NUMBER;
    }
}

// 采用2分的step
// 看似最后一轮的step为1和normal insertion sort一样，但是其实每一步都只比较一点，
// 因为前面已经比较过了，所以step为2, 4, 8.....等效果都是一样，上一步的结果会导致
// 下面的最长比较时间变短
static int shell_sort_function(uint8_t* buffer, uint32_t num) {
    int32_t i,j,step = num;
    uint8_t cur;
    while(step != 1){
        step = floor(step/2);
        for(i = step; i < num; i++){
            j = i;
            cur = buffer[j];
            while(j - step >= 0 && cur < buffer[j-step]){
                buffer[j] = buffer[j-step];
                j = j - step;
            }
            buffer[j] = cur;
        }
    }

    return 0;
}

#define SELF_COMP(x, y)   shell_sort_function(x, y)

int main(int argc, char* argv[]) 
{
    uint32_t i = 0;

    random_generator(randombuffer, RANDOM_BUFFER_NUM);
    memcpy(dst_randombuffer, randombuffer, RANDOM_MAX_NUMBER);

    COMP(dst_randombuffer);

    SELF_COMP(randombuffer, RANDOM_BUFFER_NUM);

    if(memcmp(dst_randombuffer, randombuffer, RANDOM_BUFFER_NUM) == 0){
        printf("Memory compare success!!!\r\n");
    } else
    {
        printf("Memory compare failed!!!\r\n");
    }

    for(i = 0; i < RANDOM_BUFFER_NUM; i++){
        printf("result buffer[%d]: %d  ==>  dst buffer[%d]: %d\r\n", i, randombuffer[i], i, dst_randombuffer[i]);
    }

    return 0;
}