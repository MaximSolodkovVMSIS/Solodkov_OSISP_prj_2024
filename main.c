#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//получение значения температуры 
float get_cpu_temperature(){
    FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if(fp == NULL){
        perror("error opening temperature");
        return -1.0;
    }
    char temperature_str[10];
    fgets(temperature_str, sizeof(temperature_str), fp);
    fclose(fp);

    float temperature = atof(temperature_str) / 1000.0;
    return temperature;
}

//получение информации о версии ядра Linux
int get_kernel_version(char *kernel_version, int size){
    FILE *fp = fopen("/proc/version", "r");
    if(fp == NULL){
        perror("error opening version");
        return 0;
    }
    fgets(kernel_version, size, fp);
    fclose(fp);
    return 1;

}

//информация о доступной памяти
int get_memory_info(char *memory_info, int size){
    FILE *fp = popen("free -h | grep Mem: | awk '{print $4}'", "r");
    if(fp == NULL){
        perror("error opening memory info");
        return 0;
    }
    fgets(memory_info, size, fp);
    pclose(fp);
    return 1;
}

int main(int argc, char** argv) {
    char kernel_version[128];
    char memory_info[128];
    float temperature = get_cpu_temperature();

    int success_kernel = get_kernel_version(kernel_version, sizeof(kernel_version));
    int success_memory = get_memory_info(memory_info, sizeof(memory_info));
    if(temperature == -1.0 || !success_kernel || !success_memory){
        printf("failed to get CPU temperature or kernel version or memory info");
        return 1;
    }

    printf("Kernel version: %s \n", kernel_version);
    printf("CPU temperature: %1f^C\n", temperature);
    printf("Available memory: %s\n", memory_info);
    return 0;
}
