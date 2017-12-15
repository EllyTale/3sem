#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
/*
системный вызов pipe предназначен для создания pip'a внутри операционной системы;
важное отличие pip'a от файла заключается в том, что прочитанная информаци немедленно удаляется из него и не может быть прочитана повторно;
int pipe(int*fd);
параметр fd является указателем на массив двух целых переменных
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

struct dpipe_t{
	int txd[2];
	int rxd[2];
};

int main() {
	struct dpipe_t fd;
	size_t size;
	int status;
	char buf1[4096], buf2[4096];
	char str1[4096], str2[4096];


	fgets(str1, 4095, stdin);
	
	fgets(str2, 4095, stdin);

	if (pipe(fd.txd) == -1) //создать pipe не удалось, печатаем сообщение об ошибке
{
               perror("pipe");
               printf("Can't create pipe\n");
               exit(-1);
           }

    if (pipe(fd.rxd) == -1) //создать pipe не удалось, печатаем сообщение об ошибке
{
    	perror("pipe");
    	printf("Can't create pipe\n\n");
    	exit(-1);
    } 

    pid_t pid = fork();
	if (pid == -1) {
		printf("FAILED\n");
		exit(-1);  
	}

	if (pid > 0) 		//это родитель
		{size = write(fd.txd[1], str1, strlen(str1));//пробуем записать в pipe 
		if (size == -1) //если записалось меньшее количество байт сообщаем об ошибке
{
			printf("Can't write\n");
			exit(-1);
		}
		close(fd.txd[1]);

		waitpid(pid, &status, 0);

		size = read(fd.rxd[0], buf1, strlen(str2));//пробуем прочитать
		if (size == -1) //если прочитать не смогли сообщаем об ошибке
{
			printf("Can't read\n");
			exit(-1);
		}
		printf("%s",buf1);
		close(fd.rxd[0]);
	}

	if (pid == 0) {		//это ребенок
		size = read(fd.txd[0], buf2, strlen(str1));//пробуем прочитать
		if (size == -1) //ошибка
{
			printf("Can't read\n");
			exit(-1);
		}
		printf("%s",buf2);
		close(fd.txd[0]);

		size = write(fd.rxd[1], str2, strlen(str2));//пробуем записать
			{printf("Can't write\n");
			exit(-1);
		}
		close(fd.rxd[1]);
	}

	return 0;
}
