#pragma once


#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

//闭散列的哈希表不能直接删除，状态标记的方法处理删除
typedef enum
{
	EMPTY,
	EXIST,
	DEL
}State;

typedef int KeyType;
//函数指针，指向哈希函数，返回值为size_t类型的下标,将函数指针重命名为HashFuncType类型
typedef size_t(*HashFuncType)(KeyType key, size_t capacity);

typedef struct
{
	KeyType key;
	State state;
}ItemType;

typedef struct HashTable
{
	ItemType *array;
	size_t size;//数据个数
	size_t capacity;//整个空间的大小
	HashFuncType hash;//哈希函数
}HashTable;

//时间复杂度统一为O(1)
void HashTableInit(HashTable *pHT, size_t capacity, HashFuncType hash);
void HashTableDestory(HashTable *pHT);//销毁哈希表
int HashSearch(HashTable *pHT, KeyType key);//哈希查找
int HashDelete(HashTable *pHT, KeyType key);//哈希删除
int HashInsert(HashTable *pHT, KeyType key);//插入
void EcpandIfRequired(HashTable *pHT);//扩容