#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 
#include<sys/utsname.h>
#include<unistd.h>
#include<linux/kernel.h>
#include<sys/sysinfo.h>
#include<string.h>

//prototype
long get_uptime();
void print_info(int i);

//main function
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
    
    //get cpu stuff idk je suis fatigue calisse
    FILE* file2 = fopen("/proc/cpuinfo", "r");
    char line[256];
    int i = 0;
    char cpu_name[100];
    while (fgets(line, sizeof(line), file2))
    {
        i++;
        if(i==5)
        {
            int i2 = 13;
            while(line[i2] != EOF)
            {
                cpu_name[i2-13] = line[i2];
                i2++;
            }
        }
    }
    fclose(file2);
    cpu_name[strlen(cpu_name)-1] = '\0';
    
    //get mem_total
    FILE* file3 = fopen("/proc/meminfo", "r");
    char line2[256];
    i = 0;
    char mem_total[100];
    while (fgets(line2, sizeof(line2), file3))
    {
        i++;
        if(i==1)
        {
            int i2 = 16;
            while(line2[i2] != EOF)
            {
                mem_total[i2-16] = line2[i2];
                i2++;
            }
        }
    }
    fclose(file3);
    mem_total[strlen(mem_total)-4] = '\0';
    
    //get mem_free
    FILE* file4 = fopen("/proc/meminfo", "r");
    char line3[256];
    i = 0;
    char mem_free[100];
    while (fgets(line3, sizeof(line3), file4))
    {
        i++;
        if(i==3)
        {
            int i2 = 16;
            while(line3[i2] != EOF)
            {
                mem_free[i2-16] = line3[i2];
                i2++;
            }
        }
    }
    fclose(file4);
    mem_free[strlen(mem_free)-4] = '\0';

    //print ascii
    FILE* fileAscii = NULL;

    char *distroArch = strstr(buf1.release, "arch");
    if(distroArch)
        {
            fileAscii = fopen("arch.ascii","r");
        }
    else
    {
	char *distroArch = strstr(buf1.release, "artix");
		if (distroArch)
		{
			fileAscii = fopen("arch.ascii", "r");
		}
		else
		{
			fileAscii = fopen("linux.ascii", "r");
		}
    }
    if (fileAscii != NULL)
    {
        char string[50] = "";
        int i = 1;
        printf("\n");
        while(fgets(string, 50, fileAscii) != NULL)
        {
            printf("\033[0;36m%.*s\033[0m" ,strlen(string)-1, string);
            switch (i)
            {
                case 1:
                    printf(" \033[0;36m%s\033[0m@\033[0;36m%s\033[0m\n", name, buf1.nodename);
                    break;
                case 2:
                    printf("      ---------\n");
                    break;
                case 3:
                    printf(" \033[0;36mOS\033[0m: %s %s\n", buf1.sysname, buf1.machine);
                    break;
                case 4:
                    printf(" \033[0;36mKernel\033[0m: %s\n", buf1.release);
                    break;
                case 5:
                    printf(" \033[0;36mUptime\033[0m: %ld mins\n", uptime/60);
                    break;
                case 6:
                    printf(" \033[0;36mCPU\033[0m: %s (%ld)\n",cpu_name, number_of_processors);
                    break;
                case 7:
                    printf(" \033[0;36mMemory\033[0m: %d/%d MiB\n", (atoi(mem_total)-atoi(mem_free))/1024, atoi(mem_total)/1024);
                    break;
                case 8:
                    printf("\n");
                    break;
            }
            i++;
        }
        printf("\n");


    }
    else
    {
        printf("Error - ASCII file not detected\n");
    }
    fclose(fileAscii);
  
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
