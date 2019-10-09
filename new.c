#include <stdio.h>
#include <stdlib.h>

void open_and_feed_prices();
void open_and_feed_demands();
void linear_regression();
void take_input_price();
void predict_demand();

//integer arrays which store prices and demands.

float prices[1000];
float demands[1000];

//variables required for the program to work efficiently

float sumx, sumxsq, sumy, sumxy, x, y, a0, a1, denom,test_demand,test_price;

//a Void function to open the prices file and feed the file contents into the array

void open_and_feed_prices()
{
 
    int i;
    
    //opening a file using the price pointer.
    FILE *price;
    price = fopen("_prices.txt", "r");

    //Error Handling to check the error in opening the said file
    if (price == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
       
    //Loop to feed the file values into an array
    for (i = 0; i < 1000; i++){
        fscanf(price, "%f,", &prices[i] );
    }
       
    //Closing the File Opened
    fclose(price);
}
    
// Void function to open the demands file and feed the data onto the demand array

void open_and_feed_demands()
{
    //The Loop counter variable
    int i;
   
    //Opening the Demand File
    FILE *demand;
    demand = fopen("_demands.txt", "r");
 
    //Error Handling
    if (demand == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
       
    //Loop to feed the values to an array
    for (i=0; i<1000; i++){
        fscanf(demand, "%f,", &demands[i] );
    }
       
     //Closing the file
    fclose(demand);

}


//The Linear Regression Function which maps out the points and
//Generates the linar curve using generalized Gradient descent

void linear_regression()
{
    int i;
    sumx = 0;
    sumxsq = 0;
    sumy = 0;
    sumxy = 0;
    
    for(i = 0; i < 1000; i++)
    {
 
    	sumx = sumx+ prices[i];
    	sumxsq = sumxsq + prices[i]*prices[i];
    	sumy = sumy + demands[i];
    	sumxy = sumxy + prices[i]*demands[i];
    	
    }

    //denom = 1000 * sumxsq-(sumx*sumx);
    //printf("\n%3.3f %3.3f %3.3f %3.3f\n ", sumx, sumxsq, sumy, sumxy);
    a1 = (1000*sumxy - sumx*sumy)/(1000*sumxsq-sumx*sumx);
    a0 = (sumy - a1*sumx)/1000;
    //printf("%3.3f %3.3f\n", denom, a0*denom);
    //a1 = (n*sumxy - sumx*sumy)/(1000*sumxsq-sumx*sumx);
    
    printf("demand = %3.3f * price + %3.3f", a1, a0);

}

//void function to input the test price for which the demand has to be known

void take_input_price()
{
   
    printf("\n\n\nEnter the Price you want to check the Demand for: ");
    scanf("%f",&test_price);
   
}

//Void function which generates the demand for the input test price

void predict_demand()
{
   
    test_demand = a1*test_price + a0;
   if(test_demand>=0){
     printf("The demand for the corresponding price is: %3.3f people. \n\n\n\n", test_demand);
	
   }else
    printf("Due to the exuberant prices there wont be any Demand Generated in people. \n\n\n");
}

// The generating "main" function

int main()
{
    //ALL the Function Call Statements
    
    open_and_feed_prices();
   
    open_and_feed_demands();
    
    printf("The \"Demand Vs Price\" Model is trained.\n\nThe curve for the model is :\t"); 
   
    linear_regression(); 
  
    take_input_price();
   
    predict_demand();
   
   
    return 0;
}

