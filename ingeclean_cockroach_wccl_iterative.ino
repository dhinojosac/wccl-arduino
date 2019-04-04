/*
 * dhinojosac 2019
 * ITERATIVE
 */
 extern "C"{
 #include "unionfind.h"
 }
 
#define THRESHOLD 190

#define ROWS 12
#define COLS 27

//Test trap matrix 12x28

int m[12][28] = {
{199,203,226,218,224,229,229,241,233,241,242,241,241,241,242,242,223,240,235,232,207,229,216,232,200,208,189,192},
{183,199,210,208,184,207,214,232,209,236,239,234,201,221,228,220,208,218,226,221,204,223,212,207,175,180,191,193},
{176,199,215,213,214,213,234,239,216,239,240,241,229,240,240,239,218,237,240,229,216,220,216,223,190,200,195,201},
{185,201,212,217,219,238,240,241,239,242,242,242,231,241,242,241,239,241,241,241,240,239,237,226,215,208,215,202},
{197,200,226,236,221,239,241,240,238,241,242,242,239,242,242,241,240,241,242,242,238,241,241,239,203,219,215,194},
{184,208,230,229,231,239,241,242,240,242,242,241,240,241,242,242,239,241,242,241,241,240,239,240,223,211,201,197},
{197,200,184,236,221,239,231,240,238,241,240,242,239,242,240,241,240,241,240,242,238,241,241,239,203,219,223,194},
{226,208,230,229,241,239,241,242,242,242,242,241,242,241,242,242,242,241,242,241,241,240,239,240,215,211,201,197},
{186,193,187,225,226,113,200,241,237,241,223,240,238,241,228,240,234,241,228,239,229,236,212,236,204,195,203,240},
{215,192,209,214,236,210,113,235,241,237,239,239,241,240,238,239,238,237,232,225,231,228,230,223,206,207,200,240},
{184,195,202,203,186,207,211,212,114,113,234,221,215,218,228,234,214,204,181,168,163,172,185,205,185,191,185,187},
{182,185,194,193,209,195,204,213,210,113,217,216,218,213,226,229,217,223,224,221,207,215,198,201,196,192,197,184},
};

// the labels, 0 means unlabeled
uint8_t labels[12][28];

// direction vectors
const uint8_t dx[] = {+1, +1};
const uint8_t dy[] = {0, +1};

//Label
int label = 1;

//Union 
node_t * myUnion;

//Declare functions
void find_components() ;

void setup() {
  Serial.begin(9600);
  Serial.println(F("*** IngeClean Board testing **"));
   
   myUnion = initUnion();
    
  set_labels();
  print_result();

  uint8_t len_union = get_len_union(myUnion);
  Serial.print("Union len: ");
  Serial.println(len_union);

  print_list(myUnion);


  for(uint8_t len = len_union; len>0;len--)
  { 
    data_t temp_data = get_data(myUnion,len-1);
    
    for (uint8_t i = 0; i < ROWS; ++i) 
      for (uint8_t j = 0; j < COLS; ++j){
        if(labels[i][j]==temp_data.high)
        {
          labels[i][j]=temp_data.low;
        }
      }    
      
  }
  
  print_result();
  
}

void loop() {
  
}

void set_labels()
{
  for (uint8_t i = 0; i < ROWS; ++i) 
    for (uint8_t j = 0; j < COLS; ++j){
      if(m[i][j] > THRESHOLD){
        labels[i][j] = 0;
      }else{
        if(i>0 && j>0 && ((m[i][j-1] < THRESHOLD) && (m[i-1][j] < THRESHOLD)) && labels[i][j-1] != labels[i-1][j])
        {
          
          uint8_t low_level = labels[i][j-1];
          uint8_t high_level = labels[i-1][j];
          if (labels[i][j-1] > labels[i-1][j])
          {
            labels[i][j] = labels[i-1][j];
            low_level = labels[i-1][j];
            high_level = labels[i][j-1];
           } else {
                labels[i][j] = labels[i][j-1];
           }   
           
           //add element to union    
           if(check_is_data(myUnion, {low_level,high_level})==1){
                  add_at(myUnion,{low_level,high_level});
           }
            
        }
        else if (j > 0 && m[i][j-1] < THRESHOLD)
        {
             labels[i][j] = labels[i][j-1];
        } 
        else if (i > 0 && m[i-1][j] < THRESHOLD)
        {
              labels[i][j] = labels[i-1][j];
        } 
        else if (i > 0 && j == 0 && m[i-1][j] < THRESHOLD) 
        {
              labels[i][j] = labels[i-1][j];
        } 
        else if (i == 0 && j > 0 && m[i][j-1] < THRESHOLD) 
        {
              labels[i][j] = labels[i][j-1];
        }  
        else 
        {
              labels[i][j] = label;
              label += 1;
        }
      }
    }
}


void print_result()
{
   for (uint8_t i = 0; i < ROWS; ++i) 
   {
      for (uint8_t j = 0; j < COLS; ++j){
        Serial.print(labels[i][j]);
        Serial.print(" ,");
      }
    Serial.println();
   }
}

void print_list(node_t* head) {
    node_t * temp;
    uint8_t index = 0;
    for (temp = head; temp; temp = temp->next)
    {
        Serial.print(F("i: "));
        Serial.println(index);
        Serial.print(F("l: "));
        Serial.print(temp->data.low);
        Serial.print(F(" h: "));
        Serial.println(temp->data.high);
        index++;
    }
}
