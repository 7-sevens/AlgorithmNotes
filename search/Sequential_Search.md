## 顺序查找

#### 算法说明
循环遍历查找

#### 代码实现
```
int SequentialSearch(vector<int>& v, int k) {
	for (int i = 0; i < v.size(); ++i)
		if (v[i] == k)
			return i;
	return -1;
}
```
