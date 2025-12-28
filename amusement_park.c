// Written by Jonathan Sun, z5689744
// on 20/04/2025

////////////////////////////////////////////////////////////////////////////////
// Provided Libraries
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "amusement_park.h"

////////////////////////////////////////////////////////////////////////////////
// Your libraries
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////

// Stage 1.1
// Function to initialise the park
// Params:
//      name - the name of the park
// Returns: a pointer to the park
struct park *initialise_park(char name[MAX_SIZE]) {
    // TODO: Replace this with your code
    struct park *my_park = malloc(sizeof(struct park));
    strcpy(my_park->name, name);
    my_park->total_visitors = 0;
    my_park->rides = NULL;
    my_park->visitors = NULL;
    my_park->ride_count = 0;

    return my_park;
}

// Stage 1.1
// Function to create a visitor
// Params:
//      name - the name of the visitor
//      height - the height of the visitor
// Returns: a pointer to the visitor
struct visitor *create_visitor(char name[MAX_SIZE], double height) {
    // TODO: Replace this with your code
    struct visitor *my_visitor = malloc(sizeof(struct visitor));
    strcpy(my_visitor->name, name);
    my_visitor->height = height;
    my_visitor->next = NULL;

    return my_visitor;
}

// Stage 1.1
// Function to create a ride
// Params:
//      name - the name of the ride
//      type - the type of the ride
// Returns: a pointer to the ride
struct ride *create_ride(char name[MAX_SIZE], enum ride_type type) {
    // TODO: Replace this with your code
    struct ride *my_ride = malloc(sizeof(struct ride));
    strcpy(my_ride->name, name);
    my_ride->type = type;

    if (type == ROLLER_COASTER) {
        my_ride->rider_capacity = 4;
        my_ride->queue_capacity = 7;
        my_ride->min_height = 120.0;
    } else if (type == CAROUSEL) {
        my_ride->rider_capacity = 6;
        my_ride->queue_capacity = 9;
        my_ride->min_height = 60.0;
    } else if (type == FERRIS_WHEEL) {
        my_ride->rider_capacity = 8;
        my_ride->queue_capacity = 11;
        my_ride->min_height = 75.0;
    } else if (type == BUMPER_CARS) {
        my_ride->rider_capacity = 10;
        my_ride->queue_capacity = 13;
        my_ride->min_height = 100.0;
    } else {
        free(my_ride);
        return NULL;
    }
    my_ride->queue = NULL;
    my_ride->next = NULL;

    return my_ride;
}

// Stage 1.2
// Function to run the command loop
//
// Params:
//     park - a pointer to the park
// Returns: None
void command_loop(struct park *park) {
    // TODO: Replace this with your code
    char command;
    printf("Enter command: ");
    while (scanf(" %c", &command) == 1 && command != 'q') {
        if (command == '?') {
            print_usage();
        } else if (command == 'a') {
            append_feature(park);
        } else if (command == 'p') {
            print_park(park);
        } else if (command == 'i') {
            insert_at_nth(park);
        } else if (command == 'j') {
            add_to_queue(park);
        } else if (command == 'd') {
            remove_from_queue(park);
        } else if (command == 'm') {
            move_visitor(park);
        } else if (command == 't') {
            print_total_visitors(park);
        } else if (command == 'c') {
            visitor_range(park);     
        } else if (command == 'l') {
            leave_park(park);
        } else if (command == 'r') {
            operate_rides(park);
        } else if (command == 'S') {
            shut_down_ride(park);   
        } else if (command == 'M') {
            merge_rides(park);
        } else {
            printf("ERROR: Invalid command.\n");  
        }
        printf("Enter command: ");
    }
    free_park(park);
    return;
}

// Stage 1.3
// Function to add a ride to the park
// Params:
//      park - a pointer to the park
// Returns: None
void add_ride(struct park *park) {
    // TODO: Replace this with your code
    char ride_name[MAX_SIZE];
    scan_name(ride_name);
    enum ride_type type = scan_type();

    if (error(park, ride_name, type, 0, 1) == 1) {
        return;
    }
    
    struct ride *new_ride = create_ride(ride_name, type);

    // Set the ride_index for the new ride and increment ride_count
    new_ride->ride_index = park->ride_count;
    park->ride_count++;

    struct ride *head = park->rides;

    // Append to end of ride list
    if (head == NULL) {
        park->rides = new_ride;
    } else {
        struct ride *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_ride;
    }
    printf("Ride: '%s' added!\n", ride_name);
    return;
}

// Stage 1.3
// Function to add a visitor to the park
// Params:
//      park - a pointer to the park
// Returns: None
void add_visitor(struct park *park) {
    // TODO: Replace this with your code
    char visitor_name[MAX_SIZE];
    scan_name(visitor_name);
    double height;
    scanf("%lf", &height);

    if (error(park, visitor_name, INVALID, height, 0) == 1) {
        return;
    }

    struct visitor *new_visitor = create_visitor(visitor_name, height);

    struct visitor *head = park->visitors;

    if (head == NULL) {
        park->visitors = new_visitor;
    } else {
        struct visitor *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_visitor;
    }
    park->total_visitors++;
    printf("Visitor: '%s' has entered the amusement park!\n", visitor_name);
    return;
}

// Stage 1.4
// Function to print the park
// Params:
//      park - a pointer to the park
// Returns: None
void print_park(struct park *park) {
    // TODO: Replace this with your code
    printf("===================[ UNSW ]===================\n");
    struct ride *current_ride = park->rides;
    struct visitor *current_vis = park->visitors;
    if (current_ride == NULL && current_vis == NULL) {
        printf("The amusement park is empty!\n\n");
        return;
    }

    printf("Rides:\n");
    if (current_ride == NULL) {
        printf("  No rides!\n");
    }
    while (current_ride != NULL) {
        print_ride(current_ride);
        current_ride = current_ride->next;
    }

    printf("Visitors:\n");
    if (current_vis == NULL) {
        printf("  No visitors!\n\n");
        return;
    }
    while (current_vis != NULL) {
        printf("  %s (%.2lfcm)\n", 
        current_vis->name, current_vis->height);
        current_vis = current_vis->next;
    }
    printf("\n");
    return;
}

////////////////////////////////////////////////////////////////////////////////
// Providing function definitions
////////////////////////////////////////////////////////////////////////////////

// Function to print the usage of the program
// '?' command
// Params: None
// Returns: None
// Usage:
// ```
//      print_usage();
// ```
void print_usage(void) {
    printf(
        "======================[ CS Amusement Park ]======================\n"
        "      ===============[     Usage Info     ]===============       \n"
        "  a r [ride_name] [ride_type]                                    \n"
        "    Add a ride to the park.                                      \n"
        "  a v [visitor_name] [visitor_height]                            \n"
        "    Add a visitor to the park.                                   \n"
        "  i [index] [ride_name] [ride_type]                              \n"
        "    Insert a ride at a specific position in the park's ride list.\n"
        "  j [ride_name] [visitor_name]                                   \n"
        "    Add a visitor to the queue of a specific ride.               \n"
        "  m [visitor_name] [ride_name]                                   \n"
        "    Move a visitor from roaming to a ride's queue.               \n"
        "  d [visitor_name]                                               \n"
        "    Remove a visitor from any ride queue and return to roaming.  \n"
        "  p                                                              \n"
        "    Print the current state of the park, including rides and     \n"
        "    visitors.                                                    \n"
        "  t                                                              \n"
        "    Display the total number of visitors in the park, including  \n"
        "    those roaming and in ride queues.                            \n"
        "  c [start_ride] [end_ride]                                      \n"
        "    Count and display the number of visitors in queues between   \n"
        "    the specified start and end rides, inclusive.                \n"
        "  l [visitor_name]                                               \n"
        "    Remove a visitor entirely from the park.                     \n"
        "  r                                                              \n"
        "    Operate all rides, allowing visitors to enjoy the rides      \n"
        "    and moving them to roaming after their ride.                 \n"
        "  M [ride_type]                                                  \n"
        "    Merge the two smallest rides of the specified type.          \n"
        "  s [n] [ride_name]                                              \n"
        "    Split an existing ride into `n` smaller rides.               \n"
        "  q                                                              \n"
        "    Quit the program and free all allocated resources.           \n"
        "  T [n] [command]                                                \n"
        "    Scheduled the [command] to take place `n` ticks              \n"
        "    in the future.                                               \n"
        "  ~ [n]                                                          \n"
        "    Progress the schedule for `n` ticks.                         \n"
        "  ?                                                              \n"
        "    Show this help information.                                  \n"
        "=================================================================\n");
}

// Function to print a welcome message
// Params:
//      name - the name of the park
// Returns: None
// Usage:
// ```
//      print_welcome_message(name);
// ```
void print_welcome_message(char name[MAX_SIZE]) {
    printf("===================[ %s ]===================\n", name);
}

// Function to print a ride
// Params:
//      ride - the ride to print
// Returns: None
// Usage:
// ```
//      print_ride(ride);
// ```
void print_ride(struct ride *ride) {
    printf("  %s (%s)\n", ride->name, type_to_string(ride->type));
    printf("    Rider Capacity: %d\n", ride->rider_capacity);
    printf("    Queue Capacity: %d\n", ride->queue_capacity);
    printf("    Minimum Height: %.2lfcm\n", ride->min_height);
    printf("    Queue:\n");
    struct visitor *curr_visitor = ride->queue;
    if (curr_visitor == NULL) {
        printf("      No visitors\n");
    } else {
        while (curr_visitor != NULL) {
            printf(
                "      %s (%.2lfcm)\n", curr_visitor->name,
                curr_visitor->height);
            curr_visitor = curr_visitor->next;
        }
    }
}

// Scan in the a name string into the provided buffer, placing
// '\0' at the end.
//
// Params:
//      name - a char array of length MAX_SIZE, which will be used
//                  to store the name.
// Returns: None
// Usage:
// ```
//      char name[MAX_SIZE];
//      scan_name(name);
// ```
void scan_name(char name[MAX_SIZE]) {
    scan_token(name, MAX_SIZE);
}

// Scans a string and converts it to a ride_type.
//
// Params: None
// Returns:
//      The corresponding ride_type, if the string was valid,
//      Otherwise, returns INVALID.
//
// Usage:
// ```
//      enum ride_type type = scan_type();
// ```
//
enum ride_type scan_type(void) {
    char type[MAX_SIZE];
    scan_token(type, MAX_SIZE);
    return string_to_type(type);
}

////////////////////////////////////////////////////////////////////////////////
// Additional provided functions
////////////////////////////////////////////////////////////////////////////////

// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

enum ride_type string_to_type(char *type_str) {
    int len = strlen(type_str);

    if (strncasecmp(type_str, "roller_coaster", len) == 0) {
        return ROLLER_COASTER;
    }
    if (strncasecmp(type_str, "CAROUSEL", len) == 0) {
        return CAROUSEL;
    }
    if (strncasecmp(type_str, "FERRIS_WHEEL", len) == 0) {
        return FERRIS_WHEEL;
    }
    if (strncasecmp(type_str, "BUMPER_CARS", len) == 0) {
        return BUMPER_CARS;
    }

    return INVALID;
}

char *type_to_string(enum ride_type type) {
    if (type == ROLLER_COASTER) {
        return "ROLLER_COASTER";
    }
    if (type == CAROUSEL) {
        return "CAROUSEL";
    }
    if (type == FERRIS_WHEEL) {
        return "FERRIS_WHEEL";
    }
    if (type == BUMPER_CARS) {
        return "BUMPER_CARS";
    }
    return "INVALID";
}

int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    scanf(" ");

    while (i < buffer_size - 1 && (num_scanned = scanf("%c", &c)) == 1 &&
           !isspace(c)) {
        buffer[i++] = c;
    }

    if (i > 0) {
        buffer[i] = '\0';
    }

    return num_scanned;
}

////////////////////////////////////////////////////////////////////////////////
// Own Function definitions
////////////////////////////////////////////////////////////////////////////////

// Handle 'a' command to add ride or visitor
void append_feature(struct park *park) {
    char command;
    scanf(" %c", &command);
    if (command == 'r') {
        add_ride(park);
    } else if (command == 'v') {
        add_visitor(park);
    }
    return;
}

// Validate input for rides/visitors and checks for duplicates
int error(
    struct park *park, 
    char *name, 
    enum ride_type type, 
    double height, 
    int is_ride) {
    if (is_ride == 1) {
        // Ride validation
        if (type == INVALID) {
            printf("ERROR: Invalid ride type.\n");
            return 1;
        }
        struct ride *current_ride = park->rides;
        while (current_ride != NULL) {
            if (strcmp(current_ride->name, name) == 0) {
                printf("ERROR: '%s' already exists.\n", current_ride->name);
                return 1;
            }
            current_ride = current_ride->next;
        }
    } else {
        // Visitor validation
        struct visitor *current_vis = park->visitors;
        while (current_vis != NULL) {
            if (strcmp(current_vis->name, name) == 0) {
                printf("ERROR: '%s' already exists.\n", current_vis->name);
                return 1;
            }
            current_vis = current_vis->next;
        }
        if (height < 50 || height > 250) {
            printf("ERROR: Height must be between 50 and 250.\n");
            return 1;
        }
        if (park->total_visitors >= 40) {
            capacity_message();
            return 1;
        } 
    }
    return 0;
}
// Print park capacity error message
void capacity_message(void){
    printf(
    "ERROR: Cannot add another visitor to the park. The park is at capacity.\n"
    );
}
// Insert new ride at specified position in ride list
void insert_at_nth(struct park *park) {
    int position;
    scanf("%d", &position);

    char ride_name[MAX_SIZE];
    scan_name(ride_name);
    enum ride_type type = scan_type();
    // Validate and check for errors
    if (position < 1) {
        printf("ERROR: n must be at least 1.\n");
        return;
    }

    if (error(park, ride_name, type, 0, 1) == 1) {
        return;
    }
    // Create new ride and insert at position
    struct ride *new_ride = create_ride(ride_name, type);
    if (park->rides == NULL || position == 1) {
        new_ride->next = park->rides;
        park->rides = new_ride;
        printf("Ride: '%s' inserted!\n", ride_name);
        return;
    }
    // Find insertion point and add ride
    struct ride *current = park->rides;
    int counter = 1;
    while (current->next != NULL && counter != position - 1) {
        current = current->next;
        counter++;
    }
    new_ride->next = current->next;
    current->next = new_ride;
    printf("Ride: '%s' inserted!\n", ride_name);
}

void add_to_queue(struct park *park) {
    char ride_name[MAX_SIZE];
    char vis_name[MAX_SIZE];
    scan_name(ride_name);
    scan_name(vis_name);
    
    // Find the specified ride
    struct ride *current_ride = park->rides;
    while (current_ride != NULL && strcmp(current_ride->name, ride_name) != 0) {
        current_ride = current_ride->next;
    }
    // Find the specified visitor
    struct visitor *current_vis = park->visitors;
    struct visitor *prev_visitor = NULL;
    
    while (current_vis != NULL && strcmp(current_vis->name, vis_name) != 0) {
        prev_visitor = current_vis;
        current_vis = current_vis->next;
    }
    // Validate the queue operation
    if (queue_error(park, current_ride, current_vis, ride_name, vis_name)) {
        return;
    }

    // Check if visitor was at head or middle/end of list & add to ride queue 
    if (prev_visitor == NULL) {
        park->visitors = current_vis->next;
    } else {
        prev_visitor->next = current_vis->next;
    }
    current_vis->next = NULL; 
    
    // If queue is empty, become first in line
    if (current_ride->queue == NULL) {
        current_ride->queue = current_vis;
    } else {
        // Find end of queue and add to end
        struct visitor *queue_end = current_ride->queue;
        while (queue_end->next != NULL) {
            queue_end = queue_end->next;
        }
        queue_end->next = current_vis;
    }
    printf("Visitor: '%s' has entered the queue for '%s'.\n", 
            vis_name, ride_name);
}
// Validates queues
int queue_error(
    struct park *park,
    struct ride *ride, 
    struct visitor *visitor, 
    char ride_name[MAX_SIZE], 
    char visitor_name[MAX_SIZE]) {
    if (ride == NULL) {
        printf("ERROR: No ride exists with name '%s'.\n", ride_name);
        return 1;
    }
    if (visitor == NULL) {
        printf("ERROR: No visitor exists with name '%s'.\n", visitor_name);
        return 1;
    }
    if (visitor->height < ride->min_height) {
        printf("ERROR: '%s' is not tall enough to ride '%s'.\n", 
                visitor_name, ride_name);
        return 1;
    }

    // Check queue size
    int queue_size = 0;
    struct visitor *visitor_queue = ride->queue;
    while (visitor_queue != NULL) {
        queue_size++;
        visitor_queue = visitor_queue->next;
    }
    if (queue_size >= ride->queue_capacity) {
        printf("ERROR: The queue for '%s' is full.", ride_name);
        printf(" '%s' cannot join the queue.\n", visitor_name);
        return 1;
    }
    return 0;
}
// Remove visitor from any ride queue and returns them to roaming
void remove_from_queue(struct park *park) {
    char visitor_name[MAX_SIZE];
    scan_name(visitor_name);

    struct visitor *removed_visitor = remove_from_any_queue(park, visitor_name);
    
    if (removed_visitor == NULL) {
        printf("ERROR: Visitor '%s' not found in any queue.\n", visitor_name);
        return;
    }

    add_visitor_to_roaming(park, removed_visitor);
    printf("Visitor: '%s' has been removed from their", visitor_name);
    printf(" ride queue and is now roaming the park.\n");
}
// Move visitor between roaming and ride queues
void move_visitor(struct park *park) {
    char visitor_name[MAX_SIZE];
    char ride_name[MAX_SIZE];
    scan_name(visitor_name);
    scan_name(ride_name);

    // Find target ride
    struct ride *target_ride = find_ride(park, ride_name);
    if (target_ride == NULL) {
        printf("ERROR: No ride exists with name '%s'.\n", ride_name);
        return;
    }

    // Check if already in target queue
    if (check_in_queue(target_ride, visitor_name)) {
        printf("ERROR: '%s' is already in the queue for '%s'.\n", 
                visitor_name, ride_name);
        return;
    }

    // Try to find and remove visitor from roaming or any queue
    struct visitor *visitor = find_and_remove_visitor(park, visitor_name);
    if (visitor == NULL) {
        printf("ERROR: No visitor with name: '%s' exists.\n", visitor_name);
        return;
    }

    // Validate move with queue_error and Return to roaming if error
    if (queue_error(park, target_ride, visitor, ride_name, visitor_name)) {
        add_visitor_to_roaming(park, visitor); 
        return;
    }

    // Add to target queue
    add_visitor_to_ride_queue(target_ride, visitor);
    printf("Visitor: '%s' has been moved to the queue for '%s'.\n", 
            visitor_name, ride_name);
}
// Check if visitor is in a specific ride's queue
int check_in_queue(struct ride *ride, char visitor_name[MAX_SIZE]) {
    struct visitor *current = ride->queue;
    while (current != NULL) {
        if (strcmp(current->name, visitor_name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
// Add visitor to end of ride's queue
void add_visitor_to_ride_queue(struct ride *ride, struct visitor *visitor) {
    visitor->next = NULL;
    if (ride->queue == NULL) {
        ride->queue = visitor;
    } else {
        struct visitor *last = ride->queue;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = visitor;
    }
}
// Add visitor to end of roaming list
void add_visitor_to_roaming(struct park *park, struct visitor *visitor) {
    visitor->next = NULL;
    if (park->visitors == NULL) {
        park->visitors = visitor;
    } else {
        struct visitor *last = park->visitors;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = visitor;
    }
}
// Find specific ride name in park
struct ride *find_ride(struct park *park, char ride_name[MAX_SIZE]) {
    struct ride *current = park->rides;
    while (current != NULL && strcmp(current->name, ride_name) != 0) {
        current = current->next;
    }
    return current;
}
// Find and removes visitor from roaming or queue
struct visitor *find_and_remove_visitor(
    struct park *park, 
    char visitor_name[MAX_SIZE]) {
    // Check roaming visitors first
    struct visitor *current = park->visitors;
    struct visitor *prev = NULL;
    while (current != NULL && strcmp(current->name, visitor_name) != 0) {
        prev = current;
        current = current->next;
    }
    // If visitor was found
    if (current != NULL) {
        // Remove from roaming
        // Consider when visitor is at head of list
        if (prev == NULL) {
            // Change head of list
            park->visitors = current->next;
        } else {
            // Skip current node and point to next
            prev->next = current->next;
        }
        // Isolate node so it doesnt point to next node anymore
        current->next = NULL;
        return current;
    }
    
    // If not in roaming, check queues
    return remove_from_any_queue(park, visitor_name);
}
// Go to ride and remove visitor from queue 
struct visitor *remove_from_any_queue(
    struct park *park, 
    char visitor_name[MAX_SIZE]) {

    struct ride *ride = park->rides;
    while (ride != NULL) {
        struct visitor *current = ride->queue;
        struct visitor *prev = NULL;
        
        while (current != NULL) {
            if (strcmp(current->name, visitor_name) == 0) {
                return remove_matched_visitor(ride, current, prev);
            }
            prev = current;
            current = current->next;
        }
        ride = ride->next;
    }
    // Not found in any queue
    return NULL;
}
// Helper function to remove and return matched visitor (also to reduce nesting)
struct visitor *remove_matched_visitor(
    struct ride *ride, 
    struct visitor *current, 
    struct visitor *prev) {

    if (prev == NULL) {
        // Remove from head
        ride->queue = current->next;
    } else {
        // Remove from middle/end
        prev->next = current->next;
    }
    current->next = NULL;
    return current;
}
// Print visitor stats
void print_total_visitors(struct park *park) {
    int total_visitors = 0;
    int roaming_visitors = 0;
    int queued_visitors = 0;
    
    // Count roaming visitors
    struct visitor *visitor = park->visitors;
    while (visitor != NULL) {
        roaming_visitors++;
        visitor = visitor->next;
    }
    
    // Count visitors in all ride queues
    struct ride *ride = park->rides;
    while (ride != NULL) {
        struct visitor *queue = ride->queue;
        while (queue != NULL) {
            queued_visitors++;
            queue = queue->next;
        }
        ride = ride->next;
    }
    total_visitors = roaming_visitors + queued_visitors;
    printf("Total visitors: %d\n", total_visitors);
    printf("Visitors walking around: %d\n", roaming_visitors);
    printf("Visitors in queues: %d\n", queued_visitors);
}
// Count visitors between two rides 
void visitor_range(struct park *park) {
    char start_name[MAX_SIZE], end_name[MAX_SIZE], direction;
    int count = 0;

    scan_name(start_name);
    scan_name(end_name);
    scanf(" %c", &direction);

    struct ride *start_ride = find_ride(park, start_name);
    struct ride *end_ride = find_ride(park, end_name);
    // Consider edge cases/errors
    if (start_ride == NULL || end_ride == NULL) {
        printf("ERROR: One or both rides do not exist ('%s' or '%s').\n", 
                start_name, end_name);
        return;
    }
    if (strcmp(start_name, end_name) == 0) {
        count = queue_size(start_ride);
        printf("Total visitors from '%s' to '%s': %d.\n", 
                start_name, end_name, count);
        return;
    }
    // Handle forwards direction here
    if (direction == '>') {
        count = count_forward(park, start_ride, end_ride);
        printf("Total visitors from '%s' to '%s': %d.\n", 
               start_name, end_name, count);
    } 
    // Handle backwards direction here
    else if (direction == '<') {
        count = count_reverse(park, start_ride, end_ride);
        printf("Total visitors from '%s' to '%s': %d.\n", 
               end_name, start_name, count);
    }
}

// Count number of visitors in a ride queue
int queue_size(struct ride *ride) {
    int count = 0;
    struct visitor *current = ride->queue;  
    
    // Traverse through the entire queue
    while (current != NULL) {
        count++;
        current = current->next;  
    }
    return count;
}
// count visitors in forward direction (>)
int count_forward(
    struct park *park, 
    struct ride *start_ride, 
    struct ride *end_ride) {

    int count = 0;
    int start = 0;  
    struct ride *current = park->rides;
    
    // First pass from start to end of list
    while (current != NULL) {
        if (start == 0 && current == start_ride) {
            start = 1;
        }
        if (start == 1) {
            count += queue_size(current);
            if (current == end_ride) {
                return count;
            } 
        }
        current = current->next;
    }
    
    // If not found, wrap around from beginning
    current = park->rides;
    while (current != end_ride) {
        count += queue_size(current);
        current = current->next;
    }
    // Include end ride
    count += queue_size(current); 
    
    return count;
}
// count visitors in reverse direction (<)
int count_reverse(
    struct park *park, 
    struct ride *start_ride, 
    struct ride *end_ride) {

    int count = 0;
    struct ride *current = park->rides;
    
    // First find the end ride to start counting from
    while (current != NULL && current != end_ride) {
        current = current->next;
    }
    
    if (current != NULL) {
        // Count from end ride to start of list
        while (current != NULL) {
            count += queue_size(current);
            if (current == start_ride) {
                return count;
            } 
            current = current->next;
        }
        
        // If start not found, wrap around from beginning
        current = park->rides;
        while (current != start_ride) {
            count += queue_size(current);
            current = current->next;
        }
        // Include start ride
        count += queue_size(current); 
    }
    
    return count;
}
// Frees all memory allocated for the park
void free_park(struct park *park) {
    struct ride *current_ride = park->rides;
    struct ride *prev_ride = NULL;
    struct visitor *current_vis = park->visitors;
    struct visitor *prev_visitor = NULL;

    // Free roaming visitors
    while (current_vis != NULL) {
        prev_visitor = current_vis;
        current_vis = current_vis->next;
        free(prev_visitor);
    }
    // Free rides and their queues
    while (current_ride != NULL) {
        prev_ride = current_ride;
        current_vis = current_ride->queue;
        while (current_vis != NULL) {
            prev_visitor = current_vis;
            current_vis = current_vis->next;
            free(prev_visitor);
        }
        prev_ride = current_ride;
        current_ride = current_ride->next;
        free(prev_ride);
    }
    free(park);
}
// Remove visitor from park
void leave_park(struct park *park) {
    char visitor_name[MAX_SIZE];
    scan_name(visitor_name);

    struct visitor *leaving = find_and_remove_visitor (park, visitor_name);
    if (leaving != NULL) {
        free(leaving);
        printf("Visitor: '%s' has left the park.\n", visitor_name);
    } else {
        printf("ERROR: Visitor '%s' not found in the park.\n", visitor_name);
    }
}
// Handle ride operations and move to roaming
void operate_rides(struct park *park) {
    if (park == NULL || park->rides == NULL) {
        return;
    }

    // First, count the number of rides
    int ride_count = 0;
    struct ride *current = park->rides;
    while (current != NULL) {
        ride_count++;
        current = current->next;
    }

    // Process rides from last to first
    for (int i = ride_count - 1; i >= 0; i--) {
        // Find the i-th ride
        current = park->rides;
        for (int j = 0; j < i; j++) {
            current = current->next;
        }

        // Process this ride
        int capacity = current->rider_capacity;
        while (capacity > 0 && current->queue != NULL) {
            struct visitor *visitor = current->queue;
            current->queue = visitor->next;
            add_visitor_to_roaming(park, visitor);
            capacity--;
        }
    }
}
// Shut down ride and redistribute visitors in queue
void shut_down_ride(struct park *park) {
    char ride_name[MAX_SIZE];
    scan_name(ride_name);
    
    struct ride *to_remove = find_ride(park, ride_name);
    if (to_remove == NULL) {
        printf("ERROR: No ride exists with name: '%s'.\n", ride_name);
        return;
    }

    // Count number of visitors at ride
    to_remove->queue_count = queue_size(to_remove);
    // If no visitors, free ride
    if (to_remove->queue_count == 0) {
        remove_ride(park, to_remove);
        printf("Ride: '%s' shut down.\n", ride_name);
        return;
    }
    // Find rides of same type and check available spots
    int available = 0;
    // Dont include ride that is being shut down
    int same_type = -1;
    struct ride *current = park->rides;
    while (current != NULL) {
        if (current != NULL && current->type == to_remove->type) {
            available += (current->queue_capacity - queue_size(current));
            same_type++;
        } 
        current = current->next;
    }

    if (available < to_remove->queue_count || same_type == 0) {
        printf("ERROR: Not enough capacity to");
        printf(" redistribute all visitors from '%s'.\n", ride_name);
        // Move visitors back to roaming before freeing ride
        while (to_remove->queue != NULL) {
            struct visitor *visitor = to_remove->queue;
            to_remove->queue = visitor->next;
            add_visitor_to_roaming(park, visitor);
        }
        remove_ride(park, to_remove);
        printf("Ride: '%s' shut down.\n", ride_name);
    
    } else {
        redistribute(park, to_remove);
        remove_ride(park, to_remove);
        printf("Ride: '%s' shut down.\n", ride_name);
    }
}
// Remove ride from park
void remove_ride(struct park *park, struct ride *ride) {
    if (park->rides == ride) {
        // remove head
        park->rides = ride->next;
    } else {
        struct ride *prev = park->rides;
        // go through linked list until we reach the ride to remove
        while (prev != NULL && prev != ride) {
            prev = prev->next;
        }
        if (prev != NULL) {
            // remove from mid/end
            prev->next = ride->next;
        }
    }
    free(ride);
}
// Redistribute visitors from shut-down ride to others of same type
void redistribute(struct park *park, struct ride *to_remove) {
    struct ride *target = NULL;

    // Find first ride of same type (excluding the one being removed)
    target = get_next_target(park, to_remove->type, NULL);
    if (target == to_remove) {
        target = get_next_target(park, to_remove->type, target);
    }

    while (to_remove->queue != NULL) {
        if (target == NULL || target == to_remove) {
            // No more target rides
            return;
        }
        // Calculate available space in current target
        int available = target->queue_capacity - queue_size(target);
        while (available > 0 && to_remove->queue != NULL) {
            struct visitor *visitor = to_remove->queue;
            to_remove->queue = visitor->next;
            add_visitor_to_ride_queue(target, visitor);
            available--;
        }
    }
}
// Get next ride of specified type
struct ride *get_next_target(
    struct park *park, 
    enum ride_type type, 
    struct ride *ride) {

    struct ride *current;
    
    if (ride == NULL) {
        // Start from beginning
        current = park->rides;
    } else {
        // Start after specified ride
        current = ride->next;
    }
    // Find next ride of matching type
    while (current != NULL) {
        if (current->type == type) {
            return current;
        }
        current = current->next;
    }
    // Not found
    return NULL;
}
// Add visitor to chosen ride's queue
void add_visitor_to_target(struct ride *target, struct visitor *visitor) {
    visitor->next = NULL;
    if (target->queue == NULL) {
        target->queue = visitor;
        return;
    }
    
    struct visitor *last = target->queue;
    while (last->next != NULL) last = last->next;
    last->next = visitor;
}
// Merge 2 rides of same type
void merge_rides(struct park *park) {
    enum ride_type type = scan_type();
    int same_type = 0;
    struct ride *current = park->rides;
    struct ride *ride1 = NULL;
    struct ride *ride2 = NULL;

    // Find two smallest rides of the type and count rides of this type
    while (current != NULL) {
        if (current->type == type) {
            same_type++;
            if (ride1 == NULL || queue_size(current) < queue_size(ride1)) {
                ride2 = ride1;
                ride1 = current;
            } else if (ride2 == NULL ||
                        queue_size(current) < queue_size(ride2)) {
                ride2 = current;
            }
        }
        current = current->next;
    }
    // Check if there are enough rides of same type
    if (same_type < 2) {
        printf("ERROR: Not enough rides of the specified type to merge.\n");
        return;
    } 
    // If queues are equal size, ensure ride1 is the one with smaller ride_index
    if (queue_size(ride1) == queue_size(ride2) && 
        ride1->ride_index > ride2->ride_index) {
        struct ride *temp = ride1;
        ride1 = ride2;
        ride2 = temp;
    }
    combine_rides(ride1, ride2);
    // Clear ride2 from ride list and ride2 queue pointer since moved to ride1
    struct ride *prev = NULL;
    current = park->rides;
    while (current != NULL && current != ride2) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        park->rides = ride2->next;
    } else {
        prev->next = ride2->next;
    }
    ride2->queue = NULL;
    remove_ride(park, ride2);
    printf("Merged the two smallest");
    printf(" rides of type '%s'.\n", type_to_string(type));
}
// Combine ride stats and merge queues
void combine_rides(struct ride *ride1, struct ride *ride2) {
    // Combine capacities
    ride1->rider_capacity += ride2->rider_capacity;
    ride1->queue_capacity += ride2->queue_capacity;
    
    // Merge the queues
    merge_queues(ride1, ride2); 
}
// Alternate queued visitors based off queue length
void merge_queues(struct ride *ride1, struct ride *ride2) {
    struct visitor *merged_queue = NULL;
    struct visitor *prev = NULL;
    struct visitor *queue1 = ride1->queue;
    struct visitor *queue2 = ride2->queue;

    // Swap if ride2 has longer queue
    if (queue_size(ride2) > queue_size(ride1)) {
        struct visitor *temp = queue1;
        queue1 = queue2;
        queue2 = temp;
    }
    // Alternate merging starting with longer queue
    while (queue1 != NULL || queue2 != NULL) {
        // First initialize the merged queue with the first visitor
        if (queue1 != NULL) {
            if (merged_queue == NULL) {
                merged_queue = queue1;
                prev = queue1;
            } else {
                prev->next = queue1;
                prev = prev->next;
            }
            queue1 = queue1->next;
        }
        
        if (queue2 != NULL) {
            if (merged_queue == NULL) {
                merged_queue = queue2;
                prev = queue2;
            } else {
                prev->next = queue2;
                prev = prev->next;
            }
            queue2 = queue2->next;
        }
    }
    // Point ride1's queue to our newly merged queue
    ride1->queue = merged_queue;
    ride2->queue = NULL;
}