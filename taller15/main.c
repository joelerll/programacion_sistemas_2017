#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
int main() {
				pid_t pid1;
				pid1 = 0;
				pid1 = fork();
				mode_t modo;
				char buff[100];
				pid_t pid2;
				pid_t exej;
				unsigned char recvBuff[8000000];
				if (pid1 == 0) {
								FILE *fpfile = fopen("log_cpu.log","ab");
								exej = getpid();
								modo = umask(0);
								pid2 = setsid();
								while(1) {
												sleep(1);
												FILE *fp = popen("top -bn2 | grep '%Cpu' | tail -1", "r");
												fread(buff,100,1, fp);
												fwrite(buff, 1,1000,fpfile);
												memset(buff, 0, sizeof(buff));
												fclose(fp);
								}
				}
				return 0;
}
