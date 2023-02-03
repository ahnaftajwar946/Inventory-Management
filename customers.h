#ifndef CUSTOMERS_H_
#define CUSTOMERS_H_
#include<stdio.h>
#define CUSTOMERS 128
#define MAX_LEN 1024
#define BUFFER_SIZE 1024
#define MAX_ITEMS 1000
#define NUM_INV_PROPS 4
#define NUM_SALES_PROPS 4
#define MAX_SALES 1000
#include<string.h>


int remove_newline(char []);
int add_customer(char [][NUM_INV_PROPS][MAX_LEN],
					   char [][MAX_LEN], int );
int get_customer(char [][NUM_INV_PROPS][MAX_LEN],
					   char [], int);

int log_customer(char [][NUM_SALES_PROPS][MAX_LEN],
	char [][MAX_LEN], int);

int add_customer_ui(char [][NUM_INV_PROPS][MAX_LEN],
					      int);

void list_item(char item[][MAX_LEN]);

void list_customer(char [][NUM_INV_PROPS][MAX_LEN], int);

int log_customer_ui(char [][NUM_SALES_PROPS][MAX_LEN],
				char [][NUM_INV_PROPS][MAX_LEN],
				int ,
				int ) ;

int parse_raw_csv(char [], char [][MAX_LEN], int );

int find_customer(char [][NUM_SALES_PROPS][MAX_LEN],
	char [],
	int ,
	char [][NUM_SALES_PROPS][MAX_LEN]);

	void find_customer_test() ;

#endif