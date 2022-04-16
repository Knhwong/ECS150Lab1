#include <stdio.h>
#include <sys/stat.h>

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
   struct stat file2SymCheck;
   struct stat file2HardCheck;

   //Arg 1 is being passed to S2 as the symboliic check.
   int s1 = stat(argv[2], &file1);
   int s2S = lstat(argv[1], &file2SymCheck);
   int s2H = stat(argv[1], &file2HardCheck);

   if (s1 == 0  && s2S == 0 && s2H == 0) {
      if (file1.st_ino == file2SymCheck.st_ino) {
         outMessage = "These files are linked";
      } 
      else {
         if (file1.st_ino == file2HardCheck.st_ino) {
            outMessage = "file1 is a symbolic link to file2";
         }
         else {
            outMessage = "The files are not linked";
         }
      }
      printf("%s\n", outMessage);
   } else {
      perror("File check failed!");
   }


   return 0;
}