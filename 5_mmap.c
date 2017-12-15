#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>/*mmap задает сегмент памяти, который может читаться двумя или несколькими программами и в который они могут записывать данные*/
#include <fcntl.h>
#include <string.h>
/*
Использование системного вызова mmap()
void*mmap(void*start; size_t length, int prot,int fd,off_t offset);
*/

int main(int argc, char const *argv[])
{
	int fd1, fd2;//файловые дeскрипторы для файлов
    int l;//длина отображаемой части файла
	void *ptr1, *ptr2;// указатели начального адреса выделенной памяти

	if ((fd1 = open(argv[1], O_RDONLY)) < 0) //открываем нужный нам файл, используя системный вызов open() 
{
		printf("File opened failed!\n");//файл не удалось открыть, выдаем сообщение об ошибки и завершаем работу
		exit(1);
	}
	if ((fd2 = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0) {
		printf("File opened failed!\n");//файл не удалось открыть, выдаем сообщение об ошибки и завершаем работу
		exit(1);
	}
	l = lseek(fd1, 0, SEEK_END);/*используется для перемещения указателя в лю-
         бое место файла, макрос SEEK_END определяет конец файла */
	ftruncate(fd2, l );//увеличиваем длину файла с помощью системного вызова ftruncate() 
//if(ptr == MAP_FAILED) условие ошибки
	if ((ptr1 = mmap(NULL, l, PROT_READ, MAP_SHARED, fd1, 0)) == MAP_FAILED) //здесь в качесте параметра flags используется его значение, MAP_SHARED; в качестве параметра prot используется PROT_READ(разрешено читать)
{
		printf("Failed\n");//если отобразить файл не удалось, сообщаем об ощибке и завершаем работу
		exit(1);
	}
	close(fd1);//закрывает файловый дескриптор, он нам больше не нужен
	if ((ptr2 = mmap(NULL, l, PROT_WRITE, MAP_SHARED, fd2, 0)) == MAP_FAILED) {
		printf("Failed\n");//если отобразить файл не удалось, сообщаем об ощибке и завершаем работу
		exit(1);
	}

	memcpy(ptr2, ptr1, l);
	munmap(ptr1, l);// munmap служит для прекращения отображения memory mapped файла в адресное пространство вычислительной системы  
	munmap(ptr2, l);
	return 0;
}
