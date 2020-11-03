#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
// 空间复杂度为 O(n)
// 空间复杂度为 O(nlog2n)

// 系统自己的compare函数
static int comp (const void * elem1, const void * elem2) 
{
    return ( *(uint8_t*)elem1 - *(uint8_t*)elem2 );
}

#define COMP(x)  qsort (x, sizeof(x)/sizeof(*x), sizeof(*x), comp)

#define RANDOM_BUFFER_NUM         (50)
#define RANDOM_MAX_NUMBER         (200)

// 参考数组和计算数组
static uint8_t randombuffer[RANDOM_BUFFER_NUM] = {0};
static uint8_t dst_randombuffer[RANDOM_BUFFER_NUM] = {0};

static void random_generator(uint8_t* buffer, uint32_t num){
    uint32_t i = 0;
    for(i = 0; i < num; i++){
        buffer[i] = rand()%RANDOM_MAX_NUMBER;
    }
}

static int merge_sort_function(uint8_t* buffer, uint32_t num){

    // reference function of merge sort ignore num==2
    // it's just split it to 2 element
    // and sort it in SORT stage
    /*if(num == 2){
        uint8_t temp = 0;
        // sort 2 element
        if(buffer[0] < buffer[1]){
            // pass
        }else{
            temp = buffer[0];
            buffer[0] = buffer[1];
            buffer[1] = temp;
        }
        return 0;
    }*/

    if(num == 1){
        // don't care
        return 0;
    }

    uint32_t left_num, right_num;
    left_num = num/2;
    right_num = num - left_num;    
    uint8_t * left_buffer = buffer;
    uint8_t * right_buffer = buffer + left_num;

    merge_sort_function(left_buffer, left_num);
    merge_sort_function(right_buffer, right_num);

    uint8_t* temp_buffer = NULL;
    temp_buffer = (uint8_t*) malloc(num);
    // merge
    uint32_t i = 0, j = 0, k = 0;

    // sort 2 element
    while((i < left_num) && (j < right_num)){
        if(left_buffer[i] < right_buffer[j]){
            temp_buffer[k++] = left_buffer[i++];
        }else{
            temp_buffer[k++] = right_buffer[j++];
        }
    }

    while(i < left_num){
        temp_buffer[k++] = left_buffer[i++];
    }

    while(j < right_num){
        temp_buffer[k++] = right_buffer[j++];
    }

    // copy temporary memory which sorted to destination buffer
    memcpy(buffer, temp_buffer, num);

    free(temp_buffer);

    return 0;
}

#define SELF_COMP(x, y)   merge_sort_function(x, y)

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