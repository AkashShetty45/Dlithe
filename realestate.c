#include <stdio.h>

// Structure to hold property information
struct Property {
    char address[100];
    int bedrooms;
    int bathrooms;
    double price;
};

// Function to provide advice based on property information
void provideAdvice(struct Property property) {
    if (property.bedrooms >= 3 && property.bathrooms >= 2) {
        printf("This property looks like a great option for a family!\n");
    } else if (property.price < 200000) {
        printf("This property might be a good deal!\n");
    } else {
        printf("Consider looking at other properties as well.\n");
    }
}

int main() {
    struct Property property;

    printf("Real Estate Advisor\n");
    printf("Enter property details:\n");

    printf("Address: ");
    fgets(property.address, sizeof(property.address), stdin);

    printf("Number of bedrooms: ");
    scanf("%d", &property.bedrooms);

    printf("Number of bathrooms: ");
    scanf("%d", &property.bathrooms);

    printf("Price: ");
    scanf("%lf", &property.price);

    printf("\nProperty details:\n");
    printf("Address: %s", property.address);
    printf("Bedrooms: %d\n", property.bedrooms);
    printf("Bathrooms: %d\n", property.bathrooms);
    printf("Price: %.2f\n", property.price);

    // Provide advice based on property information
    provideAdvice(property);

    return 0;
}
