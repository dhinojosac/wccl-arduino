#include "unionfind.h"

/*
 * 
 */
node_t * initUnion(void){
  node_t * head = malloc(sizeof(node_t));
  data_t mdata = {-1,-1};
  head->data = mdata;
  head->next = NULL;
  return head;
}
/*
 * 
 */
uint8_t add_at(node_t* head, data_t data) 
{
   if(head->data.low==255)
   {
    head->data.low = data.low;
    head->data.high = data.high;
    head->next = NULL;
    return 2;
   }
    node_t* temp = (node_t*) malloc(sizeof (node_t));
    if (temp == NULL) {
        exit(EXIT_FAILURE); // no memory available
    }
    temp->data = data;
    temp->next = head->next;
    head->next = temp;
    return 0;
}
/*
 * 
 */
uint8_t check_is_data(node_t* head, data_t data)
{
    node_t * temp;
    for (temp = head; temp; temp = temp->next)
    {
        if((temp->data.low==data.low) && (temp->data.high==data.high) )
        {
          return 0;
        }
    }
    return 1;
}

/*
 * 
 */
uint8_t get_len_union(node_t* head)
{
    node_t * temp;
    uint8_t index=0;
    for (temp = head; temp; temp = temp->next)
    {
      index++;
    }
    return index;
}

/*
 * 
 */
data_t get_data(node_t* head,uint8_t index)
{
  node_t * temp;
  temp->data.low = 255;
  temp->data.high = 255;
  if(index>get_len_union(head)){
    exit(EXIT_FAILURE); // no memory available
  }
  uint8_t cur_index=0;
  for (temp = head; temp; temp = temp->next)
  {
      if(cur_index==index)
      {
        return temp->data;
      }
      cur_index++;
  }
}
