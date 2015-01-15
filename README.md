Client-Server Modelling
=========================

<h1> Description </h1>

Program simulates interaction between server and clients (n <= 10). Server process abstract transactions from clients. Server and clients run in separate threads. Data from clients inserts to priority queue. Server pop that data from queue and write record to log file.

System structure:
```
+------------+      +-----------+      +------------+
|            |      |           |      |            |
|   Server   <------+   Queue   <------+   Client   |
|            |      |           |      |            |
+------+-----+      |           |      +------------+
       |            |           |                    
       |            |           |      +------------+
+------v-----+      |           |      |            |
|  log file  |      |           <------+   Client   |
+------------+      |           |      |            |
                    |           |      +------------+
                    |           |                    
                    |           |      +------------+
                    |           |      |            |
                    |           <------+   Client   |
                    |           |      |            |
                    +-----------+      +------------+
```

<h1> Structure of Input Request </h1>

```
typedef struct tagTDATA
{
    // Priority of request 0-255 (0 - highest priority)
    BYTE cPriority;
    // Request's creation time in system clock ticks
    DWORD dwTicks;
    // Unique client ID
    DWORD dwClientId;
    // Abstract data
    char data[Constants::MAX_DATA_SIZE];
} TDATA, *PTDATA;
```
