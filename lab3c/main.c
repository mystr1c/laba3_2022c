#include <stdio.h> 
#include <string.h>
#include <crtdbg.h>
#include <corecrt_malloc.h>
#pragma warning(disable : 4996)


/*
* ВАЖНО ЗАПУСТИТЬ ПРОГРАММУ С ПАРАМЕТРАМИ
* ПРОЕКТ - свойства-отладка-аргументы командной строки в текущей win32 (вписать data.csv 1)
*/

//структура для хранения информации о соструднике
typedef struct
{
	char FirstName[100];
	char LastName[100];
	char Gender[100];
	char Occupation[100];
	int  Salary;
} employee;

//фунция вырезания из строки
//пример строки s "Michael","Johnson","Male","Producer","1130"
// field это переменная в которую нужно поместить строку без кавычек

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



// переменная argc хранит количество слов (строка с пробелами) в командной строке
//если программа запускается без параметров, то argc=1 
//(первое слово - имя запускаемой программы)
//по заданию параметры программы запускаются в командной строке
//поэтому командная строка выглядит так:
// lab3.exe data.scv 1
// имя_программы имя_файла номер_дециля
//argc=3
//argv - массив строк(слов) из командной строки
//argv[0] = "lab3.exe"
//argv[1] = "data.scv"
//argv[2] = "1"
int main(int argc, char* argv[])
{
	FILE* f;
	char s[255];

	int N = 0, i;
	//адрес будущего массива структур для чтения информации из файла
	employee* m = NULL;
	employee tmp;
	int dl;


	//проверяем количество параметров
	if (argc == 3)
	{
		sscanf_s(argv[2], "%d", &dl);//из третьего параметра получаем номер дециля
		if ((dl > 0) && (dl < 11))
		{
			if (!(fopen_s(&f, argv[1], "r")))//открываем файл, имя которого во втром параметре
			{
				fgets(s, 255, f);//читаем первую строку заголовок
		//читаем файл, пока не встретим конец файла
				while (!feof(f))
				{
					fgets(s, 255, f);//читаем очередную строку во вспомогательную переменную
					m = (employee*)realloc(m, (N + 1) * sizeof(employee));//создаем новый элемент массива структур
					i = 0;
					v(s, &i, m[N].FirstName);//выделяем из строки s первую подстроку и помещаем в m[N].FirstName
					v(s, &i, m[N].LastName);//выделяем из строки s вторую подстроку и помещаем в m[N].LastName
					v(s, &i, m[N].Gender);//выделяем из строки s третью подстроку и помещаем в m[N].Gender
					v(s, &i, m[N].Occupation);//выделяем из строки s четвертую подстроку и помещаем в m[N].Occupation	
					sscanf_s(&s[i + 3], "%d", &m[N].Salary);//получаем целое число из остатка s и в m[N].Salary
					N++;//следующий элемент массива (вначале N=0)
				}
				fclose(f);//закрытие файла
		//сортировка массива по полю Salary методом пузырька
				for (i = 0; i < N - 1; i++)
				{
					for (int j = 0; j < N - 1 - i; j++)
					{
						if (m[j].Salary > m[j + 1].Salary)
						{
							//меняются местами структуры
							memcpy(&tmp, &m[j], sizeof(employee));
							memcpy(&m[j], &m[j + 1], sizeof(employee));
							memcpy(&m[j + 1], &tmp, sizeof(employee));
						}
					}
				}
				//считается сумма зарплат для заданного дециля			
				int Zp = 0;
				for (i = (dl - 1) * N / 10; i < dl * N / 10; i++)
				{
					Zp += m[i].Salary;
				}
				//печать найденной зарплаты	
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