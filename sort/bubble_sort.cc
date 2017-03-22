// 冒泡排序
void bubble_sort(int arr[], int len)  
{  
    int i, j;  
    for (i = 0; i < len; i++)  
        for (j = 1; j < len - i; j++)  
            if (arr[j - 1] > arr[j])  
                swap(arr[j - 1], arr[j]);  
}


// 冒泡排序改进①
// 通过设置标志位来记录此次遍历有无数据交换，进而可以判断是否要继续循环
void bubble_sort(int arr[], int len)
{
    for (int i = 0; i < len-1; i++){        //比较n-1次
        bool exchange = true;               //冒泡的改进，若在一趟中没有发生逆序，则该序列已有序
        for (int j = len-1; j >i; j--){     //每次从后边冒出一个最小值
            if (arr[j] < arr[j - 1]){       //发生逆序，则交换
                swap(arr[j], arr[j - 1]);
                exchange = false;
            }
        }
        if (exchange){
            return;
        }
    }
}

// 冒泡排序改进② 
// 记录某次遍历时最后发生数据交换的位置pos,
// 由于pos位置之后的记录均已交换到位,故在进行下一趟排序时只要扫描到pos位置即可。
void bubble_sort(int arr[], int len)  
{  
    int j, k;  
    int flag;  

    flag = len;  
    while (flag > 0)  
    {  
        k = flag;  
        flag = 0;  
        for (j = 1; j < k; j++)  
            if (arr[j - 1] > arr[j])  
            {  
                swap(arr[j - 1], arr[j]);  
                flag = j;  
            }  
    }  
}