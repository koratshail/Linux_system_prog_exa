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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
	int ret;
	void *ptr;
	unsigned char mincore_vec[5];
	size_t page_size;
	size_t size;
	size_t page_index;

	/*get arch specific page size */
	page_size = getpagesize();
	size = page_size * 5;

	getchar();
	/* Allocate 20k buffer(mmap region) */
	posix_memalign(&ptr, page_size, size);
	if(!ptr){
		printf("allocation failed\n");
		return -1;
	}

	printf("%p\n", ptr);

	mlock(ptr, size);
	/* fill buffer with 0's */
//	memset(ptr, 0, 4096 * 2);

	/* verify physical memory map */
	ret = mincore(ptr, size, mincore_vec);
	if(ret<0)
		perror("mincore");

	/* print results */
	for (page_index = 0; page_index < 5 ; page_index++) {
		if (mincore_vec[page_index] & 1) 
			printf("page %lu active\n", (unsigned long)page_index);
		else
			printf("page %lu not active\n", (unsigned long)page_index);
	}
	getchar();
	/* release buffer */
	munmap(ptr, size);
	return 0;
}

/* 
 *
	ptr = malloc(4096);

	vadd    phyadd status
	x	a       active                        backstore(TRAM, vmem)
								400

	*ptr = 400;
	...
	...
	...
	...
	...
	...
	printf("%d\b", *ptr);

*/
