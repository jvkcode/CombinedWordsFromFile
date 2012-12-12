//
//  main.c
//  CombinedWords
//
//  reads a file containing a sorted list of words (one
//  word per line, no spaces, all lower case), then identifies the longest
//  word in the file that can be constructed by concatenating copies of
//  shorter words also found in the file.
//
//  Created by Julia Karastoianova on 12/1/12.
//  Copyright open source
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <search.h>

#define MAX_LEN       1024  // limit of length of line from file
#define MIN_LEN_WORD     4  // min length of lexeme
#define MAX_LEN_WORD    50  // asuming max length of lexeme

#define NO_STEM         -1  // set flag to mark lexeme
#define IS_STEM          1  // set flag to mark lexeme
#define NOT_SET          0  // set flag to indicate unset
#define LEXEME_LIMIT     2  // how many combined words to print out

struct sorted_item // save info per word
{
    char key[MAX_LEN];    // stem of lexeme
    char word[MAX_LEN];   // suffix left after stem is found
    int w_len;            // suffix length
    int k_ind;            // index where to start search for new stem
    int searched;         // == NO_STEM IS_STEM NOT_SET;
    struct sorted_item *next;
};

// save sorted by length words
// or
// save one word to find if that is combined word
struct sorted_item_array
{
    struct sorted_item *stack;  // unit capasity
    size_t capacity;            // total capacity
};

// save all words from text file
struct page
{
    char key_word[MAX_LEN]; // save word from given file
    int len;                // length of the word
    int index;              // used to free memory only
    struct page *prev;
    struct page *a;
    struct page *b;
    struct page *c;
    struct page *d;
    struct page *e;
    struct page *f;
    struct page *g;
    struct page *h;
    struct page *i;
    struct page *j;
    struct page *k;
    struct page *l;
    struct page *m;
    struct page *n;
    struct page *o;
    struct page *p;
    struct page *q;
    struct page *r;
    struct page *s;
    struct page *t;
    struct page *u;
    struct page *v;
    struct page *w;
    struct page *x;
    struct page *y;
    struct page *z;
};

// function prototypes
int chomp_line(char *);
int init_sorted_item(struct sorted_item **);
int init_sorted_item_array(struct sorted_item_array *, size_t);
int resize_sorted_item_array(struct sorted_item_array *, size_t);
int init_page(struct page **);
struct page ** abc_given_node(struct page *, char);
void set_page(char *, int, struct page *);
int list_page(struct page **, struct page **, struct page *, int);
int add_to_page( char *, int, struct page *);
int save_words_by_length(char *, int, struct sorted_item_array *);
int extract_keys(struct sorted_item_array *, int, struct page *);
void print_out_lexeme(struct sorted_item_array *,int);
int set_first_word(struct sorted_item_array *, struct sorted_item **,
                   struct sorted_item_array *, int *);
int get_next_longest_word( struct sorted_item **, struct sorted_item_array *,
                          int *, struct sorted_item_array *);
int reset_index(int *, int, struct sorted_item_array *);
void free_sorted_item_array(struct sorted_item_array *, int);
void free_dict(struct page **);

// clean file line from blanks and \n
int chomp_line(char *l)
{
    int i = 0,j=0;
    
    //remove space(s) and end of the line
    for(i=0;l[i] != '\0';i++)
    {
        if(!isspace(l[i]) && l[i] != '\n' && l[i] != '\0')
        {
            l[j++] = l[i];
        }
    }
    l[j] = '\0';
    return j; // return length of the string
} // the end of int chomp_line(char *l)

// allocate memory for struct sorted_item
int init_sorted_item(struct sorted_item **n)
{
    // allocate clean memory
    if((*n = (struct sorted_item *)realloc(NULL,sizeof(struct sorted_item))) == NULL)
    {
        return 1; // if fail
    }
    return 0;
} // the end of int init_sorted_item(struct sorted_item **n)

// allocate memory for dynamic array with given size
int init_sorted_item_array(struct sorted_item_array *sia, size_t size)
{
    if(sia == NULL || size == 0)
    {
        return 1; // do nothing if input is wrong
    }
    // allocate clean memory
    if((sia->stack = realloc(NULL, size*sizeof(struct sorted_item))) == NULL)
    {
        return 1; // if fail
    }
    sia->capacity = size;
    return 0;
} // the end of // allocate memory for dynamic array with given size

// just in case if word length longer then MAX_LEN_WORD
// reset size of dynamic array x2
int resize_sorted_item_array(struct sorted_item_array *sia, size_t add_capacity)
{
    size_t new_capacity = 0;
    if(sia == NULL || add_capacity == 0)
    {
        return 1; // do nothing if input is wrong
    }
    new_capacity = sia->capacity + add_capacity;
    if((sia->stack = realloc(sia->stack,new_capacity*sizeof(struct sorted_item))) == NULL)
    {
        return 1;
    }
    sia->capacity = new_capacity;
    return 0;
} // the end of int resize_sorted_item_array(struct sorted_item_array *sia, size_t add_capacity)

// allocate memory for struct page
int init_page(struct page **p)
{
    // use realloc to have clean memory
    if((*p = (struct page *)realloc(NULL,sizeof(struct page))) == NULL)
    {
        return 1;
    }
    return 0;
} // the end of int init_page(struct page **p)

// return node according given char
struct page ** abc_given_node(struct page *curr, char c)
{
    if(curr == NULL)
    {
        return NULL;
    }
    switch (c)
    {
        case 'a' :
            return &(curr->a);
            break;
        case 'b' :
            return &(curr->b);
            break;
        case 'c' :
            return &(curr->c);
            break;
        case 'd' :
            return &(curr->d);
            break;
        case 'e' :
            return &(curr->e);
            break;
        case 'f' :
            return &(curr->f);
            break;
        case 'g' :
            return &(curr->g);
            break;
        case 'h' :
            return &(curr->h);
            break;
        case 'i' :
            return &(curr->i);
            break;
        case 'j' :
            return &(curr->j);
            break;
        case 'k' :
            return &(curr->k);
            break;
        case 'l' :
            return &(curr->l);
            break;
        case 'm' :
            return &(curr->m);
            break;
        case 'n' :
            return &(curr->n);
            break;
        case 'o' :
            return &(curr->o);
            break;
        case 'p' :
            return &(curr->p);
            break;
        case 'q' :
            return &(curr->q);
            break;
        case 'r' :
            return &(curr->r);
            break;
        case 's' :
            return &(curr->s);
            break;
        case 't' :
            return &(curr->t);
            break;
        case 'u' :
            return &(curr->u);
            break;
        case 'v' :
            return &(curr->v);
            break;
        case 'w' :
            return &(curr->w);
            break;
        case 'x' :
            return &(curr->x);
            break;
        case 'y' :
            return &(curr->y);
            break;
        case 'z' :
            return &(curr->z);
            break;
    }
    return NULL;
} // the end of struct page ** abc_given_node(struct page *curr, char c)

// save given values in page node
void set_page(char *w, int l, struct page *node)
{
    node->len = l;
    strcpy(node->key_word,w);
} // the end of void set_page(char *w, int l, struct page *node)

// save found word if that is the end of the word
// or move to next letter-page
int list_page(struct page **curr, struct page **letter, struct page *w, int end)
{
    if(*letter == NULL) // if given node is NULL
    {
        if(end) // and it is the end of the word
        {
            *letter = w; // save node at this end
            return end;  // exit function
        }
        init_page(letter); // if not the end of the word - create node
    }
    *curr = *letter; // asign curr to new node
    return end;
} // the end of int list_page(...)

// create new node with given word
// save found word in dict
int add_to_page( char *word, int len, struct page *dict_head)
{
    struct page *curr =  NULL;
    struct page *node = NULL;
    struct page **abc = NULL;
    int i = 0;
    
    if(word == NULL || len < 1 || dict_head == NULL)
    {
        return 1;                // exit if function args are wrong
    }
    curr = dict_head;            // start with the first page
    if(init_page(&node) != 0)    // create node for new word
    {
        return 1;                // exit if realloc gives NULL
    }
    set_page(word,len,node);     // save word in this node
    for(i=0;word[i] != '\0';i++) // per each word char find where to save this node
    {
        abc=abc_given_node(curr,word[i]);
        if(list_page(&curr,abc,node,(word[i+1]== '\0')?1:0))
        {
            break; // node is saved - exit loop
        }
    }
    return 0;
} // the end of int add_to_page(...)

// save a word to appropriate index == length of the word
int save_words_by_length(char *w, int len, struct sorted_item_array *s_words)
{
    struct sorted_item *word_info = NULL;
    
    // make sure dynamic array has that w_len index
    switch ((s_words->stack[len].w_len < s_words->capacity)?
            s_words->stack[len].w_len : s_words->capacity)
    {
        case 0: // init the first word if index is empty
            s_words->stack[len].w_len = len;
            if((s_words->stack[len].next= (struct sorted_item *) realloc(NULL,sizeof(struct sorted_item))) == NULL)
            {
                return 1; // realloc returns NULL
            }
            strcpy((s_words->stack[len].next)->word, w);
            break;
        case MAX_LEN_WORD*4 : // at this length of the word - check who is ku-ku
            printf("Fix this word: %s\nOr fix this code\n", w);
            return 1;
            break;
        case MAX_LEN_WORD*2 : // exceed size again - resized array
        case MAX_LEN_WORD : // exceed size of original array - resize it
            if(resize_sorted_item_array(s_words,s_words->capacity) != 0)
            {
                return 1; // realloc returns NULL
            }
        default: // add new word to list
            word_info=s_words->stack[len].next;
            if((s_words->stack[len].next= (struct sorted_item *) realloc(NULL,sizeof(struct sorted_item))) == NULL)
            {
                return 1; // realloc returns NULL
            }
            strcpy((s_words->stack[len].next)->word, w);
            s_words->stack[len].next->next = word_info;
            break;
    } // the end of switch len
    return 0;
} // the end of save_words_by_length(...)

// per given word extract all posible stems
// return index of longest stem
int extract_keys(struct sorted_item_array *lexeme, int index, struct page *dict_head)
{
    struct page **key = &dict_head; // set the top page of the dict
    int i = 0;                      // start with the first letter of the word
    int suffix = 2;                 // suffix cannot be 1 char but 2
    int diff = 0, ind_max = 0;      // calculate suffix and save longest stem index
    
    if(lexeme == NULL || dict_head == NULL)
    {
        return -1;
    }
    // for each letter in lexeme find stem/word in dictionary
    for(i=0;lexeme->stack[index].word[i] != '\0';i++)
    {
        key = abc_given_node(*key,lexeme->stack[index].word[i]); // get page with this letter
        if(*key == NULL)
        {
            break; // the end of this set of words
        }
        if((*key)->len == 0) // no stem/word yet found
        {
            continue;
        }
        // stem is found - save it if length is OK
        diff = lexeme->stack[index].w_len - (*key)->len;
        if(diff >= suffix || (index && diff == 0))
        {
            // skip marked index - we did searched it before
            if(lexeme->stack[index+(*key)->len].k_ind != NO_STEM)
            {
                ind_max = index+(*key)->len;
                lexeme->stack[ind_max].k_ind = ind_max;
                strcpy(lexeme->stack[ind_max].key,(*key)->key_word);
                lexeme->stack[ind_max].w_len = diff;
                strcpy(lexeme->stack[ind_max].word,&(lexeme->stack[0].word[ind_max]));
            }
            if(ind_max == lexeme->stack[0].w_len) // if found stem is the last one
            {
                break; // last stem for lexeme is found
            }
        } else if(diff < 0 || (index == 0 && diff< suffix))// found word is longer then given
        {
            break; // exit loop
        }
    } // the end of for(i=0;lexeme->stack[index].word[i] != '\0';i++)
    
    return (ind_max)?ind_max:index; // if ind_max was found return it; if not return given index
} // the end of int extract_keys(...)

// print word to stdout
void print_out_lexeme(struct sorted_item_array *lexeme,int last_ind)
{
    int i = 0;
    printf("%s :",lexeme->stack[0].word);          // print whole word == lexeme
    for(i=1;i <= last_ind;i++)                     // print each stem
    {
        if(lexeme->stack[i].searched == IS_STEM)
        {
            printf(" %s", lexeme->stack[i].key);
        }
    }
    printf(" %s\n", lexeme->stack[last_ind].word); // print the last stem == suffix
    fflush(stdout);
} // the end of void print_out_lexeme(...)

// get the first longest word from saved index list
int set_first_word(struct sorted_item_array *s_words, struct sorted_item **w_info,
                   struct sorted_item_array *lexeme, int *len)
{
    // if invalid values exit here
    if(s_words == NULL || lexeme == NULL || len == NULL)
    {
        return 1;
    }
    // find the first longest word index
    for(*len=(int)s_words->capacity-1; s_words->stack[*len].w_len == 0 && *len>=MIN_LEN_WORD;*len-=1);
    *w_info=s_words->stack[*len].next;               // save head of linked list of words
    if(init_sorted_item_array(lexeme, *len+1) != 0)
    {
        return 1; // exit if realloc gives NULL
    }
    // save longest word in lexeme to search for stems
    strcpy(lexeme->stack[0].word, (*w_info)->word);
    lexeme->stack[0].w_len = *len;
    lexeme->stack[0].k_ind = 0;
    
    return 0;
} // the end of int set_first_word(...)

// extract next longest word
int get_next_longest_word( struct sorted_item **w_info, struct sorted_item_array *s_words,
                          int *len, struct sorted_item_array *lexeme)
{
    int i = 0;
    
    if((*w_info)->next) // if this len words are in the list take it
    {
        (*w_info) = (*w_info)->next;
    } else{
        // extract next longest word
        for(*len-=1;(*w_info)=s_words->stack[*len].next,(*w_info == NULL && *len>=MIN_LEN_WORD);*len -=1);
    }
    if(*w_info) // if new longest word is
    {
        // set to check if this word is lexeme
        for(i=*len;i >= 0;i--)
        {
            lexeme->stack[i].word[0] = lexeme->stack[i].key[0] = '\0';
            lexeme->stack[i].w_len = lexeme->stack[i].k_ind = 0;
            lexeme->stack[i].w_len = lexeme->stack[i].searched = NOT_SET;
        }
        strcpy(lexeme->stack[0].word, (*w_info)->word);
        lexeme->stack[0].w_len = *len;
        i=0;
    } else
    {
        // no word left for search, exit loop
        return 1;
    }
    return 0;
} // the end of int get_next_longest_word(...)

// reset indext to next/previous stem or 0
int reset_index(int *i, int i_next, struct sorted_item_array *lexeme)
{
    if (*i < i_next)  // search next stem
    {
        *i = i_next;
        lexeme->stack[*i].searched = IS_STEM;
    } else if(*i > 0) // next stem is not found
    {
        // need to repead search by moving to previous stem or new candidate
        lexeme->stack[*i].k_ind = NO_STEM;
        lexeme->stack[*i].searched = NO_STEM;
        for(*i-=1; *i > 0 ;*i-=1)
        {
            if(lexeme->stack[*i].w_len >0 && lexeme->stack[*i].k_ind != NO_STEM)
            {
                if(lexeme->stack[*i].searched == IS_STEM) // this was checked - no good
                {
                    lexeme->stack[*i].searched = NO_STEM; // do not check it again
                    lexeme->stack[*i].k_ind = NO_STEM;
                } else
                {
                    lexeme->stack[*i].searched = IS_STEM; // set new candidate to be stem
                    break;
                }
            }
        }
    } else if(i_next == -1)
    {
        return 1; // invalid extract_keys(values) by developer
    }
    return 0;
} // the end of int reset_index(...)

// free memory of sorted_item index list
// if list has linked list - free that memory
void free_sorted_item_array(struct sorted_item_array *sia, int rm_next)
{
    struct sorted_item *curr = NULL;
    struct sorted_item *saved = NULL;
    int i = 0;
    
    if(sia == NULL)
    {
        return;
    }
    
    if(rm_next) // if dynamic aray has linked list - free it
    {
        for(i=0;i < sia->capacity;i++)
        {
            curr = sia->stack[i].next;
            if(curr)
            {
                for(saved = sia->stack[i].next->next;saved;saved=saved->next)
                {
                    free(curr);
                    curr = saved;
                }
                free(curr);
            }
        }
    } else // free dynamic array
    {
        free(sia->stack);
    }
} // the end of free_sorted_item_array(...)

// free allocated memory of dictionary
void free_dict(struct page **page)
{
    const char abc[] = "abcdefghijklmnopqrstuvwxyz";
    const int abc_size = (int)strlen(abc);
    struct page **abc_curr = NULL;
    struct page *abc_saved = NULL;
    int i = 0, a = 0;
    
    if(*page == NULL)
    {
        return;
    }
    for(a=0;a<abc_size;a++)
    {
        if((abc_saved = *abc_given_node(*page,abc[a])) == NULL)
        {
            continue;  // if main page letter is NULL go to next
        }
        abc_saved->prev = *page;   // link to main page
        abc_saved->index = a+1;  // save from where start to search
        
        // abc_saved->abc..z, check next abc...z
        i=0; // start search with a
        do {
            for(;i<abc_size;i++) // check this page for abc...z
            {
                abc_curr = abc_given_node(abc_saved,abc[i]);
                if(*abc_curr) break; // this is found letter
            }
            if(*abc_curr) // search next page but save index of found letter
            {
                (*abc_curr)->prev = abc_saved; // save back path
                abc_saved = (*abc_curr);       // move abc_saved to next found letter/page
                abc_saved->index = i+1;        // save index for next letter to be search
                i=0;                           // start new page with a to z
                
            } else // abc_curr page has all abc...z == NULL, free this page
            {
                do {
                    i = abc_saved->index;            // save from where to start to search
                    *abc_curr = abc_saved;           // move abc_curr one page up
                    abc_saved = (*abc_curr)->prev;   // move abc_saved to previous page
                    (*abc_curr)->prev = NULL;        // helps with debugging
                    free(*abc_curr);                 // free abc..z == NULL page
                } while(i == abc_size);              // if previous page is 'z' - free it
            }
            if(abc_saved == *page) // if we move to next letter at top page
            {
                a++; // reset top page index to next letter
            }
        } while(abc_saved);
        
        // TEST_ME: here must be control if not each page -> abc...z have been allocated
        
    } //  the end of for(a=0;a<abc_size;a++)
    
} // the end of void free_dict(...)

// read from command line text file with sorted 100K words
// from the longest to shortest find words (lexeme) that
// are constructed by other words (stem) from the same file
int main(int argc, const char * argv[])
{
    FILE *f = NULL;                               // command line file
    char line[MAX_LEN];                           // string from text file
    int i = 0,len = 0,i_next =0, found_limit = 0; // indexes
    struct page *dict;                            // dictionary to save words from text file
    struct sorted_item *word_info = NULL;         // to save info about one word
    struct sorted_item_array stack_words;         // words saved by length
    struct sorted_item_array lexeme;              // save candidate for lexeme
    
    if(argc < 2 ||(f=fopen(argv[1], "r")) == NULL)
    {
        printf("Invalid file\n"); // exit if no file at command line
        return 1;
    }
    if(init_page(&dict) != 0) // allocate space for dictionary
    {
        return 1; // exit if realloc returns NULL
    }
    if(init_sorted_item_array(&stack_words, (size_t)MAX_LEN_WORD) != 0)
    {
        return 1; // exit if realloc returns NULL
    }
    // save each word from file into dictionary
    while(fgets(line, MAX_LEN,f))
    {
        if((len = chomp_line(line)) == 0)
        {
            continue; // if blank line - read next one
        }
        
        // save words by length starting with MIN_LEN_WORD
        if(len >= MIN_LEN_WORD)
        {
            if(save_words_by_length(line,len, &stack_words) != 0)
            {
                return 1; // or exit with too long word or realloc retuns NULL
            }
        }
        if(add_to_page(line,len,dict) != 0) // save word in dict
        {
            return 1; // or exit if realloc returns NULL
        }
    }
    fclose(f); // close fiven text file
    
    // extract the first longest word
    if(set_first_word(&stack_words,&word_info,&lexeme,&len) != 0)
    {
        return 1;
    }
    found_limit = LEXEME_LIMIT;  // limits of lexeme printed out
    i=0;                         // start with char 'a'
    // find lexemes' 2 or more stems
    while(found_limit)
    {
        i_next = extract_keys(&(lexeme), i, dict);
        
        if(i_next == len) // lexeme is found - print it out
        {
            print_out_lexeme(&lexeme,i);
            // set limited # of lexemes to print out
            // by uncommenting line bellow
            found_limit--;
            i = 0;
        } else
        {
            // reset indext i to next/previous stem or 0
            if(reset_index(&i,i_next,&lexeme) != 0)
            {
                return 1; // or exit with internal error
            }
        }
        // lexeme is found or not found; get new longest word
        if(i == 0 && found_limit)
        {
            if(get_next_longest_word(&word_info,&stack_words,&len,&lexeme))
            {
                found_limit = 0; // or exit loop if no more words
            }
        }
    }// the end of while(found_limit)
    
    // free all allocated memory memory
    free_sorted_item_array(&stack_words,1);
    free_sorted_item_array(&lexeme,0);
    free_dict(&dict);
    
    return 0;
}
