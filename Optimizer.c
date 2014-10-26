/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2014                                *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{

	

	Instruction *head;
	Instruction *prev_node, *curr_node, *next_node;
	int opt_flag, opt_calc;



	head = ReadInstructionList(stdin);

        /* ---  FIRST: ALGEBRAIC SIMPLIFICATION PASS --- */

	if (!head) {
		ERROR("No instructions\n");
		exit(EXIT_FAILURE);
	}



	curr_node = head;
	next_node = curr_node->next;
	prev_node = curr_node->prev;

	while (curr_node !=NULL && next_node != NULL)
	{
		if (next_node->opcode == MUL)
		{
			if (curr_node->opcode == LOADI || prev_node->opcode == LOADI)
			{
				if (curr_node->field2 == 0 || prev_node->field2 == 0)
				{
					prev_node->opcode = LOADI;
					prev_node->field1 = next_node->field1;
					prev_node->field2 = 0;
					prev_node->field3 = NULL;
					
					prev_node->next = next_node->next;  // set next of first node in trio to 3rd's next
					next_node->next->prev = prev_node;
					curr_node = prev_node->next;

					//Instruction * temp = next_node->next;
					//if (temp)
					//{temp->prev = prev_node;}

					//next_node->next->prev = prev_node;   // set "4th" nodes prev to 1st node in trio

				//	free(curr_node);
				//	free(next_node);
				}

				else if ( (curr_node->field2 == 1 && prev_node->opcode == LOAD) || (prev_node->field2 == 1 && curr_node->opcode == LOAD) )
				{
					prev_node->opcode = LOAD;
					prev_node->field1 = next_node->field1;

					if (curr_node->field2 == 1)
					{
						prev_node->opcode = LOAD;
						prev_node->field3 = NULL;
					}

					else if (prev_node->field2 == 1)
					{
						prev_node->opcode = LOAD;
						prev_node->field2 = curr_node->field2;
						prev_node->field3 = NULL;
					}

					prev_node->next = next_node->next;  // set next of first node in trio to 3rd's next
					next_node->next->prev = prev_node;

					curr_node = prev_node->next;

				//	Instruction * temp = next_node->next;
				//	if (temp)
				//	{temp->prev = prev_node;}

					//next_node->next->prev = prev_node;   // set "4th" nodes prev to 1st node in trio

				//	free(curr_node);
					//free(next_node);
				}
			}
		}

		else if (next_node->opcode == ADD)
		{
			if (curr_node->opcode == LOADI  || prev_node->opcode == LOADI)
			{
				if ( (curr_node->field2 == 0 && prev_node->opcode == LOAD) || (prev_node->field2 == 0 && curr_node->opcode == LOAD) )
				{
				
					prev_node->opcode = LOAD;
					prev_node->field1 = next_node->field1;

					if (curr_node->field2 == 0)
					{
						prev_node->opcode = LOAD;
						prev_node->field3 = NULL;
					}

					else if (prev_node->field2 == 0)
					{
						prev_node->opcode = LOAD;
						prev_node->field2 = curr_node->field2;
						prev_node->field3 = NULL;
					}

					prev_node->next = next_node->next;  // set next of first node in trio to 3rd's next
					next_node->next->prev = prev_node;

					/*Instruction * temp = next_node->next;
					if (temp)
					{temp->prev = prev_node;}  */

					curr_node = prev_node->next;  // MAY BE FUCKING RETARDED

					//next_node->next->prev = prev_node;   // set "4th" nodes prev to 1st node in trio

					//free(curr_node);
					//free(next_node);
				}
			}
		}

		else if (next_node->opcode == SUB)
		{
			if (curr_node->opcode == LOADI  || prev_node->opcode == LOADI)
			{
				if ( (curr_node->field2 == 0 && prev_node->opcode == LOAD) || (prev_node->field2 == 0 && curr_node->opcode == LOAD) )
				{

					if (next_node->field2 == curr_node->field1 && curr_node->field2 == 0)
					{
						// do nothing
						goto iteration;
					}

					if (next_node->field2 == prev_node->field1 && prev_node->field2 == 0)
					{
						//do nothing
						goto iteration;
					}
				
					prev_node->opcode = LOAD;
					prev_node->field1 = next_node->field1;

					if (curr_node->field2 == 0)
					{
						prev_node->opcode = LOAD;
						prev_node->field3 = NULL;
					}

					if (prev_node->field2 == 0)
					{
						prev_node->opcode = LOAD;
						prev_node->field2 = curr_node->field2;
						prev_node->field3 = NULL;
					}

					prev_node->next = next_node->next;  // set next of first node in trio to 3rd's next
					next_node->next->prev = prev_node;

					curr_node = prev_node->next;  // MAY BE FUCKING RETARDED


				}
			}
		}
		
	iteration:

	curr_node = curr_node->next;
    prev_node = curr_node->prev;
    next_node = curr_node->next;

	}



// SECOND PASS

	if (!head) {
		ERROR("No instructions\n");
		exit(EXIT_FAILURE);
	}


	curr_node = head;
	next_node = curr_node->next;
	prev_node = curr_node->prev;


	while(curr_node != NULL && next_node !=NULL)
	{
        if(prev_node!= NULL && prev_node->opcode == LOADI && curr_node !=NULL && curr_node->opcode == LOADI){
            
            switch(next_node->opcode)
            {
                
                case ADD:

                    prev_node->field1 = next_node->field1;
                    prev_node->field2 = curr_node->field2 + prev_node->field2;
                    prev_node->field3 = NULL;

                    prev_node->next = next_node->next;  
                    next_node->next->prev = prev_node; 
					//next_node->next->prev = prev_node;  
					
					curr_node = prev_node->next;  // MAY BE FUCKING RETARDED

					break;

					//free(curr_node);
					//free(next_node);
                    
                case SUB:
                    
                    prev_node->field1 = next_node->field1;
                   
                    if(next_node->field2 > next_node->field3)   
                    {
                        prev_node->field2 = curr_node->field2 - prev_node->field2;
                    }
                    else
                    {
                        prev_node->field2 = prev_node->field2 -  curr_node->field2;   // test
                    }

                    prev_node->next = next_node->next;  
					next_node->next->prev = prev_node;   

					curr_node = prev_node->next;  // MAY BE FUCKING RETARDED

					break;

				//	free(curr_node);
					//free(next_node);

                    
                case MUL:

                    prev_node->field1 = next_node->field1;
                    prev_node->field2 = curr_node->field2 * prev_node->field2;

                    prev_node->next = next_node->next;   
					next_node->next->prev = prev_node; 

					curr_node = prev_node->next;  // MAY BE FUCKING RETARDED

					break;

					//free(curr_node);
				//	free(next_node);


                default:
                    break;
            }
        }
        curr_node = curr_node->next;
        prev_node = curr_node->prev;
        next_node = curr_node->next;
    }


	/* YOUR CODE GOES HERE */


	PrintInstructionList(stdout, head);
	DestroyInstructionList(head);
	return EXIT_SUCCESS;
}
