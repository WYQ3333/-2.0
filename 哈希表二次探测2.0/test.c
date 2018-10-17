#include"Hash.h"

size_t mod(KeyType key, size_t capacity)
{
	return key%capacity;
}

void test()
{
	HashTable ht;
	HashTableInit(&ht, 7, mod);
	HashInsert(&ht, 0);
	HashInsert(&ht, 7);
	HashInsert(&ht, 14);
	HashInsert(&ht, 21);
	HashInsert(&ht, 28);
	HashInsert(&ht, 8);
	HashInsert(&ht, 9);
	HashInsert(&ht, 10);
	HashDelete(&ht, 8);
	HashDelete(&ht, 9);
	HashTableDestory(&ht);
}

int main()
{
	test();
	system("pause");
	return 0;
}