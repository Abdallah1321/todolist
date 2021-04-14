#include "databasemanagement.h"
/*DatabaseManagement::DatabaseManagement()
{
    filename = nullptr; //file is null
}*/
DatabaseManagement::DatabaseManagement(const char* filename)
{
    //this->filename = filename;
    not_connected = sqlite3_open(filename, &db);

    if( not_connected ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    sqlite3_close(db);

    /*
    this is a pointer, arrow is used to dereference, helps assign the variable of same name to itself
    */
}
DatabaseManagement::~DatabaseManagement(){}

/*int createDB(const char* s)
{
    sqlite3* db;
    int exit = 0;
    exit = sqlite3_open(s, &db);

    sqlite3_close(db);
}

*/
string quotesql( const string& s ) {
    return string("'") + s + string("'");
}
/*int DatabaseManagement::connect()
{
    not_connected = sqlite3_open(filename, &db);

    if( not_connected ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    sqlite3_close(db);

    return(0);
}*/

void DatabaseManagement::deleteData()
{
    //connect();
    string sql3 = "DELETE FROM TODO";

    sqlite3* db;
    try
    {
        int exit = 0;
        exit = sqlite3_open("todolist.db", &db);

        char* messageError;
        exit = sqlite3_exec(db, sql3.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error Delete" << endl;
            sqlite3_free(messageError);
        } else
        {
            cout << "Delete Successful" << endl;
        }
        sqlite3_close(db);
    } catch (const exception & e)
    {
        cerr << e.what();
    }
}

void DatabaseManagement::insertData() {
    //connect();


    /*string task = "hello true 1";


    Item item(task);
    list.push_back(item);
    */
    deleteData();


    /*string sql3 = "DELETE FROM TODO";

    sqlite3* db;
    try
    {
        int exit = 0;
        exit = sqlite3_open("todolist.db", &db);

        char* messageError;
        exit = sqlite3_exec(db, sql3.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error Delete" << endl;
            sqlite3_free(messageError);
        } else
        {
            cout << "Delete Successful" << endl;
        }
        sqlite3_close(db);
    } catch (const exception & e)
    {
        cerr << e.what();
    }*/

        //connect();

        /*string task = "hello true 1";

        Item item(task);
        list.push_back(item);*/

    int insert = 0;
    for (Item item : list)
    {
        if (item.text().empty()) continue;
        else insert++;
        sql2 = "INSERT INTO TODO (ID, TASK,STATUS,PRIORITY) VALUES (" + quotesql(to_string(insert)) + "," + quotesql(item.text()) + "," + quotesql((item.is_done() ? "true" : "false")) + "," + quotesql(item.priority()) + ");";
        try
        {
            int exit = 0;
            exit = sqlite3_open("todolist.db", &db);

            char* messageError;
            exit = sqlite3_exec(db, sql2.c_str(), NULL, 0, &messageError);

            if (exit != SQLITE_OK)
            {
                cerr << "Error Insert" << endl;
                sqlite3_free(messageError);
            } else
            {
                cout << "Insert Successful" << endl;
            }
            sqlite3_close(db);
        } catch (const exception & e)
        {
            cerr << e.what();
        }
    }
}

void DatabaseManagement::selectData()
{
    sqlite3 *db;
    sqlite3_stmt * stmt;


    if (sqlite3_open("todolist.db", &db) == SQLITE_OK)
    {
        sqlite3_prepare( db, "SELECT * from TODO;", -1, &stmt, NULL );//preparing the statement
        sqlite3_step( stmt );//executing the statement
        char * str = (char *) sqlite3_column_text( stmt, 0 ); //reading the 1st column of the result
    }
    else
    {
        cout << "Failed to open db\n";
    }

    string line = "";
    list.clear();
    while( sqlite3_column_text( stmt, 0 ) )
    {
        string line ="";
        for( int i = 1; i < 4; i++ )
        {
            line += std::string( (char *)sqlite3_column_text( stmt, i ));
            line += " ";
        }
        sqlite3_step( stmt );
        Item item(line);
        list.push_back(line);

    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}




/*int DatabaseManagement::selectData(DatabaseManagement s)
{
    sqlite3* db;
    int exit = sqlite3_open("todolist.db", &db);

    string sql = "SELECT * FROM TODO";

    *//*
     * An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here
     *//*
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), DatabaseManagement::callback, &s, &messageError);

    if (exit != SQLITE_OK)
    {
        cerr << "Error Select" << endl;
        sqlite3_free(messageError);
    } else
    {
        cout << "Records read Successfully" << endl;

    }
    return 0;
}*/

/*int DatabaseManagement::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << argv[i] << endl;
    }
    cout << endl;
    return 0;
}*/

/*void DatabaseManagement::selectData(DatabaseManagement s) {
    sqlite3_open(filename, &db);

    string sql = "SELECT * FROM TODO;";

    *//*
     * An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here
     *//*

    int exit = sqlite3_exec(db, sql.c_str(), DatabaseManagement::callback, NULL, &ErrorMessage);

    if (exit != SQLITE_OK) {
        cerr << "Error Select" << endl;
        sqlite3_free(ErrorMessage);
    } else {
        cout << "Records read Successfully" << endl;
    }

    sqlite3_close(db);
}*/

//this link on stackoverflow said to do that so i did
// https://stackoverflow.com/questions/54848606/how-to-make-a-non-static-callback-in-c-for-sqlite
/*
 * retreive contents of database used by selectData()
 * arc: holds the number of results,
 * azColName: eholds each column returned in array
 * argv: holds each value in array
 */
/*int DatabaseManagement::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    return ((DatabaseManagement *)NotUsed)->callbackAux(argc, argv, azColName);
}

int DatabaseManagement::callbackAux(int argc, char ** argv, char ** azColName) {
    int i;
    string line;
    //list.clear();
    for (i = 1; i < argc; i++) {
        // column name and value
        line += argv[i];
        line += " ";
        //if (line.empty()) continue; //if it encounters an empty line skip iteration
    }
    Item item(line); //makes line an instance of class item (similar to type casting)
    list.push_back(item); //adds to list vector
    cout<<"item inserted"<<endl;
    cout<<list.size();
    return 0;
}*/



/*int DatabaseManagement::callback(void *s, int argc, char **argv, char **azColName) {
    return ((DatabaseManagement *) s)->callbackAux(argc, argv, azColName);
}

int DatabaseManagement::callbackAux(int argc, char **argv, char **azColName) {
    int i;
    string line;
    list.clear();
    for (i = 1; i < argc; i++) {
        // column name and value
        line += argv[i];
        line += " ";
        if (line.empty()) continue; //if it encounters an empty line skip iteration
        Item item(line); //makes line an instance of class item (similar to type casting)
        list.push_back(item); //adds to list vector

    }
    return 0;
}*/


//this function works generally so if you wanna use that for edit then you can
/*
void DatabaseManagement::updateData(int s, const string& edit)
{
    int exit = sqlite3_open(filename, &db);

    string sql = "UPDATE TODO SET TASK =" + quotesql(edit) + "WHERE ID =" + quotesql(to_string(s)) + ");";

    sqlite3_exec(db, sql.c_str(), NULL, 0, &ErrorMessage);

    if (exit != SQLITE_OK)
    {
        cerr << "Error Insert" << endl;
        sqlite3_free(ErrorMessage);
    } else
    {
        cout << "Records updated Successfully" << endl;
    }
}
*/

