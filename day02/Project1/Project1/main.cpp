#include <stdio.h> //standard input output
#include <stdlib.h> // malloc 

#define NUM 10 // c���� ���¹�� 

int main() // entry point : exe����� �޸𸮿� �ö�
{
	//int a = 100;
	//printf("Hello World. %x", &a); // & -> a������ִ� �޸��ּ�
	//// %d %x

	//// 1byte�� 8bit�� ascii�δ� �ѱ�ǥ���̾ȵ�
	//// �׷��� �����ڵ带����
	//// utf8�� 8bit�� �ѱ����ξ� 32bit�� �ѱ����ξ� �Դٰ�������

	//char b = 98; // -128 ~ 127 (0) ���� ǥ������ (1bit�� ���� +- ǥ��)
	//unsigned char c = 98; // ���ڿ� ���̳ʽ��� �Ⱦ��ڴٴ� �� 0~255���� ǥ��
	//printf("Hello World. %c", b);
	//// 98�־ %c�� ����ϸ� ���ڳ���

	//// int 32bit �ε� �����찡 32bit�� �� 4�Ⱑ�����ۿ��Ƚ���
	//// �׷��� os�� ���� int ũ�Ⱑ �ٸ���
	//// �׷��� �𸮾󿡼� int32 ó�� ���°�
	//int d;
	//printf(" aaa %d", sizeof(d));
	//unsigned int e = 0xffffffff; // int�� ���� ū��
	//printf(" largest int %u", e);

	//char r, g, b, a; // 0~255 ���伥 rgba�� char������


	////////////////////////
	////pointer//
	////////////////////////
	//int a = 2;
	//int* b = &a; // char�� �����͸� char* �ΰ���

	//printf("%x\n", &a);
	//printf("%d\n", b);
	//printf("%d\n", *b); //b�� *�����ϴ°�

	//a = 3;
	//*b = 3; // �ΰ� �Ȱ���

	//printf("%d\n", a);
	//printf("%d\n", *b);

	////unsigned char* a = 0x00000000; // ó�� �ϵ���� �ּҰ��� �ٷ������Ҽ��ִ�
	//// �����ѵ� �޸𸮿� os���� ��ŷ���������־ �ٸ����α׷��� ���ǵ��
	//// DirectX �� �׷���ī�忡 �ٷ� �����Ҽ��ִ°�
	//// OpenGL Metal Vulkan �������


	///////////////////////////
	/////�迭�� �ݺ���
	///////////////////////////

	////int kor[NUM];
	////int eng[NUM];
	////int math[NUM];
	////float avg[NUM]; NUM �����ִ´�� �ٲ��

	//int count = 0;
	//scanf("%d", &count);

	//int* kor = (int*)malloc(sizeof(int)*count); 
	//int* eng = (int*)malloc(sizeof(int)*count);
	//int* math = (int*)malloc(sizeof(int)*count);
	//float* avg = (float*)malloc(sizeof(float)*count);
	//// �迭 ����� ��� NUM �����ŭ �޸� �Ҵ�
	//// �迭�� �����ͷ� ǥ������
	//// �ϵ��ڵ��� ���ϴ� ���

	//for (int i = 0; i < count; i++)
	//{
	//	kor[i] = 100;
	//	eng[i] = 90;
	//	math[i] = 80;
	//	avg[i] = (kor[i] + eng[i] + math[i]) / 3;
	//	printf("%f\n", *(avg + i));
	//}

	//free(kor); // �����ϸ� ������ �޸� Ǯ���ֱ�
	//free(eng);
	//free(math);
	//free(avg);

	int count = 0;
	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			printf("* ");
		}
		printf("\n");
	}

}
