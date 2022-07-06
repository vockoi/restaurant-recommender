# Restaurant Recommender

The program consists of four 'stages' with different functionalities:
1. **Stage 1** - Shows the number of restaurants in the restaurant records and the restaurant with the smallest price per head
2. **Stage 2** - Shows a matrix where each row is the restaurant visiting record of a customer. The *i*-th numeric column represent customers' visiting records to the *i*-th restaurant in the array of restaurants.
3. **Stage 3** - Shows a matrix recommending restaurants a customer may want to visit next time based on restaurant similarities (**content-based recommendation**).
4. **Stage 4** - Shows a matrix recommending restaurants a customer may want to visit next time based on customer similarities (**user-based collaborative filtering**).

## Input

Input the program accepts consists of a list of restaurant records and a list of dining transactions in the following format.

The input starts with a list of at least 1 and up to 99 **restaurant records** sorted by the restaurant IDs (e.g., ABNs) in ascending order. Each restaurant record takes one line with the following six fields:
- The restaurant ID, a unique 6-digit integer.
- The x-coordinate of the restaurant, a real number.
- The y-coordinate of the restaurant, a real number. For simplicity, all x- and y-coordinates have been normalised into the range of (0, 100).
- The average price per head, an integer.
- The cuisine type, a string of at least 1 and up to 20 lower-case letters.
- The restaurant name, a string of at least 1 and up to 100 (lower-case letters or `_') characters.

The list of restaurant records ends with a line of five `#'s which serves as a separator line. 

Then input continues with **dining records** containing at least 1 dining transaction(s) sorted in ascending order of the (unique) transaction time. Each dining transaction takes one line with the following four fields:
- The transaction date and time, which uses the following format: Year:Month:Day:Hour:Minute:Second.
- The customer ID, a string of 6 lower-case letters (each unique ID represents a different customer).
- The restaurant ID, a 6-digit integer (and is in the restaurant records).
- The transaction amount, an integer.

There should be at least 3 unique customer IDs in the list of dining transactions.

To view sample program input and output, access the __ folder.
