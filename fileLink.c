#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

//With reference from https://linuxhint.com/stat-system-call-linux/
//To understand how to use the function stat and lstat from lecture.

int main(int argc, char * argv[]) {
   // printf() displays the string inside quotation
   if (argc != 3) {
      perror("Incorrect number of Arguments!");
      return 0;
   }

   char * outMessage;

   struct stat file1;
   struct stat file1SymCheck;
   struct stat file2SymCheck;
   struct stat file2;

   //Arg 1 is being passed to S2 as the symboliic check.
   int s1 = stat(argv[1], &file1);
   int s1S = lstat(argv[1], &file1SymCheck);
   int s2S = lstat(argv[2], &file2SymCheck);
   int s2H = stat(argv[2], &file2);

   if (s1 == 0  && s2S == 0 && s2H == 0) {
      printf("%lu\n", file1.st_ino);
      printf("%lu\n", file1SymCheck.st_ino);
      printf("%lu\n", file2.st_ino);
      printf("%lu\n", file2SymCheck.st_ino);
      printf("%lu\n", file2SymCheck.st_nlink);

      
      if (file1.st_ino == file2.st_ino){
         if (file1.st_ino == file1SymCheck.st_ino && file2.st_ino == file2SymCheck.st_ino) {
            printf("Files are linked \n");
         } else if (file1.st_ino != file1SymCheck.st_ino && file2.st_ino == file2SymCheck.st_ino){
            //Check for indirection
            char * buffer[file1SymCheck.st_size +1];
            readlink(argv[1], buffer, file1SymCheck.st_size +1);
            //Can't compare strings due to hard link vs symlink
            struct stat buff;
            lstat(buffer, &buff);
            //If symlink, st_ino will be different from lstat. 
            if (file1.st_ino == buff.st_ino) {
               printf("%s is a symlink to %s \n", argv[1],argv[2]);
            } else {
               printf("Files are linked \n");
            }

         } else if (file1.st_ino == file1SymCheck.st_ino && file2.st_ino != file2SymCheck.st_ino) {
            char * buffer[file2SymCheck.st_size +1];
            readlink(argv[2], buffer, file2SymCheck.st_size + 1);
            struct stat buff;
            lstat(buffer, &buff);
            if (file2.st_ino == buff.st_ino) {
               printf("%s is a symlink to %s \n", argv[2],argv[1]);
            } else {
               printf("Files are linked \n");
            }
         } else {
            printf("Files are linked \n");
         }
      } else {
         printf("Files are not linked \n");
      }
      
   } else {
      perror("perror");
   }


   return 0;
}