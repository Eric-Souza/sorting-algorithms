# sorting-algorithms
Receives a text file and two integers as input by a makefile command and sorts its data following specified algorithms, using data structures concepts. The input text files have names (strings) and binary digits (integers), both must be sorted. The input's first integer represents which sorting algorithms'll be used to sort the names and binary digits, respectively. The second integer specifies quantity of lines to be sorted. At last, the system prints the resulting sorted array. This system was developed as a Data Structures subject exercise (UFMG).
  
- Config 1: names by quicksort and digits by heapsort.
- Config 2: names by quicksort and digits by radixsort.
- Config 3: names by mergesort and digits by heapsort.
- Config 4: names by mergesort and digits by radixsort.

* Compile the code by running the command below on the Makefile directory:  

```{bash}  
make  
```  

* The "make" command will create the "run.out" file in the "bin" folder, which can be used to execute the app. To print the chosen input text data, run the command below in the "bin" folder:  

```{bash}  
run.out ../inputs/text-file-name.txt config-integer quantity-of-data-to-be-sorted-integer 
```  

