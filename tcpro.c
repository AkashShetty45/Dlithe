#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct property {
    int id;
    char types[50];
    char location[100];
    double price;
};
struct property p;

void insert() {
    FILE *fp;
    fp = fopen("techpro.txt", "ab+");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("Enter new property details:\n");
    printf("Enter property ID: ");
    scanf("%d", &p.id);
    fflush(stdin);
    printf("Enter property type: ");
    scanf("%s", p.types);
    printf("Enter property location: ");
    scanf("%s", p.location); 
    printf("Enter property price: ");
    scanf("%lf", &p.price); 
    fwrite(&p, sizeof(p), 1, fp);
    printf("Property inserted successfully\n");
    fclose(fp);
}

void display() {
    FILE *fp;
    fp = fopen("techpro.txt", "rb");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("\n---Available property details are as follows:---\n");
    printf("ID\tTYPE\tLOCATION\tPRICE\n"); 
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%-3d\t%-5s\t%-8s\t%-5lf\n", p.id, p.types, p.location, p.price);
    }
    fclose(fp);
}

void search() {
    FILE *fp;
    char loc[100]; 
    int flag = 0;
    fp = fopen("techpro.txt", "rb");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("Enter location where you want to search for properties: ");
    scanf("%s", loc); 
    printf("\n---Available property details in %s are as follows:---\n", loc);
    printf("ID\tTYPE\tLOCATION\tPRICE\n");
    while (fread(&p, sizeof(p), 1, fp) > 0) {
        if (strcmp(p.location, loc) == 0) { 
            flag = 1;
            printf("%-3d\t%-5s\t%-8s\t%-5lf\n", p.id, p.types, p.location, p.price);
        }
    }
    if (flag == 0) {
        printf("\nNo properties available in %s\n", loc);
    }
    fclose(fp);
}

void deleteProperty() {
    FILE *fp, *ft;
    int pid;
    unsigned flag = 0;
    fp = fopen("techpro.txt", "rb");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    display();
    printf("Enter property id you want to delete: ");
    scanf("%d", &pid);
    ft = fopen("temp.txt", "wb"); 
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (pid == p.id) {
            flag=1;
            printf("Successfully deleted the property\n");
        } else {
            fwrite(&p, sizeof(p), 1, ft);
        }
    }
    if (flag == 0) {
        printf("Error: No such record found\n");
    }
    fclose(fp);
    fclose(ft);
    remove("techpro.txt");
    rename("temp.txt", "techpro.txt");
}

void update() {
    FILE *fp;
    int pid;
    int flag = 0;
    fp = fopen("techpro.txt", "r+b"); 
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("Enter property id which you want to update: ");
    scanf("%d", &pid);
    while (fread(&p, sizeof(p), 1, fp) > 0 && flag == 0) {
        if (p.id == pid) {
            flag = 1;
            printf("Enter updated property details:\n");
            printf("Enter updated property ID: ");
            scanf("%d", &p.id);
            fflush(stdin);
            printf("Enter updated property type: ");
            scanf("%s", p.types);
            printf("Enter updated property location: ");
            scanf("%s", p.location);
            printf("Enter updated property price: ");
            scanf("%lf", &p.price);
            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);
            printf("Property updated successfully\n");
        }
    }
    if (flag == 0) {
        printf("Error: Property not found\n");
    }
    fclose(fp);
}

int main() {
    int ch;
    while (ch != 6) {
        int ut;
        printf("Enter 0 for admin login, 1 for regular user:   \n");
        scanf("%d",&ut);
        if(ut!=0 && ut!=1){
            printf("Invalid user type\n");
            main();
        }
        int ps;
        if(ut==0){
            printf("Enter admin password:  ");
            scanf("%d",&ps);
            if(ps!=12345){
                printf("Invalid password\n");
                main();
            }
        }
        printf("********************************************************\n");
        printf("\t\tReal Estate Advisor\n");
        printf("********************************************************\n");
        printf("\t\t1. Display property\n");
        printf("\t\t2. Insert property\n");
        printf("\t\t3. Delete property\n");
        printf("\t\t4. Search property\n");
        printf("\t\t5. Modify property\n");
        printf("\t\t6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                display();
                break;
            case 2:
                insert();
                break;
            case 3:
                deleteProperty(); 
                break;
            case 4:
                search();
                break;
            case 5:
                update();
                break;
            case 6:
                printf("Quitting!!!!!\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}