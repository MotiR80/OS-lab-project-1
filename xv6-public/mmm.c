#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int main(int argc, char *argv[]) {
    int fd;
    char tmp[5];
    char buffer[20];
    int nums[7] = {0};
    int count = 0;
    int sum = 0;
    int middle;
    int mode;
    int avg;

    // Get up to 7 numbers from the main function arguments
    for (int i = 1; i < argc && count < 7; i++) {
        int num = atoi(argv[i]);
        if (num != 0) {
            nums[count] = num;
            sum += num;
            count++;
        }
    }
    
    if (count == 7){
       printf(1, "Error: you entered more than 7 numbers.\n");
       exit();
    }
    

    // Sort the numbers using selection sort
    for (int i = 0; i < count - 1; i++) {
        int min = i;
        for (int j = i + 1; j < count; j++) {
            if (nums[j] < nums[min]) {
                min = j;
            }
        }
        int temp = nums[i];
        nums[i] = nums[min];
        nums[min] = temp;
    }

    // Calculate average, median, and mode
    avg = sum / count;
    if(count % 2 != 0)
    	middle = nums[count / 2];
    else{
    	middle = (nums[count / 2 - 1] + nums[count / 2]) / 2;
    }
    mode = nums[0];
    int max_count = 1;
    int current_count = 1;
    for (int i = 1; i < count; i++) {
        if (nums[i] == nums[i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                mode = nums[i - 1];
            }
            current_count = 1;
        }
    }
    if (current_count > max_count) {
        max_count = current_count;
        mode = nums[count - 1];
    }
    
    
    int sIndex = 0;
    
    tostring(tmp, avg);
    for(int i = 0; i < strlen(tmp);i++){
    	buffer[i] = tmp[i];
    }
    sIndex = strlen(buffer);
    buffer[sIndex++] = ' ';
    
    tostring(tmp, middle);
    for(int i = 0; i < strlen(tmp);i++){
    	buffer[i + sIndex] = tmp[i];
    }
    sIndex = strlen(buffer);
    buffer[sIndex++] = ' ';
    
    tostring(tmp, mode);
    for(int i = 0; i < strlen(tmp);i++){
    	buffer[i + sIndex] = tmp[i];
    }
    sIndex = strlen(buffer);
    buffer[sIndex++] = '\n';
    buffer[sIndex] = '\0';
    
    //Write results to file
    fd = open("mmm_result.txt",  O_CREATE | O_RDWR);
    write(fd, buffer, strlen(buffer));
    close(fd);

    exit();
}

