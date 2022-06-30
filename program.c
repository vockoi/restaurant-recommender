/* Restaurant recommender:
 *
 * Skeleton code written by Jianzhong Qi, April 2022
 * Edited by: Victoria Halim, May 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include "listops.c"
#include <string.h>
#include <math.h>

/* stage heading */
#define HEADING "==========================Stage %d==========================\n"

// matrix representations of restaurant_visits values
#define END_OF_RESTAURANT_RECORDS "#####"
#define MATRIX_SYMBOL_NEGATIVE1 '-'
#define MATRIX_SYMBOL_NEGATIVE2 '+'
#define MATRIX_SYMBOL_NEGATIVE3 '*'

#define MAX_RESTAURANTS 99        // maximum number of restaurants
#define MAX_CUISINE_LENGTH 29     // maximum length of restaurant cuisine
#define MAX_RESTAURANT_NAME 100   // maximum length of restaurant name
#define ID_LENGTH 6               // maximum length of restaurant id

/* typedefs */

typedef struct {
    int id;
    double x_coord;
    double y_coord;
    int avg_price;
    char cuisine[MAX_CUISINE_LENGTH + 1];
    char name[MAX_RESTAURANT_NAME + 1];
} restaurant_t;

typedef restaurant_t restaurant_records_t[MAX_RESTAURANTS+1];

/****************************************************************/
/* function prototypes */
void print_stage_header(int stage);

/* stage one */
void stage_one(restaurant_records_t restaurant_records, 
               int *num_restaurants);
int read_one_restaurant_record(restaurant_t *restaurant);
restaurant_t find_restaurant_with_smallest_avg_price(restaurant_records_t
restaurant_records, int *num_restaurants);

/* stage two */
void stage_two(list_t *dining_records, restaurant_records_t restaurant_records,
               int num_restaurants);
int get_restaurant_idx(int restaurant_id, int num_restaurants,
                         restaurant_records_t restaurant_records);
node_t *find_customer_data(customer_t customer, list_t *dining_record, 
                           int num_restaurants);
void add_customer_data(customer_t customer, list_t *dining_records,
                       int restaurant_idx, int num_restaurants);
void print_dining_records(list_t *dining_records, int num_restaurants);

/* stage three */
void stage_three(int num_restaurants, list_t *dining_records, 
                 restaurant_records_t restaurant_records);
int is_recommended(int idx_restaurant_1, int idx_restaurant_2, 
                   restaurant_records_t restaurant_records);
double restaurant_distance(restaurant_t restaurant_1, 
                           restaurant_t restaurant_2);

/* stage four */
void stage_four(list_t *dining_records, int num_restaurants);
void find_2_most_similar(customer_t customer, list_t *dining_records,
                       int num_restaurants, customer_t top2_most_similar[2]);
int get_similarity_score(customer_t customer_1, customer_t customer_2, 
                         int num_restaurants);
void update_recommendation(int num_restaurants, customer_t customer, 
                           customer_t top2_most_similar[2]);

/****************************************************************/

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(HEADING, stage_num);
}

/* main program controls all the action */
int
main(int argc, char *argv[]) {
    // to store restaurant records
    restaurant_records_t restaurant_records;
    
    // linked list to store dining records
    list_t *dining_records = make_empty_list();
    
    int num_restaurants = 0;
   
    stage_one(restaurant_records, &num_restaurants);
    stage_two(dining_records, restaurant_records, num_restaurants);
    stage_three(num_restaurants, dining_records, restaurant_records);
    stage_four(dining_records, num_restaurants);
    
    free(dining_records);
    
    return 0;
}

//STAGE ONE
void stage_one(restaurant_records_t restaurant_records, int *num_restaurants) {
    /* read restaurant records from input data; put each record into the array
    `restaurant_records`. print total number of restaurant records, and the
    restaurant with smallest average price per head. */
    
    print_stage_header(1);
    
    // read each restaurant record into `restaurant_records` until end of
    // restaurant records section
    for (int i = 0; read_one_restaurant_record(&restaurant_records[i]); i++) {
        *num_restaurants += 1;
    }
    
    restaurant_t restaurant_with_smallest_avg_price = 
    find_restaurant_with_smallest_avg_price(restaurant_records, 
                                            num_restaurants);
    
    printf("Number of restaurants: %d\n", *num_restaurants);
    printf("Restaurant with the smallest average price: %s\n\n",
    restaurant_with_smallest_avg_price.name);
}

int read_one_restaurant_record(restaurant_t* restaurant) {
    /* initialize and return a restaurant_t object by extracting data from one 
    restaurant record. */
    
    char restaurant_id[ID_LENGTH + 1];
    scanf("%s", restaurant_id);
    
    // if scanf reached end of restaurant records, stop extracting data
    if (!(strcmp(restaurant_id, END_OF_RESTAURANT_RECORDS))) {
        return 0;
    } else {
        restaurant->id = atoi(restaurant_id);
    }
    
    // extract data from restaurant records
    scanf("%lf", &restaurant->x_coord);
    scanf("%lf", &restaurant->y_coord);
    scanf("%d", &restaurant->avg_price);
    scanf("%s", restaurant->cuisine);
    scanf("%s", restaurant->name);
    
    return 1;
}

restaurant_t find_restaurant_with_smallest_avg_price(restaurant_records_t
restaurant_records, int* num_restaurants) {
    /* return restaurant in `restaurant_records` with smallest average
    price per head */
    
    int smallest_avg_price = restaurant_records[0].avg_price;
    restaurant_t restaurant_with_smallest_avg_price = restaurant_records[0];
    
    for (int i = 0; i < *num_restaurants; i++) {
        if (restaurant_records[i].avg_price < smallest_avg_price) {
            smallest_avg_price = restaurant_records[i].avg_price;
            restaurant_with_smallest_avg_price = restaurant_records[i];
        }
    }
    
    return restaurant_with_smallest_avg_price;
}

//STAGE TWO
void stage_two(list_t *dining_records, restaurant_records_t restaurant_records,
               int num_restaurants) {
    /* print the number of times each customer in the dining records visited
    each restaurant in the restaurant records in the form of an matrix */
    
    print_stage_header(2);
    
    /* extract data from each dining record in input file */
    while(getchar() != EOF) {
        customer_t curr_customer;
        int restaurant_id;
 
        scanf("%*s %s", curr_customer.id);
        scanf("%d %*d", &restaurant_id);
    
        // index of the restaurant the customer visited in `restaurant_records`
        int restaurant_idx = get_restaurant_idx(restaurant_id, num_restaurants,
                                                restaurant_records);
        
        //  add extracted data as a node in `dining_records`
        add_customer_data(curr_customer, dining_records, restaurant_idx, 
                         num_restaurants);
    }
    
    print_dining_records(dining_records, num_restaurants);
    printf("\n");
}

int get_restaurant_idx(int restaurant_id, int num_restaurants,
                         restaurant_records_t restaurant_records) {
    /* return index of `restaurant_id` in `restaurant_records` */
    
    for (int i = 0; i < num_restaurants; i++) {
        /* find which restaurant id in `restaurant_records` matches with 
        `restaurant_id` */
        if (!(restaurant_id - restaurant_records[i].id)) {
            return i;
        }
    }
    
    return -1;
}

void add_customer_data(customer_t customer, list_t *dining_records,
                       int restaurant_idx, int num_restaurants) {
    /* add data extracted (`customer`) from a single dining record into 
    `dining_records` */
    
   // node in `dining_records` to add the new data to
   node_t *insertion_point = find_customer_data(customer, dining_records,
                                                 num_restaurants);
   
   // update `customer` data by adding the number of times the customer has
   // visited the restaurant with index `restaurant_idx` by 1
   char old_value = insertion_point->data.restaurant_visits[restaurant_idx];
   char new_value = old_value + 1;
   insertion_point->data.restaurant_visits[restaurant_idx] = new_value;
}

node_t *find_customer_data(customer_t customer, list_t *dining_records, 
                      int num_restaurants) {
    /* return pointer of node which contains a customer's `customer` data. */
    
    node_t *temp = dining_records->head;
    
    /* if customer id in linked list of dining records, return pointer to node
    containing customer's data */
    while (temp != NULL) {
        if (!strcmp(customer.id, temp->data.id)) {
            return temp;
        }       
        temp = temp->next;
    }
    
    /* if customer id not in linked list of dining records, initialize array
    to record number of times customer visited each restaurant */
    int array_length = num_restaurants;
    customer.restaurant_visits = malloc(array_length * sizeof(int));
    for (int i = 0; i < num_restaurants; i++) {
        customer.restaurant_visits[i] = 0;
    }
    
    // add `customer` as a new node in linked list
    dining_records = insert_at_foot(dining_records, customer);
    
    // return pointer to node containing new customer data
    return dining_records->foot;
}

void print_dining_records(list_t *dining_records, int num_restaurants) {
    node_t *temp = dining_records->head;
    /* print all `dining_records` data in the form of a matrix representation */
    
    while (temp != NULL) {
        customer_t curr_customer = temp->data;
        printf("%s:", curr_customer.id);
        
        for (int i = 0; i < num_restaurants; i++) {
            int value = curr_customer.restaurant_visits[i];
       
            if (value == -1) {
                printf("  %c", MATRIX_SYMBOL_NEGATIVE1);
            } else if (value == -2) {
                printf("  %c", MATRIX_SYMBOL_NEGATIVE2);
            } else if (value == -3) {
                printf("  %c", MATRIX_SYMBOL_NEGATIVE3);
            } else {
                printf("  %d", value);
            }
        }
        
        printf("\n");
        temp = temp->next;
    }
}

//STAGE THREE
void stage_three(int num_restaurants, list_t *dining_records, 
                 restaurant_records_t restaurant_records) {
    /* for each customer C in `dining_records`, based on restaurants that C has
    visited before, identify unvisited restaurants that would be recommended to
    C. subtract corresponding restaurant_visits value by one for each 
    recommended restaurant. */
    
    print_stage_header(3);
    
    // iterate through each customer in `dining_records`
    node_t *temp = dining_records->head;
    while (temp != NULL) {
        customer_t curr_customer = temp->data;
        
        /* compare each restaurant customer has visited to restaurants customer
        have never visited */
        for (int i = 0; i < num_restaurants; i++) {
            if (curr_customer.restaurant_visits[i] > 0) {
                
                // if a restaurant is recommended, subtract value corresponding
                // to the restaurant in `restaurant_visits` array by 1.
                for (int j = 0; j < num_restaurants; j++) {
                    if (curr_customer.restaurant_visits[j] == 0 && 
                        is_recommended(i, j, restaurant_records)) {
                            curr_customer.restaurant_visits[j] -= 1;
                    }
                }
            }
        }
        
        temp = temp->next;
    }
    
    print_dining_records(dining_records, num_restaurants);
    printf("\n");
}

int is_recommended(int idx_restaurant_1, int idx_restaurant_2, 
                   restaurant_records_t restaurant_records) {
    /* evaluate whether the restaurant with index `idx_restaurant_2` would be
    recommended to a customer that visited the restaurant with index 
    `idx_restaurant_1` in `restaurant_records`. return 1 if `restaurant_2` is 
    recommended and 0 otherwise. */
    
    restaurant_t restaurant_1 = restaurant_records[idx_restaurant_1];
    restaurant_t restaurant_2 = restaurant_records[idx_restaurant_2];
    
    // recommend if restaurants share same cuisine
    if (!strcmp(restaurant_1.cuisine, restaurant_2.cuisine)) {
        return 1;
    } 
    
    // recommend if price difference is less than/equal to 20
    int price_diff = restaurant_1.avg_price - restaurant_2.avg_price;
    if (abs(price_diff) <= 20) {
        return 1;
    }
    
     // recommend if distance between restaurants is less than/equal to 30
    double distance_between = restaurant_distance(restaurant_1, restaurant_2);
    if (distance_between <= 30) {
        return 1;
    }
    
    return 0;
}

double restaurant_distance(restaurant_t restaurant_1, 
                           restaurant_t restaurant_2) {
    /* return euclidean distance between `restaurant_1` and `restaurant_2` */
    
    return sqrt(pow((restaurant_1.x_coord - restaurant_2.x_coord), 2) +
         pow((restaurant_1.y_coord - restaurant_2.y_coord), 2));
}

//STAGE FOUR
void stage_four(list_t *dining_records, int num_restaurants) {
    /* for each customer A in `dining_records`, find two other customers B and
    C with most similar restaurant_visits array to A (the similarity scores 
    must be more than 0). for each similar customer kept, recommend restaurants 
    unvisited by A, that have been visited by B and/or C (if kept). for each 
    recommended restaurant, subtract corresponding value in restaurant_visits 
    array by one.*/
    
    print_stage_header(4);
    
    node_t *temp = dining_records->head;
    while (temp != NULL) {
        customer_t curr_customer = temp->data;
        
        // to store top 2 most similar customers
        customer_t top2_most_similar[2];
        
        // find 2 customers with highest similarity score to `curr_customer`
        find_2_most_similar(curr_customer, dining_records, num_restaurants, 
                           top2_most_similar);
        
        /* update `curr_customer`'s restaurant_visits array to add
        recommendations based on the top 2 most similar customers'
        restaurant_visits array */
        update_recommendation(num_restaurants, curr_customer, 
                              top2_most_similar);
        
        temp = temp->next;
    }
    
    print_dining_records(dining_records, num_restaurants);
}

void find_2_most_similar(customer_t customer, list_t *dining_records,
                       int num_restaurants, customer_t top2_most_similar[2]) {
    /* find 2 customers in `dining_records` with highest similarity scores to
    `customer` and store them in `top_2_most_similar`. */
    
    // to store highest and second highest similarity score
    int top1_similarity_score = -1, top2_similarity_score = -1;
    
    // iterate through each customer in `dining_records`
    node_t *temp = dining_records->head;
    while (temp != NULL) {
        customer_t curr_customer = temp->data;
        
        if (strcmp(curr_customer.id, customer.id)) {
            
            // similarity score between `curr_customer` and `customer`
            int similarity_score = get_similarity_score(customer, curr_customer, 
                                                        num_restaurants);
            
            /* if `curr_customer`'s similarity score is higher than the top1, 
            remove the current top2 customer from `top2_most_similar`. move the
            top1 customer to top2 and store `curr_customer` as top1 */
            if (similarity_score > top1_similarity_score) {
                top2_similarity_score = top1_similarity_score;
                top1_similarity_score = similarity_score;
                top2_most_similar[1] = top2_most_similar[0];
                top2_most_similar[0] = curr_customer;
            } 
            
            /* if `curr_customer`'s similarity score is higher than top2 but
            less than top1, replace the top2 customer with `curr_customer` */
            else if (similarity_score > top2_similarity_score) {
                top2_similarity_score = similarity_score;
                top2_most_similar[1] = curr_customer;
            }
        }
        
        temp = temp->next;
    }
}

int get_similarity_score(customer_t customer_1, customer_t customer_2, 
                         int num_restaurants) {
    /* return similarity score between `customer_1` and `customer_2`. */
    
    int similarity_score = 0;  
    for (int i = 0; i < num_restaurants; i++) {
        
        /* if both customers have visited the same restuarant with index i, add
        the product of their restaurant_visits[i] value to `similarity_score` */
        if (customer_1.restaurant_visits[i] > 0 && 
            customer_2.restaurant_visits[i] > 0) {
            similarity_score += (customer_1.restaurant_visits[i] * 
                 customer_2.restaurant_visits[i]);
        }
    }
    
    return similarity_score;
}

void update_recommendation(int num_restaurants, customer_t customer, 
                           customer_t top2_most_similar[2]) {
    /* for each customer in `top_2_most_similar` with similarity score more than
    0, recommend restaurants unvisited by A, that have been visited by the top1
    and/or top2 most similar customers (if kept). for each recommended
    restaurant, subtract corresponding value in restaurant_visits array by one.
    */
    
    for (int i = 0; i < 2; i++) {
        customer_t curr_customer = top2_most_similar[i];
        if (!get_similarity_score(customer, curr_customer, num_restaurants)) {
            continue;
        }
        
        for (int i = 0; i < num_restaurants; i++) {
            if (customer.restaurant_visits[i] <= 0 && 
                curr_customer.restaurant_visits[i] > 0) {
                    customer.restaurant_visits[i] -= 1;
            }
        }
    }
}