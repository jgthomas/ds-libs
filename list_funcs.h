void push(Node **head_ref, void *new_data, size_t data_size);
unsigned int list_length(Node *node);
bool is_empty(Node *node);
void print_list(Node *node, void (*fptr)(void *));
void delete_list(Node *node);
void append(Node **head, void *new_data, size_t data_size);
void reverse(Node **current_node);
bool list_contains(Node *node, void *search, bool (*fptr)(void *, void *));
