# PrefexTree
## Task for Pro

### Task:   
Create a programme that uses any text file with random content as an input,   
and checks all the words contained in such text file for letter combinations   
consisting of more than 3 letters.  
   
Programme output will consist in up to 10 most common letter combinations and   
their difference in percentage displayed as a table and a bar chart.  
  
### Sample solution  
The content of the input file:
'''
"hall feels heels"
'''

### Output:  
> Frequencies:  
> eels: 28.57%  
> feel: 14.29%  
> heel: 14.29%  
> hall: 14.29%  
> feels: 14.29%  
> heels: 14.29%  

 ------------------------------  

### Simple solution  (implemented in code)
* Use a map to collect all "long" word - shortMap
* For-each word from shortMap generate "short" words and store in an extended map.  
* Copy items from an extended map to the vector
* Sort the vector and print out top N items.

### Complicated solution   (NOT implemented in code, only text algorithm)
Use new data structure - combine Trie and Min Heap to get the N most frequent words efficiently.  
The idea is to use Trie for searching existing words adding new words efficiently.  
Trie also stores count of occurrences of words. 
A Min Heap of size N is used to keep track of N most frequent words at any point of time.  

Trie and Min Heap are linked with each other by storing an additional field in Trie ‘indexMinHeap’  
and a pointer ‘trNode’ in Min Heap. The value of ‘indexMinHeap’ is maintained as -1 for the words   
which are currently not in Min Heap (or currently not among the top N frequent words).  
For the words which are present in Min Heap, ‘indexMinHeap’ contains, index of the word in Min Heap. 
The pointer ‘trNode’ in Min Heap points to the leaf node corresponding to the word in Trie.

* Read all words one by one. For every word, insert it into shortTrie. Increase the counter of the word, if already exists. 
* For-each word from shortTrie generate "short" words and insert in a extendedeTrie, and update Min Heap. 
For insertion in min heap, 3 cases arise: 
1. The word is already present. We just increase the corresponding frequency value in min heap and call minHeapify() for the index obtained by “indexMinHeap” field in Trie. When the min heap nodes are being swapped, we change the corresponding minHeapIndex in the Trie. Remember each node of the min heap is also having pointer to Trie leaf node.
2. The minHeap is not full. We will insert the new word into min heap & update the root node in the min heap node & min heap index in Trie leaf node. Now, call buildMinHeap().
3. The min heap is full. Two sub-cases arise:
 3.1 The frequency of the new word inserted is less than the frequency of the word stored in the head of min heap. Do nothing.
 3.2 The frequency of the new word inserted is greater than the frequency of the word stored in the head of min heap. Replace & update the fields. Make sure to update the corresponding min heap index of the “word to be replaced” in Trie with -1 as the word is no longer in min heap.
4. Finally, Min Heap will have the N most frequent words of all words generated from shortTrie. So we just need to print all words present in Min Heap.

 ------------------------------  
### Generate word function  
* For input 'colorfull' :
> Word source is : colorfull : new word colo  
> Word source is : colorfull : new word olor  
> Word source is : colorfull : new word lorf  
> Word source is : colorfull : new word orfu  
> Word source is : colorfull : new word rful  
> Word source is : colorfull : new word full  
> Word source is : colorfull : new word color  
> Word source is : colorfull : new word olorf  
> Word source is : colorfull : new word lorfu  
> Word source is : colorfull : new word orful  
> Word source is : colorfull : new word rfull  
> Word source is : colorfull : new word colorf  
> Word source is : colorfull : new word olorfu  
> Word source is : colorfull : new word lorful  
> Word source is : colorfull : new word orfull  
> Word source is : colorfull : new word colorfu  
> Word source is : colorfull : new word olorful  
> Word source is : colorfull : new word lorfull  
> Word source is : colorfull : new word colorful  
> Word source is : colorfull : new word olorfull  
> Word source is : colorfull : new word colorfull   

For input 'settings' :  
> Word source is : settings : new word sett  
> Word source is : settings : new word etti  
> Word source is : settings : new word ttin  
> Word source is : settings : new word ting  
> Word source is : settings : new word ings  
> Word source is : settings : new word setti  
> Word source is : settings : new word ettin  
> Word source is : settings : new word tting  
> Word source is : settings : new word tings  
> Word source is : settings : new word settin  
> Word source is : settings : new word etting  
> Word source is : settings : new word ttings  
> Word source is : settings : new word setting  
> Word source is : settings : new word ettings  
> Word source is : settings : new word settings  
  
