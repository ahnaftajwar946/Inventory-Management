#include"customers.h"
int remove_newline(char str[]) {
	int length = strlen(str);
	if (str[length - 1] == '\n') {
		str[length - 1] = 0;

		return 0;
	}

	return 1;
}


int add_customer(char inv_db[][NUM_INV_PROPS][MAX_LEN],
					   char item[][MAX_LEN], int num_items) {
	
	for (int i = 0; i < NUM_INV_PROPS; i++) {
		strcpy(inv_db[num_items][i], item[i]);
	}

	return num_items + 1;
}

int get_customer(char inv_db[][NUM_INV_PROPS][MAX_LEN],
					   char product_id[], int num_items) {

	for (int i = 0; i < num_items; i++) {
		if (!strcmp(inv_db[i][0], product_id)) {
			return i;
		}
	}

	return -1;
}

int log_customer(char sales_db[][NUM_SALES_PROPS][MAX_LEN],
	char sale[][MAX_LEN], int num_sales) {

	for (int i = 0; i < NUM_INV_PROPS; i++) {
		strcpy(sales_db[num_sales][i], sale[i]);
	}

	return num_sales + 1;
}

int log_customer_ui(char sales_db[][NUM_SALES_PROPS][MAX_LEN],
				char inv_db[][NUM_INV_PROPS][MAX_LEN],
				int num_sales,
				int num_items) {
	char buffer[BUFFER_SIZE] = { 0 };
	char temp_log[NUM_SALES_PROPS][MAX_LEN] = { 0 };

	printf("Enter ID: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	remove_newline(buffer);
	// Determine if item exists
	int item_index =get_customer(inv_db, buffer, num_items);
	if (item_index == -1) {
		printf("ERROR: Item %s does not exist.\n", buffer);
		return num_sales;
	} else {
		strcpy(temp_log[0], buffer);
	}

	printf("Enter name: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	remove_newline(buffer);
	strcpy(temp_log[1], buffer);

	printf("Enter title: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	remove_newline(buffer);
	strcpy(temp_log[2], buffer);


	return log_customer(sales_db, temp_log, num_sales);
}

int add_customer_ui(char inv_db[][NUM_INV_PROPS][MAX_LEN],
					      int num_items) {
	char buffer[BUFFER_SIZE] = { 0 };
	char temp_item[NUM_INV_PROPS][MAX_LEN] = { 0 };

	printf("Enter ID: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	remove_newline(buffer);
	// Determine if item exists
	int item_index = get_customer(inv_db, buffer, num_items);
	if (item_index >= 0) {
		printf("ERROR: Item %s already exists.\n", buffer);
		return num_items;
	} else {
		strcpy(temp_item[0], buffer);
	}

	printf("Enter name: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	remove_newline(buffer);
	strcpy(temp_item[1], buffer);

	printf("Enter phone: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	remove_newline(buffer);
	strcpy(temp_item[2], buffer);

	//printf("Enter quantity: ");
	//fgets(buffer, BUFFER_SIZE, stdin);
	//remove_newline(buffer);
	//strcpy(temp_item[3], buffer);

	return add_customer(inv_db, temp_item, num_items);
}

void list_item(char item[][MAX_LEN]) {
	printf("%-6s %-20.20s %-8s %-4s\n",
			item[0], item[1], item[2], item[3]);
}

void list_customer(char inv_db[][NUM_INV_PROPS][MAX_LEN], int num_items) {
	// Print header
	printf("%-6s %-20s %-8s\n", "ID", "NAME", "PHONE");
	for (int i = 0; i < 41; i++) {
		printf("-");
	}
	printf("\n");

	// Print individual items
	for (int i = 0; i < num_items; i++) {
		list_item(inv_db[i]);
	}
}


int parse_raw_csv(char raw_csv[], char buffer[][MAX_LEN], int num_properties) {
	int property_index = 0;
	char *token = strtok(raw_csv, ",");

	while (token != NULL && property_index < num_properties) {
		// Store the information
		strcpy(buffer[property_index++], token);

		token = strtok(NULL, ",");
	}

	return property_index;
}

int find_customer(char inv_db[][NUM_INV_PROPS][MAX_LEN],
	char search_term[],
	int num_items,
	char filtered_db[][NUM_INV_PROPS][MAX_LEN]) {

	int num_found_items = 0;

	// Search through all items
	for (int i = 0; i < num_items; i++) {
		// Compare search term
		if (strcasestr(inv_db[i][1], search_term) != NULL) {
			for (int j = 0; j < NUM_INV_PROPS; j++) {
				// Copy the product information into a sub-data structure
				strcpy(filtered_db[num_found_items][j], inv_db[i][j]);
			}
			num_found_items++;
		}
	}

	return num_found_items;
}

void find_customer_test() {
	char inv_db[MAX_ITEMS][NUM_INV_PROPS][MAX_LEN] = { 0 };
	char filtered_db[MAX_ITEMS][NUM_INV_PROPS][MAX_LEN] = { 0 };
	int num_items = 0;
	char buffer[BUFFER_SIZE] = { 0 };
	char search_term[] = "hahn";

	// Redirect data from stdin
	fgets(buffer, BUFFER_SIZE, stdin);
	remove_newline(buffer);

	while (strcmp(buffer, "END")) {
		parse_raw_csv(buffer, inv_db[num_items++], NUM_INV_PROPS);
		fgets(buffer, BUFFER_SIZE, stdin);
		remove_newline(buffer);
	}

	int num_found_items = find_customer(inv_db, search_term, num_items, filtered_db);

	list_customer(inv_db, num_items);
	list_customer(filtered_db, num_found_items);
}



int main(){
	char inv_db[MAX_ITEMS][NUM_INV_PROPS][MAX_LEN]={ 0 };
	int  num_items=0;
	int num_inv_items=0;

	//redirection 

	char buffer[BUFFER_SIZE]={ 0 };
	fgets(buffer,BUFFER_SIZE,stdin);
	remove_newline(buffer);
	while(strcmp(buffer,"END")){

		parse_raw_csv(buffer,inv_db[num_items++],NUM_INV_PROPS);
		fgets(buffer,BUFFER_SIZE,stdin);
		remove_newline(buffer);
	}

	list_customer(inv_db,num_items);
	printf("\n");

// adding input from keyboard
//	int num_sales=0;
//	char sales_db[MAX_ITEMS][NUM_SALES_PROPS][MAX_LEN]={ 0 };

//	num_sales=log_customer_ui(sales_db,inv_db,num_sales,num_inv_items);

//	num_inv_items=add_customer_ui(inv_db,num_inv_items);
//	list_customer(inv_db,num_inv_items);
//	find_customer_test();
	return 0;
	}
