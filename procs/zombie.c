#include <sys/types.h>
#include <unistd.h>

int main() {
	if (fork()) {
		/*pai*/

		while (1)
			; /* em execução */
	}
}
