#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义一个函数，用于统计文件中的字符数
int count_chars(FILE* fp) {
    int count = 0; //初始化计数器
    char ch; //定义一个字符变量，用于存储读取的字符
    while ((ch = fgetc(fp)) != EOF) { //循环读取文件中的每个字符，直到遇到文件结束符
        count++; //每读取一个字符，计数器加一
    }
    return count; //返回计数器的值
}

//定义一个函数，用于统计文件中的单词数
int count_words(FILE* fp) {
    int count = 0; //初始化计数器
    char ch; //定义一个字符变量，用于存储读取的字符
    int flag = 0; //定义一个标志变量，用于判断是否遇到单词分隔符（空格或逗号）
    while ((ch = fgetc(fp)) != EOF) { //循环读取文件中的每个字符，直到遇到文件结束符
        if (ch == ' ' || ch == ',') { //如果读取到空格或逗号
            if (flag == 1) { //如果之前已经遇到了单词的开始
                count++; //计数器加一
                flag = 0; //重置标志变量为0，表示遇到了单词的结束
            }
        }
        else { //如果读取到其他字符
            flag = 1; //设置标志变量为1，表示遇到了单词的开始
        }
    }
    if (flag == 1) { //如果文件结束时还有未结束的单词
        count++; //计数器加一
    }
    return count; //返回计数器的值
}

//主函数
int main(int argc, char* argv[]) {
    if (argc != 3) { //如果参数个数不等于3（程序名，控制参数，文件名）
        printf("Usage: %s [-c|-w] [input_file_name]\n", argv[0]); //打印用法提示信息
        exit(1); //退出程序，返回错误码1
    }
    FILE* fp; //定义一个文件指针变量，用于打开文件
    errno_t err = fopen_s(&fp, argv[2], "r");
    if (err != 0) {
        printf("Error: cannot open file %s\n", argv[2]);
        return -1;
    }
    //以只读模式打开指定的文件，并将文件指针赋给fp
    if (fp == NULL) { //如果打开失败（文件不存在或无权限）
        printf("Error: cannot open file %s\n", argv[2]); //打印错误信息
        exit(2); //退出程序，返回错误码2
    }
    if (strcmp(argv[1], "-c") == 0) { //如果控制参数为-c（统计字符数）
        int chars = count_chars(fp); //调用count_chars函数，传入文件指针，得到返回值（字符数）
        printf("Character count: %d\n", chars); //打印结果信息
    }
    else if (strcmp(argv[1], "-w") == 0) { //如果控制参数为-w（统计单词数）
        int words = count_words(fp); //调用count_words函数，传入文件指针，得到返回值（单词数）
        printf("Word count: %d\n", words); //打印结果信息
    }
    else { //如果控制参数既不是-c也不是-w（无效参数）
        printf("Error: invalid parameter %s\n", argv[1]); //打印错误信息
        exit(3); //退出程序，返回错误码3
    }
    fclose(fp); //关闭文件
    return 0; //正常结束程序，返回0
}