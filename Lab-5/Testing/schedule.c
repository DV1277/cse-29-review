#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* NOTE: We define the structs and a few functions to get you started. You
 * will mainly be fixing functions starting with "bad_" and writing tests.
 *
 * Good luck!
 */

struct course {
	int course_id;
	int units;
};

struct schedule {
    struct course **courses;
    int count;
	int capacity;
};

// There are no bugs in these three functions as far as we know.
struct schedule *create_schedule(int capacity) {
    struct schedule *schedule = malloc(sizeof(struct schedule));
	
	if (schedule == NULL) {
		return NULL;
	}

	schedule->courses = malloc(capacity * sizeof(struct course *));


	if (schedule->courses == NULL) {
		free(schedule);
		return NULL;
	}

	for (int i = 0; i < capacity; i++) {
		schedule->courses[i] = NULL;
	}

	schedule->count = 0;
	schedule->capacity = capacity;

	return schedule;
}

struct course *create_course(int id, int units) {
	struct course *course = malloc(sizeof(struct course));

	if (course == NULL) {
		return NULL;
	}
	
	course->course_id = id;
	course->units = units;

	return course;
}

int add_course(struct schedule *schedule,
					struct course *course,
					int index) {
	if (index < 0 || index > schedule->count) {
		return 0;
	}
	if (schedule->count == schedule->capacity) {
		return 0;
	}
	for (int i = schedule->count; i > index; i--) {
		schedule->courses[i] = schedule->courses[i-1];
	}

	schedule->courses[index] = course;
	schedule->count++;

	return 1;
}


/* This function should keep the schedule object in memory, but clear all non-NULL elements of the courses array.
 * It should essentially reset the schedule to its default state.
 * The count and courses array should be similar to a new schedule.
 */
void bad_clear_schedule(struct schedule *schedule) {
    for (int i = 0; i < schedule->count; i++) {
		free(schedule->courses[i]);
		schedule->courses[i] = NULL;
	}

	schedule->count = 0;
}

/* This function should properly remove and free the element in courses at the given index.
 * When the course is dropped, the elements after the index should shift left in the array. 
 * Example (drop C2): [C1, C2, C3] -> [C1, C3, NULL]
 * It should also decrement the count.
 */
void bad_drop_course(struct schedule *schedule, int index) {
	if (index < 0 || index >= schedule->count) {
		return;
	}

	free(schedule->courses[index]);

    for (int i = index; i < schedule->count - 1; i++) {
		schedule->courses[i] = schedule->courses[i+1];
	}
	schedule->courses[schedule->count - 1] = NULL;

    schedule->count--;
}

/* This function should return a pointer to a deep copy of the original schedule.
 * This means that the variables of the copy should be seperate than the original and NOT point to the same address in memory.
 */
struct schedule *bad_copy_schedule(struct schedule *original) {
	struct schedule *copy = create_schedule(original->capacity);

	if (copy == NULL) {
		return NULL;
	}

	for (int i = 0; i < original->count; i++) {
		struct course *course_copy = create_course(original->courses[i]->course_id,
													original->courses[i]->units);
		if (course_copy == NULL) {
			for (int j = 0; j < i; j++) {
				free(copy->courses[j]);
			}
			free(copy->courses);
			free(copy);
			return NULL;
		}
		copy->courses[i] = course_copy;
	}
	copy->count = original->count;

	return copy;
}

void print_schedule(struct schedule *schedule) {
    for (int i = 0; i < schedule->count; i++){
		printf("Course #%d is CSE-%d with %d units\n", i, 
			schedule->courses[i]->course_id, schedule->courses[i]->units); 
	} 
}

/* Write your tests below!
 *
 * As explained in the lab instructions, "assert" checks if the argument is true (nonzero).
 * If the argument is true, the function returns, and nothing special happens.
 * If the argument is false, the function prints an "Assertion failed" error and stops the program.
 * We use "assert" function calls to verify the outcome of a functionality being tested.
 *   By the way, not all tests need to have an assert function call.
 * Use our example for inspiration, and write a few more tests to expose more bugs!
 */

void test_clear_schedule_example() {
    struct schedule *schedule_1 = create_schedule(5);

	add_course(schedule_1, create_course(29 , 4), 0);
	add_course(schedule_1, create_course(21, 4), 1);

	printf("Schedule before clearing: \n");
	print_schedule(schedule_1);

	bad_clear_schedule(schedule_1);

	printf("Schedule after clearing: \n");
	print_schedule(schedule_1);

	assert(schedule_1->courses[1] == NULL);

	free(schedule_1->courses);
	free(schedule_1);
}

void test_clear_schedule() {
	// clearing an empty schedule should be a no-op
	struct schedule *empty = create_schedule(3);
	bad_clear_schedule(empty);
	assert(empty->count == 0);
	assert(empty->courses[0] == NULL);
	free(empty->courses);
	free(empty);

	// clearing twice should not crash or double-free
	struct schedule *schedule = create_schedule(4);
	add_course(schedule, create_course(15, 2), 0);
	add_course(schedule, create_course(20, 5), 1);
	bad_clear_schedule(schedule);
	bad_clear_schedule(schedule);
	assert(schedule->count == 0);
	assert(schedule->courses[0] == NULL);
	assert(schedule->courses[1] == NULL);
	free(schedule->courses);
	free(schedule);
}

void test_drop_course() {
	struct schedule *schedule = create_schedule(5);
	add_course(schedule, create_course(12, 4), 0);
	add_course(schedule, create_course(21, 4), 1);
	add_course(schedule, create_course(29, 4), 2);

	// drop the first course: [12, 21, 29] -> [21, 29, NULL]
	bad_drop_course(schedule, 0);
	assert(schedule->count == 2);
	assert(schedule->courses[0]->course_id == 21);
	assert(schedule->courses[1]->course_id == 29);
	assert(schedule->courses[2] == NULL);

	// drop somewhere in between: [21, 29, 30] -> [21, 30, NULL]
	add_course(schedule, create_course(30, 4), 2);
	bad_drop_course(schedule, 1);
	assert(schedule->count == 2);
	assert(schedule->courses[0]->course_id == 21);
	assert(schedule->courses[1]->course_id == 30);
	assert(schedule->courses[2] == NULL);

	// drop at the end: [21, 30] -> [21, NULL]
	bad_drop_course(schedule, 1);
	assert(schedule->count == 1);
	assert(schedule->courses[0]->course_id == 21);
	assert(schedule->courses[1] == NULL);

	// drop the only remaining course
	bad_drop_course(schedule, 0);
	assert(schedule->count == 0);
	assert(schedule->courses[0] == NULL);

	free(schedule->courses);
	free(schedule);
}

void test_copy_schedule() {
	struct schedule *original = create_schedule(5);
	add_course(original, create_course(12, 4), 0);
	add_course(original, create_course(21, 4), 1);
	add_course(original, create_course(29, 4), 2);

	struct schedule *copy = bad_copy_schedule(original);
	assert(copy != NULL);
	assert(copy != original);
	assert(copy->count == 3);
	assert(copy->capacity == 5);
	for (int i = 0; i < 3; i++) {
		// a deep copy must not share any course pointers
		assert(copy->courses[i] != original->courses[i]);
		assert(copy->courses[i]->course_id == original->courses[i]->course_id);
		assert(copy->courses[i]->units == original->courses[i]->units);
	}
	assert(copy->courses != original->courses);

	// dropping from the original must not affect the copy
	bad_drop_course(original, 1);
	assert(original->count == 2);
	assert(original->courses[0]->course_id == 12);
	assert(original->courses[1]->course_id == 29);
	assert(copy->count == 3);
	assert(copy->courses[1]->course_id == 21);

	// clearing the copy must not affect the original
	bad_clear_schedule(copy);
	assert(copy->count == 0);
	assert(copy->courses[0] == NULL);
	assert(original->count == 2);
	assert(original->courses[0]->course_id == 12);

	free(copy->courses);
	free(copy);

	bad_clear_schedule(original);
	free(original->courses);
	free(original);
}

int main(void) {
    test_clear_schedule_example();
	test_clear_schedule();
	test_drop_course();
	test_copy_schedule();
}
