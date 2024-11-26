/*****************
    Student Name 	= Nitish Grover
    Student Number	= 101324174
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here
void print_menu() {
    printf("*************************\n            Main Menu:\n*************************\n");
    printf("1. Register a new user\n 2. Manage a user's profile (change password)\n 3. Manage a user's posts (add/remove)\n 4. Manage a user's friends (add/remove)\n 5. Display a users posts\n 6. Exit\n Enter your choice:\n");
}

user_t *add_user(user_t *users, const char *username, const char *password){
     
    user_t *new_user = (user_t *)malloc(sizeof(user_t));
    assert(new_user!=NULL);

    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->friends = NULL;
    new_user->posts = NULL;
    new_user->next = NULL;
    //user_t *temp = users;

    if (users == NULL ||strcmp(users->username,new_user->username)>0) {
        new_user->next = users;
        return new_user;
    }
    user_t *current = users;
    while (current->next != NULL && strcmp(current->next->username, new_user->username) < 0) {
        current = current->next;
    }

    // Insert the new user
    new_user->next = current->next;
    current->next = new_user;
    return users;
}

user_t *find_user(user_t *users, const char *username){ 
    user_t *curr;
    for (curr = users; curr!=NULL; curr = curr->next) {
        if (strcmp(curr->username,username)==0) {
            return curr;
        } 
    }
    return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username){ 
    friend_t *new_friend = (friend_t *)malloc(sizeof(friend_t));
    assert(new_friend!=NULL);
    strcpy(new_friend->username, username);
    new_friend->next = NULL;
    return new_friend;
}


/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend){ 
    if (user == NULL) {
        return;
    }
    friend_t *friend_to_add = create_friend(friend);
    
    if (user->friends==NULL || (strcmp(friend_to_add->username,user->friends->username)<0)) {
        friend_to_add->next = user->friends;
        user->friends = friend_to_add;
    } else{
        friend_t *temp = user->friends;
        while (temp->next != NULL && strcmp(friend_to_add->username, temp->next->username) > 0) {
            temp = temp->next;
        }
        friend_to_add->next = temp->next;
        temp->next = friend_to_add;
    }
    printf(" Friend added! \n");
    
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name){

    if ( user==NULL || user->friends == NULL) {
        printf("No friends to remove.\n");
        return false;
    }
    friend_t *current = user->friends;
    friend_t *previous = NULL;
    while (current != NULL && strcmp(current->username, friend_name) != 0){
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Friend not found in the list.\n");
        return false;
    }
    else if (previous == NULL){
        user->friends = current->next;
    }else {
        previous->next = current->next;
    }
    free(current);
    printf("friend deleted \n");
    
    return true;

}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text){ 
    post_t *new_post = (post_t *)malloc(sizeof(post_t));
    assert(new_post!=NULL);
    strcpy(new_post->content, text);
    new_post->next = NULL;
    return new_post;

}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text){
    // post_t *curr_post;
    // curr_post->content =  create_post(text);
    if (user==NULL) {
        return;
    } else {
        post_t * post_to_add = create_post(text);
        post_to_add->next = user->posts;
        user->posts = post_to_add;
        printf("Post added! \n");
        return;
    }
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user){
    if (user == NULL || user->posts==NULL) {
        printf("No post to delete! \n");
        return false;
    }
    post_t *first_post;
    first_post = user->posts;
    user->posts = user->posts->next;
    free(first_post);
    printf("Post deleted! \n");
    return true;
}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user){
    post_t *curr; 
    if (user == NULL) {
        printf("No Post available \n");
        return;
    }
    int i = 1;
    for (curr = user->posts ; curr!=NULL; curr = curr->next) {
        printf("%d - %s \n",i, curr->content);
        i++;
    }
}


/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user){ 
    if (user == NULL) {
        printf("");
        return;
    }
    

    friend_t* current_friend_name;
    int counter =1;
    printf("List of %s friends: \n",user->username);
    for (current_friend_name = user->friends;current_friend_name!=NULL;current_friend_name = current_friend_name->next ){
        printf("%d - %s\n",counter,current_friend_name->username);
        counter++;
    } 
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns. 
*/
void display_posts_by_n(user_t *users, int number){ 
    if (users == NULL) {
        return;
    }
    post_t *current = users->posts;
    int total_post = 0;

    post_t *temp = users->posts;
    while (temp!=NULL) {
        total_post++;
        temp = temp->next;
    }
    if (total_post == 0) {
        printf("No post available for %s. \n", users->username);
        return;
    }
    int index = 0;
    while (current!=NULL) {
        for (int i = 0; i < number && current!=NULL ; i++) {
            printf("%d - %s \n", index+1, current->content);
            current = current->next;
            index++;
        }
        if (index>=total_post){
            printf("All post have been displayed \n");
            break;
        }

        printf("Do you want to display more post?(Y/N) \n");

        char userChoice;
        while (getchar() != '\n');
        scanf("%c", &userChoice);
        if (userChoice == 'N' || userChoice=='n') {
            break;
        }
        else if (userChoice == 'Y' || userChoice=='y'){
            for (int j = 0; j < (number + 3) && current!=NULL ; j++) {
            printf("%d - %s \n", index+1, current->content);
            current = current->next;
            index++;
            }
            if (index>=total_post){
            printf("All post have been displayed \n");
            }
            break;
        } else {
            printf("Invalid input. Enter again \n");
            break;
        }   
    }
    return;
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users){ 
    user_t *current_user = users;
    while (current_user != NULL) {
        
        friend_t *current_friend = current_user->friends;
        while (current_friend != NULL) {
            friend_t *temp_friend = current_friend;
            current_friend = current_friend->next;
            free(temp_friend);
        }

        
        post_t *current_post = current_user->posts;
        while (current_post != NULL) {
            post_t *temp_post = current_post;
            current_post = current_post->next;
            free(temp_post);
        }

        user_t *temp_user = current_user;
        current_user = current_user->next;
        free(temp_user);
    }
    return;
}



/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
