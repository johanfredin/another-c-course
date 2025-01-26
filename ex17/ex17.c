#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

typedef struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
} Address;

typedef struct Database {
	Address rows[MAX_ROWS];
} Database;

typedef struct Connection {
	FILE *file;
	Database *db;
} Connection;

void die(const char *message) {
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

void Address_print(const Address *addr) { printf("%d %s %s\n", addr->id, addr->name, addr->email); }

void Database_load(Connection *conn) {
	unsigned long rc = fread(conn->db, sizeof(Database), 1, conn->file);
	if (rc != 1) {
		die("Failed to load the database.");
	}
}

Connection *Database_open(const char *filename, const char mode) {
	Connection *conn = malloc(sizeof(Connection));
	if (!conn) {
		die("Memory error");
	}

	conn->db = malloc(sizeof(Database));
	if (!conn->db) {
		die("Memory error");
	}

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");

		if (conn->file) {
			Database_load(conn);
		}
	}

	if (!conn->file) {
		die("Failed to open the file");
	}

	return conn;
}

void Database_write(const Connection *conn) {
	rewind(conn->file);

	unsigned long rc = fwrite(conn->db, sizeof(Database), 1, conn->file);
	if (rc != 1) {
		die("Failed to write database");
	}

	rc = fflush(conn->file);
	if (rc == -1) {
		die("Could not flush database");
	}
}

void Database_create(const Connection *conn) {
	for (int i = 0; i < MAX_ROWS; i++) {
		// Make a prototype to initialize it
		// Then just assign it
		conn->db->rows[i] = (Address){.id = i, .set = 0};
	}
}

void Database_get(const Connection *conn, const int id) {
	Address address = conn->db->rows[id];
	if (address.set) {
		Address_print(&address);
	} else {
		die("ID not set");
	}
}

void Database_set(const Connection *conn, const int id, const char *name, const char *email) {
	Address *addr = &conn->db->rows[id];
	if (addr->set) {
		die("Already set, delete it first");
	}
	int res = strlcpy(addr->name, name, MAX_DATA);
	
	// demonstrate the strncpy bug
	if (!res) {
		die("name copy failed");
	}

	res = strlcpy(addr->email, email, MAX_DATA);
	if (!res) {
		die("email copy failed");
	}
}

void Database_delete(const Connection *conn, const int id) {
	conn->db->rows[id] = (Address){.id = id, .set=0};
}

void Database_list(const Connection *conn) {
	Database *db = conn->db;
	for (int i = 0; i < MAX_ROWS; i++) {
		Address *curr = &db->rows[i];
		if (curr->set) {
			Address_print(curr);
		}
	}
}

void Database_close(const Connection *conn) {
	if (conn) {
		if (conn->file) {
			fclose(conn->file);
		}
		if (conn->db) {
			free(conn->db);
		}
		free((Connection *) conn);
	}
}

int main(int argc, char **argv) {
	if (argc < 3) {
		die("USAGE: ex17 <dbfile> <action> [action params]");
	}

	const char *filename = argv[1];
	const char action = argv[2][0];

	const Connection *conn = Database_open(filename, action);
	int id = 0;

	if (argc > 3) {
		id = atoi(argv[3]);
	}
	if (id > MAX_ROWS) {
		die("There's not that many records");
	}

	switch (action) {
		case 'c':
			Database_create(conn);
			Database_write(conn);
			break;

		case 'g':
			if (argc != 4) {
				die("Need an id to get");
			}

			Database_get(conn, id);
			break;
		
		case 's':
			if (argc != 6) {
				die("Need id name, email to set");
			}

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		
		case 'd':
			if (argc != 4) {
				die("Need an id to delete");
			}

			Database_delete(conn, id);
			Database_write(conn);
			break;
		
		case 'l':
			Database_list(conn);
			break;
		
		default:
			die("Invalid action: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close(conn);

	return 0;
}