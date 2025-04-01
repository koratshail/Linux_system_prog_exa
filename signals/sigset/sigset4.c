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


/* using sigset_t.
Version : 1.0
Author : Team -C
*/

#include <stdio.h>
#include <signal.h>

void check_blocked_sigs()
{
	int i, res;
	sigset_t s;
	sigprocmask(SIG_BLOCK, NULL, &s);	//first param is not considered
	for (i = 1; i < 5; i++) {
		res = sigismember(&s, i);
		if (res)
			printf(" signal %d is blocked \n", i);
		else
			printf(" signal %d is not blocked \n", i);
	}
}

int main()
{
	sigset_t s_set, set1;
	sigemptyset(&s_set);
	sigaddset(&s_set, 1);
	sigaddset(&s_set, 4);
	sigaddset(&s_set, 3);
	sigprocmask(SIG_BLOCK | SIG_SETMASK, &s_set, NULL);

	check_blocked_sigs();

	sigemptyset(&s_set);
	sigaddset(&s_set, 2);
	sigprocmask(SIG_BLOCK | SIG_SETMASK, &s_set, NULL);

	check_blocked_sigs();
	return 0;
}
