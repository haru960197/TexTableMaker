#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAX_RAW = 100000;
char line[100000];
FILE *input, *output;
int indent_num = 0;
void indent() {
    int i;
    for (i=0; i<indent_num; i++) fprintf(output, "\t");
}
void intended_print(char *line) {
    indent();
    fprintf(output, line);
}
int main() {
    char c;
    int i, and_flag = 0; // and_flagは、一個目の空白文字であることを管理
    input = fopen("Input.txt", "r");
    output = fopen("Output.txt", "w");
    if (input == NULL || output == NULL) {
        printf("input or output is NULL\n");
        printf("This file needs Input.txt in this directory\n");
        exit(1);
    }
    intended_print("\\begin{table}[H]\n");
    indent_num++;
    intended_print("\\caption{-----}\n");
    intended_print("\\label{-----}\n");
    intended_print("\\centering\n");
    intended_print("\\begin{tabular}{SSSS|S|...}\n");
    indent_num++;
    intended_print("\\hline\n");
    intended_print("{} & {} & {} & ...\n");
    intended_print("\\hline\n");
    indent_num++;
    while (fgets(line, MAX_RAW, input) != NULL) {
        // ファイルの終端まで読み込み
        intended_print("");
        for (i=0; i<strlen(line); i++) {
            c = line[i];
            if (c == ' ' || c == '\t') {
                if (!and_flag) {
                    fprintf(output, " & ");
                    and_flag = 1;
                }
            } else if (c == '\n') {
                fprintf(output, " \\\\\n");
                and_flag = 0;
            } else {
                fprintf(output, "%c", c);
                and_flag = 0;
            }
        }
    }
    indent_num--;
    intended_print("\\hline\n");
    indent_num--;
    intended_print("\\end{tabular}\n");
    indent_num--;
    intended_print("\\end{table}");
    printf("Warning! Fill in the blanks!\n");
    printf("\\caption{}\n");
    printf("\\label{}\n");
    printf("\\begin{tabular}{SSS...}\n");
    printf("{} & {} & {} ...\n");
    fclose(input);
    fclose(output);
}