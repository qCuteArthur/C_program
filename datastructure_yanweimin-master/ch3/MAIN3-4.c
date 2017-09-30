/* main3-4.c ˳�����(��ѭ��),����bo3-4.c�������� */
#include "../ch1/c1.h"
typedef int QElemType;
#include "c3-3.h"
#include "bo3-4.c"

void visit(QElemType i)
{
	printf("%d ", i);
}

void main()
{
	Status j;
	int i, n;
	QElemType d;
	SqQueue Q;
	InitQueue(&Q);
	printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n", QueueEmpty(Q));
	printf("���г���Ϊ��%d\n", QueueLength(Q));
	printf("���������Ԫ�ظ���n: ");
	scanf("%d", &n);
	printf("������%d�����Ͷ���Ԫ��:\n", n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &d);
		EnQueue(&Q, d);
	}
	printf("���г���Ϊ��%d\n", QueueLength(Q));
	printf("���ڶ��пշ�%u(1:�� 0:��)\n", QueueEmpty(Q));
	printf("���ڶ����е�Ԫ��Ϊ: \n");
	QueueTraverse(Q, visit);
	DeQueue(&Q, &d);
	printf("ɾ����ͷԪ��%d\n", d);
	printf("�����е�Ԫ��Ϊ: \n");
	QueueTraverse(Q, visit);
	j = GetHead(Q, &d);
	if (j)
		printf("��ͷԪ��Ϊ: %d\n", d);
	else
		printf("�޶�ͷԪ��(�ն���)\n");
	ClearQueue(&Q);
	printf("��ն��к�, ���пշ�%u(1:�� 0:��)\n", QueueEmpty(Q));
	j = GetHead(Q, &d);
	if (j)
		printf("��ͷԪ��Ϊ: %d\n", d);
	else
		printf("�޶�ͷԪ��(�ն���)\n");
	DestroyQueue(&Q);
}