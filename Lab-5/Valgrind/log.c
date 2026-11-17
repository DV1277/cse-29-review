#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 10;

struct day {
	int id;
	char * title;
	char * content;
};

struct log {
    struct day **days;
    int count;
	int capacity;
};


void free_log(struct log *the_log) {
    for (int i = 0; i < the_log->count; i++) {
		printf("Freed %s\n", the_log->days[i]->title);
        free(the_log->days[i]->title);
        free(the_log->days[i]->content);
        free(the_log->days[i]);
	}
	free(the_log->days);
	free(the_log);
}

void print_log(struct log* the_log) {
    for (int i = 0; i < the_log->count; i++) {
        printf("%s:\n%s\n\n", the_log->days[i]->title, the_log->days[i]->content);
    }
}

struct log* create_log(void) {
	struct log * log = malloc(sizeof(struct log));
	log->count = 0;
	log->capacity = DEFAULT_CAPACITY;
	log->days = malloc(log->capacity * sizeof(struct day *));
    return log;
} 

void add_day(struct log* log, char* title, char* content){
	if(log->count < log->capacity){
		struct day* brand_new_day = malloc(sizeof(struct day));
		log->days[log->count] = brand_new_day;
		brand_new_day->title = malloc(strlen(title)+1);
		brand_new_day->content = malloc(strlen(content)+1);
		strcpy(brand_new_day->title, title);
		strcpy(brand_new_day->content, content);
	
		log->count++;
	}
}

int main(void) {
    struct log *ourLog = create_log();
	add_day(ourLog, "The Best Final", "Took the final and went for a car ride, then went to Old Town for dinner with the peeps");
	add_day(ourLog, "Finding the flag", "after some time, we cracked the password and fixed the broken piece of the puzzle and solved it. We did it!");
    print_log(ourLog);
	free_log(ourLog);
}
