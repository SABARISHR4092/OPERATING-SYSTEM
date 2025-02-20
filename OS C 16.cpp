#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

void writeEmployee(FILE *file, int index, Employee emp) {
    fseek(file, index * sizeof(Employee), SEEK_SET);
    fwrite(&emp, sizeof(Employee), 1, file);
}

void readEmployee(FILE *file, int index, Employee *emp) {
    fseek(file, index * sizeof(Employee), SEEK_SET);
    fread(emp, sizeof(Employee), 1, file);
}

int main() {
    FILE *file = fopen("employees.dat", "wb+");
    Employee emp1 = {1, "John Doe", 50000.0};
    writeEmployee(file, 0, emp1);
    
    Employee emp2;
    readEmployee(file, 0, &emp2);
    printf("ID: %d, Name: %s, Salary: %.2f\n", emp2.id, emp2.name, emp2.salary);
    
    fclose(file);
    return 0;
}
