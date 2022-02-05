#include <stdio.h>

int main() {
    double Final_Weight = 0;
    int counter = 0;
    int Pure_Precent;
    double Product_Weight;
    printf("Welcome, please enter the weights of each ingredient: \n"); // Input part
    if(scanf("%lf",&Product_Weight) < 1) return 1;
    while (Product_Weight >= 0) {
        counter++;
        Final_Weight = Final_Weight + Product_Weight;
        if(scanf("%lf",&Product_Weight) < 1)
            return 1;
    }
    if (counter < 3) {                        //   Some restriction
        printf("Not enough ingredients.\n");
        return 1;
    } else if (counter > 10) {
        printf("Too many ingredients.\n");
        return 1;
    }
    else {                              // and if everything goes well calculatings
        Pure_Precent = counter * 10;
        Final_Weight = Final_Weight / counter;
        printf("The final product weighs %0.3f pounds and is %d percent pure.", Final_Weight, Pure_Precent);

    }
    return 0;
}
