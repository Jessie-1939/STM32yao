#include "yi.h"
#include <stdlib.h>
#include <time.h>

// 实现 yao_function() 如果它在这里定义，否则确保已正确包含其定义
int yao_function(void) {
    int a = 50, b = 50 - 1, c ,left_hand = 1,yao = 1;
    int left,right;
    // 初始化随机数生成器的种子
      // 生成随机数
    int randomNumber = rand();
     //a为大衍数 b为大衍减一后的49 c为每次运算后的艹
    c = b;
    
    //随机一托艹（c）分成两边将
    left = randomNumber % c;
    right = c - left;
    //将右边的艹取出一个1，将这个1放到左手
    right = right - 1;
    left_hand=left_hand+1;
    //将右边的艹平均分成每4个一堆，剩余的艹放到左手
    left_hand=left_hand+right%4;
    if((right%4)==0) 
    {left_hand=left_hand+4;
      right=right-4;
        }
     else right=(right/4)*4;
    //对左手做出同样操作  将左边的艹平均分成每4个一堆，剩余的艹放到左手
    left_hand=left_hand+left%4;
    if((left%4)==0) 
    {left_hand=left_hand+4;
      left=left-4;
        }
     else  left=(left/4)*4;
    //现在完成了第一次运算 接下来还要再进行俩次运算
    c = left + right;//将左右两边的合并在一起

   

    randomNumber = rand();
    //随机一托艹（c）分成两边将
    left = randomNumber % c;
    right = c - left;
    //将右边的艹取出一个1，将这个1放到左手
    right = right - 1;
    left_hand=left_hand+1;
    //将右边的艹平均分成每4个一堆，剩余的艹放到左手
    left_hand=left_hand+right%4;
    if((right%4)==0) 
    {left_hand=left_hand+4;
      right=right-4;
        }
     else right=(right/4)*4;
    //对左手做出同样操作  将左边的艹平均分成每4个一堆，剩余的艹放到左手
    left_hand=left_hand+left%4;
    if((left%4)==0) 
    {left_hand=left_hand+4;
      left=left-4;
        }
     else  left=(left/4)*4;
  //现在完成了第二次运算 接下来还要再进行一次运算


  c = left + right;//将左右两边的合并在一起

    // 初始化随机数生成器的种子
    randomNumber = rand();
    //随机一托艹（c）分成两边将
    left = randomNumber % c;
    right = c - left;
    //将右边的艹取出一个1，将这个1放到左手
    right = right - 1;
    left_hand=left_hand+1;
    //将右边的艹平均分成每4个一堆，剩余的艹放到左手
    left_hand=left_hand+right%4;
    if((right%4)==0) 
    {left_hand=left_hand+4;
      right=right-4;
        }
     else right=(right/4)*4;
    //对左手做出同样操作  将左边的艹平均分成每4个一堆，剩余的艹放到左手
    left_hand=left_hand+left%4;
    if((left%4)==0) 
    {left_hand=left_hand+4;
      left=left-4;
        }
     else  left=(left/4)*4;
  //现在完成了第三次运算

    //将三次运算后的左右两边的艹合并在一起
    c = left + right;
    //将剩余数除以4 获得6 7 8 9 中任意一个
    yao = c / 4;

       return yao;
   }
// 实现generateYaoResults函数
int* generateYaoResults(void) {
    int* yaoResults = malloc(6 * sizeof(int));
    if (!yaoResults) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < 6; i++) {
        yaoResults[i] = yao_function();
    }

    return yaoResults;
}