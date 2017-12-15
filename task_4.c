//Задание 4
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
 
int main() {
	int msqid;// IPC-дескриптор для очереди сообщений 
	char pathname[] = "task_4.c";//имя файла, использующееся для для генерации ключа. Файл с таким именем должен существовать в текущей директории
	key_t key;//IPC ключ
	int i, len;//счетчик цикла и длина информативной части
	char text[32];



	struct mymsgbuf //пользовательская структура
{
		long mtype;
		char mtext[32];
	};
	struct mymsgbuf mybuf;
	int fd = open("file.txt", O_RDONLY | O_CREAT);//в качестве параметра flags используем O_RDONLY(только чтение); комбинируем с побитовйо операцией | с флагом O_CREAT(файла с указанным именем не существует, он должен быть создан)

	for(i = 0; i < 5; i++) {
	read(fd, text, 32);//read(int fd, void*addr,size_t nbytes); здесь мы передаем 9 байтов
	printf("%s\n", text);// печатаем текст сообщения
	key = ftok(pathname, 0);//генерирует IPC ключ
	msqid = msgget(key, 0666 | IPC_CREAT);// msgget предназначен для выполнения операции доступа к очереди сообщений; флаг IPC_CREAT означает, что очереди для указанного ключа не существует, она должна быть создана
//заполняем структуру
	mybuf.mtype = 1;
	strcpy(mybuf.mtext, text);
	msgsnd(msqid, &mybuf, 32,0);//msgsnd предназначен для помещения сообщений в очередь сообщений
	}
	close(fd);
	return 0;
}
