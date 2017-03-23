// 直接插入排序
void InsertSort(int arr[], int len){
	// 检查数据合法性
	if(arr == NULL || len <= 0){
	    return;
	}
	for(int i = 1; i < len; i++){
	    int tmp = arr[i];
		int j;
		for(j = i-1; j >= 0; j--){
			//如果比tmp大把值往后移动一位
			if(arr[j] > tmp){
			   arr[j+1] = arr[j];
			}
			else{
			   break;
			}
		}
		arr[j+1] = tmp;
	}	
}

// 插入排序改进：二分插入排序
void BinaryInsertSort(int arr[], int len)   
{   
    int key, left, right, middle;   
    for (int i=1; i<len; i++)   
    {   
        key = a[i];   
        left = 0;   
        right = i-1;   
        while (left<=right)   
        {   
            middle = (left+right)/2;   
            if (a[middle]>key)   
                right = middle-1;   
            else   
				left = middle+1;   
        }   
                   
        for(int j=i-1; j>=left; j--)   
        {   
            a[j+1] = a[j];   
        }   
                   
        a[left] = key;          
    }   
}  