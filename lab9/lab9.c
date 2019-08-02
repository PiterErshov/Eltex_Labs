#include "prot.h"

int main(int argc, char *argv[])
{
	int *shm, *s, shmid, count = 10;

	if (argc < 5)
	{
		fprintf(stderr,
			"Не верное число параметров\n");
		fprintf(stderr,
			"Используйте формат %s n_bees bee_portion honey_portion lifetime\n",
			argv[0]);
		exit(1);
	}
	int k = 0;
	int n_bees = atoi(argv[1]) + 1,
		bee_p = atoi(argv[2]),
		int_size = atoi(argv[3]), lt = atoi(argv[4]);
	pid_t pid[n_bees + 1];

	if ((shmid = shmget(IPC_PRIVATE, sizeof (int), IPC_CREAT | 0666)) < 0)
	{
		perror("shmget");
		exit(1);
	}
	if ((shm = shmat(shmid, NULL, 0)) == (int *) -1)
	{
		perror("shmat");
		exit(1);
	}

	s = shm;
	s[1] = 1;
	for (int i = 0; i < n_bees; i++)
	{
		pid[i] = fork();
		if (-1 == pid[i])
		{
			perror("fork");	/* произошла ошибка */
			exit(1);	/*выход из родительского процесса */
		}
		else if (0 == pid[i])
		{
			if (i < n_bees - 1)
				bees(bee_p, shmid, i);
			else
				bear(int_size, lt, shmid);
		}
	}
	for (int i = 0; i < n_bees; i++)
	{
		int stat;
		waitpid(pid[i], &stat, 0);
	}
	if (shmdt(shm) < 0)
	{
		printf("Ошибка отключения\n");
		exit(1);
	}
	if (shmctl(shmid, IPC_RMID, 0) < 0)
	{
		printf("Невозможно удалить область\n");
		exit(1);
	}
	return 0;
}
