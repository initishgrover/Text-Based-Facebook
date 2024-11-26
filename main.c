/********* main.c ********
    Student Name 	= Nitish Grover 
    Student Number	= 101324174
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    int choice;
    char new_username[30];
    char new_password[15];
    char old_password[15];
    char username_to_update[30];
    char username_to_manage_post[30];
    char username_to_update_friends[30];
    char new_post[250];
    char friend_name[30];
    char friend_name_to_delete[30];
    char username_to_display_post[30];
    user_t *currentUser;
    do {
       
        print_menu();
        scanf("%d", &choice);
        switch (choice) {
        case 6:
            printf("Good bye!");
            teardown(users);
            return 0;
            break;
        case 1:
            printf("Enter your username\n");
            scanf("%s", new_username);
            printf("Enter an upto 15 characters password\n");
            scanf("%s", new_password);
            users = add_user(users,new_username,new_password);
            printf("user added! \n");
            break;
        case 2:
            printf("Enter a username to update a password\n");
            scanf("%s",username_to_update);
            currentUser = find_user(users,username_to_update);
            if (currentUser == NULL){
                printf("Invalid User. Please try again\n");
                break;
            }
            printf("Enter the password\n");
            scanf("%s", old_password);
            if (strcmp(currentUser->password,old_password)!=0){
                printf("Incorrect password entered\n");
            } else {
                printf("Enter a new password upto 15 characters \n");
                scanf("%s",new_password);
                strcpy(currentUser->password,new_password);
                printf("Password changed! \n");
            }
            break;
        case 3:
            printf("Enter a username you want to manage a post\n");
            scanf("%s",username_to_manage_post);
            user_t *curr = find_user(users, username_to_manage_post);
            if (curr == NULL){
                printf("Invalid User");
                break;
            }
            printf("*************************\n      Managing %s posts\n*************************\n", curr->username);
            if (curr->posts == NULL) {
                printf("No post available for %s \n", curr->username);
            }
            printf("1. Add a new Post\n 2. Remove a Post\n 3. Return to main menu\n Enter your choice: \n");
            int user_choice_post;
            scanf("%d", &user_choice_post);
            while (getchar() != '\n');
            if (user_choice_post == 1) {
                printf("please enter a post upto 250 characters\n");
                fgets(new_post, sizeof(new_post), stdin);
                add_post(curr, new_post);
                display_all_user_posts(curr);
            }
            else if (user_choice_post==2) {
                if (curr->posts==NULL) {
                    printf("No post to delete\n");
                }
                if(delete_post(curr)){
                    printf("Post deleted\n");
                    display_all_user_posts(curr);
                } else {
                    printf("Post couldn't be deleted (failed) \n");
                }
            }
            else if (user_choice_post==3){
                break;
            } else {
                printf("Invalid choice! Please enter again \n");
            }
            break;
        case 4:
            printf("Enter a username to update their friends\n");
            scanf("%s",username_to_update_friends);
            user_t *current_ = find_user(users, username_to_update_friends);
            if (current_ == NULL){
                printf("Invalid User");
                break;
            }
            printf("*************************\n            Managing %s friends\n*************************\n", current_->username);
            if (current_->friends == NULL) {
                printf("No friends available for %s \n", current_->username);
            }
            printf("1. Add a new friend\n 2. Remove a friend\n 3. Return to main menu\n Enter your choice: \n");
            int user_choice_to_update_friends;
            scanf("%d",&user_choice_to_update_friends);
            if (user_choice_to_update_friends==1){
                printf("please enter friends name\n");
                scanf("%s", friend_name);
                add_friend(current_,friend_name);
            } 
            else if (user_choice_to_update_friends == 2) {
                if (current_->friends==NULL) {
                    printf("No friends to delete\n");
                    break;
                }
                display_user_friends(current_);
                printf("Enter a friends name to delete \n");
                scanf("%s", friend_name_to_delete);
                if(delete_friend(current_, friend_name_to_delete)){
                    printf("updated list of %s friends",current_->username);
                    display_user_friends(current_);
                    break;
                } else {
                    printf("Invalid friend name (failed) \n");
                    break;
                }
                break;
            } else if (user_choice_to_update_friends == 3) {
                break;
            } else {
                printf("invalid choice! \n");
            } 
            break;
        case 5:
            printf("Enter the username to display their post \n");
            scanf("%s", username_to_display_post);
            currentUser = find_user(users, username_to_display_post);
            if (currentUser == NULL) {
                printf("Invalid username! Enter again \n");
                break;
            }
            display_posts_by_n(currentUser, 3);
            break;        
        default:
            printf("Invalid Choice. Please try again.");
            break;
        }
        
    } while ( choice != 6);
}