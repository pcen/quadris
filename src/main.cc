#include <iostream>

#include "window/Window.h"
#include "misc/Trie.h"

// Test Prototypes
// TODO: move tests to designated location
void test_trie(void);

int main(int argc, char* argv[])
{
	// Window window("Quadris", 640, 480, argc, argv);
	// window.launch();
	test_trie();
	return 0;
}


// Tests
// TODO: move tests to designated location
void test_trie(void)
{
	Trie t;
	t.push("yeet");
	t.print(); std::cout << '\n';
	t.push("yeetus");
	t.print(); std::cout << '\n';
	t.push("reereereereeree");
	t.print(); std::cout << '\n';
}
