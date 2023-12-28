# How to test ? 

## 1 - Run the program
````
make
````

````
./bin/main/
````

## 2 - Get the program PID

````
ps aux | grep main
````

## 3 - Send signals

````
kill -SIGINT [PID]
````
````
kill -SIGTERM [PID]
````