#include <iostream>
#include <thread>
#include <type_traits>
#include <map>
#include <cmath>

// Question 1 Install g tests and add to cmakes lists
#include <gtest/gtest.h>

const int values[] = { 1,2,3,4,5 };
const int NVALS = sizeof values / sizeof (int);
void function(char**);
void fn(const int** pp);

template <typename T>
struct ptr_holder {
  static_assert(!std::is_same<T, typename std::remove_pointer<T>::type>());
  T* thePtr;
};

int total = 0;

class Wallet
{
    int mMoney;
    std::mutex theMutex;
public:
    Wallet() :mMoney(0) {}
    int getMoney() { return mMoney; }
    void addMoney(int money)
    {
        theMutex.lock();
        for(int i = 0; i < money; ++i)
        {
            mMoney++;
        }
        theMutex.unlock();
    }
};

class Foo {
public:
    Foo(int a, Wallet* b = nullptr) {};
};

struct person{
   int age;
   float weight;
};

TEST(WalletTest, ConcurrentWallet)
{
    for (int k = 0; k < 1000; ++k)
    {
        Wallet walletObject;
        std::vector<std::thread> threads;
        threads.reserve(5);

        for (int i = 0; i < 5; ++i)
        {
            threads.emplace_back(&Wallet::addMoney, &walletObject, 1000);
        }

        std::for_each(threads.begin(), threads.end(),
                      [](auto& aThread){ aThread.join(); });

        int val = 0;
        ASSERT_EQ(val = walletObject.getMoney(), 5000)
            << " Error at count = " << k << " Money in Wallet = " << val;
    }
}

int main()
{
    // Question 2
    int x = 10;
    int y = 15;
    std::cout << "(" << x << ", " << y << ")" << std::endl;


    // Question 3 Get the function to run
    char *arr[] = { "ant", "bat", "cat", "dog", "egg", "fly" };
	function(arr);


    // Question 4 Insert in map
    typedef std::map<int, double> valmap;

    valmap m;

    for (int i = 0; i < NVALS; i++)
        m.insert(std::make_pair(values[i], pow(values[i], .5)));

    // Intent not clear. However, initialized iterators
    valmap::iterator it;
    valmap::iterator it2;
    m.insert(std::make_pair(1,2));


    // Question 5
    int i = 1, j = 1;
    if ((i != 3) && (j == 1))
    {
        std::cout << "inside if statement\n";
    }


    // Question 6 Store a char * pointer in template
    ptr_holder<char *> p{nullptr};


    // Question 7 Fix the compiler errors and race conditions
    // Convert the testerFunction() into a google test
    ::testing::InitGoogleTest();
    RUN_ALL_TESTS();


    // Question 8
    int n = 1;
    const int *p2 = &n;
    fn(&p2);


    // Question 9
    auto ptr = std::make_unique<person>(person{10, 55.5f});


    // Question 10 Initialise foo
    Foo foo{0};


    // Question 11
    int c;
    while((c = getchar()) != EOF)
    {
        putchar(c);
    }

    return 0;
}

// Do not change anything besides the ptr variable
void function(char **ptr)
{
	char *ptr1;
	ptr1 = (ptr += sizeof(int))[-2];
	printf("%s\n", ptr1);
}

void fn(const int** pp)
{
    printf("%p : %p : %d", pp, *pp, **pp);
}