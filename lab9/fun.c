#include "prot.h"

void bees(int bee_p, int shmid, int i)
{
	int *s, *shm;

	while (1)
	{
		if ((shm = shmat(shmid, NULL, 0)) == (int *) -1)
		{
			perror("shmat");
			exit(1);
		}

		s = shm;
		if (s[1] == 0)
		{
			printf("Мишка умёр и пчёла номер %d тоже\n", i + 1);
			break;
		}
		else
		{
			srand(time(NULL));
			srand(rand());
			int r_h = minr + rand() % maxr;
			s[0] += bee_p;
			printf("Пчёла %d принесла мёд, теперь мёда %d единиц\n", i + 1, s[0]);
			sleep(r_h);
		}
		if (shmdt(shm) < 0)
		{
			printf("Ошибка отключения\n");
			exit(1);
		}
	}
	exit(0);
}

void bear(int h_p, int lt, int shmid)
{
	int *s, *shm, flag = 0;
	if ((shm = shmat(shmid, NULL, 0)) == (int *) -1)
	{
		perror("shmat");
		exit(1);
	}

	s = shm;
	while (1)
	{
		if (s[0] <= 0)
		{
			flag = 1;
			printf("Мишка скоро умрёт\n");
			sleep(lt);
		}
		else
		{
			printf("Мёда было %d единиц\n",
			       s[0]);
			s[0] -= h_p;
			printf("Мишка жрёт\n");
			printf("Мёда стало %d единиц\n", s[0]);
			flag = 0;
			sleep(lt);
			printf("Мишка ждёт\n");
		}
		if (s[0] <= 0 && flag == 1)
		{
			s[1] = 0;
			printf("Мишка умер\n");
			break;
		}
	}
	exit(0);
}
