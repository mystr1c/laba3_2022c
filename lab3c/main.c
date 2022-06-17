#include <stdio.h> 
#include <string.h>
#include <crtdbg.h>
#include <corecrt_malloc.h>
#pragma warning(disable : 4996)


/*
* ����� ��������� ��������� � �����������
* ������ - ��������-�������-��������� ��������� ������ � ������� win32 (������� data.csv 1)
*/

//��������� ��� �������� ���������� � �����������
typedef struct
{
	char FirstName[100];
	char LastName[100];
	char Gender[100];
	char Occupation[100];
	int  Salary;
} employee;

//������ ��������� �� ������
//������ ������ s "Michael","Johnson","Male","Producer","1130"
// field ��� ���������� � ������� ����� ��������� ������ ��� �������

void v(char s[], int* k, char field[])
{

	int i = *k;
	while ((s[i] == ',') || (s[i] == '\"'))
	{
		i++;
	}
	int j = 0;
	while (s[i] != '\"')
	{
		field[j] = s[i];
		i++;
		j++;
	}
	field[j] = '\0';
	*k = i;
}



// ���������� argc ������ ���������� ���� (������ � ���������) � ��������� ������
//���� ��������� ����������� ��� ����������, �� argc=1 
//(������ ����� - ��� ����������� ���������)
//�� ������� ��������� ��������� ����������� � ��������� ������
//������� ��������� ������ �������� ���:
// lab3.exe data.scv 1
// ���_��������� ���_����� �����_������
//argc=3
//argv - ������ �����(����) �� ��������� ������
//argv[0] = "lab3.exe"
//argv[1] = "data.scv"
//argv[2] = "1"
int main(int argc, char* argv[])
{
	FILE* f;
	char s[255];

	int N = 0, i;
	//����� �������� ������� �������� ��� ������ ���������� �� �����
	employee* m = NULL;
	employee tmp;
	int dl;


	//��������� ���������� ����������
	if (argc == 3)
	{
		sscanf_s(argv[2], "%d", &dl);//�� �������� ��������� �������� ����� ������
		if ((dl > 0) && (dl < 11))
		{
			if (!(fopen_s(&f, argv[1], "r")))//��������� ����, ��� �������� �� ����� ���������
			{
				fgets(s, 255, f);//������ ������ ������ ���������
		//������ ����, ���� �� �������� ����� �����
				while (!feof(f))
				{
					fgets(s, 255, f);//������ ��������� ������ �� ��������������� ����������
					m = (employee*)realloc(m, (N + 1) * sizeof(employee));//������� ����� ������� ������� ��������
					i = 0;
					v(s, &i, m[N].FirstName);//�������� �� ������ s ������ ��������� � �������� � m[N].FirstName
					v(s, &i, m[N].LastName);//�������� �� ������ s ������ ��������� � �������� � m[N].LastName
					v(s, &i, m[N].Gender);//�������� �� ������ s ������ ��������� � �������� � m[N].Gender
					v(s, &i, m[N].Occupation);//�������� �� ������ s ��������� ��������� � �������� � m[N].Occupation	
					sscanf_s(&s[i + 3], "%d", &m[N].Salary);//�������� ����� ����� �� ������� s � � m[N].Salary
					N++;//��������� ������� ������� (������� N=0)
				}
				fclose(f);//�������� �����
		//���������� ������� �� ���� Salary ������� ��������
				for (i = 0; i < N - 1; i++)
				{
					for (int j = 0; j < N - 1 - i; j++)
					{
						if (m[j].Salary > m[j + 1].Salary)
						{
							//�������� ������� ���������
							memcpy(&tmp, &m[j], sizeof(employee));
							memcpy(&m[j], &m[j + 1], sizeof(employee));
							memcpy(&m[j + 1], &tmp, sizeof(employee));
						}
					}
				}
				//��������� ����� ������� ��� ��������� ������			
				int Zp = 0;
				for (i = (dl - 1) * N / 10; i < dl * N / 10; i++)
				{
					Zp += m[i].Salary;
				}
				//������ ��������� ��������	
				printf("Decile %d Sum salary %d\n", dl, Zp);



			}
			else
				printf("file not found\n");
		}
		else
			printf("uncorrect decile\n");
	}
	else
		printf("parameters error\n");
	return 0;
}