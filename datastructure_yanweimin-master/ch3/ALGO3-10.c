/* algo3-10.c Hanoi������,�����㷨3.5�ĳ��� */
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>

int c = 0; /* ȫ�ֱ������ᶯ���� */

void move(char x, int n, char z)
{ /* ��n��Բ�̴�����x�ᵽ����z */
	printf("��%i��: ��%i���̴�%c�Ƶ�%c\n", ++c, n, x, z);
}

void hanoi(int n, char x, char y, char z) /* �㷨3.5 */
{ /* ������x�ϰ�ֱ����С���������϶��±��Ϊ1��n��n��Բ�� */
  /* ������ᵽ����z�ϡ�y�������������� */
	if (n == 1)
		move(x, 1, z); /* �����Ϊ1��Բ�̴�x�Ƶ�z */
	else
	{
		hanoi(n - 1, x, z, y); /* ��x�ϱ��Ϊ1��n-1��Բ���Ƶ�y��z�������� */
		move(x, n, z); /* �����Ϊn��Բ�̴�x�Ƶ�z */
		hanoi(n - 1, y, x, z); /* ��y�ϱ��Ϊ1��n-1��Բ���Ƶ�z��x�������� */
	}
}

void main()
{
	int n;
	printf("3������Ϊa��b��c��Բ�������a��������b���Ƶ�c����������Բ������");
	scanf("%d", &n);
	hanoi(n, 'a', 'b', 'c');
}