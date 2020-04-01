----------

#### 计数排序（Counting Sort）
计数排序（Counting sort）是一种稳定的线性时间排序算法。

##### 1. 基本思想
计数排序使用一个额外的数组C，其中第i个元素是待排序数组A中值等于i的元素的个数。

计数排序的核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。

用来计数的数组C的长度取决于待排序数组中数据的范围（等于待排序数组的最大值与最小值的差加上1），然后进行分配、收集处理：

> - **分配**。扫描一遍原始数组，以当前值-minValue作为下标，将该下标的计数器增1。
> - **收集**。扫描一遍计数器数组，按顺序把值收集起来。

##### 2. 实现逻辑

> - 找出待排序的数组中最大和最小的元素
> - 统计数组中每个值为i的元素出现的次数，存入数组C的第i项
> - 对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）
> - 反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1

##### 3. 动图演示

![这里写图片描述](./image/counting_sort.gif)

举个例子，假设有无序数列nums=[2, 1, 3, 1, 5], 首先扫描一遍获取最小值和最大值，maxValue=5, minValue=1，于是开一个长度为5的计数器数组counter

> **(1) 分配**
> 统计每个元素出现的频率，得到counter=[2, 1, 1, 0,
> 1]，例如counter[0]表示值0+minValue=1出现了2次。
>
> **(2) 收集**
> counter[0]=2表示1出现了两次，那就向原始数组写入两个1，counter[1]=1表示2出现了1次，那就向原始数组写入一个2，依次类推，最终原始数组变为[1,1,2,3,5]，排序好了。

##### 4. 复杂度分析
> - 平均时间复杂度：O(n + k)
> - 最佳时间复杂度：O(n + k)
> - 最差时间复杂度：O(n + k)
> - 空间复杂度：O(n + k)

当输入的元素是n 个0到k之间的整数时，它的运行时间是 O(n + k)。。在实际工作中，当k=O(n)时，我们一般会采用计数排序，这时的运行时间为O(n)。

计数排序需要两个额外的数组用来对元素进行计数和保存排序的输出结果，所以空间复杂度为O(k+n)。

计数排序的一个重要性质是它是稳定的：具有相同值的元素在输出数组中的相对次序与它们在输入数组中的相对次序是相同的。也就是说，对两个相同的数来说，在输入数组中先出现的数，在输出数组中也位于前面。

计数排序的稳定性很重要的一个原因是：计数排序经常会被用于基数排序算法的一个子过程。我们将在后面文章中介绍，为了使基数排序能够正确运行，计数排序必须是稳定的。

##### 5. 代码实现
**C版本：**

```
// 计数排序（C）
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void print_arr(int *arr, int n) {
	int i;
	printf("%d", arr[0]);
	for (i = 1; i < n; i++)
		printf(" %d", arr[i]);
	printf("\n");
}
void counting_sort(int *ini_arr, int *sorted_arr, int n) {
	int *count_arr = (int *) malloc(sizeof(int) * 100);
	int i, j, k;
	for (k = 0; k < 100; k++)
		count_arr[k] = 0;
	for (i = 0; i < n; i++)
		count_arr[ini_arr[i]]++;
	for (k = 1; k < 100; k++)
		count_arr[k] += count_arr[k - 1];
	for (j = n; j > 0; j--)
		sorted_arr[--count_arr[ini_arr[j - 1]]] = ini_arr[j - 1];
	free(count_arr);
}
int main(int argc, char **argv) {
	int n = 10;
	int i;
	int *arr = (int *) malloc(sizeof(int) * n);
	int *sorted_arr = (int *) malloc(sizeof(int) * n);
	srand(time(0));
	for (i = 0; i < n; i++)
		arr[i] = rand() % 100;
	printf("ini_array: ");
	print_arr(arr, n);
	counting_sort(arr, sorted_arr, n);
	printf("sorted_array: ");
	print_arr(sorted_arr, n);
	free(arr);
	free(sorted_arr);
	return 0;
}
```

**Java版本：**

```
// 计数排序(Java)
public class CountingSort {
    public static void main(String[] argv) {
        int[] A = CountingSort.countingSort(new int[]{16, 4, 10, 14, 7, 9, 3, 2, 8, 1});
        Utils.print(A);
    }
    public static int[] countingSort(int[] A) {
        int[] B = new int[A.length];
        // 假设A中的数据a'有，0<=a' && a' < k并且k=100
        int k = 100;
        countingSort(A, B, k);
        return B;
    }
    private static void countingSort(int[] A, int[] B, int k) {
        int[] C = new int[k];
        // 计数
        for (int j = 0; j < A.length; j++) {
            int a = A[j];
            C[a] += 1;
        }
        Utils.print(C);
        // 求计数和
        for (int i = 1; i < k; i++) {
            C[i] = C[i] + C[i - 1];
        }
        Utils.print(C);
        // 整理
        for (int j = A.length - 1; j >= 0; j--) {
            int a = A[j];
            B[C[a] - 1] = a;
            C[a] -= 1;
        }
    }
}
```

##### 6. 优化改进
**6.1 场景分析**
举个极端的例子：如果排序的数组有200W个元素，但是这200W个数的值都在1000000-1000100，也就说有100个数，总共重复了200W次，现在要排序，怎么办？

这种情况排序，计数排序应该是首选。但是这时候n的值为200W，如果按原来的算法，k的值10001000，但是此时c中真正用到的地方只有100个，这样对空间造成了极大的浪费。

**6.2 改进思路**
针对c数组的大小，优化计数排序

**6.3 改进代码**

```
// 计数排序优化(Java)
// 针对c数组的大小，优化计数排序
public class CountSort{
	public static void main(String []args){
		//排序的数组
		int a[] = {100, 93, 97, 92, 96, 99, 92, 89, 93, 97, 90, 94, 92, 95};
		int b[] = countSort(a);
		for(int i : b){
			System.out.print(i + "  ");
		}
		System.out.println();
	}
	public static int[] countSort(int []a){
		int b[] = new int[a.length];
		int max = a[0], min = a[0];
		for(int i : a){
			if(i > max){
				max = i;
			}
			if(i < min){
				min = i;
			}
		}
		//这里k的大小是要排序的数组中，元素大小的极值差+1
		int k = max - min + 1;
		int c[] = new int[k];
		for(int i = 0; i < a.length; ++i){
			c[a[i]-min] += 1;//优化过的地方，减小了数组c的大小
		}
		for(int i = 1; i < c.length; ++i){
			c[i] = c[i] + c[i-1];
		}
		for(int i = a.length-1; i >= 0; --i){
			b[--c[a[i]-min]] = a[i];//按存取的方式取出c的元素
		}
		return b;
	}
}
```

----------

#### 总结
计数算法只能使用在已知序列中的元素在0-k之间，且要求排序的复杂度在线性效率上。
Â
计数排序和基数排序很类似，都是非比较型排序算法。但是，它们的核心思想是不同的，基数排序主要是按照进制位对整数进行依次排序，而计数排序主要侧重于对有限范围内对象的统计。基数排序可以采用计数排序来实现。

---
---
**PS**: 更多资源，欢迎关注微信公众号：developer1024

![这里写图片描述](./image/wechat_qrcode.jpeg)
