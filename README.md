# Restaurant Recommender

C program which recommends restaurants for customers to visit on the basis of user-based and content-based similarities, given a list of restaurant records and dining transactions.

## Table of contents
* [Program description](#program-description)
* [Program input](#program-input)
* [Running the program](#running-the-program)

## Program Description

To view sample program input and output, access the __ folder. 

The program consists of four 'stages' with the following functionalities:

### Stage 1
- Shows the number of restaurants in the restaurant records
- Shows restaurant with the smallest price per head
### Stage 2
- Shows a restaurant-visiting matrix, where each row is the restaurant visiting record of a customer
- The *i*-th column of the matrix represents customers' visiting records to the i-th restaurant in the restaurant records
- Each integer represents the amount of times a restaurant has been visited by a customer
### Stage 3 
- Shows a matrix recommending restaurants a customer may want to visit next time based on restaurant similarities (**content-based** recommendation).
### Stage 4
- Shows a matrix recommending restaurants a customer may want to visit next time based on customer similarities (**user-based** collaborative filtering).

### Matrix representation

For stage 3 and 4, values '-', '+', and '*' in the matrix denote values -1, -2, and -3, respectively. The more negative the value, the more the restaurant is recommended.

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
