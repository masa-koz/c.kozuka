#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

struct MyData {
	RB_ENTRY(MyData) entry;
	int num;
};

int
MyDataCompare(
	struct MyData *a,
	struct MyData *b
)
{
	return a->num - b->num;
}

RB_HEAD(MyDataEntries, MyData) Head = RB_INITIALIZER(&Head);

RB_PROTOTYPE(MyDataEntries, MyData, entry, MyDataCompare);
RB_GENERATE(MyDataEntries, MyData, entry, MyDataCompare);

int __cdecl
main(void)
{
	int i, mod;
	struct MyData *data, find;

	mod = 0;
Retry:
	for (i = 0; i < 256; i++) {
		if ((i % 3) != mod)
			continue;
		data = malloc(sizeof(struct MyData));
		if (data != NULL) {
			memset(data, 0, sizeof(struct MyData));
			data->num = i;
			RB_INSERT(MyDataEntries, &Head, data);
			printf("%d,", data->num);
		}
	}
	mod++;
	if (mod < 3) {
		goto Retry;
	}
	printf("\n");

	RB_FOREACH(data, MyDataEntries, &Head) {
		printf("%d,", data->num);
	}
	printf("\n");

	find.num = 128;
	data = RB_FIND(MyDataEntries, &Head, &find);
	printf("data(%p)->num(%d)\n", data, data ? data->num : -1);
	return 0;
}