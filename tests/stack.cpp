#include <deque>
#include "containers.hpp"

template <class T , class C>
void print_stack_status(ft::stack<T, C>& stck){
	if (stck.size() > 0)
		std::cout << "|top: " << stck.top() << std::endl;
	else
		std::cout << "|top: " << std::endl;
	std::cout << "|size: " << stck.size() << std::endl;
}

void test_stack(void){
	std::cout << "==============================" << std::endl;
	std::cout << "             stack            " << std::endl;
	std::cout << "==============================" << std::endl;
	std::cout << "Constructors" << std::endl;
	ft::stack<std::string, ft::vector<std::string> > emptyStack;
	ft::vector<std::string> my_vec(10, "test");
	ft::stack<std::string, ft::vector<std::string> > notEmptyStack(my_vec);
	ft::stack<int, std::deque<int> > dequeStack;
	std::cout << "---- Is empty ----" << std::endl;
	std::cout << "emptyStack.empty(): " << (emptyStack.empty() ? "true" : "false") << std::endl;
	std::cout << "notEmptyStack.empty(): " << (notEmptyStack.empty() ? "true" : "false") << std::endl;
	std::cout << "dequeStack.empty(): " << (dequeStack.empty() ? "true" : "false") << std::endl;

	std::cout << "\n---- size ----" << std::endl;
	std::cout << "emptyStack.size(): " << emptyStack.size() << std::endl;
	std::cout << "notEmptyStack.size(): " << notEmptyStack.size() << std::endl;
	std::cout << "dequeStack.size(): " << dequeStack.size() << std::endl;

	std::cout << "\n---- top ----" << std::endl;
	std::cout << "notEmptyStack.top(): " << notEmptyStack.top() << std::endl;

	std::cout << "\n---- push ----" << std::endl;
	std::cout << "emptyStack before push(\"XXX\")" << std::endl;
	print_stack_status(emptyStack);
	emptyStack.push("XXX");
	std::cout << "emptyStack after push(\"XXX\")" << std::endl;
	print_stack_status(emptyStack);

	std::cout << "notEmptyStack before push(\"XXX\")" << std::endl;
	print_stack_status(notEmptyStack);
	notEmptyStack.push("XXX");
	std::cout << "notEmptyStack after push(\"XXX\")" << std::endl;
	print_stack_status(notEmptyStack);

	std::cout << "dequeStack before push(100)" << std::endl;
	print_stack_status(dequeStack);
	dequeStack.push(100);
	std::cout << "dequeStack after push(100)" << std::endl;
	print_stack_status(dequeStack);

	std::cout << "dequeStack before push(50)" << std::endl;
	print_stack_status(dequeStack);
	dequeStack.push(50);
	std::cout << "dequeStack after push(50)" << std::endl;
	print_stack_status(dequeStack);
	
	std::cout << "\n--- relational Operators ---" <<std::endl;
	std::cout << "emptyStack == notEmptyStack: " << (emptyStack == notEmptyStack) << std::endl;
	std::cout << "emptyStack != notEmptyStack: " << (emptyStack != notEmptyStack) << std::endl;
	std::cout << "emptyStack < notEmptyStack: " << (emptyStack < notEmptyStack) << std::endl;
	std::cout << "emptyStack <= notEmptyStack: " << (emptyStack <= notEmptyStack) << std::endl;
	std::cout << "emptyStack > notEmptyStack: " << (emptyStack > notEmptyStack) << std::endl;
	std::cout << "emptyStack >= notEmptyStack: " << (emptyStack >= notEmptyStack) << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------" << std::endl;


}