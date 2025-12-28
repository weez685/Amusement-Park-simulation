
// Written by Jonathan Sun, z5689744
// on 20/04/2025

////////////////////////////////////////////////////////////////////////////////
// Provided Constants
////////////////////////////////////////////////////////////////////////////////
#define MAX_SIZE 100

////////////////////////////////////////////////////////////////////////////////
// Your constants
////////////////////////////////////////////////////////////////////////////////
#define TRUE 1
#define FALSE 0
////////////////////////////////////////////////////////////////////////////////
// Provided Enums
////////////////////////////////////////////////////////////////////////////////

enum ride_type { ROLLER_COASTER, CAROUSEL, FERRIS_WHEEL, BUMPER_CARS, INVALID };

////////////////////////////////////////////////////////////////////////////////
// Provided Structs
////////////////////////////////////////////////////////////////////////////////

struct park {
    // The name of the park
    char name[MAX_SIZE];
    // The total number of visitors in the park
    int total_visitors;
    // The list of rides in the park
    struct ride *rides;
    // The list of visitors in the park
    struct visitor *visitors;
    // The number of rides in the park
    int ride_count;
};

struct ride {
    // The name of the ride
    char name[MAX_SIZE];
    // The type of the ride i.e. 
    // ROLLER_COASTER, CAROUSEL, FERRIS_WHEEL, BUMPER_CARS, INVALID
    enum ride_type type;
    // The number of riders the ride can hold
    int rider_capacity;
    // The number of visitors that can be in the queue
    int queue_capacity;
    // The minimum height required to ride
    double min_height;
    // The queue of visitors waiting to ride
    struct visitor *queue;
    // The next ride in the list
    struct ride *next;
    // Keep track of where a ride is in a linked list
    int ride_index;
    // Count how many people in queue
    int queue_count;
};

struct visitor {
    // The name of the visitor
    char name[MAX_SIZE];
    // The height of the visitor
    double height;
    // The next visitor in the list
    struct visitor *next;
};

////////////////////////////////////////////////////////////////////////////////
// Provided function prototypes
////////////////////////////////////////////////////////////////////////////////
void print_usage(void);
void scan_name(char name[MAX_SIZE]);
void print_ride(struct ride *ride);
enum ride_type scan_type(void);
void print_welcome_message(char name[MAX_SIZE]);

// Additional provided function prototypes
// You won't need to use these functions!
// We use just them to implement some of the provided helper functions.
int scan_token(char *buffer, int buffer_size);
char *type_to_string(enum ride_type type);
enum ride_type string_to_type(char *type_str);

////////////////////////////////////////////////////////////////////////////////
// Your function prototypes
////////////////////////////////////////////////////////////////////////////////

// Stage 1
struct park *initialise_park(char name[MAX_SIZE]);
struct visitor *create_visitor(char name[MAX_SIZE], double height);
struct ride *create_ride(char name[MAX_SIZE], enum ride_type type);
void command_loop(struct park *park);
void add_ride(struct park *park);
void add_visitor(struct park *park);
void print_park(struct park *park);

void append_feature(struct park *park);

int error(
    struct park *park, 
    char *name, 
    enum ride_type type, 
    double height, 
    int is_ride
);

void capacity_message(void);

// Stage 2
void insert_at_nth(struct park *park);
void add_to_queue(struct park *park);

int queue_error(
    struct park *park,
    struct ride *ride, 
    struct visitor *visitor, 
    char ride_name[MAX_SIZE], 
    char visitor_name[MAX_SIZE]);

void remove_from_queue(struct park *park);

void move_visitor(struct park *park);

int check_in_queue(struct ride *ride, char visitor_name[MAX_SIZE]);

struct ride *find_ride(struct park *park, char ride_name[MAX_SIZE]);

struct visitor *find_and_remove_visitor(
    struct park *park, 
    char visitor_name[MAX_SIZE]);

struct visitor *remove_from_any_queue(
    struct park *park, 
    char visitor_name[MAX_SIZE]);

struct visitor *remove_matched_visitor(
    struct ride *ride, 
    struct visitor *current, 
    struct visitor *prev);

void add_visitor_to_roaming(struct park *park, struct visitor *visitor);

void add_visitor_to_ride_queue(struct ride *ride, struct visitor *visitor);

void print_total_visitors(struct park *park);

void visitor_range(struct park *park);

int queue_size(struct ride *ride);

int count_forward(struct park *park, struct ride *start_ride, struct ride *end_ride);

int count_reverse(struct park *park, struct ride *start_ride, struct ride *end_ride);

// Stage 3

void free_park(struct park *park);

void leave_park(struct park *park);

void operate_rides(struct park *park);

void shut_down_ride(struct park *park);

void remove_ride(struct park *park, struct ride *ride);

void free_ride_queue(struct visitor *queue);

void redistribute(struct park *park, struct ride *to_remove);

struct ride *get_next_target(struct park *park, enum ride_type type, struct ride *ride);

void add_visitor_to_target(struct ride *target, struct visitor *visitor);

// Stage 4

void merge_rides(struct park *park);

void combine_rides(struct ride *ride1, struct ride *ride2);

void merge_queues(struct ride *ride1, struct ride *ride2);
// struct ride *find_ride_at_index(struct park *park, int index); 
// (maybe use in future)