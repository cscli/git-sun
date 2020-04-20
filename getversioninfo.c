

#include <stdio.h>
#include <string.h>
 //./getVersionInfo foo v1.1.1 git
 
int getBuildInfo(const char* cmd)
{
    FILE *fstream = NULL;
    char buffer[1024];
    int res = 0;
    memset(buffer,0,sizeof(buffer));
    if (NULL == (fstream = popen(cmd,"r")))      
    {     
        return -1;      
    }   
 
    fgets(buffer, sizeof(buffer), fstream); 
    pclose(fstream);    
    sscanf(buffer,"%d",&res);
    return res;     
}


int main(int argc, char *argv[])
{
   FILE *fp = NULL;
   char* gitcmd="git rev-list --all|wc -l";
   char* svncmd="svn info|grep \"Last Changed Rev:\"|awk -F : '{print $2}'|sed 's/ //g'";
   int res = 0;
   char buffer[2048];
   memset(buffer,0,sizeof(buffer));
   if (argc < 4) {
      printf("Usage:./getversion [NAME] [VERSION] [git/svn/other]\n");
      return 1;
   }
   if (strcmp(argv[3],"git") == 0){
       res = getBuildInfo(gitcmd);
   }else if (strcmp(argv[3],"svn") == 0){
       res = getBuildInfo(svncmd);
   }else{
       res = 58;
   }
   char* arr="#ifndef __VER_H_FILE__\
\r\n#define __VER_H_FILE__\
\r\n\
\r\n#define ___MODULE___	\"%s\"\
\r\n#define ___VERSION___	\"%s\"\
\r\n#define ___BUILD___	\"%d\"\
\r\n\
#endif";
   sprintf(buffer,arr,argv[1],argv[2],res);
 
   fp = fopen("verion.h", "w+");
   fprintf(fp, "%s",buffer);
   fclose(fp);
   return 0;
}