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
#include <string.h>
#include <malloc.h>

int main()
{
	int i =100;
	void *p, *p1, *p2;


	mallopt(M_TOP_PAD, 0);
	mallopt(M_MMAP_THRESHOLD, 4096 * 4);
	mallopt(M_TRIM_THRESHOLD, 4096);
//	malloc_stats();

/*	p = (void *)malloc(4096 * 5);
	malloc_stats();
	getchar();

	free(p);
	malloc_stats();
	getchar();
*/
	p1 = (void *)malloc(2048 * 3);
	malloc_stats();
	getchar();

	free(p1);
	malloc_stats();
	getchar();


	p2 = (void *)malloc(1024 * 3);
	malloc_stats();
	getchar();

	free(p2);
	malloc_stats();
	getchar();


	p2 = (void *)malloc(1024);
	malloc_stats();
	getchar();

	free(p2);
	malloc_stats();
	getchar();

	return 0;
}
