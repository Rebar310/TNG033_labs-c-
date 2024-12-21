#include "set.hpp"

/*
 * std::size_t is defined in the C++ standard library
 * std::size_t is an unsigned integer type that can store the maximum size of any possible object
 * sizes are non-negative integers -- i.e. unsigned integer type
 */

 /* *********** class Node ************ */

 // This class is private to class Set
 // but all class Node members are public to class Set
class Set::Node {
public:
	// Constructor
	// Creates a new Node with a given value and a pointer to the next node.
	Node(int nodeVal = 0, Node* nextPtr = nullptr) : value{ nodeVal }, next{ nextPtr } {
		++count_nodes; // Increment total number of nodes.
	}

	// Destructor
	// Decrements the node counter and ensures the count does not drop below zero.
	~Node() {
		--count_nodes;
		assert(count_nodes >= 0);  // number of existing nodes can never be negative
	}
	int value; // Stores the value of the node.
	Node* next; // Pointer to the next node in the list.

	// Total number of existing nodes -- used only to help to detect bugs in the code
	// Cannot be used in the implementation of any member functions
	static std::size_t count_nodes;

	// Grant ostream operator access to private Set members.
	friend std::ostream& operator<<(std::ostream& os, const Set& rhs);
};

/* ************************************ */

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
	return Set::Node::count_nodes;
}

/* *********** class Set member functions ************ */

// Default constructor
Set::Set() : head{ new Node{} }, counter{ 0 } {  // create the dummy node
}

// Constructor for creating a singleton {x}
Set::Set(int x) : Set() {

	// Anropa default-konstruktorn för att skapa en tom mängd med dummy node
	// Skapa en ny node och sätt den som nästa element efter dummy-noden
	head->next = new Node{ x }; // Lägg till en ny nod x efter dummy-noden
	++counter;  // Öka räknaren för antalet element i mängden
}

// Constructor: create a set with elements
// elements is not sorted and values in it may not be unique
Set::Set(const std::vector<int>& elements) : Set() {
	/*
	 * Sorting a vector cannot used here
	 * std::sort and std::unique cannot be used
	 */
	for (int x : elements) {
		if (!member(x)) { // Insert only if the element is not already in the set
			Node* prev = head;        // Start from the dummy node
			Node* curr = head->next; // Find the correct position for sorted insertion
			while (curr != nullptr && curr->value < x) {
				prev = curr;
				curr = curr->next;
			}
			insert(prev, x); // Use insert to add the new value
		}
	}

}


// copy constructor
Set::Set(const Set& rhs) : Set() {  // Anropa default-konstruktorn för en tom mängd
	Node* ptr = rhs.head->next;  // Starta från den första riktiga noden i rhs
	while (ptr != nullptr) {
		// Lägg till varje element från rhs i den nya mängden
		if (!member(ptr->value)) {  // Kolla om elementet redan finns i den nya mängden (borde inte vara fallet om rhs inte har dubbletter)
			// Skapa en ny node med värdet från ptr och lägg till den i mängden
			SortInsert(ptr->value);

			ptr = ptr->next;  // Gå vidare till nästa nod
		}

	}
}

// Assignment operator: use copy-and-swap idiom
Set& Set::operator=(Set rhs) { // Kopiera rhs genom att använda kopieringskonstruktorn
	std::swap(head, rhs.head);  // Byt innehållet mellan det nuvarande objektet och rhs
	std::swap(counter, rhs.counter);  // Byt räknaren mellan det nuvarande objektet och rhs
	return *this;  // Returnera det aktuella objektet (nu med det nya innehållet)

}

// Destructor: deallocate all nodes (ändrad)
Set::~Set() {
	while (head->next != nullptr) { // While there are nodes after the dummy node
		remove(head);               // Use remove to delete the first real node
	}
	delete head; // Delete the dummy node
}

// Return number of elements in the set
std::size_t Set::cardinality() const {
	
	return counter;
}

// Test if set is empty
bool Set::empty() const {
	return head->next == nullptr;  // Om första riktiga noden är nullptr, är mängden tom
}

// Test if x is an element of the set
bool Set::member(int x) const {
	Node* current = head->next;  // Starta från första riktiga noden
	while (current != nullptr) {  // Gå igenom listan tills vi når slutet
		if (current->value == x) {  // Om värdet i noden är samma som x
			return true;  // Elementet finns i mängden
		}
		current = current->next;  // Gå vidare till nästa nod
	}
	return false;  // Elementet finns inte i mängden
}

// Return true, if *this is a subset of Set b
// Otherwise, false is returned
bool Set::is_subset(const Set& b) const {
	Node* current = head->next;  // Starta från första riktiga noden i *this
	while (current != nullptr) {
		// Kontrollera om elementet i den aktuella noden finns i b
		if (!b.member(current->value)) {
			return false;  // Om något element i *this inte finns i b, returnera false
		}
		current = current->next;  // Gå vidare till nästa nod i *this
	}
	return true;  // Alla element i *this finns i b, så *this är en delmängd
}

// new union code ********************************************************************************************

Set Set::set_union(const Set& b) const {
	Set result; // Skapa ett nytt Set-objekt för att lagra unionen.
	Node* tail = result.head; // Håller reda på den senaste noden i resultatmängden.

	Node* current_this = head->next; // Börja från första riktiga noden i *this.
	Node* current_b = b.head->next;  // Börja från första riktiga noden i b.

	// Gå igenom båda listorna samtidigt
	while (current_this != nullptr || current_b != nullptr) {
		if (current_this != nullptr && (current_b == nullptr || current_this->value < current_b->value)) {
			// Lägg till element från *this om:
			// - Listan b är slut, eller
			// - current_this har ett mindre värde än current_b.
			result.insert(tail, current_this->value);
			current_this = current_this->next; // Flytta till nästa nod i *this.
		}
		else if (current_b != nullptr && (current_this == nullptr || current_b->value < current_this->value)) {
			// Lägg till element från b om:
			// - Listan *this är slut, eller
			// - current_b har ett mindre värde än current_this.
			result.insert(tail, current_b->value);
			current_b = current_b->next; // Flytta till nästa nod i b.
		}
		else {
			// Om värdena i current_this och current_b är lika, lägg till det ena och hoppa över det andra.
			result.insert(tail, current_this->value);
			current_this = current_this->next; // Hoppa till nästa nod i *this.
			current_b = current_b->next;      // Hoppa till nästa nod i b.
		}

		// Flytta tail till den sista insatta noden.
		tail = tail->next;
	}

	return result; // Returnera resultatmängden.
}

//**********************************************************************************************************************

// Return a new Set representing the intersection of Sets *this and b
Set Set::set_intersection(const Set& b) const {
	Set result; // Skapa en ny Set för snittet
	Node* tail = result.head; // Håller reda på den senaste noden i resultatet

	Node* current_this = head->next; // Börja från första riktiga noden i *this
	Node* current_b = b.head->next;  // Börja från första riktiga noden i b

	// Iterera genom båda listorna samtidigt
	while (current_this != nullptr && current_b != nullptr) {
		if (current_this->value < current_b->value) {
			// Om värdet i *this är mindre, gå vidare till nästa nod i *this
			current_this = current_this->next;
		}
		else if (current_this->value > current_b->value) {
			// Om värdet i b är mindre, gå vidare till nästa nod i b
			current_b = current_b->next;
		}
		else {
			// Om värdena är lika, lägg till det i resultatet
			result.insert(tail, current_this->value);
			tail = tail->next; // Uppdatera tail till den senaste insatta noden
			current_this = current_this->next; // Gå till nästa nod i *this
			current_b = current_b->next;      // Gå till nästa nod i b
		}
	}

	return result; // Returnera resultatmängden
}

// Return a new Set representing the difference between Set *this and Set b
Set Set::set_difference(const Set& b) const {
	Set result; // Skapa ett nytt Set-objekt för att lagra differensen.
	Node* tail = result.head; // Håll reda på den senaste noden i resultatmängden.

	Node* current_this = head->next; // Börja från första riktiga noden i *this.
	Node* current_b = b.head->next;  // Börja från första riktiga noden i b.

	// Iterera genom båda listorna samtidigt
	while (current_this != nullptr) {
		if (current_b == nullptr || current_this->value < current_b->value) {
			// Lägg till elementet från *this i resultatet om:
			// - Listan b är slut, eller
			// - current_this har ett mindre värde än current_b.
			result.insert(tail, current_this->value);
			tail = tail->next; // Flytta tail till den senaste insatta noden.
			current_this = current_this->next; // Gå vidare till nästa nod i *this.
		}
		else if (current_this->value > current_b->value) {
			// Om current_b har ett mindre värde, hoppa över det och gå vidare i b.
			current_b = current_b->next;
		}
		else {
			// Om värdena är lika, hoppa över båda (inget läggs till i resultatet).
			current_this = current_this->next;
			current_b = current_b->next;
		}
	}

	return result; // Returnera resultatmängden.
}



std::ostream& operator<<(std::ostream& os, const Set& rhs) {
	if (rhs.empty()) {
		os << "Set is empty!";
	}
	else {
		Set::Node* ptr = rhs.head->next;
		os << "{ ";

		while (ptr != nullptr) {
			os << ptr->value << " ";
			ptr = ptr->next;
		}
		os << "}";
	}
	return os;
}




/********** Private member functions ************/

// Skapa en ny node och sortera in den så att listan blir med stigande värden
void Set::SortInsert(int x)
{
	Node* prev = head;  // Börja från dummy-noden
	Node* current = head->next;

	// Gå vidare tills vi hittar rätt plats (dvs. tills current->value > x eller vi når slutet)
	while (current != nullptr && current->value < x) {
		prev = current;
		current = current->next;
	}

	// Skapa en ny nod och sätt in den efter 'prev' och före 'current'
	Node* newNode = new Node{ x };
	prev->next = newNode;
	newNode->next = current;

	++counter;  // Öka räknaren för antalet element i mängden
}

// Private helper function: Insert a new node after the node pointed by p
// The new node will store the given value
void Set::insert(Node* p, int value) {
	Node* newNode = new Node{ value }; // Allocate memory for the new node
	newNode->next = p->next;           // Link the new node to the next node
	p->next = newNode;                 // Link p to the new node
	++counter;                         // Increment the element counter
}

// Private helper function: Remove the node immediately following the node pointed by p
void Set::remove(Node* p) {
	if (p->next != nullptr) {          // Ensure there is a node to remove
		Node* temp = p->next;          // Store the node to be removed
		p->next = temp->next;          // Link p to the node after temp
		delete temp;                   // Free memory for the removed node
		--counter;                     // Decrement the element counter
	}
}