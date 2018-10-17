#include"Hash.h"

void HashTableInit(HashTable *pHT, size_t capacity, HashFuncType hash)
{
	pHT->array = (ItemType *)malloc(sizeof(ItemType)*capacity);//要动态开辟内存空间
	pHT->capacity = capacity;
	pHT->size = 0;
	pHT->hash = hash;
	for (int i = 0; i < capacity; i++)
	{
		pHT->array[i].state = EMPTY;//注意，此时要把array中的元素的状态初始化为空
	}
}

int HashSearch(HashTable *pHT, KeyType key)
{
	size_t index = pHT->hash(key, pHT->capacity);//查找的时候一定先要求下标
	//size_t index = origin_index;
	//int i = 1;
	while (1)
	{
		if (pHT->array[index].state == EMPTY)//没找到
		{
			return -1;
		}
		if (pHT->array[index].state == EXIST&&pHT->array[index].key == key)//找到了，返回下标
		{
			return index;
		}
		index = (origin_index + i*i) % pHT->capacity;//循环,下标一直在容量范围内变化
		i++;
	}
}

void EcpandIfRequired(HashTable *pHT)
{
	if (pHT->size * 10 / pHT->capacity < 8)
	{
		return;//不扩容
	}
	HashTable temp;
	HashTableInit(&temp, 2 * pHT->capacity, pHT->hash);
	for (size_t i = 0; i < pHT->capacity; i++)
	{
		//如果pHT->array[i].key存在才做插入，否则不做插入
		if (pHT->array[i].state == EXIST)
		{
			HashInsert(&temp, pHT->array[i].key);//不会发生循环调用
		}
	}
	free(pHT->array);
	pHT->array = temp.array;
	pHT->capacity = temp.capacity;
}
//负载因子，利用临时变量做扩容，不会发生循环调用
int HashInsert(HashTable *pHT, KeyType key)//插入
{
	if (HashSearch(pHT, key) != -1)
	{
		return -1;//有值插入失败,防止重复插入
	}
	EcpandIfRequired(pHT);//扩容
	size_t index = pHT->hash(key, pHT->capacity);
	while (1)
	{
		if (pHT->array[index].state != EXIST)
		{
			break;
		}
		index = (index + 1) % pHT->capacity;
	}
	pHT->array[index].key = key;
	pHT->array[index].state = EXIST;
	pHT->size++;
}

int HashDelete(HashTable *pHT, KeyType key)//哈希删除
{
	size_t index = pHT->hash(key, pHT->capacity);
	while (pHT->array[index].state != EMPTY)
	{
		if (pHT->array[index].state == EXIST&&pHT->array[index].key == key)
		{
			pHT->array[index].state = DEL;//将状态置为删除状态
			pHT->size--;//注意删除后的元素个数要减一
			return index;
		}
		index = (index + 1) % pHT->capacity;
	}
	return -1;//删除失败
}

void HashTableDestory(HashTable *pHT)
{
	free(pHT->array);
	pHT->capacity = 0;
	pHT->size = 0;
	pHT->hash = NULL;
}