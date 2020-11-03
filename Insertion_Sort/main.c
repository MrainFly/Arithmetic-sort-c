#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
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
    for(i = 0; i < num; i++){
        buffer[i] = rand()%RANDOM_MAX_NUMBER;
    }
}

// in-place array
static int insertion_sort_function(uint8_t* buffer, uint32_t num){
    uint32_t position, i; 
    uint8_t cur;
    uint8_t flag = 0;
    for(position = 1; position < num; position++){
        cur = buffer[position];
        for(i = position; i > 0; i--){
            if(cur >= buffer[i-1]){
                // exchange
                buffer[i] = cur;
                flag = 1;
                break;
            } else {
                // pass
                buffer[i] = buffer[i-1];
            }
        }
        // 没有触发过一次交换
        if (flag == 0){
            buffer[0] = cur;
        }
        flag = 0;
    }
}

// reference function of insertion sort
// reference fucntion is more better than function wirte by my self
static int insertion_sort_ref_function(uint8_t* buffer, uint32_t num) {
    int32_t preIndex, i;
    uint8_t current;
    for(i = 1; i < num; i++) {
        preIndex = i - 1;
        current = buffer[i];
        while((preIndex >= 0) && (buffer[preIndex] > current)) {
            buffer[preIndex + 1] = buffer[preIndex];
            preIndex--;
        }
        buffer[preIndex + 1] = current;
    }
    return 0;
}

#define SELF_COMP(x, y)   insertion_sort_ref_function(x, y)

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