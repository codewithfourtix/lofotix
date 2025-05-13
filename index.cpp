#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Custom string class since  string is not allowed
class MyString
{
private:
	char *data;
	size_t length;
	size_t capacity;

public:
	// Constructor
	MyString() : length(0), capacity(0)
	{
		data = new char[1];
		data[0] = '\0';
	}

	// Constructor with C-string
	MyString(const char *str) : capacity(0)
	{
		if (str == NULL)
		{
			data = new char[1];
			data[0] = '\0';
		}
		else
		{
			length = 0;
			while (str[length] != '\0')
			{
				length++;
			}
			capacity = length + 1;
			data = new char[capacity];
			for (size_t i = 0; i < length; i++)
			{
				data[i] = str[i];
			}
			data[length] = '\0';
		}
	}

	// Copy constructor
	MyString(const MyString &other)
	{
		length = other.length;
		capacity = other.capacity;
		data = new char[capacity];
		for (size_t i = 0; i < length; i++)
		{
			data[i] = other.data[i];
		}
		data[length] = '\0';
	}

	// Destructor
	~MyString()
	{
		delete[] data;
	}

	// Assignment operator
	MyString &operator=(const MyString &other)
	{
		if (this != &other)
		{
			delete[] data;
			length = other.length;
			capacity = other.capacity;
			data = new char[capacity];
			for (size_t i = 0; i < length; i++)
			{
				data[i] = other.data[i];
			}
			data[length] = '\0';
		}
		return *this;
	}

	// Append operator
	MyString &operator+=(const MyString &other)
	{
		size_t newLength = length + other.length;
		if (newLength + 1 > capacity)
		{
			capacity = newLength + 1;
			char *newData = new char[capacity];
			for (size_t i = 0; i < length; i++)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		for (size_t i = 0; i < other.length; i++)
		{
			data[length + i] = other.data[i];
		}
		length = newLength;
		data[length] = '\0';
		return *this;
	}

	// Addition operator
	MyString operator+(const MyString &other) const
	{
		MyString result(*this);
		result += other;
		return result;
	}

	//	// Get character at index
	//	char operator[](size_t index) const {
	//		if (index < length) {
	//			return data[index];
	//		}
	//		return '\0';
	//	}
	//
	//	// Get character at index (non-const)
	//	char& operator[](size_t index) {
	//		if (index < length) {
	//			return data[index];
	//		}
	//		static char nullChar = '\0';
	//		return nullChar;
	//	}

	// Get character at index (const version)
	char operator[](size_t index) const
	{
		if (index >= length)
		{
			//			throw out_of_range("Index out of range in MyString (const)");
		}
		return data[index];
	}

	// Get character at index (non-const version)
	char &operator[](size_t index)
	{
		if (index >= length)
		{
			//			throw out_of_range("Index out of range in MyString");
		}
		return data[index];
	}

	// Get C-string
	const char *c_str() const
	{
		return data;
	}

	// Get length
	size_t size() const
	{
		return length;
	}

	// Check if empty
	bool empty() const
	{
		return length == 0;
	}

	// Clear string
	void clear()
	{
		delete[] data;
		data = new char[1];
		data[0] = '\0';
		length = 0;
		capacity = 1;
	}

	// Compare strings
	bool operator==(const MyString &other) const
	{
		if (length != other.length)
		{
			return false;
		}
		for (size_t i = 0; i < length; i++)
		{
			if (data[i] != other.data[i])
			{
				return false;
			}
		}
		return true;
	}

	// Input from console
	void getLine()
	{
		clear();
		char ch;
		while ((ch = static_cast<char>(getchar())) != '\n')
		{
			if (ch == EOF)
				break;

			if (length + 1 >= capacity)
			{
				capacity = capacity * 2 + 1;
				char *newData = new char[capacity];
				for (size_t i = 0; i < length; i++)
				{
					newData[i] = data[i];
				}
				delete[] data;
				data = newData;
			}

			data[length++] = ch;
			data[length] = '\0';
		}
	}
};

// Custom dynamic array since  vector is not allowed
template <typename T>
class MyArray
{
private:
	T *data;
	size_t size_;
	size_t capacity_;

public:
	// Constructor
	MyArray() : size_(0)
	{
		data = new T[1];
		capacity_ = 1;
	}

	// Destructor
	~MyArray()
	{
		delete[] data;
	}

	// Copy constructor
	MyArray(const MyArray &other)
	{
		size_ = other.size_;
		capacity_ = other.capacity_;
		data = new T[capacity_];
		for (size_t i = 0; i < size_; i++)
		{
			data[i] = other.data[i];
		}
	}

	// Assignment operator
	MyArray &operator=(const MyArray &other)
	{
		if (this != &other)
		{
			delete[] data;
			size_ = other.size_;
			capacity_ = other.capacity_;
			data = new T[capacity_];
			for (size_t i = 0; i < size_; i++)
			{
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	// Add element
	void push_back(const T &value)
	{
		if (size_ >= capacity_)
		{
			capacity_ = capacity_ * 2;
			T *newData = new T[capacity_];
			for (size_t i = 0; i < size_; i++)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		data[size_++] = value;
	}

	// Remove last element
	void pop_back()
	{
		if (size_ > 0)
		{
			size_--;
		}
	}

	// Get element at index
	T &operator[](size_t index)
	{
		return data[index];
	}

	// Get element at index (const)
	const T &operator[](size_t index) const
	{
		return data[index];
	}

	// Get size
	size_t size() const
	{
		return size_;
	}

	// Check if empty
	bool empty() const
	{
		return size_ == 0;
	}

	// Clear array
	void clear()
	{
		delete[] data;
		data = new T[1];
		size_ = 0;
		capacity_ = 1;
	}
};

// Console colors and utilities
namespace ConsoleUtils
{
	// Color codes
	enum ConsoleColor
	{
		BLACK = 0,
		DARK_BLUE = 1,
		DARK_GREEN = 2,
		DARK_CYAN = 3,
		DARK_RED = 4,
		DARK_MAGENTA = 5,
		DARK_YELLOW = 6,
		GRAY = 7,
		DARK_GRAY = 8,
		BLUE = 9,
		GREEN = 10,
		CYAN = 11,
		RED = 12,
		MAGENTA = 13,
		YELLOW = 14,
		WHITE = 15
	};

	// Set console color
	void setColor(int textColor, int backgroundColor = 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor + (backgroundColor * 16));
	}

	// Reset to default color
	void resetColor()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}

	// Clear console screen
	void clearScreen()
	{
		system("cls");
	}

	// Set cursor position
	void setCursorPosition(int x, int y)
	{
		COORD coord;
		coord.X = static_cast<SHORT>(x);
		coord.Y = static_cast<SHORT>(y);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	// Hide cursor
	void hideCursor()
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

	// Show cursor
	void showCursor()
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 25;
		cursorInfo.bVisible = TRUE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

	// Get console width
	int getConsoleWidth()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}

	// Get console height
	int getConsoleHeight()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}

	// Print centered text
	void printCentered(const char *text, int y, int textColor, int bgColor = BLACK)
	{
		int len = 0;
		while (text[len] != '\0')
		{
			len++;
		}
		int x = (getConsoleWidth() - len) / 2;
		setCursorPosition(x, y);
		setColor(textColor, bgColor);
		cout << text;
		resetColor();
	}

	// Print text at position
	void printAt(const char *text, int x, int y, int textColor, int bgColor = BLACK)
	{
		setCursorPosition(x, y);
		setColor(textColor, bgColor);
		cout << text;
		resetColor();
	}

	// Draw box
	void drawBox(int x, int y, int width, int height, int textColor, int bgColor = BLACK)
	{
		char horizontalLine = 205; // -
		char verticalLine = 186;	 // �
		char topLeft = 201;				 // +
		char topRight = 187;			 // +
		char bottomLeft = 200;		 // +
		char bottomRight = 188;		 // +

		setColor(textColor, bgColor);

		// Draw top line
		setCursorPosition(x, y);
		cout << topLeft;
		for (int i = 0; i < width - 2; i++)
		{
			cout << horizontalLine;
		}
		cout << topRight;

		// Draw sides
		for (int i = 1; i < height - 1; i++)
		{
			setCursorPosition(x, y + i);
			cout << verticalLine;
			setCursorPosition(x + width - 1, y + i);
			cout << verticalLine;
		}

		// Draw bottom line
		setCursorPosition(x, y + height - 1);
		cout << bottomLeft;
		for (int i = 0; i < width - 2; i++)
		{
			cout << horizontalLine;
		}
		cout << bottomRight;

		resetColor();
	}

	// Draw filled box
	void drawFilledBox(int x, int y, int width, int height, int textColor, int bgColor = BLACK)
	{
		setColor(textColor, bgColor);
		for (int i = 0; i < height; i++)
		{
			setCursorPosition(x, y + i);
			for (int j = 0; j < width; j++)
			{
				cout << " ";
			}
		}
		resetColor();
	}

	// Get key press
	int getKey()
	{
		return _getch();
	}

	// Wait for key press
	void waitForKey()
	{
		_getch();
	}

	// Check if key is pressed
	bool isKeyPressed()
	{
		return _kbhit();
	}
}

// Item class for lost and found items
class Item
{
private:
	MyString name;
	MyString category;
	MyString description;
	MyString location;
	MyString contactInfo;
	MyString date;
	MyString postedByEmail;
	bool isLost; // true = lost item, false = found item

public:
	// Constructor
	Item() : isLost(true) {}

	// Constructor with parameters
	Item(const MyString &name, const MyString &category, const MyString &description,
			 const MyString &location, const MyString &contactInfo, const MyString &date, bool isLost)
			: name(name), category(category), description(description),
				location(location), contactInfo(contactInfo), date(date), isLost(isLost) {}

	// Getters
	MyString getName() const
	{
		return name;
	}
	MyString getCategory() const
	{
		return category;
	}
	MyString getDescription() const
	{
		return description;
	}
	MyString getLocation() const
	{
		return location;
	}
	MyString getContactInfo() const
	{
		return contactInfo;
	}
	MyString getDate() const
	{
		return date;
	}
	bool getIsLost() const
	{
		return isLost;
	}

	// Setters
	void setName(const MyString &name)
	{
		this->name = name;
	}
	void setCategory(const MyString &category)
	{
		this->category = category;
	}
	void setDescription(const MyString &description)
	{
		this->description = description;
	}
	void setLocation(const MyString &location)
	{
		this->location = location;
	}
	void setContactInfo(const MyString &contactInfo)
	{
		this->contactInfo = contactInfo;
	}
	void setDate(const MyString &date)
	{
		this->date = date;
	}
	void setIsLost(bool isLost)
	{
		this->isLost = isLost;
	}
};

// Lost and Found System
class LofotixSystem
{
private:
	MyArray<Item> items;

public:
	// Add item
	void addItem(const Item &item)
	{
		items.push_back(item);
	}

	// Get all items
	const MyArray<Item> &getItems() const
	{
		return items;
	}

	// Search items by name (partial match)
	MyArray<Item> searchByName(const MyString &name)
	{
		MyArray<Item> result;
		for (size_t i = 0; i < items.size(); i++)
		{
			// Simple partial string matching (since we can't use string functions)
			bool match = false;
			const MyString &itemName = items[i].getName();

			for (size_t j = 0; j <= itemName.size() - name.size(); j++)
			{
				bool subMatch = true;
				for (size_t k = 0; k < name.size(); k++)
				{
					if (itemName[j + k] != name[k])
					{
						subMatch = false;
						break;
					}
				}
				if (subMatch)
				{
					match = true;
					break;
				}
			}

			if (match)
			{
				result.push_back(items[i]);
			}
		}
		return result;
	}

	// Search items by category
	MyArray<Item> searchByCategory(const MyString &category)
	{
		MyArray<Item> result;
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items[i].getCategory() == category)
			{
				result.push_back(items[i]);
			}
		}
		return result;
	}

	// Filter items by lost/found status
	MyArray<Item> filterByStatus(bool isLost)
	{
		MyArray<Item> result;
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items[i].getIsLost() == isLost)
			{
				result.push_back(items[i]);
			}
		}
		return result;
	}

	void saveToFile(const char *filename)
	{
		std::ofstream out(filename);
		if (!out.is_open())
			return;

		for (size_t i = 0; i < items.size(); i++)
		{
			const Item &item = items[i];
			out << item.getName().c_str() << '\n';
			out << item.getCategory().c_str() << '\n';
			out << item.getDescription().c_str() << '\n';
			out << item.getLocation().c_str() << '\n';
			out << item.getContactInfo().c_str() << '\n';
			out << item.getDate().c_str() << '\n';
			out << item.getIsLost() << '\n'; // 1 for lost, 0 for found
			out << "---\n";									 // separator
		}

		out.close();
	}

	void loadFromFile(const char *filename)
	{
		std::ifstream in(filename);
		if (!in.is_open())
			return;

		while (!in.eof())
		{
			std::string name, category, desc, loc, contact, date, email, sep;
			bool isLost;

			if (!std::getline(in, name))
				break;
			if (!std::getline(in, category))
				break;
			if (!std::getline(in, desc))
				break;
			if (!std::getline(in, loc))
				break;
			if (!std::getline(in, contact))
				break;
			if (!std::getline(in, date))
				break;
			in >> isLost;
			in.ignore();					 // ignore newline after isLost
			std::getline(in, sep); // read separator line

			Item item(MyString(name.c_str()), MyString(category.c_str()), MyString(desc.c_str()),
								MyString(loc.c_str()), MyString(contact.c_str()), MyString(date.c_str()), isLost);
			items.push_back(item);
		}

		in.close();
	}

	MyArray<Item> getItemsByEmail(const MyString &email)
	{
		MyArray<Item> result;
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items[i].getPostedByEmail() == email)
			{
				result.push_back(items[i]);
			}
		}
		return result;
	}

	void clearItems()
	{
		items.clear(); // this calls MyArray<Item>::clear()
	}
};

// User Interface
class LofotixUI
{
private:
	LofotixSystem system;
	bool running;

	// Display splash screen animation
	void showSplashScreen()
	{
		using namespace ConsoleUtils;

		clearScreen();
		hideCursor();

		int width = getConsoleWidth();
		int height = getConsoleHeight();

		// Draw background
		drawFilledBox(0, 0, width, height, WHITE, DARK_BLUE);

		// Logo animation
		const char *logo[] = {
				//    "  _      _____   ________  _____   _________  __  _      _ ",
				//    " | |    / __  \  |||||||| / __  \  |||||||||  ||  \ \   / / ",
				//    " | |    | |  | | |        | |  | |    | |     ||   \ \ / / ",
				//    " | |    | |  | | |||||||| | |  | |    | |     ||    \ \ \ ",
				//    " | |___ | |__| | |        | |  | |    | |     ||   / \ \  ",
				//    " |______\ \ ___/ |        \ \ ___/    | |     ||  / / \ \ "

				"  _      ____   _____  ____  _____ _____ ___  __",
				" | |    / __ \\ / ____|/ __ \\|  __ \\_   _|__ \\/_ |",
				" | |   | |  | | (___ | |  | | |__) || |    ) || |",
				" | |   | |  | |\\___ \\| |  | |  ___/ | |   / / | |",
				" | |___| |__| |____) | |__| | |    _| |_ / /_ | |",
				" |______\\____/|_____/ \\____/|_|   |_____|____||_|"};

		// Calculate center position
		int logoHeight = 6;
		int startY = (height - logoHeight) / 2 - 3;

		// Animate logo appearance
		for (int i = 0; i < logoHeight; i++)
		{
			printCentered(logo[i], startY + i, YELLOW, DARK_BLUE);
			Sleep(150);
		}

		// Animate tagline
		printCentered("= Lost and Found System for FAST NUCES Lahore =", startY + logoHeight + 1, WHITE, DARK_BLUE);
		Sleep(200);

		// Loading animation
		printCentered("[", startY + logoHeight + 3, CYAN, DARK_BLUE);
		printCentered("]", startY + logoHeight + 3, CYAN, DARK_BLUE);

		int loadingWidth = 40;
		int startX = (width - loadingWidth) / 2;

		for (int i = 0; i < loadingWidth - 2; i++)
		{
			setCursorPosition(startX + 1 + i, startY + logoHeight + 3);
			setColor(GREEN, DARK_BLUE);
			cout << "=";
			Sleep(30);
		}

		printCentered("Press any key to continue...", startY + logoHeight + 5, WHITE, DARK_BLUE);

		waitForKey();
		showCursor();
	}

	// Display main menu
	int showMainMenu()
	{
		using namespace ConsoleUtils;

		clearScreen();

		int width = getConsoleWidth();
		int height = getConsoleHeight();

		// Draw header
		drawFilledBox(0, 0, width, 3, WHITE, DARK_BLUE);
		printCentered("LOFOTIX - Lost and Found System", 1, WHITE, DARK_BLUE);

		// Draw main content area
		drawFilledBox(0, 3, width, height - 6, WHITE, BLACK);

		// Draw footer
		drawFilledBox(0, height - 3, width, 3, WHITE, DARK_BLUE);
		printCentered("FAST NUCES Lahore", height - 2, WHITE, DARK_BLUE);

		// Draw menu box
		int menuWidth = 50;
		int menuHeight = 15;
		int menuX = (width - menuWidth) / 2;
		int menuY = (height - menuHeight) / 2;

		drawBox(menuX, menuY, menuWidth, menuHeight, CYAN);

		// Print menu items
		printCentered("===== MAIN MENU =====", menuY + 2, YELLOW);
		printCentered("1. Report Lost Item", menuY + 4, WHITE);
		printCentered("2. Report Found Item", menuY + 5, WHITE);
		printCentered("3. View All Lost Items", menuY + 6, WHITE);
		printCentered("4. View All Found Items", menuY + 7, WHITE);
		printCentered("5. Search Items", menuY + 8, WHITE);
		printCentered("6. Exit", menuY + 10, WHITE);

		printCentered("Enter your choice: ", menuY + 12, GREEN);

		char choice = static_cast<char>(getKey());
		return choice - '0';
	}

	// Add a new item (lost or found)
	void addNewItem(bool isLost)
	{
		using namespace ConsoleUtils;

		clearScreen();

		int width = getConsoleWidth();

		// Draw header
		drawFilledBox(0, 0, width, 3, WHITE, DARK_BLUE);
		if (isLost)
		{
			printCentered("REPORT LOST ITEM", 1, WHITE, DARK_BLUE);
		}
		else
		{
			printCentered("REPORT FOUND ITEM", 1, WHITE, DARK_BLUE);
		}

		// Draw form
		int formX = 10;
		int formY = 5;

		Item newItem;
		newItem.setIsLost(isLost);

		MyString input;

		setColor(YELLOW);
		setCursorPosition(formX, formY);
		cout << "Item Name: ";
		setColor(WHITE);
		// cin.ignore(numeric_limits<streamsize>max(), '\n');
		input.getLine();
		newItem.setName(input);

		setColor(YELLOW);
		setCursorPosition(formX, formY + 2);
		cout << "Category: ";
		setColor(WHITE);
		input.getLine();
		newItem.setCategory(input);

		setColor(YELLOW);
		setCursorPosition(formX, formY + 4);
		cout << "Description: ";
		setColor(WHITE);
		input.getLine();
		newItem.setDescription(input);

		setColor(YELLOW);
		setCursorPosition(formX, formY + 6);
		cout << "Location: ";
		setColor(WHITE);
		input.getLine();
		newItem.setLocation(input);

		setColor(YELLOW);
		setCursorPosition(formX, formY + 8);
		cout << "Contact Information: ";
		setColor(WHITE);
		input.getLine();
		newItem.setContactInfo(input);

		// Get current date
		time_t now = time(0);
		tm *ltm = localtime(&now);
		char dateStr[20];
		sprintf(dateStr, "%02d/%02d/%d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
		newItem.setDate(MyString(dateStr));

		// Add item to system
		system.addItem(newItem);

		setColor(GREEN);
		setCursorPosition(formX, formY + 10);
		if (isLost)
		{
			cout << "Lost item reported successfully!";
		}
		else
		{
			cout << "Found item reported successfully!";
		}

		setColor(WHITE);
		setCursorPosition(formX, formY + 12);
		cout << "Press any key to return to main menu...";

		waitForKey();
	}

	// Display list of items
	void displayItems(const MyArray<Item> &items, const char *title)
	{
		using namespace ConsoleUtils;

		clearScreen();

		int width = getConsoleWidth();

		// Draw header
		drawFilledBox(0, 0, width, 3, WHITE, DARK_BLUE);
		printCentered(title, 1, WHITE, DARK_BLUE);

		if (items.size() == 0)
		{
			printCentered("No items to display", 10, YELLOW);
			printCentered("Press any key to return to main menu...", 12, WHITE);
			waitForKey();
			return;
		}

		// Display table header
		setCursorPosition(5, 5);
		setColor(CYAN);
		cout << "Name";
		setCursorPosition(25, 5);
		cout << "Category";
		setCursorPosition(45, 5);
		cout << "Location";
		setCursorPosition(65, 5);
		cout << "Date";
		setCursorPosition(80, 5);
		cout << "Contact";

		// Draw separator line
		setColor(DARK_GRAY);
		for (int i = 5; i < width - 5; i++)
		{
			setCursorPosition(i, 6);
			cout << "-";
		}

		// Display items
		for (size_t i = 0; i < items.size(); i++)
		{
			const Item &item = items[i];

			if (item.getIsLost())
			{
				setColor(RED);
			}
			else
			{
				setColor(GREEN);
			}

			setCursorPosition(5, 7 + static_cast<int>(i));
			cout << item.getName().c_str();

			setCursorPosition(25, 7 + static_cast<int>(i));
			cout << item.getCategory().c_str();

			setCursorPosition(45, 7 + static_cast<int>(i));
			cout << item.getLocation().c_str();

			setCursorPosition(65, 7 + static_cast<int>(i));
			cout << item.getDate().c_str();

			setCursorPosition(80, 7 + static_cast<int>(i));
			cout << item.getContactInfo().c_str();
		}

		setColor(WHITE);
		setCursorPosition(5, 7 + static_cast<int>(items.size()) + 2);
		cout << "Press any key to return to main menu...";

		waitForKey();
	}

	// Search items menu
	void searchItems()
	{
		using namespace ConsoleUtils;

		clearScreen();

		int width = getConsoleWidth();

		// Draw header
		drawFilledBox(0, 0, width, 3, WHITE, DARK_BLUE);
		printCentered("SEARCH ITEMS", 1, WHITE, DARK_BLUE);

		// Draw menu box
		int menuWidth = 50;
		int menuHeight = 10;
		int menuX = (width - menuWidth) / 2;
		int menuY = 6;

		drawBox(menuX, menuY, menuWidth, menuHeight, CYAN);

		// Print menu items
		printCentered("===== SEARCH OPTIONS =====", menuY + 2, YELLOW);
		printCentered("1. Search by Name", menuY + 4, WHITE);
		printCentered("2. Search by Category", menuY + 5, WHITE);
		printCentered("3. Return to Main Menu", menuY + 7, WHITE);

		printCentered("Enter your choice: ", menuY + 9, GREEN);

		char choice = static_cast<char>(getKey());
		int option = choice - '0';

		if (option == 1)
		{
			searchByName();
		}
		else if (option == 2)
		{
			searchByCategory();
		}
	}

	// Search by name
	void searchByName()
	{
		using namespace ConsoleUtils;

		clearScreen();

		int width = getConsoleWidth();

		// Draw header
		drawFilledBox(0, 0, width, 3, WHITE, DARK_BLUE);
		printCentered("SEARCH BY NAME", 1, WHITE, DARK_BLUE);

		// Get search term
		setCursorPosition(10, 5);
		setColor(YELLOW);
		cout << "Enter item name to search: ";
		setColor(WHITE);

		MyString searchTerm;
		// cin.ignore(numeric_limits<streamsize>max(), '\n');
		searchTerm.getLine();

		// Search and display results
		MyArray<Item> results = system.searchByName(searchTerm);

		if (results.size() == 0)
		{
			printCentered("No matches found", 8, RED);
		}
		else
		{
			setCursorPosition(10, 7);
			setColor(GREEN);
			cout << "Found " << results.size() << " matches:";

			// Display table header
			setCursorPosition(5, 9);
			setColor(CYAN);
			cout << "Name";
			setCursorPosition(25, 9);
			cout << "Category";
			setCursorPosition(45, 9);
			cout << "Location";
			setCursorPosition(65, 9);
			cout << "Status";

			// Draw separator line
			setColor(DARK_GRAY);
			for (int i = 5; i < width - 5; i++)
			{
				setCursorPosition(i, 10);
				cout << "-";
			}

			// Display results
			for (size_t i = 0; i < results.size(); i++)
			{
				const Item &item = results[i];

				if (item.getIsLost())
				{
					setColor(RED);
				}
				else
				{
					setColor(GREEN);
				}

				setCursorPosition(5, 11 + static_cast<int>(i));
				cout << item.getName().c_str();

				setCursorPosition(25, 11 + static_cast<int>(i));
				cout << item.getCategory().c_str();

				setCursorPosition(45, 11 + static_cast<int>(i));
				cout << item.getLocation().c_str();

				setCursorPosition(65, 11 + static_cast<int>(i));
				if (item.getIsLost())
				{
					setColor(RED);
					cout << "LOST";
				}
				else
				{
					setColor(GREEN);
					cout << "FOUND";
				}
			}
		}

		setColor(WHITE);
		setCursorPosition(10, 12 + static_cast<int>(results.size()));
		cout << "Press any key to return to search menu...";

		waitForKey();
	}

	// Search by category
	void searchByCategory()
	{
		using namespace ConsoleUtils;

		clearScreen();

		int width = getConsoleWidth();

		// Draw header
		drawFilledBox(0, 0, width, 3, WHITE, DARK_BLUE);
		printCentered("SEARCH BY CATEGORY", 1, WHITE, DARK_BLUE);

		// Get search term
		setCursorPosition(10, 5);
		setColor(YELLOW);
		cout << "Enter category to search: ";
		setColor(WHITE);

		MyString searchTerm;
		// cin.ignore(numeric_limits<streamsize>max(), '\n');
		searchTerm.getLine();

		// Search and display results
		MyArray<Item> results = system.searchByCategory(searchTerm);

		if (results.size() == 0)
		{
			printCentered("No matches found", 8, RED);
		}
		else
		{
			setCursorPosition(10, 7);
			setColor(GREEN);
			cout << "Found " << results.size() << " matches:";

			// Display table header
			setCursorPosition(5, 9);
			setColor(CYAN);
			cout << "Name";
			setCursorPosition(25, 9);
			cout << "Category";
			setCursorPosition(45, 9);
			cout << "Location";
			setCursorPosition(65, 9);
			cout << "Status";

			// Draw separator line
			setColor(DARK_GRAY);
			for (int i = 5; i < width - 5; i++)
			{
				setCursorPosition(i, 10);
				cout << "-";
			}

			// Display results
			for (size_t i = 0; i < results.size(); i++)
			{
				const Item &item = results[i];

				if (item.getIsLost())
				{
					setColor(RED);
				}
				else
				{
					setColor(GREEN);
				}

				setCursorPosition(5, 11 + static_cast<int>(i));
				cout << item.getName().c_str();

				setCursorPosition(25, 11 + static_cast<int>(i));
				cout << item.getCategory().c_str();

				setCursorPosition(45, 11 + static_cast<int>(i));
				cout << item.getLocation().c_str();

				setCursorPosition(65, 11 + static_cast<int>(i));
				if (item.getIsLost())
				{
					setColor(RED);
					cout << "LOST";
				}
				else
				{
					setColor(GREEN);
					cout << "FOUND";
				}
			}
		}

		setColor(WHITE);
		setCursorPosition(10, 12 + static_cast<int>(results.size()));
		cout << "Press any key to return to search menu...";

		waitForKey();
	}

	// Display item details
	void displayItemDetails(const Item &item)
	{
		using namespace ConsoleUtils;

		clearScreen();

		int width = getConsoleWidth();
		int height = getConsoleHeight();

		// Draw header
		drawFilledBox(0, 0, width, 3, WHITE, DARK_BLUE);
		printCentered("ITEM DETAILS", 1, WHITE, DARK_BLUE);

		// Draw details box
		int boxWidth = 70;
		int boxHeight = 16;
		int boxX = (width - boxWidth) / 2;
		int boxY = 5;

		drawBox(boxX, boxY, boxWidth, boxHeight, CYAN);

		// Set status color
		if (item.getIsLost())
		{
			setColor(RED);
			printCentered("*** LOST ITEM ***", boxY + 2, RED);
		}
		else
		{
			setColor(GREEN);
			printCentered("*** FOUND ITEM ***", boxY + 2, GREEN);
		}

		// Display item details
		int labelX = boxX + 5;
		int valueX = boxX + 20;

		setColor(YELLOW);
		setCursorPosition(labelX, boxY + 4);
		cout << "Name:";
		setColor(WHITE);
		setCursorPosition(valueX, boxY + 4);
		cout << item.getName().c_str();

		setColor(YELLOW);
		setCursorPosition(labelX, boxY + 6);
		cout << "Category:";
		setColor(WHITE);
		setCursorPosition(valueX, boxY + 6);
		cout << item.getCategory().c_str();

		setColor(YELLOW);
		setCursorPosition(labelX, boxY + 8);
		cout << "Description:";
		setColor(WHITE);
		setCursorPosition(valueX, boxY + 8);
		cout << item.getDescription().c_str();

		setColor(YELLOW);
		setCursorPosition(labelX, boxY + 10);
		cout << "Location:";
		setColor(WHITE);
		setCursorPosition(valueX, boxY + 10);
		cout << item.getLocation().c_str();

		setColor(YELLOW);
		setCursorPosition(labelX, boxY + 12);
		cout << "Date:";
		setColor(WHITE);
		setCursorPosition(valueX, boxY + 12);
		cout << item.getDate().c_str();

		setColor(YELLOW);
		setCursorPosition(labelX, boxY + 14);
		cout << "Contact Info:";
		setColor(WHITE);
		setCursorPosition(valueX, boxY + 14);
		cout << item.getContactInfo().c_str();

		// Draw back button
		drawBox(boxX + 25, boxY + boxHeight + 2, 20, 3, CYAN);
		printCentered("Back [B]", boxY + boxHeight + 3, WHITE);

		// Wait for key press
		bool validKey = false;
		while (!validKey)
		{
			char key = static_cast<char>(getKey());
			if (key == 'b' || key == 'B')
			{
				validKey = true;
			}
		}
	}

public:
	// Constructor
	LofotixUI() : running(true) {}

	// Initialize with sample data (for testing)
	//	void initWithSampleData() {
	//		// Create sample lost items
	//		Item item1(MyString("Laptop"), MyString("Electronics"),
	//			MyString("HP Pavilion, silver color"),
	//			MyString("CS Building, Lab 4"),
	//			MyString("Ali: 0300-1234567"),
	//			MyString("25/04/2025"), true);
	//
	//		Item item2(MyString("Water Bottle"), MyString("Personal Item"),
	//			MyString("Blue metal bottle with Fast logo"),
	//			MyString("Cafeteria"),
	//			MyString("Sara: 0321-7654321"),
	//			MyString("26/04/2025"), true);
	//
	//		// Create sample found items
	//		Item item3(MyString("Calculator"), MyString("Electronics"),
	//			MyString("Scientific calculator, Casio fx-991ES"),
	//			MyString("EE Building, Room 302"),
	//			MyString("Lost & Found Office: 042-111-128-128"),
	//			MyString("24/04/2025"), false);
	//
	//		Item item4(MyString("USB Drive"), MyString("Electronics"),
	//			MyString("16GB SanDisk black USB"),
	//			MyString("Library, Computer Section"),
	//			MyString("Librarian: 042-111-128-129"),
	//			MyString("27/04/2025"), false);
	//
	//		// Add items to the system
	//		system.addItem(item1);
	//		system.addItem(item2);
	//		system.addItem(item3);
	//		system.addItem(item4);
	//	}

	void initDataFromFile()
	{
		system.loadFromFile("items.txt");
	}

	// Start the UI
	void start()
	{
		using namespace ConsoleUtils;

		// Configure console
		// system("title Lofotix: Lost and Found System for FAST NUCES Lahore");
		// system("mode con cols=100 lines=35");

		// Initialize with sample data for demonstration
		//		initWithSampleData();
		initDataFromFile();

		// Show splash screen
		showSplashScreen();

		// Main loop
		while (running)
		{
			int choice = showMainMenu();

			switch (choice)
			{
			case 1: // Report Lost Item
				addNewItem(true);
				break;
			case 2: // Report Found Item
				addNewItem(false);
				break;
			case 3: // View All Lost Items
				displayItems(system.filterByStatus(true), "ALL LOST ITEMS");
				break;
			case 4: // View All Found Items
				displayItems(system.filterByStatus(false), "ALL FOUND ITEMS");
				break;
			case 5: // Search Items
				searchItems();
				break;
			case 6: // Exit
				running = false;
				break;
			default:
				break;
			}
		}

		// Show exit message
		system.saveToFile("items.txt");
		clearScreen();
		drawFilledBox(0, 0, getConsoleWidth(), getConsoleHeight(), WHITE, DARK_BLUE);

		int centerY = getConsoleHeight() / 2;
		printCentered("Thank you for using Lofotix!", centerY - 2, YELLOW, DARK_BLUE);
		printCentered("Lost and Found System for FAST NUCES Lahore", centerY, WHITE, DARK_BLUE);
		printCentered("Press any key to exit...", centerY + 3, CYAN, DARK_BLUE);

		waitForKey();
		clearScreen();
	}
};

// Main function
int main()
{
	// Set console properties for best visual experience
	system("title Lofotix: Lost and Found System for FAST NUCES Lahore");
	system("mode con cols=100 lines=35");

	// Seed random number generator for any animations
	srand(static_cast<unsigned int>(time(NULL)));

	// Create and start the UI
	LofotixUI ui;
	ui.start();

	return 0;
}
