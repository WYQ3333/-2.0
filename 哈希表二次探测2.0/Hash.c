#include"Hash.h"

void HashTableInit(HashTable *pHT, size_t capacity, HashFuncType hash)
{
	pHT->array = (ItemType *)malloc(sizeof(ItemType)*capacity);//Ҫ��̬�����ڴ�ռ�
	pHT->capacity = capacity;
	pHT->size = 0;
	pHT->hash = hash;
	for (int i = 0; i < capacity; i++)
	{
		pHT->array[i].state = EMPTY;//ע�⣬��ʱҪ��array�е�Ԫ�ص�״̬��ʼ��Ϊ��
	}
}

int HashSearch(HashTable *pHT, KeyType key)
{
	size_t index = pHT->hash(key, pHT->capacity);//���ҵ�ʱ��һ����Ҫ���±�
	//size_t index = origin_index;
	//int i = 1;
	while (1)
	{
		if (pHT->array[index].state == EMPTY)//û�ҵ�
		{
			return -1;
		}
		if (pHT->array[index].state == EXIST&&pHT->array[index].key == key)//�ҵ��ˣ������±�
		{
			return index;
		}
		index = (origin_index + i*i) % pHT->capacity;//ѭ��,�±�һֱ��������Χ�ڱ仯
		i++;
	}
}

void EcpandIfRequired(HashTable *pHT)
{
	if (pHT->size * 10 / pHT->capacity < 8)
	{
		return;//������
	}
	HashTable temp;
	HashTableInit(&temp, 2 * pHT->capacity, pHT->hash);
	for (size_t i = 0; i < pHT->capacity; i++)
	{
		//���pHT->array[i].key���ڲ������룬����������
		if (pHT->array[i].state == EXIST)
		{
			HashInsert(&temp, pHT->array[i].key);//���ᷢ��ѭ������
		}
	}
	free(pHT->array);
	pHT->array = temp.array;
	pHT->capacity = temp.capacity;
}
//�������ӣ�������ʱ���������ݣ����ᷢ��ѭ������
int HashInsert(HashTable *pHT, KeyType key)//����
{
	if (HashSearch(pHT, key) != -1)
	{
		return -1;//��ֵ����ʧ��,��ֹ�ظ�����
	}
	EcpandIfRequired(pHT);//����
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

int HashDelete(HashTable *pHT, KeyType key)//��ϣɾ��
{
	size_t index = pHT->hash(key, pHT->capacity);
	while (pHT->array[index].state != EMPTY)
	{
		if (pHT->array[index].state == EXIST&&pHT->array[index].key == key)
		{
			pHT->array[index].state = DEL;//��״̬��Ϊɾ��״̬
			pHT->size--;//ע��ɾ�����Ԫ�ظ���Ҫ��һ
			return index;
		}
		index = (index + 1) % pHT->capacity;
	}
	return -1;//ɾ��ʧ��
}

void HashTableDestory(HashTable *pHT)
{
	free(pHT->array);
	pHT->capacity = 0;
	pHT->size = 0;
	pHT->hash = NULL;
}