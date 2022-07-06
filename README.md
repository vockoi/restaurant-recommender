# Restaurant Recommender

C program which recommends restaurants for customers to visit on the basis of user-based and content-based similarities, given a list of restaurant records and dining transactions.

## Table of contents
* [Program description](#program-description)
* [Program input](#program-input)
* [Running the program](#running-the-program)
* [Credits](#credits)

## Program description

The program consists of four 'stages' with the following functionalities:

1. **Stage 1**: Shows the number of restaurants in the restaurant records, and shows the restaurant with the smallest price per head
2. **Stage 2**: Shows a restaurant-visiting matrix, where each row is a customer's restaurant-visiting records
3. **Stage 3**: Shows a matrix recommending restaurants a customer may want to visit next time based on restaurant similarities (**content-based** recommendation).
4. **Stage 4**: Shows a matrix recommending restaurants a customer may want to visit next time based on customer similarities (**user-based** collaborative filtering).

### Matrix representations

I strongly recommend viewing the sample program output and input while reading along this section and the 'Program input' section. To do so, access the __ folder. 

- The *i*-th column of each matrix represents customers' visiting records to the i-th restaurant in the restaurant records
- Each **positive** integer represents the amount of times a restaurant has been visited by a customer.
- Each non-numeric **symbol** represents how much a restaurant is recommended to a customer. Values '-', '+', and '\*' denote values -1, -2, and -3, respectively. The more negative the value, the more the restaurant is recommended to the user.

## Program input

Input the program accepts consists of 'restaurant records' and 'dining records' in the following format.

The input starts with a list of at least 1 and up to 99 **restaurant records** sorted by the restaurant IDs (e.g., ABNs) in ascending order. Each restaurant record takes one line with the following six fields:
- The restaurant ID, a unique 6-digit integer.
- The x-coordinate of the restaurant, a real number.
- The y-coordinate of the restaurant, a real number. For simplicity, all x- and y-coordinates have been normalised into the range of (0, 100).
- The average price per head, an integer.
- The cuisine type, a string of at least 1 and up to 20 lower-case letters.
- The restaurant name, a string of at least 1 and up to 100 (lower-case letters or `_') characters.

The restaurant records ends with a line of five `#'s which serves as a separator line. 

Then input continues with **dining records** containing at least 1 dining transaction(s) sorted in ascending order of the transaction time. Each dining transaction takes one line with the following four fields:
- The transaction date and time, which uses the following format: Year:Month:Day:Hour:Minute:Second.
- The customer ID, a string of 6 lower-case letters (each unique ID represents a different customer).
- The restaurant ID, a 6-digit integer (and is in the restaurant records).
- The transaction amount, an integer.

## Running the program



## Credits

- The COMP10002 teaching team, which includes lecturers Jianzhong Qi and Shaanan Cohney in particular, came up with the specifications found in the sections 'Program description' and 'Program input'. I just did the code to implement these specifications.
- The program utilizes a C file of linked list operations implemented by Alistair Moffat in his book "Programming, Problem Solving and Abstraction with C" (2013).
