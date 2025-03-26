/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * ******************************************************************************
 * This program is part of the source code provided with "Linux Systems Programming" Course
 * (c) 2019- 2021 Techveda, Hyderabad, India
 * website : www.techveda.org
 * Author/Trainer:  Raghu Bharadwaj
 * ******************************************************************************
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


void *curr_brk, *old_brk, *new_brk;

int main(int argc, char *argv[])
{
	int ret;
	void *ptr, *ptr2;

	printf("[%d]:grab start of heap\n",getpid());
	getchar();	
	/* grab current program break address */
	curr_brk = sbrk(0);
	old_brk = curr_brk;

	printf("\n %p \n", curr_brk);
	getchar();

	/* increase program brk by 100 bytes */
	ptr = (void *) malloc(100);
	if (!ptr){
		fprintf(stderr,"malloc(100) failed\n");
		exit(1);
	}

	printf("\n %p \n", ptr);
	/* verify change */
	new_brk = sbrk(0);
	printf("\n %p \n", new_brk);
	getchar();

	/* increase prgram brk by 500 bytes  */
	ptr2 = (void *) malloc(200);
	if (!ptr2){
		fprintf(stderr,"malloc(500) failed\n");
		exit(1);
	}

	printf("\n %p \n", ptr2);
	/* verify change */
	new_brk = sbrk(0);
	printf("\n %p \n", new_brk);

	getchar();

	/* release 2nd chunck */
	free(ptr2);
	curr_brk= sbrk(0);
	printf("\n %p \n",curr_brk);
	getchar();

	/* release 1st chunck */
	free(ptr);
	curr_brk= sbrk(0);
	printf("\n %p \n",curr_brk);
	return 0;
}
