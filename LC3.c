/* 
 * This is an LC3 virtual machine I am building to learn more about computer architecture.
 * It was created by following along with this tutorial https://justinmeiners.github.io/lc3-vm/
 * All of the credits for this code go the person who created that tutorial ^^^
 */
// unix specific include statements
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

