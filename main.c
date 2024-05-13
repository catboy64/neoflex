#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 
#include<sys/utsname.h>
#include<unistd.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <string.h>

//prototype
long get_uptime();

int main() 
{ 
  struct utsname buf1; 
  errno =0;

   if(uname(&buf1)!=0) 
   { 
      perror("uname doesn't return 0, so there is an error"); 
      exit(EXIT_FAILURE); 
   }
  
  //get username
  char *name=getenv("USER");
    if(name==NULL) return EXIT_FAILURE;
  
  //get uptime
  long uptime = get_uptime();
  
  //get number of processors
  long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
  
  //get cpu temp
  FILE* file = NULL;
    file = fopen("/sys/class/thermal/thermal_zone0/temp","r");
    char temp[20] = "";
    if (file != NULL)
    {
        int i = 1;
        fgets(temp, 20, file);
    }
    else
    {
        printf("Fichier est nul ou jsp bref ca marche pas\n");
    }
    fclose(file);
    
    //get cpu stuff idk je suis fatigue calisse
    FILE* file2 = fopen("/proc/cpuinfo", "r");
    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), file2))
    {
        i++;
        if(i==5)
        {
            int i2 = 13;
            while(line[i2] != EOF)
            {
                printf("%c", line[i2]);
                i2++;
            }
        }
    }
    fclose(file2);
  
  //print title
  printf("%s@%s\n\n", name, buf1.nodename);
  
  //print OS
  printf("OS: %s %s\n", buf1.sysname, buf1.machine);
  
  //print kernel
  printf("Kernel: %s\n", buf1.release);
  
  //print uptime
  printf("Uptime: %ld mins\n", uptime/60);
  
  //print cpu info
  printf("(%ld) %d°C\n", number_of_processors, atoi(temp)/1000);
  
  return 0;
} 

long get_uptime()
{
    struct sysinfo s_info;
    int error = sysinfo(&s_info);
    if(error != 0)
    {
        printf("code error = %d\n", error);
    }
    return s_info.uptime;
}
