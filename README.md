# Restaurant Recommender

C program which recommends restaurants for customers to visit on the basis of user-based and content-based similarities, given a list of restaurant records and dining transactions.

## Table of contents
* [Program input](#program-input)
* [Program output](#program-output)
* [Running the program](#running-the-program)
* [Credits](#credits)

## Program input

I strongly recommend viewing the sample program input as you read along this section. To do so, access the __ folder. 

Input the program accepts is a .txt file consisting of two sections - 'restaurant records' and 'dining records', in the following format. The specifics of the input (e.g. length of restaurant ID) can be easily modified by changing the #defines at the top of the program.

### Restaurant records

The input starts with 1 to 99 restaurant records, sorted by the restaurant IDs in ascending order. Each record takes one line with the following six fields:
- The restaurant ID, a unique 6-digit integer.
- The x-coordinate of the restaurant, a real number.
- The y-coordinate of the restaurant, a real number. For simplicity, all x- and y-coordinates have been normalised into the range of (0, 100).
- The average price per head, an integer.
- The cuisine type, a string of at least 1 and up to 20 lower-case letters.
- The restaurant name, a string of at least 1 and up to 100 (lower-case letters or '_') characters.

The restaurant records ends with a line of five '#'s which serves as a separator line. 

### Dining records

The input continues with dining records containing at least 1 dining transaction(s), sorted in ascending order of the transaction time. Each dining transaction takes one line with the following four fields:
- The transaction date and time, which uses the following format: Year:Month:Day:Hour:Minute:Second.
- The customer ID, a string of 6 lower-case letters (each unique ID represents a different customer).
- The restaurant ID, a 6-digit integer (and is in the restaurant records).
- The transaction amount, an integer.

## Program output

I strongly recommend viewing the sample program output as you read along this section. To do so, access the __ folder. 

The program output consists of the following four 'stages':

- **Stage 1**: Shows the number of restaurants in the restaurant records, and shows the restaurant with the smallest price per head
- **Stage 2**: Shows a restaurant-visiting matrix, where each row is a customer's restaurant-visiting records
- **Stage 3**: Shows a matrix recommending restaurants a customer may want to visit next time based on restaurant similarities (**content-based** recommendation).
- **Stage 4**: Shows a matrix recommending restaurants a customer may want to visit next time based on customer similarities (**user-based** collaborative filtering).

### Matrix representations

- The *i*-th column of each matrix represents customers' visiting records to the i-th restaurant in the restaurant records
- Each **positive** integer represents the amount of times a restaurant has been visited by a customer.
- Each non-numeric **symbol** represents how much a restaurant is recommended to a customer. Values '-', '+', and '\*' denote values -1, -2, and -3, respectively. The more negative the value, the more the restaurant is recommended to the user.

## Running the program

To run the program, first compile 'program.c' which can be found in the folder 'program'; this should produce an executable file called 'program'. Use input redirection to provide your chosen restaurant and dining records file as input to the executable.

For example in Apple terminal: ```program < input_file.txt```

## Credits

- The COMP10002 teaching team, which includes lecturers Jianzhong Qi and Shaanan Cohney in particular, came up with the specifications found in the sections 'Program description' and 'Program input'. I just did the code to implement these specifications.
- The program utilizes a C file of linked list operations implemented by Alistair Moffat in his book "Programming, Problem Solving and Abstraction with C" (2013).
