#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// The maximum number of records our database can hold
#define MAX_RECORDS 100

typedef struct {
    int account_number;
    char name[50];
    float balance;
    char address[100];
    char password[100];
} database_record;


typedef struct {
    database_record records[MAX_RECORDS];
    size_t count; 
} database;


int create_account_number() {
    return rand();
}

database create_database(char *filename) {
    database db;
    db.count = 0; // Start with an empty database in memory

    FILE *file = fopen(filename, "wb"); // Open for write-binary
    if (file == NULL) {
        perror("Failed to create database file");
        exit(EXIT_FAILURE);
    }

    // --- Record 1: John Doe ---
    database_record record1;
    record1.account_number = create_account_number();
    strcpy(record1.name, "John Doe");
    record1.balance = 1000.0;
    strcpy(record1.address, "123 Main St, Anytown, USA");
    strcpy(record1.password, "securepassword");
    db.records[db.count++] = record1; // Add to our in-memory db

    // --- Record 2: Jane Smith ---
    database_record record2;
    record2.account_number = create_account_number();
    strcpy(record2.name, "Jane Smith");
    record2.balance = 500.0;
    strcpy(record2.address, "456 Oak St, Othertown, USA");
    strcpy(record2.password, "anotherpassword");
    db.records[db.count++] = record2; // Add to our in-memory db

    size_t written_count = fwrite(db.records, sizeof(database_record), db.count, file);
    
    if (written_count == db.count) {
        printf("Database file created successfully with %zu records.\n", written_count);
    } else {
        printf("Error: Only %zu of %zu records were written.\n", written_count, db.count);
    }

    fclose(file); 
    return db;
}

database read_database(FILE *file) {
    database db;
    db.count = 0; 
    if (file == NULL) {
        perror("read_database received a NULL file pointer");
        return db;
    }
    db.count = fread(db.records, sizeof(database_record), MAX_RECORDS, file);

    if (ferror(file)) {
        perror("Error reading from database file");
        db.count = 0;
    }
    
    return db;
}

void print_record(database_record record) {
    printf("\n--- Record ---\n");
    printf("Account Number: %d\n", record.account_number);
    printf("Name:           %s\n", record.name);
    printf("Balance:        %.2f\n", record.balance);
    printf("Address:        %s\n", record.address);
    printf("--- End of record ---\n");
}

void print_database(database db) { 
    printf("--- Reading %zu record(s) from database ---\n", db.count);
    if (db.count == 0) {
        printf("Database is empty or could not be read.\n");
    }

    for (size_t i = 0; i < db.count; i++) {
        database_record record = db.records[i];
        print_record(record);
    }
    printf("--- End of database ---\n");
}


void create_new_record(database *db) {
    if (db->count >= MAX_RECORDS) {
        printf("Database is full. Cannot add more records.\n");
        return;
    }

    database_record new_record;
    new_record.account_number = create_account_number();

    printf("Enter name: ");
    fgets(new_record.name, sizeof(new_record.name), stdin);
    new_record.name[strcspn(new_record.name, "\n")] = 0; // Remove newline

    printf("Enter balance: ");
    scanf("%f", &new_record.balance);
    getchar(); // Consume leftover newline

    printf("Enter address: ");
    fgets(new_record.address, sizeof(new_record.address), stdin);
    new_record.address[strcspn(new_record.address, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(new_record.password, sizeof(new_record.password), stdin);
    new_record.password[strcspn(new_record.password, "\n")] = 0; // Remove newline

    db->records[db->count++] = new_record;
    printf("New record added successfully.\n");
    print_record(new_record);
}

void save_database(database db, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open database file for writing");
        return;
    }
    size_t written_count = fwrite(db.records, sizeof(database_record), db.count, file);
    if (written_count != db.count) {
        printf("Error: Only %zu of %zu records were written.\n", written_count, db.count);
    } else {
        printf("Database saved successfully with %zu records.\n", written_count);
    }
    fclose(file);
}

void check_account_balance(database db, int account_number) {
    for (size_t i = 0; i < db.count; i++) {
        if (db.records[i].account_number == account_number) {
            printf("Account found. Balance: %.2f\n", db.records[i].balance);
            return;
        }
    }
    printf("Account number %d not found in database.\n", account_number);
}

void transfer_funds(database *db, int from_account, int to_account, float amount) {
    database_record *from_record = NULL;
    database_record *to_record = NULL;

    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].account_number == from_account) {
            from_record = &db->records[i];
        }
        if (db->records[i].account_number == to_account) {
            to_record = &db->records[i];
        }
    }

    if (from_record == NULL) {
        printf("From account number %d not found.\n", from_account);
        return;
    }
    if (to_record == NULL) {
        printf("To account number %d not found.\n", to_account);
        return;
    }
    if (from_record->balance < amount) {
        printf("Insufficient funds in account number %d.\n", from_account);
        return;
    }

    from_record->balance -= amount;
    to_record->balance += amount;
    printf("Transferred %.2f from account %d to account %d successfully.\n", amount, from_account, to_account);
}

int main() {
    char *filename = "database.bin";
    srand(time(NULL));
    database db;
    FILE *file = fopen(filename, "rb"); 
    if (file != NULL) {
        printf("Database file '%s' already exists.\n", filename);
        db = read_database(file);
        fclose(file);
    } else {
        printf("Database file '%s' not found. Creating new database...\n", filename);
        db = create_database(filename);
    }
    print_database(db);
    // create_new_record(&db);
    save_database(db, filename);
    check_account_balance(db, 2058273749); // Example account number to check
    transfer_funds(&db, db.records[0].account_number, db.records[1].account_number, 100.0); // Example transfer
    save_database(db, filename);
    print_database(db);
    // print_database(db);

    return 0;
}
