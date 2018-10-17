#pragma once


#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

//��ɢ�еĹ�ϣ����ֱ��ɾ����״̬��ǵķ�������ɾ��
typedef enum
{
	EMPTY,
	EXIST,
	DEL
}State;

typedef int KeyType;
//����ָ�룬ָ���ϣ����������ֵΪsize_t���͵��±�,������ָ��������ΪHashFuncType����
typedef size_t(*HashFuncType)(KeyType key, size_t capacity);

typedef struct
{
	KeyType key;
	State state;
}ItemType;

typedef struct HashTable
{
	ItemType *array;
	size_t size;//���ݸ���
	size_t capacity;//�����ռ�Ĵ�С
	HashFuncType hash;//��ϣ����
}HashTable;

//ʱ�临�Ӷ�ͳһΪO(1)
void HashTableInit(HashTable *pHT, size_t capacity, HashFuncType hash);
void HashTableDestory(HashTable *pHT);//���ٹ�ϣ��
int HashSearch(HashTable *pHT, KeyType key);//��ϣ����
int HashDelete(HashTable *pHT, KeyType key);//��ϣɾ��
int HashInsert(HashTable *pHT, KeyType key);//����
void EcpandIfRequired(HashTable *pHT);//����