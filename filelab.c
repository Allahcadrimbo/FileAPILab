#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

//Author: Grant Mitchell 4/11/19
//CS 5631: File API Lab

int main()
{
  //Task #1
  int fd = open("test.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 

  //Task #2
  int fdEtc = open("/etc/passwd", O_RDONLY);

  char data[120000];
  int len = 101322;

  //Task #3.1
  if(read(fdEtc, data, len) < 0){
    fprintf(stderr, "An error occured in the read. \n");
  }

  //Task #3.2
  for(int i = 0; i < len; i++){
    printf("%c", data[i]); 
  }

  //Task #4
  if(write(fd, data, len) < 0){
    fprintf(stderr, "An error occured in the write. \n");
  }

  printf("\n\n\n\n\n\n\n\n------------------------Separator between test 3 and 4--------------------\n\n\n\n\n\n");


  char temp[60000];
  //Task #5
  for(int i = 0; i < len; i+=2){
    lseek(fdEtc,i, SEEK_SET);

    if(read(fdEtc, temp, 1) < 0){ 
      fprintf(stderr, "An error occured in the read. \n");
    }
    printf("%c", temp[0]);  
  }

  //Task #6
  if(fsync(fd) < 0){ 
    fprintf(stderr, "An error occured in the fsync. \n");
  }
  
  close(fd);

  //Task #7
  rename("/home/csugrads/mitc0548/cs5631/FileAPILab/test.txt",
  	 "/home/csugrads/mitc0548/cs5631/FileAPILab/testRenamed.txt");


  printf("\n\n\n\n\n\n\n\n------------------------Separator between test 4 and 8--------------------\n\n\n\n\n\n");
  //Task #8
  struct stat info;
  fstat(fdEtc, &info);
  printf("I-node number:            %ld\n", (long) info.st_ino);
  printf("Link count:               %ld\n", (long) info.st_nlink);
  printf("Ownership:                UID=%ld\n", (long) info.st_uid);
  printf("File size:                %lld bytes\n",(long long) info.st_size);
  printf("Blocks allocated:         %lld\n",(long long) info.st_blocks);
  
  close(fdEtc);


  //Task #9
  int fdTemp = open("fileToUnlink.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  close(fdTemp);
  unlink( "/home/csugrads/mitc0548/cs5631/FileAPILab/fileToUnlink.txt");


  //Task #10
  mkdir("/home/csugrads/mitc0548/cs5631/FileAPILab/dir1",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  mkdir("/home/csugrads/mitc0548/cs5631/FileAPILab/dir2",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  int fdDir = open("dir2/dirFile.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  //Task #11
  DIR *d = opendir("dir2");
  struct dirent *dir;
  int count = 0;
  printf("\n\n\n\n\n\n\n\n------------------------Separator between test 8 and 12--------------------\n\n\n\n\n\n");
  //Task #12
  while((dir = readdir(d)) != NULL){
    if(count == 2){
      printf("File name in dir2:    %s\n", dir->d_name);
    }
    count++;
  }
  
  //Task #13
  closedir(d);
  close(fdDir);

  //Task #14
  rmdir("dir1");

  //Task #15
  if(symlink("dir2/dirFile.txt", "dirFileSymlink.txt") < 0){
    fprintf(stderr, "An error occurred with symlink. \n");
  }
}
